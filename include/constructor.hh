#ifndef CONSTRUCTOR_HH
#define CONSTRUCTOR_HH

#include <array>

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"

#include "G4Color.hh"
#include "G4VisAttributes.hh"

#include "detector.hh"
#include "config.hh"

class Constructor : public G4VUserDetectorConstruction{
    public:
        Constructor();
        ~Constructor();

        virtual G4VPhysicalVolume *Construct();
    private:
        G4double SSD;
        G4double Depth;
        G4double Hr;
        Config *posConfig;

        G4LogicalVolume *logicDetector;
        virtual void ConstructSDandField();
};

#endif