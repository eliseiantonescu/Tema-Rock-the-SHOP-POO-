#include "produs.h"
#pragma once


class discuri:public produs{
        string casa_disc;
        string data_vanzare;
        string trupa;
        string nume_album;
public:
        discuri(string den,int stc,double pret,string casa,string data,string trup,string num):produs(den,stc,pret),casa_disc(casa),data_vanzare(data),trupa(trup),nume_album(num){}

         void afisare() const{
             produs::afisare();
             cout<<"Casa de discuri este: "<<casa_disc<<endl;
             cout<<"Data vanzare: "<<data_vanzare<<endl;
             cout<<"Trupa : "<<trupa<<endl;
             cout<<"Numele albumului : "<<nume_album<<endl;
             cout<<"Pretul final + transport: "<<calcPret()<<endl;
         }
         double calcPret()const{
            return pret_baza+5;
        }




};
