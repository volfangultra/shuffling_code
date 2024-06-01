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

