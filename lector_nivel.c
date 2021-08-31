#include "lector_nivel.h"
#include "stdio.h"

FILE *archivo;
//int filas, columnas;

int Sum(int a, int b)
{
    return a+b;
}

void leer_nivel_dim(char *rutaArchivo, int dim[2]) {
    if( ( archivo = fopen( rutaArchivo, "r" ) ) == NULL ) {
		fprintf( stderr, "lector_nivel: Error leyendo el archivo %s\n", rutaArchivo );
		//exit( -1 );
	} else {

        fscanf( archivo, "%d", &dim[0] );
        fscanf( archivo, "%d", &dim[1] );
        //printf("lector_nivel: Leyendo datos %d\n", datos);
    }

    fclose(archivo);
    rutaArchivo = NULL;
}

void leer_nivel(char *rutaArchivo, int nivel[], int dim[2]) {
    
    if( ( archivo = fopen( rutaArchivo, "r" ) ) == NULL ) {
		fprintf( stderr, "lector_nivel: Error leyendo el archivo %s\n", rutaArchivo );
		//exit( -1 );
	} else {
        fscanf( archivo, "%d", &nivel[0] );
        fscanf( archivo, "%d", &nivel[0] );
     
        for (int i = 0; i < dim[0]; i++)
        {
            for (int j = 0; j < dim[1]; j++)
            {
                fscanf( archivo, "%d", &nivel[i*dim[0]+j] );
            }
            //fscanf( archivo, "%d");
        }
    }

    fclose(archivo);
    rutaArchivo = NULL;
}
