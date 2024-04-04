#include "polynome.h"

using namespace std;

int main() {
   cout << "1)" << "\n";
   Polynome p1("3*a^2*b+6*a*c+-5*x^2");
   Polynome p2("8*x^2+6*a^2*b");
   Polynome p3("2*a + -3*b");
   Polynome k("3*b");

   cout << "p1 = " << p1 << "\n";
   cout << "p2 = " << p2 << "\n";
   cout << "p3 = " << p3 << "\n";
   cout << "k = " << k << "\n\n";
   
   cout << "p3 + k:\n"; 
   cout << p3 + k << "\n\n";
   
   cout << "2)" << "\n";
   cout << "p1 * p2:\n"; 
   cout << p1 * p3 << "\n\n";

   cout << "p1 + p2:\n"; 
   cout << p1 + p2 << "\n\n";
   
   cout << "p1 - p2:\n"; 
   cout << p1 - p2 << "\n\n";
   
   cout << "3)" << "\n";
   cout << "p1 * 5:\n"; 
   cout << p1 * 5. << "\n\n";
   
   cout << "p1 / 5:\n"; 
   cout << p1 / 5 << "\n\n";
   
    cout << "p1 + 5:\n"; 
   cout << p1 + 5.0 << "\n\n";
   
   cout << "p1 - 5:\n"; 
   cout << p1 - 5.0 << "\n\n";
   
   cout << "4)" << "\n";
   cout << "p3 = p2:\n"; 
   p3=p2;
   cout << "p3 = " << p3<< "\n";
   cout << "p2 = " << p2 << "\n\n";
   
   cout << "5)" << "\n";
   cout << "Переменные p3:" ;
   for (char c :  p3.print_variables()) cout << c<< " ";
   cout<< "\n";
   cout << "Посчитаем p3 для a=2, b=5, x=10: ";
   std::map<char, double> td = { {'a' , 2}, {'b' , 5}, {'x' , 10} };
   cout << p3.count_for(td) << "\n";
   cout<< "\n";
   
   Polynome x("2*a+3*b");
   cout << "x = " << x << "\n";
   
   cout << "Переменные x:" ;
   for (char c :  x.print_variables()) cout << c<< " ";
   cout<< "\n";
   
   cout << "Посчитаем x для a=5, b=6: ";
   std::map<char, double> mp = { {'a' , 5.0}, {'b' , 6.5} };
   cout << x.count_for(mp) << "\n\n";
   
   cout << "6)" << "\n";
   cout << "Прибавим к x строку 5*z: x + 5*z = ";
   cout << x + Polynome("5*z");
   
   return 0;
}