#include "stdio.h"
#include <gtk/gtk.h>
/* 
      cc `pkg-config --cflags gtk+-3.0` prueba.c `pkg-config --libs gtk+-3.0`
*/

static void open_dialog(GtkWidget* buton, gpointer window)
{
  GtkWidget *dialog,*label;
  dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
  label = gtk_label_new("YOU CLICKED THE BUTTON");
  gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),label,0,0,0);
  gtk_widget_show_all(dialog);
  gint response = gtk_dialog_run(GTK_DIALOG(dialog));
  if(response==GTK_RESPONSE_OK)
    g_print("OKs pressed");
  else
    g_print("the cancel was clicked");
  gtk_widget_destroy(dialog);


}
int main(int argc, char* argv[])
{
  gtk_init(&argc,&argv);//INICIA GTK
  GtkWidget* window,*button,*bto,*grid,*bbtt; //VARIABLES


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //crea la ventana
  g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
  //aqui empieza la puz
  button = gtk_button_new_with_label("abre ventana");
  bbtt = gtk_button_new_with_label("ni picha");
  g_signal_connect(button,"clicked",G_CALLBACK(open_dialog),window);
  bto = gtk_button_new_with_label("no hacen");
  gtk_container_set_border_width(GTK_CONTAINER(window),150);

  grid = gtk_grid_new();

  gtk_container_add(GTK_CONTAINER(window),grid);
  gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),bto,1,0,1,1);
  gtk_grid_attach(GTK_GRID(grid),bbtt,0,1,2,1);

  gtk_widget_show_all(window);//showea todo
  gtk_main();//start

  return 0;
}