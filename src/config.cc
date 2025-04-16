#include "config.hh"

using namespace std;

Config :: Config(){
    /*
        - Energy: 6 - 15
        - SSD: 100 - 150
        - Depth: 0 - 13.6
        - Field Size: At least 10
    */
    SSD = 100;
    Depth = 0;
    Field_Size = 10;

    Energy = 6;
    numElectrons = 10000;
}

Config :: ~Config(){}

array<G4double, 3> Config :: forConstructor(){
    G4double Phantom_Pos = -1*(SSD - 74);
    G4double Detector_Pos = -1*(Depth) + 6.8;
    G4double Hole_Radius = ((Field_Size * 7.0) / SSD);

    return {Hole_Radius, Phantom_Pos, Detector_Pos};
}

array<G4double, 2> Config :: forGenerator(){
    return {Energy, numElectrons};
}

array<G4double, 4> Config :: data(){
    return {SSD, Energy, Field_Size, Depth};
}
