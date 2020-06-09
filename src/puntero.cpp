
#include <iostream>
#include </home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/singleton_Garbage_Collector.h>
#include </home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/singleton_Garbage_Collector.cpp>
using namespace std;
class puntero {

public:
    
    singleton_Garbage_Collector* garbage = &singleton_Garbage_Collector().Instancia();
    int *num;
    int data;
    int Id;
    puntero& operator=(int x){
        
        
        this->data = x;
        this->num = &x;
        this->Id = garbage->ID_Generar();
        return *this;
    }
    puntero* operator*(int x){
        this->data = x;
    }

    puntero& operator=(puntero y){
        this->data = y.data;
        this->num = y.num;
        this->Id = y.Id;
        garbage->sumarReferencia(y.Id);
        return *this;
    }

    int * operatorDelete(puntero *x){


        int *memoriaLiberada = x->num;
        int idEliminar = x->Id;
        garbage->Borrar_Direccion(idEliminar);
        delete x;
        return memoriaLiberada;

    }
};