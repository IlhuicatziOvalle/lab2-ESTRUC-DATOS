
typedef struct _BLOG{
    char usuario[30];
    char comentario[255]; 
}Blog;

typedef struct _Nodo{
    Blog *data;
    struct _Nodo *next;
    struct _Nodo *prev;
}Nodo;

typedef struct _lista{
    Nodo *Head;
    Nodo *Tail;
    Nodo *Curr;
    int size;
} ListaDoble;



void InicializarListaDoble(ListaDoble *lista);
void PushFront(ListaDoble *lista, void *dato);
void PushBack(ListaDoble *lista, void *dato);
Nodo *GetNodoPos(ListaDoble *lista, int pos);
void PushPos(ListaDoble *lista,void *dato, int pos);

void ImprimirLista(ListaDoble *lista, void (*func)(void *));

void LiberarLista(ListaDoble *lista);

void BorrarNodo(ListaDoble *lista,void *dato);
void generarComentarioAleatoria(char *cadena, int longitud);
void generarBlogAleatorio(Blog *blog);
void OrdenadoPorLongitud(ListaDoble *listaOrdenada, Blog *nuevoBlog);
void ListaMenoresA20Letras(ListaDoble *listaOriginal, ListaDoble *listaFiltrada);

void ImprimirAlrevez(ListaDoble *lista, void (*func)(void *));
void imprimirComentario(void *data);
void OrdenadoPorLongitud(ListaDoble *listaOrdenada, Blog *nuevoBlog);
void ListaMenoresA20Letras(ListaDoble *listaOriginal, ListaDoble *listaFiltrada);

void ImprimirAlrevez(ListaDoble lista,void (*func)(void *));

