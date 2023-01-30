#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
//float p_ch_dir=0.01;
//float p_reproduce_proie=0.4;
//float p_reproduce_predateur=0.5;
//int temps_repousse_herbe=-15;


int main(void) {
	
  /* A completer. Part 2:
  * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */
	srand(time(NULL));
	int tab[SIZE_X][SIZE_Y];
	for(int i=0;i<SIZE_X;i++){
		for(int j=0;j<SIZE_Y;j++){
			tab[i][j]=0;
		}
	}
	
	Animal *proie=creer_animal(2,3,50.0);
	for(int i=0;i<19;i++){
		ajouter_animal(rand()%20,rand()%50,1+rand()%99,&proie);
	}
	
	Animal *predateur=creer_animal(12,32,50.0);
	for(int i=0;i<19;i++){
		ajouter_animal(rand()%20,rand()%50,1+rand()%99,&predateur);
	}
	
	//rafraichir_proies(&proie, tab);
	//afficher_ecosys(proie,NULL);
	
	
	unsigned int nb_proies=compte_animal_it(proie);
	unsigned int nb_predateurs=compte_animal_it(predateur);
	int nb_generation=0;
	FILE *fichier=fopen("Evol_Pop.txt","w");
	if(fichier==NULL){
		fprintf(stderr,"Erreur d'ouverture du fichier");
		return 1;
	}
	else{
		fclose(fichier);
	}
	
	int cpt=0;
	afficher_ecosys(proie,predateur);// l'affichage du premier ecosys avec 20 proies et 20 predateurs
	
	while(proie!=NULL && predateur!=NULL && cpt<200){
	
		FILE *fichier=fopen("Evol_Pop.txt","a");
		fprintf(fichier,"%d %d %d\n",nb_generation++,nb_proies,nb_predateurs);
		fclose(fichier);
		
		rafraichir_proies(&proie,tab);
		rafraichir_predateurs(&predateur,&proie);
		rafraichir_monde(tab);//si on fait pas rafraichir_monde, les proies vont mourir car ils ont pas de l'herbe
		printf("compteur a chaque iteration: %d\n",cpt);
		afficher_ecosys(proie,predateur);
		cpt++;
		
		nb_proies = compte_animal_it(proie);
		nb_predateurs = compte_animal_it(predateur);
		
		usleep(999999);
	}
	
  liberer_liste_animaux(proie);
  liberer_liste_animaux(predateur);
  return 0;
}

