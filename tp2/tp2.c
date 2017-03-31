#include "pgm.h"
#include <math.h>

double Wt(double **St, int x, int y, double k) {
  double res = (St[x+1][y]-St[x-1][y])*(St[x+1][y]-St[x-1][y]);
  res += (St[x][y+1]-St[x][y-1])*(St[x][y+1]-St[x][y-1]);
  res /= 2*k*k;
  res = exp(-res);
  return res;
}

void copy_image(double **origine, double **cible, int nl, int nc) {
  for (int i = 0; i < nl; i++) {
    for (int j = 0; j < nc; j++) {
      cible[i][j] = origine[i][j];
    }
  }
}

void filtre_adaptatif_recursif(char* imgOrigin, char* imgCible,
                              int iteration, double k) {
  /* Initialisation de la fonction... */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im1=NULL;
  im1=lectureimagepgm(imgOrigin,&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }
  double**im2=imuchar2double(im1,nl,nc);
  oldnl=nl; oldnc=nc;
  double **im3=alloue_image_double(nl,nc);
  /* im2 contient l'image d'origine à manipuler
   * im3 contient l'image finale à écrire dans l'image cible */

  double **St0 = alloue_image_double(nl,nc);
  copy_image(im2, St0, nl, nc); // Signal au temps t
  double **St1 = alloue_image_double(nl,nc); // Signal au temps t+1
  for (int t = 1; t < iteration; t++) {
    for (int x = 2; x < nl-2; x++) {
      for (int y = 2; y < nc-2; y++) {
        double numerateur = 0;
        double denominateur = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            numerateur += Wt(St0, x+i, y+j, k)*St0[x+i][y+j];
            denominateur += Wt(St0, x+i, y+j, k);
          }
        }
        St1[x][y] = numerateur/denominateur;
      }
    }
    copy_image(St1, St0, nl, nc);
  }
  copy_image(St1, im3, nl, nc);

  ecritureimagepgm(imgCible,crop(imdouble2uchar(im3,nl,nc),0,0,oldnl,oldnc),oldnl,oldnc);
}

int main (int ac, char **av) {
  if (ac < 3) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
  int iteration = 20;
  double k = 3;
  filtre_adaptatif_recursif(av[1], av[2], iteration, k);
  return EXIT_SUCCESS;
}
