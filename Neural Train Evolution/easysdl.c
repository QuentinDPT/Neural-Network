#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "easysdl.h"
#include "math.h"


// On définit ici des fonctions de haut niveau permettant de simplifier l'utilisation de la SDL
//
#define NB_MAX_IMG 100
#define NB_MAX_SON 100
// fenetre est une variable externe.
SDL_Window* fenetre=NULL;
SDL_Renderer* rendu=NULL;

SDL_Event evenement;
Mix_Music* musique=NULL;
Mix_Chunk* son[NB_MAX_SON];
SDL_Surface *sauvegarde;
SDL_Surface *surface[NB_MAX_IMG];

void destruction_son();
void initialisation_son();

// Ferme les extensions et la SDL
void destruction_fenetre()
{
    extern SDL_Window* fenetre;
    extern SDL_Renderer* rendu;
    extern SDL_Surface *sauvegarde;
    extern Mix_Music* musique;
    musique_off();
    destruction_son();
    SDL_DestroyRenderer(rendu);


    SDL_DestroyWindow(fenetre);
    SDL_FreeSurface(sauvegarde);

    rendu=NULL;
    fenetre=NULL;
    sauvegarde=NULL;
    musique=NULL;
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

//Initialise SDL ses extensions et crée une fenetre
int creation_fenetre(char* nom,unsigned int x, unsigned int y)
{
    extern SDL_Window* fenetre;
    extern SDL_Renderer* rendu;
    if(fenetre)
    {
        destruction_fenetre();
    }
    // Ouverture de le SDL et de ses extensions.
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return 0;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return 0;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
      fprintf(stderr,"Erreur d'open audio %s", Mix_GetError());
      return 0;
    }
    Mix_AllocateChannels(NB_MAX_SON);
    initialisation_son();
    fenetre=SDL_CreateWindow(nom,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,x, y ,SDL_WINDOW_SHOWN);
    rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(rendu,255,255,255,255);
    SDL_RenderClear(rendu);
    SDL_RenderPresent(rendu);
    SDL_SetRenderDrawColor(rendu,0,0,0,255);

    return 1;
}




void attendre(unsigned int temps)
{
    SDL_Delay(temps);
}

//Attendre temps qu'une touche ou exit n'est pas enfoncée si exit alors retourne 0
int attendre_touche()
{
    int evenement;
    do
    {
           evenement=recupere_evenement();

    }while(evenement!=TOUCHE_ENFONCEE&&evenement!=EXIT);
    if(evenement==EXIT)return 0;
    return 1;
}

//Attendre temps qu'une touche ou un click ou exit n'est pas enfoncée si Exit alors retourn 0;
int attendre_action()
{
    int evenement;
    do
    {
           evenement=recupere_evenement();

    }while(evenement!=TOUCHE_ENFONCEE&&evenement!=EXIT&&evenement!=SOURIS_BOUTON_DROITE_ENFONCE&&evenement!=SOURIS_BOUTON_GAUCHE_ENFONCE);
    if(evenement==EXIT)return 0;
    return 1;
}

// Place un point de la couleur donnée
int trace_point(unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    extern SDL_Renderer* rendu;
    if(!rendu)            // Si fentre ou rendu n'existe pas on arrete
        return 0;
    SDL_SetRenderDrawColor(rendu,rouge,vert,bleu,255);
    SDL_RenderDrawPoint(rendu,x,y);
    SDL_SetRenderDrawColor(rendu,0,0,0,255);  // On retourne à la couleur par défaut
    return 1;
}

// trace un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int trace_rectangle_plein(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    extern SDL_Renderer* rendu;
    SDL_Rect rectangle={x,y,base,hauteur};
    if(!rendu)            // Si fentre ou rendu n'existe pas on arrete
        return 0;
    SDL_SetRenderDrawColor(rendu,rouge,vert,bleu,255);
    SDL_RenderFillRect(rendu,&rectangle);
    SDL_SetRenderDrawColor(rendu,0,0,0,255);  // On retourne à la couleur par défaut
    return 1;
}
// trace le contour d'un rectangle de la couleur donnée (x et y sont les coordonnées du coin supérieur gauche
int trace_rectangle(unsigned int x,unsigned int y,unsigned int base,unsigned int hauteur,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    extern SDL_Renderer* rendu;
    SDL_Rect rectangle={x,y,base,hauteur};
    if(!rendu)            // Si fentre ou rendu n'existe pas on arrete
        return 0;
    SDL_SetRenderDrawColor(rendu,rouge,vert,bleu,255);
    SDL_RenderDrawRect(rendu,&rectangle);
    SDL_SetRenderDrawColor(rendu,0,0,0,255);  // On retourne à la couleur par défaut
    return 1;
}

// Trace un disque plein centre et rayon
int trace_disque(int x,int y,unsigned int rayon,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    int i;
    for(i=0;i<=rayon;i++)
    {
        trace_segment(x+i,sqrt(rayon*rayon-i*i)+y,x+i,-sqrt(rayon*rayon-i*i)+y,rouge,vert,bleu);
        trace_segment(x-i,sqrt(rayon*rayon-i*i)+y,x-i,-sqrt(rayon*rayon-i*i)+y,rouge,vert,bleu);
    }
    return 1;
}


//arrondir un double positif
int arrondir(double a)
{
    if(a-(int)a>0)
        return a;
    return a+1;
}

 //Sauvegarde l'ecran
int sauvegarde_ecran()
{
    extern SDL_Window* fenetre;
    extern SDL_Surface* sauvegarde;
    extern SDL_Renderer* rendu;
    int x,y;
    SDL_GetWindowSize(fenetre,&x,&y);
    SDL_FreeSurface(sauvegarde);
    sauvegarde = SDL_CreateRGBSurface ( 0 , x , y ,  32 ,  0x00ff0000 ,  0x0000ff00 ,  0x000000ff ,  0xff000000 );
    SDL_RenderReadPixels ( rendu , NULL , SDL_PIXELFORMAT_ARGB8888 , sauvegarde -> pixels , sauvegarde -> pitch );
    return 0;
}

// Restore l'ecran sauvegardé préalablement
int restoration_ecran()
{
    extern SDL_Surface* sauvegarde;
    extern SDL_Renderer* rendu;
    extern SDL_Window* fenetre;
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(rendu, sauvegarde);
    SDL_RenderCopy(rendu,texture,NULL,NULL);
    SDL_DestroyTexture(texture);

    return 1;
}

// Récupére la couleur d'un pixel de la sauvegarde
int recupere_pixel(unsigned x,unsigned y,unsigned char *rouge,unsigned char *vert,unsigned char *bleu)
{
    extern SDL_Surface* sauvegarde;
    int nbOctetsParPixel = sauvegarde->format->BytesPerPixel;

    Uint32 *p = (Uint32 *)((Uint8 *)sauvegarde->pixels + y * sauvegarde->pitch + x * nbOctetsParPixel);
    SDL_GetRGB(*(p),sauvegarde->format,rouge,vert,bleu);
    return 1;
}
// trace un segment de couleur donné
int trace_segment( int x1, int y1, int x2, int y2,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    extern SDL_Renderer* rendu;
    SDL_SetRenderDrawColor(rendu,rouge,vert,bleu,255);
    SDL_RenderDrawLine(rendu,x1,y1,x2,y2);
    SDL_SetRenderDrawColor(rendu,0,0,0,255);
    return 1;
}

// trace un triangle de couleur et de sommets donnés
int trace_triangle_plein(int x1,int y1,int x2,int y2,int x3,int y3,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
    if(x2<x1)
    {
        trace_triangle_plein(x2,y2,x1,y1,x3,y3,rouge,vert,bleu);
        return 0;
    }
    if(x3<x2)
    {
        trace_triangle_plein(x1,y1,x3,y3,x2,y2,rouge,vert,bleu);
        return 0;
    }
    int i;
    double coef1,coef2;
    extern SDL_Renderer* rendu;

    SDL_SetRenderDrawColor(rendu,rouge,vert,bleu,255);

    SDL_RenderDrawLine(rendu,x1,y1,x2,y2);
    SDL_RenderDrawLine(rendu,x1,y1,x3,y3);
    SDL_RenderDrawLine(rendu,x3,y3,x2,y2);
    if(x2!=x1)
    {
        coef1=((double)(y2-y1))/(x2-x1);
        coef2=((double)(y3-y1))/(x3-x1);
        for(i=1;i<x2-x1+1;i++)
        {
            SDL_RenderDrawLine(rendu,x1+i,y1+i*coef1,x1+i,y1+i*coef2);
        }
    }
    if(x3!=x2)
    {
        coef1=((double)(y3-y2))/(x3-x2);
        coef2=((double)(y3-y1))/(x3-x1);
        for(i=1;i<x3-x2+1;i++)
        {
            SDL_RenderDrawLine(rendu,x2+i,y2+i*coef1,x2+i,y1+(x2-x1+i)*coef2);
        }
    }
    SDL_SetRenderDrawColor(rendu,0,0,0,255);
    return 1;
}


// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int trace_texte(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	SDL_Color couleur={rouge,vert,bleu};
	TTF_Font *police = TTF_OpenFont(nom_police, taille);
	if (police == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Surface *surface = TTF_RenderText_Blended(police,txt, couleur);
	if (surface == NULL)
    {
        TTF_CloseFont(police);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (police == NULL)
    {
        TTF_CloseFont(police);
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


    rectangle.x=x;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(police);
	return 1;
}

// trace un texte (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	SDL_Color couleur={rouge,vert,bleu};
	TTF_Font *police = TTF_OpenFont(nom_police, taille);
	if (police == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Surface *surface = TTF_RenderText_Blended(police,txt, couleur);
	if (surface == NULL)
    {
        TTF_CloseFont(police);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (police == NULL)
    {
        TTF_CloseFont(police);
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


    rectangle.x=x-rectangle.w;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(police);
	return 1;
}

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_shaded(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	SDL_Color couleur={rouge,vert,bleu};
	SDL_Color couleur_fond={rougef,vertf,bleuf};
	TTF_Font *police = TTF_OpenFont(nom_police, taille);
	if (police == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Surface *surface = TTF_RenderText_Shaded(police,txt, couleur,couleur_fond);
	if (surface == NULL)
    {
        TTF_CloseFont(police);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (police == NULL)
    {
        TTF_CloseFont(police);
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


    rectangle.x=x;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(police);
	return 1;
}

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_shaded_droite(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu,unsigned char rougef,unsigned char vertf,unsigned char bleuf)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	SDL_Color couleur={rouge,vert,bleu};
	SDL_Color couleur_fond={rougef,vertf,bleuf};
	TTF_Font *police = TTF_OpenFont(nom_police, taille);
	if (police == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Surface *surface = TTF_RenderText_Shaded(police,txt, couleur,couleur_fond);
	if (surface == NULL)
    {
        TTF_CloseFont(police);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (police == NULL)
    {
        TTF_CloseFont(police);
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


    rectangle.x=x-rectangle.w;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(police);
	return 1;
}

// trace un texte lissé sur une couleur de fond (x et y sont les coordonnées du coin supérieur gauche
int trace_texte_blended(char* txt,char* nom_police,int taille, unsigned int x,unsigned int y,unsigned char rouge,unsigned char vert,unsigned char bleu)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	SDL_Color couleur={rouge,vert,bleu};
	TTF_Font *police = TTF_OpenFont(nom_police, taille);
	if (police == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Surface *surface = TTF_RenderText_Blended(police,txt, couleur);
	if (surface == NULL)
    {
        TTF_CloseFont(police);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (police == NULL)
    {
        TTF_CloseFont(police);
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la police\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));


    rectangle.x=x;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(police);
	return 1;
}

//charge une image
int charge_image(char *nom, int position){
    extern SDL_Surface *surface[NB_MAX_IMG] ;
    SDL_FreeSurface(surface[position%NB_MAX_IMG]) ;
    surface[position%NB_MAX_IMG] = IMG_Load(nom) ;
	if (surface[position%NB_MAX_IMG] == NULL)
    {
        fprintf(stderr, "Erreur de chargement de l'image\n");
        return 0;
    }
    return 1 ;
}

//trace une image chargée
void trace_image_charge(int pos, int x, int y){
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
	extern SDL_Surface *surface[NB_MAX_IMG] ;
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface[pos%NB_MAX_IMG]);
	if (texture == NULL)
    {
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la texture\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));

    rectangle.x=x;
    rectangle.y=y;/*
    if(h>0)
        rectangle.h = h ;
    if(w>0)
        rectangle.w = w ;*/

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	return 1;
}

// trace une image (x et y sont les coordonnées du coin supérieur gauche
int trace_image(char* nom,unsigned int x,unsigned int y)
{
	extern SDL_Renderer* rendu;
	SDL_Rect rectangle;
    SDL_Surface* surface;
    surface=IMG_Load(nom);
	if (surface == NULL)
    {
        fprintf(stderr, "Erreur de chargement de l'image\n");
        return 0;
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, surface);
	if (texture == NULL)
    {
        SDL_FreeSurface(surface);
        fprintf(stderr, "Erreur d'initialisation de la texture\n");
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL, &(rectangle.w), &(rectangle.h));

    rectangle.x=x;
    rectangle.y=y;

    SDL_RenderCopy(rendu,texture,NULL,&rectangle);
    SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	return 1;
}

// Recupére les dimensions de l'image
void recupere_dimension(int *x,int* y)
{
    extern SDL_Window* fenetre;
    SDL_GetWindowSize(fenetre,x,y);
}
// Charge le son "nom" et le place à la position donnee
void charge_son(int position,char* nom)
{
    extern Mix_Chunk* son[NB_MAX_SON];
    Mix_FreeChunk(son[position%NB_MAX_SON]);
    son[position%NB_MAX_SON]=NULL;
    son[position%NB_MAX_SON]=Mix_LoadWAV(nom);
}

// joue le son un nombre nb de fois.
void joue_son(int position,int nb)
{
    extern Mix_Chunk* son[NB_MAX_SON];
    Mix_PlayChannel(position%NB_MAX_SON,son[position%NB_MAX_SON], 0);
    Mix_PlayChannelTimed(position%NB_MAX_SON,son[position%NB_MAX_SON], 3, 1000) ;
}

void initialisation_son()
{
    extern Mix_Chunk* son[NB_MAX_SON];
        int i;
    for(i=0;i<NB_MAX_SON;i++)
    {
        son[i]=NULL;
    }
}

void destruction_son()
{
    extern Mix_Chunk* son[NB_MAX_SON];
    int i;
    for(i=0;i<NB_MAX_SON;i++)
    {
        Mix_FreeChunk(son[i]);
        son[i]=NULL;
    }
}

void musique_off()
{
    extern Mix_Music* musique;
    if(musique!=NULL)
    {
        Mix_FreeMusic(musique);
        musique=NULL;
    }
}

// Joue de la musique un certain nombre de fois.
int musique_on(char* nom,int repetition)
{
    extern Mix_Music* musique;
    printf("%s",nom);

    if(musique)
        musique_off();
    musique=Mix_LoadMUS(nom);
    if(!musique)
    {
        fprintf(stderr, "Erreur d'initialisation de la musique\n");
        return 0;
    }
    Mix_PlayMusic(musique, repetition);
    return 1;
}

// Verifie musique verifie si la musique joue 1 (0 sinon)
int verifie_musique()
{
    return Mix_PlayingMusic();
}

// Mise à jour graphique
void mise_a_jour()
{
    extern SDL_Renderer* rendu;
    SDL_RenderPresent(rendu);
}

// Donne le type d'un evenement
int recupere_evenement()
{

    extern SDL_Event evenement;
    SDL_WaitEvent(&evenement);
    switch(evenement.type)
    {
    case(SDL_MOUSEBUTTONDOWN):
        if(evenement.button.button==SDL_BUTTON_RIGHT)
            return SOURIS_BOUTON_DROITE_ENFONCE;
        if(evenement.button.button==SDL_BUTTON_LEFT)
            return SOURIS_BOUTON_GAUCHE_ENFONCE;
        return RIEN;
    case(SDL_MOUSEBUTTONUP):
        if(evenement.button.button==SDL_BUTTON_RIGHT)
            return SOURIS_BOUTON_DROITE_RELACHE;
        if(evenement.button.button==SDL_BUTTON_LEFT)
            return SOURIS_BOUTON_GAUCHE_RELACHE;
        return RIEN;
    case(SDL_KEYDOWN):
        return TOUCHE_ENFONCEE;
    case(SDL_KEYUP):
        return TOUCHE_RELACHEE;
    case(SDL_MOUSEMOTION):
        return SOURIS_MOUVEMENT;
    case(SDL_QUIT):
        return EXIT;
    default:
        return RIEN;
    }
}
// Donne le type d'un evenement avec une limite de temps
int recupere_evenement_temps_limite(int temps)
{
    extern SDL_Event evenement;

    if(!SDL_WaitEventTimeout(&evenement,temps))
        return RIEN;
    switch(evenement.type)
    {
    case(SDL_MOUSEBUTTONDOWN):
        if(evenement.button.button==SDL_BUTTON_RIGHT)
            return SOURIS_BOUTON_DROITE_ENFONCE;
        if(evenement.button.button==SDL_BUTTON_LEFT)
            return SOURIS_BOUTON_GAUCHE_ENFONCE;
        return RIEN;
    case(SDL_MOUSEBUTTONUP):
        if(evenement.button.button==SDL_BUTTON_RIGHT)
            return SOURIS_BOUTON_DROITE_RELACHE;
        if(evenement.button.button==SDL_BUTTON_LEFT)
            return SOURIS_BOUTON_GAUCHE_RELACHE;
        return RIEN;
    case(SDL_KEYDOWN):
        return TOUCHE_ENFONCEE;
    case(SDL_KEYUP):
        return TOUCHE_RELACHEE;
    case(SDL_MOUSEMOTION):
        return SOURIS_MOUVEMENT;
    case(SDL_QUIT):
        return EXIT;
    default:
        return RIEN;
    }
}

int recupere_evenement_continu(int* resultat)
{
    extern SDL_Event evenement;
    *resultat=RIEN;
    if(SDL_PollEvent(&evenement))
    {
        switch(evenement.type)
        {
        case(SDL_MOUSEBUTTONDOWN):
            if(evenement.button.button==SDL_BUTTON_RIGHT)
                *resultat=SOURIS_BOUTON_DROITE_ENFONCE;
            else if(evenement.button.button==SDL_BUTTON_LEFT)
                *resultat=SOURIS_BOUTON_GAUCHE_ENFONCE;
            else *resultat=RIEN;
            return 1;
        case(SDL_MOUSEBUTTONUP):
            if(evenement.button.button==SDL_BUTTON_RIGHT)
                *resultat=SOURIS_BOUTON_DROITE_RELACHE;
            else if(evenement.button.button==SDL_BUTTON_LEFT)
                *resultat=SOURIS_BOUTON_GAUCHE_RELACHE;
            else *resultat= RIEN;
            return 1;
        case(SDL_KEYDOWN):
            *resultat= TOUCHE_ENFONCEE;
            return 1;
        case(SDL_KEYUP):
            *resultat= TOUCHE_RELACHEE;
            return 1;
        case(SDL_MOUSEMOTION):
            *resultat= SOURIS_MOUVEMENT;
            return 1;
        case(SDL_QUIT):
            *resultat= EXIT;
            return 1;
        default:
            return 1;
        }
    }
    return 0;
}

// Vide le buffer evenement
void vide_buffer()
{
    SDL_Event event;
    while(SDL_PollEvent(&event));
}


//donne la position de la souris en x
int souris_x()
{
    extern SDL_Event evenement;
    return evenement.motion.x;
}

//donne la position de la souris en y
int souris_y()
{
    extern SDL_Event evenement;
    return evenement.motion.y;
}

// Donne la touche appuyée
int touche()
{
    extern SDL_Event evenement;
    if(evenement.type==SDL_KEYDOWN||evenement.type==SDL_KEYUP)
        return evenement.key.keysym.sym;
    return 0;
}


//
