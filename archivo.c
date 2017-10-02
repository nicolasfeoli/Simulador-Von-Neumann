#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int abrirArchivo(const char *filename, char **result);

void itoa(int, char*);

void reverse(char*);
/*
int main(void){
	FILE* archivo = fopen("programaASM.txt","r");
	char contenido[255];

	int a=54325;
    char buffer[20];
    itoa(a,buffer);   // here 2 means binary
    printf("Binary value = %s\n", buffer);

	//fscanf(archivo, "%s\n", contenido); // lee de un archivo hasta encontrar un espacio
	fgets(contenido, 255, (FILE*) archivo); //lee 255 caracteres o hasta un cambio de linea
	printf("1 : %s\n", contenido );

	fclose(archivo);

	char *content; 
	int tamano,i;
	tamano = abrirArchivo("programaASM.txt", &content);
	/*
	for(i = 0; i < tamano; i++)
		putchar(content[i]);
	
	putchar('\n');
	return 0;
}
*/

/*
abrirArchivo:
	Entradas: arreglo de chars con el filename y un doble puntero al buffer
	Salida: entero con el tamano en bytes del archivo
*/
int abrirArchivo(const char *filename, char **result) 
{ 
	int tamano = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) 
	{   //el archivo no abre
		*result = NULL;
		return -1;
	} 
	fseek(f, 0, SEEK_END);
	tamano = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(tamano+1);

	fclose(f);
	(*result)[tamano] = 0;
	return tamano;
}

void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
} 