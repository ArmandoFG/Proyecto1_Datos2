#include <fstream>
#include <vector>
#include <cstring>
#include "/home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/lista.cpp"
#include "puntero.cpp"
using namespace std;
class leerTXT {
public:


public:
    lista *listaCodigo = new lista();
/**
 * lectura de archivo txt donde esta el codigo
 */
    void leerArchivo(){
        ifstream archivo;
        string linea;
        archivo.open("/home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/codigo.txt");
        if(archivo.is_open()){

            while (getline(archivo,linea)){
                    listaCodigo->addNode(linea);


            }
            ejecutarCodigo();
        }else{
            cout<<"No se encontro el archivo";
        }

    }

    leerTXT() {

    }
/**
 * metodo que almacena todo el codigo en nodos para luego interpretarlo por partes
 */
    void ejecutarCodigo(){
        for (int i = 0; i<listaCodigo->getCantidadNodos();i++){
            string linea = listaCodigo->sacarPrimero()->getLinea();
            interpretarLinea(linea);
        }



    }
    /**
 *
 * @param linea
     * metodo que lee cada linea del codigo y genera los punteros
 */
    void interpretarLinea(string linea){

        string delimitadorIgual = "=";

        auto igual = linea.find("=");

        auto amperson = linea.find("&");
        auto ptr = linea.find("VSPointer");

        if (igual != string::npos){
            string valor = linea.substr(linea.find(delimitadorIgual)+1,linea.length()-1);
            puntero *ptr = new puntero();
            int y = stoi(valor);
            ptr->nombre =  linea.substr(linea.find("VSPointer")+10,linea.find(delimitadorIgual)-11);
            ptr->data =  y;
            ptr->num = &ptr->data;


        }
        else if (amperson != string::npos){
            string valor = linea.substr(1,linea.length()-1);
            

        }
        else{
            cout<<"linea de codigo invalida";
        }

    }
};