#!/bin/bash

blue='\033[0;34m'
NC='\033[0m' # No Color

prereq() {
  echo -e "[${blue}Installing prerequisites${NC}]"
  sudo apt-get update
  sudo apt-get -y install python2.7-dev build-essential  libtool cmake
}



nxp() {
echo -e "[${blue}Downloading NXP Reader Library${NC}]"
  wget https://cache.nxp.com/documents/software/sw3693.zip -O nxp.zip
  unzip -o nxp.zip
  value=$(cat licencefile.txt)
value=$(cat licencefile.txt)
if (whiptail --title "Please read and accept the NXP NFC Reader Libary greement" --yesno --yes-button "accept" --no-button "reject" --scrolltext "$value" 0 0) then
		echo "Setup Continues"
else
	echo "Setup Aborted because of Licence Agreement"
	exit
fi

  cd build
  cmake ..
  make -j4 NxpRdLibLinuxPN512
  cd ..
  OPT="" CFLAGS="-lpthread -lrt -std=gnu99" python wrapper.py build
  cp build/lib.linux-armv7l-2.7/nxppy.so nxppy.so
}

cleanup() {
  cd ..
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

