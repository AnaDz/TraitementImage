#include "pgm.h"

double PNSR(char* im1, char* im2){
  int l,c;
  unsigned char** im_1 = lectureimagepgm(im1, &l,&c);
  unsigned char** im_2 = lectureimagepgm(im2, &l,&c);
  return psnr(im_1,im_2, l, c);
}

int main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  // Pas assez d'arguments
  if (ac < 3) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
  double pnsr = PNSR(av[1], av[2]);
  printf("PNSR entre %s et %s : %f\n",av[1], av[2], pnsr );
}
