#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ListaDoble/ListaDoble.h"

void ImprimirNumeros(void *dato){
    printf("%c", *(char *)dato);
}
void imprimirComentario(void *data){
    Blog *blog = (Blog*)data;
    printf("\nUsuario: %s\n", blog->usuario);
    printf("Comentario: %s\n", blog->comentario);
   
}


int main() {
    srand(time(0));

    ListaDoble listaComentarios;
    InicializarListaDoble(&listaComentarios);

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
    printf("\nComentarios Original:\n");
    ImprimirLista(listaComentarios, imprimirComentario);

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

    ListaDoble listaCortos;
    InicializarListaDoble(&listaCortos);
    ListaMenoresA20Letras(&listaComentarios, &listaCortos);

    printf("\nLista de comentarios ordenada por longitud:\n");
    ImprimirLista(listaLongitud, imprimirComentario);

    printf("\nLista de comentarios con 20 letras o menos:\n");
    ImprimirLista(listaCortos, imprimirComentario);

    printf("\nLista de comentarios alrevez");
    ImprimirAlrevez(listaComentarios, imprimirComentario);


    LiberarLista(&listaComentarios);
    LiberarLista(&listaLongitud);
    LiberarLista(&listaCortos);

    return 0;
}