#ifndef SHUFFLING_H
#define SHUFFLING_H

#include <iostream>
#include<map>
#include <vector>
#include <fstream>

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
    int broj_linija;

    void ucitaj_liniju(string&, int);
    void ucitaj_header(string&);

    public:
    Program();
    Program(string);

    void mjesaj(int);
    int get_broj_linija(){return broj_linija;};

    friend ostream& operator<<(ostream&, Program&);
};



#endif // SHUFFLING_H