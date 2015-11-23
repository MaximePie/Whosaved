#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "Structures.h"
#include "Constantes.h"

#include "Load_Items.h"
#include "Fenetres_Combat.h"
#include "Actions_Combat.h"
#include "Monde_Ouvert.h"


void Afficher_Menu(SDL_Surface *ecran)
{
    int pos_clic=0;
    SDL_Event event;
    SDL_Surface *Fond = IMG_Load("Sprites/EcranT/Menu_fond.png");
    SDL_Rect position = {0,0};
    int continuer = 1, color = 0;

    TTF_Font *police=TTF_OpenFont("carolingia.ttf",25);


    SDL_Color Verte = {0,255,0};

    SDL_Surface *texte = NULL;
    char Texte[128];

    position.x = 120;
    position.y = 100;
    texte = TTF_RenderText_Blended(police,"Nouvelle Partie",Verte);
    SDL_BlitSurface(texte,NULL,Fond,&position);

    position.x = 180;
    position.y = 185;

    texte = TTF_RenderText_Blended(police,"Comment Jouer ?",Verte);
    SDL_BlitSurface(texte,NULL,Fond,&position);
    position.x = 250;
    position.y = 265;

    texte = TTF_RenderText_Blended(police,"A propos des créateurs ",Verte);
    SDL_BlitSurface(texte,NULL,Fond,&position);

    position.x=0;
    position.y=0;

    while (continuer)
    {

        SDL_Flip(ecran);

        SDL_WaitEvent(&event);
        switch (event.type)
        {

        default:
            ;

            case SDL_MOUSEBUTTONDOWN:
                pos_clic = Analyse_Clic(&event, -1);

                switch(pos_clic)
                {

            case 1:
                position.x = 120;
                position.y = 100;
                texte = TTF_RenderText_Blended(police,"Nouvelle Partie",Verte);
                SDL_BlitSurface(texte,NULL,ecran,&position);
                position.x=0;
                position.y=0;

                Monde_Ouvert(ecran);

                break;



                }

                break;

            case SDL_MOUSEMOTION:


            SDL_BlitSurface(Fond,NULL,ecran,&position);
            sprintf(Texte,"%d",event.motion.x);
            texte = TTF_RenderText_Blended(police,Texte,Verte);
            SDL_BlitSurface(texte,NULL,ecran,&position);
            SDL_Flip(ecran);
            position.y+=100;
            sprintf(Texte,"%d",event.motion.y);
            texte = TTF_RenderText_Blended(police,Texte,Verte);
            SDL_BlitSurface(texte,NULL,ecran,&position);
            SDL_Flip(ecran);
            position.y-=100;

            if (event.button.x>=120 && event.button.y>=105 && event.button.y<=122 && event.button.x<=290)
                color = 1;

            else
            {
                break;
            }

            break;

            case SDL_KEYDOWN:

                    switch (event.key.keysym.sym)
                    {

                    default:
                        ;

                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    }
                break;
        }

        switch (color)
        {

        case 0:
            Verte.b=0;
            Verte.g=255;
            Verte.r=0;

            position.x = 120;
            position.y = 100;
            texte = TTF_RenderText_Blended(police,"Nouvelle Partie",Verte);
            SDL_BlitSurface(texte,NULL,ecran,&position);

            position.x = 180;
            position.y = 185;

            texte = TTF_RenderText_Blended(police,"Comment Jouer ?",Verte);
            SDL_BlitSurface(texte,NULL,ecran,&position);
            position.x = 250;
            position.y = 265;

            texte = TTF_RenderText_Blended(police,"A propos des créateurs ",Verte);
            SDL_BlitSurface(texte,NULL,ecran,&position);

            position.x=0;
            position.y=0;
            break;

            case 1:


                    Verte.r=150;
                    Verte.g=0;
                    color=0;

                    position.x = 120;
                    position.y = 100;
                    texte = TTF_RenderText_Blended(police,"Nouvelle Partie",Verte);
                    SDL_BlitSurface(texte,NULL,ecran,&position);


                    Verte.b=0;
                    Verte.g=255;
                    Verte.r=0;

                    position.x = 180;
                    position.y = 185;

                    texte = TTF_RenderText_Blended(police,"Comment Jouer ?",Verte);
                    SDL_BlitSurface(texte,NULL,ecran,&position);
                    position.x = 250;
                    position.y = 265;

                    texte = TTF_RenderText_Blended(police,"A propos des créateurs ",Verte);
                    SDL_BlitSurface(texte,NULL,ecran,&position);

                    position.x=0;
                    position.y=0;

                    position.x=0;
                    position.y=0;


            break;

        }



    }

}
