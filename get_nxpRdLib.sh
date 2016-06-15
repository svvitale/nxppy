#!/bin/bash

blue='\033[0;34m'
NC='\033[0m' # No Color

prereq() {
  PREREQS="build-essential cmake $1"
  
  if dpkg -l $PREREQS > /dev/null 2>&1; then
    echo -e "Prerequisites already installed: $PREREQS"
  else
    echo -e "[${blue}Installing prerequisites${NC}]"
    sudo apt-get update
    sudo apt-get -y install $PREREQS
  fi
}

nxp() {
  if [[ -d "nxprdlib" ]]; then
    echo -e "NXP Reader Library found, skipping download"
  else
    echo -e "[${blue}Downloading NXP Reader Library${NC}]"
    wget https://cache.nxp.com/documents/software/sw3693.zip -O nxp.zip
    unzip -o nxp.zip
  fi

  cd build
  cmake ..
  make NxpRdLibLinuxPN512
  cd ..
}

cleanup() {
  rm -rf *.zip *.gz *.deb
}

all() {
  prereq $@
  nxp
  cleanup
}

if [[ $# -eq 0 ]]; then
  all
else
  $@
fi

