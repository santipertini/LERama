#include <stdio.h>

typedef struct {
    char nombre[50];
    int puntos;
    int categoria;
} Jugador;

Jugador crearPateador();
Jugador crearArquero();
void comprobacion(Jugador p, Jugador a, int numero);

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
    }
    
    return arco;
}
