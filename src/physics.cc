#include "physics.hh"

PhysicsList :: PhysicsList(){
    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4EmLivermorePhysics());
}

PhysicsList :: ~PhysicsList(){}