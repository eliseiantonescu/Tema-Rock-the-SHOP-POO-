using namespace std;
#pragma once
#include <iostream>
#include <string>
using namespace std;

class produs {
protected:
  static int codd;
  string denumirea;
  int stoc, cod;
  double pret_baza;

public:
  produs() = default;

  produs(string den, int stc, double pret)
      : denumirea(den), stoc(stc), pret_baza(pret) {
    codd++;
    cod = codd;
  }

  virtual ~produs() {}
  virtual void afisare() const {
    cout << "Codul unic de produs : " << cod << endl;
    cout << "Denumirea produsului: " << denumirea << endl;
    cout << "Stocul de produse este: " << stoc << endl;
    cout << "Pretul de baza este: " << pret_baza << endl;
  }
  virtual double calcPret() const = 0;

  int getCod() const { return cod; }

  void modStoc(int nouu) { stoc = nouu; }
};
