#ifndef _POLYNOME_H_
#define _POLYNOME_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

class Monome { // Класс мономов из которых состоит любой полином
private:
   double coef; // Коэфициент монома
   std::map<char, int> pows;  // Переменные и их степени

public: 
   // Конструкторы
   Monome():coef(1) {}
   Monome(std::string); // конструктор преобразователь string -> Monome
   Monome(double num):coef(num) {} // аналогично double -> Monome
   
   // Определение операций
   Monome operator *(const Monome &obj) const ;
   
   Monome operator *(double number) const;
   Monome operator /(double number) const;

   friend bool operator==(const Monome &obj1, const Monome &obj2);
   // Ввод и вывод в поток
   friend std::ostream &operator <<(std::ostream &out, const Monome &obj);
   friend std::istream &operator >>(std::istream &in, Monome &obj);
   
   // Метод сравнивания по переменным+степеням, 
   // чтобы находить общие мономы для операций
   bool similar(const Monome &obj) const {return pows == obj.pows;}

   friend class Polynome;
};
// Дополнительно определим операцию для удобства
inline bool operator!=(const Monome &obj1, const Monome &obj2) {
   return !(obj1 == obj2);
}

class Polynome {
private:
   //Вектор содержащий мономы на которые раскладывается полином
   std::vector<Monome>terms; 

public:
   // Конструкторы
   Polynome() {}
   Polynome(std::string); // конструктор преобразователь string -> Polynome
   Polynome(double num);// аналогично double -> Polynome
   Polynome(Monome num);// аналогично Monome -> Polynome
   
   // Определение операций для работы с полиномами
   Polynome operator +(const Polynome &obj) const;
   Polynome operator -(const Polynome &obj) const;
   Polynome operator *(const Polynome &obj) const;
   
   // Определение операции для работы с числами
   Polynome operator /(double number) const;
   
   // Ввод и вывод в поток
   friend std::ostream &operator<<(std::ostream &out, const Polynome &obj);
   friend std::istream &operator>>(std::istream &in, Polynome &obj);
   
   //Получение переменных
   std::vector<char> print_variables();
   // Вычисление полинома для значений
   //Принимает map вида {'a': 2, 'b': 3 }, где a и b - переменные, 2 и 3 их значения
   double count_for(std::map<char, double> &mp);
   /*
      Пример работы
      Polynome p1("2*a+3*b")
      std::map<char, int> mp = { {'a' , 5}, {'b' , 6} }
      cout << p1.count_for(mp)
   */
};


#endif