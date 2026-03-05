#include "angajati.h"
#pragma once

class manager:virtual public angajati{

public:
    manager(string numee,string pren,string cnpp,int zia,int lunaa,int anA,int ziN,int lunaN,int anN):angajati(numee,pren,cnpp,zia,lunaa,anA,ziN,lunaN,anN){}

    double calcSalariu()const override{
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int lunaActual = 1 + ltm->tm_mon;
        
        int vechime = getVechime();
        double salariu = (salariu_baza + vechime * 100) * 1.25;
        return salariu;
    }
    void afisare(){
        angajati::afisare();
        double sal=calcSalariu();
        cout<<"Salariul este: "<<sal<<endl;

    }


};
