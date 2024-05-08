#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies

template < class T >
class ArrayDeque {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using size_type = std::size_t;

    ArrayDeque(size_type _capacite = 0) : debut(0),
                                          taille(0),
                                          capacite(_capacite),
                                          buffer(nullptr) {
        if (capacite)
            buffer = reinterpret_cast<pointer> (
                    ::operator new(capacite * sizeof(value_type)));
    }

    ArrayDeque(const ArrayDeque<value_type> &ad)
            : buffer(nullptr), capacite(ad.capacite), debut(ad.debut), taille(0) {
        if (ad.capacite) {
            // Allouer un nouveau tampon
            buffer = reinterpret_cast<pointer>(::operator new(ad.capacite * sizeof(value_type)));

            try {
                // Copier les éléments de l'autre tableau
                for (size_type i = 0; i < ad.taille; ++i) {
                    size_type offset = ad.i_physique(i);
                    new(&buffer[offset]) value_type(ad.buffer[offset]);
                    ++taille;
                }
            } catch (...) {
                // En cas d'exception, nettoyer la mémoire allouée
                for (size_type j = 0; j < taille; ++j) {
                    buffer[(debut + j) % capacite].~value_type();
                }
                ::operator delete(buffer);
                throw;
            }
        }
    }

    ~ArrayDeque() {
        if (buffer) {
            for (size_type i = 0; i < taille; ++i) {
                (*(buffer + i_physique(i))).~value_type();
            }
            ::operator delete(buffer);
        }
    }

    ArrayDeque<value_type> &operator=(const ArrayDeque<value_type> &rhs) {
        if (this == &rhs) {
            return *this;
        }

        ArrayDeque<value_type> tmp{rhs};
        swap(tmp);
        return *this;
    }

    ArrayDeque<value_type> &operator=(ArrayDeque<value_type> &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        ArrayDeque<value_type> tmp = std::move(rhs);
        swap(tmp);
        return *this;
    }

    //Retourn l'indice physique
    [[nodiscard]] size_type i_physique(size_type i_logique) const{
        return (debut + i_logique + capacite)% capacite;
    }
    //Retourne la taille
    [[nodiscard]] size_type size() const{
        return taille;
    }

    //Retourne la capacité
    [[nodiscard]] size_type capacity() const{
        return capacite;
    }

    [[nodiscard]] bool empty() const{
        return taille == 0;
    }

    //Retourne le premier élément
    reference front() const{
        return *(buffer + i_physique(0));
    }

    //Retourne le dernier élément
    reference back() const{
        return *(buffer + i_physique(taille - 1));
    }

    //Retourne l'élément à la position donnée
    reference operator[](size_type pos){
        if (pos < taille){
            return *(buffer + i_physique(pos));
        }
        else{
            throw std::out_of_range("Index hors du tableau");
        }
    }

    //Retourne l'élément à la position donnée
    const_reference operator[](size_type pos) const{
        if (pos < taille){
            return *(buffer + i_physique(pos));
        }
        else{
            throw std::out_of_range("Index hors du tableau");
        }
    }

    void swap(ArrayDeque<value_type> &ad) noexcept {
        using std::swap;
        swap(buffer, ad.buffer);
        swap(capacite, ad.capacite);
        swap(debut, ad.debut);
        swap(taille, ad.taille);
    }

    void push_front(value_type value){
        if (taille >= capacite){
            resize(!capacite ? 1 : 2*capacite);
        }

        size_type avant = i_physique(capacite-1);
        new(&buffer[avant]) value_type{value};
        debut = avant;
        ++taille;
    }

    void push_back(value_type value){
        if (taille >= capacite){
            resize(!capacite ? 1 : 2*capacite);
        }
        new(&buffer[i_physique(taille)]) value_type{value};
        ++taille;
    }

    void pop_front(){
        if (not this->empty()){
            buffer[debut].~value_type();
            debut = i_physique(1);
            --taille;
        }
        else{
            throw std::out_of_range("ArrayDeque::pop_front()");
        }
    }
    //Supprime le dernier élément
    void pop_back(){
        if (not this->empty()){
            buffer[i_physique(taille-1)].~value_type();
            --taille;
        }
        else{
            throw std::out_of_range("ArrayDeque::pop_back()");
        }
    }

    void shrink_to_fit(){
        if (capacite > taille){
            resize(taille);
        }
    }

private:
    pointer buffer;
    size_type capacite;
    size_type debut;
    size_type taille;

    // Placez ici les méthodes privées qui permettent de rendre votre code plus clair
    void resize(size_type newCapacite){
        if (newCapacite == capacite) {
            return;
        }

        ArrayDeque<value_type> temp(newCapacite);
        for (size_type i = 0; i < taille; ++i){
            temp.push_back(operator[](i));
        }

        swap(temp);
    }
};

template <typename T> inline
std::ostream& operator<<(std::ostream& s, const ArrayDeque<T>& v) {
    s << "(" << v.size() << "/" << v.capacity() << ") : ";
    if (not v.empty())
        s << v.front() << " -> " << v.back() << " : ";
    s << "[";
    for (int i = 0; i < v.size(); ++i) {
        s << v[i];
        if (i != v.size() - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

#endif /* ArrayDeque_hpp */