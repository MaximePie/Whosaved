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

void Refresh2(sStatiques Refresh)
{
    SDL_BlitSurface(Refresh.fond,NULL,Refresh.ecran,&Refresh.position);
    SDL_BlitSurface(Refresh.Perso_Image,&Refresh.decoupeP,Refresh.ecran,&Refresh.position_Perso);
    SDL_BlitSurface(Refresh.Monstre_Image,&Refresh.decoupeE,Refresh.ecran,&Refresh.position_Monstre);
    SDL_BlitSurface(Refresh.interface,NULL,Refresh.ecran,&Refresh.position);

    SDL_BlitSurface(Refresh.barreEnnemi,&Refresh.decoupeVE,Refresh.ecran,&Refresh.pos_Barre_vie_E);
    SDL_BlitSurface(Refresh.barreVie,&Refresh.decoupeVP,Refresh.ecran,&Refresh.pos_Barre_de_vie_P);
    SDL_BlitSurface(Refresh.barreMana,&Refresh.decoupeMP,Refresh.ecran,&Refresh.pos_Barre_Mana);

    SDL_BlitSurface(Refresh.Niveau_Perso,NULL,Refresh.ecran,&Refresh.posNiveau);

    SDL_Flip(Refresh.ecran);
}
