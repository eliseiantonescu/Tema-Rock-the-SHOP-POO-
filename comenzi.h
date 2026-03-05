using namespace std;
#pragma once
#include "produs.h"
#include <iostream>
#include <string>
#include <vector>

class comenzi {
  static int idaa;
  int IDD;
  int nrVestimentare = 0;
  int nrDiscuri = 0;

  double valoare_totala = 0;  // Inclusiv livrare pentru validari sau rapoarte
  double valoare_produse = 0; // Fara livrare

  int durata_procesare = 0;
  int data_primire = 0; // Ticked time in the simulation

  int operator_id = -1; // -1 Daca e in asteptare

public:
  comenzi(int data_primita) : data_primire(data_primita) {
    idaa++;
    IDD = idaa;
  }

  bool adaugaProdus(produs *p) {
    // Validation: max 5 discuri, max 3 vestimentare.
    // Needs dynamic_cast or type trait
    return true;
  }

  void setValori(double produse, double totala, int d, int nrV, int nrD) {
    valoare_produse = produse;
    valoare_totala = totala;
    durata_procesare = d;
    nrVestimentare = nrV;
    nrDiscuri = nrD;
  }

  int getID() const { return IDD; }
  void setOperator(int op) { operator_id = op; }
  int getOperator() const { return operator_id; }

  double getValoareTotala() const { return valoare_totala; }
  double getValoareFaraLivrare() const { return valoare_produse; }
  int getDataPrimire() const { return data_primire; }
  int getDurataRealizare() const { return durata_procesare; }

  int decrementDurata() {
    if (durata_procesare > 0)
      durata_procesare--;
    return durata_procesare;
  }

  bool esteValida() const {
    return (valoare_produse >= 100.0 && nrVestimentare <= 3 && nrDiscuri <= 5);
  }
};
