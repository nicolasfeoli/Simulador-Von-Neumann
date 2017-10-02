#include "stdio.h"
#include <gtk/gtk.h>

#define MUCHO 2000

//#include "archivo.h"
/* 
      cc `pkg-config --cflags gtk+-3.0` Von.c `pkg-config --libs gtk+-3.0`
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

static void open_dialog(GtkWidget* buton, gpointer window)
{
  GtkWidget *dialog,*label,*grid,*btoUC,*btoIR,*btoPC,*btoBD,*btoRT,*btoFlag,*btoALU,*btoB1,*btoB2,*btoB3,*btoB4,*btoMAR,*btoMBR;
 
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
  btoB1 = gtk_button_new_with_label("B1");
  btoB2 = gtk_button_new_with_label("B2");
  btoB3 = gtk_button_new_with_label("B3");
  btoB4 = gtk_button_new_with_label("B4");
  btoMAR = gtk_button_new_with_label("MAR");
  btoMBR = gtk_button_new_with_label("MBR");


  gtk_container_add(GTK_CONTAINER(dialog),grid);
  gtk_grid_attach(GTK_GRID(grid),label,0,0,4,1);//COL,FILA,COL,FILA
  gtk_grid_attach(GTK_GRID(grid),btoUC,0,3,1,4);
  gtk_grid_attach(GTK_GRID(grid),btoIR,0,1,1,2);
  gtk_grid_attach(GTK_GRID(grid),btoPC,0,7,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoBD,1,1,1,7);
  gtk_grid_attach(GTK_GRID(grid),btoRT,2,1,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoFlag,2,2,2,1);
  gtk_grid_attach(GTK_GRID(grid),btoALU,3,3,1,4);
  gtk_grid_attach(GTK_GRID(grid),btoB1,2,3,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoB2,2,4,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoB3,2,5,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoB4,2,6,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoMAR,2,7,1,1);
  gtk_grid_attach(GTK_GRID(grid),btoMBR,3,7,1,1);

  gtk_window_set_title (GTK_WINDOW(dialog), "Simulador");
  gtk_window_set_resizable (GTK_WINDOW(dialog), TRUE);
  gtk_widget_show_all(dialog);
}
int main(int argc, char* argv[])
{
  gtk_init(&argc,&argv);//INICIA GTK
  GtkWidget* window,*button,*grid, *botonArchivo; //VARIABLES


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //crea la ventana
  gtk_window_set_title (GTK_WINDOW(window), "Simulador");

  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
  //aqui empieza la puz
  button = gtk_button_new_with_label("abre ventana");
  g_signal_connect(button,"clicked",G_CALLBACK(open_dialog),window);
  //g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  botonArchivo = gtk_button_new_with_label("Carga Archivo");

  char* bufferMemoria; //Hay que reservar esta memoria para que no la reserve dentro de la funcion. Se cambia despues.
  abrirArchivo("programaASM.txt", &bufferMemoria);

  //g_signal_connect_swapped (botonArchivo, "clicked", G_CALLBACK (gtk_widget_destroy), window); // los parametros que estan despues del "clicked" son los parametros que recibe la funcion print hello que se puso en la primera linea
  
  gtk_container_set_border_width(GTK_CONTAINER(window),50);

  grid = gtk_grid_new();

  gtk_container_add(GTK_CONTAINER(window),grid);
  gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);

  gtk_widget_show_all(window);//showea todo
  gtk_main();//start

  return 0;
}