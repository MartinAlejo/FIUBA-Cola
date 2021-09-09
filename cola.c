#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *proximo;
} nodo_t;

nodo_t *crear_nodo(void *elem) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return NULL;
    }
    nodo->dato = elem;
    nodo->proximo = NULL;
    return nodo;
}

struct cola {
    nodo_t *primero;
    nodo_t *ultimo;
};

cola_t *cola_crear(void) {
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola) {
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->primero == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo_aux = crear_nodo(valor);
    if (!nodo_aux) {
        return false;
    }

    if (cola_esta_vacia(cola)) {
        cola->primero = nodo_aux;
    }
    else {
        cola->ultimo->proximo = nodo_aux;
    }

    cola->ultimo = nodo_aux;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    return cola_esta_vacia(cola) ? NULL : cola->primero->dato;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    nodo_t *primer_nodo = cola->primero;
    void *dato_primero = primer_nodo->dato;
    cola->primero = cola->primero->proximo;
    if (!cola->primero) {
        cola->ultimo = NULL;
    }
    free(primer_nodo);
    return dato_primero;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    while (!cola_esta_vacia(cola)) {
        if (destruir_dato == NULL) {
            cola_desencolar(cola);
            continue;
        }
        void *dato = cola_desencolar(cola);
        destruir_dato(dato);
    }
    free(cola);
    return;
}