#include "stdio.h"
#include <gtk/gtk.h>
#include <string.h>

#define MUCHO 2000

//#include "archivo.h"

#include "structs.h"

/* 
      cc `pkg-config --cflags gtk+-3.0` Von.c -o Von `pkg-config --libs gtk+-3.0`
*/
static void ventanaSimulador()
{
  GtkWidget *btoPlay,*btoStep,*btoReset,*txtCode,*p,*consola,*dialog,*label,*grid,*btoUC,*btoIR,*btoPC,*btoBD,*btoRT,*btoFlag,*btoALU,*btoMAR,*btoMBR;
  
  GtkTextBuffer * gtkbuffer = gtk_text_buffer_new(NULL);
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
  btoMAR = gtk_button_new_with_label("MAR");
  btoMBR = gtk_button_new_with_label("MBR");
  btoPlay = gtk_button_new_with_label("Play");
  btoStep = gtk_button_new_with_label("Step");
  btoReset = gtk_button_new_with_label("Reset");

  gtk_container_add(GTK_CONTAINER(dialog),grid);
  gtk_grid_attach(GTK_GRID(grid),label,1,0,4,1);//COL,FILA,COL,FILA
  gtk_grid_attach(GTK_GRID(grid),btoUC,1,3,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoIR,1,1,1,2);
  gtk_grid_attach(GTK_GRID(grid),btoPC,1,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoBD,2,1,1,4);
  gtk_grid_attach(GTK_GRID(grid),btoRT,3,1,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoFlag,3,2,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoALU,3,3,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoMAR,3,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoMBR,4,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),p,5,1,1,5);
  gtk_grid_attach(GTK_GRID(grid),consola,0,1,1,5);
  gtk_grid_attach(GTK_GRID(grid),btoPlay,1,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoStep,2,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoReset,3,5,2,1);
  gtk_widget_set_size_request(btoUC,50,100);
  gtk_widget_set_size_request(p,250,100);
  gtk_widget_set_size_request(consola,250,100);
  gtk_widget_set_size_request(btoIR,100,100);
  gtk_widget_set_size_request(btoPC,50,100);
  gtk_widget_set_size_request(btoBD,100,70);
  gtk_widget_set_size_request(btoRT,50,100);
  gtk_widget_set_size_request(btoFlag,50,100);
  gtk_widget_set_size_request(btoALU,50,100);
  gtk_widget_set_size_request(btoMAR,50,50);
  gtk_widget_set_size_request(btoMBR,50,50);
  g_signal_connect(btoIR,"clicked",G_CALLBACK(ventanaIR),dialog);
  g_signal_connect(btoPC,"clicked",G_CALLBACK(ventanaPC),dialog);
  g_signal_connect(btoRT,"clicked",G_CALLBACK(ventanaRT),dialog);
  g_signal_connect(btoFlag,"clicked",G_CALLBACK(ventanaFlags),dialog);
  g_signal_connect(btoPlay,"clicked",G_CALLBACK(play),NULL);
  g_signal_connect(btoStep,"clicked",G_CALLBACK(step),NULL);
  g_signal_connect(btoReset,"clicked",G_CALLBACK(reset),NULL);

  gtk_widget_set_sensitive (btoUC, FALSE);
  gtk_widget_set_sensitive (btoBD, FALSE);
  gtk_window_set_title (GTK_WINDOW(dialog), "Simulador");
  gtk_window_set_resizable (GTK_WINDOW(dialog), TRUE);
  gtk_widget_show_all(dialog);
}
int main(int argc, char* argv[])
{
  for(i = 0; i < 256; i++)
  {
    memoria[i] = (celda*) malloc(sizeof(celda));
    memoria[i]->codigoOp   = 0;
    memoria[i]->operando1  = 0;
    memoria[i]->operando2  = 0;
    memoria[i]->cuartoDato = 0;
  }
  gtk_init(&argc,&argv);//INICIA GTK
  GtkWidget* window,*button,*grid, *botonArchivo; //VARIABLES

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //crea la ventana
  gtk_window_set_title (GTK_WINDOW(window), "Simulador");
  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

  //aqui empieza la puz
  button = gtk_button_new_with_label("abre ventana");
  botonArchivo = gtk_button_new_with_label("Carga Archivo");

  char* bufferMemoria; 
  gtk_widget_set_size_request(button,100,50);
  gtk_widget_set_size_request(botonArchivo,100,50);


  g_signal_connect(button,"clicked",G_CALLBACK(ventanaSimulador),window);
  g_signal_connect(botonArchivo,"clicked",G_CALLBACK(abrirArchivo),NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window),50);

  grid = gtk_grid_new();
  
  gtk_container_add(GTK_CONTAINER(window),grid);
  gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),botonArchivo,1,0,1,1);
  gtk_widget_show_all(window);//showea todo
  gtk_main();//start

  return 0;
}