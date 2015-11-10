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


sMESS_ITEMS MESS_LoadItems(const char* filename, int ID)
{
    //On définit le conteur pour le chargement objet par objet plus tard
    int counter = 0;
    //On crée une nouvelle structure d'objet
    sMESS_ITEMS items_data;
    //On ouvre le fichier
    FILE* ptr_myfile=fopen(filename,"rb");
    //On charge les propriétés du header
    fread(&items_data.header.fileVersion,2,1,ptr_myfile); //Version du fichier
    fread(&items_data.header.nbrObjects,4,1,ptr_myfile); //Nombre d'objet dans la base de donnée
    fread(&items_data.header.type,11,1,ptr_myfile); //Type de fichier (toujours ITEMS_TABLE)

    //On charge chaque objet un par un
    for (counter = 0; counter < items_data.header.nbrObjects; counter++)
    {
        //Chargement de la prefixed length string
        char size = 0;
        fread(&size,1,1,ptr_myfile);
        //Si la taille du nom de l'objet dépasse la valeur maximum
        if (size > 18)
        {
            //Génére une erreur et retourne les valeurs incompletes
            printf("ERROR TAILLE");
            return items_data;
        }
        else
        {
            //Chargement de la prefixed length string
            fread(&items_data.data[counter].name,size,1,ptr_myfile);
        }
        //Chargement des stats de l'arme
        fread(&items_data.data[counter].categorie,4,1,ptr_myfile);
        fread(&items_data.data[counter].force,4,1,ptr_myfile);
        fread(&items_data.data[counter].agilite,4,1,ptr_myfile);
        fread(&items_data.data[counter].defense,4,1,ptr_myfile);
        fread(&items_data.data[counter].dexterite,4,1,ptr_myfile);
        fread(&items_data.data[counter].intelligence,4,1,ptr_myfile);
        fread(&items_data.data[counter].charisme,4,1,ptr_myfile);
        fread(&items_data.data[counter].prix,4,1,ptr_myfile);
        fread(&items_data.data[counter].pv,4,1,ptr_myfile);
        fread(&items_data.data[counter].pm,4,1,ptr_myfile);

        items_data.data[counter].possede = 1;
        items_data.data[counter].equipe = 1;

        if (ID == 1) //Si c'est le personnage, on met les trucs à 0 par défaut.
        {
        items_data.data[counter].possede = 0;
        items_data.data[counter].equipe = 0;
        }

    }
    //Fermeture du fichier
    fclose(ptr_myfile);
    return items_data;
}
