
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false 0
#define true !false

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


///////////////////////////////////////////////////////////////////////////////////




void Ajouter(int h)
{

    FILE *F_contrat,*F_voiture,*F_client;
      switch(h)
      {
        case 1:
            F_contrat=fopen("contratLocation.txt","a");

            printf("numContrat: -");
            scanf("%d",&contrat.numContrat);

            printf("idVoiture : -");
            scanf("%d",&contrat.idVoiture);

            printf("idClient  : -");
            scanf("%d",&contrat.idClient);

            printf("date debut:\n");
            printf("jour      : -");
            scanf("%d",&contrat.debut.jours);

            printf("mois      : -");
            scanf("%d",&contrat.debut.mois);

            printf("anner     : -");
            scanf("%d",&contrat.debut.anner);
             printf("date fin:\n");
            printf("jour      : -");
            scanf("%d",&contrat.fin.jours);

            printf("mois      : -");
            scanf("%d",&contrat.fin.mois);

            printf("anner     : -");
            scanf("%d",&contrat.fin.anner);

            printf("cout      : -");
            scanf("%d",&contrat.cout);

            fprintf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);
            fclose(F_contrat);
            break;

        case 2:
            F_voiture=fopen("Voitures.txt","a");

            printf("idVoiture : -");
            scanf("%d",&voiture.idVoiture);

            printf("marque    : -");
            scanf("%s",&voiture.marque);

            printf("nomVoiture: -");
            scanf("%s",&voiture.nomVoiture);

            printf("couleur   : -");
            scanf("%s",&voiture.couleur);

            printf("nbplaces  : -");
            scanf("%d",&voiture.nbplaces);

            printf("prixJour  : -");
            scanf("%d",&voiture.prixJour);

            printf("EnLocation: -");
            scanf("%s",&voiture.EnLocation);

            fprintf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
            fclose(F_voiture);
            break;

        case 3:
            F_client=fopen("Clients.txt","a");

            printf("idClient  : -");
            scanf("%d",&client.idClient);

            printf("nom       : -");
            scanf("%s",&client.nom);

            printf("prenom    : -");
            scanf("%s",&client.prenom);

            printf("cin       : -");
            scanf("%d",&client.cin);

            printf("adresse   : -");
            scanf("%s",&client.adresse);

            printf("telephone : -");
            scanf("%d",&client.telephone);

            fprintf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
            fclose(F_client);
            break;

      }

}

void Afficher(int h)
{
    FILE *F_contrat,*F_voiture,*F_client;
      switch(h)
      {
        case 1:
            F_contrat=fopen("contratLocation.txt","r");
            printf("numContrat  ;  idVoiture  ;  idClient  ;  debut:jours/mois/anner  ;  fin:jours/mois/anner  ;  cout\n");
            do
            {
                fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);
                printf("%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);
            }while(!feof(F_contrat));
            fclose(F_contrat);
            break;

        case 2:
            F_voiture=fopen("Voitures.txt","r");
            printf("idVoiture  ;  marque  ;  nomVoiture  ;  couleur  ;  nbplaces  ;  prixJour  ;  EnLocation\n");
            do
            {
                fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
                printf("%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
            }while(!feof(F_voiture));
            fclose(F_voiture);
            break;

        case 3:
            F_client=fopen("Clients.txt","r");
            printf("idClient  ;  nom  ;  prenom  ;  cin  ;  adresse  ;  telephone\n");
            do
            {
                fscanf(F_client,"%d ; %s ; %s ; %d ; %s ; %d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
                printf("%d ; %s ; %s ; %d ; %s ; %d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
            }while(!feof(F_client));
            fclose(F_client);
            break;
      }

}

void Retourner(int id)
{

        FILE *F_contrat,*F_voiture,*F_client,*F_tempvoiture;
        int c;
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

void verification()
{
    int i=false,j=false,k=false,voitureId;
    char Nom[20],prennom[20],con;
    FILE *F_contrat,*F_voiture,*F_client;

    printf("Entre le nom , prennom\n");
    scanf("%s %s",&Nom,&prennom);
    F_client=fopen("Clients.txt","r");
    do
    {
        fscanf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);
        if((strcmp(Nom,client.nom)==0 && strcmp(prennom,client.prenom)==0)||(strcmp(Nom,client.prenom)==0 && strcmp(prennom,client.nom)==0))
        {
            i=true;
            break;
        }
    }while(!feof(F_client));
    fclose(F_client);

    if(i)
    {
        printf("Entre l'Id du voiture\n");
        scanf("%d",&voitureId);

        F_voiture=fopen("Voitures.txt","r");
        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);
            printf("%d    %s\n",voiture.idVoiture,voiture.EnLocation);
            if(voitureId==voiture.idVoiture)
            {
                j=true;
                if(!strcmp(voiture.EnLocation,"oui"))
                {
                    printf("cette voiture n est pas disponible");
                    break;
                }
                else
                {
                    printf("vou voulez crier un novou contrat(o/y):");
                    scanf("%s",&con);
                    if(con=='o' || con=='O')
                    {
                        k=true;
                        fclose(F_voiture);
                        Retourner(voitureId);
                        printf(" %s \n",voiture.EnLocation);
                        Ajouter(1);
                        break;
                    }
                }
            }
        }while(!feof(F_voiture));

        if(!k)
            fclose(F_voiture);
    }
    else
    {
        printf("enregistrer votre propres informations a travers le menu ( Gestion clients )\n");
    }
    if(!j && i)
        printf("la voiture demande n existe pas");
}



void Modifier(int h)
{
    int id;
    FILE *F_contrat,*F_voiture,*F_client;
    FILE *F_tempcontrat,*F_tempvoiture,*F_tempclient;
    switch(h)
    {
    case 1:

        F_contrat=fopen("contratLocation.txt","r");
        F_tempcontrat=fopen("tempcontratLocation.txt","a");

        printf("numContrat : -");
        scanf("%d",&id);

        do
        {
                fscanf(F_contrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",&contrat.numContrat,&contrat.idVoiture,&contrat.idClient,&contrat.debut.jours,&contrat.debut.mois,&contrat.debut.anner,&contrat.fin.jours,&contrat.fin.mois,&contrat.fin.anner,&contrat.cout);
                if(id==contrat.numContrat)
                {
                    printf("numContrat: -");
                    scanf("%d",&contrat.numContrat);

                    printf("idVoiture : -");
                    scanf("%d",&contrat.idVoiture);

                    printf("idClient  : -");
                    scanf("%d",&contrat.idClient);

                    printf("date debut:\n");
                    printf("jour      : -");
                    scanf("%d",&contrat.debut.jours);

                    printf("mois      : -");
                    scanf("%d",&contrat.debut.mois);

                    printf("anner     : -");
                    scanf("%d",&contrat.debut.anner);

                    printf("date fin:\n");
                    printf("jour      : -");
                    scanf("%d",&contrat.fin.jours);

                    printf("mois      : -");
                    scanf("%d",&contrat.fin.mois);

                    printf("anner     : -");
                    scanf("%d",&contrat.fin.anner);

                    printf("cout      : -");
                    scanf("%d",&contrat.cout);
                }

                fprintf(F_tempcontrat,"%d ; %d ; %d ; %d/%d/%d ; %d/%d/%d ; %d \n",contrat.numContrat,contrat.idVoiture,contrat.idClient,contrat.debut.jours,contrat.debut.mois,contrat.debut.anner,contrat.fin.jours,contrat.fin.mois,contrat.fin.anner,contrat.cout);
        }while(!feof(F_contrat));

        fclose(F_tempcontrat);
        fclose(F_contrat);
        remove("contratLocation.txt");
        rename("tempcontratLocation.txt","contratLocation.txt");

        break;

    case 2:

        F_voiture=fopen("Voitures.txt","r");
        F_tempvoiture=fopen("tempVoitures.txt","a");

        printf("idVoiture");
        scanf("%d",&id);

        do
        {
            fscanf(F_voiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",&voiture.idVoiture,&voiture.marque,&voiture.nomVoiture,&voiture.couleur,&voiture.nbplaces,&voiture.prixJour,&voiture.EnLocation);

                if(id==voiture.idVoiture)
                {
                    printf("idVoiture : -");
                    scanf("%d",&voiture.idVoiture);

                    printf("marque    : -");
                    scanf("%s",&voiture.marque);

                    printf("nomVoiture: -");
                    scanf("%s",&voiture.nomVoiture);

                    printf("couleur   : -");
                    scanf("%s",&voiture.couleur);

                    printf("nbplaces  : -");
                    scanf("%d",&voiture.nbplaces);

                    printf("prixJour  : -");
                    scanf("%d",&voiture.prixJour);

                    printf("EnLocation: -");
                    scanf("%s",&voiture.EnLocation);
                }

                fprintf(F_tempvoiture,"%d ; %s ; %s ; %s ; %d ;%d ; %s \n",voiture.idVoiture,voiture.marque,voiture.nomVoiture,voiture.couleur,voiture.nbplaces,voiture.prixJour,voiture.EnLocation);
        }while(!feof(F_voiture));

        fclose(F_tempvoiture);
        fclose(F_voiture);
        remove("Voitures.txt");
        rename("tempVoitures.txt","Voitures.txt");

        break;

    case 3:

        F_client=fopen("Clients.txt","r");
        F_tempclient=fopen("tempclient.txt","a");

        printf("idClient : -");
        scanf("%d",&id);

        do
        {
            fscanf(F_client,"%d ; %s ; %s ; %d ; %s ;%d  \n",&client.idClient,&client.nom,&client.prenom,&client.cin,&client.adresse,&client.telephone);

                if(id==client.idClient)
                {
                    printf("idClient  : -");
                    scanf("%d",&client.idClient);

                    printf("nom       : -");
                    scanf("%s",&client.nom);

                    printf("prenom    : -");
                    scanf("%s",&client.prenom);

                    printf("cin       : -");
                    scanf("%d",&client.cin);

                    printf("adresse   : -");
                    scanf("%s",&client.adresse);

                    printf("telephone : -");
                    scanf("%d",&client.telephone);
                }

                fprintf(F_tempclient,"%d ; %s ; %s ; %d ; %s ;%d  \n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
        }while(!feof(F_client));

        fclose(F_tempclient);
        fclose(F_client);
        remove("Clients.txt");
        rename("tempclient.txt","Clients.txt");
        break;
    }

}



void Supprimer(int h)
{
     int id;
    FILE *F_contrat,*F_voiture,*F_client;
    FILE *F_tempcontrat,*F_tempvoiture,*F_tempclient;
    switch(h)
    {
    case 1:

        F_contrat=fopen("contratLocation.txt","r");
        F_tempcontrat=fopen("tempcontratLocation.txt","a");

        printf("numContrat : -");
        scanf("%d",&id);

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

        break;

    case 2:

        F_voiture=fopen("Voitures.txt","r");
        F_tempvoiture=fopen("tempVoitures.txt","a");

        printf("idVoiture");
        scanf("%d",&id);

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

        break;

    case 3:

        F_client=fopen("Clients.txt","r");
        F_tempclient=fopen("tempclient.txt","a");

        printf("idClient : -");
        scanf("%d",&id);

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
        break;
    }


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Location(int h)
{

    int i=0,j,id;
    while(i!=6)
    {
        printf("\n//--------------Location d'une voiture--------------//\n");
        printf("Visualiser contrat....................1\n");
        printf("Louer voiture.........................2\n");
        printf("Retourner voiture.....................3\n");
        printf("Modifier contrat......................4\n");
        printf("Supprimer contrat.....................5\n");
        printf("Retour................................6\n");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                Afficher(h);
                break;
            case 2:
                verification();
                break;
            case 3:
                printf("entre idVoiture : -");
                scanf("%d",&id);
                Retourner(id);
                break;
            case 4:
                Modifier(h);
                break;
            case 5:
                Supprimer(h);
                break;
            case 6:
                break;
        }
    }
}
void voitures(int h)
{
    int i=0,j;
    while(i!=5)
    {
        printf("\n//--------------Gestion des voitures--------------//\n");
        printf("Liste des voitures....................1\n");
        printf("Ajouter voiture.......................2\n");
        printf("Modifier voiture......................3\n");
        printf("Supprimer voiture.....................4\n");
        printf("Retour................................5\n");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                Afficher(h);
                break;
            case 2:
                Ajouter(h);
                break;
            case 3:
                Modifier(h);
                break;
            case 4:
                Supprimer(h);
                break;
            case 5:
                break;
        }
    }
}

void clients(int h)
{
    int i=0,j;
    while(i!=5)
    {
        printf("\n//--------------Gestion des clients--------------//\n");
        printf("Liste des clients.....................1\n");
        printf("Ajouter client........................2\n");
        printf("Modifier client.......................3\n");
        printf("Supprimer client......................4\n");
        printf("Retour................................5\n");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                Afficher(h);
                break;
            case 2:
                Ajouter(h);
                break;
            case 3:
                Modifier(h);
                break;
            case 4:
                Supprimer(h);
                break;
            case 5:
                break;
        }
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
    int h=0;
    while(h!=4)
    {
        printf("\n//--------------Menu Principal--------------//\n");
        printf("Location..............................1\n");
        printf("Gestion voitures......................2\n");
        printf("Gestion client........................3\n");
        printf("Quitter...............................4\n");
        scanf("%d",&h);
        switch(h)
        {
            case 1:
                Location(h);
                break;
            case 2:
                voitures(h);
                break;
            case 3:
                clients(h);
                break;
            case 4:
                printf("\n//--------------Exit--------------//\n");
                break;
        }
    }
return 0;
}
