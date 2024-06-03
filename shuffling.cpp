#include "shuffling.h"
#include "help.cpp"
using namespace std;

ostream& operator<<(ostream& ispis, Program& program){
    ispis << program.ime << "(";
    for(auto el: program.inputi)
        ispis << el << ", ";
    ispis << program.output << ")" << endl;
    ispis << program.varijable;

    return ispis;
}

bool Program::je_input(string& text){
    for(auto el: inputi)
        if(el == text)
            return true;
    return false;
}

void Program::ucitaj_liniju(string& linija, map<string, string>& mapa_transformacija, int broj_linije) {
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

    bool update = false;
    string predhodni_key = key;
    if(mapa_transformacija.find(key) != mapa_transformacija.end()){
        key = mapa_transformacija[key] + "1";
        update = true;
    }
    else
        mapa_transformacija[key] = key;

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
                if(je_input(simbol))
                    get<VARIJABLE>(varijable[key]).push_back(simbol);
                else{
                    if(mapa_transformacija.find(simbol) == mapa_transformacija.end()) throw "Syntax Error";
                    get<VARIJABLE>(varijable[key]).push_back(mapa_transformacija[simbol]);
                }

                break;
            }
            provjeri_granice(linija, i);
        }

        if(je_input(simbol))
            get<VARIJABLE>(varijable[key]).push_back(simbol);
        else{
            if(mapa_transformacija.find(simbol) == mapa_transformacija.end()) throw "Syntax Error";
            get<VARIJABLE>(varijable[key]).push_back(mapa_transformacija[simbol]);
        }
        prodji_kroz_prazno(linija, i, kraj);
        if(i == kraj)
            break;


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

    if(update)
        mapa_transformacija[predhodni_key] = key;
    
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
    output = temp;
}

bool mogu_se_zamjeniti(pair<string, pair<int, int>>& a, pair<string, pair<int, int>>& b, map<string, tuple<int, vector<string>, string, vector<string>> >& varijable){
    int red_a = get<LINIJA>(varijable[a.first]);
    int red_b = get<LINIJA>(varijable[b.first]);
    return red_b > a.second.first && red_b < a.second.second && red_a > b.second.first && red_a < b.second.second;
}

void Program::pronadji_promjene(){
    vector<pair<string, tuple<int, vector<string>, string, vector<string>>>> helper(varijable.begin(), varijable.end());
    sort(helper.begin(), helper.end(), cmp);

    for (auto it = helper.begin(); it != helper.end() - 1; it++){
        int prije_najkasnije = -1;
        int poslije_najprije = helper.size();
        int osnovna = get<LINIJA>(it->second);

        for(auto varijabla: get<VARIJABLE>(it->second)){
            if(!je_input(varijabla)){
                int trenutno = get<LINIJA>(varijable[varijabla]);
                if(trenutno < osnovna)
                    prije_najkasnije = max(trenutno, prije_najkasnije);
                else
                    poslije_najprije = min(trenutno, poslije_najprije);
            }
        }

        zavisnosti.push_back({it->first, {prije_najkasnije, poslije_najprije}});
    }

    for(int i = 0; i < zavisnosti.size(); i++){
        for(int j = i + 1; j < zavisnosti.size(); j++){
            if(mogu_se_zamjeniti(zavisnosti[i],zavisnosti[j], varijable))
                moguce_promjene.push_back({zavisnosti[i].first, zavisnosti[j].first});
        }
    }
}




Program::Program(string ime_fajla, bool file){
    map<string, string> mapa_transformacija;
    if(file){
    ifstream fajl(ime_fajla);
        if (!fajl.is_open())
            throw "Unable to open file";

        string linija;
        getline(fajl, linija);
        ucitaj_header(linija);

        int broj_linije = 1;
        while (getline(fajl, linija)){
            ucitaj_liniju(linija, mapa_transformacija, broj_linije);
            broj_linije++;
        }

        broj_linija --;

        fajl.close();
    } else{
        istringstream iss(ime_fajla);
        string linija;
        getline(iss, linija);
        ucitaj_header(linija);

        int broj_linije = 1;
        while (getline(iss, linija)){
            ucitaj_liniju(linija, mapa_transformacija, broj_linije);
            broj_linije++;
        }

        broj_linija --;
    }


    pronadji_promjene();
}

void Program::mjesaj(int broj_mjesanja, int seed){
    for(int _ = 0; _ < broj_mjesanja; _++){
        int index = rand()%moguce_promjene.size();
        int broj_linije_prve = get<LINIJA>(varijable[moguce_promjene[index].first]);
        int broj_linije_druge= get<LINIJA>(varijable[moguce_promjene[index].second]);
        get<LINIJA>(varijable[moguce_promjene[index].first]) = broj_linije_druge;
        get<LINIJA>(varijable[moguce_promjene[index].second]) = broj_linije_prve;
    }
}
