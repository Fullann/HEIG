#include <ostream>
using std::ostream, std::endl;

#include <iostream>
using std::cout;

#include <stdexcept>
using std::exception;

#include "util.h"

C::C(int i) : valeur(i), explosif(false) {
    cout << " C(" << valeur << ") ";
}

C::C(const C& c) : valeur(c.valeur), explosif(c.explosif) {
    if(explosif) throw exception();
    cout << " CP(" << valeur << ") ";
}

C& C::operator= (const C& other) {
    if(explosif) throw exception();
    valeur = other.valeur;
    explosif = other.explosif;
    cout << " =(" << valeur << ") ";
    return *this;
}

void C::rendExplosif() {
   explosif = true;
}

C::~C() {
    cout << " D(" << valeur << ") ";
}

ostream& operator<<(ostream& s, const C& c) {
    s << c.valeur;
    return s;
}
