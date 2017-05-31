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
#include <MpiManagerWJ.hh>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>


using namespace std;

SensitiveDetector::SensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{

	// MPI rank
	MpiManagerWJ *MpiManager = new MpiManagerWJ();
	MpiManager->SetRankNumber();
	this->rank = MpiManager->GetRankNumber();



	//// Time
	time_t now;
	struct tm t;


	time(&now);
	t = *localtime(&now);
	G4int year = t.tm_year + 1900;
	G4int month = t.tm_mon +1;
	G4int day = t.tm_mday;
	G4int hour = t.tm_hour;
	G4int min = t.tm_min;
	G4int sec = t.tm_sec;

	// File name
	stringstream ss_filename;
	ss_filename<< year << month << hour << day << "_" << hour << ":" << min <<":" <<sec <<"_RankNum:" << rank;
	filenameForSave = ss_filename.str();


	ofs.open(filenameForSave.c_str());

	for (G4int ii = 1; ii < 100 ; ii++){
		for (G4int jj = 1; jj < 100 ; jj++){
			DEMatrix[ii][jj] = 0;
		}
	}



}


SensitiveDetector::~SensitiveDetector()
{

	G4int nPrimaries = G4RunManager::GetRunManager()->GetNumberOfEventsToBeProcessed();
	for (G4int ii = 1; ii < 100 ; ii++){
		for (G4int jj = 1; jj < 100 ; jj++){
			ofs << ii << "\t" << jj << "\t" << DEMatrix[ii][jj]/nPrimaries/MeV << G4endl;
		}
		ofs<<G4endl;
	}
	//G4cout << " Rank check : " << rank << G4endl;

	this->ofs.close();
//	ofs.close((filenameForSave.c_str());
}

void SensitiveDetector::Initialize(G4HCofThisEvent*)
{

}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	G4int RepZNo = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(0);
	G4int RepXNo = aStep->GetPreStepPoint()->GetTouchable()->GetReplicaNumber(1);
	G4double dE = aStep->GetTotalEnergyDeposit();

	DEMatrix[RepZNo][RepXNo] += dE;
	//G4cout << " Rank check : " << rank << G4endl;

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{

}
