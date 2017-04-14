#include "pgm.h"
#include <math.h>


double ConvolutionMasque(double** image, double filtre[3][3], int x, int y, int nl, int nc) {
  double somme=0;
  for(int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      somme += image[(x+i+nl)%nl][(y+j+nc)%nc]*filtre[1+i][1+j];
    }
  }

  return somme;
}

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

int median_filter(char* imgOrigin, char*imCible, int n){
  int nL, nC;
  unsigned char **imO = NULL, **imC = NULL;

  imO = lectureimagepgm(imgOrigin, &nL, &nC);
  if(imO == NULL){
    puts("Lecture image impossible");
  }
  double** im1 = imuchar2double(imO, nL, nC); // image bruitée
  double** im2 = alloue_image_double(nL, nC);  // image débrutée

/*  for(int i=0;i<nL;i++){
    for(int j=0; j<nC;j++){
      printf("%d | ",(int) im1[i][j]);
    }
    printf("\n");
  }*/

  int histograme[256];

  int cumul = 0;
  int ind = 0;


/* recopie la bordure */
  for (int i=0;i<n; i++){
    for (int j=0; j<nC; j++){
      im2[i][j] = im1[i][j];
      im2[nL-1-i][j] = im1[nL-1-i][j];
    }
  }

  for (int i=0;i<n; i++){
    for (int j=0; j<nL; j++){
      im2[j][i] = im1[j][i];
      im2[j][nC-1-i] = im1[j][nC-1-i];
    }
  }


  for(int i=n; i<(nL-n); i++){
    //premier point : n
    for(int a=0; a<256; a++){
      histograme[a] = 0;
    }
  //  fprintf(stderr, "histo à 0\n" );
    for(int j=i-n; j<i+n+1 ; j++ ){
      for(int k=0; k<2*n+1; k++){
        histograme[(int) im1[j][k]]++;
      }
    }


//    cumul = histograme[0];
    cumul = 0;
    ind = 0;
    while(cumul<(2*n*n + 2*n) && ind<256){
      cumul += histograme[ind];
      ind++;

    }

//    fprintf(stderr, "ind : %d\n", ind-1 );
    im2[i][n] = ind-1;

    // les autres points de la ligne
    for(int j=n+1; j<nC-n; j++){
      // on retire la premiere colonne de l'ancien masque
      for(int k=i-n; k< i+n+1; k++){
        histograme[(int) im1[k][j-(n+1)]]--;
        histograme[(int) im1[k][j+n]]++;
      }

// recalcul de cumul
      cumul = 0;
      ind = 0;
      while(cumul<(2*n*n + 2*n) && ind<254){
        cumul += histograme[ind];
        ind++;
      }
      im2[i][j] = ind-1;
    }

  }

  ecritureimagepgm(imCible,imdouble2uchar(im2,nL,nC),nL,nC);

  return EXIT_SUCCESS;
}

double EstimationBruit(char* imgOrigin, int t, double p){
  /* TODO : prendre les bords en compte ! */
  int nL, nC;
  unsigned char **imO = NULL;
  imO = lectureimagepgm(imgOrigin, &nL, &nC);
  if(imO == NULL){
    puts("Lecture image impossible");
  }

  int* histograme = malloc(256*256*sizeof(int));
  for (int k=0; k<256*256;k++){
    histograme[k] = 0;
  }
  double variance = 0;
  double n = (double)(2*t+1)*(2*t+1);
  double moyenne = 0;
  double** im1 = imuchar2double(imO, nL, nC);
  double** im2 = alloue_image_double(nL, nC);  // image avec convo
  double  passe_haut[3][3] = {{0,-1,0},{-1,5,-1},{0,-1,0}};
  for (int x = 0; x < nL; x++) {
    for (int y = 0; y < nC; y++) {
      im2[x][y] = ConvolutionMasque(im1, passe_haut, x, y, nL, nC);
    }
  }


  for (int x=t; x<nL-t; x++){
    for (int y=t; y<nC-t; y++){
      variance = 0;
      moyenne = 0;
      //fprintf(stderr, "image %f \n", im2[x][y] );
      for(int i=x-t; i<x+t; i++){
        for(int j = y-t; j<y+t; j++){
          if(im2[i][j] > 255){
            im2[i][j] = 255;
          } else if(im2[i][j] <0){
            im2[i][j] = 0;
          }
          variance += im2[i][j]*im2[i][j];
          moyenne += im2[i][j];
        }
      }

      variance = (variance/n);
      variance -= moyenne*moyenne/(n*n);
      histograme[(int) variance]++;
    }
  }
  int cumul = histograme[0];
  int taux = (int) (p*(nL-2*t)*(nC-2*t)/100);
  int res = 1;
  while (cumul<taux && res<256*256) {
    cumul += histograme[res];
    res++;
  }
  return 1.13*res;
}


int main (int ac, char **av) {
  if (ac < 3) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
//  int n = 3;
//  median_filter(av[1], av[2], n);

  double bruit = EstimationBruit(av[1], 10, 0.5);
  fprintf(stdout, "bruit : %f \n", bruit);
/*
  int iteration = 20;
  double k = 3;
  filtre_adaptatif_recursif(av[1], av[2], iteration, k);*/
  return EXIT_SUCCESS;
}
