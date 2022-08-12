#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"

// User defined (?)
#include "ExG4DetectorConstruction01.hh"
/*
    Example name. could be anything else. What really matters is its contents.
    Inside the above file there should be a class derived from G4VUserDetectorConstruction and this class is where the user describes the entire detector
    Setup, including its geometry, materials used to construct, definition of sensitive regions and the readout schemes of the sensitive regions(?)
*/

#include "ExG4PhysicsList00.hh"
/*
    Inside the above file there's a class derived from G4VUserPhysicsList which requires user to define the particles
    used in the simulation and all physics processess to be simulated.

    Users can override default implementation for range cuts of the particles (Check for range cuts after)
*/

#include "ExG4ActionInitialization01.hh"
/*
    Inside the above file there's a class derived from G4VUserActionInitialization which requires
    the user to define:
    User action classes (next sec) that are invoked during the simulation, which includes one mandatory user action to define the primary particles.
*/
int main()
{
    // Construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(); 
    // For auto keyword check on C++ Reference.
    /*  G4RunManager is THE FIRST THING a main() must do and is the only manager classe in G4 Kernel which should be
        Explicitly constructed in application (user's) main.

        G4RunManager controls the flow of the application and manage the event loops within a run.
        
        Line 12 instantiates G4RunManager Object of (concrete [Check C++ Reference]) type:
        G4MTRunManager if G4 Library was build for MT Support
        G4RunManager otherwise.

        Other major classes are created with G4RunManager and deleted when G4RunManager is deleted.

        The run manager is also responsible for managing initialization procedures, 
        including methods in the user initialization classes. Through these the run manager
        must be given all the information necessary to build and run a simulation, including:

        1. How Detector should be constructed (ExG4DetectorConstruction01)
        2. All the particles and all the physics processes to be simulated (ExG4PhysicsList00)
        3. How the primary particle(s) in an event should be produced (ExG4ActionInitialization01)
        and any additional class needed for the simulation to work.
    */

    // The initialized classes are (new Foo) are derived from TOOLKIT CLASSES
    // All initializations below pass a pointer to the runManager (verify later that the constructor returns a pointer(?))
    runManager->SetUserInitialization(new ExG4DetectorConstruction01); // Creates an object to specify Detector Geometry
    runManager->SetUserInitialization(new ExG4PhysicsList00); // Create an object to specify physics processes
    runManager->SetUserInitialization(new ExG4ActionInitialization01); // Create an object to specify primary particle
    /*
        These three classes are mandatory and must derive from the abstract (check C++ Reference) base classes:
        G4VUserDetectorConstruction
        G4VUserPhysicsList
        G4VUserActionInitialization

        !! THERE IS NO DEFAULT BEHAVIOR FOR THESE CLASSES !!

        G4RunManager is responsible of checking for the existence of these three mandatory classes every time Initialize() and beamOn() are invoked.

        The class derived from G4VUserActionInitialization should include at least one mandatory
        user action class G4VUserPrimaryGeneratorAction, which requires that the initial event state be defined.
    
        An example of ActionInitialization child is given in ExG4ActionInitialization.cc
    */


    // Initialize G4 Kernel
    runManager->Initialize(); // Performs detector construction, creates physics processes and calculate crosssections, setting up the run.


    // Get the pointer to the UI manager and set verbosities
    G4UImanager* UI = G4UImanager::GetUIpointer(); // Take a pointer to the interface manager to allow the user to issue commands.
    /*
        The line above is an example of manager class created together with run manager.
    */
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->AppliCommand("/tracking/verbose 1");

    // Start a run
    int numberOfEvents = 3;
    runManager->beamOn(numberOfEvent); // This line begins a RUN of three sequentially processed events.
    /*
        beamOn() may be invoked any number of times within main(). Each invocation represents a separate run.
        Once a run has begun neither the detector setup nor the physics processes may be changed (See Geant4 as a State-Machine)
        but those can be changed between runs.
    */

    // Job termination
    delete runManager;
    return 0;
}

/*
    Final questions:
    What is a run?
    What is an event?
    What is an user action?
    What is an event action?
*/