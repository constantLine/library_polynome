#ifndef _POLYNOME_H_
#define _POLYNOME_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

class Monome { // ����� ������� �� ������� ������� ����� �������
private:
   double coef; // ���������� ������
   std::map<char, int> pows;  // ���������� � �� �������

public: 
   // ������������
   Monome():coef(1) {}
   Monome(std::string); // ����������� ��������������� string -> Monome
   Monome(double num):coef(num) {} // ���������� double -> Monome
   
   // ����������� ��������
   Monome operator *(const Monome &obj) const ;
   
   Monome operator *(double number) const;
   Monome operator /(double number) const;

   friend bool operator==(const Monome &obj1, const Monome &obj2);
   // ���� � ����� � �����
   friend std::ostream &operator <<(std::ostream &out, const Monome &obj);
   friend std::istream &operator >>(std::istream &in, Monome &obj);
   
   // ����� ����������� �� ����������+��������, 
   // ����� �������� ����� ������ ��� ��������
   bool similar(const Monome &obj) const {return pows == obj.pows;}

   friend class Polynome;
};
// ������������� ��������� �������� ��� ��������
inline bool operator!=(const Monome &obj1, const Monome &obj2) {
   return !(obj1 == obj2);
}

class Polynome {
private:
   //������ ���������� ������ �� ������� �������������� �������
   std::vector<Monome>terms; 

public:
   // ������������
   Polynome() {}
   Polynome(std::string); // ����������� ��������������� string -> Polynome
   Polynome(double num);// ���������� double -> Polynome
   Polynome(Monome num);// ���������� Monome -> Polynome
   
   // ����������� �������� ��� ������ � ����������
   Polynome operator +(const Polynome &obj) const;
   Polynome operator -(const Polynome &obj) const;
   Polynome operator *(const Polynome &obj) const;
   
   // ����������� �������� ��� ������ � �������
   Polynome operator /(double number) const;
   
   // ���� � ����� � �����
   friend std::ostream &operator<<(std::ostream &out, const Polynome &obj);
   friend std::istream &operator>>(std::istream &in, Polynome &obj);
   
   //��������� ����������
   std::vector<char> print_variables();
   // ���������� �������� ��� ��������
   //��������� map ���� {'a': 2, 'b': 3 }, ��� a � b - ����������, 2 � 3 �� ��������
   double count_for(std::map<char, double> &mp);
   /*
      ������ ������
      Polynome p1("2*a+3*b")
      std::map<char, int> mp = { {'a' , 5}, {'b' , 6} }
      cout << p1.count_for(mp)
   */
};


#endif