#!/bin/sh
if awk  '/\r$/{exit 0;} 1{exit 1;}' $1
then
    echo "is DOS"
fi
