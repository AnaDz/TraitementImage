#include "pgm.h"


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

int main (int ac, char **av) {
  if (ac < 3) {printf("Usage : %s entree sortie \n",av[0]); exit(1); }
  int n = 3;
  median_filter(av[1], av[2], n);

}
