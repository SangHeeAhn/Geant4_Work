#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4NeutronTrackingCut.hh"


#include "G4OpticalPhysics.hh"
#include "G4OpticalProcessIndex.hh"

#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
:G4VModularPhysicsList()
{
	SetVerboseLevel(1);

	// Decay physics
	RegisterPhysics(new G4DecayPhysics());
	// EM physics
	RegisterPhysics(new G4EmStandardPhysics());
	// Radioactive decay
	RegisterPhysics(new G4RadioactiveDecayPhysics());

	// Hadron physics
	RegisterPhysics(new G4HadronPhysicsQGSP_BIC());
	RegisterPhysics(new G4StoppingPhysics());
	RegisterPhysics(new G4HadronElasticPhysics());
	RegisterPhysics(new G4EmExtraPhysics());
	RegisterPhysics(new G4IonBinaryCascadePhysics());
	RegisterPhysics(new G4NeutronTrackingCut());


	// Optical Physics
	G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	RegisterPhysics( opticalPhysics );

	opticalPhysics->SetWLSTimeProfile("delta");

	opticalPhysics->SetScintillationYieldFactor(1.0);
	opticalPhysics->SetScintillationExcitationRatio(0.0);

	opticalPhysics->SetMaxNumPhotonsPerStep(100);
	opticalPhysics->SetMaxBetaChangePerStep(10.0);

	opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
	opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);

}

PhysicsList::~PhysicsList()
{

}

void PhysicsList::SetCuts()
{
	G4VUserPhysicsList::SetCuts();
}
