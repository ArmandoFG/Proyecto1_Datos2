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
#include <jansson.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>  
#include <sstream> 
#include "md5.h"
#include "md5.cpp"     

using namespace std;

int strf(char **pbuf, const char *path);
string tipo;
string dato;
string Operacion;
string ip = "vacio";
string pass = "vacio";
int status;
int status2 = -1; 
int client;
int DATO;
int puerto = 0; // Puerto a usar
string infoServer;
void read();
void write(string tipo, string operacion, string dato);
void menu();
void conexion();
void enviarInfoServer();
void readLogin();
void CleanLogin();
void enviarPassword();

/**
 * @brief main Inicializa al cliente
 * 
 * @return int 
 */

int main(void)
{
    while(status2 < 0){
      while(ip == "vacio" && puerto == 0 && pass == "vacio"){

          
          sleep(2);
          readLogin();
          
  
            
      }
            cout << ip << endl;
            cout << puerto << endl;
            const char *IpServidor =  ip.c_str();
            struct hostent* host = gethostbyname(IpServidor);
            sockaddr_in sendSockAddr;
            bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
            sendSockAddr.sin_family = AF_INET;
            sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
            sendSockAddr.sin_port = htons(puerto);
            dato = md5(pass);
            Operacion = "verificar";
            tipo = "";
            client = socket(AF_INET, SOCK_STREAM, 0);   // Socket del cliente
            status = connect(client,
                            (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
            cout << status << endl;

            if(status < 0)
                {
                    cout<<"Error al conectar el socket"<<endl;
                    sleep(2);
                    CleanLogin();
                    ip = "vacio";
                    puerto = 0;
                    pass = "vacio";
                    

                }else{
                status2 = status;
                cout << "Conectado al servidor" << endl;}
  
}
    enviarPassword();
    CleanLogin();
    

    while(1)
    {
      
    int Opcion = 0;
        do
            {
                menu();
                cin>>Opcion;

    switch (Opcion) {

    case 1:

        cout<< "Ingrese dato a ingresar: ";
       
        cin>>dato;
        
        Operacion = "guardar";
        tipo = "Interger";
        break;

    case 2:

        cout<<"Ingrese id para obtener dato: ";
        cin>>dato;
        Operacion = "obtener";
        tipo = "";
        break;

    case 3:
        cout<<"Ingrese id para borrar dato ";
        cin>>dato;
        Operacion = "borrar";
        tipo = "";
        
        break;
       



    }
    
        char *pbuf; //Datos del json del cliente
        write(tipo, Operacion, dato);
        int len = strf(&pbuf, "datos.json");
        send(client, reinterpret_cast<char*>(&len), sizeof len , 0); // Enviar datos al server

        send(client, pbuf, len, 0); // Enviar datos al server

        cout << "Esperando respuesta del servidor..." << endl;

        int len2;
        char *rbuf;
        
        std::ofstream outfile ("datos.json",std::ofstream::binary);

        recv(client,reinterpret_cast<char*>(&len2), sizeof len2, 0);

        rbuf = new char [len2]; // Variable que almacena datos recibidos
        
        recv(client, rbuf, len2, 0);  // Recibir datos del json  

        outfile.write(rbuf, len2);
        outfile.close();
        string sms_recv = rbuf;
        read(); // Leer json
        cout << dato;
            
        
    }

    while(Opcion != 7);{

    }
      
    close(client);  // Cerrar socket del cliente
    cout << "Coneccion cerrada" << endl;
    return 0;

         
    }   
}

/**
 * @brief strlf Metodo para obtener tamaño del json
 * 
 * @param pbuf Contenido del json
 * @param path Dirección del json
 * @return int 
 */

int strf(char **pbuf, const char *path){
    //Metodo para analizar tamaño de los datos del json

int len;

    std::ifstream is;
    is.open (path, std::ios::binary ); // Archivo json

    is.seekg (0, std::ios::end);
    len = is.tellg();       // Tamaño del json
    is.seekg (0, std::ios::beg);

  
    *pbuf = new char [len]; // Variable que almacena informacion del json

    is.read (*pbuf, len);   // Obtener datos del json
    is.close();

return len; // Retornar valor de json
}

/**
 * @brief Metodo para leer json
 * 
 */
void read(){
    ifstream ifs("datos.json");     // Json a leer
    Json::Value read_obj;   // Variable para leer json
    Json::Reader reader;
    reader.parse(ifs, read_obj);    //Leer json
    tipo = read_obj["tipo"].asString();
    if(tipo != "string"){
        DATO = stoi(read_obj["dato"].asString()); 
    }
    dato = read_obj["dato"].asString();
    infoServer = read_obj["Heap"].asString();
    enviarInfoServer();
    

   
}



/**
 * @brief Metodo para escribir en el jsom
 * 
 * @param tipo Tipo de dato
 * @param operacion Tipo de operacion
 * @param dato Dato principal
 */

void write(string tipo, string operacion, string dato){
    Json::Value obj;   // Dato del json a sobreescribir
    obj["tipo"]= tipo; 
    obj["operacion"]= operacion;
    obj["dato"]= dato;
    Json::StyledWriter SW ;
    ofstream OS;
    OS.open("datos.json");  // Abrir archivo json
    OS << SW.write(obj);  // Escribir nuevos datos al json
    OS.close();     // Cerrar archivo
}

void enviarInfoServer(){
    ofstream archivoDato;
    string info ="";
    archivoDato.open("dataClienteServer.txt", ios::out);
    archivoDato << "";
    archivoDato.close();
    archivoDato.open("dataClienteServer.txt", ios::out | ios::app);
    archivoDato << infoServer << endl;;
    archivoDato.close();
    
}

void readLogin(){
    ifstream ifs("IniciarSeccion.json");     // Json a leer
    Json::Value read_obj;   // Variable para leer json
    Json::Reader reader;
    reader.parse(ifs, read_obj);    //Leer json
    ip = read_obj["ip"].asString();
    puerto = stoi(read_obj["puerto"].asString()); 
    pass = read_obj["contrasena"].asString();
    
}

void CleanLogin(){
    Json::Value obj;   // Dato del json a sobreescribir
    obj["ip"]= "vacio"; 
    obj["contrasena"]= "vacio";
    obj["puerto"]= "0";
    Json::StyledWriter SW ;
    ofstream OS;
    OS.open("IniciarSeccion.json");  // Abrir archivo json
    OS << SW.write(obj);  // Escribir nuevos datos al json
    OS.close();     // Cerrar archivo
}

void enviarPassword(){
    char *pbuf; //Datos del json del cliente
        write(tipo, Operacion, dato);
        int len = strf(&pbuf, "datos.json");
        send(client, reinterpret_cast<char*>(&len), sizeof len , 0); // Enviar datos al server

        send(client, pbuf, len, 0); // Enviar datos al server

        cout << "Esperando respuesta del servidor..." << endl;

        int len2;
        char *rbuf;
        
        std::ofstream outfile ("datos.json",std::ofstream::binary);

        recv(client,reinterpret_cast<char*>(&len2), sizeof len2, 0);

        rbuf = new char [len2]; // Variable que almacena datos recibidos
        
        recv(client, rbuf, len2, 0);  // Recibir datos del json  

        outfile.write(rbuf, len2);
        outfile.close();
        string sms_recv = rbuf;
        read(); // Leer json
        cout << dato;

}



void menu(){
    cout<< "\n1) Agregar \n"
           "2) Obtener \n"
           "3) Salir \n"
           "4) Verificar conexion \n";

}
