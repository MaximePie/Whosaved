//Inclusion des bibliothèques
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
#include "Combat.h"
#include "Monde_Ouvert.h"
#include "Ecran_Titre.h"

////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{   SDL_Surface *ecran=SDL_SetVideoMode(LARGEUR_ECRAN,HAUTEUR_ECRAN,32,SDL_HWSURFACE);
    TTF_Init();
    SDL_Rect pos = {0,0};

    Afficher_Menu(ecran);

    Monde_Ouvert(ecran);

    TTF_Quit();

 return EXIT_SUCCESS;

}
