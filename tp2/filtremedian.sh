#! /bin/bash
# Estimateur fait pour bruit blanc !
Imgform2=("formes2bb40" "formes2bb10")

Tailles=("3")

mkdir images/comparaison
mkdir images/comparaison/median

for img in "${Imgform2[@]}"
do
  for taille in "${Tailles[@]}"
  do
    ./bin/tp2_pourscript "images/"${img}".pgm" "images/comparaison/median/"${img}"_"${taille}".pgm" 1 ${taille} 0 0 0 >> images/comparaison/median/tempsCPUmed.txt
  done

done

echo "PNSR" >> images/comparaison/median/tempsCPUmed.txt
for img in "${Imgform2[@]}"
do
  echo "image " $img
  for taille in "${Tailles[@]}"
  do
    ./bin/PNSR "images/median/forme2/"${img}"_"${taille}".pgm" "images/formes2.pgm" >> images/comparaison/median/tempsCPUmed.txt
  done

done
