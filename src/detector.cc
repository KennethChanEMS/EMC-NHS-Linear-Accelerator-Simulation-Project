#include "detector.hh"

using namespace std;
using namespace std :: filesystem;

Detector :: Detector(G4String name) : G4VSensitiveDetector(name){
    dataArray = new Config();
    array<G4double, 4> data = dataArray -> data();

    SSD = data[0];
    Energy = data[1];
    Field = data[2];
    Depth = data[3];

    file = "/Users/student/Desktop/geant4/Linac_V2/data.csv";

}

Detector :: ~Detector(){
    delete dataArray;
}

void Detector :: Initialize(G4HCofThisEvent *){}

void Detector :: EndOfEvent(G4HCofThisEvent *){
    ofstream Log_Data(file, ios::app);
    Log_Data << "\n"
        << Energy << ","
        << SSD << ","
        << Field << ","
        << Depth << ","
        << fSuckedEnergy/MeV;
    Log_Data.close();
    G4cout << "Data logging complete" << G4endl;
}

G4bool Detector :: ProcessHits(G4Step *Step, G4TouchableHistory *Hist){
    G4double deposit = Step -> GetTotalEnergyDeposit();
    if (deposit > 0){
        fSuckedEnergy += (deposit/MeV) * 1.2;
    }else{
        return false;
    }
    return true;
}