#include "stdio.h"
#include "stdlib.h"
#include <string.h>
int main()
{
	char hola[19] = "hola que hace";
	char a[14] = "hola que hace ";

	strcmp(a,"hola que hace")==0?printf("%s\n","iguales"):printf("%s\n", "diferentes");
	return 0;
}