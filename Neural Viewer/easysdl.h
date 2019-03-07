#ifndef EASYSDL_H_INCLUDED
#define EASYSDL_H_INCLUDED

enum {RIEN,TOUCHE_ENFONCEE,TOUCHE_RELACHEE,SOURIS_MOUVEMENT,SOURIS_BOUTON_DROITE_ENFONCE,SOURIS_BOUTON_GAUCHE_ENFONCE,SOURIS_BOUTON_DROITE_RELACHE,SOURIS_BOUTON_GAUCHE_RELACHE,EXIT};

//////////////////////// Fonction de graphique //////////////////////////////////

// Ferme les extensions et la SDL
void destruction_fenetre();

//Initialise SDL ses extensions et crée une fenetre
int creation_fenetre(char* nom,unsigned int x, unsigned int y);

// Place un point de la couleur donnée
int trace_point(unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int trace_rectangle_plein(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace le contour d'un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int trace_rectangle(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu);

int trace_image(char* nom,unsigned int x,unsigned int y);

// trace un segment de couleur donné
int trace_segment( int x,int y,int x2, int y2,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace un triangle de couleur et de sommets donnés
int trace_triangle_plein(int x1,int y1,int x2,int y2,int x3,int y3,unsigned char rouge,unsigned char vert,unsigned char bleu);

// Trace un disque plein centre et rayon
int trace_disque(int x,int y,unsigned int rayon,unsigned char rouge,unsigned char vert,unsigned char bleu);

// Mise à jour graphique
void mise_a_jour();


//////////////////////// Fonction de texte //////////////////////////////////

// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int trace_texte(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_shaded(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf);

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_blended(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu);

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_shaded_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf);


//////////////////////////////// Fonction de traitement sur l'image ////////////////////////////


 //Sauvegarde l'ecran
int sauvegarde_ecran();

// Récupére la couleur d'un pixel de la sauvegarde
int recupere_pixel(unsigned x,unsigned y,unsigned char *rouge,unsigned char *vert,unsigned char *bleu);

// Restore l'ecran sauvegardé préalablement
int restoration_ecran();

// Recupére les dimensions de l'image
void recupere_dimension(int *x,int* y);

//////////////////////////////// Fonction musicale ////////////////////////////
// Charge le son "nom" et le place à la position donnee
void charge_son(int position,char* nom);

// joue le son un nombre nb de fois.
void joue_son(int position,int nb);

// Joue de la musique un certain nombre de fois.
int musique_on(char* nom,int repetition);

// fin de la musique
void musique_off();

// Verifie musique verifie si la musique joue 1 (0 sinon)
int verifie_musique();

////////////////////////////// Fonction d evenement //////////////////////////

// Donne le type d'un evenement
int recupere_evenement();

// Donne le type d'un evenement avec une limite de temps
int recupere_evenement_temps_limite(int temps);

// Met le type de l'evenement dans resultat et retourn 1 si il y a une action (meme non reconnue)
int recupere_evenement_continu(int* resultat);

//donne la position de la souris en x
int souris_x();

//donne la position de la souris en y
int souris_y();

// Donne la touche appuyée
int touche();

// Attendre un certain temps
void attendre(unsigned int temps);

//Attendre temps qu'une touche ou exit n'est pas enfoncée
int attendre_touche();

//Attendre temps qu'une touche ou un click ou exit n'est pas enfoncée si Exit alors retourn 0;
int attendre_action();

// Vide le buffer evenement
void vide_buffer();

#endif // EASYSDL_H_INCLUDED
