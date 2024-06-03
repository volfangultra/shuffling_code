#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool cmp(pair<string, tuple<int, vector<string>, string, vector<string>>>& a, pair<string, tuple<int, vector<string>, string, vector<string>>>& b) { 
    return get<LINIJA>(a.second) < get<LINIJA>(b.second); 
};

ostream& operator<<(ostream& ispis, pair<string, pair<int, int>> par){
    ispis << par.first << " : (" << par.second.first << ", " << par.second.second << ")";;
    return ispis;
}


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



template<typename Tip>
ostream& operator<<(ostream& ispis, pair<Tip, Tip> v){
    ispis << "{" << v.first << ", " << v.second << "}";
    return ispis;
}

ostream& operator<<(ostream& ispis, map<string, tuple<int, vector<string>, string, vector<string>> > linije){
    vector<pair<string, tuple<int, vector<string>, string, vector<string>>>> helper(linije.begin(), linije.end());
    sort(helper.begin(), helper.end(), cmp);

    for(auto it = helper.begin(); it != helper.end(); it++){
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

