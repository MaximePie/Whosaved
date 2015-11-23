#ifndef ACTIONS_COMBAT_H_INCLUDED
#define ACTIONS_COMBAT_H_INCLUDED
int Mort_Chck(sJoueur *Perso, sEnnemi *Monstre, sStatiques Refresh0,sMESS_ITEMS *skills_data);

int Attack_monstre(sEnnemi *Monstre,int Vie_Perdue, int IDMonstre,sStatiques * Refresh0, sMESS_ITEMS *Skill_Monstre_data,SDL_Color noire, SDL_Rect pos,TTF_Font *police);
int SKILL(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, int tabObjet,int Vie_Perdue, sStatiques *Refresh0);

void Attaque_Ennemi(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, sStatiques *Refresh0,int tabObjet[10], char Pv_Max_P[3],char Pv_P[3], int IDMonstre, sMESS_ITEMS *Skill_Monstre_data);
void Attaque_Perso(sJoueur *Perso, sEnnemi *Monstre, sMESS_ITEMS *skills_data, sStatiques *Refresh0, int tabObjet);

#endif // ACTIONS_COMBAT_H_INCLUDED

