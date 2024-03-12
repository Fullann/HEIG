#include <iostream>
 #include <exception>
 using namespace std;

 int n; // Variable globale, statique
 class A { // Pour mettre en évidence la destruction de variables
 double x;
 public:
 A(double valeur): x(valeur){}
 ~A(){cout << "Destructeur " << "x = " << x << endl;}
 };

 void a() { cout << "a "; exit(0);}
 void b() { A z(n); cout << "b "; exit(-1);}
 void c() { cout << "c "; abort();}
 void d() { cout << "d\n";}
 void e() { cout << "e ";}
 void f() { cout << "f\n"; terminate();}
 void g() { cout << "g " << flush;}
 void h() { A z(n); cout << "h "; exit(3);}
 void i() {static A y(-8.3); }
 void j() { cout << "j " << (n/0) << endl;}
 void k() { char* c; cout << "k "; throw c;}
 void l() { cout << "l "; throw "Une exception de type const char*";}
 void m() { cout << "m "; throw "Une exception de type string"s;}
 void p() {throw runtime_error("runtime error dans p");}

 int main() {
 atexit(d);
 i();
 cin >> n;
 A objet(n + 0.5);
 if (n == 0) return 0;
 atexit(e);
 if (n == 1) return 1;
 if (n == 2) a();
 if (n == 3) b();
 if (n == 4) c();
 if (n == 5) f();
 set_terminate(g);
 if (n == 6) f();
 set_terminate(h);
 if (n == 7) f();
 if (n == 8) exit(2);
 if (n == 9) j();
 if (n == 10) k();
 try{
 if (n == 11) k();
 if (n == 12) l();
 if (n == 13) m();
 if (n == 14)
 try { p(); }
 catch (exception & e) {cout << e.what() << endl; throw 1;}
 if (n == 15)
 try { p(); }
 catch (exception e) {cout << e.what() << endl; throw 1;}
 if (n == 16)
 try { p(); }
 catch (range_error & e) {cout << e.what() << endl; throw 4;}
 if (n == 17) throw 6;
 }
 catch(char*) {cout << "Une exception de type char*" << endl;}
 catch(const char* message) {cout << message << endl;}
 catch(string& message) {cout << message << endl;}
 catch(...) {cout << "Autre exception " << endl; throw;}
 }