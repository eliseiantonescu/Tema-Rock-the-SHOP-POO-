using namespace std;
#pragma once
#include "angajati.h"
#include "art_vestimentare.h"
#include "asistent.h"
#include "comenzi.h"
#include "discuri.h"
#include "manager.h"
#include "operator_comenzi.h"
#include "produs.h"
#include "vintage.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <typeinfo>
#include <vector>


class magazin {
  vector<angajati *> angaj;
  vector<produs *> produse;
  vector<comenzi> comenzi_finalizate;
  queue<comenzi> coada_comenzi;

  int timp_curent = 0; // Simulated time in arbitrary units.

public:
  void adaugaAngajati(angajati *angajat) { angaj.push_back(angajat); }

  void stergereAngajat(int id) {
    vector<angajati *>::iterator its;
    for (its = angaj.begin(); its != angaj.end(); its++)
      if ((*its)->getID() == id) {
        delete *its;
        angaj.erase(its);
        cout << "Angajatul cu ID-ul " << id << " a fost eliminat" << endl;
        break;
      }
  }

  void modNume(int id, string nume) {
    vector<angajati *>::iterator its;
    for (its = angaj.begin(); its != angaj.end(); its++)
      if ((*its)->getID() == id) {
        (*its)->modNumee(nume);
        cout << "Numele de familie a fost modificat." << endl;
        break;
      }
  }

  void afisareTotAng() {
    vector<angajati *>::iterator its;
    for (its = angaj.begin(); its != angaj.end(); its++) {
      (*its)->afisare();
      cout << endl;
    }
  }

  void afisareTotPrd() {
    vector<produs *>::iterator itss;
    for (itss = produse.begin(); itss != produse.end(); itss++) {
      (*itss)->afisare();
      cout << endl;
    }
  }

  void adaugaProduse(produs *produ) { produse.push_back(produ); }

  void stergereProdus(int cod) {

    vector<produs *>::iterator its;
    for (its = produse.begin(); its != produse.end(); its++)
      if ((*its)->getCod() == cod) {
        delete *its;
        produse.erase(its);
        cout << "Produsul cu Codul " << cod << " a fost eliminat din productie"
             << endl;
        break;
      }
  }

  void modificareProdus(int cod, int nouStoc) {
    vector<produs *>::iterator its;
    for (its = produse.begin(); its != produse.end(); its++)
      if ((*its)->getCod() == cod) {
        (*its)->modStoc(nouStoc);
        cout << "Noul stoc pentru produsul cu cod " << cod << " este "
             << nouStoc << endl;
        break;
      }
  }

  bool validareFunctionare() {
    int countManager = 0, countOperator = 0, countAsistent = 0;
    for (auto a : angaj) {
      if (dynamic_cast<manager *>(a))
        countManager++;
      else if (dynamic_cast<op_comenzi *>(a))
        countOperator++;
      else if (dynamic_cast<asistent *>(a))
        countAsistent++;
    }

    if (countManager < 1 || countOperator < 3 || countAsistent < 1) {
      cout << "Eroare: Magazinul nu are angajatii necesari (1 manager, 3 "
              "operatori, 1 asistent)!"
           << endl;
      return false;
    }

    int contVestimentare = 0, contDiscuri = 0, contVintage = 0;
    for (auto p : produse) {
      if (dynamic_cast<vintage *>(p))
        contVintage++;
      else if (dynamic_cast<discuri *>(p))
        contDiscuri++;
      else if (dynamic_cast<art_vestimentare *>(p))
        contVestimentare++;
    }

    if (contVestimentare < 2 || contDiscuri < 2 || contVintage < 2) {
      cout << "Eroare: Magazinul nu are destule produse (minim 2 din fiecare "
              "tip de baza)!"
           << endl;
      return false;
    }

    return true;
  }

  void adaugaComanda(comenzi c) {
    if (!validareFunctionare())
      return;

    if (!c.esteValida()) {
      cout << "Eroare: Comanda nu indeplineste criteriile (minim 100 RON sau "
              "cantitati permise)!"
           << endl;
      return;
    }

    // Find operator with minimum commands < 3
    op_comenzi *op_ales = nullptr;
    int min_cmds = 4;

    for (auto a : angaj) {
      if (auto op = dynamic_cast<op_comenzi *>(a)) {
        if (op->getNrComenziAsteptare() < 3 &&
            op->getNrComenziAsteptare() < min_cmds) {
          min_cmds = op->getNrComenziAsteptare();
          op_ales = op;
        }
      }
    }

    if (op_ales) {
      op_ales->incrementAreComenzi(1);
      c.setOperator(op_ales->getID());
      cout << "Comanda " << c.getID() << " a fost preluata de operatorul "
           << op_ales->getName() << endl;
      comenzi_finalizate.push_back(c); // using it as active pool for now
    } else {
      cout << "Toti operatorii sunt ocupati. Comanda " << c.getID()
           << " intra in asteptare." << endl;
      coada_comenzi.push(c);
    }
  }

  void avanseazaTimpul(int unitati) {
    timp_curent += unitati;
    cout << "--- Timpul a avansat cu " << unitati
         << " unitati. (Suntem la T=" << timp_curent << ") ---" << endl;

    for (auto &c : comenzi_finalizate) {
      if (c.getDurataRealizare() > 0 && c.getOperator() != -1) {
        int nou = c.decrementDurata();
        if (nou <= 0) {
          cout << "Comanda " << c.getID() << " a fost finalizata!" << endl;
          int id_op = c.getOperator();

          for (auto a : angaj) {
            if (auto op = dynamic_cast<op_comenzi *>(a)) {
              if (op->getID() == id_op) {
                op->incrementAreComenzi(-1);
                op->adaugaComandaLaIstoric(c.getValoareTotala());
                break;
              }
            }
          }
        }
      }
    }

    // Preluam din coada daca s-au eliberat operatori
    while (!coada_comenzi.empty()) {
      comenzi c_steptare = coada_comenzi.front();

      op_comenzi *op_ales = nullptr;
      int min_cmds = 4;

      for (auto a : angaj) {
        if (auto op = dynamic_cast<op_comenzi *>(a)) {
          if (op->getNrComenziAsteptare() < 3 &&
              op->getNrComenziAsteptare() < min_cmds) {
            min_cmds = op->getNrComenziAsteptare();
            op_ales = op;
          }
        }
      }

      if (op_ales) {
        coada_comenzi.pop();
        op_ales->incrementAreComenzi(1);
        c_steptare.setOperator(op_ales->getID());
        cout << "Comanda restanta " << c_steptare.getID()
             << " a fost preluata de " << op_ales->getName() << endl;
        comenzi_finalizate.push_back(c_steptare);
      } else {
        break; // Toti sunt ocupati iar
      }
    }
  }

  const vector<angajati *> &getAngajati() const { return angaj; }

  ~magazin() {
    for (auto a : angaj) {
      delete a;
    }
    for (auto p : produse) {
      delete p;
    }
  }
};
