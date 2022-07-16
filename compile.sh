#!/bin/bash
path="";
# Asks for the installation path until it's a valid one (rely on the existence of /bin/geant4.sh to validade the instalation path)
while [ ! -d "$path" ] || [ ! -e "${path}/bin/geant4.sh" ];
  do
  	read -p "Insert Geant4 Installation Path: " path
  done

# Run the ShellScript provided by Geant4 Collaboration to set environment variables
source "${path}/bin/geant4.sh"

# Asks the prompt for the geant4 version in order to build folders.
geantver=$(geant4-config --version)

# Build the lib folder as it should exist inside [INSTALL_PATH]/lib/Geant4-[VERSION]
g4libdir="${path}/lib/Geant4-${geantver}" 

# Asks for the source code filename.
read -p "Example name (as written in fileName): " exampleName

# Check if g4libdir is a valid directory.
if [ -d $g4libdir ];
  then
   # Check if there isn't a build folder yet. If it does exist, just change directory to /build. If it doesn't exist, create and change directory.
    if [ ! -d "$(pwd)/build" ];
      then
        mkdir "build" && cd "build"
      else
        cd "build"
      fi
    # Run cmake with g4libdir as path to Geant4 and using CMakeLists.txt from previous folder (in this context, the one before build)
  	cmake -DGeant4_DIR=$g4libdir ..
    make $exampleName
  else
    # Exits if the installation doesn't follow the standard required by this script. (It DOES NOT MEAN the installation is broken)
    echo "Couldn't find Geant4 Libraries"
    exit
fi



