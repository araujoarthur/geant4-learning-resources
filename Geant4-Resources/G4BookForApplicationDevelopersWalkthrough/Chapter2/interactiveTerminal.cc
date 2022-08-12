#include "G4RunManager.hh"
#include "G4UIManager.hh"

#include "G4UIExecutive.hh"

#include "ExG4DetectorConstruction01.hh"
#include "ExG4PhysicsList00.hh"
#include "ExG4PrimaryGeneratorAction01.hh"

int main()
{
    G4RunManager * runManager = new G4RunManager;
    
    // construct the default run manager
    runManager->SetUserInitialization(new ExG4DetectorConstruction01);

    // set mandatory initialization classes
    runManager->SetUserInitialization(new ExG4PhysicsList00);

    // set mandatory user action class
    runManager->SetUserInitialization(new ExG4PrimaryGeneratorAction01);

    // initialize G4 Kernel
    runManager->Initialize();

    // Get the pointer to the user interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 1)
    {
        // Interactive mode: define UI Session
        G4UIExecutive* ui = new G4UIExecutive(argc, argv)
        UImanager->ApplyCommand("/control/execute init.mac");
        ui->SessionStart();

        delete ui;
    }
    else
    {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    // Job termination
    delete runManager;
    return 0;
}

/*
    G4 provides a category called intercoms managed by G4UImanager. THis category let us
    invoke set methods of class objects of which we do not know the pointer.

    G4UImanager also handles the G4cout and G4cerr (works the same as G4cerr and G4cout but the streams
    are handled by G4UImanager).
*/

/*
    Final questions:
    What is a category?
*/

