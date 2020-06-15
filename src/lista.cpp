#include "/home/jonathan/Escritorio/Proyecto/Proyecto1_Datos2/src/node"
#include <iostream>
using namespace std;
using namespace std;
class lista{


private:
    node *head,*tail;
    int cantidadNodos = 0;
public:
    int getCantidadNodos() const {
        return cantidadNodos;
    }



public:

    lista(){
        head = nullptr;
        tail = nullptr;
    }
    void addNode(string linea){
        node *temp = new node();
        temp->setLinea(linea) ;
        temp->setNext(nullptr);
        if(head == nullptr)
        {
            head = temp;
            tail = temp;
            cantidadNodos++;
        }
        else
        {
            tail->setNext(temp);
            tail = tail->getNext();
            cantidadNodos++;
        }
    }
    node* sacarPrimero(){
        node *temp = head;
        head = head->getNext();
        return temp;
    }
};