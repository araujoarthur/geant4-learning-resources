# Installing Geant4 on Linux (Extended Tutorial)

![Geant4](https://custom-icon-badges.herokuapp.com/badge/-Geant4-lightgrey?logo=g4logo)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white&style=flat)

The goal of this guide is to make it clear how to finish a standard installation of Geant4 Simulation Toolkit on Linux based on Geant4 User Docs. 

For troubleshooting, please check [this page](https://araujoarthur.github.io/geant4-learning-resources/troubleshooting)

---
### Step 1 - Dowloading and Extracting the Source Code.
<details><summary><img src="assets/arrow-down.svg"/> Details</summary>
<p>
The first step is to get Geant4's source code from their [official website](https://geant4.web.cern.ch/support/download).

After you have it on your computer, open your terminal and type[^1]:
[^1]: Please note that it won't work on non-english systems. To make it work, change `Documents` to whatever it means in you system's language.
```bash
    cd && mkdir ~/Documents/Geant4 -p && cd ~/Documents/Geant4
```
If you run `pwd` on your terminal, you should see something like[^2]:
[^2]: If you don't, please go back and check what went wrong.

```bash
/home/YOUR-USERNAME/Documents/Geant4
```
If you reached this directory, you can run[^3]:

```bash
cp ~/Downloads/geant4-v11.0.2.tar.gz . && tar -xf geant-v11.0.2.tar.gz
```
Here you must have in your `home/YOUR-USERNAME/Geant4` folder a file called `geant4-v11.0.2.tar.gz` and a folder called `geant4-v11.0.2`. Create a new folder called `geant4-v11.0.2-build` and change directory to it by running:
```bash
mkdir geant4-v11.0.2-build && cd geant4-v11.0.2-build
```

You're ready for Step 2.

[^3]: If you are trying to install another version instead 11.0.2, change `v11.0.2` to your version. In the next commands.
</p>
</details>
<br>

### Step 2 - Downloading and Installing Dependencies.
<details><summary><img src="assets/arrow-down.svg"/> Details</summary>
<p>

#### Dependency List
To successfuly compile and run examples in Geant4, you need to:

1. Prepare to build its libraries;
2. Actually build Geant4 libraries from source;
3. Prepare to build a Geant4 example, and
4. Actually build a Geant4 example.

To complete each task we need:

- **CMake**: Used to prepare build files for your environment using directives found in `CMakeLists.txt` files. This one is installed by running:

```bash
sudo apt-get install cmake
```
___

- **Compiler**: The binary that will translate our source code in build units and these in **S**hared **O**bjects (`.so`) (equivalent to **D**ynamic-**L**ink **L**ibrary (`.dll`) files in Windows). I usually install both `gcc`[^4] and `g++`[^5] (the one that better fit the compilation process for Geant4). Finally, to make sure we won't run into problems while compiling the source code and if we are in a Debian-based distribution of Linux, we could install those through `build-essential` package. If you are not in a Debian-based distribution of Linux, you might need to install each build-essential dependency separately.

<details><summary><img src="assets/arrow-down.svg"/> Command for Debian-based Distributions (such as Ubuntu, Linux Mint, elementaryOS, etc.)</summary>
<p>

```bash
sudo apt-get install build-essential 
```
</p>
</details>

<details><summary><img src="assets/arrow-down.svg"/> Command for non-Debian-based Distributions (Fedora, CentOS, etc.)</summary>
<p>

*I am not sure it will work, needs test. If you run into problem even using those, please [open an Issue](https://github.com/araujoarthur/geant4-learning-resources/issues)*
```bash
sudo [Package Tool Installation Command] libc6-dev libc-dev gcc g++ make
```
Package Tool Installation Commands:

| Distro      | Command |
| ----------- | ----------- |
| RHEL-Based  | `yum install` or `dnf install`      |
| Arch-Based | `pacman -S` |
| Debian-Based | `apt-get install` |

</p>
</details>

___

- **Graphical Interface**: Here we come to a point where this guide and your needs might diverge. I use as standard for visualization the `QT Interface`. You might want/need to use OpenGL, however I won't cover it[^6]. The graphical interface is used to check visualizations of the output of your simulations (instead of just data flowing in terminal) and to interact easily with the simulation via [Geant4 Intercomms](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/GettingStarted/graphicalUserInterface.html?highlight=intercoms)[^7]. To install the needed packages, run[^8]:

```bash
    sudo apt-get install mesa-common-dev qtbase5-dev qt3d5-dev libqt53dcore5 libqt53dextras5 libqt53dextras5
```

___

- **Expat XML Parser**: Dependency for CMake for XML Parsing. I don't really know why CMake uses Expat but even when installing cmake with `apt-get` I got the error of a missing Expat package, so I would also run the install command for this one as a backup[^9].

```bash
sudo apt-get install libexpat1-dev
```
With those installed, you should be ready for Step 3. (If you ran into problems, please [open an issue](https://github.com/araujoarthur/geant4-learning-resources/issues)).

[^4]: GNU C Compiler.
[^5]: GNU C++ Compiler.
[^6]: But I included a installation for Mesa3D packages as a backup. It also should include some qt5 packages that holds for QT Interface Installation.
[^7]: Note I said easily. It could be done without graphical interface.
[^8]: Actually, only mesa-common-dev should be necessary. I prefer to keep the others in command line just in case.
[^9]: Also, note that the dependency installed by `apt-get` for CMake is `libexpat1` and the backup added is `libexpat1-dev`.
</p>
</details>
<br>

### Step 3: Build Geant4
<details><summary><img src="assets/arrow-down.svg"/> Details</summary>
<p>
Now you should have all Geant4's dependencies and its dependencies' dependencies. ALso, if you didn't close your terminal since Step 1, you should be in `/home/YOUR-USER/Documents/Geant4/geant4-v11.0.2-build`. If you did close it, run:

```bash
cd ~/Documents/Geant4/geant4-v11.0.2-build
```

We must now prepare to build our Geant4 Source Code into Shared Objects. It can be done using CMake[^10][^11].

```bash
cmake -DCMAKE_INSTALL_PREFIX=~/Documents/Geant4/geant4-v11.0.2-install -DGEANT4_BUILD_MULTITHREADED=ON -DGEANT4_USE_QT=ON -DGEANT4_INSTALL_DATA=ON ~/Documents/Geant4/geant4-v11.0.2
```

<br>
<details><summary><img src="assets/info.svg"/> Understanding the command</summary>
<p>
The command that you just used has a syntax like:
    
```bash
cmake [OPTIONS] path/to/source
```

Where each option starting with `-D` is a *CMake's cache entry*. In this context, we can say those options are **flags**.
In the table below are the effects of the ones used here.
| FLAG | EFFECT |
|------|---------|
|`CMAKE_INSTALL_PREFIX` | Sets the installation path |
|`GEANT4_BUILD_MULTITHREADED` | Controls Multithread Support in this Geant4 build[^12] |
|`GEANT4_USE_QT` | Controls if QT Interface will be used in this Geant4 build |
|`GEANT4_INSTALL_DATA` | Controls if Geant4 will download and install its extra datasets |

You can check more about build flags [here](https://geant4-userdoc.web.cern.ch/UsersGuides/InstallationGuide/html/installguide.html#options-for-changing-the-compiler-and-build-flags).

</p>
</details>

Once the process is finished, you can actually build it:
```bash
make -j N
```
where N is the number of threads you want the compiler to use (the more you use, the faster it goes). Both this process and the former one can take a bit to complete.

Once it's finished, you can then run:

```bash
make install
```

If you had success in this last process, you have successfully built and installed Geant4 Simulation Toolkit.

<details><summary><img src="assets/info.svg"/> What if I installed and now want to add another build flag?</summary>
<p>
The `cmake` command also accepts the syntax:

```bash
cmake [OPTIONS] path/to/current-build
```
So, inside your build folder (`cd ~/Documents/Geant4/geant4-v11.0.2-build`), you can run:

```bash
cmake [OPTIONS-YOU-WANT-TO-CHANGE] .
```

Once finished, you can run `make -j N` and `make install` again and work with the tools you needed.
</p>
</details>

[^10]: Although CMake has a GUI mode, I only cover the Command Prompt way of creating build files.
[^11]: geant4-v11.0.2-install doesn't exist yet. It will be `make`'s job to create it.
[^12]: `GEANT4_BUILD_MULTITHREADED` is currently, by default, set to ON. I explicitly set it to on in case of future changes.
<p>
</details>

<br>


### Postinstall

<details><summary><img src="assets/stop.svg"/> Setting Geant4 Environment</summary>
<p>

Every time you open a new Terminal Window to compile and run your code you will need to setup the Geant4 Environment Variables[^13]. It can be done running the following command:

```bash
source ~/Documents/Geant4/geant4-v11.0.2-install/bin/geant4.sh
```

You can check for success with the command `env`, then looking for Geant4's Datasets as Environment Variables names.
</p>
</details>

[^13]: There are ways to set it permanently. I don't do it.
---
Go back to [main page](https://araujoarthur.github.io/geant4-learning-resources/).
