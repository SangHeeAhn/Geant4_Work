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

#ifndef DetectorConstruction_hh_
#define DetectorConstruction_hh_

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4VPhysicalVolume* Construct();

	G4LogicalVolume* GetScoringVolime() const { return fScoringVolume; } // Phantom mass

	G4LogicalVolume* GetScoringVolime_1() const { return fScoringVolume_1; }
	G4LogicalVolume* GetScoringVolime_2() const { return fScoringVolume_2; }
	G4LogicalVolume* GetScoringVolime_3() const { return fScoringVolume_3; }
	G4LogicalVolume* GetScoringVolime_4() const { return fScoringVolume_4; }
	G4LogicalVolume* GetScoringVolime_5() const { return fScoringVolume_5; }
	G4LogicalVolume* GetScoringVolime_6() const { return fScoringVolume_6; }
	G4LogicalVolume* GetScoringVolime_7() const { return fScoringVolume_7; }
	G4LogicalVolume* GetScoringVolime_8() const { return fScoringVolume_8; }
	G4LogicalVolume* GetScoringVolime_9() const { return fScoringVolume_9; }
	G4LogicalVolume* GetScoringVolime_10() const { return fScoringVolume_10; }


	virtual void ConstructSDandField();
private:

// gold nano logical volume name define.
G4LogicalVolume* logicgold_0;

//sensitive detector logical volume name define(SD)
G4LogicalVolume* logicwater_SD_1;
G4LogicalVolume* logicwater_SD_2;
G4LogicalVolume* logicwater_SD_3;
G4LogicalVolume* logicwater_SD_4;
G4LogicalVolume* logicwater_SD_5;
G4LogicalVolume* logicwater_SD_6;
G4LogicalVolume* logicwater_SD_7;
G4LogicalVolume* logicwater_SD_8;
G4LogicalVolume* logicwater_SD_9;
G4LogicalVolume* logicwater_SD_10;

// sensitive detector mass value
G4LogicalVolume*  fScoringVolume; // Phantom mass;

G4LogicalVolume*  fScoringVolume_1;
G4LogicalVolume*  fScoringVolume_2;
G4LogicalVolume*  fScoringVolume_3;
G4LogicalVolume*  fScoringVolume_4;
G4LogicalVolume*  fScoringVolume_5;
G4LogicalVolume*  fScoringVolume_6;
G4LogicalVolume*  fScoringVolume_7;
G4LogicalVolume*  fScoringVolume_8;
G4LogicalVolume*  fScoringVolume_9;
G4LogicalVolume*  fScoringVolume_10;





//Material
//G4Material AIR;
G4double x,y,z; // gold nano position set up
};

#endif
