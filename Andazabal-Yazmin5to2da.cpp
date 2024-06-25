#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15  // tamaño del tablero (15x15)

// funcion para inicializar el tablero con 'x', y colocar aleatoriamente pozos (O) y comodines (C)
void inicializar_tablero(char tablero[][SIZE]) {
    int i, j;
    // Inicializar el tablero con 'x'
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            tablero[i][j] = 'x';
        }
    }
    // posiciones aleatorias para los pozos (O)
    srand(time(NULL));
    int count_pozos = 0;
    while (count_pozos < 2) {
        int fila = rand() % SIZE;
        int columna = rand() % SIZE;
        if (tablero[fila][columna] == 'x') {
            tablero[fila][columna] = 'O';
            count_pozos++;
        }
    }
    //  posiciones aleatorias para los comodines (C)
    int count_comodines = 0;
    while (count_comodines < 2) {
        int fila = rand() % SIZE;
        int columna = rand() % SIZE;
        if (tablero[fila][columna] == 'x') {
            tablero[fila][columna] = 'C';
            count_comodines++;
        }
    }
}

// la funcion para imprimir el tablero actualizado con las posiciones de los jugadores
void imprimir_tablero(char tablero[][SIZE], int fila_tortuga, int col_tortuga, int fila_liebre, int col_liebre) {
    int i, j;
    // creo para imprimir el tablero con las posiciones de la tortuga (T) y la liebre (L)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i == fila_tortuga && j == col_tortuga) {
                printf(" T ");
            } else if (i == fila_liebre && j == col_liebre) {
                printf(" L ");
            } else {
                printf(" %c ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

// funcionn para simular el turno de la tortuga
void turno_tortuga(int dado, char tablero[][SIZE], int *fila_tortuga, int *col_tortuga, int *pozos_atravesados, int *comodines_atravesados) {
    int avance = dado;
    // se mueve la tortuga en el tablero
    while (avance > 0) {
        if (*fila_tortuga == SIZE - 1) {  // si llega al borde superior, se gana el juego
            printf("¡La tortuga ha llegado a la meta!\n");
            return;
        }
        (*fila_tortuga)++;
        avance--;
        //  si cae en un pozo
        if (tablero[*fila_tortuga][*col_tortuga] == 'O') {
            printf("La tortuga cayo en un pozo. Juego terminado.\n");
            return;
        }
        //  si encuentra un comodín
        if (tablero[*fila_tortuga][*col_tortuga] == 'C') {
            (*comodines_atravesados)++;
            avance = avance * 2;  //  avance por el comodin
        }
        tablero[*fila_tortuga][*col_tortuga] = 'T';  // elijo la posicion de la tortuga en el tablero
    }
}

// funcion para simular el turno de la liebre
void turno_liebre(int dado, char tablero[][SIZE], int *fila_liebre, int *col_liebre, int *pozos_atravesados, int *comodines_atravesados) {
    int avance = dado * 2;  // Avance doble de la liebre
    // se mueve la liebre en el tablero
    while (avance > 0) {
        if (*fila_liebre == SIZE - 1) {  // si llega al borde superior, ganaa el juego
            printf("¡La liebre ha llegado a la meta!\n");
            return;
        }
        (*fila_liebre)++;
        avance--;
        // verifica si cae en un pozo
        if (tablero[*fila_liebre][*col_liebre] == 'O') {
            printf("La liebre cayo en un pozo. Juego terminado.\n");
            return;
        }
        // verifica si encuentra un comodin
        if (tablero[*fila_liebre][*col_liebre] == 'C') {
            (*comodines_atravesados)++;
            avance = 1;  // avanza solo un casillero por el comodin
        }
        tablero[*fila_liebre][*col_liebre] = 'L';  // Marcar la posicion de la liebre en el tablero
    }
}

int main() {
    char tablero[SIZE][SIZE];
    int fila_tortuga = 0, col_tortuga = 0;
    int fila_liebre = 0, col_liebre = 0;
    int dados[2];
    int equipo_actual = 1;  // 1 para tortuga, 2 para liebre
    int pozos_tortuga = 0, comodines_tortuga = 0;
    int pozos_liebre = 0, comodines_liebre = 0;
    char continuar;
    
    // indico el tablero y coloco pozos (O) y comodines (C)
    inicializar_tablero(tablero);
    
    do {
        printf("Turno del equipo %c\n", (equipo_actual == 1) ? 'T' : 'L');
        printf("Presiona Enter para lanzar el dado...\n");
        getchar();  // Esperar a que el usuario presione Enter
        
        // lanzo el dado para ambos equipos
        dados[0] = rand() % 6 + 1;  //  tortuga
        dados[1] = rand() % 6 + 1;  // liebre
        
        printf("Equipo T (tortuga) avanza %d casillas.\n", dados[0]);
        turno_tortuga(dados[0], tablero, &fila_tortuga, &col_tortuga, &pozos_tortuga, &comodines_tortuga);
        printf("\n");
        
        printf("Equipo L (liebre) avanza %d casillas.\n", dados[1]);
        turno_liebre(dados[1], tablero, &fila_liebre, &col_liebre, &pozos_liebre, &comodines_liebre);
        printf("\n");
        
        //  el tablero actualizado después de cada turno
        imprimir_tablero(tablero, fila_tortuga, col_tortuga, fila_liebre, col_liebre);
        
        // cambiar de equipo para el siguiente turno
        equipo_actual = (equipo_actual == 1) ? 2 : 1;
        
        printf("Presiona 'q' y Enter para terminar el juego, o Enter para continuar...\n");
        scanf(" %c", &continuar);
    } while (continuar != 'q');
    
    // mostra el equipo ganador y mostra resultados
    if (fila_tortuga == SIZE - 1) {
        printf("¡El equipo T (tortuga) ha ganado el juego!\n");
    } else if (fila_liebre == SIZE - 1) {
        printf("¡El equipo L (liebre) ha ganado el juego!\n");
    } else {
        printf("Juego terminado.\n");
    }
    
    // mostra cantidad de pozos y comodines atravesados por cada equipo
    printf("Cantidad de pozos atravesados por la tortuga: %d\n", pozos_tortuga);
    printf("Cantidad de comodines atravesados por la tortuga: %d\n", comodines_tortuga);
    printf("Cantidad de pozos atravesados por la liebre: %d\n", pozos_liebre);
    printf("Cantidad de comodines atravesados por la liebre: %d\n", comodines_liebre);
    
    return 0;
}

