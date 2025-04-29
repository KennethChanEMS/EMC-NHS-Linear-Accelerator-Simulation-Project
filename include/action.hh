#ifndef ACTION_HH
#define ACTION_HH

#include <ctime>

#include "G4VUserActionInitialization.hh"
#include "G4Event.hh"
#include "G4RandomTools.hh"

#include "generator.hh"

class Action : public G4VUserActionInitialization{
    public:
        Action();
        ~Action();

        virtual void Build() const;
};

#endif