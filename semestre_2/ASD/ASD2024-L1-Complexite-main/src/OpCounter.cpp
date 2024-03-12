#include <cstring>
#include "OpCounter.h"

size_t OpCounter::nb_comp = 0;
size_t OpCounter::nb_affec = 0;

bool OpCounter::operator<(const OpCounter& b) const{
    ++nb_comp;
    return value < b.get_value();
}

OpCounter& OpCounter::operator=(const OpCounter& b) {
    ++nb_affec;
    value = b.value;
    return *this;
}

OpCounter& OpCounter::operator+=(const OpCounter& n) {
    value += n.get_value();
    return *this;
}

OpCounter& OpCounter::operator++() {
    ++value;
    return *this;
}
