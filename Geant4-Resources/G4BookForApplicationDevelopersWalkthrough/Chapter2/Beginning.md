# Chapter 2: GEANT4 Basics
Reference file in: [chapter2.cc](https://github.com/araujoarthur/geant4-learning-resources/blob/main/Geant4-Resources/G4BookForApplicationDevelopersWalkthrough/Chapter2/chapter2.cc)

**DISCLAIMER**: Most of this text is raw text from [Geant4 Docs: Book For Application Developers](https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/fo/BookForApplicationDevelopers.pdf). Some parts are extended explanations, in-place explanations, and code examples.

#### Toolkit Headers
```cpp
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
```

#### User Defined Headers

```cpp
#include "ExG4DetectorConstruction01.hh"
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Example name**. could be anything else. What really matters is its contents Inside the above file there should be a class derived from `G4VUserDetectorConstruction` and this class is where the user describes the entire detector setup, including its geometry, materials used to construct, definition of sensitive regions and the readout schemes of the sensitive regions (?).

```cpp
#include "ExG4PhysicsList00.hh"
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Inside the above file there's a class derived from `G4VUserPhysicsList` which requires user to define the particles used in the simulation and all physics processess to be simulated. Users can override default implementation for range cuts of the particles (Check for range cuts after).

```cpp
#include "ExG4ActionInitialization01.hh"
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Inside the above file there's a class derived from `G4VUserActionInitialization` which requires the user to define:
- User action classes (next sec) that are invoked during the simulation which includes one mandatory user action to define the primary particles.

### The Main Function

```cpp
int main()
{
    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(); // Line 12
```

> **Note**
> For auto keyword check  [C++ Reference](https://en.cppreference.com/w/cpp/language/auto).

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`G4RunManager` is ___the first thing___ a `main()` must construct and is the __only__ manager class in G4's Kernel which should be explicitly constructed in application the(user's) main. `G4RunManager` controls the flow of the application and manage the event loops within a run. *Line 12* instantiates `G4RunManager` Object of [concrete type](https://en.cppreference.com/w/cpp/language/abstract_class#Explanation) `G4MTRunManager` if G4 Library was build for MT support or `G4RunManager` otherwise. Other major classes are created with `G4RunManager` and deleted when `G4RunManager` is deleted. The run manager is also responsible for managing initialization procedures,  including methods in the user initialization classes. Through these the run manage must be given all the information necessary to build and run a simulation, including:

1. How Detector should be constructed (`ExG4DetectorConstruction01`)
2. All the particles and all the physics processes to be simulated (`ExG4PhysicsList00`)
3. How the primary particle(s) in an event should be produced (`ExG4ActionInitialization01`)
4. any additional class needed for the simulation to work.

#### User Initializations

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;All _User Initializations_ are objects built from classes that inherits from any of the Toolkit's base classes. The initialization scheme below returns a pointer to the created object to the `runManager`.

```cpp
    runManager->SetUserInitialization(new ExG4DetectorConstruction01); // Creates an object to specify Detector Geometry
    runManager->SetUserInitialization(new ExG4PhysicsList00); // Create an object to specify physics processes
    runManager->SetUserInitialization(new ExG4ActionInitialization01); // Create an object to specify primary particle
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;These three classes are mandatory and must derive from the [abstract](https://en.cppreference.com/w/cpp/language/abstract_class#Explanation) base classes:

- G4VUserDetectorConstruction
- G4VUserPhysicsList
- G4VUserActionInitialization

> **Warning**
> THERE IS NO DEFAULT BEHAVIOR FOR THESE CLASSES

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`G4RunManager` is responsible of checking for the existence of these three mandatory classes every time `Initialize()` and `beamOn()` are invoked. The class derived from `G4VUserActionInitialization` should include at least one mandatory user action class `G4VUserPrimaryGeneratorAction`, which requires that the initial event state be defined. An example of ActionInitialization child is given in [`ExG4ActionInitialization.cc`](https://github.com/araujoarthur/geant4-learning-resources/blob/main/Geant4-Resources/G4BookForApplicationDevelopersWalkthrough/Chapter2/ExG4ActionInitialization.cc).

#### `runManager` initialization

```cpp
    // Initialize G4 Kernel
    runManager->Initialize(); // Performs detector construction, creates physics processes and calculate crosssections, setting up the run.
```

#### The `G4UImanager` pointer

The `G4UImanager` is an example of manager class which is created with runManager.

```cpp
    // Get the pointer to the UI manager
    G4UImanager* UI = G4UImanager::GetUIpointer(); // Take a pointer to the interface manager to allow the user to issue commands.
```
Sending commands to __Intercomms__ to set verbosities (more on that later).
```cpp
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->AppliCommand("/tracking/verbose 1");
```
#### Starting the run with `beamOn()` method.

```cpp
// Start a run
int numberOfEvents = 3;
runManager->beamOn(numberOfEvent); // This line begins a RUN of three sequentially processed events.
```

```cpp
 // Job termination
    delete runManager;
    return 0;
}
```
### Final Questions:

- What is a run?
- What is an event?
- What is an user action?
- What is an event action?


### Full Code

```cpp
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"

#include "ExG4DetectorConstruction01.hh"
#include "ExG4PhysicsList00.hh"
#include "ExG4ActionInitialization01.hh"

int main()
{
    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(); 

    runManager->SetUserInitialization(new ExG4DetectorConstruction01); 
    runManager->SetUserInitialization(new ExG4PhysicsList00); 
    runManager->SetUserInitialization(new ExG4ActionInitialization01);


    // Initialize G4 Kernel
    runManager->Initialize();

    // Get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer(); 

    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->AppliCommand("/tracking/verbose 1");

    // Start a run
    int numberOfEvents = 3;
    runManager->beamOn(numberOfEvent);

    // Job termination
    delete runManager;
    return 0;
}
```