#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "stegano.h"
#include "pnm/pnm.h"

static int gestionnaire(int argc, char *argv[], char *optstring, unsigned int *n,  char **p, char **s, char **o)
{
    int opt;
    void *tmp;
    unsigned int is_n = 0, is_p = 0, is_s = 0, is_o = 0;
    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
            case 'n':
                *n = atoi(optarg);
                is_n = 1;
                break;
            
            case 'p':
                tmp = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));

                if (tmp != NULL) 
                {
                    *p = (char *) tmp;
                    strcpy(*p, optarg);
                    is_p = 1;
                }
                else 
                    printf("\n>> Erreur lors de l'allocation mémoire pour l'option: %c", optopt);

                break;
            
            case 's':
                tmp = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));

                if (tmp != NULL) 
                {
                    *s = (char *) tmp;
                    strcpy(*s, optarg);
                    is_s = 1;
                }
                else 
                    printf("\n>> Erreur lors de l'allocation mémoire pour l'option: %c", optopt);

                break;
            
            case 'o':
                tmp = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));

                if (tmp != NULL) 
                {
                    *o = (char *) tmp;
                    strcpy(*o, optarg);
                    is_o = 1;
                }
                else 
                    printf("\n>> Erreur lors de l'allocation mémoire pour l'option: %c", optopt);

                break;
        
            default:
                break;
            
            case ':':
                printf("\n>> Valeur manquante pour l'option: %c", optopt);
                break;
            
            case '?':
                printf("\n>> Paramètre inconnu");
                break;
        }
    }

    if (is_n && is_p && is_o && !is_s)
        return 1;

    if (is_n + is_o + is_p + is_s < 4)
    {
        if(!is_n) 
            printf("\n>> Le nombre de bit à utiliser manque: -n");

        if(!is_p)
            printf("\n>> Le fichier pgm à utiliser manque: -p");
        else
            free(*p);

        if(!is_s) 
            printf("\n>> Le fichier texte à utiliser manque: -s");
        else
            free(*s);

        if(!is_o) 
            printf("\n>> Le fichier de sortie manque: -o");
        else
            free(*o);
        
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *optstring = ":n:p:s:o:";
    char *p, *s, *o;
    unsigned int n;
    int type;

    printf("\n\n---------------------------------------------------------");
    printf("\n>> Debut du traitement...");

    if ((type = gestionnaire(argc, argv, optstring, &n, &p, &s, &o)) >= 0) 
    {
        PNM *image;
        char *message;

        if(n!=1 && n!=2 && n!=4)
            printf("\n>> L'entrée -n est invalide: %u", n);
        
        switch (load_pnm(&image, p))
        {
            case -1:
                printf("\n>> Nom du fichier erroné.");
                break;
            
            case -2:
                printf("\n>> Erreur lors de l'allocation mémoire de l'image.");
                break;

            default:

                if (type) 
                {
                    switch (decode_stegano(image, n, &message))
                    {
                        case -1:
                            printf("\n>> Erreur lors de l'allocation mémoire de du fichier: %s", p);
                            break;
                        
                        case -2:
                            printf("\n>> Aucun message n'a été trouvé");
                            break;

                        default:

                            switch (write_message(message, o))
                            {
                                case -1:
                                    printf("\n>> Erreur lors de l'ouverture du fichier: %s", o);
                                    break;

                                default:
                                    printf("\n>> Le message caché a été enregistré dans: %s", o);
                                    break;
                            }

                            free(message);
                            break;
                    }
                }
                else
                {
                    switch (read_message(&message, s))
                    {
                        case -1:
                            printf("\n>> Nom du fichier erroné: %s", s);
                            break;

                        case -2:
                            printf("\n>> Erreur lors de l'allocation mémoire de du fichier: %s", s);
                            break;

                        default:

                            switch (encode_stegano(image, n, message))
                            {
                                case -1:
                                    printf("\n>> Le message est trop grand pour l'image: %s", message);
                                    break;

                                default:

                                    switch (write_pnm(image, o))
                                    {
                                        case -1:
                                            printf("\n>> Le nom du fichier en sortie est malformé: %s", o);
                                            break;

                                        case -2:
                                            printf("\n>> L'image n'a pas pu ếtre sauvegardé.");
                                            break;

                                        default:
                                            printf("\n>> Image `%s` parfaitement sauvergardé comme `%s`.", p, o);
                                            break;
                                    }

                                    break;
                            }

                            free(message);
                            break;
                    }
                }

                detruit_pnm(image);
                break;
        }

        free(p);
        free(o);
        
        if (!type)
            free(s);
    }

    printf("\n>> Fin du traitement...");
    printf("\n---------------------------------------------------------\n\n");

    return 0;
}