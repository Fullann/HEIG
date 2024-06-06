#ifndef HASHMAP_SONDAGE_H
#define HASHMAP_SONDAGE_H

#include <vector>
#include <ostream>
#include <utility>    // pair, equal_to
#include <functional> // hash

template <typename Key, typename Value, typename HashKey, typename EqualKey>
class HashMapSondage;

template <typename Key, typename Value, typename HashKey, typename EqualKey>
std::ostream& operator<<(std::ostream&, const HashMapSondage<Key, Value, HashKey, EqualKey>&);

template <typename Key,
        typename Value,
        typename HashKey = std::hash<Key>,
        typename EqualKey = std::equal_to<Key>>
class HashMapSondage {
    HashKey hash_function;
    EqualKey is_equal;

    std::vector<std::pair<Key, Value>> data;
    std::vector<bool> is_used;
    size_t size;
    float mlf;

public:
    HashMapSondage() : size(0), mlf(1.0f), data(8), is_used(8, false) {}

    Value& operator[](Key const& key) {
        if (load_factor() > mlf) {
            rehash(data.size() * 2);
        }

        size_t idx = hash_function(key) % data.size();
        size_t start_idx = idx;
        while (is_used[idx]) {
            if (is_equal(data[idx].first, key)) {
                return data[idx].second;
            }
            idx = (idx + 1) % data.size();
            if (idx == start_idx) {
                rehash(data.size() * 2);
                idx = hash_function(key) % data.size();
                start_idx = idx;
            }
        }
        data[idx] = {key, Value{}};
        is_used[idx] = true;
        ++size;
        return data[idx].second;
    }

    size_t erase(Key const& key) {
        size_t idx = hash_function(key) % data.size();
        size_t start_idx = idx;
        while (is_used[idx]) {
            if (is_equal(data[idx].first, key)) {
                is_used[idx] = false;
                --size;
                size_t next_idx = (idx + 1) % data.size();
                while (is_used[next_idx]) {
                    auto kv = std::move(data[next_idx]);
                    is_used[next_idx] = false;
                    --size;
                    (*this)[kv.first] = kv.second;
                    next_idx = (next_idx + 1) % data.size();
                    if (next_idx == start_idx) {
                        break;
                    }
                }
                return 1;
            }
            idx = (idx + 1) % data.size();
            if (idx == start_idx) {
                break;
            }
        }
        return 0;
    }

    void rehash(size_t new_size) {
        std::vector<std::pair<Key, Value>> new_data(new_size);
        std::vector<bool> new_is_used(new_size, false);

        for (size_t i = 0; i < data.size(); ++i) {
            if (is_used[i]) {
                size_t new_idx = hash_function(data[i].first) % new_size;
                while (new_is_used[new_idx]) {
                    new_idx = (new_idx + 1) % new_size;
                }
                new_data[new_idx] = std::move(data[i]);
                new_is_used[new_idx] = true;
            }
        }
        data = std::move(new_data);
        is_used = std::move(new_is_used);
    }

    [[nodiscard]] float load_factor() const noexcept {
        return static_cast<float>(size) / data.size();
    }

    [[nodiscard]] float max_load_factor() const noexcept {
        return mlf;
    }

    void max_load_factor(float z) {
        mlf = z;
    }

    friend std::ostream& operator<< <>(std::ostream& os, const HashMapSondage& map) {
        os << "LF: " << map.load_factor() << " ";
        for (size_t i = 0; i < map.data.size(); ++i) {
            if (map.is_used[i]) {
                os << "(" << map.hash_function(map.data[i].first) % map.data.size() << ":" << map.data[i].first << "," << map.data[i].second << ") ";
            } else {
                os << "() ";
            }
        }
        return os;
    }
};

#endif //HASHMAP_SONDAGE_H
