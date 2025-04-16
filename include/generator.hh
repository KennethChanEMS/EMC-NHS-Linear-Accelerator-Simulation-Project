#ifndef GENERATOR_HH
#define GENERATOR_HH

#include <array>

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"

#include "config.hh"

class Gun : public G4VUserPrimaryGeneratorAction{
    public:
        Gun();
        ~Gun();

        virtual void GeneratePrimaries(G4Event *);
    private:
        G4ParticleGun *fParticleGun;
        Config *partConfig;

        G4double N;
        G4double Energy;
};

#endif