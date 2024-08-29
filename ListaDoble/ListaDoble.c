#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ListaDoble.h"

void InicializarListaDoble(ListaDoble *lista){
    lista->Head=NULL;
    lista->Tail=NULL;
    lista->Curr=NULL;
    lista->size=0;
}
void PushFront(ListaDoble *lista, void *dato){
     Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->data = dato;
    nuevo->next = lista->Head;
    nuevo->prev = NULL;

    if (lista->Head != NULL) {
        lista->Head->prev = nuevo;
    } else {
        lista->Tail = nuevo;
    }

    lista->Head = nuevo;
    lista->size++;
}

void PushBack(ListaDoble *lista, void *dato){
       Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->data = dato;
    nuevo->next = NULL;
    nuevo->prev = lista->Tail;

    if (lista->Tail != NULL) {
        lista->Tail->next = nuevo;
    } else {
        lista->Head = nuevo;
    }

    lista->Tail = nuevo;
    lista->size++;
}

void ImprimirLista(ListaDoble *lista, void (*func)(void *)) {
    Nodo *actual = lista->Head;
    while (actual != NULL) {
        func(actual->data);
        actual = actual->next;
    }
    printf("\n");
}

void imprimirComentario(void *data) {
    Blog *blog = (Blog *)data;
    printf("Usuario: %s, Comentario: %s\n", blog->usuario, blog->comentario);
}

Nodo *GetNodoPos(ListaDoble *lista, int pos){
    Nodo *temp=lista->Head;

    while(temp!=NULL&&pos>0){
        temp=temp->next;
        pos--;
    }
    return temp;
}
void PushPos(ListaDoble *lista,void *dato, int pos){
    if(pos==0){
        PushFront(lista,dato);
        return;
    }
    else if(pos==lista->size){
        PushBack(lista,dato);
        return;
    }
    else{
        Nodo *nuevo=(Nodo *)malloc(sizeof(Nodo));
        nuevo->data=dato;

        Nodo *ant = GetNodoPos(lista,pos -1);
        nuevo->next=ant->next;
        ant->next=nuevo;
    }
    lista->size++;
}


void ImprimirAlrevez(ListaDoble *lista, void (*func)(void *)) {
    lista->Curr = lista->Tail;
    while (lista->Curr != NULL) {
        func(lista->Curr->data);
        lista->Curr = lista->Curr->prev;
    }
}
void LiberarLista(ListaDoble *lista) {
    lista->Curr = lista->Head;
    while (lista->Curr != NULL) {
        Nodo *temp = lista->Curr;
        lista->Curr = lista->Curr->next;

        // Liberar memoria de los datos
        free(temp->data);

        // Liberar el nodo
        free(temp);
    }
}
Nodo *GetNodo(ListaDoble *lista, void *dato){
    lista->Curr=lista->Head;
    while(lista->Curr->data!=dato&&lista->Curr!=NULL){
        lista->Curr=lista->Curr->next;
    }
    return lista->Curr;
}
void BorrarNodo(ListaDoble *lista, void *dato) {
    Nodo *curr = lista->Head;
    Nodo *ant = NULL;

    // Buscar el nodo a eliminar
    while (curr != NULL && curr->data != dato) {
        ant = curr;
        curr = curr->next;
    }

    // Si no se encuentra el nodo, no hay nada que hacer
    if (curr == NULL) {
        return;
    }

    // Si curr es el primer nodo
    if (ant == NULL) {
        lista->Head = curr->next;
    } else {
        ant->next = curr->next;
    }

    // Si curr es el último nodo
    if (curr == lista->Tail) {
        lista->Tail = ant;
    }

    // Liberar memoria de los datos
    free(curr->data);

    // Liberar el nodo
    free(curr);

    // Reducir el tamaño de la lista
    lista->size--;
}

void generarComentarioAleatoria(char *cadena, int longitud) {
    static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < longitud - 1; ++i) {
        cadena[i] = alfabeto[rand() % (sizeof(alfabeto) - 1)];
    }
    cadena[longitud - 1] = '\0';
}

void generarBlogAleatorio(Blog *blog) {
    generarComentarioAleatoria(blog->usuario, 5 + rand() % 10);  // Nombre de usuario de entre 5 y 14 letras
    generarComentarioAleatoria(blog->comentario, 10 + rand() % 100);  // Comentario de entre 10 y 99 letras
}
void OrdenadoPorLongitud(ListaDoble *listaOrdenada, Blog *nuevoBlog) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->data = nuevoBlog;

    Nodo *temp = listaOrdenada->Head;
    while (temp != NULL && strlen(temp->data->comentario) < strlen(nuevoBlog->comentario)) {
        temp = temp->next;
    }

    if (temp == NULL) {
        PushBack(listaOrdenada, nuevoBlog);
    } else if (temp == listaOrdenada->Head) {
        PushFront(listaOrdenada, nuevoBlog);
    } else {
        Nodo *anterior = temp->prev;
        nuevoNodo->next = temp;
        nuevoNodo->prev = anterior;
        anterior->next = nuevoNodo;
        temp->prev = nuevoNodo;
        listaOrdenada->size++;
    }
}

void ListaMenoresA20Letras(ListaDoble *listaOriginal, ListaDoble *listaFiltrada) {
    Nodo *temp = listaOriginal->Head;
    while (temp != NULL) {
        if (strlen(temp->data->comentario) <= 20) {
            Blog *nuevoBlog = (Blog *)malloc(sizeof(Blog));
            strcpy(nuevoBlog->usuario, temp->data->usuario);
            strcpy(nuevoBlog->comentario, temp->data->comentario);
            PushBack(listaFiltrada, nuevoBlog);
        }
        temp = temp->next;
    }
}

/*void EliminarMenor3(ListaDoble *listaOriginal, ListaDoble *listaFiltrada){
    Nodo *temp = listaOriginal->Head;
    while (temp != NULL) {
        if (strlen(temp->data->comentario) <= 3) {
            Blog *nuevoBlog = (Blog *)malloc(sizeof(Blog));
            strcpy(nuevoBlog->usuario, temp->data->usuario);
            strcpy(nuevoBlog->comentario, temp->data->comentario);
            PushBack(listaFiltrada, nuevoBlog);
        }
        temp = temp->next;
    }
}*/
