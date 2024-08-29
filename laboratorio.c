#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaDoble/ListaDoble.h"  // Asegúrate de que este archivo incluya las declaraciones necesarias


int main() {
    srand(time(0));

    ListaDoble listaComentarios;
    InicializarListaDoble(&listaComentarios);

    // Generar 100 comentarios aleatorios
    for (int i = 0; i < 100; i++) {
        Blog *nuevoBlog = (Blog *)malloc(sizeof(Blog));
        generarBlogAleatorio(nuevoBlog);

        int metodoInsercion = rand() % 2;
        if (metodoInsercion == 0) {
            PushFront(&listaComentarios, nuevoBlog);
        } else {
            PushBack(&listaComentarios, nuevoBlog);
        }
    }

    // Imprimir la lista original de comentarios
    printf("\nComentarios Original:\n");
    ImprimirLista(&listaComentarios, imprimirComentario);

    // Crear y llenar la lista ordenada por longitud
    ListaDoble listaLongitud;
    InicializarListaDoble(&listaLongitud);
    Nodo *temp = listaComentarios.Head;
    while (temp != NULL) {
        Blog *nuevoBlog = (Blog *)malloc(sizeof(Blog));
        strcpy(nuevoBlog->usuario, temp->data->usuario);
        strcpy(nuevoBlog->comentario, temp->data->comentario);
        OrdenadoPorLongitud(&listaLongitud, nuevoBlog);
        temp = temp->next;
    }

    // Crear y llenar la lista con comentarios de 20 letras o menos
    ListaDoble listaCortos;
    InicializarListaDoble(&listaCortos);
    ListaMenoresA20Letras(&listaComentarios, &listaCortos);

    // Imprimir la lista ordenada por longitud
    printf("\nLista de comentarios ordenada por longitud:\n");
    ImprimirLista(&listaLongitud, imprimirComentario);

    // Imprimir la lista de comentarios con 20 letras o menos
    printf("\nLista de comentarios con 20 letras o menos:\n");
    ImprimirLista(&listaCortos, imprimirComentario);

    // Imprimir la lista de comentarios al revés
    printf("\nLista de comentarios al revés:\n");
    ImprimirAlrevez(&listaComentarios, imprimirComentario);

    // Liberar la memoria de todas las listas
    LiberarLista(&listaComentarios);
    LiberarLista(&listaLongitud);
    LiberarLista(&listaCortos);

    return 0;
}

