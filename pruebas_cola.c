#include "cola.h"
#include "testing.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void _destruir_arreglo_punteros_enteros(void **arreglo) {
    for (int i = 0; i < 2; i++) {
        free(arreglo[i]);
    }
    free(arreglo);
}

void destruir_arreglo_punteros_enteros(void *arreglo) {
    _destruir_arreglo_punteros_enteros((void **)arreglo);
}

void prueba_crear_cola(void) {
    cola_t *cola = cola_crear();
    print_test("Se creo una cola vacia", cola_ver_primero(cola) == NULL);
    // Libero la memoria utilizada en la prueba
    free(cola);
}

void prueba_destruir_cola(void) {
    cola_t *cola = cola_crear();
    int elem = 5;
    cola_encolar(cola, &elem);
    cola_destruir(cola, NULL);
    print_test("Se destruyo una cola sin destruir sus elementos", elem == 5);
    // Se elimino la memoria utilizada en la prueba
}

void prueba_destruir_cola_y_elementos_free(void) {
    cola_t *cola = cola_crear();
    int *elem_1 = malloc(sizeof(int));
    *elem_1 = 3;
    int *elem_2 = malloc(sizeof(int));
    *elem_2 = 5;
    cola_encolar(cola, elem_1);
    cola_encolar(cola, elem_2);
    cola_destruir(cola, free);
    // Si realizo un 'printf' puedo verificar que lo que contienen ambas variables ahora es basura
    // printf("Elemento 1: %d, Elemento 2: %d\n", *elem_1, *elem_2);
    print_test("Se destruyo una cola y sus elementos", 1);
    // Se elimino la memoria utilizada en la prueba
}

void prueba_destruir_cola_y_arreglo(void) {
    cola_t *cola = cola_crear();
    void **arreglo = calloc(2, sizeof(void*));
    int *elem_1 = malloc(sizeof(int));
    *elem_1 = 3;
    int *elem_2 = malloc(sizeof(int));
    *elem_2 = 5;
    arreglo[0] = elem_1;
    arreglo[1] = elem_2;
    cola_encolar(cola, arreglo);
    cola_destruir(cola, destruir_arreglo_punteros_enteros);
    // Si realizo un 'printf' puedo verificar que lo que contienen ambas variables ahora es basura
    // printf("Elemento 1: %d, Elemento 2: %d\n", *elem_1, *elem_2);
    print_test("Se destruyo una cola y la pila que se habia encolado", 1);
    // Se elimino la memoria utilizada en la prueba
}

void prueba_encolar_y_desencolar(void) {
    cola_t *cola = cola_crear();
    int *elem_1 = malloc(sizeof(int));
    *elem_1 = 3;
    cola_encolar(cola, elem_1);
    print_test("Se encolo y desencolo un elemento", cola_desencolar(cola) == elem_1);
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
    free(elem_1);
}

void prueba_encolar_muchos(void) {
    cola_t *cola = cola_crear();
    int *arr = calloc(1000, sizeof(int));
    int cont_desenc = 0;
    int primero_correcto = 1;
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
        cola_encolar(cola, &arr[i]);
    }

    while (!cola_esta_vacia(cola)) {
        int *elem_prim = cola_ver_primero(cola);
        int *elem_des = cola_desencolar(cola);
        if (elem_prim != elem_des) {
            primero_correcto = 0;
        }
        cont_desenc++;
    }
    print_test("Se encolaron y desencolaron 1000 elementos", cont_desenc == 1000 && primero_correcto);
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
    free(arr);
}

void prueba_encolar_null(void) {
    cola_t *cola = cola_crear();
    int cont_desenc = 0;
    for (int i = 0; i < 5; i++) {
        cola_encolar(cola, NULL);
    }

    while(!cola_esta_vacia(cola)) {
        cola_desencolar(cola);
        cont_desenc++;
    }
    print_test("Se encolo y desencolo NULL", cont_desenc == 5);
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
}

void prueba_desencolar_vacia(void) {
    cola_t *cola = cola_crear();
    print_test("Desencolar una cola vacia devuelve NULL", cola_desencolar(cola) == NULL);
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
}

void prueba_ver_primero_vacia(void) {
    cola_t *cola = cola_crear();
    print_test("Ver primero en una cola vacia devuelve NULL", cola_ver_primero(cola) == NULL);
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
}

void prueba_esta_vacia(void) {
    cola_t *cola = cola_crear();
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);
}

void prueba_desencolar_y_ver_primero_cola_encolada(void) {
    cola_t *cola = cola_crear();
    int *elem_1 = malloc(sizeof(int));
    char *elem_2 = malloc(sizeof(char));
    float *elem_3 = malloc(sizeof(float));
    cola_encolar(cola, elem_1);
    cola_encolar(cola, elem_2);
    cola_encolar(cola, elem_3);

    while (!cola_esta_vacia(cola)) {
        free(cola_desencolar(cola));
    }

    print_test("No se puede desencolar ni ver primero en una cola que vacio", cola_esta_vacia(cola) && !cola_ver_primero(cola) && !cola_desencolar(cola));
    // Libero la memoria utilizada en la prueba
    cola_destruir(cola, NULL);   
}

void pruebas_cola_estudiante(void) {
    prueba_crear_cola();
    prueba_destruir_cola();
    prueba_destruir_cola_y_elementos_free();
    prueba_destruir_cola_y_arreglo();
    prueba_encolar_y_desencolar();
    prueba_encolar_muchos();
    prueba_encolar_null();
    prueba_desencolar_vacia();
    prueba_ver_primero_vacia();
    prueba_esta_vacia();
    prueba_desencolar_y_ver_primero_cola_encolada();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;
}

#endif