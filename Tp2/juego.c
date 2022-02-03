#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "batalla.h"

#define ISENGARD 'I'
#define ROHAN 'R'
#define MARCADO 'M'
#define DOS_JUGADORES 2
#define UN_JUGADOR 1
const int ENERGIA_MAXIMA = 10;
const int ENERGIA_INICIAL = 5;
const int LLEGADAS_PARA_GANAR = 5;

int main(){
	
	juego_t juego;
	personaje_t personaje;

	int energia_rohan = ENERGIA_INICIAL;
	int energia_isengard = ENERGIA_INICIAL;

	srand ((unsigned)time(NULL));	
	inicializar_juego(&juego);
	mostrar_terreno(juego);
    //energia_rohan = rand() % 5;    parece que el random lo hace de 0 a 4
    //printf("su energia es %i ", energia_rohan);

	while ((juego.llegadas_rohan != LLEGADAS_PARA_GANAR) && (juego.llegadas_isengard != LLEGADAS_PARA_GANAR)){

		if (juego.cantidad_jugadores == DOS_JUGADORES){

			preguntar_para_posicionar(&energia_rohan, &personaje, &juego, juego.plus_rohan, ROHAN);
			preguntar_para_posicionar(&energia_isengard, &personaje, &juego, juego.plus_isengard, ISENGARD);
		}
		else if (juego.cantidad_jugadores == UN_JUGADOR){
			if (juego.tipo_primer_jugador == ISENGARD){
				posicionar_automaticamente(&energia_rohan, &personaje, &juego, juego.plus_rohan, ROHAN);
				preguntar_para_posicionar(&energia_isengard, &personaje, &juego, juego.plus_isengard, ISENGARD);
			}
			else if (juego.tipo_primer_jugador == ROHAN){
				preguntar_para_posicionar(&energia_rohan, &personaje, &juego, juego.plus_rohan, ROHAN);
				posicionar_automaticamente(&energia_isengard, &personaje, &juego, juego.plus_isengard, ISENGARD);
			}	
		}
        system ("clear");
		mostrar_terreno(juego);
        printf("Juega el bando Rohan\n");
        int i= 0;
        while (i < juego.cantidad_rohan){
            jugar (&juego, ROHAN, i);
            if (juego.rohan[i].codigo == MARCADO)
                eliminar_personaje(&juego, &(juego.cantidad_rohan), juego.rohan, i, ISENGARD);
            else
                i++;
        }
		mostrar_terreno(juego);
        printf("Juega el bando Isengard\n");
        
        i = 0;
		while (i < juego.cantidad_isengard){
            jugar (&juego, ISENGARD, i);
            if (juego.isengard[i].codigo == MARCADO)
                eliminar_personaje(&juego, &(juego.cantidad_isengard), juego.isengard, i, ROHAN);
            else
                i++;
        }
		mostrar_terreno(juego);
        if (energia_rohan < ENERGIA_MAXIMA)
		    energia_rohan++;
		if (energia_isengard < ENERGIA_MAXIMA)
            energia_isengard++;

	    if (juego.llegadas_rohan == LLEGADAS_PARA_GANAR)
		    printf("La guerra ha terminado! Ha ganado Rohan\n");
	    else if (juego.llegadas_isengard == LLEGADAS_PARA_GANAR)
		    printf("La guerra ha terminado! Ha ganado Isengard\n");	
	}
return 0;
}
