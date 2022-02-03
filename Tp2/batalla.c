#include "batalla.h" 
#include "perfil.h"

#define ISENGARD 'I'
#define ROHAN 'R'
#define MAX_PERSONAJES 50
#define MARCADO 'M'
#define DOS_JUGADORES 2
#define UN_JUGADOR 1
const int RANGO_ALEATORIO = 6;
const int NINGUNO = 0;
const int CANTIDAD_INICIAL = 3;
const int ENERGIA_SOLDADO = 3;
const int ENERGIA_ARQUERO = 8;
const int DISTANCIA_ARQUEROS = 3;
const int VIDA_ESTANDAR_ARQUEROS = 200;
const int VIDA_ESTANDAR_SOLDADOS = 100;
const int PLUS_ESTANDAR = 10;
const int ATAQUE_ESTANDAR_SOLDADOS = 50;
const int ATAQUE_ESTANDAR_ARQUEROS = 10;
const char HOMBRES = 'H';
const char ORCOS = 'O';
const char ELFOS = 'E';
const char URUKHAI = 'U';
const char VACIO = '-';
const char AMBOS = 'A';
const char SI = 'S';

//pos: imprime la matriz terreno actualizada
void mostrar_terreno(juego_t juego){
        printf("\n   ");
        for (int j = 0; j < MAX_TERRENO_COL; j++){
		    printf(" %i |", j);
            }
        printf("\n");	
		for (int i = 0; i < MAX_TERRENO_FIL; i++){
            printf("%i |", i );
         
			for (int j = 0; j < MAX_TERRENO_COL; j++){
				printf(" %c |", juego.terreno[i][j] );	
			}	
			printf("\n");
		}
		printf("\n");	
}

//pos: asigna el valor de plus para cada bando
void asignar_plus(juego_t* juego, int intensidad, int numero_aleatorio){
	if ((*juego).tipo_primer_jugador == ISENGARD){
		(*juego).plus_isengard = intensidad * numero_aleatorio;
		(*juego).plus_rohan = (PLUS_ESTANDAR - intensidad) * numero_aleatorio;
	} else 
		(*juego).plus_rohan = intensidad * numero_aleatorio;
		(*juego).plus_isengard = (PLUS_ESTANDAR - intensidad) * numero_aleatorio;
}

//pre: recibe datos validos de los campos de un registro personaje
//pos: crea un registro personaje con los datos cargados
void crear_personaje(personaje_t* personaje, int plus, char codigo, int fila, int columna){
	(*personaje).codigo = codigo;
	if ((codigo == HOMBRES)||(codigo == ORCOS)){
		(*personaje).vida = VIDA_ESTANDAR_SOLDADOS - plus;
		(*personaje).ataque = 50 + plus;
	} else{
		(*personaje).vida = VIDA_ESTANDAR_ARQUEROS - plus;
		(*personaje).ataque = 10 + plus;
	}
	(*personaje).fila = fila;
	(*personaje).columna = columna;
}

//pre: recibe un registro personaje cargado con datos validos
//pos: posiciona el personaje en la matriz y en el vector correspondiente
void posicionar_personaje(juego_t* juego, personaje_t personaje){

	(*juego).terreno[personaje.fila][personaje.columna] = personaje.codigo;
	if ((personaje.codigo == HOMBRES)||(personaje.codigo == ELFOS)){
		(*juego).rohan [(*juego).cantidad_rohan] = personaje;
		(*juego).cantidad_rohan++;
	} else{
		(*juego).isengard [(*juego).cantidad_isengard] = personaje;
		(*juego).cantidad_isengard++;	
	}
}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si se cumple la condicion
bool chequear_casillero_ocupado(juego_t juego, int fila, int columna){
	if (juego.terreno[fila][columna] == VACIO)
		return false;
	printf("El casillero ya está ocupado\n");
	return true;
}

//pos: posiciona en la matriz y en el vector los primeros personajes de forma automatica
void posicionar_iniciales(juego_t* juego, personaje_t* personaje){

	int fila, columna;
	for (int i = 0; i < CANTIDAD_INICIAL; i++){

		do{
			fila = rand() % ((MAX_TERRENO_FIL / 2) - 1) + (MAX_TERRENO_FIL / 2) ;
			columna = rand() % (MAX_TERRENO_COL);
		} while (chequear_casillero_ocupado(*juego, fila, columna));
			crear_personaje(personaje,(*juego).plus_rohan, ELFOS, fila, columna);
			posicionar_personaje(&(*juego), *personaje);
		do{
			fila = rand() % ((MAX_TERRENO_FIL / 2) - 1) + 1;
			columna = rand() % (MAX_TERRENO_COL);
		} while (chequear_casillero_ocupado(*juego, fila, columna));
			crear_personaje(&(*personaje), (*juego).plus_isengard, URUKHAI, fila, columna);
			posicionar_personaje(&(*juego), *personaje);
	}

}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si se cumple la condicion
bool validacion_de_respuesta_jugadores(int respuesta){

    if (respuesta == UN_JUGADOR || respuesta == DOS_JUGADORES)
        return false;
    printf("La cantidad de jugadores no es correcta\n");
    return true;
}
//pre: recibe un personaje , con todos sus campos correctamente cargados 
//pos: da el personaje de alta en el juego , sumandolo al vector correspondiente y posicionándolo también en la matriz
void inicializar_juego(juego_t* juego){
	
	int intensidad;
	char tipo;
	int numero_aleatorio;
	int respuesta;
	personaje_t personaje;

	numero_aleatorio = rand() % RANGO_ALEATORIO;
	perfil(&tipo, &intensidad);
	(*juego).tipo_primer_jugador = tipo;
    do{
	    printf("Indique si van a jugar 1 o 2 jugadores\n");
		scanf (" %i", &respuesta);
	} while (validacion_de_respuesta_jugadores(respuesta));

	(*juego).cantidad_jugadores = respuesta;
	asignar_plus(juego, intensidad, numero_aleatorio);

    system ("clear");

	(*juego).cantidad_rohan = NINGUNO;
	(*juego).llegadas_rohan = NINGUNO;
	(*juego).cantidad_isengard = NINGUNO;
	(*juego).llegadas_isengard = NINGUNO;

	for (int i = 0; i < MAX_TERRENO_FIL; i++){
		for (int j = 0; j < MAX_TERRENO_COL; j++){
			(*juego).terreno[i][j] = VACIO;
		}
	}
	posicionar_iniciales(juego, &personaje);
}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si no se cumplen las condiciones
bool chequear_energia(char codigo, int energia){
    if ((codigo == ORCOS || codigo== HOMBRES) && energia >= ENERGIA_SOLDADO)
        return true;
    else if ((codigo == URUKHAI || codigo== ELFOS) && energia >= ENERGIA_ARQUERO)
        return true;
    return false;
}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si se cumplen la condiciones
bool validacion_de_codigo(char codigo, char bando){
	if ((bando == ISENGARD && codigo == ORCOS) || (bando == ISENGARD && codigo == URUKHAI))
		return false;
	else if ((bando == ROHAN && codigo == HOMBRES) || (bando == ROHAN && codigo == ELFOS))
		return false;
    printf("El codigo ingresado es incorrecto\n");
	return true;
}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si se cumplen la condiciones
bool validacion_de_fila(char codigo, int fila){
    if (codigo == ELFOS && fila < MAX_TERRENO_FIL - 2 && fila >= MAX_TERRENO_FIL/2)
        return false;
    else if (codigo == URUKHAI && fila < MAX_TERRENO_FIL/2 && fila > 0)
        return false;
    printf("La fila elegida no está dentro de su campo\n");
    return true;
}

//pre: recibe datos cargados por el usuario
//pos: devuelve false si se cumple la condicion
bool validacion_de_columna(int columna){
    if (columna >= 0 && columna < MAX_TERRENO_COL)
        return false;
    printf("La columna elegida no está dentro del campo\n");
    return true;
}

//pos: crea un personaje y lo posiciona en la matriz y vector correspondiente si se cumple las condiciones
void posicionar_automaticamente(int* energia, personaje_t* personaje, juego_t* juego, int plus, char bando){

    char codigo;
	int fila, columna;

	if (bando == ROHAN){
		codigo = HOMBRES;
		fila = MAX_TERRENO_FIL - 1;
		printf("\nLe toca a Rohan\n");
	}else{ 
		codigo = ORCOS;
		fila = 0;
		printf("\nLe toca a Isengard\n");
	}	
    if (chequear_energia(codigo, *energia)){
      	
      	do{
			columna = rand() % (MAX_TERRENO_COL);
      	    crear_personaje (personaje, plus, codigo, fila, columna);      
                
	    } while (chequear_casillero_ocupado(*juego, fila, columna));

        posicionar_personaje (&*juego, *personaje);
		*energia -= ENERGIA_SOLDADO;
		printf("La maquina ya ha posicionado\n");

    } else
     	printf("La maquina no tiene energia suficiente\n");
}                 

//pos: imprime informacion para el jugador
void indicar_bando(char bando, int energia, char* respuesta){

	if (bando == ROHAN)
		printf("\nLe toca a Rohan\n");
	else 
		printf("\nLe toca a Isengard\n");

	printf ("Presione la tecla S si desea posicionar un personaje. Sus puntos de energia: %i\n", energia);
	scanf (" %c", respuesta);
}

//pos: pregunta al jugador si quiere posicionar, y si se cumple las condiciones, crea y posiciona el personaje cargado
void preguntar_para_posicionar(int* energia, personaje_t* personaje, juego_t* juego, int plus, char bando){

	char respuesta, respuesta_codigo;
	int respuesta_fila, respuesta_columna;

	indicar_bando(bando, *energia, &respuesta);

	if (respuesta == SI){
		
		do{
			printf("Indique el codigo del personaje que desea\n");
			scanf (" %c", &respuesta_codigo);
		} while (validacion_de_codigo(respuesta_codigo, bando));
			
        if (chequear_energia(respuesta_codigo, *energia)){

  	        do{
			    if (respuesta_codigo == HOMBRES)
				    respuesta_fila = MAX_TERRENO_FIL - 1;
			    else if (respuesta_codigo == ORCOS)
				    respuesta_fila = 0;
			    else if ((respuesta_codigo == ELFOS||respuesta_codigo == URUKHAI)){
                    do{
				        printf("Indique la fila\n"); 
			 	        scanf(" %i", &respuesta_fila);
			        } while (validacion_de_fila(respuesta_codigo, respuesta_fila));
			    }
	
                do{
			        printf("Indique la columna\n");
			        scanf(" %i", &respuesta_columna);
                } while (validacion_de_columna(respuesta_columna));

                crear_personaje (personaje, plus, respuesta_codigo, respuesta_fila, respuesta_columna); 
                
		    } while (chequear_casillero_ocupado(*juego, respuesta_fila, respuesta_columna));

            posicionar_personaje (&*juego, *personaje);

		    if (respuesta_codigo == HOMBRES || respuesta_codigo == ORCOS)
			    *energia -= ENERGIA_SOLDADO;
		    else
                *energia -= ENERGIA_ARQUERO;

        } else
                 printf("No tiene energia suficiente\n");
		
	} else 
		printf("Ha perdido su turno de posicionar\n");
}		

//pos: actualiza la matriz y la cantidad de llegadas para el bando correspondiente
void marcar_personaje (juego_t* juego, int posicion, char bando){
	if (bando == ROHAN){
        (*juego).rohan[posicion].codigo = MARCADO;
        (*juego).llegadas_rohan++;
        printf("Ha llegado un hombre. Llegadas: %i\n", (*juego).llegadas_rohan); 
	} else {
        (*juego).isengard[posicion].codigo = MARCADO;
        (*juego).llegadas_isengard++;
        printf("Ha llegado un orco. Llegadas: %i\n", (*juego).llegadas_isengard); 
	}
}
//pre: recibe un personaje con sus datos cargados
//pos: borra el personaje del terreno y actualiza el vector de personajes borrando el personaje en su posicion
void eliminar_personaje(juego_t* juego, int* cantidad, personaje_t personajes[], int posicion, char bando){

    char soldado, arquero;

	if (bando == ROHAN){
        soldado = ORCOS;
        arquero = URUKHAI;
    } else{
        soldado = HOMBRES;
        arquero = ELFOS; 
    }

    if ((*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] == AMBOS){
        if (personajes[posicion].codigo == soldado) 
           (*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] = arquero;
        else  
           (*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] = soldado;
    }else                    
        (*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] = VACIO;

	for (int i = posicion; i < *cantidad - 1; i++){
	    personajes[i] = personajes[i + 1];
	}
	*cantidad -= 1;    
}

//pos: devuelve true si se cumple la condicion 
bool distancia_manhattan(int fila_uno, int columna_uno, int fila_dos, int columna_dos){

	return (abs(fila_uno - fila_dos) + abs(columna_uno - columna_dos) <= DISTANCIA_ARQUEROS);
}

//pos: devuelve true si se cumple la condicion 
bool distancia_adyacente(int fila_uno, int columna_uno, int fila_dos, int columna_dos){

	return ((abs(fila_uno - fila_dos) <= 1) && (abs(columna_uno - columna_dos)) <= 1);
}

//pos: verifica la vida del personaje y si se cumple la condicion, lo elimina del vector correspondiente
void chequear_si_esta_muerto(juego_t* juego, char bando, int* posicion){

	if (bando == ROHAN){

        if ((*juego).isengard[*posicion].vida <= 0){ 	
		    eliminar_personaje(juego, &((*juego).cantidad_isengard), (*juego).isengard, *posicion, bando);
		    *posicion-= 1;
        }
    } else{
        if ((*juego).rohan[*posicion].vida <= 0){
            eliminar_personaje(juego, &((*juego).cantidad_rohan), (*juego).rohan, *posicion, bando);
		    *posicion-= 1;      
        }
	}		
}

//pre: recibe una personaje con sus datos cargados.
//pos: avanza el personaje un casillero, actualizando el terreno 

void avanzar(juego_t* juego, personaje_t personajes[], char bando, int posicion){

	char soldado, arquero;
	int incremento, fila_llegada;

	if (bando == ROHAN){
        soldado = HOMBRES;
        arquero = ELFOS;
        incremento = -1;
        fila_llegada = 0;
    } else{
        soldado = ORCOS;
        arquero = URUKHAI; 
        incremento = 1;
        fila_llegada = MAX_TERRENO_FIL - 1;
    }

	if ((*juego).terreno[personajes[posicion].fila + incremento][personajes[posicion].columna] == VACIO){
            personajes[posicion].fila += incremento;
			(*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] = soldado;
            if ((*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] == soldado)
                (*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] = VACIO;
            else if ((*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] == AMBOS)
                (*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] = arquero;
            if (personajes[posicion].fila == fila_llegada)
                marcar_personaje (juego, posicion, bando);

        } else if ((*juego).terreno[personajes[posicion].fila + incremento][personajes[posicion].columna] == arquero){
            personajes[posicion].fila += incremento; 
 			(*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] = AMBOS;
            if ((*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] == soldado)
                (*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] = VACIO;    
            else if ((*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] == AMBOS)   
                (*juego).terreno[personajes[posicion].fila - incremento][personajes[posicion].columna] = arquero;
        }                   
}  

//pre: recibe un personaje y su codigo, junto con el terreno de juego
//pos: daña al rival o avanza de acuerdo a la informacion del terreno
void evaluar_jugada(juego_t* juego, int* cantidad, personaje_t personajes[], personaje_t personajes_rivales[], int posicion_personaje, char bando, char soldado, char arquero){

    if (personajes[posicion_personaje].codigo == arquero){
		for (int j = 0; j < *cantidad; j++){
			if (distancia_manhattan(personajes[posicion_personaje].fila, personajes[posicion_personaje].columna, personajes_rivales[j].fila, personajes_rivales[j].columna)){
				personajes_rivales[j].vida -= personajes[posicion_personaje].ataque;
		        printf("%c en fila %i, columna %i fue herido. Ahora su vida es: %i\n", personajes_rivales[j].codigo, personajes_rivales[j].fila, personajes_rivales[j].columna, personajes_rivales[j].vida); 		
				chequear_si_esta_muerto (juego, bando, &j);			
	        }
	    }
    }else if (personajes[posicion_personaje].codigo == soldado){ 
		int j = 0;
		bool encontrado = false;
		while ((!encontrado) && j < *cantidad){
			if (distancia_adyacente(personajes[posicion_personaje].fila, personajes[posicion_personaje].columna, personajes_rivales[j].fila, personajes_rivales[j].columna)){
				encontrado = true;
				personajes_rivales[j].vida -= personajes[posicion_personaje].ataque;
		        printf("%c en fila %i, columna %i fue herido. Ahora su vida es: %i\n", personajes_rivales[j].codigo, personajes_rivales[j].fila, personajes_rivales[j].columna, personajes_rivales[j].vida); 		
				chequear_si_esta_muerto (juego, bando, &j);			
			} else
				 j++;
		}

		if (encontrado == false)
			avanzar(juego, personajes, bando, posicion_personaje);
	}
}          

void jugar(juego_t* juego, char bando, int posicion_personaje){

	char soldado, arquero;

	if (bando == ROHAN){
        soldado = HOMBRES;
        arquero = ELFOS;
        evaluar_jugada(juego, &((*juego).cantidad_isengard), (*juego).rohan, (*juego).isengard, posicion_personaje, bando, soldado, arquero);

    } else{
        soldado = ORCOS;
        arquero = URUKHAI; 
        evaluar_jugada(juego, &((*juego).cantidad_rohan), (*juego).isengard, (*juego).rohan, posicion_personaje, bando, soldado, arquero);
    }
}








