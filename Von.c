#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "structs.h"

#define MUCHO 2000

/*#include "archivo.h"*/


/* 
      cc `pkg-config --cflags gtk+-3.0` Von.c -o Von `pkg-config --libs gtk+-3.0`
*/

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
  programa = (char*)malloc(10000);
  gtk_init(&argc,&argv);/*INICIA GTK*/
  GtkWidget* window,*button,*grid, *botonArchivo,*botonAyuda,*botonAcercaDe; /*VARIABLES*/

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /*crea la ventana*/
  gtk_window_set_title (GTK_WINDOW(window), "Simulador");
  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

  /*aqui empieza la puz*/
  button = gtk_button_new_with_label("Abrir simulador");
  botonArchivo = gtk_button_new_with_label("Carga Archivo");

  char* bufferMemoria; 
  gtk_widget_set_size_request(button,100,50);
  gtk_widget_set_size_request(botonArchivo,100,50);


  g_signal_connect(button,"clicked",G_CALLBACK(ventanaSimulador),window);
  g_signal_connect(botonArchivo,"clicked",G_CALLBACK(abrirArchivo),NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window),50);

  grid = gtk_grid_new();

  botonAyuda = gtk_button_new_with_label("Ayuda");
  botonAcercaDe = gtk_button_new_with_label("Acerca de...");
  gtk_widget_set_size_request(botonAyuda,100,50);
  gtk_widget_set_size_request(botonAcercaDe,100,50);

  g_signal_connect(botonAyuda,"clicked",G_CALLBACK(ventanaAyuda),NULL);
  g_signal_connect(botonAcercaDe,"clicked",G_CALLBACK(ventanaAcercaDe),NULL);
  gtk_grid_attach(GTK_GRID(grid),botonAyuda,0,1,1,1);
  gtk_grid_attach(GTK_GRID(grid),botonAcercaDe,1,1,1,1);
  
  gtk_container_add(GTK_CONTAINER(window),grid);
  gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),botonArchivo,1,0,1,1);
  gtk_widget_show_all(window);/*showea todo*/
  gtk_main();/*start*/

  return 0;
}