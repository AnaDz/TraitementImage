#! /bin/bash
# Estimateur fait pour bruit blanc !
Imgform2=("formes2bb30" "formes2pets1" "formes2bb40b" "formes2pets5" "formes2bb40" "formes2bb10b" "formes2bb50b" "formes2sp1" "formes2bb10" "formes2bb50" "formes2sp2" "formes2bb15b" "formes2bb67b" "formes2sp5" "formes2bb15" "formes2bb67" "formes2bb25b" "formes2bb90b" "formes2bb30b" "formes2bb90")

Tailles=("3" "5" "10" "15")

mkdir images/median

mkdir images/median/forme2
for taille in "${Tailles[@]}"
do
  echo "taille " $taille
  for img in "${Imgform2[@]}"
  do
    echo "image " $img
    ./bin/tp2_pourscript "images/"${img}".pgm" "images/median/"${img}"_"${taille}".pgm" 1 ${taille} 0 0 0
    echo "PNSR "
    ./bin/PNSR "images/formes2.pgm" "images/median/"${img}"_"${taille}".pgm"
  done

done
