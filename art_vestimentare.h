#include "produs.h"
#pragma once


class art_vestimentare: public produs{
        string culoare;
        string marca;

public:
        art_vestimentare(string den,int stc,double pret,string cul,string mar):produs(den,stc,pret),culoare(cul),marca(mar){}

        void afisare() const{
            produs::afisare();
            cout<<"Marca este: "<<marca<<endl;
            cout<<"Culoare este: "<<culoare<<endl;
            cout<<"Pretul final + transport: "<<calcPret()<<endl;
        }
        double calcPret()const{
            return pret_baza+20;
        }




};
