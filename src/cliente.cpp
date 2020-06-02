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

using namespace std;

int strf(char **pbuf, const char *path);
string tipo;
string dato;
string Operacion; 
int DATO;
void read();
void write(string tipo, string operacion, string dato);
void menu();

int main(void)
{

    const char *IpServidor = "127.0.0.1";   //Ip servidor
    int puerto = 12345; // Puerto a usar
    struct hostent* host = gethostbyname(IpServidor);
    sockaddr_in sendSockAddr;
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(puerto);
    int client = socket(AF_INET, SOCK_STREAM, 0);   // Socket del cliente

    //Corroborar si el socket funciona
    int status = connect(client,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error al conectar el socket"<<endl;

    }
    cout << "Conectado al servidor" << endl;
  

    while(1)
    {
        //cout << "> ";
        //char *pbuf; //Datos del json del cliente
        //string mensaje; 
        //cin >> mensaje;
        //write(mensaje);
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
    case 4:
        cout<<"Ingrese contraseña del server: ";
        cin>>dato;
        Operacion = "verificar";
        tipo = "string";
        
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

void read(){
    ifstream ifs("datos.json");     // Json a leer
    Json::Value read_obj;   // Variable para leer json
    Json::Reader reader;
    reader.parse(ifs, read_obj);    //Leer json
    DATO = stoi(read_obj["dato"].asString());  // Obtener valor del json
    dato = read_obj["dato"].asString();
    

   
}

/**
 *
 *  
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



void menu(){
    cout<< "1) Agregar \n"
           "2) Obtener \n"
           "3) Salir \n"
           "4) Verificar conexion \n";

}