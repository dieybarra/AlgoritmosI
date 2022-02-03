#include <stdio.h>
#include <stdbool.h>

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
const int OFENSIVO=1;
const int DEFENSIVO=2;
const int INDEFINIDO=0;
const int DIEZ=10;
const int UNO=1;
const int CUATRO=4;


//pre: recibe el valor de la variable num_de_signo
//post: devuelve true si se cumple la condicion
bool validacion_de_signo (int * num_de_signo){

	return ((*num_de_signo < ARIES) || (*num_de_signo > PISCIS));
}

//pre: pide al usuario que ingrese un valor entero
//post: guarda el valor en la variable num_de_signo
void solicitar_signo (int* num_de_signo){

	do{
		printf ("\nIngrese el numero de su signo del zodiaco:\n1 Aries\n2 Tauro\n3 Geminis\n4 Cancer\n5 Leo\n6 Virgo\n7 Libra\n8 Escorpio\n9 Sagitario\n10 Capricornio\n11 Acuario\n12 Piscis\n");
		scanf (" %i", num_de_signo);
 	} while (validacion_de_signo (num_de_signo));
}

//pre: recibe el valor de la variable num_de_signo
//post: devuelve un caracter y lo guarda en la variable signo
void tipo_de_signo (char* signo, int num_de_signo){

	if ((num_de_signo == ARIES) || (num_de_signo == LEO) || (num_de_signo == SAGITARIO))
		*signo= FUEGO;
	else if ((num_de_signo == TAURO) || (num_de_signo == VIRGO) || (num_de_signo == CAPRICORNIO))
		*signo= TIERRA;
	else if ((num_de_signo == GEMINIS) || (num_de_signo == LIBRA) || (num_de_signo == ACUARIO))
		*signo= AIRE;
	else if ((num_de_signo == CANCER) || (num_de_signo == ESCORPIO) || (num_de_signo == PISCIS))
		*signo= AGUA;
 }	

//pre: pide al usuario que ingrese un caracter
//post: si es valido, guarda el valor en la variable genero
void solicitar_genero (char* genero){
	
	do{
		printf ("\nIngrese la letra de su genero de cine favorito\nA Accion\nC Comedia\nD Drama\nT Terror\n");
		scanf (" %c", genero);
	} while ((*genero != ACCION) && (*genero != COMEDIA) && (*genero != DRAMA) && (*genero != TERROR));

}

//pre: pide al usuario que ingrese un valor entero
//post: si es valido, guarda el valor en la variable maldades
void solicitar_maldades(int* maldades){

	do{
		printf ("\nIngrese la cantidad de maldades hechas en el ultimo mes, de 0 a 99\n");
		scanf (" %i", maldades);
	} while ((*maldades < MINIMO_MALDADES) || (*maldades > MAXIMO_MALDADES));
}

//pre: pide al usuario que ingrese un valor entero
//post: si es valido, guarda el valor en la variable mascotas
void solicitar_mascotas (int* mascotas){

	do{
		printf ("\nIngrese la cantidad de mascotas que tiene, del 0 al 5. Si tiene mas, ingrese 5. \n");
		scanf (" %i", mascotas);
	} while ((*mascotas < MINIMO_MASCOTAS) || (*mascotas > MAXIMO_MASCOTAS));
}

//pre: recibe el valor de las variables signo, genero y maldades
//post: si se cumplen las condiciones, devuelve la posicion aignada al usuario
int definir_posicion (char signo, char genero, int maldades){

	int posicion;

	if (((signo == AIRE) || (signo == FUEGO)) && ((genero == COMEDIA) || (genero == TERROR)) && (maldades >= MITAD_MALDADES))
		posicion= OFENSIVO;
	
	else if (((signo == AGUA) || (signo == TIERRA)) && ((genero == ACCION) || (genero == DRAMA)) && (maldades < MITAD_MALDADES))
		posicion= DEFENSIVO;

	else 	
		posicion= INDEFINIDO;

	return posicion;
}

//pre: recibe el valor de la variable maldades
//post: devuelve la cantidad de puntos de intensidad que le corresponde por esa variable
int intensidad_maldades (int maldades){

	int puntos_maldades;

	if ((maldades >= MINIMO_MALDADES) && (maldades < MITAD_MALDADES))
		puntos_maldades= (maldades/DIEZ)+ UNO;

	else if ((maldades>=MITAD_MALDADES)&&(maldades<=MAXIMO_MALDADES))
		puntos_maldades= (maldades/DIEZ)- CUATRO;

	return puntos_maldades;
}


int main(){

	char genero;
	char signo;
	int maldades;
	int mascotas;
	int posicion;
	int intensidad;
	int num_de_signo;

	do{
		solicitar_signo (&num_de_signo);
		tipo_de_signo (&signo, num_de_signo);
		solicitar_genero (&genero);
		solicitar_maldades (&maldades);
		solicitar_mascotas (&mascotas);

		posicion=definir_posicion (signo, genero, maldades);

		if (posicion == OFENSIVO)
			printf ("\nUsted va a luchar en el bando ofensivo.\n");
		else if (posicion == DEFENSIVO)
			printf ("\nUsted va a luchar en el bando defensivo.\n");			
	} while (posicion == INDEFINIDO);

	intensidad= intensidad_maldades(maldades) + mascotas;

	printf ("Su intensidad es de %i puntos.\n", intensidad );

}
