#include "lista_enlazada.h"

int main() {

    // Crear la lista en el heap, es necesario hacer un "delete"
    //Lista* lista = new Lista();
    //lista->insertarInicio(10); //modo de uso "->"

    // Crear la lista en el Stack, solo persiste en el ambito {}
    Lista lista;

    lista.insertarInicio(10); //modo de uso "."
    lista.insertarInicio(20);
    lista.insertarInicio(-50);
    lista.insertarInicio(-45);

 //-45->-50->20->10

    //lista.insertarFinal(30);
    //lista.insertarFinal(40);

    lista.imprimir();

    lista.retirarDeInicio();

    lista.imprimir();

    //lista.eliminar(20);
    //lista.imprimir();
/*
    Nodo* encontrado = lista.buscar(30);
    if (encontrado)
        cout << "Encontrado: " << encontrado->dato << endl;
    else
        cout << "No encontrado\n";
*/

    return 0;
}
