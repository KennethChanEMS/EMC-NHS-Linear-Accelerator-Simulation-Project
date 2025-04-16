#include "action.hh"

Action :: Action(){}
Action :: ~Action(){}

void Action ::Build() const{
    Gun *gun = new Gun();
    SetUserAction(gun);
}