#include <stdio.h>
#include <stdbool.h>
#include "perfil.h"

#define ISENGARD 'I'
#define ROHAN 'R'
const char INDEFINIDO = '.';
const int ARIES=1;
const int TAURO=2;
const int GEMINIS=3;
const int CANCER=4;
const int LEO=5;
const int VIRGO=6;
const int LIBRA=7;
const int ESCORPIO=8;
const int SAGITARIO=9;
const int CAPRICORNIO=10;
const int ACUARIO=11;
const int PISCIS=12;
const char AGUA='w';
const char FUEGO='f';
const char AIRE='a';
const char TIERRA='t';
const char ACCION='A';
const char COMEDIA='C';
const char DRAMA='D';
const char TERROR='T';
const int MINIMO_MALDADES=0;
const int MITAD_MALDADES=50;
const int MAXIMO_MALDADES=99;
const int MINIMO_MASCOTAS=0;
const int MAXIMO_MASCOTAS=5;
const int DIEZ=10;
const int UNO=1;
const int CUATRO=4;


//pre: recibe un valor entero
//post: devuelve true si se cumple la condicion
bool validacion_de_signo (int * num_de_signo){

	return ((*num_de_signo < ARIES) || (*num_de_signo > PISCIS));
}

//pre: 
//post: pide al usuario que ingrese un valor entero y lo guarda 
void solicitar_signo (int* num_de_signo){

	do{
		printf ("\nIngrese el numero de su signo del zodiaco:\n1 Aries\n2 Tauro\n3 Geminis\n4 Cancer\n5 Leo\n6 Virgo\n7 Libra\n8 Escorpio\n9 Sagitario\n10 Capricornio\n11 Acuario\n12 Piscis\n");
		scanf (" %i", num_de_signo);
 	} while (validacion_de_signo (num_de_signo));
}

//pre: recibe un valor valido entero entre cierto rango
//post: devuelve un caracter de acuerdo a su valor y lo guarda en la variable signo
void asignar_elemento (char* signo, int num_de_signo){

	if ((num_de_signo == ARIES) || (num_de_signo == LEO) || (num_de_signo == SAGITARIO))
		*signo= FUEGO;
	else if ((num_de_signo == TAURO) || (num_de_signo == VIRGO) || (num_de_signo == CAPRICORNIO))
		*signo= TIERRA;
	else if ((num_de_signo == GEMINIS) || (num_de_signo == LIBRA) || (num_de_signo == ACUARIO))
		*signo= AIRE;
	else if ((num_de_signo == CANCER) || (num_de_signo == ESCORPIO) || (num_de_signo == PISCIS))
		*signo= AGUA;
 }	

//pre: 
//post: pide al usuario que ingrese un caracter y lo guarda si éste es valido
void solicitar_genero (char* genero){
	
	do{
		printf ("\nIngrese la letra de su genero de cine favorito\nA Accion\nC Comedia\nD Drama\nT Terror\n");
		scanf (" %c", genero);
	} while ((*genero != ACCION) && (*genero != COMEDIA) && (*genero != DRAMA) && (*genero != TERROR));

}

//pre: 
//post: pide al usuario que ingrese un valor entero y si es valido, lo guarda 
void solicitar_maldades(int* maldades){

	do{
		printf ("\nIngrese la cantidad de maldades hechas en el ultimo mes, de 0 a 99\n");
		scanf (" %i", maldades);
	} while ((*maldades < MINIMO_MALDADES) || (*maldades > MAXIMO_MALDADES));
}

//pre: 
//post: pide al usuario que ingrese un valor entero y si es valido, lo guarda 
void solicitar_mascotas (int* mascotas){

	do{
		printf ("\nIngrese la cantidad de mascotas que tiene, del 0 al 5. Si tiene mas, ingrese 5. \n");
		scanf (" %i", mascotas);
	} while ((*mascotas < MINIMO_MASCOTAS) || (*mascotas > MAXIMO_MASCOTAS));
}

//pre: recibe valores validos en los rangos pedidos
//post: si se cumplen las condiciones, devuelve el tipo asignado al usuario
char definir_tipo (char signo, char genero, int maldades){

	char tipo;

	if (((signo == AIRE) || (signo == FUEGO)) && ((genero == COMEDIA) || (genero == TERROR)) && (maldades >= MITAD_MALDADES))
		tipo= ISENGARD;
	
	else if (((signo == AGUA) || (signo == TIERRA)) && ((genero == ACCION) || (genero == DRAMA)) && (maldades < MITAD_MALDADES))
		tipo= ROHAN;

	else 	
		tipo= INDEFINIDO;

	return tipo;
}

//pre: recibe un valor entero entre 0 y 99
//post: devuelve la cantidad de puntos de intensidad que le corresponde al usuario
 int intensidad_maldades (int maldades){

	int puntos_maldades;

	if ((maldades >= MINIMO_MALDADES) && (maldades < MITAD_MALDADES))
		puntos_maldades= (maldades/DIEZ)+ UNO;

	else if ((maldades>=MITAD_MALDADES)&&(maldades<=MAXIMO_MALDADES))
		puntos_maldades= (maldades/DIEZ)- CUATRO;

	return puntos_maldades;
}


void perfil(char* tipo, int* intensidad){

	char genero;
	char signo;
	int maldades;
	int mascotas;
	int num_de_signo;

	do{
		solicitar_signo (&num_de_signo);
		asignar_elemento (&signo, num_de_signo);
		solicitar_genero (&genero);
		solicitar_maldades (&maldades);
		solicitar_mascotas (&mascotas);

		*tipo = definir_tipo (signo, genero, maldades);

		if (*tipo == ISENGARD)
			printf ("\nUsted va a luchar en ISENGARD.\n");
		else if (*tipo == ROHAN)
			printf ("\nUsted va a luchar en ROHAN.\n");			
	} while (*tipo == INDEFINIDO);

	*intensidad= intensidad_maldades(maldades) + mascotas;

	printf ("Su intensidad es de %i puntos.\n", *intensidad );

}
