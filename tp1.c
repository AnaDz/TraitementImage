#include "pgm.h"

#include <math.h>
#include <time.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif



float FFTGauss(int u, int v, int N, int M) {
  float sigma = 2;
  float res ;
  float ufloat = (float)u;
  float vfloat = (float)v;
  float Nfloat = (float)N;
  float Mfloat = (float)M;
  res = -2*pow((float)M_PI,2)*pow(sigma,2);
  float u1 = (2*ufloat-Nfloat)/(2*Nfloat);
  float v1 = (2*vfloat-Mfloat)/(2*Mfloat);
  res = res * (pow(u1,2) + pow(v1,2)) ;
  res = exp(res);
  return res;
}

float ConvoGauss(double** image, int x, int y, int nl, int nc) {
  float sigma = 2;
  int n = 5;
  int m = 5;
  float boucle = 0;
  float res = 0;
  for (int i = -n; i<=n; i++) {
    boucle = 0;
    for (int j = -m; j<=m; j++) {
      boucle = boucle + exp(-j*j/(2*sigma*sigma)) * image[(x+i+nl)%nl][(y+j+nc)%nc];
    }
    res = res + boucle * exp(-i*i/(2*sigma*sigma));
  }
  res = res/(2*M_PI*sigma*sigma);
  return res;
}

void lissage_temporel(char* imgOrigin, char* imgCible){
  int nb,nl,nc, oldnl,oldnc; // Nombre lignes, nombre colonnes, ancien nombre lignes, ancien nombre colonnes
  unsigned char **im2=NULL,** im1=NULL;
  double** im4,** im5, ** im6, ** im7, **im8, **im9,**im10;

	/* Lecture d'une image pgm dont le nom est passe sur la ligne de commande */
  im1=lectureimagepgm(imgOrigin,&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }

  // Passage en réels
  double**im3=imuchar2double(im1,nl,nc);
  oldnl=nl; oldnc=nc;
	/*  la fft demande des puissances de 2. On padde avec des 0, mais les dimensions nl et nc changent */
  im7=padimdforfft(im3,&nl,&nc); // Partie réelle de l'image pour la FFT
  /*
	On peut aussi directement utiliser
	im7=padimucforfft(im1,&nl,&nc);
	sans convertir im1 en image de réels
  */

  /* Creation des images pour les parties reelles et imaginaires des fft  */
  im4=alloue_image_double(nl,nc); // Partie imaginaire de l'image pour la FFT
  im5=alloue_image_double(nl,nc); // Partie réelle de l'image après FFT
  im6=alloue_image_double(nl,nc); // Partie imaginaire de l'image après FFT

	/* Calcul de la fft de im7,im4  */
  fft(im7,im4,im5,im6,nl,nc);
  fftshift(im5,im6, im7,im4, nl,nc);
  // Multiplication par la FFT de la gaussienne

  for (int i=0 ; i<nl; i++){
    for (int j=0; j<nc; j++){
      im7[i][j] = im7[i][j]*FFTGauss(i, j, nl, nc);
      im4[i][j] = im4[i][j]*FFTGauss(i, j, nl, nc);
    }

  }
  fftshift(im7,im4, im5,im6, nl,nc);
	/* Creation des images pour les parties reelles et imagianires des fft inverses */
  im9=alloue_image_double(nl,nc); // Partie réelle de l'image après FFT et FFT inverse
  im10=alloue_image_double(nl,nc); // Partie imaginaire de l'image après FFT et FFT inverse
        /* Calcul de la fft inverse de im5,im6 */
  ifft(im5,im6,im9,im10,nl,nc);

	/* Conversion en entier8bits de la partie reelle de la fftinverse,
	   Suppresion des 0 qui ont servi a completer en utilisant la fonction crop
	   Sauvegarde au format pgm de cette image qui doit etre identique a 'linverse video
	   car on a realise la suite fftinv(fft(image))*/
  ecritureimagepgm(imgCible,crop(imdouble2uchar(im9,nl,nc),0,0,oldnl,oldnc),oldnl,oldnc);
  im2 = imdouble2uchar(im9,nl,nc);
  int newnl, newnc;
  unsigned char** im11 = lectureimagepgm("images/formes1sp.pgm",&newnl,&newnc);
  double pr = psnr(im2, im1, newnl, newnc) ;
  printf(" PSNR : %f\n", pr);
}

void lissage_spatial(char* imgOrigin, char* imgCible) {
  /* Même début que le lissage */
  int nb,nl,nc, oldnl,oldnc;
  unsigned char **im2=NULL,** im1=NULL;
  double** im4,** im5, ** im6, ** im7, **im8, **im9,**im10;

  im1=lectureimagepgm(imgOrigin,&nl,&nc);
  if (im1==NULL)  { puts("Lecture image impossible"); exit(1); }

  double**im3=imuchar2double(im1,nl,nc);
  oldnl=nl; oldnc=nc;
  im7=padimdforfft(im3,&nl,&nc); // Image
  im8=alloue_image_double(nl,nc);
  /* Calcul de la convolution */
  for (int i=0; i<nl; i++) {
    for (int j=0; j<nc; j++) {
      im8[i][j] = ConvoGauss(im7, i, j, nl, nc);
    }
  }

  ecritureimagepgm(imgCible,crop(imdouble2uchar(im8,nl,nc),0,0,oldnl,oldnc),oldnl,oldnc);
  im2 = imdouble2uchar(im8,nl,nc);
  int newnl, newnc;
  unsigned char** im11 = lectureimagepgm("images/formes1sp.pgm",&newnl,&newnc);
  double pr = psnr(im2, im11, newnl, newnc) ;
  printf(" PSNR : %f\n", pr);
}

int main (int ac, char **av) {  /* av[1] contient le nom de l'image, av[2] le nom du resultat . */
  // Pas assez d'arguments
  if (ac < 3) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
  clock_t debut, fin;
  debut = clock();
  lissage_temporel(av[1], av[2]);
  fin = clock();
  printf("durée convolution spatiale : %f\n", ((double) fin-debut)/CLOCKS_PER_SEC);
  debut = clock();
  lissage_spatial(av[1], av[2]);
  fin = clock();
  printf("durée convolution temporelle : %f\n", ((double) fin-debut)/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}
