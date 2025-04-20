#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"

class PhysicsList : public G4VModularPhysicsList{
    public:
        PhysicsList();
        ~PhysicsList();
};

#endif