#/usr/bin/sh
prog=gatest
conf=GAconfig
fecha=$(date '+%Y%m%d_%H%M%S')

date >./resultados/results_"$fecha".txt

for i in 1 2 3 4 5 6 7 8 9 10; do
  echo Executing run "$i" of "$prog" with configuration file "$conf"
  ./"$prog" >>./resultados/results_"$fecha".txt
  echo "************************************" >>./resultados/results_"$fecha".txt
  echo "------------------------------------" >>./resultados/results_"$fecha".txt
  echo "************************************" >>./resultados/results_"$fecha".txt
done
