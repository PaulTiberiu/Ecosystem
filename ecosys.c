#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.2;
int temps_repousse_herbe=0;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
} 


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert((x<SIZE_X) && (x>=0) && (y < SIZE_Y) && (y>=0) && (energie>0.0));
	*liste_animal = ajouter_en_tete_animal(*liste_animal,creer_animal(x,y,energie));
  /*Animal *animal1=NULL;
  animal1 = creer_animal(x,y,energie);
  animal1->suivant = *liste_animal;
  *liste_animal = animal1;              // ??????????????????????????????????*/
}

/* A Faire. Part 1, exercice 5, question 5 */

void enlever_animal(Animal **liste, Animal *animal){
  assert(liste); assert(animal);assert(*liste);
    Animal*p, *t;
    if(*liste==animal){
      p = *liste;
      *liste = (*liste)->suivant;
      free(p);
      return ;
    }
    p = *liste;
    while(p->suivant!=NULL && p->suivant!=animal){
      p=p->suivant;
    }
    if(p->suivant!=NULL){
      t = p->suivant;
      p->suivant = t->suivant;
      free(t);
    }
  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal* temp;
  for(;liste!=NULL;){
    temp = liste->suivant;
    free(liste);
    liste=temp;
  }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  /* on initialise le tableau */
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      pa = liste_proie;
      while(pa!=NULL){
        if(pa->x == i && pa->y == j){
          ecosys[i][j]='*';
          nbproie++;
        }
        pa = pa->suivant;
      }
    }
  }


  /* on ajoute les predateurs */
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      pa = liste_predateur;
      while(pa!=NULL){
        if(pa->x == i && pa->y == j){
          if(ecosys[i][j]=='*'){
            ecosys[i][j]='@';
          }
          else ecosys[i][j]='0';
          nbpred++;
        }
        pa = pa->suivant;
      }
    }
  }


  /* on affiche le tableau */
  printf("NB PROIES (*): %d\nNB PREDATEURS (0): %d\n",nbproie,nbpred);
  printf("\n+");  for(i=0;i<SIZE_Y;i++){printf("-");}  printf("+\n");
  for(i=0;i<SIZE_X;i++){
    printf("|");
    for(j=0;j<SIZE_Y;j++){
      printf("%c",ecosys[i][j]);
    }
    printf("|");
    printf("\n");
  }
  printf("+");  for(i=0;i<SIZE_Y;i++){printf("-");}  printf("+\n");
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    assert(la);
    Animal *pa = la;
    while (pa!=NULL){
      if(pa->dir[0]!=0){
        if(pa->dir[0]==1){
          if(pa->x != 0){
            pa->x+=-1;
          }
          else pa->x=SIZE_X-1;
        }
        else //if(pa->dir[0]==-1){
          {
          if(pa->x!=SIZE_X-1){
            pa->x+=1;
          }
          else pa->x=0;
        }
      }
      if(pa->dir[1]!=0){
        if(pa->dir[1]==1){
          if(pa->y != 0){
            pa->y+=-1;
          }
          else pa->y=SIZE_Y-1;
        }
        else //if(pa->dir[1]==-1){
          {
          if(pa->y!=SIZE_Y-1){
            pa->y+=1;
          }
          else pa->y=0;
        }
      }
      if(rand()/RAND_MAX<p_ch_dir){
        pa->dir[0] = rand() % 3 - 1;
        pa->dir[1] = rand() % 3 - 1;
      }
      pa = pa->suivant;
    }
    return;
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal * pa = *liste_animal;
  while(pa!=NULL){
    if((rand()*1.0)/RAND_MAX<p_reproduce){
      pa->energie = (pa->energie)/2.0;
      ajouter_animal((pa->x),(pa->y),(pa->energie),liste_animal);
    }
    pa=pa->suivant;
  }
  return;
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
  Animal * pa = *liste_proie;
  while (pa!=NULL){
    pa->energie -= 1;
    if(monde[pa->x][pa->y]>=0){
      pa->energie += monde[pa->x][pa->y];
      monde[pa->x][pa->y] = temps_repousse_herbe;
    }
    if(0.0 >= pa->energie){
      Animal * pb = pa;
      pa=pa->suivant;
      enlever_animal(liste_proie,pb);
      continue;
    }
    pa=pa->suivant;
  }
  reproduce(liste_proie,p_reproduce_proie);
  return;
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal * pa = l;
  while (pa != NULL)
  {
    if(pa->x == x && pa->y == y){
      return pa;
    }
    pa=pa->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal * pa = *liste_predateur;
  while (pa!=NULL){
    pa->energie -= 1;
    if(animal_en_XY(*liste_proie,pa->x,pa->y) != NULL){
      Animal * mourir = animal_en_XY(*liste_proie,pa->x,pa->y);
      pa->energie += mourir->energie;
      enlever_animal(liste_proie,mourir);
    }
    if(0.0 >= pa->energie){
      Animal * pb = pa;
      pa=pa->suivant;
      enlever_animal(liste_predateur,pb);
      continue;
    }
    pa=pa->suivant;
  }
  reproduce(liste_predateur,p_reproduce_predateur);
  return;

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for(int i=0;SIZE_X>i;i++){
    for(int j=0;SIZE_Y>j;j++){
      monde[i][j]+=1;
    }
  }
}

