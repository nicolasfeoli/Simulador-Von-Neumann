#include "structs.h"

void excInstruccion(char reg[],int programCounter)
{
	char ins[5],par1[5],par2[5],tmp[3];
	memset(&ins[0], 0, sizeof(ins));
	memset(&par1[0], 0, sizeof(par1));
	memset(&par2[0], 0, sizeof(par2));
	int index=0, i, tipo = 1, instruccion = 0 ,parametro1 = 0, parametro2 = 0, cuartoDato = 0;
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
					ins[index++]=reg[i];
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
	if(1){//instrucciones
		if(!strcmp(ins,"mov"))
		{
			instruccion = 0;
		}
		else if(!strcmp(ins,"add"))
		{
			instruccion = 2;
		}
		else if(!strcmp(ins,"cmp"))
		{
			instruccion = 4;
		}
		else if(!strcmp(ins,"jz"))
		{
			instruccion = 6;
		}
		else if(!strcmp(ins,"jmp"))
		{
			instruccion = 7;
		}
		else if(!strcmp(ins,"out"))
		{
			instruccion = 8;
		}
		else if(!strcmp(ins,"in"))
		{
			instruccion = 9;
		}
		else if(!strcmp(ins,"sti"))
		{
			instruccion = 10;
		}	
		else if(!strcmp(ins,"cli"))
		{
			instruccion = 11;
		}
		else{
			printf("%s\n", "#ERROR");
			printf("%i\n", programCounter); 
		}
	}
	if(1)   // parametro 1
	{
		if(par1[0]>=0x30 && par1[0]<=0x39 )
		{
			if(instruccion == 7 || instruccion == 6){
				cuartoDato = atoi(par1);
				parametro1 = 15;
			}
			else
			{
				printf("%s\n", "#ERROR");
				printf("%i\n", programCounter); 
			}
		}
		else
		{
			switch(par1[0])
			{
				case 'a': 
					switch(par1[1])
					{
						case 'x':
							parametro1 = 0;
							break;
						case 'l':
							parametro1 = 4;
							break;
						case 'h':
							parametro1 = 8;
							break;
					}
					break;
				case 'b': 
					switch(par1[1])
					{
						case 'x':
							parametro1 = 1;
							break;
						case 'l':
							parametro1 = 5;
							break;
						case 'h':
							parametro1 = 9;
							break;
					}
					break;
				case 'c': 
					switch(par1[1])
					{
						case 'x':
							parametro1 = 2;
							break;
						case 'l':
							parametro1 = 6;
							break;
						case 'h':
							parametro1 = 10;
							break;
					}
					break;
				case 'd': 
					switch(par1[1])
					{
						case 'x':
							parametro1 = 3;
							break;
						case 'l':
							parametro1 = 7;
							break;
						case 'h':
							parametro1 = 11;
							break;
					}
					break;
				case '[':
					switch(par1[1])
					{
						case 'b':
							switch(par1[2])
							{
								case 'h':
									if(par1[3]==']')
										parametro1 = 14;
									else{
										printf("%s\n","#ERROR" );
										printf("%i\n", programCounter); 
									}
									break;
								case 'l':
									if(par1[3]==']')
										parametro1 = 13;
									else{
										printf("%s\n","#ERROR" );
										printf("%i\n", programCounter); 
									}
									break;
								default:
									printf("%s\n","#ERROR" );
									printf("%i\n", programCounter); 
							}
							break;
						default: 
							if(par1[1]>=0x30 && par1[1]<=0x39)
							{
								memset(&tmp[0], 0, sizeof(tmp));
								tmp[0]=par1[1];
								tmp[1]=par1[2];
								tmp[2]=par1[3];
								cuartoDato = atoi(tmp);
								parametro1 = 12;
							}
							else{
								printf("%s\n","#ERROR" );
								printf("%i\n", programCounter); 
							}
					}
					break;
				default:
					if(instruccion == 11 || instruccion == 10){
						printf("%s\n", "no tiene parametro 1");
						printf("%i\n", programCounter); 
					}
					else{
						printf("%s\n", "#ERROR");
						printf("%i\n", programCounter); 
					}
			}
		}
	}
	if(1)//parametro 2
	{
		if(par2[0]>=0x30 && par2[0]<=0x39 )
		{
			if(instruccion >= 0 && instruccion <= 5){
				cuartoDato = atoi(par2);
				parametro2 = 15;
			}
			else
			{
				printf("%s\n", "#ERROR");
				printf("%i\n", programCounter); 
			}
		}
		else
		{
			switch(par2[0])
			{
				case 'a': 
					switch(par2[1])
					{
						case 'x':
							parametro2 = 0;
							break;
						case 'l':
							parametro2 = 4;
							break;
						case 'h':
							parametro2 = 8;
							break;
					}
					break;
				case 'b': 
					switch(par2[1])
					{
						case 'x':
							parametro2 = 1;
							break;
						case 'l':
							parametro2 = 5;
							break;
						case 'h':
							parametro2 = 9;
							break;
					}
					break;
				case 'c': 
					switch(par2[1])
					{
						case 'x':
							parametro2 = 2;
							break;
						case 'l':
							parametro2 = 6;
							break;
						case 'h':
							parametro2 = 10;
							break;
					}
					break;
				case 'd': 
					switch(par2[1])
					{
						case 'x':
							parametro2 = 3;
							break;
						case 'l':
							parametro2 = 7;
							break;
						case 'h':
							parametro2 = 11;
							break;
					}
					break;
				case '[':
					switch(par2[1])
					{
						case 'b':
							switch(par2[2])
							{
								case 'h':
									if(par2[3]==']')
										parametro2 = 14;
									else{
										printf("%s\n","#ERROR" );
										printf("%i\n", programCounter); 
									}
									break;
								case 'l':
									if(par2[3]==']')
										parametro2 = 13;
									else{
										printf("%s\n","#ERROR" );
										printf("%i\n", programCounter); 
									}
									break;
								default:
									printf("%s\n","#ERROR" );
									printf("%i\n", programCounter); 
							}
							break;
						default: 
							if(par2[1]>=0x30 && par2[1]<=0x39)
							{
								memset(&tmp[0], 0, sizeof(tmp));
								tmp[0]=par2[1];
								tmp[1]=par2[2];
								tmp[2]=par2[3];
								cuartoDato = atoi(tmp);
								parametro2 = 12;
							}
							else{
								printf("%s\n","#ERROR" );
								printf("%i\n", programCounter); 
							}
					}
					break;
				default:
					if(instruccion >= 6 || instruccion <= 11){
						printf("%s\n", "no tiene parametro 2");
						printf("%i\n", programCounter); 
					}
					else{
						printf("%s\n", "#ERROR");
						printf("%i\n", programCounter); 
					}
			}
		}	
	}

	if((parametro1>=12 && parametro1<=14 && parametro2>=12 && parametro2<=14 )||(parametro1>=4 && parametro1<=11 && parametro2>=0 && parametro2<=3)||(parametro2>=4 && parametro2<=11 && parametro1>=0 && parametro1<=3))
	{
		printf("%s\n", "#ERROR");
		printf("%i\n", programCounter); 
	}
	else{
		printf("%s\n", "todo salio perfect"); 
	}
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
	for(PC = 0;PC<24;PC++)
		excInstruccion(prog[PC],PC); 
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
int powW(int a,int b) {return b==0?1:a*powW(a,--b);}
	
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


/*
ALU
*/
void mulAlu(void)
{
	B3 = B2 * B1;
	if(!B3) zeroF = 1;
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	B2 = B1 = B4 = 0;
}

void sumAlu(void)
{
	B3 = B2 + B1;
	if(!B3) zeroF = 1;
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) carryF = signF = 1;
	else carryF = signF = 0;
	B2 = B1 = B4 = 0;
}

void restAlu(void)
{
	B3 = B1-B2;
	if(B3 < 0) carryF = signF = 1;
	else carryF = signF = 0;
	if(!B3) zeroF = 1;
	else zeroF = 0;
	B2 = B1 = B4 = 0;
}

void divAlu(void)
{
	if(!B2) ventanaError("Division por Cero");
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

void hola()
{
	MAR = 4;
}

void mov (int codigo1, int codigo2, int cuartoDato)
{
	switch(codigo2){
		case 0:
			BD = ax; //BD<-ax
			break;
		case 1:
			BD = bx;
			break;
		case 2:
			BD = cx;
			break;
		case 3:
			BD = dx;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 15:
			BD  = PC;
			MAR = BD;
			MEM(LECTURA);
			BD  = cuartoDato;
	}
	switch(codigo1){
		case 0:
			ax = BD;
			break;
		case 1:
			bx = BD;
			break;
		case 2:
			cx = BD;
			break;
		case 3:
			dx = BD;
			break;
		case 12:
			MBR = BD;
			BD  = PC;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[cuartoDato1]->cuartoDato = BD;
			break;
		case 13:
			MBR = BD;
			BD  = bl;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[bl]->cuartoDato = BD;
			break;
		case 14:
			MBR = BD;
			BD  = bh;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[bh]->cuartoDato = BD;
			break;
	}
}

void add(int codigo1, int codigo2, int cuartoDato)
{
	switch(codigo2){
		case 0:
			BD = ax;
			break;
		case 1:
			BD = bx;
			break;
		case 2:
			BD = cx;
			break;
		case 3:
			BD = dx;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
	}
	B1 = BD;
	switch(codigo1){
		case 0:
			BD = ax; 
			break;
		case 1:
			BD = bx;
			break;
		case 2:
			BD = cx;
			break;
		case 3:
			BD = dx;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
	}
	B2 = BD;
	sumAlu();
	BD = B3;
	switch(codigo1){
		case 0:
			ax = BD;
			break;
		case 1:
			bx = BD;
			break;
		case 2:
			cx = BD;
			break;
		case 3:
			dx = BD;
			break;
		case 12:
			MBR = BD;
			BD  = cuartoDato;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[cuartoDato1]->cuartoDato = BD;
			break;
		case 13:
			MBR = BD;
			BD  = bl;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[bl]->cuartoDato = BD;
			break;
		case 14:
			MBR = BD;
			BD  = bh;
			MAR = BD;
			MEM(ESCRITURA);
			//memoria[bl]->cuartoDato = BD;
			break;
	}
}

void cmp(int codigo1, int codigo2, int cuartoDato)
{
	switch(codigo2){
		case 0:
			BD = ax; //BD<-ax
			break;
		case 1:
			BD = bx;
			break;
		case 2:
			BD = cx;
			break;
		case 3:
			BD = dx;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 15:
			BD  = PC;
			MAR = BD;
			MEM(LECTURA);
			BD  = cuartoDato;
	}
	B1 = BD;
	switch(codigo1){
		case 0:
			BD = ax; //BD<-ax
			break;
		case 1:
			BD = bx;
			break;
		case 2:
			BD = cx;
			break;
		case 3:
			BD = dx;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			//MBR = memoria[MAR]->cuartoDato;
			BD  = MBR;
			break;
		case 15:
			BD  = PC;
			MAR = BD;
			MEM(LECTURA);
			BD  = cuartoDato;
	}
	B2 = BD;
	restAlu();
}

void test(int flag, int salto)
{
	switch(flag)
	{
		case 0:
			if(carryF)
				PC = salto;
			break;
		case 1:
			if(signF)
				PC = salto;
			break;
		case 2:
			if(zeroF)
				PC = salto;
			break;
		case 3:
			if(interruptF)
				PC = salto;
			break;
	}
}

void in()
{
	printf("Microinstruccion in. Dato entrada: ");
	scanf("%d", &MBR);
}

void out()
{
	printf("Microinstruccion out. Dato salida: %d\n", MBR);
}

//Esta Microinstruccion escribe en [MAR] lo que esta en MBR
//  o lee de [MAR] y lo guarda en MBR
void MEM(int operacion)
{	
	//Si operacion es 1 -> read
	if(operacion)
		MBR = memoria[MAR]->cuartoDato;
	else
		memoria[MAR]-> cuartoDato = MBR;
}

void cli()
{
	interruptF = 0;
}

void sti()
{
	interruptF = 1;
}

void cicloFetch()
{
	//Subciclo busqueda
	BD = PC;      //BD  <- PC
	MAR = BD;     //MAR <- BD
	MEM(LECTURA); //READ
	BD = MBR;     //BD  <- MBR
	IR = BD;      //IR  <- BD
	PC++;         //inc PC

	//Subciclo de Decodificacion
	//Aqui no va nada porque en teoria ya lo tenemos 

	//Subciclo indirecto
	//Esto se lleva a cabo durante la ejecucion de la instrucion

	//	
	//Subciclo de ejecucion

	switch(codigoOp)

}

/*
//Este mov es el de r/m -> r/m
void mov(int codigo1, int codigo2, int cuartoDato)
{
	int temp;
	switch(codigo1)
	{
		case 0:
			// codigo ax
			switch(codigo2)
			{
				case 0:
					//mov ax, ax
					// no hace nada?
					ax = ax;
					break;
				case 1:
					//mov ax, bx
					ax = bx;
					break;
				case 2:
					//mov ax, cx
					ax = cx;
					break;
				case 3:
					//mov ax, dx
					ax = dx;
					break;
				//Se saltan los valores [4,11] pues se asume que nunca viene algo asi
				case 12:
					//mov ax,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ax  = BD;
					break;
				case 13:
					//mov ax, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ax  = BD; 
					break;
				case 14:
					//mov ax, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ax  = BD; 
					break;
			}
			break;
		case 1:
			//codigo bx
			switch(codigo2)
			{
				case 0:
					//mov bx, ax
					bx = ax;
					break;
				case 1:
					//mov bx, bx
					//no hace nada?
					bx = bx;
					break;
				case 2:
					//mov bx, cx
					bx = cx;
					break;
				case 3:
					//mov bx, dx
					bx = dx;
					break;
				//Se saltan los valores [4,11] pues se asume que nunca viene algo asi
				case 12:
					//mov bx,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bx  = BD;
					break;
				case 13:
					//mov bx, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bx  = BD; 
					break;
				case 14:
					//mov bx, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bx  = BD; 
					break;
			break;
		case 2:
			//codigo cx
			switch(codigo2)
			{
				case 0:
					//mov cx, ax
					cx = ax;
					break;
				case 1:
					//mov cx, bx
					cx = bx;
					break;
				case 2:
					//mov cx, cx
					//no hace nada?
					cx = cx;
					break;
				case 3:
					//mov cx, dx
					cx = dx;
					break;
				//Se saltan los valores [4,11] pues se asume que nunca viene algo asi
				case 12:
					//mov cx,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cx  = BD;
					break;
				case 13:
					//mov cx, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cx  = BD; 
					break;
				case 14:
					//mov cx, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cx  = BD; 
					break;
			break;
		case 3:
			//codigo dx
			switch(codigo2)
			{
				case 0:
					//mov dx, ax
					dx = ax;
					break;
				case 1:
					//mov dx, bx
					dx = bx;
					break;
				case 2:
					//mov dx, cx
					dx = cx;
					break;
				case 3:
					//mov dx, dx
					//no hace nada?
					dx = dx;
					break;
				//Se saltan los valores [4,11] pues se asume que nunca viene algo asi
				case 12:
					//mov dx,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dx  = BD;
					break;
				case 13:
					//mov dx, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dx  = BD; 
					break;
				case 14:
					//mov dx, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dx  = BD; 
					break;
			break;
		case 4:
			//codigo al
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov al, al
					//no hace nada?
					al = al;
					break;
				case 5:
					//mov al, bl
					al = bl;
					break;
				case 6:
					//mov al, cl
					al = cl;
					break;
				case 7:
					//mov al, dl
					al = dl;
					break;
				case 8:
					//mov al, ah
					al = ah;
					break;
				case 9:
					//mov al, bh
					al = bh;
					break;
				case 10:
					//mov al, ch
					al = ch;
					break;
				case 11:
					//mov al, dh
					al = dh;
					break;
				case 12:
					//mov al,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					al  = BD;
					break;
				case 13:
					//mov al, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					al  = BD; 
					break;
				case 14:
					//mov al, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					al  = BD; 
					break;
			break;
		case 5:
			//codigo bl
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov bl, al
					bl = al;
					break;
				case 5:
					//mov bl, bl
					//no hace nada?
					bl = bl;
					break;
				case 6:
					//mov bl, cl
					bl = cl;
					break;
				case 7:
					//mov bl, dl
					bl = dl;
					break;
				case 8:
					//mov bl, ah
					bl = ah;
					break;
				case 9:
					//mov bl, bh
					bl = bh;
					break;
				case 10:
					//mov bl, ch
					bl = ch;
					break;
				case 11:
					//mov bl, dh
					bl = dh;
					break;
				case 12:
					//mov bl,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD;
					break;
				case 13:
					//mov bl, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD; 
					break;
				case 14:
					//mov bl, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD; 
					break;
			break;
		case 6:
			//codigo cl
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov cl, al
					cl = al;
					break;
				case 5:
					//mov cl, bl
					cl = bl;
					break;
				case 6:
					//mov cl, cl
					//no hace nada?
					cl = cl;
					break;
				case 7:
					//mov cl, dl
					cl = dl;
					break;
				case 8:
					//mov cl, ah
					cl = ah;
					break;
				case 9:
					//mov cl, bh
					cl = bh;
					break;
				case 10:
					//mov cl, ch
					cl = ch;
					break;
				case 11:
					//mov cl, dh
					cl = dh;
					break;
				case 12:
					//mov cl,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cl  = BD;
					break;
				case 13:
					//mov cl, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cl  = BD; 
					break;
				case 14:
					//mov cl, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					cl  = BD; 
					break;
			break;
		case 7:
			//codigo dl
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov dl, al
					dl = al;
					break;
				case 5:
					//mov dl, bl
					dl = bl;
					break;
				case 6:
					//mov dl, cl
					dl = cl;
					break;
				case 7:
					//mov dl, dl
					//no hace nada?
					dl = dl;
					break;
				case 8:
					//mov dl, ah
					dl = ah;
					break;
				case 9:
					//mov dl, bh
					dl = bh;
					break;
				case 10:
					//mov dl, ch
					dl = ch;
					break;
				case 11:
					//mov dl, dh
					dl = dh;
					break;
				case 12:
					//mov dl,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dl  = BD;
					break;
				case 13:
					//mov dl, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dl  = BD; 
					break;
				case 14:
					//mov dl, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					dl  = BD; 
					break;
			break;
		case 8:
			//codigo ah
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov ah, al
					ah = al;
					break;
				case 5:
					//mov ah, bl
					ah = bl;
					break;
				case 6:
					//mov ah, cl
					ah = cl;
					break;
				case 7:
					//mov ah, dl
					ah = dl;
					break;
				case 8:
					//mov ah, ah
					//no hace nada?
					ah = ah;
					break;
				case 9:
					//mov ah, bh
					ah = bh;
					break;
				case 10:
					//mov ah, ch
					ah = ch;
					break;
				case 11:
					//mov ah, dh
					ah = dh;
					break;
				case 12:
					//mov ah,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ah  = BD;
					break;
				case 13:
					//mov ah, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ah  = BD; 
					break;
				case 14:
					//mov ah, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					ah  = BD; 
					break;
			break;
		case 9:
			//codigo bh
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov bh, al
					bh = al;
					break;
				case 5:
					//mov bh, bl
					//no hace nada?
					bh = bl;
					break;
				case 6:
					//mov bh, cl
					bh = cl;
					break;
				case 7:
					//mov bh, dl
					bh = dl;
					break;
				case 8:
					//mov bh, ah
					bh = ah;
					break;
				case 9:
					//mov bh, bh
					bh = bh;
					break;
				case 10:
					//mov bh, ch
					bh = ch;
					break;
				case 11:
					//mov bh, dh
					bh = dh;
					break;
				case 12:
					//mov bh,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bh  = BD;
					break;
				case 13:
					//mov bh, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bh  = BD; 
					break;
				case 14:
					//mov bh, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bh  = BD; 
					break;
			break;
		case 10:
			//codigo ch
			switch(codigo2)
			{
				//Se saltan los valores [0,3] pues se asume que nunca viene algo asi
				case 4:
					//mov bl, al
					bl = al;
					break;
				case 5:
					//mov bl, bl
					//no hace nada?
					bl = bl;
					break;
				case 6:
					//mov bl, cl
					bl = cl;
					break;
				case 7:
					//mov bl, dl
					bl = dl;
					break;
				case 8:
					//mov bl, ah
					bl = ah;
					break;
				case 9:
					//mov bl, bh
					bl = bh;
					break;
				case 10:
					//mov bl, ch
					bl = ch;
					break;
				case 11:
					//mov bl, dh
					bl = dh;
					break;
				case 12:
					//mov bl,[dir]
					BD  = cuartoDato;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD;
					break;
				case 13:
					//mov bl, [bl]
					BD  = bl;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD; 
					break;
				case 14:
					//mov bl, [bh]
					BD  = bh;
					MAR = BD;
					MBR = memoria[MAR];
					BD  = MBR;
					bl  = BD; 
					break;
			break;
		case 11:
			//codigo dh
			switch(codigo2)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
			break;
		case 12:
			switch(codigo2)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
			break;
		case 13:
			switch(codigo2)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
			break;
		case 14:
			switch(codigo2)
			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
				case 13:
					break;
				case 14:
					break;
			break;
}
*/
/*
case 4:
					//Tirar error
					// diferentes tamaños
					break;
				case 5:
					//Tirar error
					// diferentes tamaños
					break;
				case 6:
					//Tirar error
					// diferentes tamaños
					break;
				case 7:
					//Tirar error
					// diferentes tamaños
					break;
				case 8:
					//Tirar error
					// diferentes tamaños
					break;
				case 9:
					//Tirar error
					// diferentes tamaños
					break;
				case 10:
					//Tirar error
					// diferentes tamaños
					break;
				case 11:
					//Tirar error
					// diferentes tamaños
					break;*/
