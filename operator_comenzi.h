#include "angajati.h"
#include <vector>
#pragma once

class op_comenzi : virtual public angajati {
  vector<double> comenzi;
  int nrComenzi; // nr comenzi mai mic de 4
public:
  op_comenzi(string numee, string pren, string cnpp, int zia, int lunaa,
             int anA, int ziN, int lunaN, int anN, vector<double> a, int nrcom)
      : angajati(numee, pren, cnpp, zia, lunaa, anA, ziN, lunaN, anN),
        nrComenzi(nrcom), comenzi(a) {}

  double calcSalariu() const override {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int lunaActual = 1 + ltm->tm_mon;

    int vechime = getVechime();
    double salariu = salariu_baza + vechime * 100;

    if (lunaNas == lunaActual) {
      salariu += 100;
    }

    double sum = 0;
    for (int i = 0; i < comenzi.size(); i++)
      sum = sum + comenzi[i];

    salariu += sum * 0.005; // 0.5% bonus from the value of processed orders

    return salariu; // coefficient is 1 for operator
  }

  int getNrComenziAsteptare() const { return nrComenzi; }
  void adaugaComandaLaIstoric(double valoare) { comenzi.push_back(valoare); }
  void incrementAreComenzi(int v) { nrComenzi += v; }
  auto getName() const -> const std::string & { return nume; }
  auto getPrenume() const -> const std::string & { return prenume; }

  void afisare() {
    angajati::afisare();
    double sal = calcSalariu();
    cout << "Salariul este: " << sal << endl;
    // for(int i=0;i<comenzi.size();i++)
    //   cout<<comenzi[i]<<" "<<endl;     //am verificat daca vector de comenzi
    //   e ok
  }
};
