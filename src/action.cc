#include "action.hh"

Action :: Action(){}
Action :: ~Action(){}

void Action ::Build() const{
    Gun *gun = new Gun();
    SetUserAction(gun);

    G4Event *event = new G4Event();
    if (event){
        unsigned long seed = event->GetEventID() + static_cast<unsigned long>(time(0));
        G4Random::setTheSeed(seed);
    }
}