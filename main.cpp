#include <iostream>
#include "shuffling.cpp"
#include <chrono>
using namespace std;

int main(){
    Program p("test.txt");
    cout << p;
    p.mjesaj(5);
    cout << endl;
    cout << p;
}