#include "produs.h"
#pragma once


class vintage:public discuri
{
    bool mint;
    int coef;//coeficientul de raritate

public:
    vintage(string den,int stc,double pret,string casa,string data,string trup,string num,bool mini,int cof):discuri(den,stc,pret,casa,data,trup,num),mint(mini),coef(cof) {}

    double calcPret()const
    {
        return pret_baza+5+coef*15;
    }
    void afisare() const
    {
        discuri::afisare();
        if(mint==1)
            cout<<"este mint"<<endl;
        else
            cout<<"nu este mint"<<endl;
        cout<<"Coeficientul de raritate este : "<<coef<<endl;
        cout<<"Pretul final + transport: "<<calcPret()<<endl;
    }




};
