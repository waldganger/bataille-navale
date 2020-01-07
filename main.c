#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plateau.h"

#define TAILLE_MAX_TABLEAU 2	/* nombre de joueurs max */


extern int numeroJoueur ;
extern int tour ;
int tour = 1;
int numeroJoueur = 0;


void menuPrincipal(void);
void creeJoueur(void);
void afficheFicheJoueur(int numeroJoueur);
void afficheTableauJoueurs (void);
void initialisationJoueur(void);
int quitter(void);

int main(void)
{
  menuPrincipal();
  return 0;
}

void menuPrincipal(void)
{
  int choixMenuPrincipal ;
  int choixDuJoueur;
  
  printf("Bienvenue. Voulez-vous :\n");
  printf("1. Créer une fiche joueur ?\n");
  printf("2. Afficher la fiche d'un joueur ?\n");
  printf("3. Voir la liste des joueurs ?\n");
  printf("4. Placer vos bateaux ?\n");
  printf("5. Démarrer une partie.\n");
  printf("6. Quitter.\n");
  scanf("%d", &choixMenuPrincipal);
  
  if(choixMenuPrincipal == 1){
    initialisationJoueur();
}
  
  else if(choixMenuPrincipal == 2){
    printf("Quelle fiche joueur voulez-vous consulter ?\n");
    scanf("%d", &choixDuJoueur);
    afficheFicheJoueur(choixDuJoueur - 1);
    menuPrincipal();
  }
  else if (choixMenuPrincipal == 3)
    afficheTableauJoueurs();
  else if (choixMenuPrincipal == 4){
    
  }

  else if (choixMenuPrincipal == 5)
    partie();
  
  else if (choixMenuPrincipal == 6)
    quitter();
  else{
    printf("\nMauvaise entrée. Veuillez VOUS REPRENDRE.\n");
    printf("Appuyez sur une touche pour revenir au menu principal.\n");
    getchar();
    putchar('\n');
    main();
  }
}
  

void creeJoueur(void)
{
  // extern int numeroJoueur;
  //extern joueur tableauJoueurs[5];
  char inputNom[256];
  printf("Entrez un nom de joueur.\n");
  scanf("%s", inputNom);
  
  strcpy(tableauJoueurs[numeroJoueur].nom, inputNom);
  tableauJoueurs[numeroJoueur].porteAvions = 5;
  tableauJoueurs[numeroJoueur].croiseur = 4;
  tableauJoueurs[numeroJoueur].contreTorpilleur = 3;
  tableauJoueurs[numeroJoueur].contreTorpilleur2 = 3;
  tableauJoueurs[numeroJoueur].torpilleur = 2;

  /* initialisation des tableaux de coordonnées des bateaux. */
  int i, j;
  for (i = 0; i < tableauJoueurs[numeroJoueur].porteAvions; i++)
    for (j = 0; j < 2; j++)
      tableauJoueurs[numeroJoueur].coordPorteAvions[i][j] = 0;

  for (i = 0; i < tableauJoueurs[numeroJoueur].croiseur; i++)
    for (j = 0; j < 2; j++)
      tableauJoueurs[numeroJoueur].coordCroiseur[i][j] = 0;

  for (i = 0; i < tableauJoueurs[numeroJoueur].contreTorpilleur; i++)
    for (j = 0; j < 2; j++)
      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][j] = 0;
      
  for (i = 0; i < tableauJoueurs[numeroJoueur].contreTorpilleur2; i++)
    for (j = 0; j < 2; j++)
      tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][j] = 0;

  for (i = 0; i < tableauJoueurs[numeroJoueur].torpilleur; i++)
    for (j = 0; j < 2; j++)
      tableauJoueurs[numeroJoueur].coordTorpilleur[i][j] = 0;
  
  printf("La fiche a bien été créée.\n\n");
  afficheFicheJoueur(numeroJoueur);
  numeroJoueur++;
  
}

void afficheFicheJoueur(int numeroJoueur)
{
  if(*tableauJoueurs[numeroJoueur].nom == 0 || numeroJoueur > TAILLE_MAX_TABLEAU - 1){
    printf("Ce joueur n'existe pas.\n\n");
    menuPrincipal();}
  printf("*** Joueur %d, %s  -- Etat des navires de la flotte. ***\n", numeroJoueur + 1, tableauJoueurs[numeroJoueur].nom);
  
  printf("porte-avions : %d/5\n", tableauJoueurs[numeroJoueur].porteAvions);
  printf("croiseur : %d/4\n", tableauJoueurs[numeroJoueur].croiseur);
  printf("contre-torpilleur : %d/3\n", tableauJoueurs[numeroJoueur].contreTorpilleur);
  printf("contre-torpilleur No. 2 : %d/3\n", tableauJoueurs[numeroJoueur].contreTorpilleur2);
  printf("torpilleur : %d/2\n", tableauJoueurs[numeroJoueur].torpilleur);
  putchar('\n');
}

void afficheTableauJoueurs (void)
{
  int i;
  for(i = 0; *tableauJoueurs[i].nom && i < TAILLE_MAX_TABLEAU; i++)
    afficheFicheJoueur(i);
  menuPrincipal();
}
void initialisationJoueur(void)
// crée un joueur et place sa flotte
{
  creeJoueur();
  plateauInit(switchPlateau());
  plateauIndices(switchPlateau());
  affichePlateauDeJeu(switchPlateau());
  deploiementFlotte();
  menuPrincipal();

}

int quitter(void){
  exit(1);
}
