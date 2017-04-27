#! /bin/bash

Img2bb=("formes2bb30" "formes2bb40b" "formes2bb40" "formes2bb10b" "formes2bb50b" "formes2bb10" "formes2bb50" "formes2bb15b" "formes2bb67b" "formes2bb15" "formes2bb67" "formes2bb25b" "formes2bb90b" "formes2bb30b" "formes2bb90")
Img1pets=("formes1pets10" "formes1pets1" "formes1pets5")
Img2pets=("formes2pets1" "formes2pets5")
Img1sp=("formes1sp")
Img2sp=("formes2sp05" "formes2sp1" "formes2sp2" "formes2sp5")

iteration=("2" "4" "5" "6" "7" "8" "10" "12" "14" "15" "16")
K=("60" "70" "80" "100" "120")

mkdir images/filtre_adaptatif_recursif

for k in "${K[@]}"
do
  echo "k = " ${k}
  for it in "${iteration[@]}"
  do
    #echo "iteration = " $it
    for img in "${Img2bb[@]}"
    do
      ./bin/tp2_pourscript "images/"${img}".pgm" "images/filtre_adaptatif_recursif/"${img}"_"${it}"_"${k}".pgm" 2 ${it} ${k} 0 0
      str="${str} images/filtre_adaptatif_recursif/"${img}"_"${it}"_"${k}".pgm"
    done
    ./bin/PNSR "images/formes2.pgm" $str
    str=""
  done
done
