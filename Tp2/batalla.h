#ifndef __BATALLA_H__
#define __BATALLA_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES 50

typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
} personaje_t;

typedef struct juego {
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];
	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	int cantidad_jugadores;
	char tipo_primer_jugador;
} juego_t;

void mostrar_terreno(juego_t juego);

void inicializar_juego(juego_t* juego);

void posicionar_iniciales(juego_t* juego, personaje_t* personaje);

void posicionar_automaticamente(int* energia, personaje_t* personaje, juego_t* juego, int plus, char bando);

void preguntar_para_posicionar(int* energia, personaje_t* personaje, juego_t* juego, int plus, char bando);

void posicionar_personaje(juego_t* juego, personaje_t personaje);

void eliminar_personaje(juego_t* juego, int* cantidad, personaje_t personajes[], int posicion, char bando);

void jugar(juego_t* juego, char bando, int posicion_personaje);

#endif
