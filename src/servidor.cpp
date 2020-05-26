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

                                       

//sudo apt-get install libjsoncpp-dev
//sudo apt-get install libjson-c-dev


using namespace std;

int strf(char **rbuf, const char *path);
string tipo;
string dato;
void read();
void write(string sms);

//Server side
int main(void)
{
    int puerto = 12345;
    char mensaje[1500];
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

    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        cerr << "Error en la solicitud del cliente" << endl;
        exit(1);
    }
    cout << "Coneccion establecida con el cliente" << endl;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    int bytesRead, bytesWritten = 0;
    while(1)
    {
    int len;
    char *pbuf;

    cout << "Esperando respuesta del cliente" << endl;
        
     

     recv(newSd,reinterpret_cast<char*>(&len), sizeof len, 0);

     std::ofstream outfile ("datosServer.json",std::ofstream::binary);

     pbuf = new char [len];
        
     recv(newSd, pbuf, len, 0);

     outfile.write(pbuf, len);
     delete [] pbuf;
     read();
     cout <<  tipo << endl;
     cout << "> ";

     
         
        char *rbuf;
        cin >> mensaje;
        write(mensaje);
        int len2 = strf(&rbuf, "datosServer.json");
        send(newSd, reinterpret_cast<char*>(&len2), sizeof len2 , 0);
        send(newSd, rbuf, len2, 0);
    }
    close(newSd);
    close(serverSd);
    cout << "Coneccion cerrada" << endl;
    return 0;
  

}
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

void read(){
    ifstream ifs("datosServer.json");   // Json a leer
    Json::Value read_obj;       // Variable para leer json
    Json::Reader reader;
    reader.parse(ifs, read_obj);    //Leer json
    tipo = read_obj["mensaje"].asString();  // Obtener valor del json
   
}

void write(string sms){
    Json::Value obj;    // Dato del json a sobreescribir
    obj["mensaje"]= sms;
    Json::StyledWriter SW ;
    ofstream OS;
    OS.open("datosServer.json"); // Abrir archivo json
    OS << SW.write(obj);  // Escribir nuevos datos al json
    OS.close(); // Cerrar archivo
}


