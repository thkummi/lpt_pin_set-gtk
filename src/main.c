/*
Copyright (C) 2018 Thomas Kummer
licensed under the GNU General Public License v3.0 
*/

#include <gtk/gtk.h>
#include <sys/io.h>
#include <sys/types.h>
#include <fcntl.h>

#define BASEPORT 0x378 // lp1

char c;
int n, tem;
char pin[8];

GtkWidget *g_lbl_on_off;
GtkWidget *g_lbl_count;


int main(int argc, char *argv[])
{   	//set permissions to access port
	if (ioperm(BASEPORT, 3, 1)) {perror("ioperm"); exit(1);}
	
		tem = fcntl(0, F_GETFL, 0);
		fcntl (0, F_SETFL, (tem | O_NDELAY));

	GtkBuilder      *builder; 
	GtkWidget       *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);
    
	// set pointers to labels
	g_lbl_on_off = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_on_off"));
	g_object_unref(builder);
	gtk_widget_show(window);                
	gtk_main();
	return 0;
}
//send decimal value to printer port
void lpt_set(int pinval)
{
	outb(pinval, BASEPORT);
}
//convert 8bit binary Number to decimal and send it to printer port
void dual_convert(int num) 
{
	int  decimal_val = 0, base = 1, rem;

	while (num > 0){
		rem = num % 10;
		decimal_val = decimal_val + rem * base;
		num = num / 10 ;
		base = base * 2;
		}		
	outb(decimal_val, BASEPORT);
	gtk_label_set_text(GTK_LABEL(g_lbl_on_off), "ON");
}

// when ON button is clicked
void on_btn_on_clicked() {
	// read pin array reverse and write into int val
	int lpt_dual = 0;
	for (int i = 7; i > -1; i--) {
    		int num = pin[i];
    		if (num != 0) {
        		while (num > 0) {
            			lpt_dual *= 10;
            			num /= 10;
        		}
        		lpt_dual += pin[i];
    		} 
		else {
        		lpt_dual *= 10;
    		}
	}
	dual_convert(lpt_dual);
}
// when OFF button is clicked
void on_btn_off_clicked()
{
	gtk_label_set_text(GTK_LABEL(g_lbl_on_off), "OFF");
	lpt_set(0);
}
// when checkboxes are toggled
void on_chkbox_pin1_toggled()
{
	if (pin[0] == 0) {
		pin[0] = 1; 
	}	
	else {
		pin[0] = 0;
	}
}
void on_chkbox_pin2_toggled()
{
	if (pin[1] == 0) {
		pin[1] = 1; 
	}	
	else {
		pin[1] = 0;
	}
}
void on_chkbox_pin3_toggled()
{
	if (pin[2] == 0) {
		pin[2] = 1; 
	}	
	else {
		pin[2] = 0;
	}
}
void on_chkbox_pin4_toggled()
{
	if (pin[3] == 0) {
		pin[3] = 1; 
	}	
	else {
		pin[3] = 0;
	}
}
void on_chkbox_pin5_toggled()
{
	if (pin[4] == 0) {
		pin[4] = 1; 
	}	
	else {
		pin[4] = 0;
	}
}
void on_chkbox_pin6_toggled()
{
	if (pin[5] == 0) {
		pin[5] = 1; 
	}	
	else {
		pin[5] = 0;
	}
}
void on_chkbox_pin7_toggled()
{
	if (pin[6] == 0) {
		pin[6] = 1; 
	}	
	else {
		pin[6] = 0;
	}
}
void on_chkbox_pin8_toggled()
{
	if (pin[7] == 0) {
		pin[7] = 1; 
	}	
	else {
		pin[7] = 0;
	}
}
// when window is closed
void on_window_main_destroy()
{
	gtk_main_quit();
}
