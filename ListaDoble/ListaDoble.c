#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ListaDoble.h"


void InicializarListaDoble(ListaDoble *lista) {
    lista->Head = NULL;
    lista->Tail = NULL;
    lista->Curr = NULL;
    lista->size = 0;
}

void PushFront(ListaDoble *lista, Blog *dato) {
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->data = dato;
    nuevo->next = lista->Head;
    nuevo->prev = NULL;

    if (lista->Head != NULL) {
        lista->Head->prev = nuevo;
    }
    lista->Head = nuevo;

    if (lista->Tail == NULL) {
        lista->Tail = nuevo;
    }
    lista->size++;
}

void PushBack(ListaDoble *lista, Blog *dato) {
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->data = dato;
    nuevo->next = NULL;
    nuevo->prev = lista->Tail;

    if (lista->Tail != NULL) {
        lista->Tail->next = nuevo;
    }
    lista->Tail = nuevo;

    if (lista->Head == NULL) {
        lista->Head = nuevo;
    }
    lista->size++;
}

NodoDoble *GetNodoPos(ListaDoble *lista, int pos) {
    NodoDoble *temp = lista->Head;
    for (int i = 0; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }
    return temp;
}

void PushPos(ListaDoble *lista, Blog *dato, int pos) {
    if (pos == 0) {
        PushFront(lista, dato);
        return;
    }
    if (pos == lista->size) {
        PushBack(lista, dato);
        return;
    }

    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->data = dato;

    NodoDoble *curr = GetNodoPos(lista, pos);
    if (curr != NULL) {
        nuevo->next = curr;
        nuevo->prev = curr->prev;
        if (curr->prev != NULL) {
            curr->prev->next = nuevo;
        }
        curr->prev = nuevo;
        if (pos == 0) {
            lista->Head = nuevo;
        }
    }
    lista->size++;
}

int BorrarPos(ListaDoble *lista, int pos) {
    if (pos < 0 || pos >= lista->size) return -1;

    NodoDoble *temp = lista->Head;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        lista->Head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        lista->Tail = temp->prev;
    }

    free(temp->data);
    free(temp);
    lista->size--;
    return 0;
}

void ImprimirLista(ListaDoble *lista, void (*func)(void *)) {
    NodoDoble *actual = lista->Head;
    while (actual != NULL) {
        func(actual->data);
        actual = actual->next;
    }
}

void LiberarLista(ListaDoble *lista) {
    NodoDoble *temp;
    while (lista->Head != NULL) {
        temp = lista->Head;
        lista->Head = lista->Head->next;
        free(temp->data);  // Asegúrate de que data sea liberado si se aloca dinámicamente
        free(temp);
    }
    lista->Tail = NULL;
    lista->size = 0;
}
void imprimirComentario(void *data) {
    Blog *blog = (Blog *)data;
    printf("Usuario: %s, Comentario: %s\n", blog->usuario, blog->comentario);
}

void ImprimirAlrevez(ListaDoble *lista, void (*func)(void *)) {
    lista->Curr = lista->Tail;
    while (lista->Curr != NULL) {
        func(lista->Curr->data);
        lista->Curr = lista->Curr->prev;
    }
}
void generarComentarioAleatoria(char *cadena, int longitud) {
    static const char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < longitud - 1; ++i) {
        cadena[i] = alfabeto[rand() % (sizeof(alfabeto) - 1)];
    }
    cadena[longitud - 1] = '\0';
}

void generarBlogAleatorio(Blog *blog) {
    generarComentarioAleatoria(blog->usuario, 3 + rand() % 10);  // Nombre de usuario de entre 3 y 14 letras
    generarComentarioAleatoria(blog->comentario, 10 + rand() % 100);  // Comentario de entre 10 y 99 letras
}
void OrdenadoPorLongitud(ListaDoble *listaOrdenada, Blog *nuevoBlog) {
    NodoDoble *nuevoNodo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevoNodo->data = nuevoBlog;
    NodoDoble *temp = listaOrdenada->Head;
    NodoDoble *prev = NULL;

    while (temp != NULL && strlen(temp->data->comentario) <= strlen(nuevoBlog->comentario)) {
        prev = temp;
        temp = temp->next;
    }

    if (prev != NULL) {
        prev->next = nuevoNodo;
        nuevoNodo->prev = prev;
    } else {
        listaOrdenada->Head = nuevoNodo;
        nuevoNodo->prev = NULL;
    }

    nuevoNodo->next = temp;
    if (temp != NULL) {
        temp->prev = nuevoNodo;
    } else {
        listaOrdenada->Tail = nuevoNodo;
    }

    listaOrdenada->size++;
}
void ListaMenoresA20Letras(ListaDoble *listaOriginal, ListaDoble *listaFiltrada) {
    NodoDoble *temp = listaOriginal->Head;
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
void EliminarComentariosLargos(ListaDoble *lista) {
    NodoDoble *actual = lista->Head;
    NodoDoble *siguiente;

    while (actual != NULL) {
        siguiente = actual->next;  // Guarda el siguiente nodo para continuar el recorrido después de eliminar el nodo actual

        if (strlen(actual->data->usuario) > 3) {
            // Elimina el nodo actual de la lista
            if (actual->prev != NULL) {
                actual->prev->next = actual->next;
            } else {
                lista->Head = actual->next;
            }

            if (actual->next != NULL) {
                actual->next->prev = actual->prev;
            } else {
                lista->Tail = actual->prev;
            }

            free(actual->data);  // Libera la memoria del dato asociado al nodo
            free(actual);        // Libera la memoria del nodo
            lista->size--;
        }

        actual = siguiente;  // Continúa con el siguiente nodo
    }
}