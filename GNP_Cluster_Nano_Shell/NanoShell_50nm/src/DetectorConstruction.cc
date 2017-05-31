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
//
//

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"

#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"

#include "SensitiveDetector.hh"

#include "stdio.h"
#include "iostream"
#include "math.h"


DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),fScoringVolume_1(0), fScoringVolume_2(0), fScoringVolume_3(0), fScoringVolume_4(0),
 fScoringVolume_5(0), fScoringVolume_6(0), fScoringVolume_7(0), fScoringVolume_8(0), fScoringVolume_9(0), fScoringVolume_10(0)
{


}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

	//Gold nano position

//	    x = 1.0;
//		y = 1.0;
//		z = 1.0;

//		x = 0.5;
//		y = 0.5;
//		z = 0.5;

//		x = 0.25;
//    	y = 0.25;
//		z = 0.25;

		x = 0.09;
		y = 0.09;
		z = 0.09;



	G4double R = sqrt(x*x+y*y+z*z);

	G4cout<<"Distance of Center gold nano: "<<R*1000<<" nm"<<G4endl;
	G4cout<<"Distance of Surface gold nano: "<<(R*1000)-50<<" nm"<<G4endl;
	G4cout<<"\n"<<G4endl;
	// World
	G4VSolid* sol_World = new G4Box("World", 0.1*m, 0.1*m, 0.1*m);
	G4Material* AIR = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	G4LogicalVolume* lv_World = new G4LogicalVolume(sol_World, AIR, "World");
	G4VPhysicalVolume* pv_World =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_World, "World", 0, false, 0);

	// Water Phantom
	// Water box (x: 0.1 um, y: 0.1 um, z: 0.1 um, at (0, 0, 0))
	G4VSolid* sol_Geom = new G4Box("Water_box", 2.0*um, 2.0*um, 2.0*um);
	G4Material* WATER = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4LogicalVolume* lv_Geom = new G4LogicalVolume(sol_Geom, WATER, "Water_box");
	G4VPhysicalVolume* pv_Geom =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_Geom, "Water_box", lv_World, false, 01);
	//====================================================================================================================//
	//Sensitive detector 1(center)
	G4Material* WaterMat = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	//G4VSolid* WaterSD = new G4Box("WaterSD", 50.5*nm, 50.5*nm, 50.5*nm);
	G4Sphere* WaterSD_1=
			new G4Sphere("WaterSD_1",                       //its name
					25*nm, 35*nm, 0*deg, 360*deg, 0*deg, 360*deg);    //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_1 = new G4LogicalVolume(WaterSD_1,          //Multiple SD set up logicalwater_SD
			WaterMat,           //its material
			"WaterSD_1");            //its name
	G4VPhysicalVolume* physwater=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_1,          //its logical volume
					"WaterSD_1",             //its name
					lv_Geom,               //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					10,                    //copy number
					true);//Sensitive detector->water sphere

	G4VisAttributes* va_WaterSD_1
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_1->SetForceWireframe(true);
	logicwater_SD_1->SetVisAttributes(va_WaterSD_1);


	//==============================================================================================================================================
	//Sensitive detector 2
	//	G4Material* WaterMat_1 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_2=
			new G4Sphere("WaterSD_2",                       //its name
					35*nm, 45*nm, 0*deg, 360*deg, 0*deg, 360*deg);    //its size 50nm	//0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_2 = new G4LogicalVolume(WaterSD_2,          //its solid
			WaterMat,           //its material
			"WaterSD_2");            //its name
	G4VPhysicalVolume* physwater_2=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_2,            //its logical volume
					"WaterSD_2",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					20,                     //copy number
					true);

	G4VisAttributes* va_WaterSD_2
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_2->SetForceWireframe(true);
	logicwater_SD_2->SetVisAttributes(va_WaterSD_2);

	//=========================================================================================================================
	//Sensitive detector 3
	G4Material* WaterMat_3 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_3=
			new G4Sphere("WaterSD_3",                       //its name
					45*nm, 55*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm
	logicwater_SD_3 =
				new G4LogicalVolume(WaterSD_3,          //its solid
						WaterMat,           //its material
						"WaterSD_3");            //its name
	G4VPhysicalVolume* physwater_3=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_3,            //its logical volume
					"WaterSD_3",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					30,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_3
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_3->SetForceWireframe(true);
	logicwater_SD_3->SetVisAttributes(va_WaterSD_3);

	//==============================================================================================================================================
	//Sensitive detector 4
	//	G4Material* WaterMat_4 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_4=
			new G4Sphere("WaterSD_4",                       //its name
					55*nm, 65*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_4 =
				new G4LogicalVolume(WaterSD_4,          //its solid
						WaterMat,           //its material
						"WaterSD_4");            //its name
	G4VPhysicalVolume* physwater_4=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_4,            //its logical volume
					"WaterSD_4",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					40,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_4
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_4->SetForceWireframe(true);
	logicwater_SD_4->SetVisAttributes(va_WaterSD_4);

	//==============================================================================================================================================
	//Sensitive detector 5
	//	G4Material* WaterMat_5 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_5=
			new G4Sphere("WaterSD_5",                       //its name
					65*nm, 75*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_5 =
				new G4LogicalVolume(WaterSD_5,          //its solid
						WaterMat,           //its material
						"WaterSD_5");            //its name
	G4VPhysicalVolume* physwater_5=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_5,            //its logical volume
					"WaterSD_5",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					50,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_5
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_5->SetForceWireframe(true);
	logicwater_SD_5->SetVisAttributes(va_WaterSD_5);

	//==============================================================================================================================================
	//Sensitive detector 6
	//	G4Material* WaterMat_5 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_6=
			new G4Sphere("WaterSD_6",                       //its name
					75*nm, 85*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_6 =
				new G4LogicalVolume(WaterSD_6,          //its solid
						WaterMat,           //its material
						"WaterSD_6");            //its name
	G4VPhysicalVolume* physwater_6=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_6,            //its logical volume
					"WaterSD_6",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					60,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_6
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_6->SetForceWireframe(true);
	logicwater_SD_6->SetVisAttributes(va_WaterSD_6);

	//==============================================================================================================================================
	//Sensitive detector 7
	//	G4Material* WaterMat_7 = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4Sphere* WaterSD_7=
			new G4Sphere("WaterSD_7",                       //its name
					85*nm, 95*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_7=
				new G4LogicalVolume(WaterSD_7,          //its solid
						WaterMat,           //its material
						"WaterSD_7");            //its name
	G4VPhysicalVolume* physwater_7=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_7,            //its logical volume
					"WaterSD_7",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					70,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_7
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_7->SetForceWireframe(true);
	logicwater_SD_7->SetVisAttributes(va_WaterSD_7);

	//==============================================================================================================================================
	//Sensitive detector 8
	G4Sphere* WaterSD_8=
			new G4Sphere("WaterSD_8",                       //its name
					95*nm, 105*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm



	logicwater_SD_8 =
				new G4LogicalVolume(WaterSD_8,          //its solid
						WaterMat,           //its material
						"WaterSD_8");            //its name
	G4VPhysicalVolume* physwater_8=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_8,            //its logical volume
					"WaterSD_8",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					80,                     //copy number
					true);
	G4VisAttributes* va_WaterSD_8
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));

	va_WaterSD_8->SetForceWireframe(true);
	logicwater_SD_8->SetVisAttributes(va_WaterSD_8);

	//==============================================================================================================================================
	//Sensitive detector 9
	G4Sphere* WaterSD_9=
			new G4Sphere("WaterSD_9",                       //its name
					105*nm, 115*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm



	logicwater_SD_9 =
				new G4LogicalVolume(WaterSD_9,          //its solid
						WaterMat,           //its material
						"WaterSD_9");            //its name
	G4VPhysicalVolume* physwater_9=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_9,            //its logical volume
					"WaterSD_9",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					90,                     //copy number
					true);

	G4VisAttributes* va_WaterSD_9
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	va_WaterSD_9->SetForceWireframe(true);
	logicwater_SD_9->SetVisAttributes(va_WaterSD_9);



	//==============================================================================================================================================
	//Sensitive detector 10
	G4Sphere* WaterSD_10=
			new G4Sphere("WaterSD_10",                       //its name
					115*nm, 125*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//										 //0.000025*mm, 0.000030*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 25nm
	//										 //0.000006*mm, 0.000011*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 10nm

	logicwater_SD_10 =
				new G4LogicalVolume(WaterSD_10,          //its solid
						WaterMat,           //its material
						"WaterSD_10");            //its name
	G4VPhysicalVolume* physwater_10=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(0.0, 0.0, 0.0),       //at (0,0,0)
					logicwater_SD_10,            //its logical volume
					"WaterSD_10",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					100,                     //copy number
					true);

	G4VisAttributes* va_WaterSD_10
	= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	va_WaterSD_10->SetForceWireframe(true);
	logicwater_SD_10->SetVisAttributes(va_WaterSD_10);


	//================================================================================================================================
	//Nano gold particle center

	G4Material* GoldMat_0 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//  G4VSolid* goldnano_0 = new G4Box("Gold", 50*nm, 50*nm, 50*nm);
	G4Sphere* goldnano_0=
			new G4Sphere("Gold",                       //its name
					0*mm, 25*nm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 100nm
	//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//0*mm, 5.*cm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	logicgold_0 =
			new G4LogicalVolume(goldnano_0,          //its solid
					GoldMat_0,           //its material
					"Gold");            //its name1

	G4VPhysicalVolume* physgold_0=
			new G4PVPlacement(0,                     //no rotation
					//G4ThreeVector(px*units,py*units,pz*units),       //at (0,0,0)
					G4ThreeVector(0*nm,0*nm,0*nm),
					//G4ThreeVector(0.0*nm,0.0*nm,0.0*nm),
					logicgold_0,            //its logical volume
					"Gold",               //its name
					lv_Geom,           	//its mother  volume(G4LogicalVolume* sol_World)
					false,               //no boolean operation
					10000,                 //copy number
					true);

	G4VisAttributes* va_goldnano_0
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));

	va_goldnano_0->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_0);

	//Nano gold particle_1
	//									               G4Material* GoldMat_1 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//									               G4Sphere* goldnano_1=
	//										           new G4Sphere("Gold_1",                       //its name
	//											        0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//							           		       //0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//							           	           //0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//										           G4LogicalVolume* logicgold_1 =
	//										           new G4LogicalVolume(goldnano_1,          //its solid
	//															  GoldMat_1,           //its material
	//															  "Gold_1");            //its name


	G4VPhysicalVolume* physgold_1=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(-x*um,y*um,z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_1",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					20000,                     //copy number
					true);

	G4VisAttributes* va_goldnano_1
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));

	va_goldnano_1->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_1);

	//Nano gold particle_2
	//										            G4Material* GoldMat_2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//										             G4Sphere* goldnano_2=
	//													 new G4Sphere("Gold_2",                       //its name
	//										     		 0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//											       	//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//										           	//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_2 =
	//													 new G4LogicalVolume(goldnano_2,          //its solid
	//													 GoldMat_2,           //its material
	//													"Gold_2");            //its name

	G4VPhysicalVolume* physgold_2=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(x*um,y*um,z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_2",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					30000,                     //copy number
					true);

	G4VisAttributes* va_goldnano_2
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_2->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_2);

	//Nano gold particle_3
	//													G4Material* GoldMat_3 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_3=
	//													 new G4Sphere("Gold_3",                       //its name
	//													 0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_3 =
	//													new G4LogicalVolume(goldnano_3,          //its solid
	//													GoldMat_3,           //its material
	//													"Gold_3");            //its name
	G4VPhysicalVolume* physgold_3=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(x*um,-y*um,z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_3",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					40000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_3
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_3->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_3);

	//Nano gold particle_4
	//													G4Material* GoldMat_4 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_4=
	//													new G4Sphere("Gold_4",                       //its name
	//													0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_4 =
	//													new G4LogicalVolume(goldnano_4,          //its solid
	//													GoldMat_4,           //its material
	//													"Gold_4");            //its name
	G4VPhysicalVolume* physgold_4=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(-x*um,-y*um,z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_4",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					50000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_4
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_4->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_4);

	//Nano gold particle_5
	//													G4Material* GoldMat_5 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_5=
	//													new G4Sphere("Gold_5",                       //its name
	//													0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_5 =
	//													new G4LogicalVolume(goldnano_5,          //its solid
	//													GoldMat_5,           //its material
	//													"Gold_5");            //its name
	G4VPhysicalVolume* physgold_5=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(-x*um,y*um,-z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_5",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					60000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_5
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_5->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_5);

	//Nano gold particle_6
	//													G4Material* GoldMat_6 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_6=
	//													new G4Sphere("Gold_6",                       //its name
	//													0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_6 =
	//													new G4LogicalVolume(goldnano_6,          //its solid
	//													GoldMat_6,           //its material
	//													"Gold_6");            //its name
	G4VPhysicalVolume* physgold_6=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(x*um,y*um,-z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_6",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					70000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_6
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_6->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_6);
	//Nano gold particle_7
	//													G4Material* GoldMat_7 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_7=
	//													new G4Sphere("Gold_7",                       //its name
	//													0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_7 =
	//													new G4LogicalVolume(goldnano_7,          //its solid
	//													GoldMat_7,           //its material
	//													"Gold_7");            //its name
	G4VPhysicalVolume* physgold_7=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(x*um,-y*um,-z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_7",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					80000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_7
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_7->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_7);

	//Nano gold particle_8
	//													G4Material* GoldMat_8 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
	//													G4Sphere* goldnano_8=
	//													new G4Sphere("Gold_8",                       //its name
	//													0*mm, 0.000025*mm, 0*deg, 360*deg, 0*deg, 360*deg);     //its size 50nm
	//													//0*mm, 0.000010*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 20nm
	//													//0*mm, 0.6*mm, 0*deg, 360*deg, 0*deg, 360*deg);		// its size 10nm
	//													G4LogicalVolume* logicgold_8 =
	//													new G4LogicalVolume(goldnano_8,          //its solid
	//													GoldMat_8,           //its material
	//													"Gold_8");            //its name
	G4VPhysicalVolume* physgold_8=
			new G4PVPlacement(0,                     //no rotation
					G4ThreeVector(-x*um,-y*um,-z*um),       //at (0,0,0)
					logicgold_0,            //its logical volume
					"Gold_8",               //its name
					lv_Geom,           //its mother  volume(G4LogicalVolume* sol_World)
					false,                 //no boolean operation
					90000,                     //copy number
					true);
	G4VisAttributes* va_goldnano_8
	= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	va_goldnano_8->SetForceSolid(true);
	logicgold_0->SetVisAttributes(va_goldnano_8);

	// Visualization
	G4VisAttributes* va_World = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_World->SetForceWireframe(true);
	lv_World->SetVisAttributes(va_World);

	G4VisAttributes* va_Geom = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
	va_Geom->SetForceWireframe(true);
	lv_Geom->SetVisAttributes(va_Geom);


	fScoringVolume_1 = logicwater_SD_1;
	fScoringVolume_2 = logicwater_SD_2;
	fScoringVolume_3 = logicwater_SD_3;
	fScoringVolume_4 = logicwater_SD_4;
	fScoringVolume_5 = logicwater_SD_5;
	fScoringVolume_6 = logicwater_SD_6;
	fScoringVolume_7 = logicwater_SD_7;
	fScoringVolume_8 = logicwater_SD_8;
	fScoringVolume_9 = logicwater_SD_9;
	fScoringVolume_10 = logicwater_SD_10;

	fScoringVolume = lv_Geom;

	return pv_World;
}

void DetectorConstruction::ConstructSDandField()
{
	// Set sensitive detector on "Geometry"
	G4VSensitiveDetector* mySD = new SensitiveDetector("WaterSD");
	SetSensitiveDetector(logicwater_SD_1, mySD);
	SetSensitiveDetector(logicwater_SD_2, mySD);
	SetSensitiveDetector(logicwater_SD_3, mySD);
	SetSensitiveDetector(logicwater_SD_4, mySD);
	SetSensitiveDetector(logicwater_SD_5, mySD);
	SetSensitiveDetector(logicwater_SD_6, mySD);
	SetSensitiveDetector(logicwater_SD_7, mySD);
	SetSensitiveDetector(logicwater_SD_8, mySD);
	SetSensitiveDetector(logicwater_SD_9, mySD);
	SetSensitiveDetector(logicwater_SD_10, mySD);

}


