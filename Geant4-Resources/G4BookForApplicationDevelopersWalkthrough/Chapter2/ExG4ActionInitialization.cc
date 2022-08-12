// Both user defined. Inherits from G4VUserActionInitialization and G4VUserPrimaryGeneratorAction respectively.
#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"

void ExG4ActionInitialization01::Build() const // Not sure if it must be the name. The skeleton for this class is in ExG4ActionInitialization.hh (where the inheritance is defined.)
{
    SetUserAction(new ExG4PrimaryGeneratorAction01);
}

/*
    G4UserPrimaryGeneratorAction is mandatory. It creates an istance of a primary particle generator.
    ExG4PrimaryGeneratorAction01 is an example of a user action class which is derivde from G4UserPrimaryGeneratorAction.

    There, the user must describe the initial state of the primary event. It has a public VIRTUAL (check C++ Reference) method called
    GeneratePrimaries() which is invoked at the beginning of EACH EVENT.

    Geant4 doesn't provide default behavior for generating a primary event.

    Geant4 Provides Additional Five User Hook Classes:
        G4UserRunAction (?)
        G4UserEventAction (?)
        G4UserStackingAction (?)
        G4UserTrackingAction (?)
        G4UserSteppingAction (?)

    These optional user action classes have several virtual methods which allow the specification of additional procedures
    at all levels of the simulation application.
*/

/*
    Final Questions:
    What is a primary event?
*/