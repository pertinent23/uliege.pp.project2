#ifndef __STEGANO__
#define __STEGANO__

#include "pnm/pnm.h"

/**
 * @brief 
 * cette fonction va lire le message à encoder dans le fichier
 * elle retourne:
 * -1 dans le cas où elle ne peut acceder au fichier
 * -2 dans le cas d'une erreur d'allocation mémoire
 *  0 le cas échéant
 * 
 * @param message 
 * @param filename 
 * @return int 
*/
int read_message(char **message, char *filename);

/**
 * @brief 
 * cette fonction va écrire dans un fichier et retourne:
 * -1 dans le cas d'un fichier invalide
 *  0 le cas échéant
 * 
 * @param message 
 * @param filename 
 * @return int 
*/
int write_message(char *message, char *filename);

/**
 * @brief 
 * cette fonction va encoder un message dans une image pgm
 * elle retourne:
 * -1 dans le cas ou le message est trop grand pour l'image
 *  0 le cas échéant
 * 
 * @param image 
 * @param nb_bit 
 * @param message 
 * @return int 
*/
int encode_stegano(PNM *image, int nb_bit, char *message);

/**
 * @brief 
 * cette fonction va decoder un message dans un fichier pgm
 * elle retourne:
 * -1 dans le cas d'une erreur d'allocation mémoire
 * -2 dans le cas où aucun message n'est trouvé
 *  0 le cas échéant
 * 
 * @param image 
 * @param nb_bit 
 * @param message 
 * @return int 
*/
int decode_stegano(PNM *image, int nb_bit, char **message);

#endif // !1