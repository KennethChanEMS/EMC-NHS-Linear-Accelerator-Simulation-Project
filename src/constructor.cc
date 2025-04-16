#include "constructor.hh"

using namespace std;

Constructor :: Constructor(){
    posConfig = new Config();
    array<G4double, 3>position = posConfig -> forConstructor();

    SSD = position[1];
    Depth = position[2];
    Hr = position[0];
};
Constructor :: ~Constructor(){
    delete posConfig;
};

G4VPhysicalVolume *Constructor::Construct(){
    G4NistManager *nist = G4NistManager::Instance();
    //Box materials
    G4Material *worldMat = nist -> FindOrBuildMaterial("G4_AIR");
    G4Material *phantomMat = nist -> FindOrBuildMaterial("G4_WATER");
    G4Material *headMat = nist -> FindOrBuildMaterial("G4_Galactic");

    //Other Solid 
    G4Material *Tungsten = nist -> FindOrBuildMaterial("G4_W");
    G4Material *Lead = nist -> FindOrBuildMaterial("G4_Pb");
    G4Material *Graphite = nist -> FindOrBuildMaterial("G4_GRAPHITE");
    G4Material *Aluminum = nist -> FindOrBuildMaterial("G4_Al");

    //Detector Gases
    G4Material *P10 = new G4Material("P10", 1.784*mg/cm3, 2);
    G4Material *CH4 = nist -> FindOrBuildMaterial("G4_METHANE");
    G4Material *Argon = nist -> FindOrBuildMaterial("G4_Ar");

    P10 -> AddMaterial(Argon, 90*perCent);
    P10 -> AddMaterial(CH4, 10*perCent);


    //Colors
    G4VisAttributes *grey = new G4VisAttributes(G4Color(0.5, 0.5, 0.5));
    G4VisAttributes *black = new G4VisAttributes(G4Color(0.0, 0.0, 0.0));
    G4VisAttributes *white = new G4VisAttributes(G4Color(1.0, 1.0, 1.0));
    G4VisAttributes *blue = new G4VisAttributes(G4Color(0.0, 1.0, 1.0));

    grey -> SetForceSolid(true);
    black -> SetForceSolid(true);
    white -> SetForceSolid(true);
    blue -> SetForceSolid(true);

    //Rotation Matrix
    G4RotationMatrix *Turn = new G4RotationMatrix();
    Turn -> rotateX(90*deg);
    Turn -> rotateY(0*deg);
    Turn -> rotateZ(0*deg);

    //Rotation Matrix
    G4RotationMatrix *Turn2 = new G4RotationMatrix();
    Turn2 -> rotateX(0*deg);
    Turn2 -> rotateY(90*deg);
    Turn2 -> rotateZ(0*deg);
    

    //Others
    G4double t = 9;
    G4double h = t - 1.5;



    //World
    G4Box *solidWorld = new G4Box("solidWord", 1*m, 1*m , 1*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    //Linac Head
    G4Box *solidHead = new G4Box("solidHead", 20*cm, 20*cm, 20*cm);
    G4LogicalVolume *logicHead = new G4LogicalVolume(solidHead, headMat, "logicHead");

    //Phantom
    G4Box *solidPhantom = new G4Box("solidPhantom", 27.5*cm, 7.5*cm, 30/2*cm);
    G4LogicalVolume *logicPhantom = new G4LogicalVolume(solidPhantom, phantomMat, "logicPhantom");

    logicPhantom -> SetVisAttributes(blue);
    
    //Primary Collimators
    G4Sphere *ShellA = new G4Sphere("solidCollA", 0, 15*cm, 0*deg, 360*deg, 0*deg, 180*deg);
    G4Sphere *ShellB = new G4Sphere("Shell", 0, 20*cm, 0*deg, 360*deg, 0*deg, 180*deg);
    G4Box *Cutter = new G4Box("Cutter", 12*cm, ((15-t)/2)*cm, 12*cm);
    G4Box *Cutter2 = new G4Box("Cutter", sqrt(319)*cm, (5.5)*cm, sqrt(319)*cm);
    G4Tubs *Passage = new G4Tubs("Passage", 0, 2*mm, 1.5*cm, 0*deg, 360*deg);
    G4Cons *Cone = new G4Cons("Cone", 0, 12*cm, 0, 2*mm, 3.75*cm, 0*deg, 360*deg);
    
    //Outer Collimator
    G4SubtractionSolid *Outer = new G4SubtractionSolid("Outer", ShellB, ShellA);
    G4SubtractionSolid *solidCollB = new G4SubtractionSolid("FlatOuter", Outer, Cutter2, 
nullptr, G4ThreeVector(0, -(20-((20-t)/2))*cm, 0));
    
    //Inner Collimator
    G4SubtractionSolid *Inner = new G4SubtractionSolid("Inner", ShellA, Passage,
Turn, G4ThreeVector(0, 0, 0));
    G4SubtractionSolid *FlatInner = new G4SubtractionSolid("FlatInner", Inner, Cutter, 
nullptr, G4ThreeVector(0, -(15-((15-t))/2)*cm, 0));
    G4SubtractionSolid *solidCollA = new G4SubtractionSolid("solidCollA", FlatInner, Cone,
Turn, G4ThreeVector(0, -5.25*cm, 0));


    G4LogicalVolume *logicCollB = new G4LogicalVolume(solidCollB, Lead, "logicCollB");
    G4LogicalVolume *logicCollA = new G4LogicalVolume(solidCollA, Tungsten, "logicCollA");

    logicCollB -> SetVisAttributes(grey);
    logicCollA -> SetVisAttributes(black);

    //target
    G4Tubs *solidTarget = new G4Tubs("solidTarget", 0, 2*mm, 1*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicTarget = new G4LogicalVolume(solidTarget, Tungsten, "logicTarget");

    logicTarget -> SetVisAttributes(grey);

    //absorber
    G4Tubs *solidGraphite = new G4Tubs("solidGraphite", 0, 2*mm, 1*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicGraphite = new G4LogicalVolume(solidGraphite, Graphite, "logicGraphite");

    //Secondary Collimators
    G4Tubs *Outer2 = new G4Tubs("Outer2", 0, sqrt(319)*cm, 2.5*cm, 0*deg, 360*deg);
    G4Cons *Hole = new G4Cons("Hole", 0, Hr*cm, 0, 12*cm, 2.5*cm, 0*deg, 360*deg);
    
    G4SubtractionSolid *solidCollOut = new G4SubtractionSolid("solidCollOut", Outer2, Hole);
    G4LogicalVolume *logicCollOut = new G4LogicalVolume(solidCollOut, Tungsten, "logicCollOut");
    
    logicCollOut -> SetVisAttributes(white);

    //Flattening
    G4Tubs *solidFlatDisk = new G4Tubs("solidFlatDisk", 0, 3*cm, 1*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicFlatDisk = new G4LogicalVolume(solidFlatDisk, Tungsten, "logicFlatDisk");

    G4Cons *solidFlatCone = new G4Cons("solidFlatCone", 0, 1*mm, 0, 0, 1*mm, 0*deg, 360*deg);
    G4LogicalVolume *logicFlatCone = new G4LogicalVolume(solidFlatCone, Tungsten, "logicFlatCone");

    logicFlatDisk -> SetVisAttributes(black);
    logicFlatCone -> SetVisAttributes(grey);

    //Ionisation Chamber
    G4Tubs *solidDetector = new G4Tubs("solidGas", 0, 0.5*cm, 3*cm, 0*deg, 360*cm);
    G4Tubs *FullCase = new G4Tubs("FullCase", 0, 0.7*cm, 3.2*cm, 0*deg, 360*cm);

    G4SubtractionSolid *solidCase = new G4SubtractionSolid("solidCase", FullCase, solidDetector);

    logicDetector = new G4LogicalVolume(solidDetector, P10, "logicGas");
    G4LogicalVolume *logicCase = new G4LogicalVolume(solidCase, Graphite, "logicCase");

    //Placement World
    G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), 
logicWorld, "physWorld" , nullptr, false, 0, true);
    G4VPhysicalVolume *physHead = new G4PVPlacement(nullptr, G4ThreeVector(0, 80*cm, 0), 
logicHead, "physHead", logicWorld, false, 0, true);
    G4VPhysicalVolume *physPhantom = new G4PVPlacement(nullptr, G4ThreeVector(0, SSD*cm, 0),
logicPhantom, "physPhantom", logicWorld, false, 0, true);

    //Placement Head
    G4VPhysicalVolume *physCollB = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), 
logicCollB, "physCollB", logicHead, false, 0, true);
    G4VPhysicalVolume *physCollA = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0),
logicCollA, "physCollA", logicHead, false, 0, true);
    G4VPhysicalVolume *physTarget = new G4PVPlacement(Turn, G4ThreeVector(0, -0.5*cm, 0),
logicTarget, "physTarget", logicHead, false, 0, true);
    G4VPhysicalVolume *physGraphite = new G4PVPlacement(Turn, G4ThreeVector(0, -1.4*cm, 0),
logicGraphite, "physGraphite", logicHead, false, 0, true);
    G4VPhysicalVolume *physCollOut = new G4PVPlacement(Turn, G4ThreeVector(0, -(t+2.5)*cm, 0),
logicCollOut, "physCollOut", logicHead, false, 0, true);
    G4VPhysicalVolume *physFlatDisk = new G4PVPlacement(Turn, G4ThreeVector(0, -(9-(675/118))*cm - 1*mm, 0),
logicFlatDisk, "physFlatDisk", logicHead, false, 0, true);
    G4VPhysicalVolume *physFlatCone = new G4PVPlacement(Turn, G4ThreeVector(0, -(9-(675/118))*cm + 1*mm, 0),
logicFlatCone, "physFlatCone", logicHead, false, 0, true);

//Placement Phantom
    G4VPhysicalVolume *physDetector = new G4PVPlacement(Turn2, G4ThreeVector(0, Depth*cm, 0),
logicDetector, "physDetector", logicPhantom, false, 0, true);
    G4VPhysicalVolume *physCase = new G4PVPlacement(Turn2, G4ThreeVector(0, Depth*cm, 0),
logicCase, "physCase", logicPhantom, false, 0, true);



    return physWorld;
}

void Constructor :: ConstructSDandField(){
    //Sensitive Detector
    Detector *detect = new Detector("IC");
    logicDetector -> SetSensitiveDetector(detect);
    G4SDManager::GetSDMpointer()->AddNewDetector(detect);
}