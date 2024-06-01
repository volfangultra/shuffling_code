#include "shuffling.h"
#include "help.cpp"
using namespace std;

void Program::ucitaj_liniju(string& linija) {
    int i = 0;
    int kraj = linija.size();
    //Prodji kroz sve prazne linije
    prodji_kroz_prazno(linija, i, kraj);

    //Pokupi symbol
    string simbol = "";
    while(!je_ekvivalencija(linija[i])){
        simbol += linija[i];
        i++;
        if(i == kraj)
            throw "Sytax error";
    }
    if(simbol == "")
        throw "Syntax error";
    
    //Prodji kroz sve prazne linija
    prodji_kroz_prazno(linija, i, kraj);
    
    //Pokupi ekvivalenciju
    string ekvivalencija = "";
    ekvivalencija += linija[i];
    while(je_ekvivalencija(ekvivalencija)){
        ekvivalencija += linija[i];
        i++;
        if(i == kraj)
            throw "Syntax error";
    }
    if(ekvivalencija == "")
        throw "Syntax error";

    ekvivalencija.pop_back();
    i--;

    //Prodji kroz sve prazne linije
    prodji_kroz_prazno(linija, i, kraj);





}

Program::Program(string ime_fajla){
    
    std::ifstream fajl(ime_fajla);

    if (!fajl.is_open()) 
        throw "Unable to open file";

    string linija;
    
    while (std::getline(fajl, linija)) 
        ucitaj_liniju(linija);
    
    
    fajl.close();
}