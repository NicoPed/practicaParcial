#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//TP5
#define MAX 150

typedef struct Tarea
{
    
    int TareaID;
    char *Descripcion;
    int Duracion;

}sTAREA;

typedef struct sNodo{
    sTAREA T;
    struct sNodo* Siguiente;
}sNodo;

sNodo* crearListaVacio();
sNodo* crearNodo(sTAREA t);
sTAREA crearTarea(int id, char* descripcion, int duracion);

void insertarNodo(sNodo** cabecera,sNodo* nuevoNodo);
void insertarNodoAlFinal(sNodo ** cabecera, sNodo * nuevoNodo);
void insertarEnUnaPosiconDada(sNodo ** cabecera, sNodo* nuevoNodo,int posicion);

void mostrarTodasLasTareas(sNodo* t);
void mostrarTarea(sTAREA t);


sNodo* BuscarTareaID(sNodo * lista,int id);
sNodo* BuscarTareaClave(sNodo * lista, char clave[]);
sNodo* buscarPorPocicion(sNodo * lista, int posicionBuscada);

void Eliminar(sNodo ** t, int id);
sNodo* quitarNodo(sNodo** lista, int id);
sNodo* quitarUltimo(sNodo ** cabecera);

void liberarMemoria(sNodo * lista);
void eliminarNodo(sNodo * nodo);

void mostrarDatos(sNodo* lista);
int cantidadTareas(sNodo* lista);
int sacarTiempoAsociado(sNodo *lista);

sNodo* copiarNodo(sNodo* nodoACopiar);
sNodo* copiarNodoPuntero(sNodo* nodoAcopiar);

void ordenarPorId(sNodo ** lista);

int main (){
    char buffer[MAX],*clave;
    int cantTareas,duracion,respuesta,id = 0, opcionCase2,idAux,opcionLista, posicion;
    sTAREA nuevaTarea;
    sNodo* nodoAux;
    sNodo* tareasRealizadas,* tareaPendientes,*tareasEnProceso; 
    sNodo* busqueda; 
    tareasRealizadas = crearListaVacio();
    tareaPendientes = crearListaVacio();
    tareasEnProceso = crearListaVacio();
    do
    {
        printf("\n1- Agregar una tarea pendiente: ");
        printf("\n2- Ver y Marcar como realizadas las tareas pendientes: ");
        printf("\n3- Mostrar Tareas Pendientes");
        printf("\n4- Mostrar Tareas En proceso");
        printf("\n5- Mostrar Tareas Realizadas");
        printf("\n6- Copiar Tarea");
        printf("\n7- Ordenar por id: ");
        //printf("\n6- Buscar por ID");
        //printf("\n7- Buscar por clave");
        //printf("\n8- Mostrar Datos de una lista");
        //printf("\n9- Insertar en una posicion dada: ");
        //printf("\n9- Quitar ultima Tarea: ");
        //printf("\n9- Agregar una tarea al final");
        //printf("\n9-Eliminar por id (solo prueba): ");
        printf("\n10- Salir");
        fflush(stdin);
        printf("\nIngrese una opcion: ");
        scanf("%d",&respuesta);
        
        switch (respuesta)
        {
        case 1 :

            printf("\n==========================");
            printf("\nIngrese una descripción para la tarea: ");
            fflush(stdin);
            gets(buffer);
            printf("\nIngrese una duracion(en minutos): ");
            fflush(stdin);
            scanf("%d",&duracion);
            printf("\n==========================");
            nuevaTarea = crearTarea(id,buffer,duracion);
            nodoAux= crearNodo(nuevaTarea);
            insertarNodo(&tareaPendientes,nodoAux);
            free(nuevaTarea.Descripcion);
            id ++;
            break;
        case 2 :
            do
            {
                printf("\n=== Tareas Pendienetes ===");
                mostrarTodasLasTareas(tareaPendientes);
                printf("\n==========================");
                printf("\n=== Tareas En Proceso ===");
                mostrarTodasLasTareas(tareasEnProceso);
                printf("\n==========================");
                printf("\n=== Tareas Realizadas ===");
                mostrarTodasLasTareas(tareasRealizadas);
                printf("\n==========================");
                printf("\nIngrese el ID de la tarea a seleccionar: ");
                scanf("%d",&idAux);
                printf("\nQue desea hacer: ");
                
                do
                {
                printf("\n1- Mover a Tareas Pendientes");
                printf("\n2- Mover a Tareas En Proceso");
                printf("\n3- Mover a Tareas Realizadas");
                printf("\n4- Eliminar Tarea");
                printf("\n5- Salir");
                printf("\nSeleccione una opcion: ");
                scanf("%d", &opcionCase2 );
                busqueda = BuscarTareaID(tareaPendientes,idAux);
                if (busqueda == NULL)
                {
                    busqueda = BuscarTareaID(tareasRealizadas,idAux);
                    if (busqueda == NULL)
                    {
                        busqueda = BuscarTareaID(tareasEnProceso,idAux);
                        if (busqueda == NULL)
                        {
                            printf("\nERROR 404 la tarea no existe.\n");
                            opcionCase2 = 5;
                        }
                        else
                        {
                            nodoAux = quitarNodo(&tareasEnProceso,idAux);
                        }   
                    }
                    else
                    {
                        nodoAux = quitarNodo(&tareasRealizadas,idAux);
                    }
                }
                else
                {
                    nodoAux = quitarNodo(&tareaPendientes,idAux);
                }
                        

                    switch (opcionCase2)
                    {
                    case 1:
                        insertarNodo(&tareaPendientes,nodoAux);
                        printf("==== DATOS TAREAS PENDIENTES ====");
                        mostrarDatos(tareaPendientes);
                        opcionCase2 = 5;
                        break;
                    case 2:
                        insertarNodo(&tareasEnProceso,nodoAux);
                        printf("==== DATOS TAREAS EN PROCESO ====");
                        mostrarDatos(tareasEnProceso);
                        opcionCase2 = 5;
                        break;
                    case 3:
                        insertarNodo(&tareasRealizadas,nodoAux);
                        printf("==== DATOS TAREAS REALIZADAS ====");
                        mostrarDatos(tareasRealizadas);
                        opcionCase2 = 5;
                        break;
                    case 4:
                        eliminarNodo(nodoAux);
                        opcionCase2 = 5;
                        break;
                    case 5: 
                        printf("\n-------------------------------------");
                        break;
                    default:
                        printf("\nIngresee una opcion correcta porfavor");
                        break;
                    }


                } while (opcionCase2 != 5);
                printf("\nDesea modificar otra tarea? 1 = SI; 0 = NO");
                printf("\nIngrese una opcion: ");
                scanf("%d",&opcionCase2);
            } while (opcionCase2 != 0);
            
            break;
        case 3:
            printf("\n=== Tareas Pendienetes ===");
            mostrarTodasLasTareas(tareaPendientes);
            printf("\n==========================");
            break;
        case 4:
            printf("\n=== Tareas En Proceso ===");
            mostrarTodasLasTareas(tareasEnProceso);
            printf("\n==========================");
            break;
        case 5:
            printf("\n=== Tareas Realizadas ===");
            mostrarTodasLasTareas(tareasRealizadas);
            printf("\n==========================");
            break;
        case 6:
            printf("\nIngrese el id: ");
            scanf("%d",&idAux);
            nodoAux = BuscarTareaID(tareaPendientes,idAux);
            if (nodoAux)
            {
                nodoAux = copiarNodo(nodoAux);
                insertarNodo(&tareasEnProceso ,nodoAux);
                //nodoAux = copiarNodoPuntero(nodoAux);
                //insertarNodo(&tareasEnProceso ,nodoAux);
            }
            
            break;
        case 7:
            ordenarPorId(&tareaPendientes);
            break;
        }

        /*if (respuesta == 6 || respuesta == 7)
        {
            if (busqueda != NULL){
                printf("\n=== LA TAREA BUSCADA ES: ===");
                mostrarTarea(busqueda->T);
                printf("\n================");
            }
            else
            {
                printf("\n===NO HUBO RESULTADOS===");
            }
        }
        */
    } while (respuesta != 10);

    liberarMemoria(tareasRealizadas);
    liberarMemoria(tareaPendientes);
    liberarMemoria(tareasEnProceso);
    //free(tareasRealizadas);
    //free(tareaPendientes);
    return 0;
}


void liberarMemoria(sNodo * lista){
    sNodo* aux = lista;
    sNodo* aux2;
    while (aux)
    {
        aux2 = aux;
        aux = aux->Siguiente;
        eliminarNodo(aux2);
    }
}
void eliminarNodo(sNodo * nodo){
    if (nodo != NULL)
    {
    free(nodo->T.Descripcion);
    free(nodo);    
    }
    
}
void Eliminar(sNodo ** Lista, int id){
    if (*Lista != NULL)
    {    
        sNodo* aux, *auxAnterior;
        aux = *Lista;
        auxAnterior = *Lista;

        while (aux && aux->T.TareaID != id)
        {
            auxAnterior = aux;
            aux = aux->Siguiente;
        }
        if (aux == *Lista)
        {
            *Lista = aux->Siguiente;
            free(aux->T.Descripcion);
            free(aux);    
        }else{
            if (aux)
            {
                auxAnterior->Siguiente = aux->Siguiente;
                free(aux->T.Descripcion);
                free(aux);
            }
        }
    }

}
sNodo* quitarPrimero(sNodo ** lista){
    if (*lista)
    {
        sNodo*quitado = (*lista);
        (*lista) = (*lista)->Siguiente;
        quitado->Siguiente = NULL;
        return quitado;    
    }
    return NULL;
}
sNodo* quitarUltimo(sNodo **lista){
    if (*lista)
    {
        sNodo *aux = (*lista);
        sNodo *auxAnterior = (*lista);
        while (aux->Siguiente)
        {   
            auxAnterior = aux;
            aux= aux->Siguiente;
        }
        if (aux == (*lista))
        {
            (*lista) = (*lista)->Siguiente;
        }
        else{
            auxAnterior->Siguiente = aux->Siguiente;
        }
        return aux;
    }
    return NULL;
}
sNodo* quitarNodo(sNodo** lista, int id){
    sNodo * aux;
    sNodo * auxAnterior;
    aux = *lista;
    auxAnterior = *lista;
    while (aux && aux->T.TareaID != id)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }
    if (aux)
    {
        if (aux = *lista)
        {
            *lista = aux->Siguiente;
            aux->Siguiente = NULL;
            return aux;
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
            aux->Siguiente = NULL;
            return aux;
        }
        
    }
    
}

sTAREA crearTarea(int id, char* descripcion, int duracion){
    sTAREA t;
    t.Descripcion = (char *) malloc(sizeof(char)* strlen(descripcion) + 1);
    strcpy(t.Descripcion,descripcion);
    t.TareaID = id;
    t.Duracion = duracion;
    return t;
}

void mostrarTodasLasTareas(sNodo* t){
    sNodo* aux = t;
    while (aux != NULL)
    {
        printf("\n---------------------");
        mostrarTarea(aux->T);
        printf("\n---------------------");
        aux = aux->Siguiente;
    }
    
}
void mostrarTarea(sTAREA t){

    printf("\nID : %d", t.TareaID);
    printf("\nDescripción: ");
    puts(t.Descripcion);
    printf("Duracion: %d",t.Duracion);

}
void mostrarDatos(sNodo* lista){
    int cantTareas = cantidadTareas(lista);
    int tiempoAsociado = sacarTiempoAsociado(lista);
    printf("\n=============================");
    printf("\nLa cantidad de tareas son: %d",cantTareas);
    printf("\nEl tiempo Asociado es: %d",tiempoAsociado);
    printf("\n=============================");

}
int cantidadTareas(sNodo* lista){
    if (lista == NULL)
    {
        return 0;
    }else
    {
        return(1 + cantidadTareas(lista->Siguiente));
    }  
}
int sacarTiempoAsociado(sNodo *lista){
    if (lista == NULL)
    {
        return 0;
    }else
    {
        return(lista->T.Duracion + sacarTiempoAsociado(lista->Siguiente));
    }  
}

sNodo* BuscarTareaClave(sNodo * lista, char clave[]){
    // HACER QUE SOLO RECIBA UNA LISTA Y LO BUSQUE DE AHI RECIEN EN EL PROGRAMA
    //PRINCIPAL HACES EL TRAMUYO DE SI ESTABA O NO
    sNodo* aux = lista;
    while (aux && strstr(aux->T.Descripcion, clave) == NULL)
    {
        aux =aux->Siguiente;
    }
    return aux;
}
sNodo* BuscarTareaID(sNodo * tareas, int id){

        sNodo* aux = tareas;
        while (aux != NULL && aux->T.TareaID != id)
        {
            aux = aux->Siguiente;
        }
        return aux;

}
sNodo* buscarPorPocicion(sNodo * lista, int posicionBuscada){
    sNodo* aux = lista;
    int cont= 0;
    while (aux && cont != posicionBuscada)
    {
        aux = aux->Siguiente;
        cont ++;
    }
    return aux;
    
}

sNodo* crearNodo(sTAREA t){
    sNodo* nuevoNodo= (sNodo *) malloc(sizeof(sNodo));
    nuevoNodo->T.Descripcion = (char *) malloc(sizeof(char) * strlen(t.Descripcion) + 1);
    strcpy(nuevoNodo->T.Descripcion, t.Descripcion);
    nuevoNodo->T.Duracion = t.Duracion;
    nuevoNodo->T.TareaID = t.TareaID;
    return nuevoNodo;
}
sNodo* crearListaVacio(){
    return NULL;
}

void insertarNodo(sNodo** cabecera,sNodo* nuevoNodo){
    nuevoNodo->Siguiente = *cabecera;
    *cabecera = nuevoNodo;
}
void insertarNodoAlFinal(sNodo ** cabecera, sNodo * nuevoNodo){
    sNodo *aux;
    aux = *cabecera;
    //auxAnterior = *cabecera;
    
    if (aux == NULL)
    {
        nuevoNodo->Siguiente = *cabecera;
        *cabecera = nuevoNodo;
    }else
    {
        while (aux->Siguiente != NULL)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevoNodo;
        nuevoNodo->Siguiente = NULL;
    }
        
}
void insertarEnUnaPosiconDada(sNodo ** cabecera, sNodo* nuevoNodo, int posicion){
        if (posicion == 0)
        {
            insertarNodo(cabecera,nuevoNodo);
        }
        else
        {
            
            sNodo * aux = (*cabecera);
            sNodo * auxAnterior = (*cabecera);
            
            int cont = 0;
            while (aux && cont != posicion)
            {
                auxAnterior = aux;
                aux = aux->Siguiente;
                cont ++;    
            }
            if (cont == posicion)
            {
                auxAnterior->Siguiente = nuevoNodo;
                //nuevoNodo->Siguiente = aux;
                //aux = nuevoNodo;
                insertarNodo(&aux,nuevoNodo);   
            }
        }
}

sNodo* copiarNodo(sNodo* nodoACopiar){
    if (nodoACopiar)
    {    
        sNodo* nuevoNodo;
        sTAREA nuevaTarea;
        nuevaTarea = crearTarea(nodoACopiar->T.TareaID,nodoACopiar->T.Descripcion,nodoACopiar->T.Duracion);
        nuevoNodo = crearNodo(nuevaTarea);
        //nuevoNodo->Siguiente = NULL;
        return nuevoNodo;
    }
}
//ESTE NO FUNCA IDKWHY
sNodo* copiarNodoPuntero(sNodo* nodoAcopiar){
    if (&nodoAcopiar)
    {    
    sNodo* nuevoNodo;
    nuevoNodo->T.Descripcion = nodoAcopiar->T.Descripcion;
    nuevoNodo->T.TareaID = nodoAcopiar->T.TareaID;
    nuevoNodo->T.Duracion = nodoAcopiar->T.Duracion;
    nuevoNodo->Siguiente = NULL;
    mostrarTarea(nuevoNodo->T);
    return nuevoNodo;
    }
}
//NO FUNCA
void ordenarPorId(sNodo ** lista){
    sNodo *aux = *lista, *auxAnterior = *lista, *auxCambiar;

    while (aux)
    {
        if (auxAnterior->T.TareaID > aux->T.TareaID )
        {
            printf("\n==ENTRA==");
            aux = quitarNodo(lista,aux->T.TareaID);
            aux->Siguiente = NULL;
            insertarNodo(lista,aux);
            aux = *lista;
            auxAnterior = *lista;
        }
        else
        {
            auxAnterior = aux;
            aux = aux->Siguiente;
        }
        
    }
    

}
//==============================================================================================================================0
//==============================================================================================================================0
//==============================================================================================================================0

/*
        case 6:
            printf("\nIngrese el id: ");
            fflush(stdin);
            scanf("%d",&idAux); 
            busqueda = BuscarTareaID(tareaPendientes,idAux);
            if (busqueda == NULL)
            {
                busqueda = BuscarTareaID(tareasRealizadas,idAux);
                if (busqueda == NULL)
                {
                    busqueda = BuscarTareaID(tareasEnProceso,idAux);
                }
            }
            break;
        case 7:
            printf("\nIngrese la clave: ");
            fflush(stdin);
            gets(buffer);
            clave = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
            strcpy(clave,buffer);
            busqueda = BuscarTareaClave(tareaPendientes,clave);        
            if (busqueda == NULL)
            {
                busqueda = BuscarTareaClave(tareasRealizadas,clave);
                if (busqueda == NULL)
                {
                    busqueda = BuscarTareaClave(tareasEnProceso,clave);
                }
            }
            
            break;
        case 8:
            do
            {
            printf("\n1- Tareas Pendientes: ");
            printf("\n2- Tareas Realizadas");
            printf("\n3- Tareas en proceso: ");
            printf("\nIngrese una opción: ");
            scanf("%d",&opcionLista);
            } while (opcionLista != 1 && opcionLista != 2 && opcionLista != 3);
                switch (opcionLista)
                {
                case 1:
                    printf("==== PARA TAREAS PENDIENTES ====");
                    mostrarDatos(tareaPendientes);
                    break;
                case 2:
                    printf("==== PARA TAREAS REALIZADAS ====");
                    mostrarDatos(tareasRealizadas);
                    break;
                case 3:
                    printf("==== PARA TAREAS EN PROCESO ====");
                    mostrarDatos(tareasEnProceso);
                    break;            
                }
            break;
        */
//==============================================================================================================================0
//==============================================================================================================================0
//==============================================================================================================================0

/*case 9:
                nodoAux = quitarUltimo(&tareaPendientes);
                if (nodoAux != NULL)
                {
                    printf("\n=========== LA TAREA QUITADA ES ============");
                    mostrarTarea(nodoAux->T);
                    printf("\n============================================");
                    free(nodoAux->T.Descripcion);
                    free(nodoAux);
                }else
                {
                    printf("\nLa lista esta vacìa picaron");
                }
                break;
                */
           /* case 9:
                printf("\n==========================");
                printf("\nIngrese una descripción para la tarea: ");
                fflush(stdin);
                gets(buffer);
                printf("\nIngrese una duracion(en minutos): ");
                fflush(stdin);
                scanf("%d",&duracion);
                printf("\n==========================");
                nuevaTarea = crearTarea(id,buffer,duracion);
                nodoAux= crearNodo(nuevaTarea);
                insertarNodoAlFinal(&tareaPendientes,nodoAux);
                free(nuevaTarea.Descripcion);
                id ++;
                break;
            */
           /* case 9:
                fflush(stdin);
                printf("\nIngrese el id: ");
                scanf("%d",&idAux);
                Eliminar(&tareaPendientes,idAux);
            break;*/
            /*  case 9: 
            printf("\n==========================");
            printf("\nIngrese una descripción para la tarea: ");
            fflush(stdin);
            gets(buffer);
            printf("\nIngrese una duracion(en minutos): ");
            fflush(stdin);
            scanf("%d",&duracion);
            printf("\n==========================");
            nuevaTarea = crearTarea(id,buffer,duracion);
            nodoAux= crearNodo(nuevaTarea);
            printf("\nIngrese La posicion :");
            scanf("%d",&posicion);
            insertarEnUnaPosiconDada(&tareaPendientes,nodoAux,posicion);
            free(nuevaTarea.Descripcion);
            id ++;
            break;    
        */