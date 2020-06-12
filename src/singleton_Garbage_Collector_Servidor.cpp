#include <iostream>
#include </home/armando/Project/src/singleton_Garbage_Collector_Servidor.h>



using namespace std;


struct Dir_VsPointer{

            int* ID = new int[10];//Puntero del id
            struct Dir_VsPointer *sgte;  //Puntero hacia el id siguiente
            struct Dir_VsPointer *ant;//puntero hacia el anterior id
            int* Direccion = new int[10];   //Direccion que almacena el garbage
            int* Referencias = new int[10]; //Numero de referencias del puntero
            };

typedef struct Dir_VsPointer *Tnodo;

Tnodo Direcciones;  // Puntero que referencia a la lista enlazada


int ID_Generar();   //Función para generar ID
int ID;
singleton_Garbage_Collector_Servidor::singleton_Garbage_Collector_Servidor()
{
}

/**
 * @brief agregar_direccion Metodo para ingresar un dato al garbage
 * @param dir Direccion de memoria del dato
 * 
 * */

void singleton_Garbage_Collector_Servidor::agregar_direccion(int dir){
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

/**
 * @brief ID_Generar Metodo que genera una id al dato
 * 
 * */

int singleton_Garbage_Collector_Servidor::ID_Generar(){

    ID++;
    return ID;

}

/**
 * @brief Borrar_Direccion Metodo para borrar un dato de la lista enlazada
 * @param DIR ID del dato en la lista
 * 
 * */
void singleton_Garbage_Collector_Servidor::Borrar_Direccion(int DIR){

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

/**
 * @brief singleton_Garbage_Collector Metodo para instanciar la clase del garbage
 * 
 * 
 * */

singleton_Garbage_Collector_Servidor& singleton_Garbage_Collector_Servidor::Instancia(){
    static singleton_Garbage_Collector_Servidor Garbage;
    return Garbage;
}

/**
 * @brief obtener Metodo para retornar un dato de la lista
 * @param ID Identificacion del dato en la lista
 * */
int singleton_Garbage_Collector_Servidor::obtener(int ID){
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
/**
 * @brief sumarReferencia Metodo para agregar una nueva referencia a un dato
 * @param ID Identificacion del dato en la lista
 * */

void singleton_Garbage_Collector_Servidor::sumarReferencia(int ID){
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