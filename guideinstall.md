## Installing Geant4 on Linux (Extended Tutorial)

![Geant4](https://custom-icon-badges.herokuapp.com/badge/-Geant4-lightgrey?logo=g4logo)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white&style=flat)

The goal of this guide is to make it clear how to finish a standard installation of Geant4 Simulation Toolkit on Linux based on Geant4 User Docs. 

For troubleshooting, please check [this page](https://araujoarthur.github.io/geant4-learning-resources/troubleshooting)

---
## Step 1 - Dowloading and Extracting the Source Code:
<details><summary>Details</summary>
<p>
The first step is to get Geant4's source code from their [official website](https://geant4.web.cern.ch/support/download).

After you have it on your computer, open your terminal and type[^1]:
[^1]: Please note that it won't work on non-english systems. To make it work, change `Documents` to whatever it means in you system's language.
```bash
    cd && mkdir ~/Documents/Geant4 -p && cd ~/Documents/Geant4
```
If you run `pwd` on your terminal, you should see something like[^2]:
[^2]:If you don't, please go back and check what went wrong.

```bash
/home/YOUR-USERNAME/Documents/Geant4
```
If you reached this directory, you can run[^3]:

```bash
cp ~/Downloads/geant4-v11.0.2.tar.gz . && tar -xf geant-v11.0.2.tar.gz
```
Here you must have in your `home/YOUR-USERNAME/Geant4` folder a file called `geant4-v11.0.2.tar.gz` and a folder called `geant4-v11.0.2`. Create a new folder called `geant4-v11.0.2-install`
[^3]:If you are trying to install another version instead 11.0.2, change `v11.0.2` to your version. In the next commands.

</p>
</details>



---
Go back to [main page](https://araujoarthur.github.io/geant4-learning-resources/).