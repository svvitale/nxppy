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
  wget https://cache.nxp.com/documents/software/sw3693.zip -O nxp.zip
  unzip -o nxp.zip

value=$(cat NXP_NFC_Reader_Library_licencefile.txt)
if (whiptail --title "Please read and accept the NXP NFC Reader Libary greement" --yesno --yes-button "accept" --no-button "reject" --scrolltext "$value" 0 0) then
		echo "Setup Continues"
else
	echo "Setup Aborted because of Licence Agreement"
	exit
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
  prereq
  nxp
  cleanup
}

if [[ $# -eq 0 ]]; then
  all
else
  $@
fi

