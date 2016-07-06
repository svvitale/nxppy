#!/bin/bash

blue='\033[0;34m'
NC='\033[0m' # No Color

prereq() {
  echo -e "[${blue}Installing prerequisites${NC}]"
  sudo apt-get update
  sudo apt-get -y install python2.7-dev build-essential cmake
}



nxp() {
echo -e "[${blue}Downloading NXP Reader Library${NC}]"
  wget https://nxp.box.com/shared/static/xxuwpzh2ztl63b8ujsclg5wqsmlxfmw1.zip -O nxp.zip
  unzip -o nxp.zip


  cd build
  cmake ..
  make NxpRdLibLinuxPN512
  cd ..
}

cleanup() {
  rm -rf *.zip *.gz *.deb
}

all() {
  prereq
  nxp
  cleanup
}

if [[ $# -eq 0 ]]; then
  all
else
  $@
fi

