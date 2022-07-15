#!/bin/bash
path="";
while [ ! -d "$path" ] || [ ! -e "${path}/bin/geant4.sh" ];
  do
  	read -p "Insert Geant4 Installation Path: " path
  done

curr_pwd=$(pwd)

source "${path}/bin/geant4.sh"

geantver=$(geant4-config --version)

g4libdir="${path}/lib/Geant4-${geantver}" 
read -p "Example name (as written in fileName): " exampleName

if [ -d $g4libdir ];
  then
    if [ ! -d "$(pwd)/build" ];
      then
        mkdir "build" && cd "build"
      else
        cd "build"
      fi
  	cmake -DGeant4_DIR=$g4libdir ..
    make $exampleName
  else
    echo "Couldn't find Geant4 Libraries"
    exit
fi



