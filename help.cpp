#include <fstream>
#include <vector>
#include <string>

using namespace std;
template<typename Tip>
ostream& operator<<(ostream& ispis, vector<Tip> v){
    for(auto el:v)
        ispis << el << " ";
    return ispis;
}

template<typename Tip>
ostream& operator<<(ostream& ispis, vector<vector<Tip>> v){
    for(auto el:v)
        ispis << el << endl;
    return ispis;
}

ostream& operator<<(ostream& ispis, map<string, tuple<int, vector<string>, string, vector<string>> > linije){

    for(auto it = linije.begin(); it != linije.end(); it++){
        ispis << "    " << get<LINIJA>(it->second) << ". " << it->first << " " << get<EKVIVALENCIJA>(it->second) << " ";
        for(int i = 0; i < get<OPERACIJE>(it->second).size(); i++)
            ispis << get<VARIJABLE>(it->second)[i] << " " << get<OPERACIJE>(it->second)[i] << " ";
        ispis << get<VARIJABLE>(it->second)[get<OPERACIJE>(it->second).size()] << endl;
    }
    return ispis;
}

bool je_ekvivalencija(string znak){
    return (znak == "=" || znak == ">" || znak == "<" || znak == "<=" || znak == ">=");
}

bool je_ekvivalencija(char znak){
    return (znak == '=' || znak == '>' || znak == '<');
}

bool je_operacija(string znak){
    return (znak == "+" || znak == "*" || znak == "/");
}

bool je_operacija(char znak){
    return (znak == '+' || znak == '>' || znak == '<');
}

void prodji_kroz_prazno(string& linija, int& i, int kraj){
    while(linija[i] == ' '){
        i++;
        if(i == kraj)
            throw "Syntax error";
    }
}

void provjeri_granice(string& linija, int& i){
    if(i >= linija.size() || i < 0)
        throw "Syntax error";
}

ostream& operator<<(ostream& ispis, Program& program){
    return ispis;
}