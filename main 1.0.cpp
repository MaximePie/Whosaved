#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#define TAILLE_MAX_NomObjet 18

typedef struct
{
    char name[16];

    int pv;
    int pv_max;
    int mana;
    int mana_max;

    int force;
    int agilite;
    int defense;
    int dexterite;
    int intelligence;

    int charisme;
    int xp;
    int xp_pallier;
    int niveau;
    int gold;

}sJoueur;

typedef struct
{
    char name[16];

    int pv;
    int pv_max;

    int force;
    int agilite;
    int defense;
    int dexterite;
    int intelligence;

    int xp;
    int gold;


}sEnnemi;

typedef struct
{
    int fileVersion;
    int nbrObjects;
    char type[11];
} sMESS_ITEMS_HEADER;

typedef struct
{
    char name[TAILLE_MAX_NomObjet];
    int categorie;
    int force;
    int agilite;
    int defense;
    int dexterite;
    int intelligence;
    int charisme;
    int prix;
    int pv;
    int pm;
    int equipe;
    int possede;
} sMESS_ITEMS_DATA;

typedef struct
{
    sMESS_ITEMS_HEADER header;
    sMESS_ITEMS_DATA data[999];
} sMESS_ITEMS;

sMESS_ITEMS MESS_LoadItems(const char* filename)
{
    //On définit le conteur pour le chargement objet par objet plus tard
    int counter = 0;
    //On crée une nouvelle structure d'objet
    sMESS_ITEMS items_data;
    //On ouvre le fichier
    FILE* ptr_myfile=fopen(filename,"rb");
    //On charge les propriétés du header
    fread(&items_data.header.fileVersion,2,1,ptr_myfile); //Version du fichier
    fread(&items_data.header.nbrObjects,4,1,ptr_myfile); //Nombre d'objet dans la base de donnée
    fread(&items_data.header.type,11,1,ptr_myfile); //Type de fichier (toujours ITEMS_TABLE)

    //On charge chaque objet un par un
    for (counter = 0; counter < items_data.header.nbrObjects; counter++)
    {
        //Chargement de la prefixed length string
        char size = 0;
        fread(&size,1,1,ptr_myfile);
        //Si la taille du nom de l'objet dépasse la valeur maximum
        if (size > 18)
        {
            //Génére une erreur et retourne les valeurs incompletes
            printf("ERROR TAILLE");
            return items_data;
        }
        else
        {
            //Chargement de la prefixed length string
            fread(&items_data.data[counter].name,size,1,ptr_myfile);
        }
        //Chargement des stats de l'arme
        fread(&items_data.data[counter].categorie,4,1,ptr_myfile);
        fread(&items_data.data[counter].force,4,1,ptr_myfile);
        fread(&items_data.data[counter].agilite,4,1,ptr_myfile);
        fread(&items_data.data[counter].defense,4,1,ptr_myfile);
        fread(&items_data.data[counter].dexterite,4,1,ptr_myfile);
        fread(&items_data.data[counter].intelligence,4,1,ptr_myfile);
        fread(&items_data.data[counter].charisme,4,1,ptr_myfile);
        fread(&items_data.data[counter].prix,4,1,ptr_myfile);
        fread(&items_data.data[counter].pv,4,1,ptr_myfile);
        fread(&items_data.data[counter].pm,4,1,ptr_myfile);
        items_data.data[counter].possede = 0;
        items_data.data[counter].equipe = 0;

    }
    //Fermeture du fichier
    fclose(ptr_myfile);
    return items_data;
}

//Initialisation du joueur avant le combat, cette fonction sera à supprimer par la suite !
void Ini_Joueur(sJoueur* Perso)
{

    sprintf(Perso->name,"Chatmalow");

    Perso->pv_max=20;
    Perso->pv=Perso->pv_max;
    Perso->mana=12;
    Perso->mana=Perso->mana_max;

    Perso->force=5;
    Perso->agilite=3;
    Perso->defense=2;
    Perso->dexterite=3;
    Perso->intelligence=4;

    Perso->xp=0;
    Perso->xp_pallier=52;
    Perso->niveau=1;
    Perso->gold=0;



}

//Initialisation du monstre avant le combat
void Ini_Ennemi(sEnnemi* Monstre)
{
    char nom[16]="JeanleTroll";
    int i=0;

     for (i=0;i<16;i++)
    {
        Monstre->name[i]=nom[i];
    }

    Monstre->pv_max=20;
    Monstre->pv=Monstre->pv_max;

    Monstre->force=4;
    Monstre->agilite=2;
    Monstre->intelligence=1;
    Monstre->defense=2;
    Monstre->dexterite=0;

    Monstre->xp=27;
    Monstre->gold=15;



}

void closeFenetre(SDL_Surface *interface,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Rect position, SDL_Rect positionFenetre, SDL_Rect decoupeF,int deroulement,SDL_Surface *Perso_Image, SDL_Rect position_Perso, SDL_Rect decoupeP, SDL_Surface *Monstre_Image, SDL_Rect position_Monstre, SDL_Rect decoupeE,SDL_Surface *barreVie,SDL_Surface *barreMana,SDL_Surface *barreEnnemi,SDL_Rect decoupeVP, SDL_Rect decoupeMP, SDL_Rect decoupeVE, SDL_Rect pos_Barre_de_vie_P, SDL_Rect pos_Barre_Mana,SDL_Rect pos_Barre_vie_E,SDL_Surface *Pv_Max_Perso,SDL_Rect pos_Pv_Max,SDL_Surface *Pv_Perso,SDL_Rect pos_Pv_P,SDL_Surface *Niveau_Perso,SDL_Rect posNiveau)
{

    for(deroulement=0;deroulement<=450;deroulement=deroulement+150)
        {
            positionFenetre.y=468+deroulement;
            decoupeF.y=deroulement;

            SDL_BlitSurface(interface,NULL,ecran,&position);
            SDL_BlitSurface(fenetre,&decoupeF,ecran,&positionFenetre);
            SDL_BlitSurface(Perso_Image,&decoupeP,ecran,&position_Perso);
            SDL_BlitSurface(Monstre_Image,&decoupeE,ecran,&position_Monstre);

            SDL_BlitSurface(barreVie,&decoupeVP,ecran,&pos_Barre_de_vie_P);
            SDL_BlitSurface(barreMana,&decoupeMP,ecran,&pos_Barre_Mana);
            SDL_BlitSurface(barreEnnemi,&decoupeVE,ecran,&pos_Barre_vie_E);

            SDL_BlitSurface(Pv_Max_Perso,NULL,ecran,&pos_Pv_Max);
            SDL_BlitSurface(Pv_Perso,NULL,ecran,&pos_Pv_P);
            SDL_BlitSurface(Niveau_Perso,NULL,ecran,&posNiveau);

            SDL_Flip(ecran);
        }

}

void affFenetre(SDL_Surface *fenetreListe,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Surface *curseur,SDL_Rect positionCurseur, SDL_Rect positionFenetre, SDL_Rect positionFenetreListe, SDL_Rect decoupeF,int deroulement,SDL_Surface *Perso_Image, SDL_Rect position_Perso, SDL_Rect decoupeP, SDL_Surface *Monstre_Image, SDL_Rect position_Monstre, SDL_Rect decoupeE,SDL_Surface *barreVie,SDL_Surface *barreMana,SDL_Surface *barreEnnemi,SDL_Rect decoupeVP, SDL_Rect decoupeMP, SDL_Rect decoupeVE, SDL_Rect pos_Barre_de_vie_P, SDL_Rect pos_Barre_Mana,SDL_Rect pos_Barre_vie_E,SDL_Surface *Pv_Max_Perso,SDL_Rect pos_Pv_Max,SDL_Surface *Pv_Perso,SDL_Rect pos_Pv_P,SDL_Surface *Niveau_Perso,SDL_Rect posNiveau)
{

SDL_BlitSurface(curseur,NULL,ecran,&positionCurseur);
SDL_BlitSurface(Perso_Image,&decoupeP,ecran,&position_Perso);
SDL_BlitSurface(Monstre_Image,&decoupeE,ecran,&position_Monstre);


SDL_BlitSurface(barreVie,&decoupeVP,ecran,&pos_Barre_de_vie_P);
SDL_BlitSurface(barreMana,&decoupeMP,ecran,&pos_Barre_Mana);
SDL_BlitSurface(barreEnnemi,&decoupeVE,ecran,&pos_Barre_vie_E);

SDL_BlitSurface(Pv_Max_Perso,NULL,ecran,&pos_Pv_Max);
SDL_BlitSurface(Pv_Perso,NULL,ecran,&pos_Pv_P);
SDL_BlitSurface(Niveau_Perso,NULL,ecran,&posNiveau);


SDL_Flip(ecran);

    for(deroulement=450 ;deroulement>=0;deroulement=deroulement-10)
        {
            positionFenetre.y=468 +deroulement;
            decoupeF.y=deroulement;



            SDL_BlitSurface(fenetre,&decoupeF,ecran,&positionFenetre);;

            SDL_Flip(ecran);
        }
}

int affListe(int tabObjet[10], int deplaList, int listType,SDL_Surface *fenetreListe,SDL_Surface *ecran,SDL_Surface *texte,SDL_Rect positionFenetreListe, SDL_Rect postexte,sMESS_ITEMS items_data,TTF_Font *police,SDL_Color noire)
{

    //affichage liste

SDL_BlitSurface(fenetreListe,NULL,ecran,&positionFenetreListe);
SDL_Flip(ecran);

int listeActive=10;
int affichageinventaire=0,pos=0,anaItems=0,numObjets=0;

for (affichageinventaire=listeActive-10;affichageinventaire<listeActive;affichageinventaire++)
    {
        postexte.x=123;
        postexte.y=195+pos;

    if (items_data.data[affichageinventaire].categorie==listType && items_data.data[affichageinventaire].possede==1)
        {
            if (anaItems>=deplaList)
                {
                    texte = TTF_RenderText_Blended(police ,items_data.data[affichageinventaire].name,noire);
                    SDL_BlitSurface(texte,NULL,ecran,&postexte);
                    pos=pos+67;
                    tabObjet[numObjets]=affichageinventaire;
                    numObjets++;
                }
            else
                {
                    affichageinventaire++;
                    listeActive++;
                    anaItems++;
                }
        }
    else if (affichageinventaire>100)
        {
            affichageinventaire = listeActive;
        }
    else
        {
            listeActive++;
        }

    }
return tabObjet[10];
}

int Analyse_Clic(SDL_Event *event, int numFenetre)
{
    if ( event->button.x>=0 && event->button.y>=909 && event->button.x<=336 && event->button.y<=1050 && numFenetre!=1)
        return 1;

      if (event->button.x>=337 && event->button.y>=909 && event->button.x<=672 && event->button.y<=1050 && numFenetre!=2)
        return 2;

    if (event->button.x>=673 && event->button.y>=909 && event->button.x<=1008 && event->button.y<=1050 && numFenetre!=3)
        return 3;

    if (event->button.x>=10 && event->button.y>=650 && event->button.x<=47 && event->button.y<=718 && numFenetre==1)
        return 6;
    if (event->button.x>=10 && event->button.y>=583 && event->button.x<=47 && event->button.y<=649&& numFenetre==1)
        return 7;

    if (event->button.x>=55 && event->button.y>=492 && event->button.x<=345 && event->button.y<=525 && numFenetre==1)//+33
        return 16;


    else
        return 0;

}

void Refresh(SDL_Surface* ecran, SDL_Surface *interface, SDL_Rect position, SDL_Surface *Perso_Image, SDL_Rect decoupeP, SDL_Rect position_Perso, SDL_Surface *Monstre_Image, SDL_Rect decoupeE, SDL_Rect position_Monstre, SDL_Surface *barreVie, SDL_Rect decoupeVP, SDL_Rect pos_Barre_de_vie_P, SDL_Surface *barreMana, SDL_Rect decoupeMP, SDL_Rect pos_Barre_Mana, SDL_Surface *barreEnnemi, SDL_Rect decoupeVE, SDL_Rect pos_Barre_vie_E, SDL_Surface *Niveau_Perso, SDL_Rect posNiveau, SDL_Surface *Pv_Max_Perso, SDL_Rect pos_Pv_Max, SDL_Surface *Pv_Perso, SDL_Rect pos_Pv_P)
{
    //interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P
SDL_BlitSurface(interface,NULL,ecran,&position);
SDL_BlitSurface(Perso_Image,&decoupeP,ecran,&position_Perso);
SDL_BlitSurface(Monstre_Image,&decoupeE,ecran,&position_Monstre);

SDL_BlitSurface(barreVie,&decoupeVP,ecran,&pos_Barre_de_vie_P);
SDL_BlitSurface(barreMana,&decoupeMP,ecran,&pos_Barre_Mana);
SDL_BlitSurface(barreEnnemi,&decoupeVE,ecran,&pos_Barre_vie_E);

SDL_BlitSurface(Niveau_Perso,NULL,ecran,&posNiveau);
SDL_BlitSurface(Pv_Max_Perso,NULL,ecran,&pos_Pv_Max);
SDL_BlitSurface(Pv_Perso,NULL,ecran,&pos_Pv_P);

SDL_Flip(ecran);
}

void Attaque_P(sJoueur *Perso, sEnnemi *Monstre)
{

}

int affEquip(sJoueur *Perso,int tabEquipement[7],SDL_Surface *ecran,SDL_Surface *refreshEquipement,SDL_Surface *texte,SDL_Rect postexte,SDL_Rect posrefreshEquipement,TTF_Font *police,SDL_Color noire,sMESS_ITEMS items_data)
{

Ini_Joueur(Perso);
int a=0;
for (a=0;a<1;a++)
    {
        posrefreshEquipement.x=1209;
        posrefreshEquipement.y=205;
        postexte.x=1215;
        postexte.y=202;
        texte = TTF_RenderText_Blended(police ,items_data.data[tabEquipement[a]].name,noire);
        SDL_BlitSurface(refreshEquipement,NULL,ecran,&posrefreshEquipement);
        SDL_BlitSurface(texte,NULL,ecran,&postexte);
        postexte.y+=89;
        posrefreshEquipement.y+=90;
        Perso->force+=items_data.data[tabEquipement[a]].force;
        Perso->agilite+=items_data.data[tabEquipement[a]].agilite;
        Perso->defense+=items_data.data[tabEquipement[a]].defense;
        Perso->intelligence+=items_data.data[tabEquipement[a]].intelligence;
        Perso->dexterite+=items_data.data[tabEquipement[a]].dexterite;
        Perso->charisme+=items_data.data[tabEquipement[a]].charisme;


    }
        postexte.x=900;
        postexte.y=65;
        char tampon [3]={0,0,0};
        sprintf (tampon, "%d", Perso->force);
        texte = TTF_RenderText_Blended(police,tampon,noire);

       SDL_BlitSurface(texte,NULL,ecran,&postexte);
       SDL_Flip(ecran);
}



void Inventaire()
{

sJoueur Perso;
sMESS_ITEMS items_data = MESS_LoadItems("Inventaire1.bin");

TTF_Init();
SDL_Rect postexte;
SDL_Surface *texte =NULL;
TTF_Font *police= NULL;
police = TTF_OpenFont("carolingia.ttf" ,50);
SDL_Color noire = {135,65,14};

int tabEquipement[10]={0,0,0,0,0,0,0,0,0,0};

SDL_Rect position,positionFenetreListe,positionFenetreSelect,positionOnglets,positionImagesOnglets,posrefreshEquipement;

//Affichage ecran
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface* ecran = NULL;
ecran=SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE|SDL_FULLSCREEN);
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

//Affichage interface
SDL_Surface* interface =NULL;
interface= SDL_LoadBMP("Sprites/Interface II.bmp");
SDL_SetColorKey(interface, SDL_SRCCOLORKEY, SDL_MapRGB(interface->format, 0, 0, 255));
position.x=0;
position.y=0;

//Affichage Fenetres Liste
SDL_Surface* fenetreListe = NULL;
fenetreListe = SDL_LoadBMP("Sprites/Liste II.bmp");
positionFenetreListe.x=113;
positionFenetreListe.y=189;

//Affichage Fenetres Select
SDL_Surface* fenetreSelect = NULL;
fenetreSelect = SDL_LoadBMP("Sprites/Fenetre Select II.bmp");
SDL_SetColorKey(fenetreSelect, SDL_SRCCOLORKEY, SDL_MapRGB(fenetreSelect->format, 0, 0, 255));
positionFenetreSelect.x=113;
positionFenetreSelect.y=0;

//Affichage Onglets
SDL_Surface* Onglets = NULL;
Onglets = SDL_LoadBMP("Sprites/Onglets II.bmp");
SDL_SetColorKey(Onglets, SDL_SRCCOLORKEY, SDL_MapRGB(Onglets->format, 0, 0, 255));
positionOnglets.x=722;

//Affichage Onglets
SDL_Surface* ImagesOnglets = NULL;
ImagesOnglets = SDL_LoadBMP("Sprites/Images Onglets II.bmp");
SDL_SetColorKey(ImagesOnglets, SDL_SRCCOLORKEY, SDL_MapRGB(ImagesOnglets->format, 0, 0, 255));
positionImagesOnglets.x=724;
positionImagesOnglets.y=162;

//Affichage Refresh Equipement
SDL_Surface* refreshEquipement = NULL;
refreshEquipement = SDL_LoadBMP("Sprites/Refersh Equipement II.bmp");
SDL_SetColorKey(refreshEquipement, SDL_SRCCOLORKEY, SDL_MapRGB(refreshEquipement->format, 0, 0, 255));
posrefreshEquipement.x=724;
posrefreshEquipement.y=162;

int tabObjet[10];
int deplaList=0;
int listType=1;

SDL_BlitSurface(interface,NULL,ecran,&position);
positionOnglets.y=156;
SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
positionOnglets.y=287;
SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
positionOnglets.y=419;
SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
positionOnglets.y=550;
SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
positionOnglets.y=682;
SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);

SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);


affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

SDL_Flip(ecran);

int Select=0;


//EVENT
 int continuer = 1;

    SDL_Event event;

    while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
                {
                    case SDL_KEYDOWN:

                    switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                            continuer=0;
                            break;

                        }
                    break;

                case SDL_MOUSEBUTTONDOWN:

//SELECTION
                if (event.button.x>=112 && event.button.y>=188 && event.button.x<=676 && event.button.y<=255)
                    {
                        Select =0;

                        positionFenetreSelect.y=189;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=256 && event.button.x<=676 && event.button.y<=325)
                    {
                        Select =1;

                        positionFenetreSelect.y=256;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=326 && event.button.x<=676 && event.button.y<=391)
                    {
                        Select=2;

                        positionFenetreSelect.y=324;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=391 && event.button.x<=676 && event.button.y<=460)
                    {
                        Select =3;

                        positionFenetreSelect.y=389;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=461 && event.button.x<=676 && event.button.y<=525)
                    {
                        Select =4;

                        positionFenetreSelect.y=457;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=526 && event.button.x<=676 && event.button.y<=592)
                    {
                        Select =5;

                        positionFenetreSelect.y=524;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>593 && event.button.x<=676 && event.button.y<=660)
                    {
                        Select =6;

                        positionFenetreSelect.y=590;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=661 && event.button.x<=676 && event.button.y<=725)
                    {
                        Select =7;

                        positionFenetreSelect.y=658;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=725 && event.button.x<=676 && event.button.y<=792)
                    {
                        Select =8;

                        positionFenetreSelect.y=722;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=793 && event.button.x<=676 && event.button.y<=959)
                    {
                        Select =9;

                        positionFenetreSelect.y=791;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }

//FLECHES
                if (event.button.x>=9 && event.button.y>=532 && event.button.x<=100 && event.button.y<=700)
                    {

                            deplaList++;
                            affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                            SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                            SDL_Flip(ecran);

                    }
                if (event.button.x>=9 && event.button.y>=361 && event.button.x<=100 && event.button.y<=531)
                    {
                        if (deplaList>0)
                            {
                        deplaList--;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                            }
                    }

//ONGLETS
                if (event.button.x>=722 && event.button.y>=170 && event.button.x<=810 && event.button.y<=305)
                    {
                    deplaList=0;
                    listType=1;
                    affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                    positionOnglets.y=682;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=550;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=419;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=287;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=156;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);
                    SDL_Flip(ecran);
                    }
                if (event.button.x>=722 && event.button.y>=306 && event.button.x<=810 && event.button.y<=436)
                    {
                    deplaList=0;
                    listType=2;
                    affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                    positionOnglets.y=682;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=550;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=419;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=156;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=287;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);
                    SDL_Flip(ecran);
                    }
                if (event.button.x>=722 && event.button.y>=437 && event.button.x<=810 && event.button.y<=567)
                    {
                    deplaList=0;
                    listType=3;
                    affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                    positionOnglets.y=682;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=550;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=156;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=287;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=419;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);
                    SDL_Flip(ecran);
                    }
                if (event.button.x>=722 && event.button.y>=568 && event.button.x<=810 && event.button.y<=698)
                    {
                    deplaList=0;
                    listType=4;
                    affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                    positionOnglets.y=682;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=156;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=287;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=419;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=550;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);
                    SDL_Flip(ecran);
                    }
                if (event.button.x>=722 && event.button.y>=699 && event.button.x<=810 && event.button.y<=829)
                    {
                    deplaList=0;
                    listType=5;
                    affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

                    positionOnglets.y=156;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=287;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=419;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=550;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    positionOnglets.y=682;
                    SDL_BlitSurface(Onglets,NULL,ecran,&positionOnglets);
                    SDL_BlitSurface(ImagesOnglets,NULL,ecran,&positionImagesOnglets);
                    SDL_Flip(ecran);
                    }

//EQUIPER
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==0)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==1)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==2)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==3)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==4)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==5)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==6)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==7)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==8)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==9)
                    {
                        items_data.data[tabObjet[Select]].equipe=1;
                        items_data.data[tabEquipement[items_data.data[tabObjet[Select]].categorie]]=items_data.data[tabObjet[Select]];
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                    }

//JETER
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==0 && items_data.data[tabObjet[Select]].equipe==0)
                    {

                                items_data.data[tabObjet[Select]].possede=0;
                                items_data.data[tabObjet[Select]].equipe=0;
                                affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                                SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                                affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                                SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==1 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==2 && items_data.data[tabObjet[Select]].equipe==0)
                    {

                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                        affEquip(&Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==3 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==4 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==5 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==6 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==7 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==8 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==9 && items_data.data[tabObjet[Select]].equipe==0)
                    {
                        items_data.data[tabObjet[Select]].possede=0;
                        affListe (tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }



                break;
            break;
                }

    }




}

void combat()
{

//Initiaisation
int ListObjects[5][99]={0};

int tabObjet[10];
int deplaList=0;
int deroulement;
int listType=0;
int fenetre_c[5];
int i=0;
TTF_Init();
SDL_Rect postexte;
SDL_Surface *texte =NULL;
SDL_Surface *Texte_Affichage=NULL;
TTF_Font *police=TTF_OpenFont("carolingia.ttf",25);
SDL_Color noire = {135,65,14};
SDL_Rect position,positionBarreDeManaIC,positionCurseur,positionFenetre,positionFenetreListe,decoupeF,positionFenetreSelect,posMiniOnglet,positionPerso,positionMonstre,position_Pv_Perso,position_Pv_Monstre,position_Niveau_Perso, position_Mana_Perso, position_Texte_1,position_Menu_1,position_Menu_2,position_Menu_3,position_Menu_4,position_Menu_5;
sMESS_ITEMS items_data = MESS_LoadItems("Skills.bin");

items_data.data[0].possede=1;
items_data.data[0].equipe=1;





//Chargement et initialisation du personnage et du monstre
sJoueur Perso;
sEnnemi Monstre;

Ini_Joueur(&Perso);
Ini_Ennemi(&Monstre);

SDL_Surface *Perso_Image=IMG_Load("Sprites/Combat/Perso_Combat.png");
SDL_Rect position_Perso={100,480};

SDL_Surface *Monstre_Image=IMG_Load("Sprites/Combat/Palette_combat_1.png");
SDL_Rect position_Monstre={1200,200};

SDL_Rect decoupeP={0,0,500,450};

/*
decoupeP.x=50;
decoupeP.y=323;
decoupeP.w=395;
decoupeP.h=317;*/


SDL_Rect decoupeE={282,0,249,198};



//////////////////////////////////////////:


//Affichage ecran
SDL_Init(SDL_INIT_VIDEO);
SDL_Surface* ecran = NULL;
ecran=SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE|SDL_FULLSCREEN);
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

//Affichage fond interface
SDL_Surface* interface =NULL;
interface= IMG_Load("Sprites/Combat/Interface Combat.bmp");
SDL_SetColorKey(interface, SDL_SRCCOLORKEY, SDL_MapRGB(interface->format, 0, 0, 255));
position.x=0;
position.y=0;

//Affichage Barre de vie et Mana
SDL_Surface* barreVie = SDL_LoadBMP("Sprites/Combat/Barre De Vie IC.bmp"),*barreMana = SDL_LoadBMP("Sprites/Combat/Barre De Mana IC.bmp"), *barreEnnemi=SDL_LoadBMP("Sprites/Combat/Barre De Vie Monstre IC.bmp");
SDL_Rect pos_Barre_de_vie_P={107,0}, pos_Barre_Mana={190,103}, pos_Barre_vie_E={1279,129};
SDL_SetColorKey(barreVie, SDL_SRCCOLORKEY, SDL_MapRGB(barreVie->format, 0, 0, 255));
SDL_SetColorKey(barreMana, SDL_SRCCOLORKEY, SDL_MapRGB(barreMana->format, 0, 0, 255));
SDL_SetColorKey(barreEnnemi, SDL_SRCCOLORKEY, SDL_MapRGB(barreEnnemi->format, 0, 0, 255));

SDL_Rect decoupeVP={0,0,927,100},decoupeVE={0,0,235,29},decoupeMP={0,0,738,61};

//Affichage Curseur
SDL_Surface* curseur =NULL;
curseur= SDL_LoadBMP("Sprites/Combat/Curseur IC.bmp");
SDL_SetColorKey(curseur, SDL_SRCCOLORKEY, SDL_MapRGB(curseur->format, 0, 0, 255));
positionCurseur.x=1680;
positionCurseur.y=0;

//Affichage Fenetres
SDL_Surface* fenetre = NULL;
fenetre = SDL_LoadBMP("Sprites/Combat/Fenetre IC.bmp");
SDL_SetColorKey(fenetre, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 0, 0, 255));
positionFenetre.x=1680;
positionFenetre.y=1050;
decoupeF.x=0;
decoupeF.y=0;
decoupeF.w=482;
decoupeF.h=549;

//Affichage Fenetres Liste
SDL_Surface* fenetreListe = NULL;
fenetreListe = SDL_LoadBMP("Sprites/Combat/Liste IC.bmp");
positionFenetreListe.x=0;
positionFenetreListe.y=0;

//Affichage Fenetres Select
SDL_Surface* fenetreSelect = NULL;
fenetreSelect = SDL_LoadBMP("Sprites/Combat/Fenetre Select IC.bmp");
SDL_SetColorKey(fenetreSelect, SDL_SRCCOLORKEY, SDL_MapRGB(fenetreSelect->format, 0, 0, 255));
positionFenetreSelect.x=53;
positionFenetreSelect.y=22;

//Affichage Mini Onglet
SDL_Surface* MiniOnglet = NULL;
MiniOnglet = SDL_LoadBMP("Sprites/Combat/Mini Onglet IC.bmp");
SDL_SetColorKey(MiniOnglet, SDL_SRCCOLORKEY, SDL_MapRGB(MiniOnglet->format, 0, 0, 255));
posMiniOnglet.x=53;
posMiniOnglet.y=22;



//Analyse de la position
int posfenetre=0;

/////////////////////////

///////////Affichage des valeurs


noire.r = 0;
noire.g = 0;
police = TTF_OpenFont("carolingia.ttf" ,92);
char Niveau_P[2], Pv_Max_P[3], Pv_P[3], Mana_Max_P[3], Mana_P[3], Pv_M[3], Nom_M[16];
sprintf(Niveau_P,"%d",Perso.niveau);
SDL_Surface *Niveau_Perso = TTF_RenderText_Blended(police ,Niveau_P,noire);
SDL_Rect posNiveau={75,50};

//Chargement des PV (affichage des nombres) du personnage
int Vie_Actuelle_Decoupe=0; //Il s'agit d'une variable utilisée dans les fonctions de combat.
police = TTF_OpenFont("carolingia.ttf" ,40);
sprintf(Pv_Max_P,"/%d",Perso.pv_max);
sprintf(Pv_P,"%d",Perso.pv);
SDL_Surface *Pv_Max_Perso = TTF_RenderText_Blended(police, Pv_Max_P, noire), *Pv_Perso = TTF_RenderText_Blended(police, Pv_P, noire);
SDL_Rect pos_Pv_Max={550,40}, pos_Pv_P={500,40};


SDL_Surface *Mana_Perso;
SDL_Surface *Pv_Monstre=NULL, *Nom_Monstre=NULL;


noire.r = 135;
noire.g = 65;
police = TTF_OpenFont("carolingia.ttf" ,15);
///////////////////////


//VARIABLES PROPRES AUX ATTAQUES ENNEMIES ET ALLIEES.
int Vie_Perdue=0, Diminution=0;
////////////////////////////

//AFFICHAGE TEXTE
char Texte[6][128];
sprintf(Texte[0],"Que faire ?");
sprintf(Texte[1],"%s Attaque !",Perso.name);
//Texte[2] = "Jean le troll perd x PV !
sprintf(Texte[3],"%s Attaque !",Monstre.name);


//Blitage de toutes les surfaces en général
Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);
////////////////////////////////////////////////

//EVENT

 int continuer = 1;
 int numFenetre=0;
    SDL_Event event;

    while (continuer)
        {
            SDL_WaitEvent(&event);
            police = TTF_OpenFont("carolingia.ttf" ,24);

            noire.r=0;
            noire.g=0;
            noire.b=0;
            texte = TTF_RenderText_Blended(police,Texte[0],noire);
            postexte.x=280;
            postexte.y=280;

            SDL_BlitSurface(texte,NULL,ecran,&postexte);
            SDL_Flip(ecran);
            noire.r = 135;
            noire.g = 65;

            police = TTF_OpenFont("carolingia.ttf" ,24);
            switch(event.type)
                {
                    case SDL_KEYDOWN:

                    switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                            continuer=0;
                            break;


                        }
                    break;


                    case SDL_MOUSEBUTTONDOWN:
                    posfenetre=Analyse_Clic(&event,numFenetre);
                    switch(posfenetre)

                    {

                    case 0://Fermeture

                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=1680;
                        positionFenetre.x=1680;
                        numFenetre=0;

                        Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);


                        SDL_Flip(ecran);

                        break;

                    case 1://FENETRE-Fenetre 1
                        deplaList=0;
                        numFenetre=1;
                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=239;
                        positionCurseur.y=908;
                        positionFenetre.x=0;
                        listType=0;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                    break;

                    case 2:
                        //Fenetre 2
                        deplaList=0;
                        numFenetre=2;
                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=575;
                        positionCurseur.y=908;
                        positionFenetre.x=336;
                        listType=1;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                    break;

                    case 3:
                        //Fenetre 3
                        deplaList=0;
                        numFenetre=3;
                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=911;
                        positionCurseur.y=908;
                        positionFenetre.x=672;
                        listType=2;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);



                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=640;//-
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        SDL_Flip(ecran);

                    break;



                //BOUTONS FENETRES HAUT BAS
                    case 6: //BOUTON 1.1

                        if (numFenetre==1)
                            {

                                deplaList=deplaList+1;

                                affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                            }

                    break;

                    case 7: //BOUTON 1.2
                        if (deplaList>0 )
                            {
                                if (numFenetre==1)
                                    {
                                        deplaList=deplaList-1;

                                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                                    }
                            }
                    break;



                //SI FENETRE 1 OUVERTE

                    case 16: //LE JOUEUR CLIQUE SUR ONGLET 1.1

                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);

                        //Attaque_P(&Perso,&Monstre);
                         Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);


//LE JOUEUR ATTAQUE
                        police = TTF_OpenFont("carolingia.ttf" ,24);
                        noire.r=0;
                        noire.g=0;
                        noire.b=0;
                        texte = TTF_RenderText_Blended(police,Texte[1],noire);
                        postexte.x=280;
                        postexte.y=280;
                        SDL_BlitSurface(texte,NULL,ecran,&postexte);
                        SDL_Flip(ecran);
                        police = TTF_OpenFont("carolingia.ttf" ,15);

                        SDL_Delay(1000);

                        decoupeE.x=0;

                        Vie_Perdue=Perso.force+items_data.data[tabObjet[0]].force-Monstre.defense;
                                Diminution = 235/Monstre.pv_max*Vie_Perdue;
                                Vie_Actuelle_Decoupe = decoupeVE.w;

                                for(i=Vie_Actuelle_Decoupe;Vie_Actuelle_Decoupe-Diminution<=i;i-=9)
                                {
                                    decoupeVE.w=i;
                                    Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);
                                }




                                Monstre.pv-=Vie_Perdue;
                                decoupeVE.w=Monstre.pv*(235/Monstre.pv_max);


                                Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);


                                sprintf(Texte[2],"%s Perd %d PV ! ",Monstre.name,Vie_Perdue);
                                police = TTF_OpenFont("carolingia.ttf" ,24);
                                noire.r=0;
                                noire.g=0;
                                noire.b=0;
                                texte = TTF_RenderText_Blended(police,Texte[2],noire);
                                postexte.x=280;
                                postexte.y=280;
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);
                                police = TTF_OpenFont("carolingia.ttf" ,15);




                                decoupeE.x=225;

                                if(Monstre.pv<=0)


//L'ENNEMI ATTAQUE A SON TOUR..
                            SDL_Delay(1000);
                            decoupeE.x=536;
                            Vie_Perdue=Monstre.force-Perso.defense;

                              Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);
                                police = TTF_OpenFont("carolingia.ttf" ,24);
                                noire.r=0;
                                noire.g=0;
                                noire.b=0;
                                texte = TTF_RenderText_Blended(police,Texte[3],noire);
                                postexte.x=280;
                                postexte.y=280;
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);
                                police = TTF_OpenFont("carolingia.ttf" ,15);

                            SDL_Delay(1000);

                                Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);
                                sprintf(Texte[4],"%s Perd %d PV ! ",Perso.name,Vie_Perdue);
                                police = TTF_OpenFont("carolingia.ttf" ,24);
                                noire.r=0;
                                noire.g=0;
                                noire.b=0;
                                texte = TTF_RenderText_Blended(police,Texte[4],noire);
                                postexte.x=280;
                                postexte.y=280;
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);
                                police = TTF_OpenFont("carolingia.ttf" ,15);

                                SDL_Delay(1000);
                            Diminution = 864/Perso.pv_max*Vie_Perdue;
                            Vie_Actuelle_Decoupe = decoupeVP.w;

                                noire.r = 0;
                                noire.g = 0;
                                police = TTF_OpenFont("carolingia.ttf" ,26);
                                Perso.pv-=Vie_Perdue;
                                sprintf(Pv_P,"%d",Perso.pv);
                                Pv_Perso=TTF_RenderText_Blended(police,Pv_P,noire);
                                police = TTF_OpenFont("carolingia.ttf",15);
                                noire.r = 135;
                                noire.g = 65;



                                for(i=Vie_Actuelle_Decoupe;Vie_Actuelle_Decoupe-Diminution<=i;i-=5)
                                {

                                    decoupeVP.w=i;

                                    Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);

                                }

                                decoupeVP.w=Perso.pv*(864/Perso.pv_max);

                                decoupeE.x=282;

                                Refresh(ecran,interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P);
                                if(Perso.pv<=0)


                        break;








                 if (event.button.x>=1009 && event.button.y>=909 && event.button.x<=1344 && event.button.y<=1050 && numFenetre!=4)
                    {//Fenetre 4
                        deplaList=0;
                        numFenetre=4;
                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=1247;
                        positionCurseur.y=908;
                        positionFenetre.x=1008;
                        listType=3;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=705;//-
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=640;//-
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        SDL_Flip(ecran);

                    }
                else if (event.button.x>=1345 && event.button.y>=909 && event.button.x<=1680 && event.button.y<=1050 && numFenetre!=5)
                    {//Fenetre 5
                        closeFenetre(interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        positionCurseur.x=1583;
                        positionCurseur.y=908;
                        positionFenetre.x=1680;
                        numFenetre=5;
                        SDL_BlitSurface(curseur,NULL,ecran,&positionCurseur);
                        SDL_Flip(ecran);
                    }
//BOUTONS FENETRES HAUT BAS

                else if (event.button.x>=346 && event.button.y>=650 && event.button.x<=384 && event.button.y<=718 && numFenetre==2)
                    {//BOUTON 2.1
                        if (numFenetre==2)
                            {
                                deplaList=deplaList+1;

                                affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                            }
                    }
                else if (event.button.x>=346 && event.button.y>=583 && event.button.x<=384 && event.button.y<=649 && numFenetre==2)
                    {//BOUTON 2.2
                        if (deplaList>0)
                            {
                                if (numFenetre==2)
                                    {
                                        deplaList=deplaList-1;

                                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                                    }
                            }
                    }
                else if (event.button.x>=683 && event.button.y>=650 && event.button.x<=721 && event.button.y<=718 && numFenetre==3)
                    {//BOUTON 3.1
                        if (numFenetre==3)
                            {
                                deplaList=deplaList+1;

                                affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                            }
                    }
                else if (event.button.x>=683 && event.button.y>=583 && event.button.x<=721 && event.button.y<=649 && numFenetre==3)
                    {//BOUTON 3.2
                        if (deplaList>0)
                            {
                                if (numFenetre==3)
                                    {
                                        deplaList=deplaList-1;

                                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                                    }
                            }
                    }
                else if (event.button.x>=1019 && event.button.y>=650 && event.button.x<=1057 && event.button.y<=718 && numFenetre==4)
                    {//BOUTON 4.1
                       if (numFenetre==4)
                           {
                                deplaList=deplaList+1;

                                affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                          }
                    }
                else if (event.button.x>=1019 && event.button.y>=583 && event.button.x<=1057 && event.button.y<=649 && numFenetre==4)
                    {//BOUTON 4.2
                        if (deplaList>0)
                            {
                               if (numFenetre==4)
                                   {
                                        deplaList=deplaList-1;

                                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);
                                    }
                            }
                    }


//FENETRES OUVERTES
                else if (event.button.x>=55 && event.button.y>=526 && event.button.x<=345 && event.button.y<=559 && numFenetre==1)
                    {//ONGLET 1.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);


                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=560 && event.button.x<=345 && event.button.y<=593 && numFenetre==1)
                    {//ONGLET 1.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=594 && event.button.x<=345 && event.button.y<=627 && numFenetre==1)
                    {//ONGLET 1.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=628 && event.button.x<=345 && event.button.y<=661 && numFenetre==1)
                    {//ONGLET 1.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=662 && event.button.x<=345 && event.button.y<=695 && numFenetre==1)
                    {//ONGLET 1.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=696 && event.button.x<=345 && event.button.y<=729 && numFenetre==1)
                    {//ONGLET 1.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=730 && event.button.x<=345 && event.button.y<=763 && numFenetre==1)
                    {//ONGLET 1.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=764 && event.button.x<=345 && event.button.y<=797 && numFenetre==1)
                    {//ONGLET 1.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=798 && event.button.x<=345 && event.button.y<=831 && numFenetre==1)
                    {//ONGLET 1.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 2
                else if (event.button.x>=391 && event.button.y>=492 && event.button.x<=681 && event.button.y<=525 && numFenetre==2)//+33
                    {//ONGLET 2.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=526 && event.button.x<=681 && event.button.y<=559 && numFenetre==2)
                    {//ONGLET 2.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=560 && event.button.x<=681 && event.button.y<=593 && numFenetre==2)
                    {//ONGLET 2.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=594 && event.button.x<=681 && event.button.y<=627 && numFenetre==2)
                    {//ONGLET 2.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=628 && event.button.x<=681 && event.button.y<=661 && numFenetre==2)
                    {//ONGLET 2.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=662 && event.button.x<=681 && event.button.y<=695 && numFenetre==2)
                    {//ONGLET 2.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=696 && event.button.x<=681 && event.button.y<=729 && numFenetre==2)
                    {//ONGLET 2.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=730 && event.button.x<=681 && event.button.y<=763 && numFenetre==2)
                    {//ONGLET 2.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=764 && event.button.x<=681 && event.button.y<=797 && numFenetre==2)
                    {//ONGLET 2.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=798 && event.button.x<=681 && event.button.y<=831 && numFenetre==2)
                    {//ONGLET 2.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 3
                else if (event.button.x>=727 && event.button.y>=492 && event.button.x<=1017 && event.button.y<=525 && numFenetre==3)//+33
                    {//ONGLET 3.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=526 && event.button.x<=1017 && event.button.y<=559 && numFenetre==3)
                    {//ONGLET 3.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=560 && event.button.x<=1017 && event.button.y<=593 && numFenetre==3)
                    {//ONGLET 3.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=594 && event.button.x<=1017 && event.button.y<=627 && numFenetre==3)
                    {//ONGLET 3.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=628 && event.button.x<=1017 && event.button.y<=661 && numFenetre==3)
                    {//ONGLET 3.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=662 && event.button.x<=1017 && event.button.y<=695 && numFenetre==3)
                    {//ONGLET 3.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=696 && event.button.x<=1017 && event.button.y<=729 && numFenetre==3)
                    {//ONGLET 3.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=730 && event.button.x<=1017 && event.button.y<=763 && numFenetre==3)
                    {//ONGLET 3.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=764 && event.button.x<=1017 && event.button.y<=797 && numFenetre==3)
                    {//ONGLET 3.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=798 && event.button.x<=1017 && event.button.y<=831 && numFenetre==3)
                    {//ONGLET 3.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 4
                else if (event.button.x>=1063 && event.button.y>=492 && event.button.x<=1353 && event.button.y<=525 && numFenetre==4)//+33
                    {//ONGLET 4.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=526 && event.button.x<=1353 && event.button.y<=559 && numFenetre==4)
                    {//ONGLET 4.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=560 && event.button.x<=1353 && event.button.y<=593 && numFenetre==4)
                    {//ONGLET 4.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=594 && event.button.x<=1353 && event.button.y<=627 && numFenetre==4)
                    {//ONGLET 4.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=628 && event.button.x<=1353 && event.button.y<=661 && numFenetre==4)
                    {//ONGLET 4.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=662 && event.button.x<=1353 && event.button.y<=695 && numFenetre==4)
                    {//ONGLET 4.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=696 && event.button.x<=1353 && event.button.y<=729 && numFenetre==4)
                    {//ONGLET 4.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=730 && event.button.x<=1353 && event.button.y<=763 && numFenetre==4)
                    {//ONGLET 4.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=764 && event.button.x<=1353 && event.button.y<=797 && numFenetre==4)
                    {//ONGLET 4.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=798 && event.button.x<=1353 && event.button.y<=831 && numFenetre==4)
                    {//ONGLET 4.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//MINI ONGLET
                else if (event.button.x>=1043 && event.button.y>=520 && event.button.x<=1087 && event.button.y<=585 && numFenetre==3)//+33
                    {//Mini Onglet 3.1
                        deplaList=0;
                        numFenetre=3;

                        positionFenetre.x=672;
                        listType=2;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);


                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1043 && event.button.y>=586 && event.button.x<=1087 && event.button.y<=650 && numFenetre==3)//+33
                    {//Mini Onglet 3.2
                        deplaList=0;
                        numFenetre=3;

                        positionFenetre.x=672;
                        listType=1;

                        affListe (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, items_data, police, noire);
                        affFenetre (fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement,Perso_Image,position_Perso,decoupeP,Monstre_Image,position_Monstre,decoupeE,barreVie,barreMana,barreEnnemi,decoupeVP,decoupeMP,decoupeVE,pos_Barre_de_vie_P,pos_Barre_Mana,pos_Barre_vie_E,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P,Niveau_Perso,posNiveau);


                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1043 && event.button.y>=651 && event.button.x<=1087 && event.button.y<=715 && numFenetre==3)//+33
                    {//Mini Onglet 3.3
                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1043;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1379 && event.button.y>=520 && event.button.x<=1423 && event.button.y<=585 && numFenetre==4)//+33
                    {//Mini Onglet 4.1
                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=705;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1379 && event.button.y>=586 && event.button.x<=1423 && event.button.y<=650 && numFenetre==4)//+33
                    {//Mini Onglet 4.2
                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=705;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1379 && event.button.y>=651 && event.button.x<=1423 && event.button.y<=715 && numFenetre==4)//+33
                    {//Mini Onglet 4.3
                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=705;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1379 && event.button.y>=715 && event.button.x<=1423 && event.button.y<=780 && numFenetre==4)//+33
                    {//Mini Onglet 4.4
                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=510;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=575;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=640;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);

                        posMiniOnglet.x=1379;
                        posMiniOnglet.y=705;
                        SDL_BlitSurface(MiniOnglet,NULL,ecran,&posMiniOnglet);
                        SDL_Flip(ecran);
                    }


                else if (event.button.x>=0 && event.button.y>=467 && event.button.x<=371 && event.button.y<=909 && numFenetre==1)
                    {}
                else if (event.button.x>=337 && event.button.y>=467 && event.button.x<=708 && event.button.y<=909 && numFenetre==2)
                    {}
                else if (event.button.x>=673 && event.button.y>=467 && event.button.x<=1044 && event.button.y<=909 && numFenetre==3)
                    {}
                else if (event.button.x>=1009 && event.button.y>=467 && event.button.x<=1380 && event.button.y<=909 && numFenetre==4)
                    {}

                    }

                  if (Monstre.pv<=0)
                  {
                      continuer=0;
                  }


                break;





                }

            SDL_Flip(ecran);

    }

//Fin systeme
   SDL_FreeSurface(ecran);
   SDL_FreeSurface(interface);
   SDL_FreeSurface(fenetre);
   SDL_FreeSurface(texte);
}

void InterfacePricipale()
{

        //Initiaisation
   TTF_Init();
   int viePerdu=200,manaPerdu=300,manaFinal=0,vieFinal=0,vieTotale=800,manaTotale=800,xpTotal=800,xpManquant=700,xpFinal=0,xpFinal2=0,xpFinalTotal;
   SDL_Rect position,positionBarreDeVieIP,positionBarreDeManaIP,decoupeV,decoupeM,decoupeXP1,decoupeXP2,positionCurseur1,positionCurseur2,
   positionTexte,positionTexte2,positionTexte3,positionTexte4,positionTexte5,positionTexte6,positionBarreXP1IP,positionBarreXP2IP,positionFOR,positionAGI,positionDEF,positionINT,positionDEX,positionCHA;
   vieFinal=(viePerdu*793)/vieTotale;
   manaFinal=(manaPerdu*773)/manaTotale;
   xpFinalTotal=(xpManquant*1463)/xpTotal;



        //Affichage ecran
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE);
   SDL_Surface* ecran = NULL;
   ecran=SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE|SDL_FULLSCREEN);
   SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

         //Affichage Map interface
   SDL_Surface* interface =NULL;
   interface= SDL_LoadBMP("Sprites/IP/Interface principale.bmp");
   position.x=0;
   position.y=0;

        //Affichage Barre de vie et Mana
   SDL_Surface* barreVie = NULL,*barreMana = NULL;
   barreMana = SDL_LoadBMP("Sprites/IP/Barre De Mana IP.bmp");
   barreVie = SDL_LoadBMP("Sprites/IP/Barre De Vie IP.bmp");
   SDL_SetColorKey(barreVie, SDL_SRCCOLORKEY, SDL_MapRGB(barreVie->format, 0, 0, 255));
   SDL_SetColorKey(barreMana, SDL_SRCCOLORKEY, SDL_MapRGB(barreMana->format, 0, 0, 255));
   positionBarreDeManaIP.x=855;
   positionBarreDeManaIP.y=0;
   decoupeM.x=0;
   decoupeM.y=0;
   decoupeM.w=805;
   decoupeM.h=181;
   positionBarreDeVieIP.x=22+vieFinal;
   positionBarreDeVieIP.y=0;
   decoupeV.x=vieFinal;
   decoupeV.y=0;
   decoupeV.w=815;
   decoupeV.h=181;

       //Affichage Barre d'XP

SDL_Surface* barreXP1 = NULL,*barreXP2 = NULL;
barreXP1 = SDL_LoadBMP("Sprites/IP/Barre d'XP 1 IP.bmp");
barreXP2 = SDL_LoadBMP("Sprites/IP/Barre d'XP 2 IP.bmp");
SDL_SetColorKey(barreXP1, SDL_SRCCOLORKEY, SDL_MapRGB(barreXP1->format, 0, 0, 255));
SDL_SetColorKey(barreXP2, SDL_SRCCOLORKEY, SDL_MapRGB(barreXP2->format, 0, 0, 255));
  if (xpFinalTotal>725)
    {
        xpFinal2=725;
        xpFinal=xpFinalTotal-738;
    }
  else
    {
        xpFinal2=xpFinalTotal;
        xpFinal=0;
    }
positionBarreXP1IP.x=5;
positionBarreXP1IP.y=0;
decoupeXP1.x=0;
decoupeXP1.y=0;
decoupeXP1.w=738-xpFinal;
decoupeXP1.h=197;
positionBarreXP2IP.x=950;
positionBarreXP2IP.y=0;
decoupeXP2.x=0;
decoupeXP2.y=0;
decoupeXP2.w=725-xpFinal2;
decoupeXP2.h=197;

        //Affichage curseur1
   SDL_Surface* curseur1 =NULL;
   curseur1= SDL_LoadBMP("Sprites/IP/curseur1 IP.bmp");
SDL_SetColorKey(curseur1, SDL_SRCCOLORKEY, SDL_MapRGB(curseur1->format, 0, 0, 255));

        //Afichage curseur2
SDL_Surface* curseur2 =NULL;
   curseur2= SDL_LoadBMP("Sprites/IP/curseur2 IP.bmp");
SDL_SetColorKey(curseur2, SDL_SRCCOLORKEY, SDL_MapRGB(curseur2->format, 0, 0, 255));

       //Initialisation police
SDL_Surface *texte =NULL,*texte2 =NULL,*texte3 =NULL,*texte4 =NULL,*texte5 =NULL,*texte6 =NULL,*FOR=NULL,*AGI=NULL,*DEF=NULL,*INT=NULL,*DEX=NULL,*CHA=NULL;
TTF_Font *police= NULL;
police = TTF_OpenFont("carolingia.ttf" ,90);
SDL_Color noire = {135,65,14};
positionTexte.x=25;
positionTexte.y=290;
texte = TTF_RenderText_Blended(police ,"INVENTAIRE",noire);
positionTexte2.x=25;
positionTexte2.y=485;
texte2 = TTF_RenderText_Blended(police ,"STATISTIQUES",noire);
positionTexte3.x=25;
positionTexte3.y=665;
texte3 = TTF_RenderText_Blended(police ,"CARTE",noire);
positionTexte4.x=1350;
positionTexte4.y=295;
texte4 = TTF_RenderText_Blended(police ,"SORTS",noire);
positionTexte5.x=967;
positionTexte5.y=490;
texte5 = TTF_RenderText_Blended(police ,"COMPETENCE",noire);
positionTexte6.x=1260;positionTexte2;
positionTexte6.y=665;
texte6 = TTF_RenderText_Blended(police ,"RETOUR",noire);

positionFOR.x=25;
positionFOR.y=850;
FOR = TTF_RenderText_Blended(police ,"FOR",noire);
positionAGI.x=275;
positionAGI.y=855;
AGI = TTF_RenderText_Blended(police ,"AGI",noire);
positionDEF.x=485;
positionDEF.y=854;
DEF = TTF_RenderText_Blended(police ,"DEF",noire);
positionINT.x=1000;
positionINT.y=853;
INT = TTF_RenderText_Blended(police ,"INT",noire);
positionDEX.x=1225;
positionDEX.y=852;
DEX = TTF_RenderText_Blended(police ,"DEX",noire);
positionCHA.x=1470;
positionCHA.y=851;
CHA = TTF_RenderText_Blended(police ,"CHA",noire);

//Blit Statique
 SDL_BlitSurface(FOR,NULL,interface,&positionFOR);
 SDL_BlitSurface(AGI,NULL,interface,&positionAGI);
 SDL_BlitSurface(DEF,NULL,interface,&positionDEF);
 SDL_BlitSurface(INT,NULL,interface,&positionINT);
 SDL_BlitSurface(DEX,NULL,interface,&positionDEX);
 SDL_BlitSurface(CHA,NULL,interface,&positionCHA);
 SDL_BlitSurface(texte,NULL,interface,&positionTexte);
 SDL_BlitSurface(texte2,NULL,interface,&positionTexte2);
 SDL_BlitSurface(texte3,NULL,interface,&positionTexte3);
 SDL_BlitSurface(texte4,NULL,interface,&positionTexte4);
 SDL_BlitSurface(texte5,NULL,interface,&positionTexte5);
 SDL_BlitSurface(texte6,NULL,interface,&positionTexte6);




         //Gestion Evenement

 int continuerIP = 1;
    SDL_Event event;


    while (continuerIP)
{
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:

            switch (event.key.keysym.sym)
               {
                  case SDLK_ESCAPE:
                    continuerIP=0;
                    break;

               }
               break;

        case SDL_MOUSEMOTION:

            if (event.motion.x>=0 && event.motion.y>=275 && event.motion.x<=740 && event.motion.y<=400)
                {
                    positionCurseur1.x=723;
                    positionCurseur1.y=282;

                }

            else if (event.motion.x>=0 && event.motion.y>=462 && event.motion.x<=740 && event.motion.y<=595)
                {
                    positionCurseur1.x=724;
                    positionCurseur1.y=471;

                }
            else if (event.motion.x>=0 && event.motion.y>=645 && event.motion.x<=740 && event.motion.y<=780)
                {
                    positionCurseur1.x=729;
                    positionCurseur1.y=654;

                }
            else if (event.motion.x>=950 && event.motion.y>=275 && event.motion.x<=1680 && event.motion.y<=400)
                {
                    positionCurseur2.x=900;
                    positionCurseur2.y=278;

                }
            else if (event.motion.x>=950 && event.motion.y>=462 && event.motion.x<=1680 && event.motion.y<=595)
                {
                   positionCurseur2.x=899;
                   positionCurseur2.y=470;

                }
            else if (event.motion.x>=950 && event.motion.y>=645 && event.motion.x<=1680 && event.motion.y<=780)
                {
                    positionCurseur2.x=900;
                    positionCurseur2.y=649;

                }
            else
                {
                    positionCurseur1.x=1680;
                    positionCurseur1.y=1050;
                    positionCurseur2.x=1680;
                    positionCurseur2.y=1050;
                }

              break;

        case SDL_MOUSEBUTTONUP:

            if (event.button.x>=0 && event.button.y>=275 && event.button.x<=740 && event.button.y<=400)
                {
                    Inventaire();
                }
            else if (event.button.x>=0 && event.button.y>=462 && event.button.x<=740 && event.button.y<=595)
                {

                }
            else if (event.button.x>=0 && event.button.y>=645 && event.button.x<=740 && event.button.y<=780)
                {

                }
            else if (event.button.x>=950 && event.button.y>=275 && event.button.x<=1680 && event.button.y<=400)
                {

                }
            else if (event.button.x>=950 && event.button.y>=462 && event.button.x<=1680 && event.button.y<=595)
                {

                }
            else if (event.button.x>=950 && event.button.y>=645 && event.button.x<=1680 && event.button.y<=780)
                {
                    continuerIP=0;
                }

        break;
    break;
    }
      // Blit et refresh

 SDL_BlitSurface(interface,NULL,ecran,&position);
 SDL_BlitSurface(barreVie,&decoupeV,ecran,&positionBarreDeVieIP);
 SDL_BlitSurface(barreMana,&decoupeM,ecran,&positionBarreDeManaIP);
 SDL_BlitSurface(barreXP1,&decoupeXP1,ecran,&positionBarreXP1IP);
 SDL_BlitSurface(barreXP2,&decoupeXP2,ecran,&positionBarreXP2IP);
 SDL_BlitSurface(curseur1,NULL,ecran,&positionCurseur1);
 SDL_BlitSurface(curseur2,NULL,ecran,&positionCurseur2);


   SDL_Flip(ecran);
   SDL_Flip(curseur1);
   SDL_Flip(curseur2);
}

        //Fin systeme
   SDL_FreeSurface(interface);
   SDL_FreeSurface(ecran);
   SDL_FreeSurface(curseur1);
   SDL_FreeSurface(curseur2);
   SDL_FreeSurface(texte);
   SDL_FreeSurface(texte2);
   SDL_FreeSurface(texte3);
   SDL_FreeSurface(texte4);
   SDL_FreeSurface(texte5);
   SDL_FreeSurface(texte6);
   SDL_FreeSurface(FOR);
   SDL_FreeSurface(AGI);
   SDL_FreeSurface(DEF);
   SDL_FreeSurface(INT);
   SDL_FreeSurface(DEX);
   SDL_FreeSurface(CHA);
   SDL_FreeSurface(barreVie);
   SDL_FreeSurface(barreMana);
   SDL_FreeSurface(barreXP1);
   SDL_FreeSurface(barreXP2);
}

////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    int compteur=0, randCombat=0;
    int continuer = 1;
    const int MAX = 4, MIN = 1;

    SDL_Event event;
    SDL_Surface* ecran = NULL, *personnage=NULL, *Map=NULL;
    SDL_Rect positionpersonnage, positioncarte, positionMap, decoupeMap;

    personnage=SDL_LoadBMP("Sprites/MAP/Personnage.bmp");
    Map=SDL_LoadBMP("Sprites/MAP/Map.bmp");

    SDL_SetColorKey(personnage, SDL_SRCCOLORKEY, SDL_MapRGB(personnage->format, 0, 0, 255));    // pour définir la couleur invisible

//Affichage ecran
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE| SDL_FULLSCREEN |SDL_DOUBLEBUF);//SDL_FULLSCREEN);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

positionpersonnage.x=1680/2;
positionpersonnage.y=1050/2;

positionMap.x= 0;
positionMap.y= 0;
decoupeMap.x=500;
decoupeMap.h=1611;
decoupeMap.w=2405;
decoupeMap.y=560;

SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);

SDL_Flip(ecran);

    SDL_EnableKeyRepeat(10,10);            // pour que quand on garde la touche enfoncer il répète l'évènement

        while (continuer)               // début des conditions
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
    case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE: // Echap

        continuer=0;

        break;

            case SDLK_q:
{
InterfacePricipale ();
}
            break;


    case SDLK_UP: // Flèche haut
        {
            for(compteur=0;compteur<=8;compteur++)
            {
                if (decoupeMap.y==0)
                {

                        positionpersonnage.y=positionpersonnage.y-1;
                        SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                        SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);

                }
                else if ( decoupeMap.y!=0)
                {
                    if(positionpersonnage.y!=1050/2)
                    {
                        positionpersonnage.y=positionpersonnage.y-1;
                        SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);


                    }
                    else if (positionpersonnage.y==1050/2)
                    {
                        decoupeMap.y = decoupeMap.y-1;
                        decoupeMap.h=decoupeMap.h+1;

                    }
                }
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                SDL_Flip(ecran);
            }
//AléaCombat
srand(time(NULL));
randCombat = (rand() % (MAX - MIN + 1)) + MIN;
    if (randCombat==1)
        {
        combat();
        }
    }
break;

    case SDLK_DOWN: // Flèche bas
        {

        for(compteur=0;compteur<=8;compteur++)
            {
                if (decoupeMap.h==1611)
                {
                positionpersonnage.y=positionpersonnage.y+1;
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                }
                else if (decoupeMap.h!=1611)
                {
                    if(positionpersonnage.y!=1050/2)
                    {
                    positionpersonnage.y=positionpersonnage.y+1;
                    SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                    }
                else if (positionpersonnage.y==1050/2)
                {

                decoupeMap.h =decoupeMap.h-1;
                decoupeMap.y = decoupeMap.y+1;
                }

                }
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                SDL_Flip(ecran);
            }
//AléaCombat
srand(time(NULL));
randCombat = (rand() % (MAX - MIN + 1)) + MIN;
    if (randCombat==1)
        {
        combat();
        }
    }
break;

    case SDLK_RIGHT: // Flèche droite
        {
                for(compteur=0;compteur<=8;compteur++)
                    {
                    if (decoupeMap.w==2400)
                    {
                positionpersonnage.x=positionpersonnage.x+1;
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                    }
                    else if ( decoupeMap.w!=2400)
                    {
                        if (positionpersonnage.x!=1680/2)
                        {
                        positionpersonnage.x=positionpersonnage.x+1;
                        SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                        }
                        else if (positionpersonnage.x==1680/2)
                        {
                decoupeMap.w =decoupeMap.w-1;
                decoupeMap.x = decoupeMap.x+1;
                    }
                    }
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                SDL_Flip(ecran);
                }
//AléaCombat
srand(time(NULL));
randCombat = (rand() % (MAX - MIN + 1)) + MIN;
    if (randCombat==1)
        {
        combat();
        }
    }
break;

    case SDLK_LEFT: // Flèche gauche
        {
                for(compteur=0;compteur<=8;compteur++)
                    {
                    if (decoupeMap.x==0)
                    {
                positionpersonnage.x=positionpersonnage.x-1;
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                    }
                    else if (decoupeMap.x!=0)
                    {
                        if (positionpersonnage.x!=1680/2)
                        {
                        positionpersonnage.x=positionpersonnage.x-1;
                        SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);

                        SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);

                        }
                        else if (positionpersonnage.x==1680/2)
                        {
                decoupeMap.x = decoupeMap.x-1;
                decoupeMap.w =decoupeMap.w+1;
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                        }
                    }
                SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
                SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
                SDL_Flip(ecran);
                }
//AléaCombat
srand(time(NULL));
randCombat = (rand() % (MAX - MIN + 1)) + MIN;
    if (randCombat==1)
        {
        combat();
        }
    }
break;

}


    SDL_BlitSurface(Map, &decoupeMap, ecran, &positionMap);
    SDL_BlitSurface(ecran,NULL,ecran, &positionMap);
    SDL_BlitSurface(personnage, NULL, ecran, &positionpersonnage);
    SDL_Flip(ecran);
}

    }

TTF_Quit();
SDL_Quit();

 return EXIT_SUCCESS;

}
