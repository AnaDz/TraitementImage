#! /bin/bash

Img2bb=("formes2bb30" "formes2bb40b" "formes2bb40" "formes2bb10b" "formes2bb50b" "formes2bb10" "formes2bb50" "formes2bb15b" "formes2bb67b" "formes2bb15" "formes2bb67" "formes2bb25b" "formes2bb90b" "formes2bb30b" "formes2bb90")
Img1pets=("formes1pets10" "formes1pets1" "formes1pets5")
Img2pets=("formes2pets1" "formes2pets5")
Img1sp=("formes1sp")
Img2sp=("formes2sp05" "formes2sp1" "formes2sp2" "formes2sp5")

patch=("10" "20" "30" "40" "50")
region=("1" "2" "3" "4" "5")
sigma=("1" "2" "4" "6" "8" "10" "20" "30" "40" "50" "70" "90" "110" "130" "150" "200" "300")

mkdir images/patch

for t in "${region[@]}"
do
  echo "t = " ${t}
  for r in "${patch[@]}"
  do
    echo "r = " ${r}
    for s in "${sigma[@]}"
    do
        #echo "sigma = " ${s}
      ./bin/tp2_pourscript "images/image_pour_patch.pgm" "images/patch/image_pour_patch_"${t}"_"${r}"_"${s}".pgm" 4 ${t} ${r} ${s} 0 0
      ./bin/PNSR "images/forme_pour_patch.pgm" "images/patch/image_pour_patch_"${t}"_"${r}"_"${s}".pgm"
    done
  done
done
