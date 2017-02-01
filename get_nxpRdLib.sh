#!/bin/bash

blue='\033[0;34m'
NC='\033[0m' # No Color

nxp() {
  if [[ -d "nxp" ]]; then
    echo -e "NXP Reader Library found, skipping download"
  else
    echo -e "[${blue}Downloading NXP Reader Library${NC}]"
    wget https://nxp.box.com/shared/static/xxuwpzh2ztl63b8ujsclg5wqsmlxfmw1.zip -O nxp.zip
    unzip -q -o -d nxp nxp.zip
    rm nxp.zip
  fi

  rm -rf nxp/build/*
  pushd nxp/build > /dev/null
  CFLAGS=-fPIC cmake ..
  make NxpRdLibLinuxPN512
  popd > /dev/null
}

cleanup() {
  rm -rf *.zip *.gz *.deb
}

all() {
  nxp
  cleanup
}

if [[ $# -eq 0 ]]; then
  all
else
  $@
fi
