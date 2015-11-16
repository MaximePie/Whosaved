#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

//Inclusion des headers
#include "Structures.h"
#include "Constantes.h"
#include "Load_Items.h"


int Ini_ID(int mapid1, int mapid2)
{
    switch(mapid1)
    {
    case 1:
            switch(mapid2)
            {
                case 1:
                    return 1;
                break;

                case 2:
                    return 2;
                break;
            }
    break;
    }

}

//Initialisation du joueur avant le combat, cette fonction sera à supprimer par la suite !
void Ini_Joueur(sJoueur* Perso)
{

    sprintf(Perso->name,"Chatmalow");

    Perso->pv_max=30;
    Perso->pv=Perso->pv_max;
    Perso->mana=50;
    Perso->mana_max=Perso->mana;

    Perso->force=7;
    Perso->agilite=3;
    Perso->defense=4;
    Perso->dexterite=3;
    Perso->intelligence=4;

    Perso->xp=0;
    Perso->xp_pallier=20;
    Perso->niveau=1;
    Perso->gold=0;



}

//Initialisation du monstre avant le combat
void Ini_Ennemi(sEnnemi* Monstre, int IDMonstre)
{
    int i=0;
    char nom[16] = "";

    switch(IDMonstre)
    {

    case 1: //Gwilgi

    nom[0] = 'G';
    nom[1] = 'w';
    nom[2] = 'i';
    nom[3] = 'l';
    nom[4] = 'g';
    nom[5] = 'i';

        Monstre->pv_max=12+(rand() % 5) + 1 - 3;
        Monstre->pv=Monstre->pv_max;

        Monstre->force=4 + (rand() % 3) + 1 - 2;
        Monstre->agilite=2 + (rand() % 3) + 1 - 2;
        Monstre->intelligence=1 + (rand() % 3) + 1 - 2;
        Monstre->defense=2 + (rand() % 3) + 1 - 2;
        Monstre->dexterite=0;

        Monstre->xp=54 + (rand() % 23) + 1 - 12;
        Monstre->gold=15 + (rand() % 7) + 1 - 4;
    break;



    case 2: //Stawk

        nom[0] = 'S';
        nom[1] = 't';
        nom[2] = 'a';
        nom[3] = 'w';
        nom[4] = 'k';

        Monstre->pv_max=10+ (rand() % 7) + 1 - 3;
        Monstre->pv=Monstre->pv_max;

        Monstre->force=4 + (rand() % 3) + 1 - 2;
        Monstre->agilite=2 + (rand() % 3) + 1 - 2;
        Monstre->intelligence=1;
        Monstre->defense=2 + (rand() % 3) + 1 - 2;
        Monstre->dexterite=0;

        Monstre->xp=67 + (rand() % 27) + 1 - 8;
        Monstre->gold=25 + (rand() % 11) + 1 - 6;
    break;


    }


    for (i=0;i<16;i++)
    {
        Monstre->name[i]=nom[i];
    }

}



void Ini_Sprites(sStatiques *Refresh,sJoueur *Perso, int IDMonstre)
{
    //PERSONNAGE
Refresh->Perso_Image =IMG_Load("Sprites/Combat/Perso_Combat.png");
Refresh->position_Perso.x=0;
Refresh->position_Perso.y=218;

Refresh->decoupeP.x=0;
Refresh->decoupeP.y=218;
Refresh->decoupeP.w=262;
Refresh->decoupeP.h=215;

//MONSTRE

switch(IDMonstre)
{
    case 1:
    Refresh->Monstre_Image = IMG_Load("Sprites/Combat/Palette_combat_1.png");

    Refresh->decoupeE.x=153;
    Refresh->decoupeE.y=0; //Première ligne
    Refresh->decoupeE.w=129;
    Refresh->decoupeE.h=107;

    break;

    case 2:
    Refresh->Monstre_Image = IMG_Load("Sprites/COMBAT/Monstres/Stawk.png");

    Refresh->decoupeE.x=153;
    Refresh->decoupeE.y=0;
    Refresh->decoupeE.w=129;
    Refresh->decoupeE.h=107;
    break;
}
Refresh->position_Monstre.x=435;
Refresh->position_Monstre.y=180;


//Affichage fond interface
Refresh->fond = IMG_Load("Sprites/Combat/fond.png");
Refresh->interface = IMG_Load("Sprites/Combat/Interface Combat.png");

Refresh->position.x=0;
Refresh->position.y=0;

//Affichage Barre de vie et Mana

Refresh->barreVie = IMG_Load("Sprites/Combat/Barre De Vie IC.png");
Refresh->barreMana = IMG_Load("Sprites/Combat/Barre De Mana IC.png");
Refresh->barreEnnemi=IMG_Load("Sprites/Combat/Barre De Vie Monstre IC.png");

Refresh->pos_Barre_de_vie_P.x=45;
Refresh->pos_Barre_de_vie_P.y=0;

Refresh->pos_Barre_Mana.x=74;
Refresh->pos_Barre_Mana.y=47;


Refresh->pos_Barre_vie_E.x=460;
Refresh->pos_Barre_vie_E.y=0;

//AFFICHAGE FOND NIVEAU
Refresh->NiveauFond = IMG_Load("Sprites/Combat/niveau.png");

//DECOUPAGE DES BARRES

Refresh->decoupeVP.x=45;
Refresh->decoupeVP.y=0;
Refresh->decoupeVP.w=324/(Perso->pv_max)*(Perso->pv + 2);
Refresh->decoupeVP.h=100;

Refresh->decoupeVE.x=460;
Refresh->decoupeVE.y=0;
Refresh->decoupeVE.w=90;
Refresh->decoupeVE.h=500;

Refresh->decoupeMP.x=74;
Refresh->decoupeMP.y=48;
Refresh->decoupeMP.w=282/(Perso->mana_max) * (Perso->mana);
Refresh->decoupeMP.h=33;





}


sMESS_ITEMS Load_Skills_Monstre(int IDMonstre)
{


    switch(IDMonstre)
    {
        case 1:
            return MESS_LoadItems("Gwigli.bin",0);
        break;

        case 2:
            return MESS_LoadItems("Stawk.bin",0);
        break;
    }
}

void ini_Quete(sQueteconditions *Quete_cond)
{
    Quete_cond->biere = 0;
}

