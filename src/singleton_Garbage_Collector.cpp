#include <iostream>
#include </home/armando/Project/src/singleton_Garbage_Collector.h>

using namespace std;
struct Dir_VsPointer{

            int ID;//Puntero del id
            struct Dir_VsPointer *sgte;  //Puntero hacia el id siguiente
            struct Dir_VsPointer *ant;//puntero hacia el anterior id
            int Direccion;
            };

typedef struct Dir_VsPointer *Tnodo;
bool first = true;
Tnodo Direcciones;
int IDent = 0;

singleton_Garbage_Collector::singleton_Garbage_Collector(){

};
//Lista enlazada para almacenar los punteros




int ID_Generar();   //Función para generar ID



void singleton_Garbage_Collector::agregar_direccion(int dir){
    Tnodo temporal, temporal2,nuevo= new struct Dir_VsPointer;  //3 punteros auxiliares
    nuevo->sgte = NULL;
    nuevo->ant = NULL;
    nuevo->ID = ID_Generar();  //Se le asigna el ID al nuevo dato
    nuevo->Direccion = dir;    //Direccion de memoria del dato
    if((first = true)){
        Direcciones = nuevo;
        first = false;
        //Revisa si es el primer dato que se ingresa
    }

else{
    temporal = Direcciones; //Se copia el puntero de las direcciones en un temporal para recorrerlo en un while
    while(temporal->sgte!=NULL){
        temporal = temporal->sgte;  //Cuando llega a null almacena el dato nuevo
    }
    temporal->sgte = nuevo;         //Se le asigna el dato anterior al nuevo dato
    temporal2 = temporal->sgte;
    temporal2->ant = temporal;
}

}

int singleton_Garbage_Collector::ID_Generar(){

    IDent++;
    return IDent;

}

void singleton_Garbage_Collector::Borrar_Direccion(int ID){

    Tnodo temporal, temporal2, temporal3;
    temporal = Direcciones;
    while(temporal->ID != ID){
        temporal = temporal->sgte;
    }
    temporal2 = temporal->ant;
    temporal3 = temporal->sgte;

    temporal2->sgte = temporal3;
    temporal3->ant = temporal2;


}

//Esta funcion se debe a que el garbage funciona como un singleton entonces este retorna
//Una nueva instancia y asi se asegura que sea la unica asi que cuando la ocupe
//simplemente llama a esta función en la clase que la necesite

singleton_Garbage_Collector& singleton_Garbage_Collector::Instancia(){
    static singleton_Garbage_Collector Garbage;
    return Garbage;
}

int singleton_Garbage_Collector::obtener(int ID){
    Tnodo temporal;
    int iD = ID;
    temporal = Direcciones;
    while(temporal->ID != iD){
        cout<<temporal->Direccion<<" : "<<temporal->ID<<endl;
        temporal = temporal->sgte;

}
    int resultado = temporal->Direccion;
    return resultado;
}
