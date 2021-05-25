#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#define false 0
#define true !false
#include <ctype.h>


FILE *F_contrat,*F_voiture,*F_client,*F_text;

int inder=false;
int enlocat=false;
int ver=false;
int j=false;
int k=false;
int click=false;

static messag(GtkWidget *widget, gpointer entry,int a);
void verif_id_Cl(GtkWidget *widget, gpointer entry);
void ver_Vr(GtkWidget *widget, gpointer entry);
void verif_id_Cont(GtkWidget *widget, gpointer entry);
static void open_dialog(int a);

void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}


typedef struct date
{
    int jours;
    int mois;
    int anner;
}date;


struct Voiture
{
    int idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char EnLocation[4];
}voiture;


struct contratLocation
{
    int numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date fin;
    int cout;
}contrat;



struct Client
{
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
}client;



void distroy(GtkWidget *widget1, gpointer window){

    gtk_widget_destroy(window);
}


void distroy1(GtkWidget *widget1, gpointer window)
{
    if(!inder)
       {
           gtk_widget_destroy(window);
           enlocat=true;
       }
}


void insert_text_event(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (!isdigit(text[i])) {
            g_signal_stop_emission_by_name(G_OBJECT(editable), "insert-text");
            return;
        }
    }
}



void insert_text(GtkWidget *widget, gpointer entry)
{
    if((!strcmp(gtk_entry_get_text(GTK_ENTRY(entry)),"")) && inder==false)
    {
        inder=true;
        GtkWidget *window, *table, *label;
        GtkWidget *button1;


        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);
        gtk_widget_set_name(window, "window5");


        table = gtk_table_new(1, 1, FALSE);
        gtk_container_add(GTK_CONTAINER(window), table);


        label = gtk_tool_button_new_from_stock(GTK_STOCK_DIALOG_WARNING);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 0, 1, 0,1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


        char *num1 =gtk_entry_get_placeholder_text(GTK_ENTRY(entry));
        char game1[40];
        snprintf(game1, sizeof(game1), "ENTRE : %s",num1);
        label = gtk_label_new(game1);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 1, 5, 0,1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


        button1 = gtk_button_new_with_label("ok");
        gtk_widget_set_name(button1, "button4");
        gtk_table_attach(GTK_TABLE(table), button1, 2, 3, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


        gtk_widget_show_all(window);


        g_signal_connect(window, "destroy",
            G_CALLBACK(gtk_main_quit), NULL);

        g_signal_connect(G_OBJECT(button1), "clicked",
            G_CALLBACK(distroy), (gpointer) window);

        gtk_main();
    }
}

void change(GtkWidget *widget, gpointer entry){inder=false;}

void verif1(GtkWidget *widget, gpointer entry){click=true;}

void chg_ver3(){ver=false;}

void verif2(GtkWidget *widget, gpointer entry){click=false;}


static messag(GtkWidget *widget, gpointer entry,int a){

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;

    GtkWidget *button1;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");


    table = gtk_table_new(1, 1, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    switch(a)
    {
    case 1:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*cette voiture n est pas disponible*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 2:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*cette client n est pas inscrit*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 3:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*cette voiture n existe pas*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 4:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*cette voiture deja retourner*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 5:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*retourner*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 6:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Suprimer*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 7:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Cette Contrat n existe pas*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
     case 8:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Cette Contrat n existe pas*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 9:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Cette Contrat existe deja*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 10:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Cette Voiture existe deja*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    case 11:
       sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                    "*Cette Client existe deja*</span>"
                           ,-1, NULL, NULL, NULL);
    break;
    }

    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 3, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


    button1 = gtk_button_new_with_label("Ok");
    gtk_widget_set_name(button1, "button4");
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);


    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button1), "clicked",
        G_CALLBACK(verif1), window);
    g_signal_connect(G_OBJECT(button1), "clicked",
        G_CALLBACK(distroy), (gpointer) window);


    gtk_main();
}


static void open_dialog(int a){

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;

    GtkWidget *button1;
    GtkWidget *button2;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(2, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);

    switch(a)
    {
    case 1:
        sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t*** Ajouter ! ***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    break;
    case 2:
        sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t*** Modifier ! ***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    break;
    case 3:
        sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t*** Returner ! ***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    break;
    case 4:
        sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t*** Suprimer ! ***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);

    break;
    }




    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 2, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    button1 = gtk_button_new_with_label("Oui");
    gtk_widget_set_name(button1, "button4");
    gtk_table_attach(GTK_TABLE(table), button1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    button2 = gtk_button_new_with_label("Non");
    gtk_widget_set_name(button2, "button4");
    gtk_table_attach(GTK_TABLE(table), button2, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);


    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button1), "clicked",
        G_CALLBACK(verif1), window);
    g_signal_connect(G_OBJECT(button1), "clicked",
        G_CALLBACK(distroy), (gpointer) window);

    g_signal_connect(G_OBJECT(button2), "clicked",
        G_CALLBACK(verif2), window);
    g_signal_connect(G_OBJECT(button2), "clicked",
        G_CALLBACK(distroy), (gpointer) window);

  gtk_main();


}


void verif_id_Cl(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    F_client=fopen("Clients.txt","r");
    do
    {
        fscanf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
        if(num1==client.idClient)
        {
            inder=false;
            ver=true;
            break;
        }

    }while(!feof(F_client));
    fclose(F_client);
    if(!ver)
        {
            messag(widget, entry,2);
            inder=true;
        }
    }

}



void verif_id_Cont(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    F_contrat=fopen("contratLocation.txt","r");
    do
    {
        fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);
        if(num1==contrat.numContrat)
        {
            inder=false;
            ver=true;
            break;
        }

    }while(!feof(F_contrat));
    fclose(F_contrat);
    if(!ver)
        {
            messag(widget, entry,8);
            inder=true;
        }
    }

}



void ver_Vr(GtkWidget *widget, gpointer entry){
    char *voitureId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    if(!inder)
    {

        F_voiture=fopen("Voitures.txt","r");
        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
            if(voitureId==voiture.idVoiture)
            {
                inder=false;
                j=true;
                break;
            }
        }while(!feof(F_voiture));
        fclose(F_voiture);

        if(!j)
            {
            inder=true;
            messag(widget, entry,3);
        }
        j=false;
    }
}

void Revers_verif_id_Cont(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    F_contrat=fopen("contratLocation.txt","r");
    do
    {
        fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);
        if(num1==contrat.numContrat)
        {
            messag(widget, entry,9);
            inder=true;
            ver=true;
            break;
        }

    }while(!feof(F_contrat));
    fclose(F_contrat);
    if(!ver)
            inder=false;
    }

}


void Revers_ver_Vr(GtkWidget *widget, gpointer entry){
    char *voitureId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    if(!inder)
    {

        F_voiture=fopen("Voitures.txt","r");
        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
            if(voitureId==voiture.idVoiture)
            {
               messag(widget, entry,10);
                inder=true;
                j=true;
                break;
            }
        }while(!feof(F_voiture));
        fclose(F_voiture);

        if(!j)
            inder=false;
        j=false;
    }
}

void Revers_verif_id_Cl(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    F_client=fopen("Clients.txt","r");
    do
    {
        fscanf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
        if(num1==client.idClient)
        {
            messag(widget, entry,11);
            inder=true;
            ver=true;
            break;
        }

    }while(!feof(F_client));
    fclose(F_client);
    if(!ver)
        inder=false;

    }

}

void Retourner(int id)
{
    FILE *F_tempvoiture;

    F_voiture=fopen("Voitures.txt","r");
    F_tempvoiture=fopen("tempVoitures.txt","a");
    do
    {
        fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);

            if(id==voiture.idVoiture)
            {
                if(!strcmp(voiture.EnLocation,"non"))
                    strcpy(voiture.EnLocation,"oui");
                else
                    strcpy(voiture.EnLocation,"non");
            }
            fprintf(F_tempvoiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
    }while(!feof(F_voiture));
    fclose(F_tempvoiture);
    fclose(F_voiture);
    remove("Voitures.txt");
    rename("tempVoitures.txt","Voitures.txt");


}

void freed(GtkWidget *widget, gpointer entry){
    if(!inder && click)
        gtk_entry_set_text(entry,"");

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                //       Location         //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**********************************************************************************************************************************************************************/
      // Location                                                     //       Afichier       //
/************************************************************************************************************************************************************************/

void Afficher1()
{
    int l;

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *labe;





    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window3");



    table = gtk_table_new(100, 7, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_set_name(table, "table_A");

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\"  >* \t***List Contrats***\t *</span>"
                            ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);

    gtk_widget_set_name(label0, "label3");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);
    gtk_table_attach(GTK_TABLE(table), label0, 0, 7, 0, 1,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




    label = gtk_label_new("Ligne");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Num Contrat");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Id Voiture ");
    gtk_table_attach(GTK_TABLE(table), label, 2, 3, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Id Client");
    gtk_table_attach(GTK_TABLE(table), label, 3, 4, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Date Debut");
    gtk_table_attach(GTK_TABLE(table), label, 4, 5, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Date Fin");
    gtk_table_attach(GTK_TABLE(table), label, 5, 6, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Cout");
    gtk_table_attach(GTK_TABLE(table), label, 6, 7, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");




    l=2;
    F_contrat=fopen("contratLocation.txt","r");
    do
    {

        fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);

        char game1[40];
        snprintf(game1, sizeof(game1), "%d   :", l-1);
        label = gtk_label_new(game1);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 0, 1, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game2[40];
        snprintf(game2, sizeof(game2), "%d", contrat.numContrat);
        label = gtk_label_new(game2);
        gtk_widget_set_halign (label, GTK_ALIGN_CENTER);
        gtk_table_attach(GTK_TABLE(table), label, 1, 2, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game3[40];
        snprintf(game3, sizeof(game3), "%d", contrat.idVoiture);
        label = gtk_label_new(game3);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 2, 3, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game4[40];
        snprintf(game4, sizeof(game4), "%d", contrat.idClient);
        label = gtk_label_new(game4);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 3, 4, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game5[40];
        snprintf(game5, sizeof(game5), "%d/%d/%d",contrat.debut.jours,contrat.debut.mois,contrat.debut.anner);
        label = gtk_label_new(game5);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 4, 5, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game6[40];
        snprintf(game6, sizeof(game6), "%d/%d/%d",contrat.fin.jours,contrat.fin.mois,contrat.fin.anner);
        label = gtk_label_new(game6);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 5, 6, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game7[40];
        snprintf(game7, sizeof(game7), "%d", contrat.cout);
        label = gtk_label_new(game7);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 6, 7, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        l++;

    }while(!feof(F_contrat));
    fclose(F_contrat);


    button = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 2, 5, l, l+1,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_widget_show_all(window);


    g_signal_connect(window, "destroy",
    G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
    G_CALLBACK(distroy), (gpointer) window);

    gtk_main();

    return 0;
}

/**********************************************************************************************************************************************************************/
       // Location                                                    //       Ajouter       //
/************************************************************************************************************************************************************************/

void Ajouter1_f1(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat,"%d ;",num1);

    fclose(F_contrat);
        gtk_entry_set_text(entry,"");

}}
void Ajouter1_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat," %d ;",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat," %d ;",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat," %d/",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat,"%d/",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter1_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat,"%d ;",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f7(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat," %d/",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f8(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat,"%d/",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter1_f9(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat,"%d ;",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}
void Ajouter1_f10(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_contrat=fopen("contratLocation.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_contrat," %d  \n",num1);

    fclose(F_contrat);
    gtk_entry_set_text(entry,"");

}}

void Ajouter1() {

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;

    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;

    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *entry5;
    GtkWidget *entry6;
    GtkWidget *entry7;
    GtkWidget *entry8;
    GtkWidget *entry9;
    GtkWidget *entry10;
    GtkWidget *button;




    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 4, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
               "*************************************\n"
               "* \t \t***Add New Contrat***\t \t *\n"
               "*************************************</span>\n"
               ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Num Contrat  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Id Voiture   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Id Client  :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Date Debut   :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Date Fin  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Cout  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label6, "labe00");

    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();
    entry7 = gtk_entry_new();
    entry8 = gtk_entry_new();
    entry9 = gtk_entry_new();
    entry10 = gtk_entry_new();

    gtk_widget_set_name(entry1, "entry");
    gtk_widget_set_name(entry2, "entry");
    gtk_widget_set_name(entry3, "entry");
    gtk_widget_set_name(entry4, "entry");
    gtk_widget_set_name(entry5, "entry");
    gtk_widget_set_name(entry6, "entry");
    gtk_widget_set_name(entry7, "entry");
    gtk_widget_set_name(entry8, "entry");
    gtk_widget_set_name(entry9, "entry");
    gtk_widget_set_name(entry10, "entry");


    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 4, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 4, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 2, 3, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 3, 4, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry7, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry8, 2, 3, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry9, 3, 4, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry10, 1, 4, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_max_length(entry4,2);
    gtk_entry_set_max_length(entry5,2);
    gtk_entry_set_max_length(entry6,4);
    gtk_entry_set_max_length(entry7,2);
    gtk_entry_set_max_length(entry8,2);
    gtk_entry_set_max_length(entry9,4);
    gtk_entry_set_placeholder_text(entry1,"Num Contrat");
    gtk_entry_set_placeholder_text(entry2,"Id Voiture");
    gtk_entry_set_placeholder_text(entry3,"Id Client");

    gtk_entry_set_placeholder_text(entry4,"jours");
    gtk_entry_set_placeholder_text(entry5,"mois");
    gtk_entry_set_placeholder_text(entry6,"anner");
    gtk_entry_set_placeholder_text(entry7,"jours");
    gtk_entry_set_placeholder_text(entry8,"mois");
    gtk_entry_set_placeholder_text(entry9,"anner");


    gtk_entry_set_placeholder_text(entry10,"Cout en DH");

    button = gtk_button_new_with_label("add new");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry2), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry3), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry4), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry5), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry7), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry8), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry9), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry10), "insert-text", G_CALLBACK(insert_text_event), NULL);


    g_signal_connect(window, "destroy",
    G_CALLBACK(gtk_main_quit), NULL);




    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Revers_verif_id_Cont), entry1);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry7);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry8);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry9);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry10);


    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f6), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f7), entry7);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f8), entry8);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f9), entry9);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter1_f10), entry10);


    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(distroy1), (gpointer) window);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry1);


    gtk_main();

    return 0;
}


/**********************************************************************************************************************************************************************/
     // Location                                                        //       Louer        //
/************************************************************************************************************************************************************************/




void verif_id_Vr(GtkWidget *widget, gpointer entry){
    char *voitureId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));

         if(ver)
    {

        F_voiture=fopen("Voitures.txt","r");
        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);


            if(voitureId==voiture.idVoiture)
            {
                j=true;
                if(!strcmp(voiture.EnLocation,"oui"))
                {
                    messag(widget,entry,1);
                    break;
                }
                else
                {
                    open_dialog(1);
                     if(click)
                    {
                        k=true;
                        fclose(F_voiture);
                        Ajouter1();
                        if(enlocat)
                            Retourner(voitureId);
                        click=false;
                    }
                    break;
                }
            }
        }while(!feof(F_voiture));

        if(!k)
            fclose(F_voiture);
       }

    if(!j && ver && !inder)
        messag(widget, entry,3);
    inder=false;
    ver=false;
    j=false;
    k=false;
    click=false;
}


void Louer_ver(){

    GtkWidget *window,*table, *sUtf8, *label0;
    GtkWidget *label1, *label2;
    GtkWidget *entry1, *entry2;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");


    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Add New Contrat***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id Client  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Id Voiture   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");

    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");
        gtk_widget_set_name(entry2, "entry");


    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 4, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




    gtk_entry_set_placeholder_text(entry1,"Id Client");
    gtk_entry_set_placeholder_text(entry2,"Id Voiture");



    button = gtk_button_new_with_label("add new");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);


g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
g_signal_connect(G_OBJECT(entry2), "insert-text", G_CALLBACK(insert_text_event), NULL);


    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_id_Cl), entry1);
        g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_id_Vr), entry2);


         g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry2);
  gtk_main();

  return 0;

}


/**********************************************************************************************************************************************************************/
     // Location                                                        //       Retourner        //
/************************************************************************************************************************************************************************/


void verif_Vr(GtkWidget *widget, gpointer entry){
    char *voitureId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));

    F_voiture=fopen("Voitures.txt","r");
    do
    {
        fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);


        if(voitureId==voiture.idVoiture)
        {
            j=true;

            if(!strcmp(voiture.EnLocation,"oui"))
            {
                fclose(F_voiture);
                 Retourner(voitureId);
                messag(widget,entry,5);
            }
            else
                messag(widget,entry,4);

            break;
        }
    }while(!feof(F_voiture));

    fclose(F_voiture);

    if(!j)
        messag(widget, entry,3);

    chg_ver3();
    j=false;

}


void returne(){

    GtkWidget *window, *table, *sUtf8, *label0;
    GtkWidget *label1;
    GtkWidget *entry1;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");


    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Retourner Voiture***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id Voiture  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);




    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");


    entry1 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");



    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


    gtk_entry_set_placeholder_text(entry1,"Id Client");



    button = gtk_button_new_with_label("Retourn");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);



    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_Vr), entry1);

  gtk_main();
}



/**********************************************************************************************************************************************************************/
     // Location                                                        //       Modifier        //
/************************************************************************************************************************************************************************/


char *idcon;
void Mod_Fin1()
{
    FILE *F_tempcontrat;

    F_contrat=fopen("contratLocation.txt","r");
    F_tempcontrat=fopen("tempcontratLocation.txt","a");
    do
    {
            fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);

            if(idcon==contrat.numContrat)
            {
                F_text=fopen("text.txt","r");
                 do
                 {
                    fscanf(F_text,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);
                    fprintf(F_tempcontrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);
                 }while(!feof(F_text));
                fclose(F_text);
            }
            else
                fprintf(F_tempcontrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);

    }while(!feof(F_contrat));
    fclose(F_text);
    fclose(F_tempcontrat);
    fclose(F_contrat);
    remove("contratLocation.txt");
    remove("text.txt");
    rename("tempcontratLocation.txt","contratLocation.txt");

}

void Modifier1_f0(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        idcon=atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
        gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f1(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);
        gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text," %d/",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d/",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier1_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin3();
    }

}
void Modifier1_f7(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text," %d/",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin3();
    }

}
void Modifier1_f8(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d/",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin3();
    }

}
void Modifier1_f9(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d  ;",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin3();
    }

}
void Modifier1_f10(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d  \n",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin1();
    }

}
void Modifier1() {

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *labe0,*label1, *label2,*label3,*label4, *label5,*label6,*label7,*label8,*label9,*label10;
    GtkWidget *entry0,*entry1,*entry2,*entry3,*entry4,*entry5,*entry6,*entry7,*entry8,*entry9,*entry10;
    GtkWidget *button;



    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");


    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Modifier Contrat***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    labe0 = gtk_label_new("Num Contrat :");
    gtk_widget_set_halign (labe0, GTK_ALIGN_START);
    label1 = gtk_label_new("Nouveau Num  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Id Voiture   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Id Client  :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Date Debut   :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Date Fin  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Cout  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), labe0, 0, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(labe0, "lab");
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label1, "labe00");
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label6, "labe00");

    entry0 = gtk_entry_new();
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();
    entry7 = gtk_entry_new();
    entry8 = gtk_entry_new();
    entry9 = gtk_entry_new();
    entry10 = gtk_entry_new();

    gtk_widget_set_name(entry1, "entry");
    gtk_widget_set_name(entry2, "entry");
    gtk_widget_set_name(entry3, "entry");
    gtk_widget_set_name(entry4, "entry");
    gtk_widget_set_name(entry5, "entry");
    gtk_widget_set_name(entry6, "entry");
    gtk_widget_set_name(entry7, "entry");
    gtk_widget_set_name(entry8, "entry");
    gtk_widget_set_name(entry9, "entry");
    gtk_widget_set_name(entry10, "entry");


    gtk_table_attach(GTK_TABLE(table), entry0, 2, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 4, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 4, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 2, 3, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 3, 4, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry7, 1, 2, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry8, 2, 3, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry9, 3, 4, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry10, 1, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_max_length(entry4,2);
    gtk_entry_set_max_length(entry5,2);
    gtk_entry_set_max_length(entry6,4);
    gtk_entry_set_max_length(entry7,2);
    gtk_entry_set_max_length(entry8,2);
    gtk_entry_set_max_length(entry9,4);

    gtk_entry_set_placeholder_text(entry0,"Num Contrat");
    gtk_entry_set_placeholder_text(entry1,"Nouveau Num Con...");
    gtk_entry_set_placeholder_text(entry2,"Id Voiture");
    gtk_entry_set_placeholder_text(entry3,"Id Client");
    gtk_entry_set_placeholder_text(entry4,"jours");
    gtk_entry_set_placeholder_text(entry5,"mois");
    gtk_entry_set_placeholder_text(entry6,"anner");
    gtk_entry_set_placeholder_text(entry7,"jours");
    gtk_entry_set_placeholder_text(entry8,"mois");
    gtk_entry_set_placeholder_text(entry9,"anner");
    gtk_entry_set_placeholder_text(entry10,"Cout en DH");


    button = gtk_button_new_with_label("Modifier");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 8, 9,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry0), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry2), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry3), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry4), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry5), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry7), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry8), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry9), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry10), "insert-text", G_CALLBACK(insert_text_event), NULL);




    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);



     g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_id_Cont), entry0);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry7);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry8);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry9);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry10);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f0), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f6), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f7), entry7);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f8), entry8);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f9), entry9);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier1_f10), entry10);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(chg_ver3), entry0);

    gtk_main();

  return 0;
}


/**********************************************************************************************************************************************************************/
     // Location                                                       //       Suprimer        //
/************************************************************************************************************************************************************************/


void Supprimer1(id){
    FILE *F_contrat,*F_voiture,*F_client;
    FILE *F_tempcontrat,*F_tempvoiture,*F_tempclient;

        F_contrat=fopen("contratLocation.txt","r");
        F_tempcontrat=fopen("tempcontratLocation.txt","a");
        do
        {
            fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);

            if(id!=contrat.numContrat)
                fprintf(F_tempcontrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);
            else
                Retourner(contrat.idVoiture);
        }while(!feof(F_contrat));

        fclose(F_tempcontrat);
        fclose(F_contrat);
        remove("contratLocation.txt");
        rename("tempcontratLocation.txt","contratLocation.txt");

}

void verif_sup1(GtkWidget *widget, gpointer entry){
    char *contratId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));

    F_contrat=fopen("contratLocation.txt","r");
    do
    {
        fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);

        if(contratId==contrat.numContrat)
        {
            j=true;
            open_dialog(4);
            if(click)
            {
                fclose(F_contrat);
                Supprimer1(contratId);
                Retourner(contratId);
                messag(widget,entry,6);
            }
            break;
        }
    }while(!feof(F_contrat));
    fclose(F_contrat);

    if(!j)
        messag(widget,entry,7);

    chg_ver3();
    click=false;
    j=false;

}

void Afich_Suprimer1(){
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0, *label1;
    GtkWidget *entry1;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");


    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Suprimer Contrat***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id Contrat  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);


    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");


    entry1 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");



    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_entry_set_placeholder_text(entry1,"Id Contrat");



    button = gtk_button_new_with_label("Suprimer");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);


    g_signal_connect(G_OBJECT(entry1), "insert-text",
        G_CALLBACK(insert_text_event), NULL);

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_sup1), entry1);

  gtk_main();
}



/**********************************************************************************************************************************************************************/
     // Location                                                       //       Fonction Void Location        //
/************************************************************************************************************************************************************************/



void A_LOCATION(GtkWidget *widget1, gpointer window){


    GtkWidget *window1;
    GtkWidget *vbox;
    GtkWidget *grid;

    GtkWidget *Visualiser, *Louer, *Retourner_voiture, *modifier,*suprimer,*cash,*debit,*label;
    gchar* sUtf8;



    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window1, "window1");
    gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 300);
    gtk_window_set_title(GTK_WINDOW(window1), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window1), 5);

    vbox = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window1), vbox);

    grid = gtk_grid_new ();
    gtk_widget_set_name(grid, "grid");

    label = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" foreground=\"#0000FF\">"
                           "**********************************************************\n"
                           "* \t \t \t \t       ***Location d'une voiture***       \t \t \t \t * \n"
                           "**********************************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label, "label");

    Visualiser = gtk_button_new_with_label("Visualiser contrat");
    gtk_widget_set_name(Visualiser, "myButton_1");
    g_object_set (Visualiser, "margin",10, NULL);

    Louer = gtk_button_new_with_label("Louer voiture");
    gtk_widget_set_name(Louer, "myButton_2");
    g_object_set (Louer, "margin",10, NULL);

    Retourner_voiture = gtk_button_new_with_label("Retourner voiture");
    gtk_widget_set_name(Retourner_voiture, "myButton_3");
    g_object_set (Retourner_voiture, "margin",10, NULL);

    modifier = gtk_button_new_with_label("Modifier contrat");
    gtk_widget_set_name(modifier, "myButton_3");
    g_object_set (modifier, "margin",10, NULL);

    suprimer = gtk_button_new_with_label("Supprimer client");
    gtk_widget_set_name(suprimer, "myButton_3");
    g_object_set (suprimer, "margin",10, NULL);

    cash = gtk_label_new("Retour");
    debit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);

    g_object_set (grid, "margin-top",40, NULL);


    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Visualiser, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Louer, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Retourner_voiture, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), modifier, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), suprimer, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid, 1, 1, 0);

    gtk_container_add (GTK_CONTAINER (vbox), grid);
    gtk_grid_attach (GTK_GRID (grid), debit,0, 0, 1, 1);
    gtk_widget_set_name(debit, "grid_1");
    gtk_grid_attach (GTK_GRID (grid),cash , 1, 0,1 , 1);
    gtk_widget_set_name(cash, "grid_2");

    g_signal_connect(G_OBJECT(window1), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window1));


    g_signal_connect(G_OBJECT(Visualiser), "clicked",
        G_CALLBACK(Afficher1), 0);
    g_signal_connect(G_OBJECT(Louer), "clicked",
        G_CALLBACK(Louer_ver), 0);
    g_signal_connect(G_OBJECT(Retourner_voiture), "clicked",
        G_CALLBACK(returne), 0);
    g_signal_connect(G_OBJECT(modifier), "clicked",
        G_CALLBACK(Modifier1), 0);
    g_signal_connect(G_OBJECT(suprimer), "clicked",
        G_CALLBACK(Afich_Suprimer1), 0);


    g_signal_connect(G_OBJECT(debit), "clicked",
        G_CALLBACK(distroy), (gpointer)window1);



    gtk_widget_show_all(window1);

    gtk_main();

    return 0;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                    //    Gestion  Voiture    //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**********************************************************************************************************************************************************************/
     // Gestion  Voiture                                            //       Afficher        //
/************************************************************************************************************************************************************************/

void Afficher2(){
    int l;

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *button;
    GtkWidget *label;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window3");



    table = gtk_table_new(100, 8, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_set_name(table, "table_A");

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\"  >* \t***List Voitures***\t *</span>"
                            ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);

    gtk_widget_set_name(label0, "label3");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);
    gtk_table_attach(GTK_TABLE(table), label0, 0, 8, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




    label = gtk_label_new("Ligne");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Id Voiture");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("marque ");
    gtk_table_attach(GTK_TABLE(table), label, 2, 3, 1,2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Nom Voiture");
    gtk_table_attach(GTK_TABLE(table), label, 3, 4, 1,2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("couleur");
    gtk_table_attach(GTK_TABLE(table), label, 4, 5, 1,2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Nb places");
    gtk_table_attach(GTK_TABLE(table), label, 5, 6, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Prix Jour");
    gtk_table_attach(GTK_TABLE(table), label, 6, 7, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("EnLocation");
    gtk_table_attach(GTK_TABLE(table), label, 7, 8, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");




    l=2;
    F_voiture=fopen("Voitures.txt","r");
     do
    {

        fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);

        char game1[40];
        snprintf(game1, sizeof(game1), "%d   :", l-1);
        label = gtk_label_new(game1);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 0, 1, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game2[40];
        snprintf(game2, sizeof(game2), "%d", voiture.idVoiture);
        label = gtk_label_new(game2);
        gtk_widget_set_halign (label, GTK_ALIGN_CENTER);
        gtk_table_attach(GTK_TABLE(table), label, 1, 2, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game3[40];
        snprintf(game3, sizeof(game3), "%s", voiture.marque);
        label = gtk_label_new(game3);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 2, 3, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game4[40];
        snprintf(game4, sizeof(game4), "%s", voiture.nomVoiture);
        label = gtk_label_new(game4);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 3, 4, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game5[40];
        snprintf(game5, sizeof(game5), "%s", voiture.couleur);
        label = gtk_label_new(game5);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 4, 5, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game6[40];
        snprintf(game6, sizeof(game6), "%d", voiture.nbplaces);
        label = gtk_label_new(game6);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 5, 6, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game7[40];
        snprintf(game7, sizeof(game7), "%d", voiture.prixJour);
        label = gtk_label_new(game7);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 6, 7, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game8[40];
        snprintf(game8, sizeof(game8), "%s", voiture.EnLocation);
        label = gtk_label_new(game8);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 7, 8, l, l+1,
            GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        l++;

    }while(!feof(F_voiture));
    fclose(F_voiture);



    button = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 3, 5, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_widget_show_all(window);


    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(distroy), (gpointer) window);

    gtk_main();

    return 0;
}


/**********************************************************************************************************************************************************************/
     // Gestion  Voiture                                            //       Ajouter        //
/************************************************************************************************************************************************************************/


void Ajouter2_f1(GtkWidget *widget, gpointer entry){
    if(inder==false){
        F_voiture=fopen("Voitures.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_voiture,"%d ;",num1);

    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
    }

}
void Ajouter2_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_voiture," %s ;",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}
void Ajouter2_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_voiture," %s ;",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}
void Ajouter2_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_voiture," %s ;",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}
void Ajouter2_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_voiture," %d ;",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}
void Ajouter2_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_voiture,"%d ;",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}
void Ajouter2_f7(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_voiture=fopen("Voitures.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_voiture," %s \n",num1);
    fclose(F_voiture);
    gtk_entry_set_text(entry,"");
}}



void Ajouter2() {
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *label1, *label2, *label3, *label4, *label5, *label6, *label7;
    GtkWidget *entry1, *entry2, *entry3, *entry4, *entry5, *entry6, *entry7;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(9, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t     ***Add New Voiture***     \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id Voiture  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Marque   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Nom Voiture  :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Couleur   :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Nb places  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Prix Jour  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);
    label7 = gtk_label_new("EnLocation  :");
    gtk_widget_set_halign (label7, GTK_ALIGN_START);


    gtk_table_attach(GTK_TABLE(table), label0, 0, 2, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");

    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
      gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label6, "labe00");
    gtk_table_attach(GTK_TABLE(table), label7, 0, 1, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label7, "labe00");


    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();
    entry7 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");
        gtk_widget_set_name(entry2, "entry");
        gtk_widget_set_name(entry3, "entry");
        gtk_widget_set_name(entry4, "entry");
        gtk_widget_set_name(entry5, "entry");
        gtk_widget_set_name(entry6, "entry");
        gtk_widget_set_name(entry7, "entry");


    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 1, 2, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry7, 1, 2, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_placeholder_text(entry1,"Id Voiture");
    gtk_entry_set_placeholder_text(entry2,"Marque");
    gtk_entry_set_placeholder_text(entry3,"Nom Voiture");
    gtk_entry_set_placeholder_text(entry4,"Couleur");
    gtk_entry_set_placeholder_text(entry5,"Nb places");
    gtk_entry_set_placeholder_text(entry6,"Prix par jour en DH");
    gtk_entry_set_placeholder_text(entry7,"EnLocation");


    button = gtk_button_new_with_label("add new");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 2, 8, 9,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry5), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);



    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);





     g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Revers_ver_Vr), entry1);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry7);


    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f6), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter2_f7), entry7);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry1);

    gtk_main();

  return 0;
}


/**********************************************************************************************************************************************************************/
     // Gestion  Voiture                                            //       Modifier        //
/************************************************************************************************************************************************************************/


char *idco;
void Mod_Fin2(){
    FILE *F_tempvoiture;


    F_voiture=fopen("Voitures.txt","r");
    F_tempvoiture=fopen("tempVoitures.txt","a");
    do
    {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);

            if(idco==voiture.idVoiture)
            {
                F_text=fopen("text.txt","r");
                 do
                 {
                    fscanf(F_text,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
                    fprintf(F_tempvoiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
                 }while(!feof(F_text));
                fclose(F_text);
            }
            else
                fprintf(F_tempvoiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
    }while(!feof(F_voiture));

    fclose(F_tempvoiture);
        fclose(F_voiture);
        remove("Voitures.txt");
        remove("text.txt");
        rename("tempVoitures.txt","Voitures.txt");
}

void Modifier2_f0(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        idco=atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
        gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f1(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);
        gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text," %d ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier2_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text," %d  ;",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    }

}
void Modifier2_f7(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text,"%s  \n",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin2();
    }

}


void Modifier2() {

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *labe0,*label1, *label2, *label3, *label4, *label5,*label6,*label7;
    GtkWidget *entry0,*entry1, *entry2,*entry3,*entry4,*entry5,*entry6,*entry7;
    GtkWidget *button;



    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Modifier Voiture***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    labe0 = gtk_label_new("Id Voiture  :");
    gtk_widget_set_halign (labe0, GTK_ALIGN_START);
    label1 = gtk_label_new("Nouveau Id :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Marque   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Nom Voiture :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Couleur  :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Nb places  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Prix par jour  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);
    label7 = gtk_label_new("EnLocation  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 2, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_table_attach(GTK_TABLE(table), labe0, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(labe0, "lab");
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label6, "labe00");
    gtk_table_attach(GTK_TABLE(table), label7, 0, 1, 8,9,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label7, "labe00");

    entry0 = gtk_entry_new();
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();
    entry7 = gtk_entry_new();

        gtk_widget_set_name(entry1, "entry");
        gtk_widget_set_name(entry2, "entry");
        gtk_widget_set_name(entry3, "entry");
        gtk_widget_set_name(entry4, "entry");
        gtk_widget_set_name(entry5, "entry");
        gtk_widget_set_name(entry6, "entry");
        gtk_widget_set_name(entry7, "entry");


    gtk_table_attach(GTK_TABLE(table), entry0, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 1, 2, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
     gtk_table_attach(GTK_TABLE(table), entry7, 1, 2, 8, 9,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_placeholder_text(entry0,"Id Voiture");
    gtk_entry_set_placeholder_text(entry1,"Nouveau Id Voi...");
    gtk_entry_set_placeholder_text(entry2,"Marque");
    gtk_entry_set_placeholder_text(entry3,"Nom Voiture");
    gtk_entry_set_placeholder_text(entry4,"Couleur");
    gtk_entry_set_placeholder_text(entry5,"Nb places");
    gtk_entry_set_placeholder_text(entry6,"Prix par jour en DH");
    gtk_entry_set_placeholder_text(entry7,"EnLocation");;



    button = gtk_button_new_with_label("Modifier");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 2, 9, 10,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry0), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry5), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);



     g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(ver_Vr), entry0);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry7);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f0), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f6), entry6);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier2_f7), entry7);


    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry0);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(chg_ver3), entry0);

    gtk_main();

  return 0;
}


/**********************************************************************************************************************************************************************/
     // Gestion  Voiture                                            //       Suprimer        //
/************************************************************************************************************************************************************************/



void Supprimer2(id)
{
    FILE *F_contrat,*F_voiture,*F_client;
    FILE *F_tempcontrat,*F_tempvoiture,*F_tempclient;

        F_voiture=fopen("Voitures.txt","r");
        F_tempvoiture=fopen("tempVoitures.txt","a");

        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);

            if(id!=voiture.idVoiture)
                fprintf(F_tempvoiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);

        }while(!feof(F_voiture));

        fclose(F_tempvoiture);
        fclose(F_voiture);
        remove("Voitures.txt");
        rename("tempVoitures.txt","Voitures.txt");

}

void verif_sup2(GtkWidget *widget, gpointer entry){
    char *voitureId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));

    F_voiture=fopen("Voitures.txt","r");
    do
    {
        fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
        if(voitureId==voiture.idVoiture)
        {
            j=true;
            open_dialog(4);
            if(click)
            {
                fclose(F_voiture);
                Supprimer2(voitureId);
                messag(widget,entry,6);
            }
            break;
        }
    }while(!feof(F_voiture));
    fclose(F_voiture);

    if(!j)
        messag(widget,entry,3);

    chg_ver3();
    click=false;
    j=false;

}

void Afich_Suprimer2(){
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;

    GtkWidget *label1;
    GtkWidget *entry1;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Suprimer Voiture***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id Voiture  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);


    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");


    entry1 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");



    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


    gtk_entry_set_placeholder_text(entry1,"Id Voiture");



    button = gtk_button_new_with_label("Suprimer");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);



    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_sup2), entry1);

  gtk_main();
}


/**********************************************************************************************************************************************************************/
     // Gestion  Voiture                                            //       Fonction Void Voiture        //
/************************************************************************************************************************************************************************/


void A_VOITURES(GtkWidget *widget, gpointer window){


    GtkWidget *window2;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *Liste,*Ajouter, *Modifier,*suprimer,*cash, *debit, *label;
    gchar* sUtf8;



    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window2, "window1");
    gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window2), 500, 400);
    gtk_window_set_title(GTK_WINDOW(window2), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window2), 5);


    vbox = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window2), vbox);

    grid = gtk_grid_new ();
    gtk_widget_set_name(grid, "grid");

    label = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" foreground=\"#0000FF\">"
                           "**********************************************************\n"
                           "* \t \t \t \t       ***Gestion des voitures***       \t \t \t \t * \n"
                           "**********************************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label, "label");

    Liste = gtk_button_new_with_label("Liste des voitures");
    gtk_widget_set_name(Liste, "myButton_1");
    g_object_set (Liste, "margin",10, NULL);

    Ajouter = gtk_button_new_with_label("Ajouter voiture");
    gtk_widget_set_name(Ajouter, "myButton_2");
    g_object_set (Ajouter, "margin",10, NULL);

    Modifier = gtk_button_new_with_label("Modifier voiture");
    gtk_widget_set_name(Modifier, "myButton_3");
    g_object_set (Modifier, "margin",10, NULL);

    suprimer = gtk_button_new_with_label("Supprimer voiture");
    gtk_widget_set_name(suprimer, "myButton_3");
    g_object_set (suprimer, "margin",10, NULL);

    cash = gtk_label_new("Retour");
    debit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);

    g_object_set (grid, "margin-top",40, NULL);


    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Liste, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Ajouter, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Modifier, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), suprimer, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (vbox), grid);
    gtk_grid_attach (GTK_GRID (grid), debit, 0, 0, 1, 1);
    gtk_widget_set_name(debit, "grid_1");
    gtk_grid_attach (GTK_GRID (grid),cash , 1, 0,1 , 1);
    gtk_widget_set_name(cash, "grid_2");

        g_signal_connect(G_OBJECT(window2), "destroy",
            G_CALLBACK(gtk_main_quit), G_OBJECT(window2));

        g_signal_connect(G_OBJECT(Liste), "clicked",
            G_CALLBACK(Afficher2),NULL);
        g_signal_connect(G_OBJECT(Ajouter), "clicked",
            G_CALLBACK(Ajouter2),NULL);
        g_signal_connect(G_OBJECT(Modifier), "clicked",
            G_CALLBACK(Modifier2),NULL);
        g_signal_connect(G_OBJECT(suprimer), "clicked",
            G_CALLBACK(Afich_Suprimer2),NULL);

        g_signal_connect(G_OBJECT(debit), "clicked",
            G_CALLBACK(distroy), (gpointer) window2);

    gtk_widget_show_all(window2);

    gtk_main();

    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                    //    Gestion  de  Client     //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**********************************************************************************************************************************************************************/
     // Gestion  Client                                           //       Afficher        //
/************************************************************************************************************************************************************************/

void Afficher3()
{
    int l;

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *labe;





    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window3");



    table = gtk_table_new(100, 7, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_set_name(table, "table_A");

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\"  >* \t***List Clients***\t *</span>"
                            ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);

    gtk_widget_set_name(label0, "label3");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);
    gtk_table_attach(GTK_TABLE(table), label0, 0, 7, 0, 1,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);




    label = gtk_label_new("Ligne");
    gtk_table_attach(GTK_TABLE(table), label, 0, 1, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Id Client");
    gtk_table_attach(GTK_TABLE(table), label, 1, 2, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Nom ");
    gtk_table_attach(GTK_TABLE(table), label, 2, 3, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Prennom");
    gtk_table_attach(GTK_TABLE(table), label, 3, 4, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Cin");
    gtk_table_attach(GTK_TABLE(table), label, 4, 5, 1,2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Adresse");
    gtk_table_attach(GTK_TABLE(table), label, 5, 6, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");

    label = gtk_label_new("Telephon");
    gtk_table_attach(GTK_TABLE(table), label, 6, 7, 1, 2,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label, "labe4");




    l=2;
    F_client=fopen("Clients.txt","r");
    do
    {

        fscanf(F_client,"%d ; %s ; %s ; %d ; %s ; %d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);

        char game1[40];
        snprintf(game1, sizeof(game1), "%d   :", l-1);
        label = gtk_label_new(game1);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 0, 1, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game2[40];
        snprintf(game2, sizeof(game2), "%d", client.idClient);
        label = gtk_label_new(game2);
        gtk_widget_set_halign (label, GTK_ALIGN_CENTER);
        gtk_table_attach(GTK_TABLE(table), label, 1, 2, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game3[40];
        snprintf(game3, sizeof(game3), "%s", client.nom);
        label = gtk_label_new(game3);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 2, 3, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game4[40];
        snprintf(game4, sizeof(game4), "%s", client.prenom);
        label = gtk_label_new(game4);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 3, 4, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game5[40];
        snprintf(game5, sizeof(game5), "%d", client.cin);
        label = gtk_label_new(game5);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 4, 5, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game6[40];
        snprintf(game6, sizeof(game6), "%s", client.adresse);
        label = gtk_label_new(game6);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 5, 6, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        char game7[40];
        snprintf(game7, sizeof(game7), "%d", client.telephone);
        label = gtk_label_new(game7);
        gtk_widget_set_halign (label, GTK_ALIGN_START);
        gtk_table_attach(GTK_TABLE(table), label, 6, 7, l, l+1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(label, "labe5");

        l++;

    }while(!feof(F_client));
    fclose(F_client);



    button = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 2, 5, l, l+1,
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_widget_show_all(window);


    g_signal_connect(window, "destroy",
    G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
    G_CALLBACK(distroy), (gpointer) window);


    gtk_main();

    return 0;
}

/**********************************************************************************************************************************************************************/
     // Gestion  Client                                           //       Ajouter        //
/************************************************************************************************************************************************************************/


void Ajouter3_f1(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_client,"%d ;",num1);

    fclose(F_client);
        gtk_entry_set_text(entry,"");
    }
}
void Ajouter3_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_client," %s ;",num1);

    fclose(F_client);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter3_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_client," %s ;",num1);

    fclose(F_client);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter3_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_client," %d ;",num1);

    fclose(F_client);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter3_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_client," %s ;",num1);

    fclose(F_client);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter3_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_client=fopen("Clients.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_client,"%d  \n",num1);

    fclose(F_client);
    gtk_entry_set_text(entry,"");
    }
}
void Ajouter3() {

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *label1, *label2, *label3, *label4, *label5, *label6;
    GtkWidget *entry1,*entry2,*entry3,*entry4,*entry5,*entry6;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Add New Client***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id_Client  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Nom   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Prennom  :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Cin   :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Adresse  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Telephon  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 2, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");

    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label6, "labe00");

    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");
        gtk_widget_set_name(entry2, "entry");
        gtk_widget_set_name(entry3, "entry");
        gtk_widget_set_name(entry4, "entry");
        gtk_widget_set_name(entry5, "entry");
        gtk_widget_set_name(entry6, "entry");


    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 1, 2, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_placeholder_text(entry1,"Id Client");
    gtk_entry_set_placeholder_text(entry2,"Nom");
    gtk_entry_set_placeholder_text(entry3,"Prennom");
    gtk_entry_set_placeholder_text(entry4,"Cin");
    gtk_entry_set_placeholder_text(entry5,"Adresse");
    gtk_entry_set_placeholder_text(entry6,"Telephon");



    button = gtk_button_new_with_label("add new");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 2, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry4), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);



    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Revers_verif_id_Cl), entry1);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Ajouter3_f6), entry6);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry1);

    gtk_main();

  return 0;
}

/**********************************************************************************************************************************************************************/
     // Gestion  Client                                           //       Modifier        //
/************************************************************************************************************************************************************************/


char *idcl;
void Mod_Fin3()
{
    FILE *F_tempclient;


        F_client=fopen("Clients.txt","r");
        F_tempclient=fopen("tempclient.txt","a");
        do
        {
            fscanf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);

                if(idcl==client.idClient)
                {
                    F_text=fopen("text.txt","r");
                     do
                     {
                        fscanf(F_text,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
                        fprintf(F_tempclient,"%d ; %s ; %s ; %d ; %s ;%d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
                     }while(!feof(F_text));
                    fclose(F_text);
                }
                else
                fprintf(F_tempclient,"%d ; %s ; %s ; %d ; %s ;%d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);

        }while(!feof(F_client));

        fclose(F_text);
        fclose(F_tempclient);
        fclose(F_client);
        remove("Clients.txt");
        remove("text.txt");
        rename("tempclient.txt","Clients.txt");


}

void Modifier3_f0(GtkWidget *widget, gpointer entry){
    if(!inder)
    {
        idcl=atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
        gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f1(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d ;",num1);

    fclose(F_text);
        gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f2(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f3(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f4(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text," %d ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f5(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = gtk_entry_get_text(GTK_ENTRY(entry));
    fprintf(F_text," %s ;",num1);

    fclose(F_text);
    gtk_entry_set_text(entry,"");
    }
}
void Modifier3_f6(GtkWidget *widget, gpointer entry){
    if(!inder){
    F_text=fopen("text.txt","a");

    char *num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(entry)));
    fprintf(F_text,"%d  \n",num1);

    fclose(F_text);

    gtk_entry_set_text(entry,"");
    Mod_Fin3();
    }

}
void Modifier3() {

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;
    GtkWidget *labe0,*label1,*label2, *label3, *label4, *label5, *label6;
    GtkWidget *entry0,*entry1, *entry2, *entry3, *entry4, *entry5, *entry6;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Modifier Client***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    labe0 = gtk_label_new("Id_Client  :");
    gtk_widget_set_halign (labe0, GTK_ALIGN_START);
    label1 = gtk_label_new("Nouveau Id :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);
    label2 = gtk_label_new("Nom   :");
    gtk_widget_set_halign (label2, GTK_ALIGN_START);
    label3 = gtk_label_new("Prennom  :");
    gtk_widget_set_halign (label3, GTK_ALIGN_START);
    label4 = gtk_label_new("Cin   :");
    gtk_widget_set_halign (label4, GTK_ALIGN_START);
    label5 = gtk_label_new("Adresse  :");
    gtk_widget_set_halign (label5, GTK_ALIGN_START);
    label6 = gtk_label_new("Telephon  :");
    gtk_widget_set_halign (label6, GTK_ALIGN_START);



    gtk_table_attach(GTK_TABLE(table), label0, 0, 2, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_table_attach(GTK_TABLE(table), labe0, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
        gtk_widget_set_name(labe0, "lab");
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");
    gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label2, "labe00");
    gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label3, "labe00");
    gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label4, "labe00");
    gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label5, "labe00");
    gtk_table_attach(GTK_TABLE(table), label6, 0, 1, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label6, "labe00");

    entry0 = gtk_entry_new();
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry3 = gtk_entry_new();
    entry4 = gtk_entry_new();
    entry5 = gtk_entry_new();
    entry6 = gtk_entry_new();

        gtk_widget_set_name(entry1, "entry");
        gtk_widget_set_name(entry2, "entry");
        gtk_widget_set_name(entry3, "entry");
        gtk_widget_set_name(entry4, "entry");
        gtk_widget_set_name(entry5, "entry");
        gtk_widget_set_name(entry6, "entry");


    gtk_table_attach(GTK_TABLE(table), entry0, 1, 2, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 2, 3,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 3, 4,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 4, 5,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry4, 1, 2, 5, 6,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry5, 1, 2, 6, 7,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), entry6, 1, 2, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    gtk_entry_set_placeholder_text(entry0,"Id Client");
    gtk_entry_set_placeholder_text(entry1,"Nouveau Id Cli...");
    gtk_entry_set_placeholder_text(entry2,"Nom");
    gtk_entry_set_placeholder_text(entry3,"Prennom");
    gtk_entry_set_placeholder_text(entry4,"Cin");
    gtk_entry_set_placeholder_text(entry5,"Adresse");
    gtk_entry_set_placeholder_text(entry6,"Telephon");



    button = gtk_button_new_with_label("Modifier");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 2, 8, 9,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry0), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry4), "insert-text", G_CALLBACK(insert_text_event), NULL);
    g_signal_connect(G_OBJECT(entry6), "insert-text", G_CALLBACK(insert_text_event), NULL);

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);



     g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_id_Cl), entry0);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(insert_text), entry6);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f0), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f1), entry1);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f2), entry2);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f3), entry3);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f4), entry4);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f5), entry5);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(Modifier3_f6), entry6);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(change), entry0);
    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(chg_ver3), entry0);

    gtk_main();

  return 0;
}

/**********************************************************************************************************************************************************************/
     // Gestion  Client                                           //       Suprimer        //
/************************************************************************************************************************************************************************/



void Supprimer3(int id)
{

    FILE *F_contrat,*F_voiture,*F_client;
    FILE *F_tempcontrat,*F_tempvoiture,*F_tempclient;

        F_client=fopen("Clients.txt","r");
        F_tempclient=fopen("tempclient.txt","a");


        do
        {
            fscanf(F_client,"%d ; %s ; %s ; %d ; %s ; %d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);

            if(id!=client.idClient)
                fprintf(F_tempclient,"%d ; %s ; %s ; %d ; %s ; %d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);

        }while(!feof(F_client));

        fclose(F_tempclient);
        fclose(F_client);
        remove("Clients.txt");
        rename("tempclient.txt","Clients.txt");


}

void verif_sup3(GtkWidget *widget, gpointer entry){
    char *clientId =atoi((char *) gtk_entry_get_text(GTK_ENTRY(entry)));

    F_client=fopen("Clients.txt","r");
    do
    {
        fscanf(F_client,"%d ; %s ; %s ; %d ; %s ; %d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);


        if(clientId==client.idClient)
        {
            j=true;
            open_dialog(4);
            if(click)
            {
                fclose(F_client);
                Supprimer3(clientId);
                messag(widget,entry,6);
            }
            break;
        }
    }while(!feof(F_client));
    fclose(F_client);

    if(!j)
        messag(widget,entry,2);

    chg_ver3();
    click=false;
    j=false;

}

void Afich_Suprimer3(){
    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *sUtf8;
    GtkWidget *label0;

    GtkWidget *label1;
    GtkWidget *entry1;
    GtkWidget *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_name(window, "window2");



    table = gtk_table_new(8, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);

    label0 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" >"
                           "*************************************\n"
                           "* \t \t***Suprimer Client***\t \t *\n"
                           "*************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label0), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label0, "labe2");
    gtk_widget_set_halign (label0, GTK_ALIGN_CENTER);

    label1 = gtk_label_new("Id client  :");
    gtk_widget_set_halign (label1, GTK_ALIGN_START);


    gtk_table_attach(GTK_TABLE(table), label0, 0, 4, 0, 1,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    gtk_widget_set_name(label1, "labe00");


    entry1 = gtk_entry_new();
        gtk_widget_set_name(entry1, "entry");



    gtk_table_attach(GTK_TABLE(table), entry1, 1, 4, 1, 2,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);


    gtk_entry_set_placeholder_text(entry1,"Id client");



    button = gtk_button_new_with_label("Suprimer");
    gtk_widget_set_name(button, "button4");
    gtk_table_attach(GTK_TABLE(table), button, 0, 4, 7, 8,
        GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);



    gtk_widget_show_all(window);

    g_signal_connect(G_OBJECT(entry1), "insert-text", G_CALLBACK(insert_text_event), NULL);



    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(button), "clicked",
        G_CALLBACK(verif_sup3), entry1);

  gtk_main();
}


/**********************************************************************************************************************************************************************/
     // Gestion  Client                                           //       Fonction Void Client        //
/************************************************************************************************************************************************************************/


void A_CLIENT(GtkWidget *widget1, gpointer window){
    gpointer *window3;
    GtkWidget *widget;
    GtkWidget *vbox;
    GtkWidget *grid;
    GtkWidget *Liste, *Ajouter, *Modifier,*suprimer, *cash, *debit,*label;
    gchar* sUtf8;


    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window3, "window1");

    gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window3), 500, 400);
    gtk_window_set_title(GTK_WINDOW(window3), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window3), 5);


    vbox = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window3), vbox);

    grid = gtk_grid_new ();
    gtk_widget_set_name(grid, "grid");

    label = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" foreground=\"#0000FF\">"
                           "**********************************************************\n"
                           "* \t \t \t \t       ***Gestion des clients***       \t \t \t \t * \n"
                           "**********************************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label, "label");

    Liste = gtk_button_new_with_label("Liste des clients");
    gtk_widget_set_name(Liste, "myButton_1");
    g_object_set (Liste, "margin",10, NULL);

    Ajouter = gtk_button_new_with_label("Ajouter client");
    gtk_widget_set_name(Ajouter, "myButton_2");
    g_object_set (Ajouter, "margin",10, NULL);

    Modifier = gtk_button_new_with_label("Modifier client");
    gtk_widget_set_name(Modifier, "myButton_3");
    g_object_set (Modifier, "margin",10, NULL);

    suprimer = gtk_button_new_with_label("Supprimer client");
    gtk_widget_set_name(suprimer, "myButton_3");
    g_object_set (suprimer, "margin",10, NULL);

    cash = gtk_label_new("Retour");
    debit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);

    g_object_set (grid, "margin-top",40, NULL);


    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Liste, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Ajouter, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Modifier, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), suprimer, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (vbox), grid);
    gtk_grid_attach (GTK_GRID (grid), debit, 0, 0, 1, 1);
    gtk_widget_set_name(debit, "grid_1");
    gtk_grid_attach (GTK_GRID (grid),cash , 1, 0,1 , 1);
    gtk_widget_set_name(cash, "grid_2");

    g_signal_connect(G_OBJECT(window3), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window3));

    g_signal_connect(G_OBJECT(Liste), "clicked",
        G_CALLBACK(Afficher3),NULL);
    g_signal_connect(G_OBJECT(Ajouter), "clicked",
        G_CALLBACK(Ajouter3),NULL);
    g_signal_connect(G_OBJECT(Modifier), "clicked",
        G_CALLBACK(Modifier3),NULL);
    g_signal_connect(G_OBJECT(suprimer), "clicked",
        G_CALLBACK(Afich_Suprimer3),NULL);

    g_signal_connect(G_OBJECT(debit), "clicked",
        G_CALLBACK(distroy), (gpointer) window3);

    gtk_widget_show_all(window3);

    gtk_main();

    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                                                //    Main  Function    //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *grid;

    GtkWidget *Location;
    GtkWidget *voitures;
    GtkWidget *client;
    GtkWidget *cash;
    GtkWidget *debit;
    GtkWidget *label;
    gchar* sUtf8;



    gtk_init(&argc, &argv);

        myCSS();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window, "window0");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_title(GTK_WINDOW(window), "GtkVBox");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);


    vbox = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    grid = gtk_grid_new();
    gtk_widget_set_name(grid, "grid");

    label = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span font_desc=\" Georgia, serif\" foreground=\"#0000FF\">"
                           "**********************************************************\n"
                           "* \t \t \t \t       ***Menu Principal***       \t \t \t \t * \n"
                           "**********************************************************</span>\n"
                           ,-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(label), sUtf8);
    g_free(sUtf8);
    gtk_widget_set_name(label, "label");

    Location = gtk_button_new_with_label("Location");
    gtk_widget_set_name(Location, "myButton_1");
    g_object_set (Location, "margin",10, NULL);

    voitures = gtk_button_new_with_label("Gestion voitures");
    gtk_widget_set_name(voitures, "myButton_2");
    g_object_set (voitures, "margin",10, NULL);

    client = gtk_button_new_with_label("Gestion client");
    gtk_widget_set_name(client, "myButton_3");
    g_object_set (client, "margin",10, NULL);

    cash = gtk_label_new("Quitter");
    debit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);

    g_object_set (grid, "margin-top",40, NULL);


    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), Location, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), voitures, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), client, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (vbox), grid);
    gtk_grid_attach (GTK_GRID (grid), debit, 0, 0, 1, 1);
    gtk_widget_set_name(debit, "grid_1");
    gtk_grid_attach (GTK_GRID (grid),cash , 1, 0, 1, 1);
    gtk_widget_set_name(cash, "grid_2");

    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));


    g_signal_connect(G_OBJECT(Location), "clicked",
        G_CALLBACK(A_LOCATION), NULL);
    g_signal_connect(G_OBJECT(voitures), "clicked",
        G_CALLBACK(A_VOITURES), NULL);
    g_signal_connect(G_OBJECT(client), "clicked",
        G_CALLBACK(A_CLIENT), NULL);


    g_signal_connect(G_OBJECT(debit), "clicked",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();



    return 0;

}
