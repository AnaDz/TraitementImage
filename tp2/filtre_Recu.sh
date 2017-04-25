#! /bin/bash

Imgform2=("formes2bb30" "formes2bb40b" "formes2bb40" "formes2bb10b" "formes2bb50b" "formes2bb10" "formes2bb50" "formes2bb15b" "formes2bb67b" "formes2bb15" "formes2bb67" "formes2bb25b" "formes2bb90b" "formes2bb30b" "formes2bb90")

iteration=("1" "2" "4" "6" "10" "15")
K=("5" "10" "15" "20" "25")
res=0
let "moyenne = 0"

mkdir images/filtre_adaptatif_recursif

for k in "${K[@]}"
do
  echo "k = " ${k}
  for it in "${iteration[@]}"
  do
    #echo "iteration = " $it
    for img in "${Imgform2[@]}"
    do
      ./bin/tp2_pourscript "images/"${img}".pgm" "images/filtre_adaptatif_recursif/"${img}"_"${it}"_"${k}".pgm" 2 ${it} ${k} 0 0
      str="${str} images/filtre_adaptatif_recursif/"${img}"_"${it}"_"${k}".pgm"
    done
    ./bin/PNSR "images/formes2.pgm" $str
    str=""
  done
done
