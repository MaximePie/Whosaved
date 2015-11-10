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

#include "LV_UP.h"

int Mort_Chck(sJoueur *Perso, sEnnemi *Monstre, sStatiques Refresh0,sMESS_ITEMS *skills_data)
{
    char Texte[128];
    SDL_Rect postexte = {380,20};
    SDL_Color noire = {0,0,0};
    SDL_Surface *texte = NULL;
    TTF_Font *police = TTF_OpenFont("carolingia.ttf" ,17);

        //SI LE MONSTRE EST MORT
                                if (Monstre->pv<=0)
                                {
                                Refresh0.decoupeVE.w=1;
                                Refresh0.decoupeE.x=0;

                                Perso->xp+=Monstre->xp;
                                int Xp_reste = Perso->xp_pallier-Perso->xp;
                                int  Xp_reste_aff=Xp_reste;
                                if(0>Xp_reste_aff)
                                    Xp_reste_aff=0;



                                SDL_Delay(500);

                                Refresh(Refresh0);

                                sprintf(Texte,"%s Est Vaincu !",Monstre->name);
                                texte=TTF_RenderText_Blended(police,Texte,noire);
                                SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                SDL_Flip(Refresh0.ecran);
                                SDL_Delay(1000);
                                Refresh(Refresh0);



                                sprintf(Texte,"%s Gagne %d XP et %d Gold !",Perso->name, Monstre->xp, Monstre->gold);
                                texte=TTF_RenderText_Blended(police,Texte,noire);
                                SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                SDL_Flip(Refresh0.ecran);

                                SDL_Delay(1000);
                                Refresh(Refresh0);

                                sprintf(Texte,"Encore %d XP pour le niveau suivant ! ",Xp_reste_aff);
                                texte=TTF_RenderText_Blended(police,Texte,noire);
                                SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);

                                SDL_Flip(Refresh0.ecran);
                                SDL_Delay(1000);
                                Refresh(Refresh0);



                      //SI PASSAGE DE NIVEAU :
                      LV_UP(Perso);
                                if(0>=Xp_reste)
                                {
                                    Perso->xp=0-Xp_reste;
                                    int attaque=Perso->force*0.3+1;
                                    int vie=Perso->pv_max*0.2;
                                    int defense=Perso->defense*0.3+1;

                                    Perso->niveau++;
                                    Perso->force+=attaque;
                                    Perso->defense+=defense;
                                    Perso->pv+=vie;
                                    Perso->pv_max+=vie;
                                    Perso->xp-=Perso->xp_pallier;
                                    Perso->xp_pallier*=1.5;

                                    Xp_reste=0;


                                    Refresh(Refresh0);
                                    sprintf(Texte,"Level up !");
                                    texte = TTF_RenderText_Blended(police,Texte,noire);
                                    SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                    SDL_Flip(Refresh0.ecran);

                                    postexte.y += 40;

                                    sprintf(Texte,"Niveau : %d",Perso->niveau);
                                    texte=TTF_RenderText_Blended(police,Texte,noire);
                                    SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                    postexte.y+=40;

                                    sprintf(Texte,"Force + %d",attaque);
                                    texte=TTF_RenderText_Blended(police,Texte,noire);
                                    SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                    postexte.y+=40;

                                    sprintf(Texte,"Defense + %d",defense);
                                    texte=TTF_RenderText_Blended(police,Texte,noire);
                                    SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                    postexte.y+=40;

                                    sprintf(Texte,"PV Max + %d",vie);



                                    texte=TTF_RenderText_Blended(police,Texte,noire);
                                    SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                    postexte.y+=40;




                                    postexte.y-=200;
                                    SDL_Flip(Refresh0.ecran);

                                    SDL_Delay(3000);
                                    Refresh(Refresh0);


                                    switch (Perso->niveau)
                                    {
                                        case 2: //Débloque coup d'assaut
                                        Refresh(Refresh0);
                                        sprintf(Texte,"Nouvelle compétence : %s",skills_data->data[2].name);
                                        texte=TTF_RenderText_Blended(police,Texte,noire);
                                        SDL_BlitSurface(texte,NULL,Refresh0.ecran,&postexte);
                                        SDL_Flip(Refresh0.ecran);
                                        skills_data->data[2].possede=1;
                                        SDL_Delay(1500);
                                        break;
                                    }
                                }
                        ///////////////////////////////////
                                    return 1;

                                }
return 0;

}


int Attack_monstre(sEnnemi *Monstre,int Vie_Perdue, int IDMonstre,sStatiques * Refresh0, sMESS_ITEMS *Skill_Monstre_data, SDL_Color noire, SDL_Rect pos, TTF_Font *police)
{


    char Texte[128] = "";

    SDL_Surface *texte = NULL;

    int attaque_type = 0, attaque = 0;

    switch(IDMonstre)
    {
        case 1:

        srand(time(NULL));
        attaque = (rand() % 6) + 1;

        if(attaque != 1)
            return Vie_Perdue;
            attaque_type = 1;
            switch(attaque_type)
            {
                case 1:
                Vie_Perdue+= Skill_Monstre_data->data[0].force;


                sprintf(Texte,"%s utilise %s !",Monstre->name,Skill_Monstre_data->data[0].name);


                                Refresh(*Refresh0);




                                noire.r=0;
                                noire.g=0;
                                texte = TTF_RenderText_Blended(police,Texte,noire);

                                pos.x=420;
                                pos.y=35;
                                SDL_BlitSurface(texte,NULL,Refresh0->ecran,&pos);
                                SDL_Flip(Refresh0->ecran);

                                SDL_Delay(1000);

                break;
            }
        break;


        case 2:

        srand(time(NULL));
        attaque = (rand() % 6) + 1;

        if(attaque != 1)
            return Vie_Perdue;

            attaque_type = 1;

            switch(attaque_type)
            {
                case 1:
                Vie_Perdue+= Skill_Monstre_data->data[0].force;

                sprintf(Texte,"%s utilise %s !",Monstre->name,Skill_Monstre_data->data[0].name);


                        Refresh(*Refresh0);




                        noire.r=0;
                        noire.g=0;
                        texte = TTF_RenderText_Blended(police,Texte,noire);

                        pos.x=420;
                        pos.y=35;
                        SDL_BlitSurface(texte,NULL,Refresh0->ecran,&pos);
                        SDL_Flip(Refresh0->ecran);

                        SDL_Delay(1000);


                break;
            }
        break;
    }

  return Vie_Perdue;
}

void Attaque_Ennemi(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, sStatiques *Refresh0,int tabObjet[10],char *Pv_Max_P[3],char * Pv_P[3], int IDMonstre, sMESS_ITEMS *Skill_Monstre_data)
{
    int i = 0;
    SDL_Rect postexte = {425,35};
    char Texte[128];
    SDL_Color noire = {0,0,0};
    SDL_Surface *texte = NULL;
    TTF_Font *police = TTF_OpenFont("carolingia.ttf" ,15);

                            SDL_Delay(500);
                            Refresh0->decoupeE.x=285;

                            sprintf(Texte,"%s attaque !",Monstre->name);

                              Refresh(*Refresh0);


                                noire.r=0;
                                noire.g=0;
                                texte = TTF_RenderText_Blended(police,Texte,noire);
                                postexte.x=420;
                                postexte.y=35;
                                SDL_BlitSurface(texte,NULL,Refresh0->ecran,&postexte);
                                SDL_Flip(Refresh0->ecran);

                                SDL_Delay(500);

                           int  Vie_Perdue=Monstre->force-Perso->defense;



                           Vie_Perdue = Attack_monstre(Monstre, Vie_Perdue, IDMonstre, Refresh0, Skill_Monstre_data, noire, postexte, police);

                             if (Vie_Perdue < 0)
                            Vie_Perdue = 0;

                                Refresh(*Refresh0);

                                sprintf(Texte,"%s Perd %d PV ! ",Perso->name,Vie_Perdue);


                                noire.r=0;
                                noire.g=0;
                                noire.b=0;
                                texte = TTF_RenderText_Blended(police,Texte,noire);
                                postexte.x=420;
                                postexte.y=35;
                                SDL_BlitSurface(texte,NULL,Refresh0->ecran,&postexte);
                                SDL_Flip(Refresh0->ecran);
                                SDL_Delay(500);


                           int  Diminution = 324/Perso->pv_max*Vie_Perdue;
                           int  Vie_Actuelle_Decoupe = Refresh0->decoupeVP.w;

                                Perso->pv-=Vie_Perdue;
                                police = TTF_OpenFont("carolingia.ttf" ,24);

                                sprintf(Pv_P,"%d",Perso->pv);



                                Refresh0->Pv_Perso=TTF_RenderText_Blended(police,Pv_P,noire);
                                police = TTF_OpenFont("carolingia.ttf" ,15);
                                noire.r = 135;
                                noire.g = 65;



                                for(i=Vie_Actuelle_Decoupe;Vie_Actuelle_Decoupe-Diminution<=i;i-=3)
                                {

                                    Refresh0->decoupeVP.w=i;

                                    Refresh(*Refresh0);


                                }


                                Refresh0->decoupeVP.w=Perso->pv*(324/Perso->pv_max);

                                Refresh0->decoupeE.x=153;


                                Refresh(*Refresh0);




}


int SKILL(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, int tabObjet,int Vie_Perdue, sStatiques *Refresh0)
{
    SDL_Rect postexte = {425,35};
    char Texte[128];
    SDL_Color noire = {0,0,0};
    SDL_Surface *texte = NULL;
    TTF_Font *police = TTF_OpenFont("carolingia.ttf" ,15);

    int Diminution = 0 ;

    switch(tabObjet)
    {
        case 0:
        Vie_Perdue = Perso->force - Monstre->defense;

        break;

            case 1: //Si colère meurtrière

            break;

            case 2: //Si Coup d'assaut !
            Refresh(*Refresh0);

            sprintf(Texte,"%s utilise %s ! ",Perso->name, skills_data->data[2].name);
            texte = TTF_RenderText_Blended(police,Texte,noire);
            SDL_BlitSurface(texte,NULL,Refresh0->ecran,&postexte);
            SDL_Flip(Refresh0->ecran);
            SDL_Delay(1000);

            Vie_Perdue = Perso->force - Monstre->defense + skills_data->data[2].force;

            Perso->mana -= skills_data->data[2].intelligence;



            break;
    }

    if (Vie_Perdue < 0)
        Vie_Perdue = 0;




    return Vie_Perdue;
}


void Attaque_Perso(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, sStatiques *Refresh0,int tabObjet)
{
    int i = 0;
    SDL_Rect postexte = {425,35};
    char Texte[128];
    SDL_Color noire = {0,0,0};
    SDL_Surface *texte = NULL;
    TTF_Font *police = TTF_OpenFont("carolingia.ttf" ,15);

    int Vie_Perdue = 0;

    Refresh(*Refresh0);


                        sprintf(Texte,"%s utilise %s !",Perso->name,skills_data->data[tabObjet].name);
                        //Diminution = 324/Perso->mana_max*skills_data->data[2].intelligence;
                        Refresh0->decoupeMP.w -= 315/Perso->mana_max*skills_data->data[tabObjet].intelligence;

                        texte = TTF_RenderText_Blended(police,Texte,noire);
                        SDL_BlitSurface(texte,NULL,Refresh0->ecran,&postexte);
                        SDL_Flip(Refresh0->ecran);

                        SDL_Delay(750);

                        Refresh0->decoupeE.x=0;

                        Vie_Perdue=SKILL(Perso,Monstre,skills_data,tabObjet, Vie_Perdue, Refresh0);


                        Refresh(*Refresh0);

                        sprintf(Texte,"%s Perd %d PV ! ",Monstre->name,Vie_Perdue);
                            texte = TTF_RenderText_Blended(police,Texte,noire);
                            SDL_BlitSurface(texte,NULL,Refresh0->ecran,&postexte);
                            SDL_Flip(Refresh0->ecran);

                            SDL_Delay(750);


                                if (Monstre->pv-Vie_Perdue<=0)
                                    Vie_Perdue=Monstre->pv;
                               int Diminution = 90/Monstre->pv_max*Vie_Perdue;
                                int Vie_Actuelle_Decoupe = Refresh0->decoupeVE.w;

                                for(i=Vie_Actuelle_Decoupe;Vie_Actuelle_Decoupe-Diminution<=i;i-=6)
                                {
                                    Refresh0->decoupeVE.w=i;
                                    SDL_Delay(50);
                                    Refresh(*Refresh0);
                                }



                                Monstre->pv-=Vie_Perdue;

                                Refresh0->decoupeVE.w=Monstre->pv*(90/Monstre->pv_max);

                                Refresh0->decoupeE.x=153;

                                Refresh(*Refresh0);

}
