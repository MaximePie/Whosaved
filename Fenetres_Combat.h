#ifndef FENETRES_COMBAT_H_INCLUDED
#define FENETRES_COMBAT_H_INCLUDED

void Refresh(sStatiques Refresh);

void closeFenetre(SDL_Surface *interface,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Rect position, SDL_Rect positionFenetre, SDL_Rect decoupeF,int deroulement,sStatiques Refresh0);
void affFenetre(sStatiques Refresh0,SDL_Surface *fenetreListe,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Surface *curseur,SDL_Rect positionCurseur, SDL_Rect positionFenetre, SDL_Rect positionFenetreListe, SDL_Rect decoupeF,int deroulement);
int affListeCombat(int tabObjet[10], int deplaList, int listType,SDL_Surface *fenetreListe,SDL_Surface *fenetre,SDL_Surface *ecran,SDL_Surface *texte,SDL_Rect positionFenetre,SDL_Rect positionFenetreListe, SDL_Rect postexte,sMESS_ITEMS *items_data,TTF_Font *police,SDL_Color noire);


int Analyse_Clic(SDL_Event *event, int numFenetre);

#endif // FENETRES_COMBAT_H_INCLUDED
