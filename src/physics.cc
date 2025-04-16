#include "physics.hh"

PhysicsList :: PhysicsList(){
    RegisterPhysics(new G4EmStandardPhysics_option4());
}

PhysicsList :: ~PhysicsList(){}