#include "stdio.h"
#include "stdlib.h"
#include <string.h>
int main()
{
	char hola[5];
	memset(&hola[0], 0, sizeof(hola));

	hola[0]==0?printf("%s\n","es 0" ):printf("%s\n","no es 0" );
	return 0;
}