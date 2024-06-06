#ifndef HASHMAP_CHAINAGE_H
#define HASHMAP_CHAINAGE_H

#include <vector>
#include <forward_list>
#include <ostream>
#include <utility>    // pair, equal_to
#include <functional> // hash
#include <iostream>

template <typename Key, typename Value, typename HashKey, typename EqualKey>
class HashMapChainage;

template <typename Key, typename Value, typename HashKey, typename EqualKey>
std::ostream & operator<<(std::ostream &, const HashMapChainage<Key,Value, HashKey, EqualKey> &);

template <typename Key,
        typename Value,
        typename HashKey = std::hash<Key>,
        typename EqualKey = std::equal_to<Key>>
class HashMapChainage {
   HashKey hash_function;
   EqualKey is_equal;

   std::vector<std::forward_list<std::pair<const Key,Value>>> data;
   size_t size;
   float mlf;

public:
   HashMapChainage();

   Value& operator[](Key const& key);
   size_t erase(Key const&);
   void rehash(size_t);

   [[nodiscard]] float load_factor() const noexcept;
   [[nodiscard]] float max_load_factor() const noexcept;
   void max_load_factor ( float z );

   friend std::ostream & operator<< <>(std::ostream &, const HashMapChainage &);
};

// votre mise en oeuvre vient ici
template<typename Key, typename Value, typename HashKey, typename EqualKey>
HashMapChainage<Key, Value, HashKey, EqualKey>::HashMapChainage(): size(0), mlf(1.0f) {
    data.resize(2);
    for(size_t x = 0; x < data.size(); ++x){
        data[x].push_front({"",0});
    }
}

template <typename Key, typename Value, typename HashKey, typename EqualKey>
Value& HashMapChainage<Key, Value, HashKey, EqualKey>::operator[](Key const& key) {
    size_t index = hash_function(key) % data.size();
    for (auto& pair : data[index]) {
        if (is_equal(pair.first, key)) {
            return pair.second;
        }
    }

    data[index].emplace_front(key, Value{});
    ++size;

    if (load_factor() >= max_load_factor()) {
        rehash(data.size() * 2);
    }

    return data[index].front().second;
}

template <typename Key, typename Value, typename HashKey, typename EqualKey>
size_t HashMapChainage<Key, Value, HashKey, EqualKey>::erase(Key const& key) {
    size_t index = hash_function(key) % data.size();
    auto& chain = data[index];
    auto it = chain.before_begin();
    for (auto current = chain.begin(); current != chain.end(); ++it, ++current) {
        if (is_equal(current->first, key)) {
            chain.erase_after(it);
            --size;
            return 1;
        }
    }
    return 0;
}

template <typename Key, typename Value, typename HashKey, typename EqualKey>
void HashMapChainage<Key, Value, HashKey, EqualKey>::rehash(size_t new_size) {
    std::vector<std::forward_list<std::pair<const Key, Value>>> new_data(new_size);

    for(size_t x = 0; x < new_data.size(); ++x){
        new_data[x].push_front({"",0});
    }

    for (auto& chain : data) {
        for (auto& pair : chain) {
            if (pair.first != ""){
                size_t index = hash_function(pair.first) % new_size;
                new_data[index].push_front(pair);
            }
        }
    }
    data = std::move(new_data);
}

template<typename Key, typename Value, typename HashKey, typename EqualKey>
void HashMapChainage<Key, Value, HashKey, EqualKey>::max_load_factor(float z) {
    mlf = z;
}

template<typename Key, typename Value, typename HashKey, typename EqualKey>
float HashMapChainage<Key, Value, HashKey, EqualKey>::load_factor() const noexcept {
    return static_cast<float>(size) / data.size();
}

template<typename Key, typename Value, typename HashKey, typename EqualKey>
float HashMapChainage<Key, Value, HashKey, EqualKey>::max_load_factor() const noexcept {
    return mlf;
}

template <typename Key, typename Value, typename HashKey, typename EqualKey>
std::ostream& operator<<(std::ostream &os, const HashMapChainage<Key,Value, HashKey, EqualKey> &hashMapChainage){
    for(size_t i = 0; i < hashMapChainage.data.size(); ++i){
        auto dataX = hashMapChainage.data[i];
        os << (i+1) << " : ";
        for (auto j = dataX.cbegin(); j != dataX.cend(); ++j){
            if (j != dataX.cbegin()){
                os << " -> ";
            }

            if (j->first != ""){
                os << "(" << j->first << "," << j->second << ")";
            } else{
                os << " NULL";
            }
        }
        os << std::endl;
    }

    return os;
}


#endif //HASHMAP_CHAINAGE_H
