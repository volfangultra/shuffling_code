#ifndef SHUFFLING_H
#define SHUFFLING_H

#include <iostream>
#include<map>
#include <vector>
#include <fstream>

using namespace std;

class Program{
    string ime;
    vector<string> inputi;
    vector<string> outputi;
    map<string, tuple<int, vector<string>, string, vector<string>> > varijable;

    void ucitaj_liniju(string&);

    public:
    Program();
    Program(string);

    void mjesaj(int);

    friend ostream& operator<<(ostream&, Program&);
};



#endif // SHUFFLING_H