
#include <iostream>
using namespace std;
class puntero {

public:
    int *num;
    int data;
    puntero& operator=(int x){
        this->data = x;
        this->num = &x;
        return *this;
    }
    puntero* operator*(int x){
        this->data = x;
    }

    puntero& operator=(puntero y){
        this->data = y.data;
        this->num = y.num;
        return *this;
    }

    int * operatorDelete(puntero *x){


        int *memoriaLiberada = x->num;
        delete x;
        return memoriaLiberada;

    }
};