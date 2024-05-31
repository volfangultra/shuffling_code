#ifndef SHUFFLING_H
#define SHUFFLING_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include<random>
#include <unordered_map> 
#include <string>
#include<set>

using namespace std;

enum TipOptimizacije {NONE, POSTOJI_PUT};
//POSTOJI_PUT je optimizacija tokom rjesavanja gdje prije prelaska na sljedeću boju provjerimo sa dfs-om da li je postoji put izmedju sljedecih boja.
enum TipRedoslijeda {NASUMICNO, BLIZINA_KRAJU, PRVI_KORAK, UDALJENOST};
//BLIZINA_KRAJU je optimizacija redoslijeda koja bira prvo one boje koje su blize krajevima bilo po x ili y osi
//PRVI_KORAK je optimizacija redoslijeda koja bira boje tkd da u prvom koraku te boje imamo sto manje kretanje to jest da je sto vise od koordinata (i+1, j), (i, j+1), (i, j-1), (i-1, j) nisu validne
//UDALJENOST je ooptimizacija redoslijeda koja bora bpje sa najmanjom manhatan udaljenosti


class FlowFree{
    vector<vector<int>> board; //trenutno stanje boarda
    vector<vector<bool>> posjeceno; //trenutno posjecena polja
    vector<bool> napravljen_put_za_boju; //boje za koje je napravljen put
    struct Polje{
        int x;
        int y;
        int boja;
        Polje(int a=0, int b=0, int c=0):x(a), y(b), boja(c){};
    };
    list<pair<Polje, Polje>> polja_boja; //polja boja radi brzeg pristupa (umjesto da svaki put prolazim kroz cijelu matricu)
    

    Polje pronadji_sljedecu_boju(const TipRedoslijeda tip_redoslijeda=NASUMICNO); //pronalazi sljedecu dostupnu boju
    
    bool validne_koordinate(int x, int y){return x < board.size() && y < board[0].size() && x >= 0 && y >= 0;}
    void rijesi(int trenutna_boja, int x, int y, const TipOptimizacije&, const TipRedoslijeda&);
    //Provjerava da li postoji put od (x,y) do (kraj_x, kraj_y) u trenutnom stanju ploce.
    friend void ima_put(int x, int y, int& kraj_x, int& kraj_y, bool& zavrsio, int& index_boje, vector<vector<bool>>& posjecena_polja, FlowFree& game);
    //Provjerava da li postoji put od (x,y) do neke od boja (ne koristi se ni u jednoj optimizaciji jer je pre sporo ali ideja je bila da u slucaju u kojem je 
    //jedno od polja nedostizno tada taj slucaj odma odbacujemo).
    friend void moze_izaci(int x, int y, vector<int>& moguce_boje, vector<vector<bool>>& posjecena_polja, FlowFree& game, bool& rez);

    public:
    FlowFree():board(){};
    FlowFree(int n): board(n, vector<int>(n)), posjeceno(n, vector<bool>(n, false)){if(board.size() == 0) throw "Prazan board"; };
    FlowFree(int n, int m):board(n, vector<int>(m)), posjeceno(n, vector<bool>(m, false)){if(board.size() == 0) throw "Prazan board";};
    FlowFree(vector<vector<int>> b);
    FlowFree(const string file_path, int dimention); //Konstruktor koji cita iz fajla

    bool mogu_povezati_boju(int index_boje);
    bool moze_zavrsit(int index_boje, pair<int, int> pocetak);
    bool ima_nedostizno_mjesto(); //Provjerava da li ima neko nedostizno mjesto(ne koristi se u optimizacije (koristi moze_izaci))
    bool rijesi(const TipOptimizacije tip_optimizacije=NONE, const TipRedoslijeda tip_redoslijeda=NASUMICNO); //rjesava igru i vraca false ako ne moze
    bool je_zavrsena(); //Provjerava da li je igra zavrsena
    friend ostream& operator<<(ostream&, FlowFree);


};



#endif // SHUFFLING_H