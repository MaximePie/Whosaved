#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

//Inclusion des headers
#include "Structures.h"
#include "Constantes.h"

#include "Load_Items.h"
#include "Fenetres_Combat.h"




int affListeInventaire(int tabObjet[10], int deplaList, int listType,SDL_Surface *fenetreListe,SDL_Surface *ecran,SDL_Surface *texte,SDL_Rect positionFenetreListe, SDL_Rect postexte,sMESS_ITEMS *items_data,TTF_Font *police,SDL_Color noire)
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

    if (items_data->data[affichageinventaire].categorie==listType && items_data->data[affichageinventaire].possede==1)
        {
            if (anaItems>=deplaList)
                {
                    texte = TTF_RenderText_Blended(police ,items_data->data[affichageinventaire].name,noire);
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

void Inventaire(sJoueur *Perso,sMESS_ITEMS *items_data)
{

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
ecran=SDL_SetVideoMode(1680,1050,32,SDL_HWSURFACE/*|SDL_FULLSCREEN*/);
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

//Affichage interface
SDL_Surface* interface =NULL;
interface= SDL_LoadBMP("Sprites/II/Interface II.bmp");
SDL_SetColorKey(interface, SDL_SRCCOLORKEY, SDL_MapRGB(interface->format, 0, 0, 255));
position.x=0;
position.y=0;

//Affichage Fenetres Liste
SDL_Surface* fenetreListe = NULL;
fenetreListe = SDL_LoadBMP("Sprites/II/Liste II.bmp");
positionFenetreListe.x=113;
positionFenetreListe.y=189;

//Affichage Fenetres Select
SDL_Surface* fenetreSelect = NULL;
fenetreSelect = SDL_LoadBMP("Sprites/II/Fenetre Select II.bmp");
SDL_SetColorKey(fenetreSelect, SDL_SRCCOLORKEY, SDL_MapRGB(fenetreSelect->format, 0, 0, 255));
positionFenetreSelect.x=113;
positionFenetreSelect.y=0;

//Affichage Onglets
SDL_Surface* Onglets = NULL;
Onglets = SDL_LoadBMP("Sprites/II/Onglets II.bmp");
SDL_SetColorKey(Onglets, SDL_SRCCOLORKEY, SDL_MapRGB(Onglets->format, 0, 0, 255));
positionOnglets.x=722;

//Affichage Onglets
SDL_Surface* ImagesOnglets = NULL;
ImagesOnglets = SDL_LoadBMP("Sprites/II/Images Onglets II.bmp");
SDL_SetColorKey(ImagesOnglets, SDL_SRCCOLORKEY, SDL_MapRGB(ImagesOnglets->format, 0, 0, 255));
positionImagesOnglets.x=724;
positionImagesOnglets.y=162;

//Affichage Refresh Equipement
SDL_Surface* refreshEquipement = NULL;
refreshEquipement = SDL_LoadBMP("Sprites/II/Refersh Equipement II.bmp");
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


affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

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

                            default:
                                break;

                        }
                    break;

                case SDL_MOUSEBUTTONDOWN:

//SELECTION
                if (event.button.x>=112 && event.button.y>=188 && event.button.x<=676 && event.button.y<=255)
                    {
                        Select =0;

                        positionFenetreSelect.y=189;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=256 && event.button.x<=676 && event.button.y<=325)
                    {
                        Select =1;

                        positionFenetreSelect.y=256;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=326 && event.button.x<=676 && event.button.y<=391)
                    {
                        Select=2;

                        positionFenetreSelect.y=324;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=391 && event.button.x<=676 && event.button.y<=460)
                    {
                        Select =3;

                        positionFenetreSelect.y=389;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=461 && event.button.x<=676 && event.button.y<=525)
                    {
                        Select =4;

                        positionFenetreSelect.y=457;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=526 && event.button.x<=676 && event.button.y<=592)
                    {
                        Select =5;

                        positionFenetreSelect.y=524;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>593 && event.button.x<=676 && event.button.y<=660)
                    {
                        Select =6;

                        positionFenetreSelect.y=590;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=661 && event.button.x<=676 && event.button.y<=725)
                    {
                        Select =7;

                        positionFenetreSelect.y=658;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=725 && event.button.x<=676 && event.button.y<=792)
                    {
                        Select =8;

                        positionFenetreSelect.y=722;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=112 && event.button.y>=793 && event.button.x<=676 && event.button.y<=959)
                    {
                        Select =9;

                        positionFenetreSelect.y=791;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }

//FLECHES
                if (event.button.x>=9 && event.button.y>=532 && event.button.x<=100 && event.button.y<=700)
                    {

                            deplaList++;
                                                    affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                            SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                            SDL_Flip(ecran);

                    }
                if (event.button.x>=9 && event.button.y>=361 && event.button.x<=100 && event.button.y<=531)
                    {
                        if (deplaList>0)
                            {
                        deplaList--;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                            }
                    }

//ONGLETS
                if (event.button.x>=722 && event.button.y>=170 && event.button.x<=810 && event.button.y<=305)
                    {
                    deplaList=0;
                    listType=1;
                                            affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
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
                                            affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
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
                                            affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
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
                    affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
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
                                            affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);

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
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==1)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==2)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==3)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==4)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==5)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==6)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==7)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==8)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=1215 && event.button.y>=859 && event.button.x<=1614 && event.button.y<=1011 && Select==9)
                    {
                        items_data->data[tabObjet[Select]].equipe=1;
                        items_data->data[tabEquipement[items_data->data[tabObjet[Select]].categorie]]=items_data->data[tabObjet[Select]];
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                    }

//JETER
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==0 && items_data->data[tabObjet[Select]].equipe==0)
                    {

                                items_data->data[tabObjet[Select]].possede=0;
                                items_data->data[tabObjet[Select]].equipe=0;

                                                        affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                                SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                                affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);
                                SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==1 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==2 && items_data->data[tabObjet[Select]].equipe==0)
                    {

                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                        affEquip(Perso,tabEquipement,ecran,refreshEquipement,texte,postexte,posrefreshEquipement,police,noire,items_data);

                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==3 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==4 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==5 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==6 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==7 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==8 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }
                if (event.button.x>=672 && event.button.y>=900 && event.button.x<=986 && event.button.y<=1050 && Select==9 && items_data->data[tabObjet[Select]].equipe==0)
                    {
                        items_data->data[tabObjet[Select]].possede=0;
                                                affListeInventaire(tabObjet, deplaList ,listType,fenetreListe, ecran, texte, positionFenetreListe, postexte, items_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,ecran,&positionFenetreSelect);
                        SDL_Flip(ecran);
                    }



                break;
            break;
                }

    }




}


int affEquip(sJoueur *Perso,int tabEquipement[7],SDL_Surface *ecran,SDL_Surface *refreshEquipement,SDL_Surface *texte,SDL_Rect postexte,SDL_Rect posrefreshEquipement,TTF_Font *police,SDL_Color noire,sMESS_ITEMS *items_data)
{

int a=0;
for (a=0;a<1;a++)
    {
        posrefreshEquipement.x=1209;
        posrefreshEquipement.y=205;
        postexte.x=1215;
        postexte.y=202;
        texte = TTF_RenderText_Blended(police ,items_data->data[tabEquipement[a]].name,noire);
        SDL_BlitSurface(refreshEquipement,NULL,ecran,&posrefreshEquipement);
        SDL_BlitSurface(texte,NULL,ecran,&postexte);
        postexte.y+=89;
        posrefreshEquipement.y+=90;
        Perso->force+=items_data->data[tabEquipement[a]].force;
        Perso->agilite+=items_data->data[tabEquipement[a]].agilite;
        Perso->defense+=items_data->data[tabEquipement[a]].defense;
        Perso->intelligence+=items_data->data[tabEquipement[a]].intelligence;
        Perso->dexterite+=items_data->data[tabEquipement[a]].dexterite;
        Perso->charisme+=items_data->data[tabEquipement[a]].charisme;


    }
        postexte.x=900;
        postexte.y=65;
        char tampon [3]={0,0,0};
        sprintf (tampon, "%d", Perso->force);
        texte = TTF_RenderText_Blended(police,tampon,noire);

       SDL_BlitSurface(texte,NULL,ecran,&postexte);
       SDL_Flip(ecran);
}



void InterfacePricipale(sJoueur *Perso, sMESS_ITEMS *item_data)
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
   SDL_Surface* ecran = NULL;
   ecran=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE/*|SDL_FULLSCREEN*/);
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

                  default:
                    ;

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
                    Inventaire(Perso, item_data);
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
