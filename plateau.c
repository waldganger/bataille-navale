#include <stdio.h>

#include "plateau.h"

#define NOMBRELIGNES 11
#define NOMBRECOLONNES 11

char plateauDeJeu1[NOMBRELIGNES][NOMBRECOLONNES];
char plateauDeJeu2[NOMBRELIGNES][NOMBRECOLONNES];

int numeroJoueur;
joueur tableauJoueurs[];

void plateauInit(char *ptableau)
{
  int i, j;
  //char *ptableau = &(*tableau)[0][0];
  for(i = 0; i < NOMBRELIGNES; i++)
    for(j = 0; j < NOMBRECOLONNES; j++)
      *(ptableau + i * NOMBRECOLONNES + j) = '~';
}

void affichePlateauDeJeu(char *ptableau)
{
  int i, j;
  if(numeroJoueur > 0)
    printf("*** Joueur %d -- Plateau de %s. ***\n", numeroJoueur, tableauJoueurs[numeroJoueur - 1].nom);
  for(i = 0; i < NOMBRELIGNES; i++){
    for(j = 0; j < NOMBRECOLONNES ; j++){
      if (i == 10 && j == 0)
	printf("[%d ]", *(ptableau +i * NOMBRECOLONNES + j));
      else
	printf("[%2c ]", *(ptableau + i * NOMBRECOLONNES + j));}
    printf("\n");
  }
}
void plateauIndices(char *ptableau)
//A l'aide d'un pointeur et de la table ASCII, créée la ligne et la colonne d'indice.
{
  int i, j;
  char *pAbcisses = ptableau;
  char *pOrdonnees = ptableau;
  
  pAbcisses++;			/* On décale le pointeur d'une colonne. */
  /* abcisses, de A à J */
  for (i = 0; i < NOMBRECOLONNES - 1; i++){
    *(pAbcisses + i) = 65 + i;
  }
  //ordonnées, char de 1 à 9
  for(i = 1, j = 0; i < NOMBRECOLONNES - 1; i++){
    *(pOrdonnees + (i * NOMBRECOLONNES + j)) = 48 + i ; // i = 1, donc on démarre à 48 au lieu de 49;
  }
  //10 != ASCII, alors on place un nombre en le castant en int.
  *(pOrdonnees + (i++ * NOMBRECOLONNES + j)) = (int) 10;
}

int placeBateau(char *ptableau, char typeNavire[], int taille)
{
  char xPoupe;			/* abcisses 0ABCDEFGHIJ */
  int yPoupe;			/* ordonnées 012345678910 */
  char *pCoordsNavire = ptableau;
  
    /* -------------- POUPE--------------- */
  printf("Entrez les coordonnées de la poupe de votre %s.\nEx : B 6 ou J7\n", typeNavire);
  scanf(" %1c%2d", &xPoupe, &yPoupe); // espace pour éviter un bug
  /* Test : case dans le cadre ? */
  if((xPoupe < 65 || xPoupe > 74) || (yPoupe < 1 || yPoupe > 10)){
    printf("Coordonnées erronées.\n");
    return 1;
  }
  printf("Vous avez entré les coordonnées %c - %d\n", xPoupe, yPoupe);
  (int) xPoupe;
  xPoupe -= 64;
  *(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '=';

  /* -------------- PROUE--------------- */
  char xProue;
  int yProue;
  printf("Entrez les coordonnées de la proue votre %s.\nEx : B 6 ou J7\n", typeNavire);
  scanf(" %1c%2d", &xProue, &yProue);
  /* Test : case hors du cadre ? */
  if((xProue < 65 || xProue > 74) || (yProue < 1 || yProue > 10)
     /* Test : cases en diagonale ? */
     || (xProue != xPoupe + 64 && yProue != yPoupe) /* XPoupe +64 pour comparer vals ASCII */
     /* Test : le bateau est trop grand ? */
     || ((xProue > (xPoupe + 64) + (taille - 1)) ||
	 (yProue > yPoupe + (taille - 1)))
     ){
    *(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
    *(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
    printf("Coordonnées erronées.\n");
    return 1;
  }
  printf("Vous avez entré les coordonnées %c - %d\n", xProue, yProue);
  (int) xProue;
  xProue -= 64;
  *(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '=';

  /* si le bateau est horizontal, on remplit les cases entre proue et poupe */
  if (yPoupe == yProue)
    for(; xProue > xPoupe; xProue--)
      *(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '=';
  /* si le bateau est vertical, on remplit les cases entre proue et poupe */
  else
    for(; yProue > yPoupe; yProue--)
      *(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '=';
      
  taille -= 1;			/* la taille servira à vérifier que le joueur dépasse pas. */
  
  return 0;
}

char * switchPlateau(void)
{
  char *pplateau = NULL;
  
  if(numeroJoueur == 1)
    return pplateau = &plateauDeJeu1[0][0];
  else
    return pplateau = &plateauDeJeu2[0][0];

}

void deploiementFlotte(void)
  // On code en dur l'appel de fonction pour placer chaque bateau
{
  while (placeBateau(switchPlateau(), "porte-avions", 5));
  affichePlateauDeJeu(switchPlateau());
  while (placeBateau(switchPlateau(), "croiseur", 4));
  affichePlateauDeJeu(switchPlateau());
  while (placeBateau(switchPlateau(), "contre-torpilleur", 3));
  affichePlateauDeJeu(switchPlateau());
  while (placeBateau(switchPlateau(), "contre-torpilleur", 3));
  affichePlateauDeJeu(switchPlateau());
  while (placeBateau(switchPlateau(), "torpilleur", 2));
  affichePlateauDeJeu(switchPlateau());
}
