#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h> 
#include "singleton_Garbage_Collector.h"
#include "singleton_Garbage_Collector.cpp"                                    
#include <sstream>
#include "md5.h"
#include "md5.cpp" 
                                       



using namespace std;

int strf(char **rbuf, const char *path);
string tipo;
int DATO;
string Operacion; 
string dato;
singleton_Garbage_Collector* garbage = &singleton_Garbage_Collector().Instancia();
void read();
void write(string Tipo, string Oper, string dato);
void operacion(string operacion, int dato);
string password = md5("barriga");
bool verificar = false;
int newSd;


/**
 * @brief main Funcionalidades del servidor
 * */
int main(void)
{
    int puerto = 12345;
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(puerto);
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cout << "Error al establecer el socket del servidor" << endl;
        exit(0);
    }
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cout << "Error al vincular el socket a la dirección local" << endl;
        exit(0);
    }
    cout << "Esperando conexion del cliente" << endl;
    listen(serverSd, 5);

    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error en la solicitud del cliente" << endl;
        exit(1);
    }
    cout << "Coneccion establecida con el cliente" << endl;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    while(1)
    {
 
    int len;
    char *pbuf;

    cout << "Esperando respuesta del cliente" << endl;
        
     

     recv(newSd,reinterpret_cast<char*>(&len), sizeof len, 0);

     std::ofstream outfile ("datosServer.json",std::ofstream::binary);

     pbuf = new char [len];
        
     recv(newSd, pbuf, len, 0);

     string sms_recv = pbuf;

     outfile.write(pbuf, len);
     outfile.close();
     delete [] pbuf;
     read();
     operacion(Operacion, DATO);
     write(tipo, dato, dato);
     char *rbuf;
     int len2 = strf(&rbuf, "datosServer.json");
     send(newSd, reinterpret_cast<char*>(&len2), sizeof len2 , 0);
     send(newSd, rbuf, len2, 0);
     
    

    }
    close(newSd);
    close(serverSd);
    cout << "Coneccion cerrada" << endl;
    verificar = false;
    return 0;
  

}

/**
 * @brief strlf Metodo para obtener tamaño del json
 * 
 * @param rbuf Contenido del json
 * @param path Dirección del json
 * @return int 
 */
int strf(char **rbuf, const char *path){

    //Metodo para analizar tamaño de los datos del json

int len;

    std::ifstream is;
    is.open (path, std::ios::binary );  // Archivo json

    is.seekg (0, std::ios::end);
    len = is.tellg();       // Tamaño del json
    is.seekg (0, std::ios::beg);

  
    *rbuf = new char [len]; // Variable que almacena informacion del json
    is.read (*rbuf, len);   // Obtener datos del json
    is.close();

return len; // Retornar valor del tamaño del json
}

/**
 * @brief read Metodo para leer los datos del json
 * */
void read(){
    ifstream ifs("datosServer.json");   // Json a leer
    Json::Value read_obj;       // Variable para leer json
    Json::Reader reader;
    reader.parse(ifs, read_obj);    //Leer json
    tipo = read_obj["tipo"].asString();  // Obtener valor del json
    Operacion = read_obj["operacion"].asString();  // Obtener valor del json
    if(tipo != "string"){
        DATO = stoi(read_obj["dato"].asString()); 

    }
    dato = read_obj["dato"].asString();
}


/**
 * @brief Metodo para escribir datos al json
 * @param Tipo Variable que indica de que tipo es el dato recibido
 * @param Oper Define el tipo de operacion que se requere hacer
 * @param dato Variable con el dato a pasar
 * */
void write(string Tipo, string Oper, string dato){
    Json::Value obj;    // Dato del json a sobreescribir
    obj["tipo"]= Tipo; 
    obj["operacion"]= Oper;
    obj["dato"]= dato;
    Json::StyledWriter SW ;
    ofstream OS;
    OS.open("datosServer.json"); // Abrir archivo json
    OS << SW.write(obj);  // Escribir nuevos datos al json
    OS.close(); // Cerrar archivo
}
/**
 * @brief operacion Metodo que le indica al server que debe hacer
 * @param operacion Indica que tipo de funcion debe hacer
 * @param num Variable del ID del dato
 * */

void operacion(string operacion, int num){
    if(operacion == "guardar" && verificar == true){
        garbage->agregar_direccion(num);
        dato = "Dato guardado";
        tipo = "string";
    }else if(operacion == "obtener" && verificar == true){
        DATO = garbage->obtener(num);
        stringstream ss;
        ss << DATO;
        dato = ss.str();
        tipo = "Integer";
        
    }else if(operacion == "borrar" && verificar == true){
        garbage->Borrar_Direccion(num);
        dato = "Dato borrado";
        tipo = "string";
    }else if(operacion == "verificar"){
        if(dato == password){
            verificar = true;
            dato = "Comunicacion correcta";
            tipo = "string";
        }else{
            tipo = "string";
            dato = "Error al iniciar comunicacion, contraseña incorrecta";
        }
    }else{
        dato = "Ingresar contraseña del server";
        tipo = "string";
    }
}





