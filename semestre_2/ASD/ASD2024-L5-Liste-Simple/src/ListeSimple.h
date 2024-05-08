#ifndef LISTE_H
#define LISTE_H

#include <utility> // std::swap;
#include <iterator>

template <typename T>
class ListeSimple {
private:
   struct Maillon;
   struct MaillonVide {
      Maillon* suivant;
   };

   MaillonVide avant_premier; // seul attribut autorisé

   struct Maillon : public MaillonVide { // Maillon hérite de MaillonVide
      T valeur;
   };

   // Pour créer un nouveau Maillon contenant la valeur v et le pointeur p
   // Maillon* m = new Maillon{{p},v};

public:
   using value_type = T;
   using reference = T&;
   using const_reference = T const&;

    /* Classe iterator */
   class iterator {
   public:
#if _LIBCPP_STD_VER > 17
      // C++20
      using iterator_concept = std::forward_iterator_tag;
      using value_type = std::remove_cv_t<T>;
#else
      using value_type = T;
#endif
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      iterator() : m(nullptr) {}

      iterator& operator++() {
         m = m->suivant;
         return *this;
      }

      iterator operator++(int) {
         auto tmp{*this};
         operator++();
         return tmp;
      }

      friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.m == rhs.m; }

      friend bool operator!=(const iterator& lhs, const iterator& rhs) { return lhs.m != rhs.m; }

      reference operator*() const { return reinterpret_cast<Maillon*>(m)->valeur; }

      friend class ListeSimple;

   private:
      MaillonVide* m;

      explicit iterator(MaillonVide* _m) : m(_m) {}
   };

   // A compléter pour fournir ...
   //
   // sous-classe const_iterator, y compris la conversion d'iterator vers const_iterator
   //
   // cbefore_begin, before_begin (const, la version non const étant fournie),
   // cbegin, begin (const ou pas)
   // cend, end (const ou pas)
   //
   // constructeur, opérateur d'affectation et destructeur
   //
   // insert_after, erase_after, splice_after
   //
   // empty, front, push_front, pop_front, push_back swap, sort

   /* Classe const_iterator */
   class const_iterator {
   public:
#if _LIBCPP_STD_VER > 17
       // C++20
      using iterator_concept = std::forward_iterator_tag;
      using value_type = std::remove_cv_t<T>;
#else
       using value_type = T;
#endif
       using iterator_category = std::forward_iterator_tag;
       using difference_type = std::ptrdiff_t;
       using pointer = T*;
       using reference = T&;

       const_iterator() : m(nullptr) {}

       const_iterator(const iterator& i): m(i.m){}

       const_iterator operator++(){
           m = m->suivant;
           return *this;
       }

       const_iterator operator++(int){
           auto tmp{*this};
           operator++();
           return tmp;
       }

       friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) { return lhs.m == rhs.m; }

       friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) { return lhs.m != rhs.m; }

       reference operator*() const { return reinterpret_cast<Maillon*>(m)->valeur; }

       friend class ListeSimple;

   private:
       MaillonVide* m;

       explicit const_iterator(MaillonVide* _m) : m(_m) {}
   };

    ListeSimple() : avant_premier{nullptr} {}

    ListeSimple(const ListeSimple<value_type> &ls) : avant_premier{nullptr} {
        try {
            iterator last = before_begin();
            for (auto it = ls.begin(); it != ls.end(); ++it) {
                last = insert_after(last, *it);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    ~ListeSimple() {
        clear();
    }

    ListeSimple<value_type> &operator=(const ListeSimple<value_type> &rhs) {
        if (this == &rhs) {
            return *this;
        }

        ListeSimple<value_type> tmp{rhs};
        swap(tmp);
        return *this;
    }

    iterator before_begin() noexcept { return iterator(&avant_premier); }

    iterator begin() const{
        return iterator(avant_premier.suivant);
    }

    iterator end() const{
        return iterator(nullptr);
    }

    const_iterator cbefore_begin() const{ return const_iterator(&avant_premier); }

    const_iterator cbegin() const{
        return const_iterator(avant_premier.suivant);
    }

    const_iterator cend() const{
        return const_iterator(nullptr);
    }

    bool empty() const noexcept { return avant_premier.suivant == nullptr; }


    /* Public  Classe ListeSimple*/
    iterator insert_after(iterator m, const_reference v){
        auto *temp = new Maillon{m.m->suivant, v};
        m.m->suivant = temp;
        return iterator(temp);
    }

    void erase_after(Maillon m){
        Maillon* temp = m.suivant;
        m.suivant = temp->suivant;
        delete temp;
    }

    void splice_after(iterator m, iterator debut, iterator fin){
        if (debut == fin){
            return;
        }

        auto tempNexte = m.m->suivant;

        m.m->suivant = debut.m->suivant;
        debut.m->suivant = fin.m->suivant;
        fin.m->suivant = tempNexte;
    }

    void sort(){
        if (empty() || avant_premier.suivant->suivant == nullptr){
            return;
        }

        iterator j = before_begin();
        while (j.m->suivant->suivant != nullptr){
            iterator min = j;
            iterator i = j;
            ++i;

            while (i.m->suivant != nullptr){
                if (i.m->suivant->valeur < min.m->suivant->valeur) {
                    min = i;
                }
                ++i;
            }

            if (j != min){
                splice_after(j, min, iterator(min.m->suivant));
            }

            ++j;
        }
    }

    void push_front(value_type v){
        insert_after(before_begin(), v);
    }

    reference front() const {
        return *(cbegin());
    }

    reference front() {
        return *(begin());
    }

    void swap(ListeSimple<value_type> &other) noexcept {
        using std::swap;
        swap(avant_premier, other.avant_premier);
    }

    void clear() {
        Maillon *current = avant_premier.suivant;
        while (current != nullptr) {
            Maillon *tmp = current;
            current = current->suivant;
            delete tmp;
        }
        avant_premier.suivant = nullptr;
    }

};



#endif //LISTE_H
