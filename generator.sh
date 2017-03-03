#! /bin/bash
# A EXECUTER DANS LE DOSSIER VOULU
numImg=( "1" "5" "10")
sigma=(0.5 1 2 3 5 10)
mask=("1" "2" "3" "4" "5" "6" "10")
for t1 in "${numImg[@]}"
do
  for t2 in "${sigma[@]}"
  do
    for t3 in "${mask[@]}"
    do
      echo "image" $t1 "sigma" $t2 "masque" $t3
      ./bin/tp1_pourtest "images/formes1pets"${t1}".pgm" "images/determination_loi_W/"$t2"/temporel_pets"${t1}".pgm" "images/determination_loi_W/"$t2"/spacial_pets"${t1}"_masque"$t3"*"$t3".pgm" $t3 $t3 $t2
      ./bin/PNSR "images/determination_loi_W/"$t2"/temporel_pets"${t1}".pgm" "images/determination_loi_W/"$t2"/spacial_pets"${t1}"_masque"$t3"*"$t3".pgm" >> "resul.txt"

    done
  done
done
