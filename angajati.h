using namespace std;
#pragma once
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class angajati {
protected:
  static int ida;
  int ID = 1;
  string nume, prenume;
  string CNP;
  double salariu_baza = 3500;
  int ziAng, lunaAng, anAng; // ziua luna si anul angajarii
  int ziNas, lunaNas, anNas; // ziua luna si anul nasterii

public:
  angajati() = default;

  angajati(string numee, string pren, string cnpp, int zia, int lunaa, int anA,
           int ziN, int lunaN, int anN)
      : nume(numee), prenume(pren), CNP(cnpp), ziAng(zia), lunaAng(lunaa),
        anAng(anA), ziNas(ziN), lunaNas(lunaN), anNas(anN) {
    ida++;
    ID = ida;
    if (Varsta(ziNas, lunaNas, anNas) < 18)
      throw invalid_argument("Angajatul nu este major!");
    if (nume.size() < 3 || nume.size() > 30 || prenume.size() < 3 ||
        prenume.size() > 30) {
      throw invalid_argument(
          "Numele si prenumele trebuie sa aiba intre 3 si 30 de caractere");
    }
    int cc = calculeazaCifraControl(CNP);
    int ok = 0;
    long long nrConvertit = 0;
    nrConvertit = stoll(CNP);
    while (nrConvertit) {
      if (cc == nrConvertit % 10)
        ok = 1;
      nrConvertit = nrConvertit / 10;
    }
    if (ok == 0)
      throw invalid_argument("CNP-ul este invalid!!!");
  }
  int getID() const { return ID; }

  int Varsta(int ziNas, int lunaNas, int anNas) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int ziActual = ltm->tm_mday;
    int lunaActual = 1 + ltm->tm_mon;
    int anActual = 1900 + ltm->tm_year;

    int varsta = anActual - anNas;
    if (lunaNas > lunaActual || (lunaNas == lunaActual && ziNas > ziActual)) {
      varsta--;
    }
    return varsta;
  }

  int getLunaNas() const { return lunaNas; }
  int getZiNas() const { return ziNas; }
  int getAnAng() const { return anAng; }
  int getLunaAng() const { return lunaAng; }
  int getZiAng() const { return ziAng; }

  int getVechime() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int ziActual = ltm->tm_mday;
    int lunaActual = 1 + ltm->tm_mon;
    int anActual = 1900 + ltm->tm_year;

    int vechime = anActual - anAng;
    if (lunaAng > lunaActual || (lunaAng == lunaActual && ziAng > ziActual))
      vechime--;
    return vechime;
  }
  int calculeazaCifraControl(const string &cnp) {
    string constanta = "279146358279";
    if (cnp.size() != 13) {
      throw invalid_argument("CNP-ul trebuie să aiba 13 caractere.");
    }

    int suma = 0;
    for (size_t i = 0; i < 12; ++i) {
      if (!isdigit(cnp[i])) {
        throw invalid_argument("CNP-ul trebuie sa aiba doar cifre.");
      }
      suma += (cnp[i] - '0') * (constanta[i] - '0');
    }

    int rest = suma % 11;
    int cifraControlCalculata;
    if (rest < 10) {
      cifraControlCalculata = rest;
    } else {
      cifraControlCalculata = 1;
    }

    return cifraControlCalculata;
  }

  void modNumee(string numi) { nume = numi; }

  virtual ~angajati() {};
  virtual void afisare() {
    cout << "ID angajatului este: " << ID << endl;
    cout << "Numele este: " << nume << endl;
    cout << "Prenumele este: " << prenume << endl;
    cout << "Cnp: " << CNP << endl; 
    cout << "Data Angajarii: " << ziAng << "/" << lunaAng << "/" << anAng
         << endl;
    cout << "Data Nasterii: " << ziNas << "/" << lunaNas << "/" << anNas
         << endl;
  }
  virtual double calcSalariu() const = 0;
};
