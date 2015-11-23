/*Ce fichier contient : -Toutes les structures du programme
                        -Toutes les fonctions d'initialisation des structures
                        */

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include "Constantes.h"


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

typedef struct{

    int biere;


}sQueteconditions;

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



typedef struct
{
    SDL_Surface *fond;
    SDL_Surface *ecran;
    SDL_Surface *interface;
    SDL_Rect position;
    SDL_Surface *Perso_Image;
    SDL_Rect decoupeP;
    SDL_Rect position_Perso;
    SDL_Surface *Monstre_Image;
    SDL_Rect decoupeE;
    SDL_Rect position_Monstre;
    SDL_Surface *barreVie;
    SDL_Rect decoupeVP;
    SDL_Rect pos_Barre_de_vie_P;
    SDL_Surface *barreMana;
    SDL_Rect decoupeMP;
    SDL_Rect pos_Barre_Mana;
    SDL_Surface *barreEnnemi;
    SDL_Rect decoupeVE;
    SDL_Rect pos_Barre_vie_E;
    SDL_Surface *Niveau_Perso;
    SDL_Rect posNiveau;
    SDL_Surface * Pv_Max_Perso;
    SDL_Rect pos_Pv_Max;
    SDL_Surface * Pv_Perso;
    SDL_Rect pos_Pv_P;

    SDL_Surface *NiveauFond;

}   sStatiques;


int Ini_ID(int mapid1, int mapid2);

void Ini_Joueur(sJoueur* Perso);
void Ini_Ennemi(sEnnemi* Monstren,int IDMonstre);
void Ini_Sprites(sStatiques *Refresh, sJoueur* Perso,int IDMonstre);
void ini_Quete(sQueteconditions *Quete_cond);
sMESS_ITEMS Load_Skills_Monstre(int IDMonstre);

#endif // STRUCTURES_H_INCLUDED
