#!/bin/bash
while read line
do
    name=$line
    to_download="https://my.pgp-hms.org/profile/"$line
    echo "to download ${to_download}"
    curl $to_download >> "../in/PGP-participants/"$name".html"
done < $1
