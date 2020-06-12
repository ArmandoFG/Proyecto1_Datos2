#ifndef SINGLETON_GARBAGE_COLLECTOR_SERVIDOR_H
#define SINGLETON_GARBAGE_COLLECTOR_SERVIDOR_H

class singleton_Garbage_Collector_Servidor
{
public:
    singleton_Garbage_Collector_Servidor();
    static singleton_Garbage_Collector_Servidor& Instancia();
    int ID_Generar();
    void agregar_direccion(int dir);
    void Borrar_Direccion(int DIR);
    int obtener(int ID);
    void sumarReferencia(int ID);


};

#endif // SINGLETON_GARBAGE_COLLECTOR_SERVIDOR_H