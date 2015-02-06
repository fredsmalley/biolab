#!/bin/bash
DOWNLOAD_DIR="."
# html -> xml
pre_processing() {
  for f in $(ls ${DOWNLOAD_DIR}/*.html)
  do
    tidy -asxml $f > ${f}.xml
  done
}

pre_processing
