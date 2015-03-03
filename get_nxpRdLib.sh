#!/bin/bash

blue='\033[0;34m'
NC='\033[0m' # No Color

prereq() {
  echo -e "[${blue}Installing prerequisites${NC}]"
  sudo apt-get update
  sudo apt-get -y install libglib2.0 glib-networking-services libreadline6-dev libglib2.0-dev glib-networking-services python2.7-dev build-essential autoconf libtool
}

neardal() {
  echo -e "[${blue}Downloading NeardAL${NC}]"
  curl -L https://github.com/connectivity/neardal/archive/0.14.tar.gz | tar --overwrite -xz
  cd neardal-0.14

  echo -e "[${blue}Running autogen.sh${NC}]"
  ./autogen.sh

  echo -e "[${blue}Configuring NeardAL${NC}]"
  ./configure --prefix=/usr --sysconfdir=/etc --localstatedir=/var

  echo -e "[${blue}Building NeardAL${NC}]"
  make

  echo -e "[${blue}Installing NeardAL${NC}]"
  sudo make install

  cd ..
}

wiringpi() {
  echo -e "[${blue}Downloading wiringPi${NC}]"
  git clone git://git.drogon.net/wiringPi
  git reset --hard 72b2af231be337d45a557ce6ca3ed1eeb6675ffd

  echo -e "[${blue}Building and Installing wiringPi${NC}]"
  cd wiringPi
  ./build

  echo -e "[${blue}Running ldconfig${NC}]"
  sudo ldconfig

  cd ..
}

nxp() {
  echo -e "[${blue}Downloading NXP Reader Library${NC}]"
  wget http://www.nxp.com/redirect/explore-nfc-dev_latest -O nxp.zip
  unzip -o nxp.zip
  tar --overwrite -xzf neard-explorenfc_0.1.orig.tar.gz
  cd neard-explorenfc-0.1

  export WIRINGPI_CFLAGS=-I/usr/local/include
  export WIRINGPI_LIBS=-L/usr/local/lib\ -lwiringPi

  echo -e "[${blue}Running bootstrap${NC}]"
  ./bootstrap

  echo -e "[${blue}Configuring NXP Reader Library${NC}]"
  ./configure --prefix=/usr --sysconfdir=/etc

  echo -e "[${blue}Building NXP Reader Library${NC}]"
  cd nxprdlib
  make
}

all() {
  prereq
  neardal
  wiringpi
  nxp
}

if [[ $# -eq 0 ]]; then
  all
else
  $@
fi

