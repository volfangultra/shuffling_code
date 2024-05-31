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


