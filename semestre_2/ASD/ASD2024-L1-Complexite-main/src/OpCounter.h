#ifndef ASD2022_L1_COMPLEXITE_OPCOUNTER_H
#define ASD2022_L1_COMPLEXITE_OPCOUNTER_H
#include <cstring>
class OpCounter{
    int value;
    static std::size_t nb_comp;
    static std::size_t nb_affec;
public:
    OpCounter():value(0){}
    OpCounter(int v):value(v){}
    OpCounter(const OpCounter& a):value(a.get_value()){
        ++nb_affec;
    }

    int get_value() const { return value;}
    static size_t get_nb_comp(){ return nb_comp;}
    static size_t get_nb_affec(){ return nb_affec;}

    bool operator<(const OpCounter& b) const;
    OpCounter& operator=(const OpCounter& b);
    OpCounter& operator+=(const OpCounter& n);
    OpCounter& operator++();

    static void reset_all(){
        nb_comp=0;
        nb_affec=0;
    }
};

#endif //ASD2022_L1_COMPLEXITE_OPCOUNTER_H
