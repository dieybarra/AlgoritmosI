#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define MAX_RANGO 50
#define MAX_DESCRIPCION 200
#define COINCIDENCIA 0
#define INICIAL 1
#define SEGUNDO 2
#define TERCERO 3
#define CUARTO 4
#define QUINTO 5
#define DOS_ARGUMENTOS 2
#define TRES_ARGUMENTOS 3
#define CINCO_ARGUMENTOS 5
#define SEIS_ARGUMENTOS 6
#define MAX_APRENDICES 10
#define ID_APRENDIZ 2
#define ID_GUERRERO 3
#define ID_LIDER 4
#define ID_GENERAL 5

#define FORMATO_LECTURA "%[^;];%i;%i;%i\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%i\n"
#define ACTUALIZAR "actualizar_censo"
#define ELEGIR "integrantes_mision"
#define PROMOVER "promover_enanos"
#define LISTAR "listar_enanos"
#define MISION "mision.dat"
#define CENSO "censo.csv"
#define CENSO_ACTUAL "censo_actual.csv"
#define ARCHIVO_RANGOS "rangos.dat"
#define EXTENSION_DAT ".dat"

typedef struct enano{
	char nombre[MAX_NOMBRE];
	int edad;
	int cantidad_misiones;
	int id_rango;
} enano_t;

typedef struct rango{
	int id;
	char nombre[MAX_RANGO];
	char descripcion[MAX_DESCRIPCION];
} rango_t;

//pos: actualiza el archivo censo de acuerdo a la mision pasada por parametro si es que existe
int actualizar_censo(char* ruta_mision){

    enano_t enano_censo;
    enano_t enano_mision;
    int leido_censo;

    FILE* censo = fopen(CENSO, "r");

    if(!censo){
    	perror("Problema al abrir el archivo censo");
    	return -1;
    }

	FILE* censo_actual = fopen(CENSO_ACTUAL, "w");

	if(!censo_actual){
		perror("Problema al abrir el archivo censo_actual");
		return -1;
	}

    FILE* mision = fopen(ruta_mision, "r");

    if(!mision){
        perror("No existe el archivo");
        return -1;
    }

    leido_censo = fscanf(censo, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);     
    fread(&enano_mision, sizeof(enano_t), 1, mision);

    while(!feof(mision) && (leido_censo != EOF)){
        
        if (strcmp(enano_mision.nombre, enano_censo.nombre) == COINCIDENCIA){
            if(enano_mision.edad != -1){
                enano_censo.cantidad_misiones += 1;
                fprintf(censo_actual, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);
            }

            leido_censo = fscanf(censo, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
            fread(&enano_mision, sizeof(enano_t), 1, mision);
                           
        
        }else if (strcmp(enano_mision.nombre, enano_censo.nombre) < COINCIDENCIA){
        
            enano_mision.cantidad_misiones += 1;
            fprintf(censo_actual, FORMATO_ESCRITURA, enano_mision.nombre, enano_mision.edad, enano_mision.cantidad_misiones, enano_mision.id_rango);     
            fread(&enano_mision, sizeof(enano_t), 1, mision);

        }else{ 
            fprintf(censo_actual, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);     
            fscanf(censo, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango);
        }
    }

    while(leido_censo != EOF){
        fprintf(censo_actual, FORMATO_ESCRITURA, enano_censo.nombre, enano_censo.edad, enano_censo.cantidad_misiones, enano_censo.id_rango);     
        leido_censo = fscanf(censo, FORMATO_LECTURA, enano_censo.nombre, &enano_censo.edad, &enano_censo.cantidad_misiones, &enano_censo.id_rango); 
    }
    
    while(!feof(mision)){
			enano_mision.cantidad_misiones += 1;
            fprintf(censo_actual, FORMATO_ESCRITURA, enano_mision.nombre, enano_mision.edad, enano_mision.cantidad_misiones, enano_mision.id_rango);     
            fread(&enano_mision, sizeof(enano_t), 1, mision);
    }

    fclose(mision);
    fclose(censo);
    fclose(censo_actual);
    remove(CENSO);
    rename(CENSO_ACTUAL, CENSO);
    printf("Se ha actualizado el censo con la mision: %s\n", ruta_mision);
    return 1;
}    

//pos: crea un archivo binario con los datos de los enanos y se lo guarda con el nombre elegido. Si el archivo ya existe, no hace nada 
int elegir_enanos(int guerreros, int lideres, int generales, const char* nombre_mision){

	int leidos = 0;
	enano_t enano;
  	int contador_guerreros = 0;
  	int contador_lideres = 0;
  	int contador_generales = 0;
  	int aprendices = 0;

    FILE* leer_mision = fopen(nombre_mision, "r");

    if(leer_mision){
        printf("El nombre de tu mision ya existe papu\n");
        return -1;
    }

	FILE* enanos = fopen(CENSO, "r");
    
    if(!enanos){
		perror("Problema al abrir el archivo censo");
    	return -1;
	}

  	FILE* mision = fopen(nombre_mision, "w");

	if(!mision){
		perror("Problema al abrir el archivo de la mision");
    	return -1;
	}

    leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);
 	while(leidos != EOF){

    	switch (enano.id_rango){
      		case ID_APRENDIZ:
        		if(aprendices < MAX_APRENDICES){
          			aprendices++;
          			fwrite(&enano, sizeof(enano), 1, mision);
        		}
        		break;
	      	case ID_GUERRERO:
	        	if(contador_guerreros < guerreros){
	          		contador_guerreros++;
   			 		fwrite(&enano, sizeof(enano), 1, mision);
	        	}
	        	break;
	      	case ID_LIDER:
	        	if(contador_lideres < lideres){
	          		contador_lideres++;
				    fwrite(&enano, sizeof(enano), 1, mision);
	        	}
	        	break;
	      	case ID_GENERAL:
	        	if(contador_generales < generales){
	          		contador_generales++;
				    fwrite(&enano, sizeof(enano), 1, mision);
	        	}
	        	break;
	    }
        leidos = fscanf(enanos, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);

    }

    if(contador_guerreros == guerreros && contador_lideres == lideres && contador_generales == generales){
		fclose(enanos);
		fclose(mision);
        printf("Se ha creado la mision: %s\n", nombre_mision);
		return 1;
	}
	else{
        printf("No se alcanzo la cantidad pedida, sorri\n");
	    fclose(mision);
	    fclose(enanos);
	    remove(nombre_mision);
	    return -1;
	}
}

//pos: actualiza el censo promoviendo a los enanos que cumplan con las condiciones
int promover_enanos(){

	int leidos;
	enano_t enano;

	FILE* censo = fopen(CENSO, "r");

	if(!censo){
		perror("Problema al abrir el archivo censo");
    	return -1;
	}

	FILE* censo_actual = fopen(CENSO_ACTUAL, "w");

	if (!censo_actual){
		perror("Problema al abrir el archivo censo_actual");
		return -1;
	}
    leidos = fscanf (censo, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);		
	while (leidos != EOF){

		if (enano.cantidad_misiones > 10 && enano.id_rango == ID_APRENDIZ)
			enano.id_rango = ID_GUERRERO;
		else if (enano.cantidad_misiones > 100 && enano.edad >= 40 && enano.edad < 50 && enano.id_rango == ID_GUERRERO)
			enano.id_rango = ID_LIDER;
		else if (enano.cantidad_misiones > 250 && enano.edad >=50 && enano.edad < 60 && enano.id_rango == ID_LIDER)
			enano.id_rango = ID_GENERAL;

		fprintf (censo_actual, FORMATO_ESCRITURA, enano.nombre, enano.edad, enano.cantidad_misiones, enano.id_rango);
        leidos = fscanf (censo, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);	
    }

	fclose(censo);
	fclose(censo_actual);
	remove(CENSO);
    rename(CENSO_ACTUAL, CENSO);
    printf("Se ha actualizado el censo con las promociones");
    return 1;
}

//pos: Imprime los datos de los enanos que tienen el rango pasado por parametro
int listar_enanos(int rango_id){

    FILE* rangos = fopen(ARCHIVO_RANGOS, "r");

    if (!rangos){
		perror("Problema al abrir el archivo rangos");
		return -1;
	}
 
    FILE* censo = fopen(CENSO, "r");

	if (!censo){
		perror("Problema al abrir el archivo censo");
		return -1;
	}

    int leidos;
    enano_t enano;
    rango_t rango;

    fseek(rangos,(rango_id - 1) * (long) sizeof (rango_t), SEEK_SET);
    fread (&rango, sizeof (rango_t), 1, rangos);

    printf ("Rango: %s\nDescripcion: %s\n\n", rango.nombre, rango.descripcion);  

    fread (&rango, sizeof (rango), 1, rangos);   

    leidos = fscanf (censo, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);		

    while (leidos != EOF){

		if (enano.id_rango == rango_id)

            printf("Nombre: %s\nEdad: %i\nCantidad de misiones: %i\n\n", enano.nombre, enano.edad, enano.cantidad_misiones); 
        
        leidos = fscanf (censo, FORMATO_LECTURA, enano.nombre, &enano.edad, &enano.cantidad_misiones, &enano.id_rango);	
    }

    fclose(censo);
    fclose(rangos);

    return 1;
}

int main(int argc, char *argv[]){

    if(argc == DOS_ARGUMENTOS && strcmp(argv[INICIAL], PROMOVER) == COINCIDENCIA)
        promover_enanos();

    else if (argc == TRES_ARGUMENTOS && strcmp(argv[INICIAL], LISTAR) == COINCIDENCIA)
    	if(atoi(argv[SEGUNDO])> 0 && atoi(argv[SEGUNDO]) < 6)
        	listar_enanos(atoi(argv[SEGUNDO]));
        else
        	printf("No existe ese id_rango\n");


    else if(argc == TRES_ARGUMENTOS && strcmp(argv[INICIAL], ACTUALIZAR) == COINCIDENCIA){
        
        strcat(argv[SEGUNDO], EXTENSION_DAT);
        actualizar_censo(argv[2]);

    }else if(argc == CINCO_ARGUMENTOS && strcmp(argv[INICIAL], ELEGIR) == COINCIDENCIA)

        elegir_enanos(atoi(argv[SEGUNDO]), atoi(argv[TERCERO]), atoi(argv[CUARTO]), MISION);

    else if (argc == SEIS_ARGUMENTOS && strcmp(argv[INICIAL], ELEGIR) == COINCIDENCIA){
        
        strcat(argv[QUINTO], EXTENSION_DAT);
        elegir_enanos(atoi(argv[SEGUNDO]), atoi(argv[TERCERO]), atoi(argv[CUARTO]), argv[QUINTO]);

    }else{
        perror("Cantidad de argumentos inválidaaaa");
        return -1;
      }

	return 0;
}        
