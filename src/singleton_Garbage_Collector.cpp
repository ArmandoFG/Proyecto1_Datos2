#include <iostream>
#include </home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/singleton_Garbage_Collector.h>



using namespace std;


struct Dir_VsPointer{

            int* ID = new int[10];//Puntero del id
            struct Dir_VsPointer *sgte;  //Puntero hacia el id siguiente
            struct Dir_VsPointer *ant;//puntero hacia el anterior id
            int* Direccion = new int[10];
            int* Referencias = new int[10];
            };

typedef struct Dir_VsPointer *Tnodo;

Tnodo Direcciones;  // Puntero que referencia a la lista enlazada


int ID_Generar();   //Función para generar ID
int ID;
singleton_Garbage_Collector::singleton_Garbage_Collector()
{
}



void singleton_Garbage_Collector::agregar_direccion(int dir){
    Tnodo temporal, temporal2,nuevo= new struct Dir_VsPointer;  //3 punteros auxiliares
    nuevo->sgte = NULL;
    nuevo->ant = NULL;
    *nuevo->ID = ID_Generar();  //Se le asigna el ID al nuevo dato
    *nuevo->Direccion = dir;    //Direccion de memoria del dato
    *nuevo->Referencias += 1;

    if(Direcciones == NULL){
        Direcciones = nuevo;    //Revisa si es el primer dato que se ingresa
    }

else{
    temporal = Direcciones; //Se copia el puntero de las direcciones en un temporal para recorrerlo en un while
    while(temporal->sgte != NULL){
        temporal = temporal->sgte;  //Cuando llega a null almacena el dato nuevo
    }
    temporal->sgte = nuevo;         //Se le asigna el dato anterior al nuevo dato
    temporal2 = temporal->sgte;
    temporal2->ant = temporal;
}

}

int singleton_Garbage_Collector::ID_Generar(){

    ID++;
    return ID;

}

void singleton_Garbage_Collector::Borrar_Direccion(int DIR){

     Tnodo temporal, temporal2, temporal3;
    temporal = Direcciones;
    while(*temporal->ID != DIR){
        temporal = temporal->sgte;
    }
    *temporal->Referencias -= 1;
    if(*temporal->Referencias == 0){
    temporal2 = temporal->ant;
    temporal3 = temporal->sgte;

    if(temporal->sgte == NULL && temporal->ant == NULL){
        temporal = NULL;
    }else if(temporal->sgte != NULL && temporal->ant == NULL){
        temporal3->ant = NULL;
        temporal = NULL;
        Direcciones = temporal3;
    }
    else if(temporal->sgte == NULL && temporal->ant != NULL){
        temporal2->sgte = NULL;
    }else{
        temporal2->sgte = temporal3;
        temporal3->ant = temporal2;
    }
    }


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
    int valor = *temporal->ID;
    while(*temporal->ID != iD){
        temporal = temporal->sgte;

}
    int resultado = *temporal->Direccion;
    return resultado;
}

void singleton_Garbage_Collector::sumarReferencia(int ID){
    Tnodo temporal;
    int iD = ID;
    temporal = Direcciones;
    int valor = *temporal->ID;
    while(*temporal->ID != iD){
        temporal = temporal->sgte;

}
    int resultado = *temporal->Direccion;
    *temporal->Referencias += 1;
}