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
  int vertical = 0;		/* pour la fonction memCoordonnées. Par défaut, horizontal. */
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
    
    {
      /*Mais d'abord, on vérifie que le bateau n'est pas collé à un autre 
	Si bateau horizontal, on teste les cases suivantes en deux temps :

	1. boucle if
	rien à gauche de la poupe
	rien à droite de la proue
	rien à [-1][-1] de la poupe
	rien à [-1][+1] de la poupe
	rien à [+1][-1] de la proue
	rien à [+1][+1] de la proue
	2. boucle for
	rien en haut de chaque case
	rien en bas de chaque case
      */
    
    if ( *(pCoordsNavire + (yPoupe * NOMBRECOLONNES + xPoupe - 1)) == '='
	 || *(pCoordsNavire + (yProue * NOMBRECOLONNES + xProue + 1)) == '='
	 || *(pCoordsNavire + ((yPoupe -1) * NOMBRECOLONNES + xPoupe - 1)) == '='
	 || *(pCoordsNavire + ((yPoupe + 1) * NOMBRECOLONNES + xPoupe - 1)) == '='
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue - 1)) == '='
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue + 1)) == '=')
      {
	/* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	*(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
	*(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
	printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
	return 1;
      }
    for (; xProue > xPoupe; xProue--){
      
      if ( *(pCoordsNavire + ((yProue + 1) * NOMBRECOLONNES + xProue)) == '='
      	   || *(pCoordsNavire + ((yProue - 1) * NOMBRECOLONNES + xProue)) == '=')
      	{
	  /* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	  *(pCoordsNavire + (yPoupe * NOMBRECOLONNES + xPoupe)) = '~'; // on efface la poupe
	  //la proue ne s'efface pas car xProue décrémente dans la boucle.
	  *(pCoordsNavire + (yProue * NOMBRECOLONNES + xProue + 1)) = '~'; // on efface la proue
      	  printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
      	  return 1;
      	}
	
      *(pCoordsNavire + (yProue * NOMBRECOLONNES + xProue)) = '=';
    }
    
    }
  
  /* le bateau n'est pas horizontal, il est donc vertical #genius */
  
  else
    {
      vertical = 1;			/* on passe le commutateur à vrai */
      /* On vérifie que les cases adjacentes sont libres en 2 temps : 
	 1. boucle if
	 rien en haut de la poupe
	 rien en bas de la proue
	 rien à [-1][-1] de la poupe
	 rien à [+1][-1] de la poupe
	 rien à [-1][+1] de la proue
	 rien à [+1][+1] de la proue
	 2. Boucle for
	 rien à gauche de chaque case
	 rien à droite de chaque case */
      
    if ( *(pCoordsNavire + ((yPoupe - 1) * NOMBRECOLONNES + xPoupe)) == '='
	 || *(pCoordsNavire + ((yProue + 1) * NOMBRECOLONNES + xProue)) == '='
	 || *(pCoordsNavire + ((yPoupe -1) * NOMBRECOLONNES + xPoupe - 1)) == '='
	 || *(pCoordsNavire + ((yPoupe + 1) * NOMBRECOLONNES + xPoupe - 1)) == '='
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue - 1)) == '='
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue + 1)) == '=')
      {
	/* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	*(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
	*(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
	
	printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
	return 1;
      }
    /* Préparation copie coordonnées pour les passer à la fonction memCoordonnées */
    
    int copieyPoupe = yPoupe;
    int copiexPoupe = xPoupe;
    
    for(; yProue > yPoupe; yProue--){

      if ( *(pCoordsNavire + (yProue * NOMBRECOLONNES + xProue - 1)) == '='
      	   || *(pCoordsNavire + (yProue * NOMBRECOLONNES + xProue + 1)) == '=')
      	{
	  /* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	  *(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
	  //la proue ne s'efface pas car yProue décrémente dans la boucle.
	  *(pCoordsNavire + ((yProue + 1) * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
	  
      	  printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
      	  return 1;
      	}
      /* on remplit les cases entre proue et poupe  */
      *(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '=';
    }
    /* Les coordonnées ont été testées, on peut enfin les copier dans la mémoire */
    memCoordonnees(numeroJoueur, copiexPoupe, copieyPoupe, vertical, taille);
    
    }
  /* retour 0 sert à sortir des boucles dans fonction deploiementFlotte */
  return 0; 			
}


void memCoordonnees(int numeroJoueur, int xPoupe, int yPoupe, int vertical, int taille)

/* 
copie des coordonnées dans array tableauJoueurs[numeroJoueur].coordPorteAvions[5][2]
tableauJoueurs[numeroJoueur].coordPorteAvions[5][2] = {
{65 , 2}
{66 , 2}
{67 , 2}
{68 , 2}
{69 , 2}
}
 */
  
{
  int i, j;
  if(vertical)			/* on itère les Ypoupe, les xPoupes restent fixes */
    switch (taille)		/* quel type de bateau est-ce ? */
      {

      case 5:			/* c'est le porte-avion */
	
	for (i = 0; i < taille; i++, yPoupe++)	
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][0] = yPoupe;
	for (i = 0; i < taille; i++)
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][1] = xPoupe;
	
	for (i = 0; i < taille; i++)
	  for (j= 0; j < 2; j++)
	    printf(" %d ", tableauJoueurs[numeroJoueur].coordPorteAvions[i][j]);
	printf("\n");
       	break;
	
      case 4:
	for (i = 0; i < taille; i++, yPoupe++)	
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][0] = yPoupe;
	for (i = 0; i < taille; i++)
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][1] = xPoupe;
	
	for (i = 0; i < taille; i++)
	  for (j= 0; j < 2; j++)
	    printf(" %d ", tableauJoueurs[numeroJoueur].coordCroiseur[i][j]);
	printf("\n");
       	break;

      case 3:
	/* Les deux contre-torpilleurs ont une taille de 3.
	 Pour savoir quel tableau remplir, on teste si le premier est vide.
	S'il l'est, on le remplit.
	S'il ne l'est pas, on remplir le 2eme. */
	
	if (tableauJoueurs[numeroJoueur].coordContreTorpilleur[0][0])
	  {
	    for (i = 0; i < taille; i++, yPoupe++)	
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][0] = yPoupe;
	    for (i = 0; i < taille; i++)
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][1] = xPoupe;
	
	    for (i = 0; i < taille; i++)
	      for (j= 0; j < 2; j++)
		printf(" %d ", tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][j]);
	    printf("\n");
	    break;
	  }

	else
	  {
	    for (i = 0; i < taille; i++, yPoupe++)	
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][0] = yPoupe;
	    for (i = 0; i < taille; i++)
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][1] = xPoupe;
	
	    for (i = 0; i < taille; i++)
	      for (j= 0; j < 2; j++)
		printf(" %d ", tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][j]);
	    printf("\n");
	    break;
	  }

      case 2:
	  for (i = 0; i < taille; i++, yPoupe++)	
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][0] = yPoupe;
	    for (i = 0; i < taille; i++)
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][1] = xPoupe;
	
	    for (i = 0; i < taille; i++)
	      for (j= 0; j < 2; j++)
		printf(" %d ", tableauJoueurs[numeroJoueur].coordTorpilleur[i][j]);
	    printf("\n");
	    break;
		
	default:
	  break;
      }
    

  else				/* on itère les xPoupe */
    ;
  
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
  while (placeBateau(switchPlateau(), "contre-torpilleur n°2", 3));
  affichePlateauDeJeu(switchPlateau());
  while (placeBateau(switchPlateau(), "torpilleur", 2));
  affichePlateauDeJeu(switchPlateau());
}
