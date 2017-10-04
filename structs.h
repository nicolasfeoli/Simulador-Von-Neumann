#include "stdio.h"
#include "stdlib.h"
#include <string.h>

char prog[256][500];

short memoria[256] = {0};

//FUENTE8  FUENTE16
//DESTINO8 DESTINO16
//INDEX

char* IR = "mov ax, 5";
int PC = 0,
	ah,al,ax = 0,
	bh,bl,bx = 0,
	ch,cl,cx = 0,
	dl,dh,dx = 0,
	zeroF=0,signF=0,
	interruptF=0,carryF=0,
	B1=0,B2=0,B3=0,B4=0;

GtkWidget *AXdec,*BXdec,*CXdec,*DXdec;
void excInstruccion(char reg[])
{
	char ins[5],par1[5],par2[5];
	memset(&ins[0], 0, sizeof(ins));
	memset(&par1[0], 0, sizeof(par1));
	memset(&par2[0], 0, sizeof(par2));
	int index, i, tipo = 1,instruccion,parametro1,parametro2,cuartoDato;
	for(i = 0;i<(int)strlen(reg);i++)
	{
		switch(tipo)
		{
			case 1:

				if(reg[i]==0x20)
				{
					tipo++;
					index = 0;
				}
				else
				{
					if(reg[i]!=0x20) ins[index++]=reg[i];
				}
				break;
			case 2:
				if(reg[i]==',') 
				{
					tipo++;
					index = 0;
				}
				else
				{
					if(reg[i]!=0x20) par1[index++]=reg[i];
				}
				break;
			case 3:
				if(reg[i]!=0x20) par2[index++]=reg[i];
				break;
		}
	}

	if(!strcmp(ins,"cmp"))
		printf("%s\n", "FUCK YEA");
	/*printf("%s\n", reg);
	putchar('\n');
	printf("%s\n", "Instruccion:");
	printf("%s\n", ins);
	printf("%s\n", "Parametro 1:");
	printf("%s\n", par1);
	printf("%s\n", "Parametro 2:");
	printf("%s\n", par2);*/
}
void getRenglones(char* text)
{
	int i = 0,index = 0,comment = 0;;
	while(text[i]!='\0')
	{
		if(text[i]=='\n')
		{
			index = 0;
			comment =0;
			PC++;
		}
		else if(text[i]==';')
		{
			comment = 1;
			if(!index) PC--;
		}
		else
		{
			if(!comment) prog[PC][index++]=text[i];
		}
		i++;
	}
	PC=0;
	excInstruccion(prog[8]);
}
gchar *get_dialog_path_selection()
{
    GtkWidget *dialog;
    int dlg_res = 0;
    gchar *path;

	dialog = gtk_file_chooser_dialog_new("Seleccione el archivo a cargar", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    dlg_res = gtk_dialog_run(GTK_DIALOG(dialog));

    if( dlg_res == GTK_RESPONSE_ACCEPT )
    {
	   path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    else
    {
    	printf("Path selection: Canceled.\n");
    	path = NULL;
    }

    gtk_widget_destroy(dialog);
    
    return path;
}
char* abrirArchivo(GtkButton* button, gpointer func_data) 
{ 
	const char *filename = get_dialog_path_selection();;
  	char *buffer = NULL;
   	int tamano, lenRes;
   	FILE *file = fopen(filename, "r");

   	if (file)
   	{
       	fseek(file, 0, SEEK_END);//enceuntra ultimo byte del archivo
       	tamano = ftell(file);//tamaño del inicio al fin
       	rewind(file);//se pone al inicio del archivo				

       	buffer = (char*) malloc(sizeof(char) * (tamano + 1) );//crea el char* donde estara
       	lenRes = fread(buffer, sizeof(char), tamano, file);//lee todo
       	buffer[tamano] = '\0';//para que sea el fin del string

       	if (tamano != lenRes)//si son de distintos tamaños estamos mamando
       	{
           	free(buffer);
           	buffer = NULL;
       	}
       fclose(file);
    }
    getRenglones(buffer);
    return buffer;
}
int powW(int a,int b) 
{
	return b==0?1:a*powW(a,--b);
}

int getRThigh(int valor)
{
	int i;
	for(i=0;i<8;i++)
	{
		valor/=2;
	}
	return valor;
}
int getRTlow(int valor)
{
	int i,res=0;
	for(i=0;i<8;i++)
	{
		if(valor%2!=0)
		{
			res+=powW(2,i);
		}
		valor/=2;
	}
	return res;
}
void reverse(char s[])
{
     int i,j;
     char digit;
     for (i=0,j=strlen(s)-1;i<j;i++,j--)
     {
         digit=s[i];
         s[i]=s[j];
         s[j]=digit;
     }
}
char* itoa(int num, char* str, int base)
{
    int i = 0,sign = 0; 
    if (!num)//si es 0
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0 && base == 10)//base 10
    {
        sign = 1;
        num *= -1;
    }
    while (num != 0)// cambia si ocupa letras
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }
    if (sign) str[i++] = '-'; // si es negativo pone el -
    str[i] = '\0'; // le pone el final de str
    reverse(str);
    return str;
}
void actualizarRT(int a,int b,int c, int d)
{
	ax=a%65535;
	bx=b%65535;
	cx=c%65535;
	dx=d%65535;
}
void onBtoCnlClicked(GtkButton* button, gpointer func_data)
{
	gtk_widget_destroy (GTK_WIDGET(func_data));
}
void onBtoOKClicked(GtkButton* button, gpointer func_data)
{
	actualizarRT(atoi(gtk_entry_get_text(GTK_ENTRY(AXdec))),atoi(gtk_entry_get_text(GTK_ENTRY(BXdec))),atoi(gtk_entry_get_text(GTK_ENTRY(CXdec))),atoi(gtk_entry_get_text(GTK_ENTRY(DXdec))));
	gtk_widget_destroy (GTK_WIDGET(func_data));
}
static void ventanaIR()
{
	GtkWidget *window,*grid,*label;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	label = gtk_label_new(IR);

	gtk_widget_set_size_request(label,250,30);

	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_grid_attach(GTK_GRID(grid),label,0,0,1,1);

	gtk_window_set_title (GTK_WINDOW(window), "Registro de Instruccion");
  	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  	gtk_widget_show_all(window);
}
static void ventanaPC()
{
	GtkWidget *dialog,*entry;

 	dialog = gtk_dialog_new_with_buttons("Contador del Programa",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
  	entry = gtk_entry_new();
  	char tmp[3];

  	gtk_entry_set_text(GTK_ENTRY(entry),itoa(PC,tmp,10));
  	gtk_widget_set_size_request(entry,250,30);
  	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),entry,0,0,0);
  	gtk_widget_show_all(dialog);

  	gint response = gtk_dialog_run(GTK_DIALOG(dialog));

	if(response==GTK_RESPONSE_OK)
		PC=atoi(gtk_entry_get_text(GTK_ENTRY(entry)));

	gtk_widget_destroy(dialog);
}
static void ventanaRT()
{
	GtkWidget *window,*grid,*btoOK,*btoCnl,*lblCambios,*AX,*BX,*CX,*DX,*DEC,*HEX,*BIN,*AXhex,*AXbin,*BXhex,*BXbin,*CXhex,*CXbin,*DXhex,*DXbin;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	
	AXdec = gtk_entry_new();
	BXdec = gtk_entry_new();
	CXdec = gtk_entry_new();
	DXdec = gtk_entry_new();
	AX = gtk_label_new("AX");
	BX = gtk_label_new("BX");
	CX = gtk_label_new("CX");
	DX = gtk_label_new("DX");
	DEC = gtk_label_new("DEC");
	BIN = gtk_label_new("BIN");
	HEX = gtk_label_new("HEX");
	lblCambios = gtk_label_new("");
	btoOK = gtk_button_new_with_label("Ok");
	btoCnl = gtk_button_new_with_label("Cancel");
	char tmp[6];
	AXbin = gtk_label_new(itoa(ax,tmp,2));
	char tmp2[6];
	BXbin = gtk_label_new(itoa(bx,tmp2,2));
	char tmp3[6];
	CXbin = gtk_label_new(itoa(cx,tmp3,2));
	char tmp4[6];
	DXbin = gtk_label_new(itoa(dx,tmp4,2));
	char tmp5[6];
	AXhex = gtk_label_new(itoa(ax,tmp5,16));
	char tmp6[6];
	BXhex = gtk_label_new(itoa(bx,tmp6,16));
	char tmp7[6];
	CXhex = gtk_label_new(itoa(cx,tmp7,16));
	char tmp8[6];
	DXhex = gtk_label_new(itoa(dx,tmp8,16));
	
	char tmp9[6];
	gtk_entry_set_text(GTK_ENTRY(AXdec),itoa(ax,tmp9,10));
	char tmp10[6];
	gtk_entry_set_text(GTK_ENTRY(BXdec),itoa(bx,tmp10,10));
	char tmp11[6];
	gtk_entry_set_text(GTK_ENTRY(CXdec),itoa(cx,tmp11,10));
	char tmp12[6];
	gtk_entry_set_text(GTK_ENTRY(DXdec),itoa(dx,tmp12,10));

	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_grid_attach(GTK_GRID(grid),AX,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),BX,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),CX,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),DX,0,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),DEC,3,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),HEX,2,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),BIN,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),AXbin,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),AXhex,2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),AXdec,3,1,2,1);
	gtk_grid_attach(GTK_GRID(grid),BXbin,1,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),BXhex,2,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),BXdec,3,2,2,1);
	gtk_grid_attach(GTK_GRID(grid),CXbin,1,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),CXhex,2,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),CXdec,3,3,2,1);
	gtk_grid_attach(GTK_GRID(grid),DXbin,1,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),DXhex,2,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),DXdec,3,4,2,1);

	gtk_grid_attach(GTK_GRID(grid),lblCambios,3,5,2,1);

	gtk_grid_attach(GTK_GRID(grid),btoOK,3,6,1,1);
	gtk_grid_attach(GTK_GRID(grid),btoCnl,4,6,1,1);

	gtk_widget_set_size_request(AXbin,150,30);
	gtk_widget_set_size_request(AXhex,150,30);
	gtk_widget_set_size_request(AXdec,150,30);

	int ttmmpp[4];

	g_signal_connect(btoCnl,"clicked",G_CALLBACK(onBtoCnlClicked),window);
	g_signal_connect(btoOK,"clicked",G_CALLBACK(onBtoOKClicked),window);

	gtk_window_set_title (GTK_WINDOW(window), "Registros de Trabajo");
  	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  	gtk_widget_show_all(window);
}
static void ventanaFlags()
{
	GtkWidget *window,*grid,*lblSign,*lblCarry,*lblInterrupt,*lblZero,*carry,*sign,*interrupt,*zero;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	lblZero = gtk_label_new("ZeroFlag            ->");
	lblCarry = gtk_label_new("CarryFlag     ->");
	lblSign = gtk_label_new("SignFlag      ->");
	lblInterrupt = gtk_label_new("InterruptFlag ->");
	char t1[4],t2[4],t3[4],t4[4];
	interrupt = gtk_label_new(itoa(interruptF,t1,10));
	carry = gtk_label_new(itoa(carryF,t2,10));
	sign = gtk_label_new(itoa(signF,t3,10));
	zero = gtk_label_new(itoa(zeroF,t4,10));

	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_grid_attach(GTK_GRID(grid),lblCarry,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lblSign,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),carry,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),sign,1,1,1,1);

	gtk_grid_attach(GTK_GRID(grid),lblInterrupt,2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lblZero,2,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),interrupt,3,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),zero,3,0,1,1);

	gtk_widget_set_size_request(lblZero,75,30);
	gtk_widget_set_size_request(lblCarry,75,30);
	gtk_widget_set_size_request(lblSign,75,30);
	gtk_widget_set_size_request(lblInterrupt,75,30);

	gtk_widget_set_size_request(zero,40,30);
	gtk_widget_set_size_request(carry,40,30);
	gtk_widget_set_size_request(sign,40,30);
	gtk_widget_set_size_request(interrupt,40,30);

	gtk_window_set_title (GTK_WINDOW(window), "Banderas");
  	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  	gtk_widget_show_all(window);
}
static void ventanaALU()
{
	GtkWidget *window,*grid,*lblB1,*lblB2,*lblB3,*lblB4,*lB1,*lB2,*lB3,*lB4;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	lblB1 = gtk_label_new("B1   ->");
	lblB2 = gtk_label_new("B2   ->");
	lblB3 = gtk_label_new("B3   ->");
	lblB4 = gtk_label_new("B4   ->");
	char t1[2],t2[2],t3[2],t4[2];
	lB1 = gtk_label_new(itoa(B1,t1,10));
	lB2 = gtk_label_new(itoa(B2,t2,10));
	lB3 = gtk_label_new(itoa(B3,t3,10));
	lB4 = gtk_label_new(itoa(B4,t4,10));

	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_grid_attach(GTK_GRID(grid),lblB1,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lblB2,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lB1,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lB2,1,1,1,1);

	gtk_grid_attach(GTK_GRID(grid),lblB3,2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lblB4,2,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lB3,3,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lB4,3,0,1,1);

	gtk_widget_set_size_request(lblB1,50,30);
	gtk_widget_set_size_request(lblB2,50,30);
	gtk_widget_set_size_request(lblB3,50,30);
	gtk_widget_set_size_request(lblB4,50,30);

	gtk_widget_set_size_request(lB1,40,30);
	gtk_widget_set_size_request(lB2,40,30);
	gtk_widget_set_size_request(lB3,40,30);
	gtk_widget_set_size_request(lB4,40,30);

	gtk_window_set_title (GTK_WINDOW(window), "Unidad Aritmetologica");
  	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  	gtk_widget_show_all(window);
}
/*
MICROINSTRUCCIONES

Microinstrucciones mínimas de la AFOC:
X<-Y es la que permite mover datos del registro X al registro Y.
ALU: op ejecuta la operación correspondiente de la ALU (add, sub, mul, div, and, or, xor, not, shl o shr).
MEM: op ejecuta la operación de acceso a la memoria correspondiente (read o write)
TEST: flag, N bifurca a la instrucción N del microprograma si la bandera flag está encendida.
In abre una ventana y solicita un número que dejará almacenado en el MBR.
Out En la ventana de salida despliega el contenido del MBR.
*/

//Microinstruccion de mover de un registro a otro
void moverMicro(void)
{
	return;
}


//Micoinstruccion de mover a memoria


/*
ALU
*/
void mulAlu(void)
{
	B3 = B2 * B1;
	B2 = B1 = B4 = 0;
}

void sumAlu(void)
{
	B3 = B2 + B1;
	B2 = B1 = B4 = 0;
}

void restAlu(void)
{
	B3 = B2 + B1;
	B2 = B1 = B4 = 0;
}

void divAlu(void)
{
	B3 = B1 / B2; // Hay que revisar que el orden este bien
	B4 = B1 % B2;  // lo mismo
}

void andAlu(void)
{
	B3 = B1 & B2;
	B2 = B1 = B4 = 0;
}

void orAlu(void)
{
	B3 = B1 | B2;
	B2 = B1 = B4 = 0;
}

void xorAlu(void)
{
	B3 = B1 ^ B2;
	B2 = B1 = B4 = 0;
}

void notAlu(void)
{
	B3 = !B1;
	B2 = B1 = B4 = 0;
}

void shlAlu(void)
{
	B3 = B1 << B2;
	B2 = B1 = B4 = 0;
}

void shrAlu(void)
{
	B3 = B1 >> B2;
	B2 = B1 = B4 = 0;
}


//Esto no es lo que el profe explico 
void mov(char registro, char altBjo, int num)
{
	int temp;
	switch(registro)
	{
		case 'a': 
			switch(altBjo)
			{
				case 'h':
					ah = num;
					temp = ax;
					ax = ah;
					ax = ax << 8; //
					break;
				case 'l':
					al = num;
					break;
				case 'x':
					ax = num;
					break;
			}
			break;
	}
}