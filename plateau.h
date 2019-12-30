#ifndef PLATEAU_H
#define PLATEAU_H

#define NOMBRELIGNES 11
#define NOMBRECOLONNES 11
#define TAILLE_MAX_TABLEAU 256


extern char plateauDeJeu1[NOMBRELIGNES][NOMBRECOLONNES];
extern char plateauDeJeu2[NOMBRELIGNES][NOMBRECOLONNES];


typedef struct joueur
{
  signed char nom[256];
  unsigned char porteAvions;
  unsigned char croiseur;
  unsigned char contreTorpilleur;
  unsigned char contreTorpilleur2;
  unsigned char torpilleur;
  
  int coordPorteAvions[5][2];
  int coordCroiseur[4][2];
  int coordContreTorpilleur[3][2];
  int coordContreTorpilleur2[3][2];
  int coordTorpilleur[2][2];
  
}joueur;

extern joueur tableauJoueurs[TAILLE_MAX_TABLEAU];

void plateauInit(char *ptableau);
void affichePlateauDeJeu(char *ptableau);
void plateauIndices(char *ptableau);
int placeBateau(char *ptableau, char typeNavire[], int taille);
char * switchPlateau(void);
void placementGeneral(void);

#endif
