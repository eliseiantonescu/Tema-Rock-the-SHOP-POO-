#include "meniu.h"
#include <fstream>

void Meniu::popupare_initiala() {
  vector<double> vs = {120.3, 210.3, 402.2};
  try {
    maga.adaugaAngajati(new manager("Popescu", "Ion", "5041222170010", 12, 4,
                                    2010, 12, 10, 2000));
  } catch (const invalid_argument &e) {
    cout << "Eroare initializare: " << e.what() << endl;
  }
  try {
    maga.adaugaAngajati(new op_comenzi("Ionescu", "Mihai", "1770326128364", 1,
                                       4, 2012, 22, 10, 2002, vs, 0));
  } catch (const invalid_argument &e) {
    cout << "Eroare initializare: " << e.what() << endl;
  }
  try {
    maga.adaugaAngajati(new op_comenzi("Vasile", "Andrei", "1800512128365", 5,
                                       2, 2015, 12, 5, 1980, vs, 0));
  } catch (const invalid_argument &e) {
    cout << "Eroare initializare: " << e.what() << endl;
  }
  try {
    maga.adaugaAngajati(new op_comenzi("Georgescu", "Ana", "2850714128366", 14,
                                       8, 2019, 14, 7, 1985, vs, 0));
  } catch (const invalid_argument &e) {
    cout << "Eroare initializare: " << e.what() << endl;
  }
  try {
    maga.adaugaAngajati(new asistent("Dumitru", "Oana", "2900326129964", 23, 9,
                                     2014, 26, 3, 1990));
  } catch (const invalid_argument &e) {
    cout << "Eroare initializare: " << e.what() << endl;
  }

  maga.adaugaProduse(
      new art_vestimentare("Geaca Piele", 10, 200, "Negru", "RockBrand"));
  maga.adaugaProduse(
      new art_vestimentare("Tricou Trupa", 25, 80, "Rosu", "MetalMerch"));
  maga.adaugaProduse(new discuri("Album X", 15, 50, "Universal", "12/12/2012",
                                 "Metallica", "Black Album"));
  maga.adaugaProduse(new discuri("Album Y", 10, 45, "Sony", "10/10/2010",
                                 "AC/DC", "Back in Black"));
  maga.adaugaProduse(new vintage("Vinil Vechi 1", 5, 150, "EMI", "01/01/1980",
                                 "Pink Floyd", "The Wall", true, 4));
  maga.adaugaProduse(new vintage("Vinil Vechi 2", 2, 250, "Columbia",
                                 "05/05/1975", "Led Zeppelin",
                                 "Physical Graffiti", false, 5));

  cout << "Date initiale incarcate cu succes!" << endl;
}

void Meniu::afisMenu() {
  cout << "\n=== ROCK the SHOP ===" << endl;
  cout << "1. Gestiune Angajati" << endl;
  cout << "2. Gestiune Produse" << endl;
  cout << "3. Adaugare Comanda" << endl;
  cout << "4. Avanseaza Timpul (Simulare)" << endl;
  cout << "0. Iesire" << endl;
  cout << "Alege o optiune: ";
}

void Meniu::ruleaza() {
  popupare_initiala();
  int optiune;
  do {
    afisMenu();
    cin >> optiune;
    switch (optiune) {
    case 1:
      menuAngaj();
      break;
    case 2:
      menuProdus();
      break;
    case 3:
      menuComenzi();
      break;
    case 4: {
      int unitati;
      cout << "Introdu numarul de unitati de timp pentru avansare: ";
      cin >> unitati;
      maga.avanseazaTimpul(unitati);
      break;
    }
   
    case 0:
      cout << "Iesire din aplicatie." << endl;
      break;
    default:
      cout << "Optiune invalida!" << endl;
    }
  } while (optiune != 0);
}

void Meniu::menuAngaj() {
  int opt;
  do {
    cout << "\n--- Gestiune Angajati ---" << endl;
    cout << "1. Adauga angajat\n2. Sterge angajat\n3. Modifica nume\n4. "
            "Afiseaza angajati\n0. Inapoi"
         << endl;
    cout << "Alege: ";
    cin >> opt;
    if (opt == 1) {
      string nume, prenume, tip, CNP;
      int zA, lA, aA, zN, lN, aN;
      cout << "Tip (Manager/Operator/Asistent): ";
      cin >> tip;
      cout << "Nume: ";
      cin >> nume;
      cout << "Prenume: ";
      cin >> prenume;
      cout << "CNP: ";
      cin >> CNP;
      cout << "Data angajarii (Z L A): ";
      cin >> zA >> lA >> aA;
      cout << "Data nasterii (Z L A): ";
      cin >> zN >> lN >> aN;

      try {
        if (tip == "Manager")
          maga.adaugaAngajati(
              new manager(nume, prenume, CNP, zA, lA, aA, zN, lN, aN));
        else if (tip == "Operator")
          maga.adaugaAngajati(new op_comenzi(nume, prenume, CNP, zA, lA, aA, zN,
                                             lN, aN, vector<double>(), 0));
        else if (tip == "Asistent")
          maga.adaugaAngajati(
              new asistent(nume, prenume, CNP, zA, lA, aA, zN, lN, aN));
        else
          cout << "Tip invalid!" << endl;
      } catch (const invalid_argument &e) {
        cout << "Eroare la adaugare: " << e.what() << endl;
      }
    } else if (opt == 2) {
      int id;
      cout << "ID: ";
      cin >> id;
      maga.stergereAngajat(id);
    } else if (opt == 3) {
      int id;
      string nume;
      cout << "ID: ";
      cin >> id;
      cout << "Nume nou: ";
      cin >> nume;
      maga.modNume(id, nume);
    } else if (opt == 4) {
      maga.afisareTotAng();
    }
  } while (opt != 0);
}

void Meniu::menuProdus() {
  int opt;
  do {
    cout << "\n--- Gestiune Produse ---" << endl;
    cout << "1. Adauga produs\n2. Sterge produs\n3. Modifica stoc\n4. Afiseaza "
            "produse\n0. Inapoi"
         << endl;
    cout << "Alege: ";
    cin >> opt;
    if (opt == 1) {
      string den, tip;
      int stoc;
      double pret;
      cout << "Tip (Vestimentar/Discuri/Vintage): ";
      cin >> tip;
      cout << "Denumire: ";
      cin >> den;
      cout << "Stoc: ";
      cin >> stoc;
      cout << "Pret baza: ";
      cin >> pret;
      if (tip == "Vestimentar") {
        string cul, mar;
        cout << "Culoare: ";
        cin >> cul;
        cout << "Marca: ";
        cin >> mar;
        maga.adaugaProduse(new art_vestimentare(den, stoc, pret, cul, mar));
      } else if (tip == "Discuri") {
        string casa, data, trupa, alb;
        cout << "Casa discuri: ";
        cin >> casa;
        cout << "Data: ";
        cin >> data;
        cout << "Trupa: ";
        cin >> trupa;
        cout << "Album: ";
        cin >> alb;
        maga.adaugaProduse(
            new discuri(den, stoc, pret, casa, data, trupa, alb));
      } else if (tip == "Vintage") {
        string casa, data, trupa, alb;
        int coef;
        bool mint;
        cout << "Casa discuri: ";
        cin >> casa;
        cout << "Data: ";
        cin >> data;
        cout << "Trupa: ";
        cin >> trupa;
        cout << "Album: ";
        cin >> alb;
        cout << "Coeficient raritate (1-5): ";
        cin >> coef;
        cout << "Mint (1/0): ";
        cin >> mint;
        maga.adaugaProduse(
            new vintage(den, stoc, pret, casa, data, trupa, alb, mint, coef));
      } else
        cout << "Tip invalid!" << endl;
    } else if (opt == 2) {
      int cod;
      cout << "Cod: ";
      cin >> cod;
      maga.stergereProdus(cod);
    } else if (opt == 3) {
      int cod, stoc;
      cout << "Cod: ";
      cin >> cod;
      cout << "Stoc nou: ";
      cin >> stoc;
      maga.modificareProdus(cod, stoc);
    } else if (opt == 4) {
      maga.afisareTotPrd();
    }
  } while (opt != 0);
}

void Meniu::menuComenzi() {
  cout << "\n--- Adaugare Comanda ---" << endl;
  int nrV, nrD;
  cout << "Numar articole vestimentare dorite: ";
  cin >> nrV;
  cout << "Numar discuri dorite: ";
  cin >> nrD;

  double valProduse = 0;
  double valTotala = 0;
  int durata = nrV * 1 + nrD * 2; 
  valProduse = (nrV * 50) + (nrD * 40);
  valTotala =
      (nrV * (50 + 20)) + (nrD * (40 + 5)); 

  comenzi c(0); 
  c.setValori(valProduse, valTotala, durata, nrV, nrD);
  maga.adaugaComanda(c);
}
