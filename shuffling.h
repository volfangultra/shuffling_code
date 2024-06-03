#ifndef SHUFFLING_H
#define SHUFFLING_H

#include <iostream>
#include<map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const int LINIJA = 0;
const int VARIJABLE = 1;
const int EKVIVALENCIJA = 2;
const int OPERACIJE = 3;

class Program{
    string ime;
    vector<string> inputi;
    string output;
    map<string, tuple<int, vector<string>, string, vector<string>> > varijable;

    vector<pair<string, pair<int, int>>> zavisnosti;
    vector<pair<string, string>> moguce_promjene;

    int broj_linija;

    void ucitaj_liniju(string&, map<string, string>&, int);
    void ucitaj_header(string&);
    bool je_input(string&);
    void pronadji_promjene();

    public:
    Program();
    Program(string, bool file = true);

    void mjesaj(int jacina, int seed=42);
    int get_broj_linija(){return broj_linija;};

    friend ostream& operator<<(ostream&, Program&);
};



#endif // SHUFFLING_H