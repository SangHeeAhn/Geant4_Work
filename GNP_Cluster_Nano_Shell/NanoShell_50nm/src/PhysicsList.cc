// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 	Author: yskim
//

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
#include "G4EmPenelopePhysics.hh"
#include "G4EmDNAPhysics.hh"
PhysicsList::PhysicsList()
:G4VModularPhysicsList()
{
	SetVerboseLevel(1);

	// Decay physics
	//RegisterPhysics(new G4DecayPhysics());
	// EM physics
	//RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4EmPenelopePhysics());
	//RegisterPhysics(new G4EmDNAPhysics());
	// Radioactive decay
	//RegisterPhysics(new G4RadioactiveDecayPhysics());

	// Hadron physics
//	RegisterPhysics(new G4HadronPhysicsQGSP_BIC());
//	RegisterPhysics(new G4StoppingPhysics());
//	RegisterPhysics(new G4HadronElasticPhysics());
//	RegisterPhysics(new G4EmExtraPhysics());
//	RegisterPhysics(new G4IonBinaryCascadePhysics());
//	RegisterPhysics(new G4NeutronTrackingCut());
}

PhysicsList::~PhysicsList()
{

}

void PhysicsList::SetCuts()
{

	G4VUserPhysicsList::SetCuts();

}
