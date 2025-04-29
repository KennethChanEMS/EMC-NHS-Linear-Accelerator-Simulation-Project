#ifndef CONFIG_HH
#define CONFIG_HH

#include <array>
#include <math.h>

#include "globals.hh"

class Config{
    public:
        Config();
        ~Config();
        virtual std::array<G4double, 3> forConstructor();
        virtual std::array<G4double, 2> forGenerator();
        virtual std::array<G4double, 4> data();
    private:
        //Constructor
        G4double SSD;
        G4double Depth;
        G4double Field_Size;

        //Generator
        G4double Energy;
        G4double numElectrons;
};

#endif