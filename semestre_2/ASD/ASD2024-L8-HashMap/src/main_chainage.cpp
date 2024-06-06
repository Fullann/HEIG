#include "HashMapChainage.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
   vector<string> v = { "Alice", "Bob", "Chiara", "David", "Elena",
                        "Francis", "Gertrude", "Hector", "Isabelle",
                        "Alice", "Elena"};

   HashMapChainage<std::string, size_t> m;
   m.max_load_factor(3.f);

   for(size_t i = 0; i < v.size(); ++i) {
      m[v[i]] = i;

      cout << m << endl;
   }

   m.rehash(6);
   cout << endl << m << endl;

   m.erase("Alice");
   m.erase("Hector");
   m.erase("Chiara");
   cout << m << endl;
}