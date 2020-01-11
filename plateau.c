#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

#define NOMBRELIGNES 11
#define NOMBRECOLONNES 11

char plateauDeJeu1[NOMBRELIGNES][NOMBRECOLONNES];
char plateauDeJeu2[NOMBRELIGNES][NOMBRECOLONNES];

char masquePlateauDeJeu1[NOMBRELIGNES][NOMBRECOLONNES];
char masquePlateauDeJeu2[NOMBRELIGNES][NOMBRECOLONNES];

int numeroJoueur;
joueur tableauJoueurs[];

void plateauInit(char *ptableau)
{
  int i, j;
  
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
     /* Test : le bateau est trop grand ou trop petit ? */
     /* || ((xProue > (xPoupe + 64) + (taille - 1)) || */
     /* 	 (yProue > yPoupe + (taille - 1))) */
     || ((xProue - (taille - 1) != (xPoupe + 64)) && (yProue - (taille - 1) != yPoupe))
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
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue + 1)) == '='
  	 )
      {
	/* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	*(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
	*(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
	printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
	return 1;
      }

    /* Copie coordonnées validées pour les passer à la fonction memCoordonnées */
    
    int copieyPoupe = yPoupe;
    int copiexPoupe = xPoupe;
    
    for (; xProue >= xPoupe; xProue--){
      
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
    memCoordonnees(numeroJoueur, copiexPoupe, copieyPoupe, vertical, taille);
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
	 || *(pCoordsNavire + ((yProue +1) * NOMBRECOLONNES + xProue + 1)) == '='
	 )
      {
	/* les bateaux se chevauchent ou sont collés : on fait un reset des coords entrées */
	*(pCoordsNavire + (yPoupe * NOMBRECOLONNES +xPoupe)) = '~'; // on efface la poupe
	*(pCoordsNavire + (yProue * NOMBRECOLONNES +xProue)) = '~'; // on efface la proue
	
	printf("Les bateaux ne doivent pas se chevaucher, ni être collés.\n");
	return 1;
      }
    /* Copie coordonnées validées pour les passer à la fonction memCoordonnées */
    
    int copieyPoupe = yPoupe;
    int copiexPoupe = xPoupe;
    
    for(; yProue >= yPoupe; yProue--){

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
/* copie des coordonnées dans array tableauJoueurs[numeroJoueur].coordPorteAvions[5][2] */
{
  numeroJoueur--;		/* creeJoueur a déjà incrémenté de 1, on recule */
  int i, j;
  if(vertical)			/* on itère les Ypoupe, les xPoupes restent fixes */
    switch (taille)		/* quel type de bateau est-ce ? */
      {

      case 5:			/* c'est le porte-avion */
	
	for (i = 0; i < taille; i++, yPoupe++)	
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][0] = yPoupe;
	for (i = 0; i < taille; i++)
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][1] = xPoupe;
       	break;
	
      case 4:
	for (i = 0; i < taille; i++, yPoupe++)	
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][0] = yPoupe;
	for (i = 0; i < taille; i++)
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][1] = xPoupe;
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
	    break;
	  }

	else
	  {
	    for (i = 0; i < taille; i++, yPoupe++)	
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][0] = yPoupe;
	    for (i = 0; i < taille; i++)
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][1] = xPoupe;
	    break;
	  }

      case 2:
	  for (i = 0; i < taille; i++, yPoupe++)	
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][0] = yPoupe;
	    for (i = 0; i < taille; i++)
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][1] = xPoupe;
	    break;
		
	default:
	  break;
      }
    

  else				/* Le bateau est horizontal, on itère les xPoupe */
    {
      
      switch (taille)		/* quel type de bateau est-ce ? */
      {

      case 5:			/* c'est le porte-avion */
	
	for (i = 0; i < taille; i++)	
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][0] = yPoupe;
	for (i = 0; i < taille; i++, xPoupe++)
	  tableauJoueurs[numeroJoueur].coordPorteAvions[i][1] = xPoupe;
       	break;
	
      case 4:
	for (i = 0; i < taille; i++)	
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][0] = yPoupe;
	for (i = 0; i < taille; i++, xPoupe++)
	  tableauJoueurs[numeroJoueur].coordCroiseur[i][1] = xPoupe;
       	break;

      case 3:
	/* Les deux contre-torpilleurs ont une taille de 3.
	 Pour savoir quel tableau remplir, on teste si le premier est vide.
	S'il est plein, on remplit le 2nd.
	Sinon, on remplit le premier. */
	
	if (tableauJoueurs[numeroJoueur].coordContreTorpilleur[0][0])
	  {
	    for (i = 0; i < taille; i++)	
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][0] = yPoupe;
	    for (i = 0; i < taille; i++, xPoupe++)
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur2[i][1] = xPoupe;
	    break;
	  }

	else
	  {
	    for (i = 0; i < taille; i++)	
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][0] = yPoupe;
	    for (i = 0; i < taille; i++, xPoupe++)
	      tableauJoueurs[numeroJoueur].coordContreTorpilleur[i][1] = xPoupe;
	    break;
	  }

      case 2:
	  for (i = 0; i < taille; i++)	
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][0] = yPoupe;
	  for (i = 0; i < taille; i++, xPoupe++)
	      tableauJoueurs[numeroJoueur].coordTorpilleur[i][1] = xPoupe;
	    break;
		
	default:
	  break;
      } 
    }
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
  printf("\nDéployez votre flotte !\n");
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


void plateauxMasquesinit(void)
{
  int i, j;
  char *ptableaumasque1 = &masquePlateauDeJeu1[0][0];
  char *ptableaumasque2 = &masquePlateauDeJeu2[0][0];
  
  for(i = 0; i < NOMBRELIGNES; i++)
    for(j = 0; j < NOMBRECOLONNES; j++)
      {
      *(ptableaumasque1 + i * NOMBRECOLONNES + j) = '~';
      *(ptableaumasque2 + i * NOMBRECOLONNES + j) = '~';
      }
}

int aPrintAquiDeTirer(int tour)
{
  if(tour % 2) 		/* joueur 1 si tour impair */
    printf("*** Tour n° %d. A %s de tirer !\n", tour, tableauJoueurs[0].nom);
  else
    printf("*** Tour n° %d. A %s de tirer !\n", tour, tableauJoueurs[1].nom);
  return tour;
}


char * afficheMasquePlateauDeJeu(int tour)
{
  int i, j;
  char *pointeurmasque = NULL;
  char *pAbcisses = NULL;
  char *pOrdonnees = NULL;
  
  if(tour % 2) 		/* joueur 1 si tour impair */
    pointeurmasque = pAbcisses = pOrdonnees = &masquePlateauDeJeu1[0][0];
  else
    pointeurmasque = pAbcisses = pOrdonnees = &masquePlateauDeJeu2[0][0];

/* --- affichage des indices --- */
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


  
  for(i = 0; i < NOMBRELIGNES; i++){
    for(j = 0; j < NOMBRECOLONNES ; j++)
      {
      if (i == 10 && j == 0)
	printf("[%d ]", *(pointeurmasque +i * NOMBRECOLONNES + j));
      else
	printf("[%2c ]", *(pointeurmasque + i * NOMBRECOLONNES + j));
      }
    printf("\n");
  }
  return pointeurmasque;
}


int tir(char *pointeurVersBonPlateauMasque)
{
  char xTir;
  int yTir;
  char *pCoordonneesTir = pointeurVersBonPlateauMasque;
  int controleCoordonneesTir = 1;
  int indiceTableauJoueurs = 1;
  int i;
 
  /* Le joueur entre ses coordonnées de tir */
  while(controleCoordonneesTir)
    {
  printf("Entrez les coordonnées de tir.\n Ex : B 6 ou J7\n");
  scanf(" %1c%2d", &xTir, &yTir); // espace pour éviter un bug
  /* Test : case dans le cadre ? */
  if((xTir < 65 || xTir > 74) || (yTir < 1 || yTir > 10))
    printf("Coordonnées erronées.\n");
  /* Test : 2ème tir au même endroit ? */
  else if (*(pCoordonneesTir + (yTir * NOMBRECOLONNES + (xTir - 64))) == 'X'
	   || *(pCoordonneesTir + (yTir * NOMBRECOLONNES + (xTir - 64))) == 'o')
    printf("Vous avez déjà diré à cet endroit.\n");
  else
    controleCoordonneesTir = 0;
    }
  
  printf("TIR en %c - %d\n", xTir, yTir);
  
  (int) xTir;
  xTir -= 64;

  int coordonneesTir[2] = {yTir, xTir};

  /* si joueur 1 avec masque de jeu 1, on lie le tir au plateau de jeu du J2 pour vérifier si le tir réussit */
  indiceTableauJoueurs = (pCoordonneesTir == &masquePlateauDeJeu1[0][0]) ? 1 : 0;

  /* Cinq boucles avec limite adaptées pour comparer coords tir et coords de chaque navire */
  /* Porte-avions */
    for (i = 0; i < 5 ; i++)
      if (coordonneesTir[0] == tableauJoueurs[indiceTableauJoueurs].coordPorteAvions[i][0] &&
	coordonneesTir[1] == tableauJoueurs[indiceTableauJoueurs].coordPorteAvions[i][1])
	{
	*(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'X';
	
	if (--(tableauJoueurs[indiceTableauJoueurs].porteAvions))
	  printf("Porte-avions touché %d/5!\n\n", 5 - tableauJoueurs[indiceTableauJoueurs].porteAvions);
	else
	  printf("Porte-avions coulé !\n\n");
	tour++;
	return indiceTableauJoueurs;
	}
	
    /* Croiseur */
    for (i = 0; i < 4 ; i++)
      if (coordonneesTir[0] == tableauJoueurs[indiceTableauJoueurs].coordCroiseur[i][0] &&
	coordonneesTir[1] == tableauJoueurs[indiceTableauJoueurs].coordCroiseur[i][1])
	{
	*(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'X';
	if (--(tableauJoueurs[indiceTableauJoueurs].croiseur))
	printf("Croiseur touché %d/4!\n\n", 4 - tableauJoueurs[indiceTableauJoueurs].croiseur);
	else
	  printf("Croiseur coulé !\n\n");
	tour++;
	return indiceTableauJoueurs;
	}

    /* Contre-torpilleur 1 */
    for (i = 0; i < 3 ; i++)
      if (coordonneesTir[0] == tableauJoueurs[indiceTableauJoueurs].coordContreTorpilleur[i][0] &&
	coordonneesTir[1] == tableauJoueurs[indiceTableauJoueurs].coordContreTorpilleur[i][1])
	{
	*(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'X';
	if (--(tableauJoueurs[indiceTableauJoueurs].contreTorpilleur))
	printf("Contre-torpilleur No 1 touché %d/3!\n\n", 3 - tableauJoueurs[indiceTableauJoueurs].contreTorpilleur);
	
	else
	  printf("Contre torpilleur No 1 coulé !\n\n");
	tour++;
	return indiceTableauJoueurs;
	}
    
    /* Contre-torpilleur 2 */
    for (i = 0; i < 3 ; i++)
      if (coordonneesTir[0] == tableauJoueurs[indiceTableauJoueurs].coordContreTorpilleur2[i][0] &&
	coordonneesTir[1] == tableauJoueurs[indiceTableauJoueurs].coordContreTorpilleur2[i][1])
	{
	*(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'X';
	if (--(tableauJoueurs[indiceTableauJoueurs].contreTorpilleur2))
	printf("Contre-torpilleur No 2 touché %d/3!\n\n", 3 - tableauJoueurs[indiceTableauJoueurs].contreTorpilleur2);
	else
	  printf("Contre torpilleur No 2 coulé !\n\n");
	tour++;
	return indiceTableauJoueurs;
	}
	
    /* Torpilleur */
    for (i = 0; i < 2 ; i++)
      if (coordonneesTir[0] == tableauJoueurs[indiceTableauJoueurs].coordTorpilleur[i][0] &&
	coordonneesTir[1] == tableauJoueurs[indiceTableauJoueurs].coordTorpilleur[i][1])
	{
	*(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'X';
	if (--(tableauJoueurs[indiceTableauJoueurs].torpilleur))
	printf("Torpilleur touché %d/2!\n\n", 2 - tableauJoueurs[indiceTableauJoueurs].torpilleur);
	else
	  printf("Torpilleur coulé !\n\n");
	tour++;
	return indiceTableauJoueurs;
	}
    *(pCoordonneesTir + (yTir * NOMBRECOLONNES +xTir)) = 'o';
    tour++;
    return indiceTableauJoueurs;
}

int clrScreen(int indiceTableauJoueurs)
{
  
  afficheMasquePlateauDeJeu(tour - 1); // le tour a déjà été incrémenté par tir();
  printf("Appuyez sur entrée pour changer de tour.\n");
  //scanf(" %1c", &touche);
  getchar();
  getchar();
  system("@cls||clear");
  //clrscr();
  //efface l'écran d'un terminal GNU/Linux ou Windows.
  return indiceTableauJoueurs;
}

int victoire(int indiceTableauJoueurs)
/* détecte la vitoire et retourne le signal de fin de partie 
   0 : continue
   1 : joueur 1 gagne
   2 : joueur 2 gagne
*/
{ 
  if (tableauJoueurs[indiceTableauJoueurs].porteAvions +
      tableauJoueurs[indiceTableauJoueurs].croiseur +
      tableauJoueurs[indiceTableauJoueurs].contreTorpilleur +
      tableauJoueurs[indiceTableauJoueurs].contreTorpilleur2 +
      tableauJoueurs[indiceTableauJoueurs].torpilleur)
    return -1;			/* pas de victoire */

  else
    return indiceTableauJoueurs; /* 0 ou 1 */
}

void partie(void)
{
  plateauxMasquesinit();
  
  while(1)
    {
      int ctrlVictoire;
      //clrScreen();
      ctrlVictoire = victoire(clrScreen(tir(afficheMasquePlateauDeJeu(aPrintAquiDeTirer(tour)))));
      
      if (ctrlVictoire == 0 )
	{
	  printf("%s a gagné la partie. La flotte de %s est entièrement détruite.\n",
  	     tableauJoueurs[1].nom, tableauJoueurs[0].nom);
	  break;
      }
      
      else if (ctrlVictoire == 1 )
	{
	  printf("%s a gagné la partie. La flotte de %s est entièrement détruite.\n",
  	     tableauJoueurs[0].nom, tableauJoueurs[1].nom);
	  break;
  }
  
    }
  printf("Fin de la partie.\n\n");
}
