#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"


#include "constructor.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv){
    //Run Manager
    G4RunManager *runManager = new G4RunManager();
    runManager -> SetUserInitialization(new Constructor());
    runManager -> SetUserInitialization(new PhysicsList());
    runManager -> SetUserInitialization(new Action());

    runManager -> Initialize();

    //UI Manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    //vis Manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager -> Initialize();

    
    //start
    UImanager -> ApplyCommand("/control/execute vis.mac");
    ui -> SessionStart();

    delete ui;
    delete runManager;
    delete visManager;
    return 0;
}