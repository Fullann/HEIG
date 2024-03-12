#include <iostream>
using namespace std;
int main()
{
    string s1("123456789", 5);
    string s2(string(s1, 2) + s1);
    string s3 = "1124121213";
    string s4 = s3.substr(s3.find_first_of("def32"), 3);
    size_t p = s3.find("121", 5);
    s3.insert(p, "zz");
    string s5{"12112123"};
    p = s5.rfind("121");
    s5.erase(p);

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
}