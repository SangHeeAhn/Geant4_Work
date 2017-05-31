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

#include "SensitiveDetector.hh"
//#include <vector>
#include "G4FastSimulationVector.hh"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

SensitiveDetector::SensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{

	Counter = 1;
	string filename;
	G4cout<<"Please enter a file name for GammaCamera1 (LeftUp) : "<<G4endl;
	getline(cin,filename);
	ofs.open(filename.c_str());

	string filename2;
	G4cout<<"Please enter a file name for GammaCamera2 (RightUp) : "<<G4endl;
	getline(cin,filename2);
	ofs2.open(filename2.c_str());


	//Initialization.
	for(G4int i=0;i<16;i++){
		for(G4int j=0;j<16;j++){
			DEMatrix[i][j] = 0;
		}
	}


	//Initialization.
	for(G4int ii=0;ii<16;ii++){
		for(G4int jj=0;jj<16;jj++){
			DEMatrix2[ii][jj] = 0;
		}
	}


	//ofs_hist.open("ForHistogram_pixe.out");

}

SensitiveDetector::~SensitiveDetector()
{

	for(G4int i=0;i<16;i++){
		for(G4int j=0;j<16;j++){
			ofs<< i << "\t"<<j<<"\t"<<DEMatrix[i][j]<<G4endl;
		}
		ofs<<G4endl;
	}


	ofs.close();

	for(G4int ii=0;ii<16;ii++){
		for(G4int jj=0;jj<16;jj++){
			ofs2<< ii << "\t"<<jj<<"\t"<<DEMatrix2[ii][jj]<<G4endl;
		}
		ofs2<<G4endl;
	}


	ofs2.close();


	//ofs_hist.close();

}

void SensitiveDetector::Initialize(G4HCofThisEvent*)
{

}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	G4String ParName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();

	if(ParName == "opticalphoton"){
		G4int RepZNo = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(0);
		G4int RepXNo = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(1);

		//optical photon doesn't have Deposit Energy
		//G4double dE = aStep->GetTotalEnergyDeposit();
		//
		G4int GammaCameraNum = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(3);

		if(GammaCameraNum==11)
		{

			DEMatrix[RepZNo][RepXNo] += Counter;
			//G4double KE = aStep->GetPreStepPoint()->GetKineticEnergy();
			//ofs_hist<<KE<<G4endl;
			//G4cout<<KE<<G4endl;
		}
		else if (GammaCameraNum==10){

			DEMatrix2[RepZNo][RepXNo] += Counter;
			//G4double KE = aStep->GetPreStepPoint()->GetKineticEnergy();
			//ofs_hist<<KE<<G4endl;
		}


		//G4cout<<"Sensitive Detector Activated"<<G4endl;
		return true;
	}
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{


}
