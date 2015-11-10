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
#include "Actions_Combat.h"


void combat(sJoueur *Perso,sMESS_ITEMS *skills_data,SDL_Surface *ecran, int map_id[2])
{
    int IDMonstre = Ini_ID(map_id[0],map_id[1]);


    sStatiques Refresh0;
    Refresh0.ecran = ecran;
    //Temporaire
    SDL_Surface *Coordonnees=NULL;

//Initiaisation

int tabObjet[10];
int deplaList=0;
int deroulement;
int listType=0;
int i=0;
int Mort=0;
TTF_Init();
SDL_Rect postexte;
SDL_Surface *texte =NULL;
TTF_Font *police=TTF_OpenFont("carolingia.ttf",25);
SDL_Color noire = {135,65,14};
SDL_Rect position,positionBarreDeManaIC,positionCurseur,positionFenetre,positionFenetreListe,decoupeF,positionFenetreSelect,posMiniOnglet,position_Mana_Perso;

skills_data->data[2].possede=1;
skills_data->data[2].equipe=1;

sMESS_ITEMS skills_monstre_data = Load_Skills_Monstre(IDMonstre);



Ini_Sprites(&Refresh0, Perso, IDMonstre);

//Chargement et initialisation du monstre
SDL_SetVideoMode(640,480,32,SDL_HWSURFACE/*|SDL_FULLSCREEN*/);
sEnnemi Monstre;
Ini_Ennemi(&Monstre,IDMonstre);

//////////////////////////////////////////:

//Affichage ecran
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
//Affichage du fond.
SDL_BlitSurface(Refresh0.fond,NULL,ecran,&position);
//

//Affichage Curseur
SDL_Surface* curseur =NULL;
curseur= SDL_LoadBMP("Sprites/Combat/Curseur IC.bmp");
SDL_SetColorKey(curseur, SDL_SRCCOLORKEY, SDL_MapRGB(curseur->format, 0, 0, 255));
positionCurseur.x=1680;
positionCurseur.y=0;

//Affichage Fenetres
SDL_Surface* fenetre = NULL;
fenetre = IMG_Load("Sprites/Combat/Fenetre IC.png");
SDL_SetColorKey(fenetre, SDL_SRCCOLORKEY, SDL_MapRGB(fenetre->format, 0, 0, 255));
positionFenetre.x=1680;
positionFenetre.y=1050;
decoupeF.x=0;
decoupeF.y=0;
decoupeF.w=482;
decoupeF.h=549;

//Affichage Fenetres Liste
SDL_Surface* fenetreListe = NULL;
fenetreListe = IMG_Load("Sprites/Combat/Liste IC.png");
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
//ANALYSE DE LA FUITE
int randFuite=0;

/////////////////////////

///////////Affichage des valeurs
noire.r = 0;
noire.g = 0;
police = TTF_OpenFont("carolingia.ttf" ,45);
char Niveau_P[2], Pv_Max_P[3], Pv_P[3], Mana_Max_P[3], Mana_P[3], Nom_M[16];
sprintf(Niveau_P,"%d",Perso->niveau);

SDL_Surface *Niveau_Perso = TTF_RenderText_Blended(police ,Niveau_P,noire);
Refresh0.Niveau_Perso = TTF_RenderText_Blended(police ,Niveau_P,noire);

SDL_Rect posNiveau={27,21};
Refresh0.posNiveau.x=27;
Refresh0.posNiveau.y=21;

//Chargement des PV (affichage des nombres) du personnage
int Vie_Actuelle_Decoupe=0; //Il s'agit d'une variable utilisée dans les fonctions de combat.
police = TTF_OpenFont("carolingia.ttf" ,24);
sprintf(Pv_Max_P,"/%d",Perso->pv_max);
sprintf(Pv_P,"%d",Perso->pv);
SDL_Surface *Pv_Max_Perso = TTF_RenderText_Blended(police, Pv_Max_P, noire), *Pv_Perso = TTF_RenderText_Blended(police, Pv_P, noire);

SDL_Rect pos_Pv_Max={205,14}, pos_Pv_P={170,14};

Refresh0.Pv_Max_Perso = TTF_RenderText_Blended(police, Pv_Max_P, noire);
Refresh0.Pv_Perso = TTF_RenderText_Blended(police, Pv_P, noire);

Refresh0.pos_Pv_Max.x=205;
Refresh0.pos_Pv_Max.y=14;

Refresh0.pos_Pv_P.x = 170;
Refresh0.pos_Pv_P.y = 14;



SDL_Surface *Mana_Perso;


noire.r = 135;
noire.g = 65;
police = TTF_OpenFont("carolingia.ttf" ,15);
///////////////////////


//VARIABLES PROPRES AUX ATTAQUES ENNEMIES ET ALLIEES.
int Vie_Perdue=0, Diminution=0;
////////////////////////////

//AFFICHAGE TEXTE
char Texte[16][128];
sprintf(Texte[0],"Que faire ?");
char Texte_2[16];
//Texte[2] = "Jean le troll perd x PV !
sprintf(Texte[3],"%s Attaque !",Monstre.name);

sprintf(Texte[5],"Tentative de fuite...");
sprintf(Texte[6],"Fuite réussie ! %s s'enfuit du combat comme un lâche !",Perso->name);
sprintf(Texte[7],"Echec !");

sprintf(Texte[8],"%s est vaincu !",Monstre.name);
sprintf(Texte[9],"%s gagne %d XP et %d Gold !",Perso->name,Monstre.xp,Monstre.gold);

//SI LEVEL UP
sprintf(Texte[10],"Level up !");

postexte.x=420;
postexte.y=16;
//FIN COMBAT
int Xp_reste=0, Xp_reste_aff=0;
///////////////////

//LEVEL_UP
int attaque=0, vie = 0, pallier=0, defense=0;
////////////////////////


//Blitage de toutes les surfaces en général
Refresh(Refresh0);
////////////////////////////////////////////////

//EVENT

 int continuer = 1;
 int numFenetre=0;
    SDL_Event event;

    while (continuer)
        {
            SDL_WaitEvent(&event);
            police = TTF_OpenFont("carolingia.ttf" ,15);

            noire.r=0;
            noire.g=0;
            texte = TTF_RenderText_Blended(police,Texte[0],noire);
            postexte.x=420;
            postexte.y=16;

            SDL_BlitSurface(texte,NULL,ecran,&postexte);
            SDL_Flip(ecran);
            noire.r = 135;
            noire.g = 65;



            switch(event.type)
                {


                    case SDL_MOUSEMOTION:
                    break;

                    case SDL_KEYDOWN:

                    switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;

//CETTE PARTIE A ETE CREEE PAR MOI POUR QUE JE PUISE BOSSER SUR MON PC DE MORT ! A SUPPRIMER !
//////////////////////////////////////////////////////////////////////////////////////////////
                            case SDLK_q: //SI FUITE (FENETRE 5)

                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);

                        positionCurseur.x=1583;
                        positionCurseur.y=908;
                        positionFenetre.x=1680;
                        numFenetre=5;
                        SDL_BlitSurface(curseur,NULL,ecran,&positionCurseur);
                        SDL_Flip(ecran);

                             Refresh(Refresh0);
                                noire.r=0;
                                noire.g=0;
                                noire.b=0;
                                texte = TTF_RenderText_Blended(police,Texte[5],noire);
                            SDL_BlitSurface(texte,NULL,ecran,&postexte);
                            SDL_Flip(ecran);

                        SDL_Delay(500);

                        srand(time(NULL));
                        randFuite = (rand() % (MAX_FUITE - MIN + 1)) + MIN;
                            if (randFuite==1)
                            {
                                Refresh(Refresh0);
                                texte=TTF_RenderText_Blended(police,Texte[6],noire);
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);
                                SDL_Delay(500);
                                 continuer=0;
                            }

                                else
                                {
                    //L'ENNEMI ATTAQUE A SON TOUR..

                                Refresh(Refresh0);
                                texte=TTF_RenderText_Blended(police,Texte[7],noire);
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);

                            SDL_Delay(500);
                            Refresh0.decoupeE.x=536;
                            Vie_Perdue=Monstre.force-Perso->defense;



                              Refresh(Refresh0);
                                police = TTF_OpenFont("carolingia.ttf" ,15);
                                texte = TTF_RenderText_Blended(police,Texte[3],noire);
                                postexte.x=420;
                                postexte.y=15;
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);
                                police = TTF_OpenFont("carolingia.ttf" ,36);

                            SDL_Delay(500);

                                Refresh(Refresh0);
                                sprintf(Texte[4],"%s Perd %d PV ! ",Perso->name,Vie_Perdue);
                                police = TTF_OpenFont("carolingia.ttf" ,36);
                                texte = TTF_RenderText_Blended(police,Texte[4],noire);
                                postexte.x=420;
                                postexte.y=35;
                                SDL_BlitSurface(texte,NULL,ecran,&postexte);
                                SDL_Flip(ecran);

                                SDL_Delay(500);
                            Diminution = 864/Perso->pv_max*Vie_Perdue;
                            Vie_Actuelle_Decoupe = Refresh0.decoupeVP.w;

                                police = TTF_OpenFont("carolingia.ttf" ,40);
                                Perso->pv-=Vie_Perdue;
                                sprintf(Pv_P,"%d",Perso->pv);
                                Pv_Perso=TTF_RenderText_Blended(police,Pv_P,noire);
                                noire.r = 135;
                                noire.g = 65;



                                for(i=Vie_Actuelle_Decoupe;Vie_Actuelle_Decoupe-Diminution<=i;i-=5)
                                {

                                    Refresh0.decoupeVP.w=i;

                                    Refresh(Refresh0);


                                }

                                Refresh0.decoupeVP.w=Perso->pv*(864/Perso->pv_max);

                                Refresh0.decoupeE.x=282;

                                Refresh(Refresh0);
                              if(Perso->pv<=0)
                                    continuer=0;
                                }



                                break;
//////////////////////////////////FIN DE LA PARTIE "SPECIALE PC CHAT///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

                            default:
                                ;


                        }
                    break;


                    case SDL_MOUSEBUTTONDOWN:
                    posfenetre=Analyse_Clic(&event,numFenetre);
                    switch(posfenetre)

                    {

                    case 0://Fermeture

                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);

                        positionCurseur.x=1680;
                        positionFenetre.x=1680;
                        numFenetre=0;

                        Refresh(Refresh0);


                        SDL_Flip(ecran);

                        break;

                    case 1://FENETRE-Fenetre 1

                        deplaList=0;
                        numFenetre=1;
                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);
                        Refresh(Refresh0);

                        positionCurseur.x=105;
                        positionCurseur.y=415;
                        positionFenetre.x=0;
                        listType=0;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                    break;

                    case 2:
                        //Fenetre 2 (Defense)
                        deplaList=0;
                        numFenetre=2;
                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);
                        Refresh(Refresh0);
                        positionCurseur.x=219;
                        positionCurseur.y=415;
                        positionFenetre.x=128;
                        listType=1;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                    break;

                    case 3:
                        //Fenetre 3 (Sorts)
                        deplaList=0;
                        numFenetre=3;
                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);
                        Refresh(Refresh0);

                        positionCurseur.x=911;
                        positionCurseur.y=908;
                        positionFenetre.x=672;
                        listType=2;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

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

                                affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                            }

                    break;

                    case 7: //BOUTON 1.2
                        if (deplaList>0 )
                            {
                                if (numFenetre==1)
                                    {
                                        deplaList=deplaList-1;

                                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                                    }
                            }
                    break;



                //SI FENETRE 1 OUVERTE

                    case 16: //LE JOUEUR CLIQUE SUR ONGLET 1.1

                        positionFenetreSelect.x=23;
                        positionFenetreSelect.y=10;
                        SDL_Flip(ecran);

                        if (Perso->mana < skills_data->data[tabObjet[0]].intelligence)
                        {
                        Refresh(Refresh0);

                        sprintf(Texte,"Pas assez de mana ! ");
                        texte = TTF_RenderText_Blended(police,Texte,noire);
                        SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                        SDL_Flip(Refresh0.ecran);
                        SDL_Delay(1000);
                        sprintf(Texte,"Que faire ? ");

                        Refresh(Refresh0);
                        break;
                        }

                        Attaque_Perso(Perso, &Monstre, skills_data,&Refresh0, tabObjet[0]);

                         Mort = Mort_Chck(Perso, &Monstre, Refresh0, skills_data);
                            if (Mort)
                            {
                                continuer=0;
                                break;
                            }

                        Attaque_Ennemi(Perso,&Monstre, skills_data, &Refresh0, tabObjet[0], &Pv_Max_P, &Pv_P, IDMonstre, &skills_monstre_data);
                             if(Perso->pv<=0)
                                    continuer=0;



                        break;

                        case 17:
                        //BOUTON 1.2 (ONGLET 2, FENETRE 1)

                        positionFenetreSelect.x=23;
                        positionFenetreSelect.y=25;

                        Refresh(Refresh0);

                        if (Perso->mana < skills_data->data[tabObjet[1]].intelligence)
                        {
                        Refresh(Refresh0);

                        sprintf(Texte,"Pas assez de mana ! ");
                        texte = TTF_RenderText_Blended(police,Texte,noire);
                        SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                        SDL_Flip(Refresh0.ecran);
                        SDL_Delay(1000);
                        sprintf(Texte,"Que faire ? ");

                        Refresh(Refresh0);
                        break;
                        }

                        Attaque_Perso(Perso, &Monstre, skills_data,&Refresh0, tabObjet[1]);

                        Refresh(Refresh0);

                        Mort = Mort_Chck(Perso, &Monstre, Refresh0, skills_data);
                            if (Mort)
                            {
                                continuer=0;
                                break;
                            }

                        Attaque_Ennemi(Perso,&Monstre, skills_data, &Refresh0, tabObjet[1], &Pv_Max_P, &Pv_P,IDMonstre, &skills_monstre_data);
                             if(Perso->pv<=0)
                                    continuer=0;


                        break;

                 case 4: // Objets

                        deplaList=0;
                        numFenetre=4;
                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);

                        positionCurseur.x=1247;
                        positionCurseur.y=908;
                        positionFenetre.x=1008;
                        listType=3;


                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

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


                    break;

                case 5:
                    {//Si Fuite
                        closeFenetre(Refresh0.interface,fenetre,ecran,position, positionFenetre, decoupeF, deroulement,Refresh0);

                        positionCurseur.x=1583;
                        positionCurseur.y=908;
                        positionFenetre.x=1680;
                        numFenetre=5;
                        SDL_BlitSurface(curseur,NULL,ecran,&positionCurseur);
                        SDL_Flip(ecran);

                        srand(time(NULL));
                        int randFuite = (rand() % (MAX_FUITE - MIN + 1)) + MIN;
                            if (randFuite)
                                continuer=0;


                    }
                    break;
//////////////////////////////AJOUTFIN////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//BOUTONS FENETRES HAUT BAS

                if (event.button.x>=346 && event.button.y>=650 && event.button.x<=384 && event.button.y<=718 && numFenetre==2)
                    {//BOUTON 2.1
                        if (numFenetre==2)
                            {
                                deplaList=deplaList+1;

                                affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                            }
                    }
                else if (event.button.x>=346 && event.button.y>=583 && event.button.x<=384 && event.button.y<=649 && numFenetre==2)
                    {//BOUTON 2.2
                        if (deplaList>0)
                            {
                                if (numFenetre==2)
                                    {
                                        deplaList=deplaList-1;

                                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                                    }
                            }
                    }
                else if (event.button.x>=683 && event.button.y>=650 && event.button.x<=721 && event.button.y<=718 && numFenetre==3)
                    {//BOUTON 3.1
                        if (numFenetre==3)
                            {
                                deplaList=deplaList+1;

                                affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                            }
                    }
                else if (event.button.x>=683 && event.button.y>=583 && event.button.x<=721 && event.button.y<=649 && numFenetre==3)
                    {//BOUTON 3.2
                        if (deplaList>0)
                            {
                                if (numFenetre==3)
                                    {
                                        deplaList=deplaList-1;

                                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                                    }
                            }
                    }
                else if (event.button.x>=1019 && event.button.y>=650 && event.button.x<=1057 && event.button.y<=718 && numFenetre==4)
                    {//BOUTON 4.1
                       if (numFenetre==4)
                           {
                                deplaList=deplaList+1;

                                affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                          }
                    }
                else if (event.button.x>=1019 && event.button.y>=583 && event.button.x<=1057 && event.button.y<=649 && numFenetre==4)
                    {//BOUTON 4.2
                        if (deplaList>0)
                            {
                               if (numFenetre==4)
                                   {
                                        deplaList=deplaList-1;

                                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);
                                    }
                            }
                    }

//FENETRES OUVERTES
                if (event.button.x>=55 && event.button.y>=560 && event.button.x<=345 && event.button.y<=593 && numFenetre==1)
                    {//ONGLET 1.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=594 && event.button.x<=345 && event.button.y<=627 && numFenetre==1)
                    {//ONGLET 1.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=628 && event.button.x<=345 && event.button.y<=661 && numFenetre==1)
                    {//ONGLET 1.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=662 && event.button.x<=345 && event.button.y<=695 && numFenetre==1)
                    {//ONGLET 1.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=696 && event.button.x<=345 && event.button.y<=729 && numFenetre==1)
                    {//ONGLET 1.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=730 && event.button.x<=345 && event.button.y<=763 && numFenetre==1)
                    {//ONGLET 1.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=764 && event.button.x<=345 && event.button.y<=797 && numFenetre==1)
                    {//ONGLET 1.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=55 && event.button.y>=798 && event.button.x<=345 && event.button.y<=831 && numFenetre==1)
                    {//ONGLET 1.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 2
                else if (event.button.x>=391 && event.button.y>=492 && event.button.x<=681 && event.button.y<=525 && numFenetre==2)//+33
                    {//ONGLET 2.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=526 && event.button.x<=681 && event.button.y<=559 && numFenetre==2)
                    {//ONGLET 2.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=560 && event.button.x<=681 && event.button.y<=593 && numFenetre==2)
                    {//ONGLET 2.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=594 && event.button.x<=681 && event.button.y<=627 && numFenetre==2)
                    {//ONGLET 2.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=628 && event.button.x<=681 && event.button.y<=661 && numFenetre==2)
                    {//ONGLET 2.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=662 && event.button.x<=681 && event.button.y<=695 && numFenetre==2)
                    {//ONGLET 2.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=696 && event.button.x<=681 && event.button.y<=729 && numFenetre==2)
                    {//ONGLET 2.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=730 && event.button.x<=681 && event.button.y<=763 && numFenetre==2)
                    {//ONGLET 2.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=764 && event.button.x<=681 && event.button.y<=797 && numFenetre==2)
                    {//ONGLET 2.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=391 && event.button.y>=798 && event.button.x<=681 && event.button.y<=831 && numFenetre==2)
                    {//ONGLET 2.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 3
                else if (event.button.x>=727 && event.button.y>=492 && event.button.x<=1017 && event.button.y<=525 && numFenetre==3)//+33
                    {//ONGLET 3.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=526 && event.button.x<=1017 && event.button.y<=559 && numFenetre==3)
                    {//ONGLET 3.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=560 && event.button.x<=1017 && event.button.y<=593 && numFenetre==3)
                    {//ONGLET 3.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=594 && event.button.x<=1017 && event.button.y<=627 && numFenetre==3)
                    {//ONGLET 3.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=628 && event.button.x<=1017 && event.button.y<=661 && numFenetre==3)
                    {//ONGLET 3.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=662 && event.button.x<=1017 && event.button.y<=695 && numFenetre==3)
                    {//ONGLET 3.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=696 && event.button.x<=1017 && event.button.y<=729 && numFenetre==3)
                    {//ONGLET 3.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=730 && event.button.x<=1017 && event.button.y<=763 && numFenetre==3)
                    {//ONGLET 3.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=764 && event.button.x<=1017 && event.button.y<=797 && numFenetre==3)
                    {//ONGLET 3.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=727 && event.button.y>=798 && event.button.x<=1017 && event.button.y<=831 && numFenetre==3)
                    {//ONGLET 3.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
//SELECTION FENETRE 4
                else if (event.button.x>=1063 && event.button.y>=492 && event.button.x<=1353 && event.button.y<=525 && numFenetre==4)//+33
                    {//ONGLET 4.1
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=22;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=526 && event.button.x<=1353 && event.button.y<=559 && numFenetre==4)
                    {//ONGLET 4.2
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=56;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=560 && event.button.x<=1353 && event.button.y<=593 && numFenetre==4)
                    {//ONGLET 4.3
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=90;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=594 && event.button.x<=1353 && event.button.y<=627 && numFenetre==4)
                    {//ONGLET 4.4
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=124;

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=628 && event.button.x<=1353 && event.button.y<=661 && numFenetre==4)
                    {//ONGLET 4.5
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=158;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=662 && event.button.x<=1353 && event.button.y<=695 && numFenetre==4)
                    {//ONGLET 4.6
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=192;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=696 && event.button.x<=1353 && event.button.y<=729 && numFenetre==4)
                    {//ONGLET 4.7
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=226;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=730 && event.button.x<=1353 && event.button.y<=763 && numFenetre==4)
                    {//ONGLET 4.8
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=260;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=764 && event.button.x<=1353 && event.button.y<=797 && numFenetre==4)
                    {//ONGLET 4.9
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=294;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        SDL_BlitSurface(fenetreSelect,NULL,fenetre,&positionFenetreSelect);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);

                        SDL_Flip(fenetre);
                        SDL_Flip(ecran);
                    }
                else if (event.button.x>=1063 && event.button.y>=798 && event.button.x<=1353 && event.button.y<=831 && numFenetre==4)
                    {//ONGLET 4.10
                        positionFenetreSelect.x=53;
                        positionFenetreSelect.y=328;//+34

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
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

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);


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

                        affListeCombat (tabObjet, deplaList ,listType,fenetreListe, fenetre, ecran, texte,positionFenetre, positionFenetreListe, postexte, skills_data, police, noire);
                        affFenetre (Refresh0,fenetreListe,fenetre,ecran,curseur,positionCurseur,positionFenetre,positionFenetreListe, decoupeF,deroulement);


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


                        break;



                }
                SDL_Flip(ecran);

    }

//Fin systeme
   SDL_FreeSurface(ecran);
   SDL_FreeSurface(Refresh0.interface);
   SDL_FreeSurface(fenetre);
   SDL_FreeSurface(texte);
}
