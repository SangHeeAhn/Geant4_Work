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

#include "SensitiveDetectorOnScint.hh"
//#include <vector>
#include "G4FastSimulationVector.hh"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

SensitiveDetectorOnScint::SensitiveDetectorOnScint(G4String name)
:G4VSensitiveDetector(name)
{
	ofsScint.open("KEofGammarayOnScint");



}

SensitiveDetectorOnScint::~SensitiveDetectorOnScint()
{
	ofsScint.close();

}

void SensitiveDetectorOnScint::Initialize(G4HCofThisEvent*)
{

}

G4bool SensitiveDetectorOnScint::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{


	G4double ThresholdOfGamma = 10;
	G4double ReferenceKE = 0.511;
	G4String ParName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
	G4double KEOfParticle = aStep->GetPreStepPoint()->GetKineticEnergy();
	//ofsScint<<KEOfParticle<<G4endl;
	if(ParName == "gamma"){
		ofsScint<<KEOfParticle<<G4endl;

	}

	if(ParName == "gamma"){
		if(KEOfParticle < ReferenceKE *((100-ThresholdOfGamma)/100) ||
				KEOfParticle > ReferenceKE *((100+ThresholdOfGamma)/100) ){
		//ofsScint<<ParName<<G4endl;
		//G4cout<<"wonjoong"<<G4endl;
		aStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
		}
	}





	return true;

}


void SensitiveDetectorOnScint::EndOfEvent(G4HCofThisEvent*)
{


}
