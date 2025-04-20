#ifndef DETECTOR_HH
#define DETECTOR_HH

#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4Track.hh"
#include "Gamma.hh"

#include "config.hh"

class Detector : public G4VSensitiveDetector{
    public:
        Detector(G4String);
        ~Detector();
    private:
        //logged data
        G4double fSuckedEnergy;
        G4double SSD;
        G4double Energy;
        G4double Field;
        G4double Depth;


        Config *dataArray;
        //file name
        std::filesystem::path file;

        virtual void Initialize(G4HCofThisEvent *) override;
        virtual void EndOfEvent(G4HCofThisEvent *) override;
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;
};

#endif