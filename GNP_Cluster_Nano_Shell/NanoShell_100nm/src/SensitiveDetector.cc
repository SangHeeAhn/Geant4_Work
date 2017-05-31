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
#include "iostream"
using namespace std;
#include "stdio.h"
#include "DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "math.h"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{

ofs.open("OutPut.txt");
//Counter = 1;
//string filename;
//G4cout <<"Input the save file name: "<<G4endl;
//getline(cin,filename);
//ofs.open(filename.c_str());


//std::ofstream ofs[5];
//for(G4int num = 0; num<=1; num++){
//G4String filename = "OutPut.txt_"+ num;
//ofs[num].open(filename,std::ios::out);
//}

	// open the output file

	NumberofSeco_1 = 0; // shell_1 secondary electron emission

	NumberofSeco_2 = 0;// shell_2 secondary electron emission

	NumberofSeco_3 = 0;// shell_3 secondary electron emission

	NumberofSeco_4 = 0;// shell_4 secondary electron emission

	NumberofSeco_5 = 0;// shell_5 secondary electron emission

	NumberofSeco_6 = 0;// shell_6 secondary electron emission

	NumberofSeco_7 = 0;// shell_7 secondary electron emission

	NumberofSeco_8 = 0;// shell_8 secondary electron emission

	NumberofSeco_9 = 0;	// shell_9 secondary electron emission

	NumberofSeco_10 = 0;// shell_10 secondary electron emission


	// Each of nano particle energy deposited
	TE_1= 0;
	TE_2 = 0;
	TE_3 = 0;
	TE_4 = 0;
	TE_5 = 0;
	TE_6 = 0;
	TE_7 = 0;
	TE_8 = 0;
	TE_9 = 0;
	TE_10 = 0;



	// Dose value initialize;
	dose = 0;
	// mass value initialize;
	mass_1 = 0;
	mass_2 = 0;
	mass_3 = 0;
	mass_4 = 0;
	mass_5 = 0;
	mass_6 = 0;
	mass_7 = 0;
	mass_8 = 0;
	mass_9 = 0;
	mass_10 = 0;


	ofs.open("Position.txt");


}

SensitiveDetector::~SensitiveDetector()
{
	// print out

	G4cout<<"\n"<<G4endl;

	G4cout<<"Number of Secondary electron and deposited energy"<<G4endl;

	G4cout<<"\n"<<G4endl;

	G4cout<<"NumSEco Shell_1  : "<<NumberofSeco_1<<G4endl;

	G4cout<<"NumSEco Shell_2  : "<<NumberofSeco_2<<G4endl;

	G4cout<<"NumSEco Shell_3  : "<<NumberofSeco_3<<G4endl;

	G4cout<<"NumSEco Shell_4  : "<<NumberofSeco_4<<G4endl;

	G4cout<<"NumSEco Shell_5  : "<<NumberofSeco_5<<G4endl;

	G4cout<<"NumSEco Shell_6  : "<<NumberofSeco_6<<G4endl;

	G4cout<<"NumSEco Shell_7  : "<<NumberofSeco_7<<G4endl;

	G4cout<<"NumSEco Shell_8  : "<<NumberofSeco_8<<G4endl;

	G4cout<<"NumSEco Shell_9  : "<<NumberofSeco_9<<G4endl;

	G4cout<<"NumSEco Shell_10  : "<<NumberofSeco_10<<G4endl;

	G4cout<<"\n"<<G4endl;

	G4cout<<"Shell_1 SE e- deposited energy: "<<(TE_1)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_2 SE e- deposited energy: "<<(TE_2)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_3 SE e- deposited energy: "<<(TE_3)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_4 SE e- deposited energy: "<<(TE_4)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_5 SE e- deposited energy: "<<(TE_5)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_6 SE e- deposited energy: "<<(TE_6)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_7 SE e- deposited energy: "<<(TE_7)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_8 SE e- deposited energy: "<<(TE_8)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_9 SE e- deposited energy: "<<(TE_9)/keV<<" keV"<<G4endl;

	G4cout<<"Shell_10 SE e- deposited energy: "<<(TE_10)/keV<<" keV"<<G4endl;

	G4cout<<"\n"<<G4endl;

	G4cout<<"Total Dose Shell_1: "<<dose_1<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_2: "<<dose_2<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_3: "<<dose_3<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_4: "<<dose_4<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_5: "<<dose_5<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_6: "<<dose_6<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_7: "<<dose_7<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_8: "<<dose_8<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_9: "<<dose_9<<" Gy"<<G4endl;

	G4cout<<"Total Dose Shell_10: "<<dose_10<<" Gy"<<G4endl;

	G4cout<<"\n"<<G4endl;

	G4cout<<"Copy and Paste"<<G4endl;

	G4cout<<NumberofSeco_1<<"\n"<<NumberofSeco_2<<"\n"<<NumberofSeco_3<<"\n"<<NumberofSeco_4<<"\n"
			<<NumberofSeco_5<<"\n"<<NumberofSeco_6<<"\n"<<NumberofSeco_7<<"\n"<<NumberofSeco_8<<"\n"
			<<NumberofSeco_9<<"\n"<<NumberofSeco_10<<G4endl;

	G4cout<<"\n"<<G4endl;

	G4cout<<dose_1<<"\n"<<dose_2<<"\n"<<dose_3<<"\n"<<dose_4<<"\n"
			<<dose_5<<"\n"<<dose_6<<"\n"<<dose_7<<"\n"<<dose_8<<"\n"
			<<dose_9<<"\n"<<dose_10<<G4endl;



	// Output text file

	ofs<<"Number of Secondary electron, deposited energy, absorbed Dose"<<G4endl;

	ofs<<"\n"<<G4endl;

	ofs<<"NumSEco Shell_1: "<<NumberofSeco_1<<G4endl;

	ofs<<"NumSEco Shell_2: "<<NumberofSeco_2<<G4endl;

	ofs<<"NumSEco Shell_3: "<<NumberofSeco_3<<G4endl;

	ofs<<"NumSEco Shell_4: "<<NumberofSeco_4<<G4endl;

	ofs<<"NumSEco Shell_5: "<<NumberofSeco_5<<G4endl;

	ofs<<"NumSEco Shell_6: "<<NumberofSeco_6<<G4endl;

	ofs<<"NumSEco Shell_7: "<<NumberofSeco_7<<G4endl;

	ofs<<"NumSEco Shell_8: "<<NumberofSeco_8<<G4endl;

	ofs<<"NumSEco Shell_9: "<<NumberofSeco_9<<G4endl;

	ofs<<"NumSEco Shell_10: "<<NumberofSeco_10<<G4endl;

	ofs<<"\n"<<G4endl;

	ofs<<"Total Dose Shell_1: "<<dose_1<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_2: "<<dose_2<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_3: "<<dose_3<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_4: "<<dose_4<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_5: "<<dose_5<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_6: "<<dose_6<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_7: "<<dose_7<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_8: "<<dose_8<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_9: "<<dose_9<<" Gy"<<G4endl;

	ofs<<"Total Dose Shell_10: "<<dose_10<<" Gy"<<G4endl;

	ofs.close();


//Secondary electron position
//	ofs<<"Position : "<<Center_Position<<G4endl;
//	ofs.close();
}

void SensitiveDetector::Initialize(G4HCofThisEvent*)
{

}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{

	if(aStep->GetTrack()->GetParentID()==0) return false;
	if(aStep->GetTrack()->GetParentID()!= 0){  //secondary particle only
		if(aStep->GetTrack()->GetDefinition()->GetParticleName() == "e-"){ //electron only
			//if(aStep->GetTrack()->GetOriginTouchable()->GetVolume()->GetName()=="Water_box") return false;


			// shell_1
			if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==10){
				//G4cout<<"From Gold: "<<aStep->GetTrack()->GetDefinition()->GetParticleName()<<G4endl;
				NumberofSeco_1++;
				TE_1 += aStep->GetTotalEnergyDeposit();
				//Center_Position=aStep->GetTrack()->GetPosition();
				//G4cout<<aStep->GetTrack()->GetPosition()<<G4endl;
				//	G4cout<<"Shell_1 "<<NumberofSeco_1<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=10){
				//				//G4cout<<"From others: "<<aStep->GetTrack()->GetDefinition()->GetParticleName()<<G4endl;
				//				NumberofSeco_D1++;
				//				TE_D1 += aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_1_1 "<<NumberofSeco_D1<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				// shell_2
			}else if (aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==20){

				NumberofSeco_2++;
				TE_2+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_2 "<<NumberofSeco_2<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//			}if (aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=20){
				//
				//				NumberofSeco_D2++;
				//				TE_D2+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_2_1 "<<NumberofSeco_D2<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//
				// shell_3
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==30){


				NumberofSeco_3++;
				TE_3+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_3 "<<NumberofSeco_3<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=30){
				//
				//
				//				NumberofSeco_D3++;
				//				TE_D3+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_3_1 "<<NumberofSeco_D3<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//
				// shell_4
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==40){


				NumberofSeco_4++;
				TE_4+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_4 "<<NumberofSeco_4<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=40){
				//
				//
				//				NumberofSeco_D4++;
				//				TE_D4+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_4_1 "<<NumberofSeco_D4<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				// shell_5
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==50){


				NumberofSeco_5++;
				TE_5+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_5 "<<NumberofSeco_5<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=50){
				//
				//
				//				NumberofSeco_D5++;
				//				TE_D5+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_5_1 "<<NumberofSeco_D5<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				// shell_6
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==60){

				NumberofSeco_6++;
				TE_6+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_6 "<<NumberofSeco_6<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;


				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=60){
				//
				//
				//				NumberofSeco_D6++;
				//				TE_D6+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_6_1 "<<NumberofSeco_D6<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				// shell_7
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==70){

				NumberofSeco_7++;
				TE_7+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_7 "<<NumberofSeco_7<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=70){
				//
				//				NumberofSeco_D7++;
				//				TE_D7+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_7_1 "<<NumberofSeco_D7<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;

				// shell_8
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==80){


				NumberofSeco_8++;
				TE_8+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_8 "<<NumberofSeco_8<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				//			}if(aStep->GetTrack()->GetOriginTouchable()->GetCopyNumber(0)!=80){
				//
				//
				//				NumberofSeco_D8++;
				//				TE_D8+= aStep->GetTotalEnergyDeposit();
				//				G4cout<<"Shell_8_1 "<<NumberofSeco_D8<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				// shell_9
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==90){

				NumberofSeco_9++;
				TE_9+= aStep->GetTotalEnergyDeposit();
				//	G4cout<<"Shell_9 "<<NumberofSeco_9<<G4endl;
				//	G4cout<<aStep->GetTrack()->GetVolume()->GetName()<<G4endl;
				// shell_10
			}else if(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber()==100){
				//
				NumberofSeco_10++;
				TE_10+= aStep->GetTotalEnergyDeposit();


			}

			//G4cout<<aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName()<<G4endl; // Number of gold print out
		}

	}
	return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{


	const DetectorConstruction* detectorConstruction  = static_cast<const DetectorConstruction*>

	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	mass_1 = detectorConstruction->GetScoringVolime_1()->GetMass();
	mass_2 = detectorConstruction->GetScoringVolime_2()->GetMass();
	mass_3 = detectorConstruction->GetScoringVolime_3()->GetMass();
	mass_4 = detectorConstruction->GetScoringVolime_4()->GetMass();
	mass_5 = detectorConstruction->GetScoringVolime_5()->GetMass();
	mass_6 = detectorConstruction->GetScoringVolime_6()->GetMass();
	mass_7 = detectorConstruction->GetScoringVolime_7()->GetMass();
	mass_8 = detectorConstruction->GetScoringVolime_8()->GetMass();
	mass_9 = detectorConstruction->GetScoringVolime_9()->GetMass();
	mass_10 = detectorConstruction->GetScoringVolime_10()->GetMass();


	//	mass = detectorConstruction->GetScoringVolime()->GetMass(); // Phantom mass 1g check

	//	G4cout<<"Shell_1 "<<mass_1/kg<<G4endl;
	//	G4cout<<"Shell_2 "<<mass_2/kg<<G4endl;
	//	G4cout<<"Shell_3 "<<mass_3/kg<<G4endl;
	//	G4cout<<"Shell_4 "<<mass_4/kg<<G4endl;
	//	G4cout<<"Shell_5 "<<mass_5/kg<<G4endl;
	//	G4cout<<"Shell_6 "<<mass_6/kg<<G4endl;
	//	G4cout<<"Shell_7 "<<mass_7/kg<<G4endl;
	//	G4cout<<"SHell_8 "<<mass_8/kg<<G4endl;
	//	G4cout<<"SHell_9 "<<mass_9/kg<<G4endl;

	//	G4cout<<"Phantom "<<mass/g<<G4endl;


	G4double J = 1.602176487*pow(10,-16);

	dose_1 = ((TE_1/keV)*J)/(mass_1/kg);
	dose_2 = ((TE_2/keV)*J)/(mass_2/kg);
	dose_3 = ((TE_3/keV)*J)/(mass_3/kg);
	dose_4 = ((TE_4/keV)*J)/(mass_4/kg);
	dose_5 = ((TE_5/keV)*J)/(mass_5/kg);
	dose_6 = ((TE_6/keV)*J)/(mass_6/kg);
	dose_7 = ((TE_7/keV)*J)/(mass_7/kg);
	dose_8 = ((TE_8/keV)*J)/(mass_8/kg);
	dose_9 = ((TE_9/keV)*J)/(mass_9/kg);
	dose_10 = ((TE_10/keV)*J)/(mass_10/kg);

}


void SensitiveDetector::GetCounter()
{




}








