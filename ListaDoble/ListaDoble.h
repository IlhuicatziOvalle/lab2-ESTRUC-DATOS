
typedef struct _BLOG{
    char usuario[30];
    char comentario[255]; 
}Blog;

typedef struct _NodoDoble{
    Blog *data;
    struct _NodoDoble *next;
    struct _NodoDoble *prev;
}NodoDoble;

typedef struct _ListaDoble{
    NodoDoble *Head;
    NodoDoble *Tail;
    NodoDoble *Curr;
    int size;
} ListaDoble;




void InicializarListaDoble(ListaDoble *lista);
void PushFront(ListaDoble *lista, Blog *dato);
void PushBack(ListaDoble *lista, Blog *dato);
NodoDoble *GetNodoPos(ListaDoble *lista, int pos);
void PushPos(ListaDoble *lista, Blog *dato, int pos);
int BorrarPos(ListaDoble *lista, int pos);
void ImprimirLista(ListaDoble *lista, void (*func)(void *));
void LiberarLista(ListaDoble *lista);


void imprimirComentario(void *data);
void ImprimirAlrevez(ListaDoble *lista, void (*func)(void *));
void generarComentarioAleatoria(char *cadena, int longitud);
void generarBlogAleatorio(Blog *blog);
void OrdenadoPorLongitud(ListaDoble *listaOrdenada, Blog *nuevoBlog);
void ListaMenoresA20Letras(ListaDoble *listaOriginal, ListaDoble *listaFiltrada);
void EliminarComentariosLargos(ListaDoble *lista);