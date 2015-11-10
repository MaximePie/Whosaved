//Inclusion des biblioth�ques
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

#include "Interface_Principale.h"

#include "Load_Items.h"
#include "Combat.h"

#include "cartes.h"
////////////////////////////////////////////////////////////////////


SDL_Surface * Load_Map(int map_id[2], int *Carte[15][20])
{
    int i = 0, j = 0;

    SDL_Surface *Map=NULL;

     int Taverne_rdc [15][20] ={ //Il s'agit du tableau fourni par le logiciel de Julien, 20 de largeur par 15 de hauteur.)
{ 68, 17, 39, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,112, 18,121,122,123, 69},
{ 68, 25, 47, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,129,130,131, 69},
{ 68,  1,  1,  1,145,  1,  1,  1,  1,  1,  1,175,  1,  1,  1,  1,137,138,139, 69},
{ 68,  1,  1,  1,153,146,167,147,147,147,148,175,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,161,154,155,155,155,155,156,161,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,174, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,174, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1, 55,  1,  1,  1,  1,  1,  1,  1,  1,182, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1, 33, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1, 55, 41, 42, 43, 55,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1, 49, 50, 51, 55,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1, 55,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,132,133,134,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,140,141,142,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69}
};



    int Taverne_ss[15][20] ={
{ 68,121,122,123, 17, 18, 18, 18, 18, 18,162,163, 18, 18, 18, 18, 18, 18, 19, 69},
{ 68,129,130,131, 25, 26,109,110, 26, 26, 26, 26, 62, 63, 26, 26, 26, 26, 27, 69},
{ 68,137,138,139,  1,  1,117,118,  1,  1,  1,  1, 70, 71,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,174,174, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,182,182, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1, 36, 37, 37, 37, 37, 37, 37, 38,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1, 44, 45, 33, 34,168, 45, 45, 46,  1,  1, 93, 94,  1,  1,  1, 69},
{ 68,  1,  1,  1, 44, 45,167, 42, 43, 45, 45, 46,  1,  1,101,102,  1,  1,  1, 69},
{ 68,  1,  1,  1, 44, 45, 41,168, 43, 45, 45, 46,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1, 44, 45, 49, 50, 51, 45, 45, 46,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1, 52, 53, 53, 53, 53, 53, 53, 54,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69},
{ 68,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 69}
};


    switch(map_id[1])
    {
        case 1:
            Map = IMG_Load("Sprites/MAP/taverne.png");

            for (i=0; i < 20; i++)
                {
                    for (j = 0; j < 15; j++)
                    {
                        Carte[j][i] = Taverne_rdc[j][i];
                    }
                }

        break;

        case 2:
            Map = IMG_Load("Sprites/MAP/taverne_ss.png");

            for (i=0; i < 20; i++)
                {
                    for (j = 0; j < 15; j++)
                    {
                        Carte[j][i] = Taverne_ss[j][i];
                    }
                }



            break;
    }


return Map;
}


SDL_Surface *load_sprite(int map_id[2], int Sprite_id)
{
    SDL_Surface *sprite = NULL;

    switch(map_id[0])
    {
    case 1:
        switch (map_id[1])
        {
            case 1:

                switch(Sprite_id)
                {

                    case 1:
                        sprite = IMG_Load("Sprites/MAP/Tavernier.bmp");
                    break;

                    default:
                        sprite = NULL;
                        break;

                }

            break;

        }
        break;
    }

return sprite;
}

SDL_Rect load_decoupe(int map_id[2], int Sprite_id)
{
    SDL_Rect decoupe;

    switch(map_id[0])
    {
    case 1:
        switch (map_id[1])
        {
            case 1:

                switch(Sprite_id)
                {

                    case 1:

                        decoupe.h = 78;
                        decoupe.w = 40;
                        decoupe.x = 9;
                        decoupe.y = 0;

                    break;

                    default:

                        break;

                }

            break;

        }
        break;
    }

return decoupe;
}


SDL_Rect load_pos(int map_id[2], int Sprite_id, int *Carte [15][20])
{
    SDL_Rect position = {0,0};

    switch(map_id[0])
    {
    case 1:
        switch (map_id[1])
        {
            case 1:

                switch(Sprite_id)
                {

                    case 1:
                        position.x = 32 * 7;
                        position.y = 32 * 1;

                        Carte[1 + 2] [7] = 2;

                    break;

                    default:

                        break;

                }

            break;

        }
        break;
    }

return position;
}


void Action(int *map_id, int pos_perso_x, int pos_perso_y, SDL_Rect Pos_1, SDL_Rect Decoupe_1, SDL_Rect decoupePerso,int *Carte[15][20],SDL_Surface *ecran)
{
    SDL_Surface *Boite_Dialogue = IMG_Load("Sprites/GENERAL/Boite de dialogue.png");

    SDL_Surface *error = IMG_Load("Sprites/error.png");


    SDL_Rect pos_boite = {0,0};
    int continuer = 1;

    char Texte[99][99][999];

    SDL_Event event;

    int position_1[2] = {Pos_1.x / 32, Pos_1.y / 32};

    SDL_Delay(50);

    SDL_BlitSurface(error,NULL,ecran,&pos_boite);
    SDL_Flip(ecran);



    switch(map_id[0])
    {
    case 1:
        switch(map_id[1])
        {

        case 1:
            if(Carte[pos_perso_y ][pos_perso_x - 1] == 2  && decoupePerso.x == 187)


                do{

                     SDL_WaitEvent(&event);
                        switch(event.type)
                        {
                            case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                                {
                                    case SDLK_z:
                                    SDL_Delay(50);
                                    continuer = 0;
                                    break;

                                    default:
                                        ;



                                }
                        }

                        SDL_BlitSurface(Boite_Dialogue,NULL,ecran,&pos_boite);
                        SDL_Flip(ecran);

                }while(continuer);

            break;

        }
    break;

    }

}



void transition(SDL_Surface *ecran)
{
    SDL_Surface *Image = IMG_Load("Sprites/MAP/transition.png");
    SDL_Rect decoupe = {0,0,640,480}, position = {0,0};
    int i = 0;

    for (i = 0; i < 640 * 6; i += 640)
    {
        decoupe.x = i;
        SDL_BlitSurface (Image, &decoupe, ecran, &position);
        SDL_Flip(ecran);
        SDL_Delay(70);
    }

}


int warp_chck(int pos_perso_x, int pos_perso_y, int *Carte[15][20], int *map_id)
{
    switch(map_id[1])
    {


    case 1:

        if (Carte[pos_perso_y+2][pos_perso_x-1]==133 || Carte[pos_perso_y+2][pos_perso_x-1]==138 )
        return 1;
    break;


    case 2:
        if (Carte[pos_perso_y+2][pos_perso_x-1]==138)
        return 1;
        break;

    }

    return 0;
}


void test(int *map_id, int pos_perso_x, int pos_perso_y, SDL_Rect Pos_1, SDL_Rect Decoupe_1, SDL_Rect decoupePerso,int *Carte[15][20],SDL_Surface *ecran)
{
    SDL_Surface *Boite_Dialogue = IMG_Load("Sprites/GENERAL/Boite de dialogue.png");

    SDL_Surface *error = IMG_Load("Sprites/error.png");


    SDL_Rect pos_boite = {0,0};
    int continuer = 1;

    //char Texte[99][99][999];

    SDL_Event event;

    int position_1[2] = {Pos_1.x / 32, Pos_1.y / 32};

    SDL_Delay(50);

    SDL_BlitSurface(error,NULL,ecran,&pos_boite);
    SDL_Flip(ecran);



}



void Warp(int *map_id,int *pos_perso_x, int *pos_perso_y)
{
    switch(map_id[1])
    {

    case 1:

        if(*pos_perso_x == 4 && *pos_perso_y == 11) //Si escalier qui descend
        {
            map_id[1]=2;
            *pos_perso_x = 3;
            *pos_perso_y = 1;
        }

    break;

    case 2:
        if(*pos_perso_x == 3 && *pos_perso_y == 0) //Si escalier pour aller au rdc
        {
            map_id[1]=1;
            *pos_perso_x = 4;
            *pos_perso_y = 10;
        }
    break;


    }


}



int pass_chck(SDL_Rect positionperso, SDL_Event event, int carte [15][20], int pos_perso_x, int pos_perso_y) //La fonction qui donne la permission de se d�placer. Supprimez les commentaires pour l'essayer.
{

    int carteID = 1;

    switch (carteID)
    {


        case 1:


            switch (event.key.keysym.sym)
            {

                default:
                    ;


                case SDLK_UP:
                    if (carte [pos_perso_y+1][pos_perso_x-1] != 1 && carte [pos_perso_y+1][pos_perso_x-1] != 138) // Pour des questions d'ajustement j'ai d� rajouter et retirer des +1/-1/+2/0 un peu partout. (Sinon le personnage pouvait marcher dans les murs, il fait 2*32 pixels de haut !)
                        return 0;
                    break;

                case SDLK_DOWN:
                    if (carte [pos_perso_y+3][pos_perso_x-1] != 1&& carte [pos_perso_y+3][pos_perso_x-1] != 133 )
                        return 0;
                    break;

                case SDLK_RIGHT:
                    if (carte [pos_perso_y+2][pos_perso_x] != 1)
                        return 0;
                    break;

                case SDLK_LEFT:
                    if (carte [pos_perso_y+2][pos_perso_x-2] != 1)
                        return 0;
                    break;


            }



        break;


    }
    return 1;
}




void Monde_Ouvert(SDL_Surface *ecran)
{
    TTF_Init();
    SDL_Surface * Texte=NULL;
    char texte [32];
    TTF_Font *police=TTF_OpenFont("carolingia.ttf",25); //C'est temporaire, c'est pour afficher les coordonn�es du personnage, ainsi que le type de case sur lequel il se trouve.
    SDL_Color Verte = {0,255,0};
    SDL_Rect position = {200,200};


    int compteur=0, randCombat=0;
    int pos_perso_x = 4, pos_perso_y = 10;
    int continuer = 1;


    int map_id[2]={1,1}; //L'identifiant de la map.

    int Carte[15][20];

    SDL_Surface *Map = Load_Map(map_id,&Carte);

    SDL_Event event;
    SDL_Rect positionpersonnage, positionMap = {0,0}, decoupePerso={9,0,40,78};



    SDL_Surface *personnage=SDL_LoadBMP("Sprites/MAP/Personnage.bmp");



    SDL_Surface *error = IMG_Load("Sprites/error.png");



    SDL_Surface *Sprite_1 = load_sprite(map_id,1), *Sprite_2 = NULL, *Sprite_3 = NULL,*Sprite_4 = NULL,*Sprite_5 = NULL,*Sprite_6 = NULL, *Sprite_7 = NULL;
    SDL_Rect Decoupe_1 = load_decoupe(map_id, 1);
    SDL_Rect Pos_1 = load_pos(map_id, 1,Carte);








    SDL_SetColorKey(personnage, SDL_SRCCOLORKEY, SDL_MapRGB(personnage->format, 0, 0, 255));    // pour d�finir la couleur invisible
    SDL_SetColorKey(Sprite_1, SDL_SRCCOLORKEY, SDL_MapRGB(Sprite_1->format, 0, 0, 255));

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));




    sJoueur Perso;
    sMESS_ITEMS skills_data = MESS_LoadItems("Skills.bin", 1);
    sMESS_ITEMS items_data = MESS_LoadItems("Inventaire1.bin",1);
    Ini_Joueur(&Perso);

positionpersonnage.x=pos_perso_x*32 -32   + 3; //On colle le personnage � sa position pos_perso multipli�s par le nombre de pixels (Ici pos_perso_x = 4 et pos_perso_y = 10 (On fait - 32 car le d�but d'un tableau commence � 0 et non � 1)
positionpersonnage.y=pos_perso_y*32 ;


SDL_BlitSurface(Map, NULL, ecran, &positionMap);
SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);

texte[0]='\0';
sprintf(texte,"%d : %d %d",Carte[pos_perso_y][pos_perso_x], pos_perso_x, pos_perso_y);
sprintf(texte,"%d : %d",Pos_1.x, Pos_1.y); //C'est le texte qu'on affiche en vert. On affiche le Y avant le X, c'est l� le d�but du probl�me. Changez le X en Y, �a marchera pas, vous verrez.
Texte = TTF_RenderText_Blended(police,texte,Verte);
SDL_BlitSurface(Texte,NULL,ecran,&position);

SDL_Flip(ecran);

    SDL_EnableKeyRepeat(20,0);            // pour que quand on garde la touche effonc�e il r�p�te l'�v�nement (j'ai mis le d�lai au minimum)

        while (continuer)               // d�but des conditions
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

                default:
                    ;

                case SDLK_a:
                InterfacePricipale(&Perso,&items_data);
                SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                SDL_BlitSurface(Map, NULL, ecran, &positionMap);
                SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                break;

                case SDLK_c:
                    test(map_id, pos_perso_x, pos_perso_y, Pos_1, Decoupe_1, decoupePerso, &Carte,ecran);
                    SDL_Delay(1000);
                    break;


                case SDLK_z:

                   // Action(map_id, pos_perso_x, pos_perso_y, Pos_1, Decoupe_1, decoupePerso, &Carte,ecran);

                    break;


        case SDLK_UP: // Fl�che haut

                decoupePerso.x=187;
                decoupePerso.w=82;


                // On envoie en param�tres la position (en pixels) le type d'event (SDLK_UP,DOWN,ETC.), et les positions en cases.
                if(!pass_chck(positionpersonnage,event,Carte,pos_perso_x,pos_perso_y) ) //On demande la permission de se d�placer. Si la fonction pass_chck renvoie 0 on annule le d�placement.
                    break;

                else
                {
                    for(compteur=0;compteur<=8;compteur++)
                    {

                        SDL_Delay(DELAI_DEPLACEMENT);

                    if (compteur==2)
                        decoupePerso.y=86;

                    if (compteur==4||compteur==8)
                        decoupePerso.y=0;

                    if (compteur==6)
                        decoupePerso.y=165;

                        positionpersonnage.y-=4;
                        SDL_BlitSurface(Map,NULL,ecran,&positionMap);
                        if(positionpersonnage.y<Pos_1.y)
                            {
                            SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                            SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                            }

                            else
                            {
                                SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                                SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                            }
                        SDL_Flip(ecran);
                    }

                    pos_perso_y--;
                    positionpersonnage.y = pos_perso_y*32;
                }


        break;

        case SDLK_DOWN: // Fl�che bas


                decoupePerso.x=9;
                decoupePerso.w=40;

                if(!pass_chck(positionpersonnage,event,Carte,pos_perso_x,pos_perso_y))
                    break;

            for(compteur=0;compteur<=8;compteur++)
                {
                    SDL_Delay(DELAI_DEPLACEMENT);

                    if (compteur==2)
                        decoupePerso.y=86;

                    if (compteur==4||compteur==8)
                        decoupePerso.y=0;

                    if (compteur==6)
                        decoupePerso.y=165;

                    positionpersonnage.y+=4;

                    SDL_BlitSurface(Map,NULL,ecran,&positionMap);
                    if(positionpersonnage.y<Pos_1.y)
                    {
                    SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                    SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                    }

                    else
                    {
                        SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                        SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                    }

                    SDL_Flip(ecran);

                }

                pos_perso_y++;
                positionpersonnage.y = pos_perso_y*32;

        break;

        case SDLK_RIGHT: // Fl�che droite

                decoupePerso.x=121;
                decoupePerso.w=48;

                if(!pass_chck(positionpersonnage,event,Carte,pos_perso_x,pos_perso_y) )
                    break;

                    for(compteur=0;compteur<=8;compteur++)
                        {

                        SDL_Delay(DELAI_DEPLACEMENT);

                    if (compteur==2)
                        decoupePerso.y=86;

                    if (compteur==4||compteur==8)
                        decoupePerso.y=0;

                    if (compteur==6)
                        decoupePerso.y=165;

                        positionpersonnage.x+=4;
                        SDL_BlitSurface(Map,NULL,ecran,&positionMap);
                        if(positionpersonnage.y<Pos_1.y)
                        {
                        SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                        SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                        }

                        else
                        {
                            SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                            SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                        }
                        SDL_Flip(ecran);
                        }

                        pos_perso_x++;
                        positionpersonnage.x = pos_perso_x*32- 32;


            break;

        case SDLK_LEFT: // Fl�che gauche

                decoupePerso.x=66;
                decoupePerso.w=45;

                if(!pass_chck(positionpersonnage,event,Carte,pos_perso_x,pos_perso_y) )
                    break;

                    for(compteur=0;compteur<=8;compteur++)
                        {

                        SDL_Delay(DELAI_DEPLACEMENT);

                    if (compteur==2)
                        decoupePerso.y=86;

                    if (compteur==4||compteur==8)
                        decoupePerso.y=0;

                    if (compteur==6)
                        decoupePerso.y=165;

                            positionpersonnage.x-=4;
                            SDL_BlitSurface(Map,NULL,ecran,&positionMap);
                            if(positionpersonnage.y<Pos_1.y)
                            {
                            SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                            SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                            }

                            else
                            {
                                SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
                                SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
                            }
                            SDL_Flip(ecran);

                        }
                        pos_perso_x--;
                        positionpersonnage.x = pos_perso_x*32- 32;
            break;

        }

       if(warp_chck(pos_perso_x,pos_perso_y,&Carte, map_id))
        {

            Warp(map_id,&pos_perso_x,&pos_perso_y);

            Map = Load_Map(map_id,&Carte);
            Sprite_1 = load_sprite(map_id,1);



            positionpersonnage.x = pos_perso_x * 32 - 32 + 3;
            positionpersonnage.y = pos_perso_y * 32;


        }

        //Al�aCombat
        if (event.key.keysym.sym == SDLK_DOWN ||event.key.keysym.sym == SDLK_UP ||event.key.keysym.sym == SDLK_RIGHT ||event.key.keysym.sym == SDLK_LEFT )
        {
            srand(time(NULL));
            randCombat = (rand() % (MAX - MIN + 1)) + MIN;

        if (randCombat==1)
            {
            transition(ecran);

            combat(&Perso,&skills_data,ecran,map_id);
            SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
            SDL_BlitSurface(Map, NULL, ecran, &positionMap);
            SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
            SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
            }
        }


}


    SDL_BlitSurface(Map, NULL, ecran, &positionMap);
    SDL_BlitSurface(ecran,NULL,ecran, &positionMap);

    if(positionpersonnage.y<Pos_1.y)
    {
    SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
    SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
    }

    else
    {
        SDL_BlitSurface(Sprite_1,&Decoupe_1,ecran,&Pos_1);
        SDL_BlitSurface(personnage, &decoupePerso, ecran, &positionpersonnage);
    }

    texte[0]='\0';
    sprintf(texte,"%d : %d       %d",Carte[pos_perso_y+2][pos_perso_x-1], pos_perso_y, pos_perso_x);
    sprintf(texte,"%d : %d       %d",Carte[pos_perso_y][pos_perso_x - 1], pos_perso_y, pos_perso_x);
    Texte = TTF_RenderText_Blended(police,texte,Verte);
    SDL_BlitSurface(Texte,NULL,ecran,&position);

    SDL_Flip(ecran);
}



TTF_Quit();
SDL_Quit();

 return EXIT_SUCCESS;

}