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

#ifndef SensitiveDetector_hh_
#define SensitiveDetector_hh_

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

class G4HCofThisEvent;
class G4TouchableHistory;

class SensitiveDetector: public G4VSensitiveDetector
{
public:

	SensitiveDetector(G4String name);
	virtual ~SensitiveDetector();

	void Initialize(G4HCofThisEvent*);
	G4bool ProcessHits(G4Step* aStep, G4TouchableHistory*);
	void EndOfEvent(G4HCofThisEvent*);
	void GetCounter();
private:
	std::ofstream ofs;
	int NumberofSeco_1; // center of gold secondary electron emission
	int NumberofSeco_D1;
	int NumberofSeco_2 ;// Gold_1 secondary electron emission
	int	NumberofSeco_D2;
	int NumberofSeco_3 ;// Gold_2 secondary electron emission
	int NumberofSeco_D3;
	int NumberofSeco_4 ;// Gold_4 secondary electron emission
	int NumberofSeco_D4;
	int NumberofSeco_5 ;// Gold_5 secondary electron emission
	int NumberofSeco_D5;
	int NumberofSeco_6 ;// Gold_6 secondary electron emission
	int NumberofSeco_D6;
	int NumberofSeco_7 ;// Gold_7 secondary electron emission
	int NumberofSeco_D7;
	int NumberofSeco_8 ;// Gold_8 secondary electron emission
	int NumberofSeco_D8;
	int	NumberofSeco_9 ;// Gold_9 secondary electron emission
	int NumberofSeco_D9;
	int	NumberofSeco_10 ; // Gold_10 secondary electron emission
	int NumberofSeco_D10;

	//Total energy deposited variable
	G4double TE_1 ;
	G4double TE_dep_1; //Total deposited energy
	G4double dose_1; //Total absorbed dose
	G4double mass_1; //Sensitive detector shell_1 mass

	G4double TE_2 ;
	G4double TE_dep_2; //Total deposited energy
	G4double dose_2; //Total absorbed dose
	G4double mass_2; //Sensitive detector shell_2 mass

	G4double TE_3 ;
	G4double TE_dep_3; //Total deposited energy
	G4double dose_3; //Total absorbed dose
	G4double mass_3; //Sensitive detector shell_3 mass

	G4double TE_4 ;
	G4double TE_dep_4; //Total deposited energy
	G4double dose_4; //Total absorbed dose
	G4double mass_4; //Sensitive detector shell_4 mass

	G4double TE_5 ;
	G4double TE_dep_5; //Total deposited energy
	G4double dose_5; //Total absorbed dose
	G4double mass_5; //Sensitive detector shell_5 mass

	G4double TE_6 ;
	G4double TE_dep_6; //Total deposited energy
	G4double dose_6; //Total absorbed dose
	G4double mass_6; //Sensitive detector shell_6 mass

	G4double TE_7 ;
	G4double TE_dep_7; //Total deposited energy
	G4double dose_7; //Total absorbed dose
	G4double mass_7; //Sensitive detector shell_7 mass

	G4double TE_8 ;
	G4double TE_dep_8; //Total deposited energy
	G4double dose_8; //Total absorbed dose
	G4double mass_8; //Sensitive detector shell_8 mass

	G4double TE_9 ;
	G4double TE_dep_9; //Total deposited energy
	G4double dose_9; //Total absorbed dose
	G4double mass_9; //Sensitive detector shell_9 mass


	G4double TE_10 ;
	G4double TE_dep_10; //Total deposited energy
	G4double dose_10; //Total absorbed dose
	G4double mass_10; //Sensitive detector shell_10 mass

	G4double mass; // phantom mass

	G4double dose; //Total deposited dose

	G4ThreeVector Center_Position; // secondary electron position


};

#endif
