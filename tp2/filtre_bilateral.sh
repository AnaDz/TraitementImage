#! /bin/bash
# Estimateur fait pour bruit blanc !
Imgform2=("formes2bb40" "formes2bb10")

sigma1=("3")
sigma2=("15")

mkdir images/comparaison/bilateral
for img in "${Imgform2[@]}"
do
  # echo "image " $img >> sortie/$img".txt"
  for sigmauno in "${sigma1[@]}"
  do
    # echo "sigma1" $sigmauno >> sortie/$img".txt"
    for sigmados in "${sigma2[@]}"
    do
      ./bin/tp2_pourscript "images/"${img}".pgm" "images/comparaison/bilateral/"${img}"_"${sigmauno}"_"${sigmados}".pgm" 3 ${sigmauno} ${sigmados} 0 0 >> images/comparaison/bilateral/comparaison.txt
    done
  done

done

echo "PNSR"
for img in "${Imgform2[@]}"
do
#  echo "image " $img >> sortie/$img".txt"
  for sigmaun in "${sigma1[@]}"
  do
#    echo "sigma1 " ${sigmaun} >> sortie/$img".txt"
    for sigmade in "${sigma2[@]}"
    do
      ./bin/PNSR "images/formes2.pgm" "images/comparaison/bilateral/"${img}"_"${sigmaun}"_"${sigmade}".pgm" >> images/comparaison/bilateral/comparaison.txt 
    done
  done

done
