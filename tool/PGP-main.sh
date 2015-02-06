#!/bin/bash

DOWNLOAD_DIR="../in/PGP-participants/"


# download participants' profiles
while read line
do
    name=$line
    to_download="https://my.pgp-hms.org/profile/"$line
    echo "to download ${to_download}"
    curl $to_download >> "../in/PGP-participants/"$name".html"
done < $1

# html -> xml
pre_processing() {
  for f in $(ls ${DOWNLOAD_DIR}/*.html)
  do
    tidy -asxml $f > ${f}.xml
  done
}

pre_processing
