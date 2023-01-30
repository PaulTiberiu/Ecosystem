#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20


int main(void) {
	
  /* A Completer. */
  /* Part 1, exercice 5, question 3 */
  
  Animal *pa=NULL;

  Animal *pred2=creer_animal(18,49,50.0);
  pred2->dir[1]=-1;
  Animal *pred=creer_animal(1,2,50.0);
  ajouter_animal(10,10,75.0,&pred2);
  ajouter_en_tete_animal(pred2,pred);
  ajouter_animal(19,49,75.0,&pred);
  //on a cree un predateur puis on a ajoute encore 3 predateurs dans notre  liste de predateurs 
  
  enlever_animal(&pred,pred2);
  
  pa=pred;
  for(int i=0;pa!=NULL;i++){
    printf("predateur n°%d: %d ,%d ,%f\n",i+1,pa->x,pa->y,pa->energie);
    pa=pa->suivant;
  }

  Animal *proie=creer_animal(19,49,50.0);
  proie->dir[0]=-1;
  ajouter_animal(1,2,25.0,&proie);
  ajouter_animal(10,10,75.0,&proie);
  ajouter_animal(13,20,75.0,&proie);
  //on a cree une proie puis on a ajoute encore 3 proies dans notre liste de proies

  pa=proie;
  for(int i=0;pa!=NULL;i++){
    printf("proie n°%d: %d ,%d ,%f\n",i+1,pa->x,pa->y,pa->energie);
    pa=pa->suivant;
  }
  
  afficher_ecosys(proie,pred);
  reproduce(&proie,1);
  reproduce(&pred,1);
  bouger_animaux(proie);
  bouger_animaux(pred);
  afficher_ecosys(proie,pred);
  liberer_liste_animaux(pred);
  liberer_liste_animaux(proie);


  return 0;
}
