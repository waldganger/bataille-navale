#include <stdio.h>
#include <string.h>

#include "plateau.h"

#define TAILLE_MAX_TABLEAU 256



extern int numeroJoueur ;
int numeroJoueur = 0;


void menuPrincipal(void);
void creeJoueur(void);
void afficheFicheJoueur(int numeroJoueur);
void afficheTableauJoueurs (void);
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
  printf("5. Quitter.\n");
  scanf("%d", &choixMenuPrincipal);
  if(choixMenuPrincipal == 1){
    
    if(numeroJoueur > 0){
      creeJoueur();
      plateauInit(&plateauDeJeu2);
      plateauIndices(&plateauDeJeu2);
      affichePlateauDeJeu(&plateauDeJeu2);

      menuPrincipal();
    }
    else{
      
      creeJoueur();
      plateauInit(&plateauDeJeu1);
      plateauIndices(&plateauDeJeu1);
      affichePlateauDeJeu(&plateauDeJeu1);
      while (1){
	placeBateau(plateauDeJeu1, "porte-avions", 5); // On code en dur le plac. pr ch bat.
      affichePlateauDeJeu(&plateauDeJeu1);}
      menuPrincipal();
    }
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
  
  printf("La fiche a bien été créée.\n\n");
  afficheFicheJoueur(numeroJoueur);
  numeroJoueur++;
  //menuPrincipal();
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

int quitter(void){
  return 0;
}
