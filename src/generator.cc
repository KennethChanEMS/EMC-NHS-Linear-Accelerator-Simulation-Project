#include "generator.hh"

using namespace std;

Gun :: Gun(){
    fParticleGun = new G4ParticleGun;
    partConfig = new Config();

    array<G4double, 2> particle = partConfig -> forGenerator();
    N = particle[1];
    Energy = particle[0];
}

Gun :: ~Gun(){
    delete fParticleGun;
    delete partConfig;
}

void Gun :: GeneratePrimaries(G4Event *Event){

    G4ParticleTable *ParticleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "e-";
    G4ParticleDefinition *particle = ParticleTable -> FindParticle(particleName);

    G4ThreeVector pos(0, 81.5*cm, 0);
    G4ThreeVector dir(0, -1, 0);

    fParticleGun -> SetParticlePosition(pos);
    fParticleGun -> SetParticleMomentumDirection(dir);
    fParticleGun -> SetParticleEnergy(Energy * MeV);
    fParticleGun -> SetParticleDefinition(particle);

    for (G4int i; i < N; i++){
        fParticleGun -> SetParticleTime(i * 1*ns);
        fParticleGun -> GeneratePrimaryVertex(Event);
    }
}
