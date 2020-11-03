#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct nodo {
 int id, hash;
 struct nodo *izq, *der;
} Nodo;

void desbalancear(Nodo **pa, Nodo **pult){
    if (*pa == NULL){
        *pult = NULL;
        return;
    }
    Nodo *aux = *pa;
    if ((aux->izq == NULL)&&(aux->der == NULL)){
        *pult = aux;
    }
    if(!(aux->izq == NULL)){ // IZQUIERDA
        desbalancear(&aux->izq, pult);
        *pa = aux->izq;
        (*pult)->der = aux;
        *pult = aux;
        (*pult)->izq = NULL;
    }
    if(!(aux->der == NULL)){ // DERECHA
        desbalancear(&aux->der, pult);
        aux->izq = NULL;
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    if  (a == NULL){
        *pult = NULL;
        return a;
    }
    int i = 0;
    Nodo *resultado = malloc(sizeof(Nodo));
    resultado->id = a->id;
    resultado->hash = a->hash;
    resultado->der = NULL;
    resultado->izq = NULL;
    Nodo *aux = resultado;
    if ((a->izq == NULL)&&(a->der == NULL)){
        resultado->id = a->id;
        resultado->hash = a->hash;
        *pult = resultado;
    }
    if(!(a->izq == NULL)){ // IZQUIERDA
        i++;
        resultado->izq = desbalanceado(a->izq, pult);
        resultado = resultado->izq;
        (*pult)->der = aux;
        *pult = aux;
        (*pult)->izq = NULL;
    }
    if(!(a->der == NULL)){ // DERECHA
	if (i){
            (*pult)->der = desbalanceado(a->der, pult);
	} else {
	    resultado->der = desbalanceado(a->der, pult);
	}
    }
    return resultado;
}

static Nodo nu= { 'u', 0, NULL, NULL };
static Nodo ns= { 's', 0, NULL, &nu };
static Nodo nw= { 'w', 0, NULL, NULL };
static Nodo nx= { 'x', 0, &nw, NULL };
static Nodo nv= { 'v', 0, &ns, &nx };
