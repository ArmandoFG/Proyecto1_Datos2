#ifndef SINGLETON_GARBAGE_COLLECTOR_H
#define SINGLETON_GARBAGE_COLLECTOR_H

class singleton_Garbage_Collector
{
public:
    singleton_Garbage_Collector();
    static singleton_Garbage_Collector& Instancia();
    int ID_Generar();
    void agregar_direccion(int dir);
    void Borrar_Direccion(int DIR);
    int obtener(int ID);
    void sumarReferencia(int ID);
    string buscar();
    void enviarInfo();

};

#endif // SINGLETON_GARBAGE_COLLECTOR_H