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

void Refresh(sStatiques Refresh)
{
    //interface,position,Perso_Image,decoupeP,position_Perso,Monstre_Image,decoupeE,position_Monstre,barreVie,decoupeVP,pos_Barre_de_vie_P,barreMana,decoupeMP,pos_Barre_Mana,barreEnnemi,decoupeVE,pos_Barre_vie_E,Niveau_Perso,posNiveau,Pv_Max_Perso,pos_Pv_Max,Pv_Perso,pos_Pv_P
    SDL_BlitSurface(Refresh.fond,NULL,Refresh.ecran,&Refresh.position);
    SDL_BlitSurface(Refresh.Perso_Image,&Refresh.decoupeP,Refresh.ecran,&Refresh.position_Perso);
    SDL_BlitSurface(Refresh.Monstre_Image,&Refresh.decoupeE,Refresh.ecran,&Refresh.position_Monstre);
    SDL_BlitSurface(Refresh.interface,NULL,Refresh.ecran,&Refresh.position);

    SDL_BlitSurface(Refresh.barreEnnemi,&Refresh.decoupeVE,Refresh.ecran,&Refresh.pos_Barre_vie_E);
    SDL_BlitSurface(Refresh.barreVie,&Refresh.decoupeVP,Refresh.ecran,&Refresh.pos_Barre_de_vie_P);
    SDL_BlitSurface(Refresh.barreMana,&Refresh.decoupeMP,Refresh.ecran,&Refresh.pos_Barre_Mana);


    SDL_BlitSurface(Refresh.NiveauFond,NULL,Refresh.ecran,&Refresh.position);

    SDL_BlitSurface(Refresh.Niveau_Perso,NULL,Refresh.ecran,&Refresh.posNiveau);

    SDL_BlitSurface(Refresh.Pv_Max_Perso,NULL,Refresh.ecran,&Refresh.pos_Pv_Max);
    SDL_BlitSurface(Refresh.Pv_Perso,NULL,Refresh.ecran,&Refresh.pos_Pv_P);




    SDL_Flip(Refresh.ecran);
}


void closeFenetre(SDL_Surface *interface,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Rect position, SDL_Rect positionFenetre, SDL_Rect decoupeF,int deroulement,sStatiques Refresh0)
{

    for(deroulement=0;deroulement<=206;deroulement=deroulement+68)
        {
            positionFenetre.y=214+deroulement;
            decoupeF.y=deroulement;

            SDL_BlitSurface(interface,NULL,ecran,&position);
            SDL_BlitSurface(fenetre,&decoupeF,ecran,&positionFenetre);
            Refresh(Refresh0);

            SDL_Flip(ecran);
        }

}


void affFenetre(sStatiques Refresh0,SDL_Surface *fenetreListe,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Surface *curseur,SDL_Rect positionCurseur, SDL_Rect positionFenetre, SDL_Rect positionFenetreListe, SDL_Rect decoupeF,int deroulement)
{

SDL_BlitSurface(curseur,NULL,ecran,&positionCurseur);

Refresh(Refresh0);

SDL_Flip(ecran);

    for(deroulement=210 ;deroulement>=0;deroulement=deroulement-2)
        {
            positionFenetre.y=214 +deroulement;
            decoupeF.y=deroulement;

            SDL_BlitSurface(fenetre,&decoupeF,ecran,&positionFenetre);;

            SDL_Flip(ecran);
        }
}

int affListeCombat(int tabObjet[10], int deplaList, int listType,SDL_Surface *fenetreListe,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Surface *texte,SDL_Rect positionFenetre,SDL_Rect positionFenetreListe, SDL_Rect postexte,sMESS_ITEMS *items_data,TTF_Font *police,SDL_Color noire)
    {
        police=TTF_OpenFont("carolingia.ttf",15);

    //affichage liste

SDL_BlitSurface(fenetreListe,NULL,fenetre,&positionFenetreListe);
SDL_Flip(fenetre);

int listeActive=10;
int affichageinventaire=0,pos=0,anaItems=0, compteur=0;


for (affichageinventaire=listeActive-10;affichageinventaire<listeActive;affichageinventaire++)
    {
        postexte.x=26;
        postexte.y=10+pos;



    if (items_data->data[affichageinventaire].categorie==listType&&items_data->data[affichageinventaire].possede!=0)
        {
            if (anaItems>=deplaList)
                {
                    texte = TTF_RenderText_Blended(police ,items_data->data[affichageinventaire].name,noire);
                    SDL_BlitSurface(texte,NULL,fenetre,&postexte);
                    pos+=16;
                    tabObjet[compteur]=affichageinventaire;
                    compteur++;


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






//GESTION DES EVENEMENTS///////////////////////////
int Analyse_Clic(SDL_Event *event, int numFenetre)
{
    if(numFenetre== -1) //RETURN DE 100 à 200
    {
        if (event->button.x>=120 && event->button.y>=105 && event->button.y<=122 && event->button.x<=290)
            return 1;

    }

    //RETURN DE 0 à 100
    if ( event->button.x>=0 && event->button.y>=417 && event->button.x<=125 && numFenetre!=1)
        return 1;

      if (event->button.x>=130 && event->button.y>=417 && event->button.x<=253 &&  numFenetre!=2)
        return 2;

    if (event->button.x>=673 && event->button.y>=417 && event->button.x<=1008 &&  numFenetre!=3)
        return 3;

//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////AJOUT///////////////////////////////////
    if (event->button.x>=1009 && event->button.y>=417 && event->button.x<=1344 &&  numFenetre!=4)
        return 4;

    if (event->button.x>=1345 && event->button.y>=417 && event->button.x<=1680 &&   numFenetre!=5)
        return 5;
////////////////////////////////////////AJOUT FIN//////////////////////////////////
//////////////////////////////////////////////////////////////////////////

    if (event->button.x>=10 && event->button.y>=650 && event->button.x<=47 && event->button.y<=718 && numFenetre==1)
        return 6;
    if (event->button.x>=10 && event->button.y>=583 && event->button.x<=47 && event->button.y<=649&& numFenetre==1)
        return 7;

    if (event->button.x>=24 && event->button.y>=225 && event->button.x<=152 && event->button.y<=240 && numFenetre==1)//+33
        return 16;
    if (event->button.x>=24 && event->button.y>=240 && event->button.x<=152 && event->button.y<=255 && numFenetre==1)
        return 17;





    else
        return 0;

}
