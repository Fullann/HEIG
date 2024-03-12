#include "tris.cpp"
#include <vector>

using namespace std;

int main(){
    vector<int> v{1,2,2,4,5,77,2};


    tri_par_selection<int>(v);
    tri_a_bull<int>(v);
    tri_par_insertion<int>(v);
}
