#include "HashMapSondage.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
   vector<string> v = { "Alice", "Bob", "Chiara", "David", "Elena",
                        "Francis", "Gertrude", "Hector", "Isabelle",
                        "Alice", "Elena"};

   HashMapSondage<std::string, size_t> m;
   m.max_load_factor(0.7f);

   for(size_t i = 0; i < v.size(); ++i) {
      m[v[i]] = i;

      cout << m << endl;
   }

   m.rehash(10);
   cout << m << endl;

   for(auto s : { "Alice", "Hector", "Francis"} ) {
      m.erase(s);
      cout << m << endl;
   }
}