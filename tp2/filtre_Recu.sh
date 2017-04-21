#! /bin/bash
# Estimateur fait pour bruit blanc !
Imgform2=("formes2bb30" "formes2pets1" "formes2bb40b" "formes2pets5" "formes2bb40" "formes2bb10b" "formes2bb50b" "formes2sp1" "formes2bb10" "formes2bb50" "formes2sp2" "formes2bb15b" "formes2bb67b" "formes2sp5" "formes2bb15" "formes2bb67" "formes2bb25b" "formes2bb90b" "formes2bb30b" "formes2bb90")

iteration=("1" "2" "4" "6" "10" "15")
K=("5" "10" "15" "20" "25")

mkdir images/filtre_adaptatif_recursif

for it in "${iteration[@]}"
do
  echo "iteration " $it
  for img in "${Imgform2[@]}"
  do
    for k in "${K[@]}"
    do
      echo "k " ${k}

      echo "image " $img
      ./bin/tp2_pourscript "images/"${img}".pgm" "images/filtre_adaptatif_recursif/"${img}"_"${it}"_"${k}".pgm" 2 ${it} ${k} 0 0
    done

  done

done
