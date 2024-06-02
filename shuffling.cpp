#include "shuffling.h"
#include "help.cpp"
using namespace std;

void Program::ucitaj_liniju(string& linija, int broj_linije) {
    int i = 0;
    int kraj = linija.size();
    if(kraj == 0)
        return;

    prodji_kroz_prazno(linija, i, kraj);

    string key = "";
    while(!je_ekvivalencija(linija[i]) && !je_operacija(linija[i]) && !(linija[i] == ' ')){
        key += linija[i];
        i++;
        provjeri_granice(linija, i);
    }
    if(key == "")
        throw "Syntax error";

    prodji_kroz_prazno(linija, i, kraj);

    string ekvivalencija = "";
    ekvivalencija += linija[i];
    while(je_ekvivalencija(ekvivalencija)){
        i++;
        ekvivalencija += linija[i];
        provjeri_granice(linija, i);
    }
    if(ekvivalencija == "")
        throw "Syntax error";

    ekvivalencija.pop_back();
    if(!je_ekvivalencija(ekvivalencija))
        throw "Syntax error";

    prodji_kroz_prazno(linija, i, kraj);

    varijable[key] = make_tuple(broj_linije, vector<string>(), ekvivalencija, vector<string>());

    while(i != kraj){
        string simbol = "";
        while(!je_operacija(linija[i]) && !je_ekvivalencija(linija[i]) && !(linija[i] == ' ')){
            simbol += linija[i];
            i++;
            if(i == kraj){
                get<VARIJABLE>(varijable[key]).push_back(simbol);
                return;
            }
            provjeri_granice(linija, i);
        }

        get<1>(varijable[key]).push_back(simbol);
        prodji_kroz_prazno(linija, i, kraj);
        if(i == kraj)
            return;


        string operacija = "";
        operacija += linija[i];
        while(je_operacija(operacija) && !(linija[i] == ' ')){
            i++;
            operacija += linija[i];
            provjeri_granice(linija, i);
        }
        operacija.pop_back();
        get<OPERACIJE>(varijable[key]).push_back(operacija);
        prodji_kroz_prazno(linija, i, kraj);

    }
}

void Program::ucitaj_header(string& header){
    int i = 0;
    int kraj = header.size();
    if(kraj == 0)
        throw "Syntax Error";
    prodji_kroz_prazno(header, i, kraj);

    string name = "";
    while(header[i] != '(' || header[i] == ' '){
        name += header[i];
        i++;
        provjeri_granice(header, i);
    }
    ime = name;
    
    prodji_kroz_prazno(header, i, kraj);
    if(header[i] != '(')
        throw "Syntax Error";
    i++;
    provjeri_granice(header, i);

    string temp = "";
    while(header[i] != ')'){
        provjeri_granice(header, i);
        if (temp != "" && (header[i] == ' ' || header[i] == ',')){
            inputi.push_back(temp);
            temp = "";
        }

        if (header[i] == ' ')
            prodji_kroz_prazno(header, i, kraj);
        
        if(header[i] == ','){
            i++;
            provjeri_granice(header, i);
        }

        if (header[i] == ' ')
            prodji_kroz_prazno(header, i, kraj);

        temp += header[i];
        i++;

    }
    
}

Program::Program(string ime_fajla){

    std::ifstream fajl(ime_fajla);

    if (!fajl.is_open())
        throw "Unable to open file";

    string linija;
    getline(fajl, linija);
    ucitaj_header(linija);
    cout << linija << endl;

    int broj_linije = 1;
    while (getline(fajl, linija)){
        ucitaj_liniju(linija, broj_linije);
        broj_linije++;
    }

    broj_linija --;
    cout << varijable;


    fajl.close();
}
