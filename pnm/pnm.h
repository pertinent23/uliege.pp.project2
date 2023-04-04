/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: HEUBA BATOMEN Franck Duval S227629
 * @date: 07/03/2023
 * @projet: INFO0030 Projet 1
*/

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

#define MAXIMUM_POUR_COULEUR 65536
#define MAXIMUN_POUR_PIXEL 255

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;


/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * @brief 
 * Cette fonction permet de dédruire 
 * un objet crée
 * 
 * @param image 
*/
void detruit_pnm(struct PNM_t *image);

/**
 * @brief 
 * 
 * @param image 
 * @return int 
*/
int image_nb_colones(struct PNM_t *image);

/**
 * @brief 
 * 
 * @param image 
 * @return int 
*/
int image_nb_lignes(struct PNM_t *image);

/**
 * @brief 
 * 
 * @param image 
 * @return int 
*/
int est_pgm(struct PNM_t *image);

/**
 * @brief Get the pixel object
 * retourne -1 si i n'appartient par à la matrice
 * retourne -2 si j n'appartient par à la matrice
 * 
 * @param image 
 * @param i 
 * @param j 
 * @return int 
*/
int get_pixel(struct PNM_t *image, int i, int j);

/**
 * @brief 
 * retourne -1 si i n'appartient par à la matrice
 * retourne -2 si j n'appartient par à la matrice
 * 
 * @param image 
 * @param i 
 * @param j 
 * @param value 
 * @return int
*/
int mettre_pixel_ajour(struct PNM_t *image, int i, int j, int value);


#endif // __PNM__

