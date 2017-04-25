#! /bin/bash
# Estimateur fait pour bruit blanc !
Img=("formes2bb30.pgm" "globulesbb50.pgm" "formes2bb40b.pgm" "formes2bb40.pgm"
"formes2bb10b.pgm" "formes2bb50b.pgm" "formes2bb10.pgm" "formes2bb50.pgm"
"formes2bb15b.pgm" "formes2bb67b.pgm" "formes2bb15.pgm" "formes2bb67.pgm"
"globulesbb10.pgm"  "formes2bb25b.pgm" "formes2bb90b.pgm"  "globulesbb25.pgm"
"formes2bb30b.pgm" "formes2bb90.pgm" "globulesbb26.pgm")
for img in "${Img[@]}"
do
  echo "image" $img
  ./bin/tp2_pourscript "images/"${img} "images/pasdesortie.pgm" 5 10 0.5 0

done
