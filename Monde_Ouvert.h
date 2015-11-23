#ifndef MONDE_OUVERT_H_INCLUDED
#define MONDE_OUVERT_H_INCLUDED

void wait_clic(void);

int parler(int debut, int fin, char texte[99][999], SDL_Surface *ecran, int texte_rang[20], int texte_longueur[20]);


void succes(void);

SDL_Surface *Load_Map(int map_id[2], int *Carte[15][20]);
SDL_Surface *load_sprite(int map_id[2], int Sprite_id);
SDL_Rect load_decoupe(int map_id[2], int Sprite_id);
SDL_Rect load_pos(int map_id[2], int Sprite_id, int *Carte [15][20]);


void Action(int *map_id, int pos_perso_x, int pos_perso_y, SDL_Rect Pos_1, SDL_Rect Decoupe_1, SDL_Rect decoupePerso,int *Carte[15][20],SDL_Surface *ecran,sQueteconditions *Quete_cond);







void transition(SDL_Surface *ecran);

int Monde_Ouvert(SDL_Surface *ecran);



#endif // MONDE_OUVERT_H_INCLUDED
