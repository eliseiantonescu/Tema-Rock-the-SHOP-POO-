#pragma once
#include "magazin.h"

class Meniu {
  magazin maga;

public:
  void popupare_initiala();
  void ruleaza();

private:
  void afisMenu();
  void menuAngaj();
  void menuProdus();
  void menuComenzi();
  void menuRapoarte();
};
