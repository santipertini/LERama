#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int fila;
    int columna;
} Coordenada;
typedef struct {
    char nombre[50];
    int puntos;
    int categoria;
} Jugador;

Jugador crearPateador();
Jugador crearArquero();
void comprobacion(Jugador p, Jugador a, int numero);
int** crearArco(int categoria, int puntos);
int patear(int** arco, int categoria);
Coordenada* pistasArquero(int categoria, int** arco, int* numPistas);

int main() {
    printf("Bienvenido al juego de penales\n");
    printf("La suma entre pateador y arquero debe ser 10\n\n");

    printf("=== PAR 1 ===\n");
    Jugador pateador1 = crearPateador();
    Jugador arquero1 = crearArquero();

    printf("\n=== PAR 2 ===\n");
    Jugador pateador2 = crearPateador();
    Jugador arquero2 = crearArquero();

    printf("\n--- RESULTADOS ---\n");
    comprobacion(pateador1, arquero1, 1);
    comprobacion(pateador2, arquero2, 2);

    // Juego para par 1
    int categoria;
    if(pateador1.puntos <= 4) categoria = 1;
    else if(pateador1.puntos == 5) categoria = 2;
    else categoria = 3;

    int** arco = crearArco(categoria, pateador1.puntos);
    int columna = patear(arco, categoria);

    // Obtener pistas
    int numPistas;
    Coordenada* pistas = pistasArquero(categoria, arco, &numPistas);

    printf("Pistas para el arquero:\n");
    for(int i = 0; i < numPistas; i++) {
        printf("Posición no pateada: fila %d, columna %d\n", pistas[i].fila, pistas[i].columna);
    }

    free(pistas);

    // Liberar arco
    for(int i = 0; i < categoria; i++) {
        free(arco[i]);
    }
    free(arco);

    return 0;
}

Jugador crearPateador() {
    Jugador p;
    printf("Ingrese el nombre del pateador: ");
    scanf("%s", p.nombre);
    printf("Ingrese los puntos de habilidad del pateador: ");
    scanf("%d", &p.puntos);
    return p;
}

Jugador crearArquero() {
    Jugador a;
    printf("Ingrese el nombre del arquero: ");
    scanf("%s", a.nombre);
    printf("Ingrese los puntos de habilidad del arquero: ");
    scanf("%d", &a.puntos);
    return a;
}

void comprobacion(Jugador p, Jugador a, int numero) {
    int suma = p.puntos + a.puntos;

    printf("Par %d: %s (P) + %s (A) = %d \n",
           numero, p.nombre, a.nombre, suma);

    if (suma > 10) {
        printf("Error: supera 10\n");
    } else if (suma < 10) {
        printf("Error: menor a 10\n");
    } else {
        printf("Correcto\n");
    }
}

int** crearArco(int categoria, int puntos) {
    int filas;
    
    if(puntos <= 4) {
        categoria = 1;
    } else if(puntos == 5) {  
        categoria = 2;
    } else {  
        categoria = 3;
    }
    
    switch(categoria) {
        case 1:
            filas = 1;
            break;
        case 2:
            filas = 2;
            break;
        case 3:
            filas = 3;
            break;
    }
    int** arco = (int**)malloc(filas * sizeof(int*));
    for(int i = 0; i < filas; i++) {
        arco[i] = (int*)malloc(3 * sizeof(int));
        for(int j = 0; j < 3; j++) {
            arco[i][j] = 0;  // Inicializar con 0 (no pateado)
        }
    }
    
    return arco;
}

int patear(int** arco, int categoria) {
    int columna;
    printf("Ingrese la columna a patear (0, 1, 2): ");
    scanf("%d", &columna);
    
    if(columna < 0 || columna > 2) {
        printf("Columna inválida. Intente de nuevo.\n");
        return patear(arco, categoria);
    }
    
    for(int i = 0; i < categoria; i++) {
        if(arco[i][columna] == 0) {
            printf("¡Gol!\n");
            return columna;
        }
    }
    
    printf("¡Atajado!\n");
    return columna;
}

Coordenada* pistasArquero(int categoria, int** arco, int* numPistas) {
    int filas;
    switch(categoria) {
        case 1: filas = 1; break;
        case 2: filas = 2; break;
        case 3: filas = 3; break;
    }
    
    // Máximo pistas: filas * 3
    Coordenada* pistas = (Coordenada*)malloc((filas * 3) * sizeof(Coordenada));
    int contador = 0;
    
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < 3; j++) {
            if(arco[i][j] == 0) {  // No pateado en TODO el arco
                pistas[contador].fila = i;
                pistas[contador].columna = j;
                contador++;
            }
        }
    }
    
    *numPistas = contador;
    return pistas;
}
