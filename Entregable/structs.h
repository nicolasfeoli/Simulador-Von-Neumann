#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <gtk/gtk.h>

#define LECTURA 1
#define ESCRITURA 0


typedef struct {
	int codigoOp;
	int operando1;
	int operando2;
	int cuartoDato;
} celda;

static char prog[256][500];

celda* memoria[256];
celda  arregloMemoriaArchivo[256];

char * IR = "", 
	* buff = "", 
	* programa;

int globalTamano = 0, 
	size = 0, 
	lineasPrograma = 0, 
	IR_fetch,
	seg = 0,
	i;

static int PC = 0,
	ah,al,ax  = 0,
	bh,bl,bx  = 0,
	ch,cl,cx  = 0,
	dl,dh,dx  = 0,
	zeroF      = 0, signF  = 0,
	interruptF = 0, carryF = 0,
	B1 =0,B2=0,B3=0,B4=0,BD =0, MAR=0, MBR=0;

GtkWidget *AXdec,
		*BXdec,
		*CXdec,
		*DXdec, 
		*entrada,
		*btoPlay,
		*btoStep;

GtkTextBuffer * gtkbuffer2,
		* gtkbuffer;

void ventanaSimulador();
void ventanaAcercaDe();
void ventanaAyuda();
void play();
void step();
void reset();
void resetALL();
GtkWidget * createConsoleBox();
gchar * getTextBuffer();
void clearBuffer();
void concatBuffer();
void reverse();
char * itoa();
void onBtoListoClicked();
void onBtoInterruptClicked();
void ventanaError();
void ventanaInterrupt();
void excInstruccion();
void getRenglones();
gchar * get_dialog_path_selection();
void abrirArchivo();
int powW();
int getRThigh();
int getRTlow();
void actualizarRT();
void onBtoCnlClicked();
void ventanaIR();
void ventanaPC();
void ventanaRT();
void ventanaFlags();
void ventanaALU();
void ventanaMMB();
void mulAlu();
void sumAlu();
void restAlu();
void divAlu();
void andAlu();
void orAlu();
void xorAlu();
void notAlu();
void shlAlu();
void shrAlu();
void mov();
void add();
void cmp();
void test();
void inMicro();
void outMicro();
void MEM();
void cli();
void sti();
void in();
void out();
void jz();
void jmp();
void cicloFetch();
void actualizarRegistroX();
void actualizarRegistroLH();
void guardarAFOC();
void cargarAFOC();




void ventanaSimulador()
{
  GtkWidget *btoListo,*btoCargar,*btoInt,*btoGuardar,*btoReset,*txtCode,*p,*consola,*dialog,*label,*grid,*btoUC,*btoIR,*btoPC,*btoBD,*btoRT,*btoFlag,*btoALU,*btoMR;
  
  gtkbuffer = gtk_text_buffer_new(NULL);
  gtkbuffer2 = gtk_text_buffer_new(NULL);

  p=createConsoleBox(gtkbuffer,buff,size);
  consola= createConsoleBox(gtkbuffer2,"",0);

  dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  label = gtk_label_new("ARQUITECTURA VON NEWMAN");
  grid = gtk_grid_new();
  btoUC = gtk_button_new_with_label("UC");
  btoIR = gtk_button_new_with_label("IR");
  btoPC = gtk_button_new_with_label("PC");
  btoBD = gtk_button_new_with_label("BD");
  btoRT = gtk_button_new_with_label("RT");
  btoFlag = gtk_button_new_with_label("Flags");
  btoALU = gtk_button_new_with_label("ALU");
  btoMR = gtk_button_new_with_label("MAR\nMBR");
  btoPlay = gtk_button_new_with_label("Play");
  btoStep = gtk_button_new_with_label("Step");
  btoReset = gtk_button_new_with_label("Reset");
  btoListo = gtk_button_new_with_label("Ok");
  btoGuardar =  gtk_button_new_with_label("Guardar");
  btoCargar =  gtk_button_new_with_label("Cargar");
  btoInt =  gtk_button_new_with_label("Int");
  entrada = gtk_entry_new();


  gtk_container_add(GTK_CONTAINER(dialog),grid);
  gtk_grid_attach(GTK_GRID(grid),label,1,0,4,1);/*COL,FILA,COL,FILA*/
  gtk_grid_attach(GTK_GRID(grid),btoUC,2,3,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoIR,2,1,1,2);
  gtk_grid_attach(GTK_GRID(grid),btoPC,2,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoBD,3,1,1,4);
  gtk_grid_attach(GTK_GRID(grid),btoRT,4,1,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoFlag,4,2,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoALU,4,3,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoMR,4,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoInt,5,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),p,6,1,2,4);
  gtk_grid_attach(GTK_GRID(grid),consola,0,1,2,4);
  gtk_grid_attach(GTK_GRID(grid),btoCargar,6,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoGuardar,7,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoPlay,2,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoStep,3,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoReset,4,5,2,1);
  gtk_grid_attach(GTK_GRID(grid),entrada,0,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoListo,1,5,1,1);
  gtk_widget_set_size_request(btoUC,50,100);
  gtk_widget_set_size_request(p,250,100);
  gtk_widget_set_size_request(consola,250,100);
  gtk_widget_set_size_request(btoIR,100,100);
  gtk_widget_set_size_request(btoPC,50,100);
  gtk_widget_set_size_request(btoBD,100,70);
  gtk_widget_set_size_request(btoRT,50,100);
  gtk_widget_set_size_request(btoFlag,50,100);
  gtk_widget_set_size_request(btoALU,50,100);
  gtk_widget_set_size_request(btoMR,50,50);
  g_signal_connect(btoIR,"clicked",G_CALLBACK(ventanaIR),dialog);
  g_signal_connect(btoPC,"clicked",G_CALLBACK(ventanaPC),dialog);
  g_signal_connect(btoRT,"clicked",G_CALLBACK(ventanaRT),dialog);
  g_signal_connect(btoFlag,"clicked",G_CALLBACK(ventanaFlags),dialog);
  g_signal_connect(btoALU,"clicked",G_CALLBACK(ventanaALU),dialog);
  g_signal_connect(btoPlay,"clicked",G_CALLBACK(play),NULL);
  g_signal_connect(btoStep,"clicked",G_CALLBACK(step),NULL);
  g_signal_connect(btoReset,"clicked",G_CALLBACK(reset),NULL);
  g_signal_connect(btoListo,"clicked",G_CALLBACK(onBtoListoClicked),NULL);
  g_signal_connect(btoCargar,"clicked",G_CALLBACK(cargarAFOC),NULL);
  g_signal_connect(btoMR,"clicked",G_CALLBACK(ventanaMMB),NULL);
  g_signal_connect(btoInt,"clicked",G_CALLBACK(onBtoInterruptClicked),NULL);
  g_signal_connect(btoGuardar,"clicked",G_CALLBACK(guardarAFOC),NULL);

  gtk_widget_set_sensitive (btoUC, FALSE);
  gtk_widget_set_sensitive (btoBD, FALSE);
  /*gtk_widget_set_sensitive (p, FALSE);
  gtk_widget_set_sensitive (consola, FALSE);*/
  gtk_window_set_title (GTK_WINDOW(dialog), "Simulador");
  gtk_window_set_resizable (GTK_WINDOW(dialog), FALSE);
  gtk_widget_show_all(dialog);
}

void ventanaAyuda()
{
  GtkWidget *dialog,*label,*lblerr;
  dialog = gtk_dialog_new_with_buttons("AYUDA",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
  label = gtk_label_new("AYUDA:\n Para iniciar una simulación, seleccione un archivo que contenga código ensamblador.\nLuego toque el botón llamado abrir ventana, para dar inicio a la simulación.\n Para más información y ayuda revise el manual de usuario:\nhttp://bit.ly/2gFMfpy");
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),label,0,0,0);
  gtk_widget_show_all(dialog);
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void ventanaAcercaDe()
{
  GtkWidget *dialog,*label,*lblerr;
  dialog = gtk_dialog_new_with_buttons("ACERCA DE",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
  label = gtk_label_new("-------------------------------------------------------------------------------------------\n       -SIMULADOR ARQUITECTURA VON NEUMANN -\n-------------------------------------------------------------------------------------------\nHECHO POR:\n\tJUAN DE DIOS MARTINEZ CEDEÑO\n\tNICOLAS FEOLI CHACON\n-------------------------------------------------------------------------------------------\n LENGUAJES DE PROGRAMACION\n\tKIRSTEIN GÄTJENS\n\tGRUPO 2");
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),label,0,0,0);
  gtk_widget_show_all(dialog);
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
void play()
{
	while(PC!=lineasPrograma){
		if(memoria[PC]->codigoOp == 9){
			gtk_widget_set_sensitive (btoPlay, FALSE);
			gtk_widget_set_sensitive (btoStep, FALSE);
			concatBuffer(gtkbuffer2, "Inserte el valor para el registro: ");
			break;
		}
		cicloFetch();
	}
}
void step()
{
	if(memoria[PC]->codigoOp == 9){
		gtk_widget_set_sensitive (btoPlay, FALSE);
		gtk_widget_set_sensitive (btoStep, FALSE);
		concatBuffer(gtkbuffer2, "Inserte el valor para el registro: ");		
	}
	else
		cicloFetch();
}
void reset()
{
	int tp = 0;
	for(;tp<256;tp++)
	{
		memoria[tp]->codigoOp = memoria[tp]->operando1 = memoria[tp]->operando2 = memoria[tp]->cuartoDato = 0;
	}

	i = 0;

	IR = "";
	buff = "";
	PC = ah = al = ax = bh = seg = bl = bx = ch = cl = cx = dh = dl = dx = zeroF = signF = interruptF = carryF = 0;
	B1 = B2 = B3 = B4 = BD = MAR = MBR = 0;

	clearBuffer(gtkbuffer2);
	getRenglones(programa);
}
void resetALL()
{
	int tp = 0;
	int t = 0;
	for(;tp<256;tp++)
	{
		memoria[tp]->codigoOp = memoria[tp]->operando1 = memoria[tp]->operando2 = memoria[tp]->cuartoDato = 0;
		arregloMemoriaArchivo[tp].codigoOp = arregloMemoriaArchivo[tp].operando1 = arregloMemoriaArchivo[tp].operando2 = arregloMemoriaArchivo[tp].cuartoDato = 0;
		memset(&prog[tp][0], 0, sizeof(prog[tp]));
	}

	i = 0;

	IR = "";
	buff = "";
	PC = ah = al = ax = bh = seg = bl = bx = ch = cl = cx = dh = dl = dx = zeroF = signF = interruptF = carryF = 0;
	B1 = B2 = B3 = B4 = BD = MAR = MBR = 0;

	clearBuffer(gtkbuffer2);
	clearBuffer(gtkbuffer);

	programa = (char*)malloc(10000);

	globalTamano = 0;/**/

	size = lineasPrograma = 0;
	IR_fetch=0;
	seg=0;
}
GtkWidget* createConsoleBox(GtkTextBuffer * gtkbuffer,char* b,int s)
{
    gtk_text_buffer_set_text(gtkbuffer,b,s);
    GtkWidget* textArea = gtk_text_view_new_with_buffer(gtkbuffer);
    GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget* console = gtk_table_new(3, 1, FALSE);
    

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
    gtk_table_attach_defaults(GTK_TABLE(console), scrolledwindow, 0, 1, 0, 1);

    return console;
}
gchar* getTextBuffer(GtkTextBuffer* gtkbuffer){
    GtkTextIter start, end;
    gchar *text;
    gtk_text_buffer_get_bounds (gtkbuffer, &start, &end);
    text = gtk_text_buffer_get_text (gtkbuffer, &start, &end, FALSE);
    return text;
}
void clearBuffer(GtkTextBuffer * gtkbf)
{
	gtk_text_buffer_set_text(gtkbf," ",0);
}
void concatBuffer(GtkTextBuffer * gtkbf,gchar* str)
{
    gchar* qwe = g_strconcat(getTextBuffer(gtkbf),str,"\n",NULL);
    gtk_text_buffer_set_text(gtkbf,qwe,strlen(qwe));
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
    if (!num)/*si es 0*/
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0 && base == 10)/*base 10*/
    {
        sign = 1;
        num *= -1;
    }
    while (num != 0)/* cambia si ocupa letras*/
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }
    if (sign) str[i++] = '-'; /* si es negativo pone el - */
    str[i] = '\0'; /* le pone el final de str*/
    reverse(str);
    return str;
}
void onBtoListoClicked()
{
	gtk_widget_set_sensitive (btoPlay, TRUE);
	gtk_widget_set_sensitive (btoStep, TRUE);
	cicloFetch();
	gtk_entry_set_text(GTK_ENTRY(entrada),"");
}
void onBtoInterruptClicked()
{
	interruptF = 1;
}
void ventanaError(int pp,char*err)
{
  GtkWidget *dialog,*label,*lblerr;
  dialog = gtk_dialog_new_with_buttons("ERROR",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
  char e[3];
  label = gtk_label_new(itoa(pp+1,e,10));
  lblerr = gtk_label_new(err);
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),label,0,0,0);
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),lblerr,0,0,0);
  gtk_widget_show_all(dialog);
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void ventanaInterrupt()
{
  GtkWidget *dialog,*label;
  dialog = gtk_dialog_new_with_buttons("ERROR",NULL,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
  label = gtk_label_new("Interrupción creada");
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),label,0,0,0);
  gtk_widget_show_all(dialog);
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));

  gtk_widget_destroy(dialog);


}
void excInstruccion(char reg[],int programCounter)
{

	char ins[5],par1[5],par2[5],tmp[3];
	memset(&ins[0], 0, sizeof(ins));
	memset(&par1[0], 0, sizeof(par1));
	memset(&par2[0], 0, sizeof(par2));
	int index=0, i, tipo = 1, instruccion = -1 ,parametro1 = -1, parametro2 = -1, cuartoDato = -1, band = 1;
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
	if(1){/*instrucciones*/
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
		else
		{
			if(strcmp(ins,"")) ventanaError(programCounter,"Funcion no existe.");
			band = 0;
		}
	}
	if(band)   /* parametro 1*/
	{
		if((par1[0]>=0x30 && par1[0]<=0x39)||par1[0]=='-')
		{
			if(instruccion == 7 || instruccion == 6){
				cuartoDato = atoi(par1);
				parametro1 = 15;
			}
			else
			{
				ventanaError(programCounter,"Primer parametro no puede ser inmediato.");
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
										ventanaError(programCounter,"Hace falta ].");
									}
									break;
								case 'l':
									if(par1[3]==']')
										parametro1 = 13;
									else{
										ventanaError(programCounter,"Hace falta ]."); 
									}
									break;
								default:
									ventanaError(programCounter,"Parametro 1 no existe.");
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
								ventanaError(programCounter,"Indice debe ser inmediato|bh|bl.");
							}
					}
					break;
				default:
					if(!(instruccion == 11 || instruccion == 10)){
						ventanaError(programCounter,"Hace falta parametro o no existe.");
					}
			}
		}
	}
	if(band)/*parametro 2*/
	{
		if((par2[0]>=0x30 && par2[0]<=0x39 )||par2[0]=='-')
		{
			if(instruccion >= 0 && instruccion <= 5){
				cuartoDato = atoi(par2);
				parametro2 = 15;
			}
			else
			{
				ventanaError(programCounter,"Segundo parametro no puede ser inmediato.");
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
										ventanaError(programCounter,"Hace falta ]");

									}
									break;
								case 'l':
									if(par2[3]==']')
										parametro2 = 13;
									else{
										ventanaError(programCounter,"Hace falta ]");
									}
									break;
								default:
									ventanaError(programCounter,"Parametro 2 no existe."); 
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
								ventanaError(programCounter,"Indice debe ser inmediato|bh|bl.");
							}
					}
					break;
				default:
					if(!(instruccion >= 6 || instruccion <= 11)){
						ventanaError(programCounter,"Hace falta parametro o no existe.");
					}
			}
		}	
	}

	if((parametro1>=12 && parametro1<=14 && parametro2>=12 && parametro2<=14 )||(parametro1>=4 && parametro1<=11 && parametro2>=0 && parametro2<=3)||(parametro2>=4 && parametro2<=11 && parametro1>=0 && parametro1<=3))
	{
		ventanaError(programCounter,"Parametros no pueden ir de mem->mem o de 16/8 bits a 8/16.");
	}

	memoria[programCounter]-> codigoOp = instruccion;
	memoria[programCounter]-> operando1 = parametro1;
	memoria[programCounter]-> operando2 = parametro2;
	memoria[programCounter]-> cuartoDato = cuartoDato;
}
void getRenglones(char* text)
{
	int i = 0,index = 0,comment = 0;;
	PC=0;
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
	lineasPrograma = PC + 1;
	for(PC = 0;PC<lineasPrograma;PC++)
		excInstruccion(prog[PC],PC); 
	PC =0;


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
    	printf("Seleccion de archivo cancelado.\n");
    	path = NULL;
    }

    gtk_widget_destroy(dialog);
    
    return path;
}
void abrirArchivo(GtkButton* button, gpointer func_data) 
{ 
	/*reset();*/
	resetALL();
	clearBuffer(gtkbuffer);
	const char *filename = get_dialog_path_selection();
	char *buffer = NULL;
	if(filename){
	   	int tamano, lenRes;
	   	FILE *file = fopen(filename, "r");

	   	if (file)
	   	{
	       	fseek(file, 0, SEEK_END);/*enceuntra ultimo byte del archivo*/
	       	globalTamano = tamano = ftell(file);/*tamaño del inicio al fin*/
	       	rewind(file);/*se pone al inicio del archivo*/				
	       	buffer = (char*) malloc(sizeof(char) * (tamano + 1) );/*crea el char* donde estara*/
	       	lenRes = fread(buffer, sizeof(char), tamano, file);/*lee todo*/
	       	buffer[tamano] = '\0';/*para que sea el fin del string*/

	       	if (tamano != lenRes)/*si son de distintos tamaños estamos mamando*/
	       	{
	           	free(buffer);
	           	buffer = NULL;
	       	}
	       fclose(file);
	    }
	    programa = buffer;
	    getRenglones(buffer);
	    buff = buffer;
	    size = tamano;
	}
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

void actualizarRT(int a,int b,int c, int d)
{
	ax=a%65535;
	bx=b%65535;
	cx=c%65535;
	dx=d%65535;
	actualizarRegistroLH(0);
	actualizarRegistroLH(1);
	actualizarRegistroLH(2);
	actualizarRegistroLH(3);
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

void ventanaIR()
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
void ventanaPC()
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
void ventanaRT()
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
void ventanaFlags()
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
void ventanaALU()
{
	GtkWidget *window,*grid,*lblB1,*lblB2,*lblB3,*lblB4,*lB1,*lB2,*lB3,*lB4;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	lblB1 = gtk_label_new("B1   ->");
	lblB2 = gtk_label_new("B2   ->");
	lblB3 = gtk_label_new("B3   ->");
	lblB4 = gtk_label_new("B4   ->");
	char t1[5],t2[5],t3[5],t4[5];
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
void ventanaMMB()
{
	GtkWidget *window,*grid,*lblmar,*lblmbr,*lblBd,*lmar,*lmbr,*lbd;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	grid = gtk_grid_new();
	lblmbr = gtk_label_new("MBR   ->");
	lblmar = gtk_label_new("MAR   ->");
	lblBd = gtk_label_new("BD    ->");
	char t1[5],t2[5],t3[5];
	lmar = gtk_label_new(itoa(MAR,t1,10));
	lmbr = gtk_label_new(itoa(MBR,t2,10));
	lbd = gtk_label_new(itoa(BD,t3,10));

	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_grid_attach(GTK_GRID(grid),lblmar,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lblmbr,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lmar,1,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),lmbr,1,1,1,1);

	gtk_grid_attach(GTK_GRID(grid),lblBd,2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),lbd,3,1,1,1);

	gtk_widget_set_size_request(lblmar,50,30);
	gtk_widget_set_size_request(lblmbr,50,30);
	gtk_widget_set_size_request(lblBd,50,30);

	gtk_widget_set_size_request(lmar,40,30);
	gtk_widget_set_size_request(lmbr,40,30);
	gtk_widget_set_size_request(lbd,40,30);

	gtk_window_set_title (GTK_WINDOW(window), "MAR - MBR - BD");
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
	/*B2 = B1 = B4 = 0;*/
}

void sumAlu(void)
{
	B3 = B2 + B1;
	if(!B3) zeroF = 1;
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) carryF = signF = 1;
	else carryF = signF = 0;
	/*B2 = B1 = B4 = 0;*/
}

void restAlu(void)
{
	B3 = B1-B2;
	if(B3 < 0) carryF = signF = 1;
	else carryF = signF = 0;
	if(!B3) zeroF = 1;
	else zeroF = 0;
	/*B2 = B1 = B4 = 0;*/
}

void divAlu(void)
{
	if(!B2) ventanaError(0,"Division por Cero");
	else{
		B3 = B1 / B2;
		B4 = B1 % B2;
		if(!B3) zeroF = 1;
	}
}

void andAlu(void)
{
	B3 = B1 & B2;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void orAlu(void)
{
	B3 = B1 | B2;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void xorAlu(void)
{
	B3 = B1 ^ B2;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void notAlu(void)
{
	B3 = !B1;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void shlAlu(void)
{
	B3 = B1 << B2;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void shrAlu(void)
{
	B3 = B1 >> B2;
	/*B2 = B1 = B4 = 0;*/
	if(B3 > 65535){B3 = B3%65535; carryF=1;}
	if(B3 < 0) signF = 1;
	if(!B3) zeroF = 1;
}

void mov (int codigo1, int codigo2, int cuartoDato)
{
	switch(codigo2){
		case 0:
			BD = ax; /*BD<-ax*/
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
		case 4:
			BD = al;
			break;
		case 5:
			BD = bl;
			break;
		case 6:
			BD = cl;
			break;
		case 7:
			BD = dl;
			break;
		case 8:
			BD = ah;
			break;
		case 9:
			BD = bh;
			break;
		case 10:
			BD = ch;
			break;
		case 11:
			BD = dh;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
	}
	switch(codigo1){
		case 0:
			ax = BD;
			actualizarRegistroLH(0);
			break;
		case 1:
			bx = BD;
			actualizarRegistroLH(1);
			break;
		case 2:
			cx = BD;
			actualizarRegistroLH(2);
			break;
		case 3:
			dx = BD;
			actualizarRegistroLH(3);
			break;
		case 4:
			al = BD;
			actualizarRegistroX(0);
			break;
		case 5:
			bl = BD;
			actualizarRegistroX(1);
			break;
		case 6:
			cl = BD;
			actualizarRegistroX(2);
			break;
		case 7:
			dl = BD;
			actualizarRegistroX(3);
			break;
		case 8:
			ah = BD;
			actualizarRegistroX(0);
			break;
		case 9:
			bh = BD;
			actualizarRegistroX(1);
			break;
		case 10:
			ch = BD;
			actualizarRegistroX(2);
			break;
		case 11:
			dh = BD;
			actualizarRegistroX(3);
			break;
		case 12:
			MBR = BD;
			BD  = PC;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[cuartoDato1]->cuartoDato = BD;*/
			break;
		case 13:
			MBR = BD;
			BD  = bl;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[bl]->cuartoDato = BD;*/
			break;
		case 14:
			MBR = BD;
			BD  = bh;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[bh]->cuartoDato = BD;*/
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
		case 4:
			BD = al;
			break;
		case 5:
			BD = bl;
			break;
		case 6:
			BD = cl;
			break;
		case 7:
			BD = dl;
			break;
		case 8:
			BD = ah;
			break;
		case 9:
			BD = bh;
			break;
		case 10:
			BD = ch;
			break;
		case 11:
			BD = dh;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
			break;
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
		case 4:
			BD = al;
			break;
		case 5:
			BD = bl;
			break;
		case 6:
			BD = cl;
			break;
		case 7:
			BD = dl;
			break;
		case 8:
			BD = ah;
			break;
		case 9:
			BD = bh;
			break;
		case 10:
			BD = ch;
			break;
		case 11:
			BD = dh;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
			break;
	}
	B2 = BD;
	sumAlu();
	BD = B3;
	switch(codigo1){
		case 0:
			ax = BD;
			actualizarRegistroLH(0);
			break;
		case 1:
			bx = BD;
			actualizarRegistroLH(1);
			break;
		case 2:
			cx = BD;
			actualizarRegistroLH(2);
			break;
		case 3:
			dx = BD;
			actualizarRegistroLH(3);
			break;
		case 4:
			al = BD;
			actualizarRegistroX(0);
			break;
		case 5:
			bl = BD;
			actualizarRegistroX(1);
			break;
		case 6:
			cl = BD;
			actualizarRegistroX(2);
			break;
		case 7:
			dl = BD;
			actualizarRegistroX(3);
			break;
		case 8:
			ah = BD;
			actualizarRegistroX(0);
			break;
		case 9:
			bh = BD;
			actualizarRegistroX(1);
			break;
		case 10:
			ch = BD;
			actualizarRegistroX(2);
			break;
		case 11:
			dh = BD;
			actualizarRegistroX(3);
			break;
		case 12:
			MBR = BD;
			BD  = cuartoDato;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[cuartoDato1]->cuartoDato = BD;*/
			break;
		case 13:
			MBR = BD;
			BD  = bl;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[bl]->cuartoDato = BD;*/
			break;
		case 14:
			MBR = BD;
			BD  = bh;
			MAR = BD;
			MEM(ESCRITURA);
			/*memoria[bl]->cuartoDato = BD;*/
			break;
	}
}

void cmp(int codigo1, int codigo2, int cuartoDato)
{
	switch(codigo2){
		case 0:
			BD = ax; /*BD<-ax*/
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
		case 4:
			BD = al;
			break;
		case 5:
			BD = bl;
			break;
		case 6:
			BD = cl;
			break;
		case 7:
			BD = dl;
			break;
		case 8:
			BD = ah;
			break;
		case 9:
			BD = bh;
			break;
		case 10:
			BD = ch;
			break;
		case 11:
			BD = dh;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 15:
			BD  = cuartoDato;
	}
	B1 = BD;
	switch(codigo1){
		case 0:
			BD = ax; /*BD<-ax*/
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
		case 4:
			BD = al;
			break;
		case 5:
			BD = bl;
			break;
		case 6:
			BD = cl;
			break;
		case 7:
			BD = dl;
			break;
		case 8:
			BD = ah;
			break;
		case 9:
			BD = bh;
			break;
		case 10:
			BD = ch;
			break;
		case 11:
			BD = dh;
			break;
		case 12:
			BD  = cuartoDato;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 13:
			BD  = bl;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 14:
			BD  = bh;
			MAR = BD;
			MEM(LECTURA);
			/*MBR = memoria[MAR]->cuartoDato;*/
			BD  = MBR;
			break;
		case 15:
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

void inMicro()
{
	printf("Microinstruccion in. Dato entrada: ");/*ver*/
	scanf("%d", &MBR);
}

void outMicro()
{
	char temp[5];
	concatBuffer(gtkbuffer2,g_strconcat("Dato salida MBR: ",itoa(MBR,temp,10),NULL));
}

/*Esta Microinstruccion escribe en [MAR] lo que esta en MBR
o lee de [MAR] y lo guarda en MBR*/
void MEM(int operacion)
{	
	/*Si operacion es 1 -> read*/
	if(operacion)
	{	
		MBR = memoria[MAR]->cuartoDato;
	}
	else/*lectura*/
	{
		memoria[MAR]-> codigoOp   = -1;
		memoria[MAR]-> operando1  =  0;
		memoria[MAR]-> operando2  =  0;
		memoria[MAR]-> cuartoDato = MBR;
	}
}

void cli(void)
{
	interruptF = 0;
}

void sti(void)
{
	interruptF = 1;
}
void in(int a)/*ver*/
{
	char*aaaa= gtk_entry_get_text(GTK_ENTRY(entrada));
	int num = atoi(aaaa);

	switch(a)
	{
		case 0:
			mov(0,15,num);
			concatBuffer(gtkbuffer2,g_strconcat("ax: ",aaaa,NULL));
			break;
		case 1:
			concatBuffer(gtkbuffer2,g_strconcat("bx: ",aaaa,NULL));
			mov(1,15,num);
			break;
		case 2:
			concatBuffer(gtkbuffer2,g_strconcat("cx: ",aaaa,NULL));
			mov(2,15,num);	
			break;
		case 3:
			concatBuffer(gtkbuffer2,g_strconcat("dx: ",aaaa,NULL));
			mov(3,15,num);
			break;
		case 4:
			concatBuffer(gtkbuffer2,g_strconcat("al: ",aaaa,NULL));
			mov(4,15,num);
			break;
		case 5:
			concatBuffer(gtkbuffer2,g_strconcat("bl: ",aaaa,NULL));
			mov(5,15,num);
			break;
		case 6:
			concatBuffer(gtkbuffer2,g_strconcat("cl: ",aaaa,NULL));
			mov(6,15,num);
			break;
		case 7:
			concatBuffer(gtkbuffer2,g_strconcat("dl: ",aaaa,NULL));
			mov(7,15,num);
			break;
		case 8:
			concatBuffer(gtkbuffer2,g_strconcat("ah: ",aaaa,NULL));
			mov(8,15,num);
			break;
		case 9:
			concatBuffer(gtkbuffer2,g_strconcat("bh: ",aaaa,NULL));
			mov(9,15,num);
			break;
		case 10:
			concatBuffer(gtkbuffer2,g_strconcat("ch: ",aaaa,NULL));
			mov(10,15,num);
			break;
		case 11:
			concatBuffer(gtkbuffer2,g_strconcat("dh: ",aaaa,NULL));
			mov(11,15,num);
			break;
	}
}
void out(int a)
{
	char temp[5];
	switch(a)
	{
		case 0:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro ax: ",itoa(ax,temp,10),NULL));
			break;
		case 1:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro bx: ",itoa(bx,temp,10),NULL));
			break;
		case 2:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro cx: ",itoa(cx,temp,10),NULL));
			break;
		case 3:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro dx: ",itoa(dx,temp,10),NULL));
			break;
		case 4:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro al: ",itoa(al,temp,10),NULL));
			break;
		case 5:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro bl: ",itoa(bl,temp,10),NULL));
			break;
		case 6:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro cl: ",itoa(cl,temp,10),NULL));
			break;
		case 7:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro dl: ",itoa(dl,temp,10),NULL));
			break;
		case 8:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro ah: ",itoa(ah,temp,10),NULL));
			break;
		case 9:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro bh: ",itoa(bh,temp,10),NULL));
			break;
		case 10:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro ch: ",itoa(ch,temp,10),NULL));
			break;
		case 11:
			concatBuffer(gtkbuffer2,g_strconcat("Salida registro dh: ",itoa(dh,temp,10),NULL));
			break;
	}
}
void jz(int a)
{
	if(zeroF) PC = a - 1;
}
void jmp(int a)
{
	PC = a -1;
}
void cicloFetch() 
{
	IR = prog[PC];
	/*Subciclo busqueda*/
	BD = PC;      /*BD  <- ax*/
	MAR = BD;     /*B1 <- BD*/
	MEM(LECTURA); /*sum*/
	BD = MBR;     /*BD  <- MBR*/
	IR_fetch = BD;      /*IR  <- BD*/

	/*Subciclo de Decodificacion
	Subciclo indirecto
	Esto se lleva a cabo durante la ejecucion de la instrucion	
	Subciclo de ejecucion

	en el siguiente switch*/
	int inss = memoria[PC]->codigoOp;
	int parr1 = memoria[PC]->operando1;
	int parr2 = memoria[PC]->operando2;
	int cuarr = memoria[PC]->cuartoDato;

	switch(inss){
		case 0:
			mov(parr1,parr2,cuarr);
			break;
		case 2:
			add(parr1,parr2,cuarr);
			break;
		case 4:
			cmp(parr1,parr2,cuarr);
			break;
		case 6:
			jz(cuarr);
			break;
		case 7:
			jmp(cuarr);
			break;
		case 8:
			out(parr1);
			break;
		case 9:
			in(parr1);
			break;
		case 10:
			sti();
			break;
		case 11:
			cli();
			break;
	} 



	/*subciclo de interrupcion*/
	if(interruptF){
		interruptF = 0;
		ventanaInterrupt();
	}

	PC++;          /*inc PC*/
}

void actualizarRegistroX(int a)
{
	/*a es el registro que cambio*/
	switch(a)
	{
		case 0:
			ax = ah*256 + al;
			break;
		case 1:
			bx = bh*256 + bl;
			break;
		case 2:
			cx = ch*256 + cl;
			break;
		case 3:
			dx = dh*256 + dl;
			break;
	}
}
void actualizarRegistroLH(int a)
{
	/*a es el registro que cambio*/
	switch(a)
	{
		case 0:
			ah = getRThigh(ax);
			al = getRTlow (ax);
			break;
		case 1:
			bh = getRThigh(bx);
			bl = getRTlow (bx);
			break;
		case 2:
			ch = getRThigh(cx);
			cl = getRTlow (cx);
			break;
		case 3:
			dh = getRThigh(dx);
			dl = getRTlow (dx);
			break;
	}
}
void guardarAFOC(void)
{
	int arreglo[28];

	FILE *archivito = fopen("AFOC", "wb");

	arreglo[0]  = size;
	arreglo[1]  = lineasPrograma;
	arreglo[2]  = IR_fetch;
	arreglo[3]  = PC;
	arreglo[4]  = ah;
	arreglo[5]  = al;
	arreglo[6]  = ax;
	arreglo[7]  = bh;
	arreglo[8]  = bl;
	arreglo[9]  = bx;
	arreglo[10] = ch;
	arreglo[11] = cl;
	arreglo[12] = cx;
	arreglo[13] = dh;
	arreglo[14] = dl;
	arreglo[15] = dx;
	arreglo[16] = zeroF;
	arreglo[17] = signF;
	arreglo[18] = interruptF;
	arreglo[19] = carryF;
	arreglo[20] = B1;
	arreglo[21] = B2;
	arreglo[22] = B3;
	arreglo[23] = B4;
	arreglo[24] = BD;
	arreglo[25] = MAR;
	arreglo[26] = MBR;
	arreglo[27] = globalTamano;
	int i;
	fwrite(arreglo, sizeof(int), 28, archivito);

	fwrite(programa, sizeof(char), globalTamano,archivito);

	for(i = 0; i < 256; i++)
		fwrite(memoria[i], sizeof(celda), 1, archivito);

	fclose(archivito);

}

void cargarAFOC(void)
{
	int arreglo[28];

	FILE *archivito = fopen("AFOC", "rb");
	if (archivito != NULL)
	{
		fread(arreglo,sizeof(int),28,archivito);
		size            = arreglo[0];
		lineasPrograma  = arreglo[1];
		IR_fetch        = arreglo[2];
		PC              = arreglo[3];
		ah              = arreglo[4];
		al              = arreglo[5];
		ax              = arreglo[6];
		bh              = arreglo[7];
		bl              = arreglo[8];
		bx              = arreglo[9];
		ch              = arreglo[10];
		cl              = arreglo[11];
		cx              = arreglo[12];
		dh              = arreglo[13];
		dl              = arreglo[14];
		dx              = arreglo[15];
		zeroF           = arreglo[16];
		signF           = arreglo[17];
		interruptF      = arreglo[18];
		carryF          = arreglo[19];
		B1              = arreglo[20];
		B2              = arreglo[21];
		B3              = arreglo[22];
		B4              = arreglo[23];
		BD              = arreglo[24];
		MAR             = arreglo[25];
		MBR             = arreglo[26];
		globalTamano    = arreglo[27];

		fread(programa, sizeof(char), globalTamano, archivito);
		fread(arregloMemoriaArchivo, sizeof(celda),256,archivito);
		fclose(archivito);

		concatBuffer(gtkbuffer,programa);


		int i;
	    for(i = 0; i<256; i++)
	    	memoria[i] = &(arregloMemoriaArchivo[i]);
	}
}