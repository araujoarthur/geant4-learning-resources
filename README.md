# Geant4 Learning Resources
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white&style=flat)
![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white&style=flat)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black&style=flat)
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white&style=flat)

## General Description
This is a repository with stuff I made while learning Geant4 Application Development and the C++ Programming Language. Further information not detailed as comments inside the source files can be found in:
 - [Introduction to Geant4](https://geant4-userdoc.web.cern.ch/UsersGuides/IntroductionToGeant4/html/index.html)
 - [Geant4 User's Guide: For Application Developers](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/index.html)
 - [Geant4 User's Guide: For Toolkit Developers](https://geant4-userdoc.web.cern.ch/UsersGuides/ForToolkitDeveloper/html/index.html)
 - [Geant4 Physics Reference Manual](https://geant4-userdoc.web.cern.ch/UsersGuides/PhysicsReferenceManual/html/index.html)
 - [Geant4 Physics List Guide](https://geant4-userdoc.web.cern.ch/UsersGuides/PhysicsListGuide/html/index.html)
 - [C++ Reference](https://en.cppreference.com/w/)
 - [C Standard Library Reference](https://en.cppreference.com/w/c/header)
 - C Standard ([Older](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf)) ([Newer](https://www.iso.org/standard/74528.html))

## `compile.sh`
### Introduction
Using this ShellScript one should be able to compile every basic and avanced example in Geant4's examples folder.  In order to do that, place it inside the same folder where the source code for examples are found and run `. compile.sh`.

### How does it work
The script will prompt for installation path to init ENVIRONMENT VARIABLES required by Geant4 to compile and run examples. It will also ask for the name of the source code file containing the `int main{}` function (Usually it is `exampleB1`, `exampleB2a`, `exampleB2b`, etc) but may differ in advanced examples. It will automatically create and go to directory ./build, then it will automatically generate build tools and compile the example.

### Disclaimer

 - This ShellScript was NOT tested against extended examples, but should work just fine with advanced and basic ones. 
 - This ShellScript was created to work on LINUX environments and was tested in Ubuntu 22.04 LTS using a standard installation of Geant4 v11.0.2 based on [Geant4 Installation Guide doc Rev6.0](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/installguide.html#on-unix-platforms) using `-DGEANT4_USE_QT=ON`, `-DGEANT4_BUILD_MULTITHREADED=ON`, `-DGEANT4_INSTALL_DATA=ON` flags. Although it could work in previous and future versions (if folder structure don't change), there's no warranty that it will work.
 - This ShellScript is meant to make it easy to compile your first examples and should be treated as a training-wheel you want to get rid of and not get used to. You are strongly encouraged to read the [Geant4 Documentation](https://geant4.web.cern.ch/support/user_documentation), [CMake Documentation](https://cmake.org/documentation/) and [Make Documentation](https://www.gnu.org/software/make/manual/make.html).

