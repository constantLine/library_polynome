#include "polynome.h"

#include <sstream>
#include <algorithm>

using namespace std;

Monome::Monome(string str) {
   stringstream ss(str);
   ss >> coef;
   if (coef == 0) coef = 1;

   for (int i = 0; i < str.size(); ++i) {
      if (isalpha(str[i])) {
         if (str[i + 1] == '^') {
            string number = "";
            int k = i + 1;
            while (isdigit(str[k + 1])) {
               k++;
               number += str[k];
            }
            pows[str[i]] += stoi(number);
         }
         else
            pows[str[i]] = 1;
      }
   }
}

Monome Monome::operator*(const Monome &obj) const {
   Monome result = *this;

   result.coef = result.coef * obj.coef;

   for (auto it : obj.pows) {
      if (result.pows.contains(it.first)) {
         result.pows[it.first] =result.pows[it.first] +  it.second;
      }
      else {
         result.pows[it.first] = it.second;
      }
   }
   return result;
}

Monome Monome::operator*(double number) const {
   Monome result = *this;
   result.coef = result.coef * number;
   return result;
}

Monome Monome::operator/(double number) const {
   if (number == 0) throw exception();
   Monome result = *this;
   result.coef = result.coef / number;
   return result;
}

bool operator==(const Monome &obj1, const Monome &obj2) {
   return obj1.coef == obj2.coef && obj1.pows == obj2.pows;
}

ostream &operator <<(ostream &out, const Monome &obj) {
   out << obj.coef;
   if (obj.pows.size() == 0) return out;
   out << "*";
   int counter = 0;
   for (auto it = obj.pows.begin(); it != obj.pows.end(); ++it) {
      if (it->second == 1)
         out << it->first;
      else
         out << it->first << "^" << it->second;
      counter++;

      if (counter != obj.pows.size())
         out << "*";
   }
   return out;
}

istream &operator >>(istream &in, Monome &obj) {
   in >> obj.coef;

   string str;
   in >> str;
   obj.pows.clear();
   for (int i = 0; i < str.size(); ++i) {
      if (isalpha(str[i])) {
         if (str[i + 1] == '^') {
            string number = "";
            int k = i + 1;
            while (isdigit(str[k + 1])) {
               k++;
               number += str[k];
            }
            obj.pows[str[i]] += stoi(number);
         }
         else
            obj.pows[str[i]] = 1;
      }
   }
   return in;
}

Polynome::Polynome(string str) {

   for (int i = 0; i < str.size(); ++i) {
      if (isdigit(str[i]) || str[i]=='-') {
         string buf = "";
         int k = i;
         while (str[k] != '+'  && k < str.size())
            buf += str[k++];

         Monome m(buf);
         terms.push_back(m);
         i = k;
      }
   }
}

Polynome::Polynome(double num) {
   terms.push_back(num);
}

Polynome::Polynome(Monome obj) {
   terms.push_back(obj);
}

Polynome Polynome::operator/(double number) const {
   if (number == 0) throw exception();
   Polynome res = *this;
   for (auto &term : res.terms)
      term.coef /= number;

   return res;
}

Polynome Polynome::operator +(const Polynome &obj) const {
   Polynome res = *this;
   bool flg;
   for (auto term : obj.terms) {
      flg=false;
      for (auto &term2 : res.terms) {
         if (term.similar(term2)) { //если нашло общий то flg=1, не добавляется в конец
               term2.coef += term.coef;
               flg=true;
               break;
         }
      }//не создавал отдельный метод add потому что этот код только здесь
      if(!flg) res.terms.push_back(term);
   }
   // все мономы нулевых коэфов. попали внутрь, очищаем от них
   for (int i=0; i < res.terms.size(); i++){
      if (res.terms[i].coef == 0){
        res.terms.erase(res.terms.begin()+i); 
      }
   }
   return res;
}

Polynome Polynome::operator -(const Polynome &obj) const {
   Polynome res = *this;
   return res + obj*(-1.);
}

Polynome Polynome::operator*(const Polynome &obj) const {
   Polynome result;

   for (auto it1 : this->terms) {
      for (auto it2 : obj.terms) {
         result = result + (it1 * it2);
      }
   }
   return result;
}

ostream &operator<<(std::ostream &out, const Polynome &obj) {
   int end = 0;
   for (auto term : obj.terms) {
      out << term;
      end++;
      if (end != obj.terms.size())
         out << "+";
   }
   return out;
}

std::vector<char> Polynome::print_variables(){
   std::vector<char> v = {' '};
   for (auto term: this->terms){
      for (auto it : term.pows) {
         if (*std::find(v.begin(), v.end(), it.first) != it.first){
            v.push_back(it.first);
         }
      }
   }
   return v;
}

double Polynome::count_for(std::map<char, double> &mp){
   int allsum = 0;
   for (auto term: this->terms){
      int msum = term.coef;
      for (auto it : term.pows) {
         msum *= std::pow(mp[it.first], it.second);
      }
      allsum += msum;
   }
   return allsum;
}

