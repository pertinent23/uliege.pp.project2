#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stegano.h"

/**
 * @brief 
 * cette fonction est utilisé pour compter le nombre
 * de charactère dans un fichier
 * 
 * @param fichier 
 * @return int 
*/
static int count_file_character(FILE *fichier)
{
    fseek(fichier, 0, SEEK_SET);
    int counter = 0;
    char character;

    while (fscanf(fichier, "%c", &character) == 1)
        counter++;
    
    fseek(fichier, 0, SEEK_SET);
    return counter;  
}

int read_message(char **message, char *filename)
{
    assert(filename != NULL);

    FILE *fichier = fopen(filename, "r");
    int nb_characteres, i;

    if (fichier == NULL)
        return -1;
    
    nb_characteres = count_file_character(fichier);
    *message = (char *) malloc(sizeof(char) * (nb_characteres+1));

    if (*message == NULL)
        return -2;

    i = 0;
    while (i<nb_characteres && fscanf(fichier, "%c", &(*message)[i]) == 1)
        i++;
    
    fclose(fichier);
    return 0;
}

int write_message(char *message, char *filename)
{
    FILE *fichier;

    fichier = fopen(filename, "w");

    if (fichier == NULL)
        return -1;

    fprintf(fichier, "%s", message);
    fclose(fichier);
    return 0;
}

int encode_stegano(PNM *image, int nb_bit, char *message)
{
    assert(image != NULL && message != NULL && nb_bit > 0);
    /**
     * @brief 
     * - le nombre de pixels nécessaires est égal au nombre d'octects nécessaires divisé fois 8
     *   divisé par le nombre de bit par pixel
     * - le nombre d'octects nécessaires est égal à 4 (nécessaire pour stocker le nombre de caractères du message)
     *  + le nombre de charactères du message
    */
    int length = strlen(message);
    int nb_pixel_necessaire = (4 + length)*8/nb_bit;

    if (image_nb_colones(image)*image_nb_lignes(image)<nb_pixel_necessaire)
        return -1;
    
    int i = 0, j, k=0, result;
    int size = 32, level=0;
    unsigned int tmp = length;

    while (i < image_nb_lignes(image))
    {
        j = 0;

        while (j < image_nb_colones(image))
        {
            if (level < size)
            {
                result = get_pixel(image, i,  j);
                result &= (unsigned int) (~0) << nb_bit;
                result |= (tmp<<level) >> (32-nb_bit);
                mettre_pixel_ajour(image, i, j, result);
            }
            

            level += nb_bit;
            j++;

            if (k<length && level >= size)
            {
                //8 le nombre de bit d'un charactère
                level = size - 8;
                tmp = message[k++];
            }
        }
        
        i++;
    }
    

    return 0;
}

int decode_stegano(PNM *image, int nb_bit, char **message)
{
    assert(image != NULL && nb_bit > 0);

    int nb_characteres = 0, i = 0, j, k = 0;
    int size = 32, level = 0;
    unsigned int temp = 0, result;

    while (i < image_nb_lignes(image))
    {
        j = 0;

        while (j < image_nb_colones(image))
        {
            result = get_pixel(image, i, j);
            result <<= size - nb_bit;
            temp |= result >> level;
            level += nb_bit;

            if (level == size) 
            {
                if (!nb_characteres)
                {
                    nb_characteres = temp;

                    if (!nb_characteres)
                        return -2;

                    *message = (char *) malloc(sizeof(char) * (nb_characteres+1));

                    if(*message == NULL)
                        return -1;
                }
                else if (k<nb_characteres)
                {
                    (*message)[k++] = (char) temp;
                    if (k==nb_characteres)
                    {
                        (*message)[k] = '\0';
                        return 0;
                    }
                }

                //8 le nombre de bit d'un charactère
                temp = 0;
                level = size - 8;
            }

            j++;
        }
        
        i++;
    }

    return 0;
}