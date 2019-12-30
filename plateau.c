#include <stdio.h>

#include "plateau.h"

#define NOMBRELIGNES 11
#define NOMBRECOLONNES 11

char plateauDeJeu1[NOMBRELIGNES][NOMBRECOLONNES];
char plateauDeJeu2[NOMBRELIGNES][NOMBRECOLONNES];

int numeroJoueur;
joueur tableauJoueurs[];

void plateauInit(char (*tableau)[NOMBRELIGNES][NOMBRECOLONNES])
{
  int i, j;
  char *ptableau = &(*tableau)[0][0];
  for(i = 0; i < NOMBRELIGNES; i++)
    for(j = 0; j < NOMBRECOLONNES; j++)
      //tableau[i][j] = '~';
      *(ptableau + i * NOMBRECOLONNES + j) = '~';
}

void affichePlateauDeJeu(char (*tableau)[NOMBRELIGNES][NOMBRECOLONNES])
{
  int i, j;
  char *ptableau = &(*tableau)[0][0];
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

void plateauIndices(char *plateauDeJeu, int n)
//A l'aide d'un pointeur et de la table ASCII, créée la ligne et la colonne d'indice.
{
  int i;
  char *pdepart = plateauDeJeu + n;
  plateauDeJeu++;
  for (i = 0; i < n - 1; i++){
    *plateauDeJeu = 65 + i;
    plateauDeJeu++;
  }
  //ordonnées, char de 1 à 9
  for(i = 0; i < n-2; i++){
    *pdepart = 49 + i;
    pdepart += n;
  }
  //10 != ASCII, alors on place un nombre
  *pdepart++ = 10;
  
}

int placeBateau(char tableau[NOMBRELIGNES][NOMBRECOLONNES], char typeNavire[], int taille)
{
  char x;			/* abcisses 0ABCDEFGHIJ */
  int y;			/* ordonnées 012345678910 */
  char *p1 = &tableau[0][0];
  char *p2 = &tableau[0][0];
  while (taille > 0){
  printf("Entrez les coordonnées de votre %s.\nEx : B 6 ou J7\n", typeNavire);
  scanf(" %1c%2d", &x, &y);
  if((x < 65 || x > 74) || (y < 1 || y > 10)){
    printf("Coordonnées erronées.\n");
    return -1;
  }
  printf("Vous avez entré les coordonnées %c - %d\n", x, y);
  (int) x;
  x -= 64;
  
  tableau[y][x] = '=';
  taille -= 1;
  }
  return 0;
}

void placementGeneral(void)
{
  
}
