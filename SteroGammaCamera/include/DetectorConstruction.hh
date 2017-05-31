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
#include "G4Element.hh"
#include "G4MaterialPropertiesTable.hh"

//FOR SURFACE
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

//Rotation
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"



class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	void SetMaterial();
	void SetDimension();
	void SetSurfaceProperty();
	void SetRotationMatrix();
	void CalRotationMatrix();


	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();
private:
//	G4Transform3D transform1;

	G4Element* fH;
	G4Element* fC;
	G4Element* fN;
	G4Element* fO;


	G4Material *fGd2O3;
	G4Element *elO;
	G4Element *elGd;
	G4Material *G4_Eu;
	G4Material *fGd2O3_Eu;
	G4MaterialPropertiesTable *fGd2O3_Eu_mt;
	G4Material *Zinc68_mat;

	G4Material *fAir;
	G4MaterialPropertiesTable *vacuum_mt;

	G4Material *fVacuum;

	G4Material *G4_Pb;
	G4MaterialPropertiesTable *G4_Pb_mt;
	G4Material *fPb;

	//Dimension
	G4double WorldX;
	G4double WorldY;
	G4double WorldZ;

	G4double ScintX;
	G4double ScintY;
	G4double ScintZ;

	G4double SolidWaterX;
	G4double SolidWaterY;
	G4double SolidWaterZ;

	G4double OpDetectorX;
	G4double OpDetectorY;
	G4double OpDetectorZ;

	G4double GammaCameraMotherX;
	G4double GammaCameraMotherY;
	G4double GammaCameraMotherZ;

	G4int NumOfReplica;
	G4int NumOfWaterPhantom;

	G4double CollimatorHeight;

	//Surface
	G4OpticalSurface* CathodeSurface;


};

#endif
