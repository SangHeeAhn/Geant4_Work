//
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
// The code was written by :
//	^Claudio Andenna  claudio.andenna@ispesl.it, claudio.andenna@iss.infn.it
//      *Barbara Caccia barbara.caccia@iss.it
//      with the support of Pablo Cirrone (LNS, INFN Catania Italy)
//	with the contribute of Alessandro Occhigrossi*
//
// ^INAIL DIPIA - ex ISPESL and INFN Roma, gruppo collegato Sanit�, Italy
// *Istituto Superiore di Sanit� and INFN Roma, gruppo collegato Sanit�, Italy
//  Viale Regina Elena 299, 00161 Roma (Italy)
//  tel (39) 06 49902246
//  fax (39) 06 49387075
//
// more information:
// http://g4advancedexamples.lngs.infn.it/Examples/medical-linac
//
//*******************************************************//


#include "ML2Acc1.hh"
#include "ML2Acc1Messenger.hh"

CML2Acc1::CML2Acc1()
{
	this->acc1Messenger=new CML2Acc1Messenger(this);
}

CML2Acc1::~CML2Acc1(void)
{
}
CML2Acc1* CML2Acc1::instance = 0;

CML2Acc1* CML2Acc1::GetInstance(void)
{
  if (instance == 0)
    {
      instance = new CML2Acc1();
    }
  return instance;
}
void CML2Acc1::writeInfo()
{
	std::cout <<"\n\n\tnominal beam energy: "<<this->idEnergy << G4endl;
	std::cout <<"\tJaw X aperture: 1) "<< this->jaw1XAperture/mm<<"[mm]\t2) " << this->jaw2XAperture/mm<< " [mm]"<< G4endl;
	std::cout <<"\tJaw Y aperture: 1) "<< this->jaw1YAperture/mm<<"[mm]\t2) " << this->jaw2YAperture/mm<< " [mm]\n"<< G4endl;
}
G4Material * CML2Acc1::otherMaterials(const G4String materialName)
{
	G4Material * material=0;
	G4String name;
	name = materialName;
	return material;
}
void CML2Acc1::Construct(G4VPhysicalVolume *PVWorld, G4double isoCentre)
{
	this->PVWorld=PVWorld;
	this->setIsoCentre(isoCentre);
	switch (this->idEnergy)
	{
		case 6:

			this->target();
			break;
		case 10:
			this->target_10MV();
			break;
	}
	//this->target_modify();
	this->primaryCollimator();
	//this->primaryCollimator_modify();
	this->BeWindow();
	this->ionizationChamber();
	//this->flatteningFilter();
	switch (this->idEnergy)
	{
		case 6:
			this->flatteningFilter_modify();
			break;
		case 10:
			this->flatteningFilter_modify_10MV();
			break;
	}
	this->mirror();
	this->Jaw1X();
	this->Jaw2X();
	this->Jaw1Y();
	this->Jaw2Y();
	this->DYNVMLC();
	//this->MLC();
	//this->Upper_Wedge();
	//this->Lower_Wedge();
	//this->Reticle();

}
void CML2Acc1::reset()
{
	this->leavesA.clear();
	this->leavesB.clear();
}
bool CML2Acc1::target()
{
	//    materials
	G4Material* Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
	G4Material* W = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

	switch (this->idEnergy)
	{
		case 6:

		//    volumes
		//    beam line along z axis
		G4double ZdistanceofTarget = -0.0889*cm;


		//------------------------target 6MV------------------------
		G4double targetADim_x = 0.4*cm;
		G4double targetADim_y = 0.4*cm;
		G4double targetADim_z = 0.0889*cm;
		G4Box* targetA_box = new G4Box("targetA_box",targetADim_x,targetADim_y,targetADim_z/2.);
		G4LogicalVolume *targetA_log = new G4LogicalVolume(targetA_box,W,"targetA_log",0,0,0);

		G4double targetAPos_x = 0.*cm;
		G4double targetAPos_y = 0.*cm;
		G4double targetAPos_z = ZdistanceofTarget + (targetADim_z/2.);
		ZdistanceofTarget += targetADim_z;

		G4VPhysicalVolume *targetA_phys=0;
		targetA_phys = new G4PVPlacement(0,
						G4ThreeVector(targetAPos_x,targetAPos_y,targetAPos_z),
						"targetA",targetA_log,this->PVWorld,false,0);

		G4double targetBDim_x = 0.4*cm;
		G4double targetBDim_y = 0.4*cm;
		G4double targetBDim_z = 0.1575*cm;
		G4Box* targetB_box = new G4Box("targetB_box",targetBDim_x,targetBDim_y,targetBDim_z/2.);
		G4LogicalVolume *targetB_log = new G4LogicalVolume(targetB_box,Cu,"targetB_log",0,0,0);
		G4double targetBPos_x = 0.*cm;
		G4double targetBPos_y = 0.*cm;
		G4double targetBPos_z = ZdistanceofTarget + (targetBDim_z/2.);
		ZdistanceofTarget += targetBDim_z;
		G4VPhysicalVolume *targetB_phys=0;
		targetB_phys = new G4PVPlacement(0,
						G4ThreeVector(targetBPos_x,targetBPos_y,targetBPos_z),
						"targetB",targetB_log,this->PVWorld,false,0);


		// ***********  REGIONS for CUTS

		G4Region *regVol;
		regVol= new G4Region("targetR");
		G4ProductionCuts* cuts = new G4ProductionCuts;
		cuts->SetProductionCut(0.1*cm);
		regVol->SetProductionCuts(cuts);

		targetA_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(targetA_log);
		targetB_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(targetB_log);

		// Visualization attributes

		G4VisAttributes* simpleWVisAtt, *simpleCuVisAtt;
		simpleWVisAtt= new G4VisAttributes(G4Colour::Gray());
		simpleWVisAtt->SetVisibility(true);
		simpleWVisAtt->SetForceSolid(true);
		simpleCuVisAtt= new G4VisAttributes(G4Colour::Cyan());
		simpleCuVisAtt->SetVisibility(true);
		simpleCuVisAtt->SetForceSolid(true);
		targetA_log->SetVisAttributes(simpleWVisAtt);
		targetB_log->SetVisAttributes(simpleCuVisAtt);

		return true;
		break;
	}
	return false;
}
bool CML2Acc1::target_10MV()
{
		//    materials
		G4Material* Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");


		switch (this->idEnergy)
		{
			case 10:

		//    volumes
		//    beam line along z axis
		G4double ZdistanceofTarget = 0.*cm;


		//------------------------target 10MV------------------------
		G4double targetADim_x = 0.6*cm;
		G4double targetADim_y = 0.6*cm;
		G4double targetADim_z = 0.5715*cm;
		G4Box* targetA_box = new G4Box("targetA_box",targetADim_x,targetADim_y,targetADim_z/2.);
		G4LogicalVolume *targetA_log = new G4LogicalVolume(targetA_box,Cu,"targetA_log",0,0,0);

		G4double targetAPos_x = 0.*cm;
		G4double targetAPos_y = 0.*cm;
		G4double targetAPos_z = ZdistanceofTarget + (targetADim_z/2.);
		ZdistanceofTarget += targetADim_z;

		G4VPhysicalVolume *targetA_phys=0;
		targetA_phys = new G4PVPlacement(0,
						G4ThreeVector(targetAPos_x,targetAPos_y,targetAPos_z),
						"targetA",targetA_log,this->PVWorld,false,0);


		// ***********  REGIONS for CUTS

		G4Region *regVol;
		regVol= new G4Region("targetR");
		G4ProductionCuts* cuts = new G4ProductionCuts;
		cuts->SetProductionCut(0.1*cm);
		regVol->SetProductionCuts(cuts);

		targetA_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(targetA_log);


		// Visualization attributes

		G4VisAttributes* simpleWVisAtt;
		simpleWVisAtt= new G4VisAttributes(G4Colour::Magenta());
		simpleWVisAtt->SetVisibility(true);
		simpleWVisAtt->SetForceSolid(true);
		targetA_log->SetVisAttributes(simpleWVisAtt);

		return true;
		break;
	}
	return false;
}


bool CML2Acc1::primaryCollimator()
{

  //    materials

	G4Material* W = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

  //    colors

   G4Colour  magenta (1.0, 0.0, 1.0);

 //---------rotation matrix first collimator --------

  /*G4RotationMatrix*  rotateMatrix=new G4RotationMatrix();
  rotateMatrix->rotateX(180.0*deg);*/

  //-------------------- the first collimator upper----------------
   G4double ZdistanceofCollimator = 0.*cm;


  G4double innerRadiusOfTheTubeEx = 1.0*cm;
  G4double outerRadiusOfTheTubeEx = 3.772*cm;
  G4double heightOfTheTubeEx = 1.524*cm;
  G4double startAngleOfTheTubeEx = 0.*deg;
  G4double spanningAngleOfTheTubeEx = 360.*deg;
  G4Tubs* UpperCollimator = new G4Tubs("UpperCollimator",innerRadiusOfTheTubeEx,
                                    outerRadiusOfTheTubeEx,heightOfTheTubeEx/2.,
				    startAngleOfTheTubeEx,spanningAngleOfTheTubeEx);
  G4LogicalVolume *UpperCollimator_log = new G4LogicalVolume(UpperCollimator,W,"UpperCollimator_log",0,0,0);

	G4double UpperCollimatorPosX = 0.*cm;
	G4double UpperCollimatorPosY = 0.*cm;
	G4double UpperCollimatorPosZ = ZdistanceofCollimator + (heightOfTheTubeEx/2.);
	ZdistanceofCollimator += heightOfTheTubeEx;

  G4VPhysicalVolume *UpperCollimator_phys=0;
  UpperCollimator_phys = new G4PVPlacement(0,
					   G4ThreeVector(UpperCollimatorPosX,UpperCollimatorPosY,
							 UpperCollimatorPosZ),"UpperCollimator",
					   UpperCollimator_log,this->PVWorld,false,0);



  //-------------------- the first collimator lower----------------

  G4double  pRmin1 = 0.380*cm;

  G4double  pRmax1 = 3.772*cm;
  G4double  pRmin2 = 1.900*cm;
  G4double  pRmax2 = 3.772*cm;
  G4double  heightOfTheCone =6.096*cm;
  G4double  startAngleOfTheCone = 0.*deg;
  G4double  spanningAngleOfTheCone = 360.*deg;

  G4Cons* collim_cone = new G4Cons("collim_cone",pRmin1,pRmax1,pRmin2,
   	   	   	   	   	   pRmax2,heightOfTheCone/2.,startAngleOfTheCone,
		   	   	   	   	   	   	   spanningAngleOfTheCone);
  G4LogicalVolume *collim_log = new G4LogicalVolume(collim_cone,W,"collim_log",0,0,0);

	G4double Collimator_Cone_PosX = 0.*cm;
	G4double Collimator_Cone_PosY = 0.*cm;
	G4double Collimator_Cone_PosZ = ZdistanceofCollimator + (heightOfTheCone/2.);
	ZdistanceofCollimator += heightOfTheCone;
	G4VPhysicalVolume *collim_phys=0;
	collim_phys = new G4PVPlacement(0,
					G4ThreeVector(Collimator_Cone_PosX,Collimator_Cone_PosY,Collimator_Cone_PosZ),
					"collimator",collim_log,this->PVWorld,false,0);

//--------- Visualization attributes -------------------------------
   G4VisAttributes* simpleTungstenVisAtt= new G4VisAttributes(G4Colour::Magenta());
   simpleTungstenVisAtt->SetVisibility(true);
   simpleTungstenVisAtt->SetForceSolid(true);
   UpperCollimator_log->SetVisAttributes(simpleTungstenVisAtt);
   collim_log->SetVisAttributes(simpleTungstenVisAtt);

	// ***********  REGIONS for CUTS

   G4Region *regVol;
	regVol= new G4Region("PrymCollR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*cm);
	regVol->SetProductionCuts(cuts);

	collim_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(collim_log);
	UpperCollimator_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(UpperCollimator_log);
	return true;
}

bool CML2Acc1::BeWindow()
{
	bool bCreated=false;

  //    materials
	G4Material *Be=G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");

	G4double ZdistanceofTarget = 8.89*cm;

	G4double innerRadiusOfTheTube = 0.*cm;
	G4double outerRadiusOfTheTube = 2.6*cm;
	G4double heightOfTheTube = 0.0254*cm;
	G4double startAngleOfTheTube = 0.*deg;
	G4double spanningAngleOfTheTube = 360.*deg;

	G4Tubs* BeWTube = new G4Tubs("BeWindowTube",innerRadiusOfTheTube,
									outerRadiusOfTheTube,heightOfTheTube/2.,
									startAngleOfTheTube,spanningAngleOfTheTube);

	G4LogicalVolume *BeWTubeLV = new G4LogicalVolume(BeWTube, Be, "BeWTubeLV", 0, 0, 0);

	G4double BeWindowPos_x = 0.*cm;
	G4double BeWindowPos_y = 0.*cm;
	G4double BeWindowPos_z = ZdistanceofTarget + (heightOfTheTube/2.);
	ZdistanceofTarget += heightOfTheTube;
	G4VPhysicalVolume *BeWTubePV=0;
	BeWTubePV=new G4PVPlacement(0, G4ThreeVector(BeWindowPos_x,BeWindowPos_y,
			BeWindowPos_z), "BeWTubePV", BeWTubeLV, this->PVWorld, false, 0);

	G4Region *regVol;
	G4VisAttributes* simpleAlVisAtt;

	// Region for cuts
	regVol= new G4Region("BeWindow");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*cm);
	regVol->SetProductionCuts(cuts);

	//--------- Visualization attributes -------------------------------
	simpleAlVisAtt= new G4VisAttributes(G4Colour::Yellow());
	simpleAlVisAtt->SetVisibility(true);
	simpleAlVisAtt->SetForceSolid(false);
	BeWTubeLV->SetVisAttributes(simpleAlVisAtt);
	BeWTubeLV->SetRegion(regVol);
	regVol->AddRootLogicalVolume(BeWTubeLV);

	bCreated=true;
	return true;
}

bool CML2Acc1::flatteningFilter()
{
	switch (this->idEnergy)
	{
		case 6:
	G4double z0, h0;
	G4ThreeVector centre, halSize;
	G4Material *Cu=G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region("flatfilterR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.5*cm);
	regVol->SetProductionCuts(cuts);

	G4VisAttributes* simpleAlVisAtt;

	// one
	z0=130.0*mm;
	h0=5.0/2.*cm;
	centre.set(0.,0.,z0);
	G4Cons *FFL1A_1Cone = new G4Cons("FFL1A_1", 0.*cm, 0.3*cm, 0.*cm, 5.*cm, h0, 0.*deg, 360.*deg);
	G4LogicalVolume *FFL1A_1LV = new G4LogicalVolume(FFL1A_1Cone, Cu, "FFL1A_1LV", 0, 0, 0);
	G4VPhysicalVolume *FFL1A_1PV=0;
	FFL1A_1PV=new G4PVPlacement(0, centre, "FFL1A_1PV", FFL1A_1LV, this->PVWorld, false, 0);

	// two
	z0+=h0;
	h0=0.081/2.*cm;
	z0+=h0;
	centre.setZ(z0);
	z0+=h0;
	G4Tubs *FFL2_1Tube = new G4Tubs("FFL6_1", 0.*cm, 2.5*cm, h0, 0.*deg, 360.*deg);
	G4LogicalVolume *FFL2_1LV = new G4LogicalVolume(FFL2_1Tube, Cu, "FFL2_1LV", 0, 0, 0);
	G4VPhysicalVolume *FFL2_1PV=0;
	FFL2_1PV=new G4PVPlacement(0, centre, "FFL2_1PV", FFL2_1LV, this->PVWorld, false, 0);

	simpleAlVisAtt= new G4VisAttributes(G4Colour::Red());
	simpleAlVisAtt->SetVisibility(true);
// 	simpleAlSVisAtt->SetForceSolid(true);
	FFL1A_1LV->SetVisAttributes(simpleAlVisAtt);
	FFL2_1LV->SetVisAttributes(simpleAlVisAtt);

	FFL1A_1LV->SetRegion(regVol);
	FFL2_1LV->SetRegion(regVol);

	regVol->AddRootLogicalVolume(FFL1A_1LV);
	regVol->AddRootLogicalVolume(FFL2_1LV);
	return true;
	break;
	}
	return false;
}

bool CML2Acc1::flatteningFilter_modify()
{
	switch (this->idEnergy)
	{
		case 6:
		//------------------------target 6MV------------------------
		//    materials

		G4Material* OFECu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

		G4double ZdistanceofFlatFilter = 11.698*cm;

		 //  ------------------------1------------------------ //
		G4double innerMinRadiusOfThecone1 = 0.*cm;
		G4double innerMaxRadiusOfThecone1 = 0.*cm;
		G4double outerMinRadiusOfThecone1 = 0.*cm;
		G4double outerMaxRadiusOfThecone1 = 0.025*cm;
		G4double heightOfThecone1 = 0.011*cm;
		G4double startAngleOfThecone1 = 0.*deg;
		G4double spanningAngleOfThecone1 = 360.*deg;
		G4Cons* FlatFilter_cone1 = new G4Cons("FlatFilter_cone1",innerMinRadiusOfThecone1,innerMaxRadiusOfThecone1,
										outerMinRadiusOfThecone1,outerMaxRadiusOfThecone1,
									 heightOfThecone1/2., startAngleOfThecone1, spanningAngleOfThecone1);
		G4LogicalVolume *FlatFilter_cone1_log = new G4LogicalVolume(FlatFilter_cone1,OFECu,"FlatFilter_cone1_log",0,0,0);

		G4double FlatFilter_cone1_PosX = 0.*cm;
		G4double FlatFilter_cone1_PosY = 0.*cm;
		G4double FlatFilter_cone1_PosZ = ZdistanceofFlatFilter + (heightOfThecone1/2.);
		ZdistanceofFlatFilter += heightOfThecone1;
		G4VPhysicalVolume *FlatFilter_cone1_phys=0;
		FlatFilter_cone1_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone1_PosX,FlatFilter_cone1_PosY,
								   FlatFilter_cone1_PosZ),"FlatFilter_cone1",
								   FlatFilter_cone1_log,this->PVWorld,false,0);


		 //  ------------------------2------------------------ //
		G4double innerMinRadiusOfThecone2 = 0.*cm;
		G4double innerMaxRadiusOfThecone2 = 0.025*cm;
		G4double outerMinRadiusOfThecone2 = 0.*cm;
		G4double outerMaxRadiusOfThecone2 = 0.05*cm;
		G4double heightOfThecone2 = 0.011*cm;
		G4double startAngleOfThecone2 = 0.*deg;
		G4double spanningAngleOfThecone2 = 360.*deg;
		G4Cons* FlatFilter_cone2 = new G4Cons("FlatFilter_cone2",innerMinRadiusOfThecone2,innerMaxRadiusOfThecone2,
										outerMinRadiusOfThecone2,outerMaxRadiusOfThecone2,
									 heightOfThecone2/2., startAngleOfThecone2, spanningAngleOfThecone2);
		G4LogicalVolume *FlatFilter_cone2_log = new G4LogicalVolume(FlatFilter_cone2,OFECu,"FlatFilter_cone2_log",0,0,0);

		G4double FlatFilter_cone2_PosX = 0.*cm;
		G4double FlatFilter_cone2_PosY = 0.*cm;
		G4double FlatFilter_cone2_PosZ = ZdistanceofFlatFilter + (heightOfThecone2/2.);
		ZdistanceofFlatFilter += heightOfThecone2;
		G4VPhysicalVolume *FlatFilter_cone2_phys=0;
		FlatFilter_cone2_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone2_PosX,FlatFilter_cone2_PosY,
								   FlatFilter_cone2_PosZ),"FlatFilter_cone2",
								   FlatFilter_cone2_log,this->PVWorld,false,0);


		 //  ------------------------3------------------------ //
		G4double innerMinRadiusOfThecone3 = 0.*cm;
		G4double innerMaxRadiusOfThecone3 = 0.05*cm;
		G4double outerMinRadiusOfThecone3 = 0.*cm;
		G4double outerMaxRadiusOfThecone3 = 0.075*cm;
		G4double heightOfThecone3 = 0.015*cm;
		G4double startAngleOfThecone3 = 0.*deg;
		G4double spanningAngleOfThecone3 = 360.*deg;
		G4Cons* FlatFilter_cone3 = new G4Cons("FlatFilter_cone3",innerMinRadiusOfThecone3,innerMaxRadiusOfThecone3,
										outerMinRadiusOfThecone3,outerMaxRadiusOfThecone3,
									 heightOfThecone3/2., startAngleOfThecone3, spanningAngleOfThecone3);
		G4LogicalVolume *FlatFilter_cone3_log = new G4LogicalVolume(FlatFilter_cone3,OFECu,"FlatFilter_cone3_log",0,0,0);

		G4double FlatFilter_cone3_PosX = 0.*cm;
		G4double FlatFilter_cone3_PosY = 0.*cm;
		G4double FlatFilter_cone3_PosZ = ZdistanceofFlatFilter + (heightOfThecone3/2.);
		ZdistanceofFlatFilter += heightOfThecone3;
		G4VPhysicalVolume *FlatFilter_cone3_phys=0;
		FlatFilter_cone3_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone3_PosX,FlatFilter_cone3_PosY,
								   FlatFilter_cone3_PosZ),"FlatFilter_cone3",
								   FlatFilter_cone3_log,this->PVWorld,false,0);


		 //  ------------------------4------------------------ //
		G4double innerMinRadiusOfThecone4 = 0.*cm;
		G4double innerMaxRadiusOfThecone4 = 0.075*cm;
		G4double outerMinRadiusOfThecone4 = 0.*cm;
		G4double outerMaxRadiusOfThecone4 = 0.1*cm;
		G4double heightOfThecone4 = 0.016*cm;
		G4double startAngleOfThecone4 = 0.*deg;
		G4double spanningAngleOfThecone4 = 360.*deg;
		G4Cons* FlatFilter_cone4 = new G4Cons("FlatFilter_cone4",innerMinRadiusOfThecone4,innerMaxRadiusOfThecone4,
										outerMinRadiusOfThecone4,outerMaxRadiusOfThecone4,
									 heightOfThecone4/2., startAngleOfThecone4, spanningAngleOfThecone4);
		G4LogicalVolume *FlatFilter_cone4_log = new G4LogicalVolume(FlatFilter_cone4,OFECu,"FlatFilter_cone4_log",0,0,0);

		G4double FlatFilter_cone4_PosX = 0.*cm;
		G4double FlatFilter_cone4_PosY = 0.*cm;
		G4double FlatFilter_cone4_PosZ = ZdistanceofFlatFilter + (heightOfThecone4/2.);
		ZdistanceofFlatFilter += heightOfThecone4;
		G4VPhysicalVolume *FlatFilter_cone4_phys=0;
		FlatFilter_cone4_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone4_PosX,FlatFilter_cone4_PosY,
								   FlatFilter_cone4_PosZ),"FlatFilter_cone4",
								   FlatFilter_cone4_log,this->PVWorld,false,0);

		 //  ------------------------5------------------------ //
		G4double innerMinRadiusOfThecone5 = 0.*cm;
		G4double innerMaxRadiusOfThecone5 = 0.1*cm;
		G4double outerMinRadiusOfThecone5 = 0.*cm;
		G4double outerMaxRadiusOfThecone5 = 0.15*cm;
		G4double heightOfThecone5 = 0.029*cm;
		G4double startAngleOfThecone5 = 0.*deg;
		G4double spanningAngleOfThecone5 = 360.*deg;
		G4Cons* FlatFilter_cone5 = new G4Cons("FlatFilter_cone5",innerMinRadiusOfThecone5,innerMaxRadiusOfThecone5,
										outerMinRadiusOfThecone5,outerMaxRadiusOfThecone5,
									 heightOfThecone5/2., startAngleOfThecone5, spanningAngleOfThecone5);
		G4LogicalVolume *FlatFilter_cone5_log = new G4LogicalVolume(FlatFilter_cone5,OFECu,"FlatFilter_cone5_log",0,0,0);

		G4double FlatFilter_cone5_PosX = 0.*cm;
		G4double FlatFilter_cone5_PosY = 0.*cm;
		G4double FlatFilter_cone5_PosZ = ZdistanceofFlatFilter + (heightOfThecone5/2.);
		ZdistanceofFlatFilter += heightOfThecone5;
		G4VPhysicalVolume *FlatFilter_cone5_phys=0;
		FlatFilter_cone5_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone5_PosX,FlatFilter_cone5_PosY,
								   FlatFilter_cone5_PosZ),"FlatFilter_cone5",
								   FlatFilter_cone5_log,this->PVWorld,false,0);


		 //  ------------------------6------------------------ //
		G4double innerMinRadiusOfThecone6 = 0.*cm;
		G4double innerMaxRadiusOfThecone6 = 0.15*cm;
		G4double outerMinRadiusOfThecone6 = 0.*cm;
		G4double outerMaxRadiusOfThecone6 = 0.2*cm;
		G4double heightOfThecone6 = 0.053*cm;
		G4double startAngleOfThecone6 = 0.*deg;
		G4double spanningAngleOfThecone6 = 360.*deg;
		G4Cons* FlatFilter_cone6 = new G4Cons("FlatFilter_cone6",innerMinRadiusOfThecone6,innerMaxRadiusOfThecone6,
										outerMinRadiusOfThecone6,outerMaxRadiusOfThecone6,
									 heightOfThecone6/2., startAngleOfThecone6, spanningAngleOfThecone6);
		G4LogicalVolume *FlatFilter_cone6_log = new G4LogicalVolume(FlatFilter_cone6,OFECu,"FlatFilter_cone6_log",0,0,0);

		G4double FlatFilter_cone6_PosX = 0.*cm;
		G4double FlatFilter_cone6_PosY = 0.*cm;
		G4double FlatFilter_cone6_PosZ = ZdistanceofFlatFilter + (heightOfThecone6/2.);
		ZdistanceofFlatFilter += heightOfThecone6;
		G4VPhysicalVolume *FlatFilter_cone6_phys=0;
		FlatFilter_cone6_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone6_PosX,FlatFilter_cone6_PosY,
								   FlatFilter_cone6_PosZ),"FlatFilter_cone6",
								   FlatFilter_cone6_log,this->PVWorld,false,0);


		 //  ------------------------7------------------------ //
		G4double innerMinRadiusOfThecone7 = 0.*cm;
		G4double innerMaxRadiusOfThecone7 = 0.2*cm;
		G4double outerMinRadiusOfThecone7 = 0.*cm;
		G4double outerMaxRadiusOfThecone7 = 0.25*cm;
		G4double heightOfThecone7 = 0.043*cm;
		G4double startAngleOfThecone7 = 0.*deg;
		G4double spanningAngleOfThecone7 = 360.*deg;
		G4Cons* FlatFilter_cone7 = new G4Cons("FlatFilter_cone7",innerMinRadiusOfThecone7,innerMaxRadiusOfThecone7,
										outerMinRadiusOfThecone7,outerMaxRadiusOfThecone7,
									 heightOfThecone7/2., startAngleOfThecone7, spanningAngleOfThecone7);
		G4LogicalVolume *FlatFilter_cone7_log = new G4LogicalVolume(FlatFilter_cone7,OFECu,"FlatFilter_cone7_log",0,0,0);

		G4double FlatFilter_cone7_PosX = 0.*cm;
		G4double FlatFilter_cone7_PosY = 0.*cm;
		G4double FlatFilter_cone7_PosZ = ZdistanceofFlatFilter + (heightOfThecone7/2.);
		ZdistanceofFlatFilter += heightOfThecone7;
		G4VPhysicalVolume *FlatFilter_cone7_phys=0;
		FlatFilter_cone7_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone7_PosX,FlatFilter_cone7_PosY,
								   FlatFilter_cone7_PosZ),"FlatFilter_cone7",
								   FlatFilter_cone7_log,this->PVWorld,false,0);

		 //  ------------------------8------------------------ //
		G4double innerMinRadiusOfThecone8 = 0.*cm;
		G4double innerMaxRadiusOfThecone8 = 0.25*cm;
		G4double outerMinRadiusOfThecone8 = 0.*cm;
		G4double outerMaxRadiusOfThecone8 = 0.3*cm;
		G4double heightOfThecone8 = 0.043*cm;
		G4double startAngleOfThecone8 = 0.*deg;
		G4double spanningAngleOfThecone8 = 360.*deg;
		G4Cons* FlatFilter_cone8 = new G4Cons("FlatFilter_cone8",innerMinRadiusOfThecone8,innerMaxRadiusOfThecone8,
										outerMinRadiusOfThecone8,outerMaxRadiusOfThecone8,
									 heightOfThecone8/2., startAngleOfThecone8, spanningAngleOfThecone8);
		G4LogicalVolume *FlatFilter_cone8_log = new G4LogicalVolume(FlatFilter_cone8,OFECu,"FlatFilter_cone8_log",0,0,0);

		G4double FlatFilter_cone8_PosX = 0.*cm;
		G4double FlatFilter_cone8_PosY = 0.*cm;
		G4double FlatFilter_cone8_PosZ = ZdistanceofFlatFilter + (heightOfThecone8/2.);
		ZdistanceofFlatFilter += heightOfThecone8;
		G4VPhysicalVolume *FlatFilter_cone8_phys=0;
		FlatFilter_cone8_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone8_PosX,FlatFilter_cone8_PosY,
								   FlatFilter_cone8_PosZ),"FlatFilter_cone8",
								   FlatFilter_cone8_log,this->PVWorld,false,0);


		 //  ------------------------9------------------------ //
		G4double innerMinRadiusOfThecone9 = 0.*cm;
		G4double innerMaxRadiusOfThecone9 = 0.3*cm;
		G4double outerMinRadiusOfThecone9 = 0.*cm;
		G4double outerMaxRadiusOfThecone9 = 0.35*cm;
		G4double heightOfThecone9 = 0.044*cm;
		G4double startAngleOfThecone9 = 0.*deg;
		G4double spanningAngleOfThecone9 = 360.*deg;
		G4Cons* FlatFilter_cone9 = new G4Cons("FlatFilter_cone9",innerMinRadiusOfThecone9,innerMaxRadiusOfThecone9,
										outerMinRadiusOfThecone9,outerMaxRadiusOfThecone9,
									 heightOfThecone9/2., startAngleOfThecone9, spanningAngleOfThecone9);
		G4LogicalVolume *FlatFilter_cone9_log = new G4LogicalVolume(FlatFilter_cone9,OFECu,"FlatFilter_cone9_log",0,0,0);

		G4double FlatFilter_cone9_PosX = 0.*cm;
		G4double FlatFilter_cone9_PosY = 0.*cm;
		G4double FlatFilter_cone9_PosZ = ZdistanceofFlatFilter + (heightOfThecone9/2.);
		ZdistanceofFlatFilter += heightOfThecone9;
		G4VPhysicalVolume *FlatFilter_cone9_phys=0;
		FlatFilter_cone9_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone9_PosX,FlatFilter_cone9_PosY,
								   FlatFilter_cone9_PosZ),"FlatFilter_cone9",
								   FlatFilter_cone9_log,this->PVWorld,false,0);


		 //  ------------------------10----------------------- //
		G4double innerMinRadiusOfThecone10 = 0.*cm;
		G4double innerMaxRadiusOfThecone10 = 0.35*cm;
		G4double outerMinRadiusOfThecone10 = 0.*cm;
		G4double outerMaxRadiusOfThecone10 = 0.4*cm;
		G4double heightOfThecone10 = 0.041*cm;
		G4double startAngleOfThecone10 = 0.*deg;
		G4double spanningAngleOfThecone10 = 360.*deg;
		G4Cons* FlatFilter_cone10 = new G4Cons("FlatFilter_cone10",innerMinRadiusOfThecone10,innerMaxRadiusOfThecone10,
										outerMinRadiusOfThecone10,outerMaxRadiusOfThecone10,
									 heightOfThecone10/2., startAngleOfThecone10, spanningAngleOfThecone10);
		G4LogicalVolume *FlatFilter_cone10_log = new G4LogicalVolume(FlatFilter_cone10,OFECu,"FlatFilter_cone10_log",0,0,0);

		G4double FlatFilter_cone10_PosX = 0.*cm;
		G4double FlatFilter_cone10_PosY = 0.*cm;
		G4double FlatFilter_cone10_PosZ = ZdistanceofFlatFilter + (heightOfThecone10/2.);
		ZdistanceofFlatFilter += heightOfThecone10;
		G4VPhysicalVolume *FlatFilter_cone10_phys=0;
		FlatFilter_cone10_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone10_PosX,FlatFilter_cone10_PosY,
								   FlatFilter_cone10_PosZ),"FlatFilter_cone10",
								   FlatFilter_cone10_log,this->PVWorld,false,0);


		 //  ------------------------11----------------------- //
		G4double innerMinRadiusOfThecone11 = 0.*cm;
		G4double innerMaxRadiusOfThecone11 = 0.4*cm;
		G4double outerMinRadiusOfThecone11 = 0.*cm;
		G4double outerMaxRadiusOfThecone11 = 0.5*cm;
		G4double heightOfThecone11 = 0.082*cm;
		G4double startAngleOfThecone11 = 0.*deg;
		G4double spanningAngleOfThecone11 = 360.*deg;
		G4Cons* FlatFilter_cone11 = new G4Cons("FlatFilter_cone11",innerMinRadiusOfThecone11,innerMaxRadiusOfThecone11,
										outerMinRadiusOfThecone11,outerMaxRadiusOfThecone11,
									 heightOfThecone11/2., startAngleOfThecone11, spanningAngleOfThecone11);
		G4LogicalVolume *FlatFilter_cone11_log = new G4LogicalVolume(FlatFilter_cone11,OFECu,"FlatFilter_cone11_log",0,0,0);

		G4double FlatFilter_cone11_PosX = 0.*cm;
		G4double FlatFilter_cone11_PosY = 0.*cm;
		G4double FlatFilter_cone11_PosZ = ZdistanceofFlatFilter + (heightOfThecone11/2.);
		ZdistanceofFlatFilter += heightOfThecone11;
		G4VPhysicalVolume *FlatFilter_cone11_phys=0;
		FlatFilter_cone11_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone11_PosX,FlatFilter_cone11_PosY,
								   FlatFilter_cone11_PosZ),"FlatFilter_cone11",
								   FlatFilter_cone11_log,this->PVWorld,false,0);


		 //  ------------------------12----------------------- //
		G4double innerMinRadiusOfThecone12 = 0.*cm;
		G4double innerMaxRadiusOfThecone12 = 0.5*cm;
		G4double outerMinRadiusOfThecone12 = 0.*cm;
		G4double outerMaxRadiusOfThecone12 = 0.6*cm;
		G4double heightOfThecone12 = 0.075*cm;
		G4double startAngleOfThecone12 = 0.*deg;
		G4double spanningAngleOfThecone12 = 360.*deg;
		G4Cons* FlatFilter_cone12 = new G4Cons("FlatFilter_cone12",innerMinRadiusOfThecone12,innerMaxRadiusOfThecone12,
										outerMinRadiusOfThecone12,outerMaxRadiusOfThecone12,
									 heightOfThecone12/2., startAngleOfThecone12, spanningAngleOfThecone12);
		G4LogicalVolume *FlatFilter_cone12_log = new G4LogicalVolume(FlatFilter_cone12,OFECu,"FlatFilter_cone12_log",0,0,0);

		G4double FlatFilter_cone12_PosX = 0.*cm;
		G4double FlatFilter_cone12_PosY = 0.*cm;
		G4double FlatFilter_cone12_PosZ = ZdistanceofFlatFilter + (heightOfThecone12/2.);
		ZdistanceofFlatFilter += heightOfThecone12;
		G4VPhysicalVolume *FlatFilter_cone12_phys=0;
		FlatFilter_cone12_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone12_PosX,FlatFilter_cone12_PosY,
								   FlatFilter_cone12_PosZ),"FlatFilter_cone12",
								   FlatFilter_cone12_log,this->PVWorld,false,0);


		 //  ------------------------13----------------------- //
		G4double innerMinRadiusOfThecone13 = 0.*cm;
		G4double innerMaxRadiusOfThecone13 = 0.6*cm;
		G4double outerMinRadiusOfThecone13 = 0.*cm;
		G4double outerMaxRadiusOfThecone13 = 0.7*cm;
		G4double heightOfThecone13 = 0.073*cm;
		G4double startAngleOfThecone13 = 0.*deg;
		G4double spanningAngleOfThecone13 = 360.*deg;
		G4Cons* FlatFilter_cone13 = new G4Cons("FlatFilter_cone13",innerMinRadiusOfThecone13,innerMaxRadiusOfThecone13,
										outerMinRadiusOfThecone13,outerMaxRadiusOfThecone13,
									 heightOfThecone13/2., startAngleOfThecone13, spanningAngleOfThecone13);
		G4LogicalVolume *FlatFilter_cone13_log = new G4LogicalVolume(FlatFilter_cone13,OFECu,"FlatFilter_cone13_log",0,0,0);

		G4double FlatFilter_cone13_PosX = 0.*cm;
		G4double FlatFilter_cone13_PosY = 0.*cm;
		G4double FlatFilter_cone13_PosZ = ZdistanceofFlatFilter + (heightOfThecone13/2.);
		ZdistanceofFlatFilter += heightOfThecone13;
		G4VPhysicalVolume *FlatFilter_cone13_phys=0;
		FlatFilter_cone13_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone13_PosX,FlatFilter_cone13_PosY,
								   FlatFilter_cone13_PosZ),"FlatFilter_cone13",
								   FlatFilter_cone13_log,this->PVWorld,false,0);


		 //  ------------------------14----------------------- //
		G4double innerMinRadiusOfThecone14 = 0.*cm;
		G4double innerMaxRadiusOfThecone14 = 0.7*cm;
		G4double outerMinRadiusOfThecone14 = 0.*cm;
		G4double outerMaxRadiusOfThecone14 = 0.8*cm;
		G4double heightOfThecone14				 = 0.066*cm;
		G4double startAngleOfThecone14 = 0.*deg;
		G4double spanningAngleOfThecone14 = 360.*deg;
		G4Cons* FlatFilter_cone14 = new G4Cons("FlatFilter_cone14",innerMinRadiusOfThecone14,innerMaxRadiusOfThecone14,
										outerMinRadiusOfThecone14,outerMaxRadiusOfThecone14,
									 heightOfThecone14/2., startAngleOfThecone14, spanningAngleOfThecone14);
		G4LogicalVolume *FlatFilter_cone14_log = new G4LogicalVolume(FlatFilter_cone14,OFECu,"FlatFilter_cone14_log",0,0,0);

		G4double FlatFilter_cone14_PosX = 0.*cm;
		G4double FlatFilter_cone14_PosY = 0.*cm;
		G4double FlatFilter_cone14_PosZ = ZdistanceofFlatFilter + (heightOfThecone14/2.);
		ZdistanceofFlatFilter += heightOfThecone14;
		G4VPhysicalVolume *FlatFilter_cone14_phys=0;
		FlatFilter_cone14_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone14_PosX,FlatFilter_cone14_PosY,
								   FlatFilter_cone14_PosZ),"FlatFilter_cone14",
								   FlatFilter_cone14_log,this->PVWorld,false,0);



		 //  ------------------------15----------------------- //
		G4double innerMinRadiusOfThecone15 = 0.*cm;
		G4double innerMaxRadiusOfThecone15 = 0.8*cm;
		G4double outerMinRadiusOfThecone15 = 0.*cm;
		G4double outerMaxRadiusOfThecone15 = 0.9*cm;
		G4double heightOfThecone15				 = 0.061*cm;
		G4double startAngleOfThecone15 = 0.*deg;
		G4double spanningAngleOfThecone15 = 360.*deg;
		G4Cons* FlatFilter_cone15 = new G4Cons("FlatFilter_cone15",innerMinRadiusOfThecone15,innerMaxRadiusOfThecone15,
										outerMinRadiusOfThecone15,outerMaxRadiusOfThecone15,
									 heightOfThecone15/2., startAngleOfThecone15, spanningAngleOfThecone15);
		G4LogicalVolume *FlatFilter_cone15_log = new G4LogicalVolume(FlatFilter_cone15,OFECu,"FlatFilter_cone15_log",0,0,0);

		G4double FlatFilter_cone15_PosX = 0.*cm;
		G4double FlatFilter_cone15_PosY = 0.*cm;
		G4double FlatFilter_cone15_PosZ = ZdistanceofFlatFilter + (heightOfThecone15/2.);
		ZdistanceofFlatFilter += heightOfThecone15;
		G4VPhysicalVolume *FlatFilter_cone15_phys=0;
		FlatFilter_cone15_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone15_PosX,FlatFilter_cone15_PosY,
								   FlatFilter_cone15_PosZ),"FlatFilter_cone15",
								   FlatFilter_cone15_log,this->PVWorld,false,0);


		 //  ------------------------16----------------------- //
		G4double innerMinRadiusOfThecone16 = 0.*cm;
		G4double innerMaxRadiusOfThecone16 = 0.9*cm;
		G4double outerMinRadiusOfThecone16 = 0.*cm;
		G4double outerMaxRadiusOfThecone16 = 1.00*cm;
		G4double heightOfThecone16				 = 0.056*cm;
		G4double startAngleOfThecone16 = 0.*deg;
		G4double spanningAngleOfThecone16 = 360.*deg;
		G4Cons* FlatFilter_cone16 = new G4Cons("FlatFilter_cone16",innerMinRadiusOfThecone16,innerMaxRadiusOfThecone16,
										outerMinRadiusOfThecone16,outerMaxRadiusOfThecone16,
									 heightOfThecone16/2., startAngleOfThecone16, spanningAngleOfThecone16);
		G4LogicalVolume *FlatFilter_cone16_log = new G4LogicalVolume(FlatFilter_cone16,OFECu,"FlatFilter_cone16_log",0,0,0);

		G4double FlatFilter_cone16_PosX = 0.*cm;
		G4double FlatFilter_cone16_PosY = 0.*cm;
		G4double FlatFilter_cone16_PosZ = ZdistanceofFlatFilter + (heightOfThecone16/2.);
		ZdistanceofFlatFilter += heightOfThecone16;
		G4VPhysicalVolume *FlatFilter_cone16_phys=0;
		FlatFilter_cone16_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone16_PosX,FlatFilter_cone16_PosY,
								   FlatFilter_cone16_PosZ),"FlatFilter_cone16",
								   FlatFilter_cone16_log,this->PVWorld,false,0);


		 //  ------------------------17----------------------- //
		G4double innerMinRadiusOfThecone17 = 0.*cm;
		G4double innerMaxRadiusOfThecone17 = 1.0*cm;
		G4double outerMinRadiusOfThecone17 = 0.*cm;
		G4double outerMaxRadiusOfThecone17 = 1.1*cm;
		G4double heightOfThecone17				 = 0.051*cm;
		G4double startAngleOfThecone17 = 0.*deg;
		G4double spanningAngleOfThecone17 = 360.*deg;
		G4Cons* FlatFilter_cone17 = new G4Cons("FlatFilter_cone17",innerMinRadiusOfThecone17,innerMaxRadiusOfThecone17,
										outerMinRadiusOfThecone17,outerMaxRadiusOfThecone17,
									 heightOfThecone17/2., startAngleOfThecone17, spanningAngleOfThecone17);
		G4LogicalVolume *FlatFilter_cone17_log = new G4LogicalVolume(FlatFilter_cone17,OFECu,"FlatFilter_cone17_log",0,0,0);

		G4double FlatFilter_cone17_PosX = 0.*cm;
		G4double FlatFilter_cone17_PosY = 0.*cm;
		G4double FlatFilter_cone17_PosZ = ZdistanceofFlatFilter + (heightOfThecone17/2.);
		ZdistanceofFlatFilter += heightOfThecone17;
		G4VPhysicalVolume *FlatFilter_cone17_phys=0;
		FlatFilter_cone17_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone17_PosX,FlatFilter_cone17_PosY,
								   FlatFilter_cone17_PosZ),"FlatFilter_cone17",
								   FlatFilter_cone17_log,this->PVWorld,false,0);



		 //  ------------------------18----------------------- //
		G4double innerMinRadiusOfThecone18 = 0.*cm;
		G4double innerMaxRadiusOfThecone18 = 1.1*cm;
		G4double outerMinRadiusOfThecone18 = 0.*cm;
		G4double outerMaxRadiusOfThecone18 = 1.205*cm;
		G4double heightOfThecone18				 = 0.038*cm;
		G4double startAngleOfThecone18 = 0.*deg;
		G4double spanningAngleOfThecone18 = 360.*deg;
		G4Cons* FlatFilter_cone18 = new G4Cons("FlatFilter_cone18",innerMinRadiusOfThecone18,innerMaxRadiusOfThecone18,
										outerMinRadiusOfThecone18,outerMaxRadiusOfThecone18,
									 heightOfThecone18/2., startAngleOfThecone18, spanningAngleOfThecone18);
		G4LogicalVolume *FlatFilter_cone18_log = new G4LogicalVolume(FlatFilter_cone18,OFECu,"FlatFilter_cone18_log",0,0,0);

		G4double FlatFilter_cone18_PosX = 0.*cm;
		G4double FlatFilter_cone18_PosY = 0.*cm;
		G4double FlatFilter_cone18_PosZ = ZdistanceofFlatFilter + (heightOfThecone18/2.);
		ZdistanceofFlatFilter += heightOfThecone18;
		G4VPhysicalVolume *FlatFilter_cone18_phys=0;
		FlatFilter_cone18_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone18_PosX,FlatFilter_cone18_PosY,
								   FlatFilter_cone18_PosZ),"FlatFilter_cone18",
								   FlatFilter_cone18_log,this->PVWorld,false,0);



		 
		 //  ------------------------19----------------------- //
		// TUBE //

		G4double innerRadiusOfThetube19 = 0.*cm;
		G4double outerRadiusOfThetube19 = 1.5*cm;
		G4double heightOfThetube19	 = 0.065*cm;
		G4double startAngleOfThetube19 = 0.*deg;
		G4double spanningAngleOfThetube19 = 360.*deg;
		G4Tubs* FlatFilter_tube19 = new G4Tubs("FlatFilter_tube19",innerRadiusOfThetube19,
						outerRadiusOfThetube19,heightOfThetube19/2., startAngleOfThetube19, spanningAngleOfThetube19);
		G4LogicalVolume *FlatFilter_tube19_log = new G4LogicalVolume(FlatFilter_tube19,OFECu,"FlatFilter_tube19_log",0,0,0);

		G4double FlatFilter_tube19_PosX = 0.*cm;
		G4double FlatFilter_tube19_PosY = 0.*cm;
		G4double FlatFilter_tube19_PosZ = ZdistanceofFlatFilter + (heightOfThetube19/2.);
		ZdistanceofFlatFilter += heightOfThetube19;
		G4VPhysicalVolume *FlatFilter_tube19_phys=0;
		FlatFilter_tube19_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_tube19_PosX,FlatFilter_tube19_PosY,
								   FlatFilter_tube19_PosZ),"FlatFilter_tube19",
								   FlatFilter_tube19_log,this->PVWorld,false,0);



                ZdistanceofFlatFilter = 12.571*cm;

 //  ------------------------20----------------------- //
		G4double innerMinRadiusOfThecone20 = 1.325*cm;
		G4double innerMaxRadiusOfThecone20 = 1.5*cm;
		G4double outerMinRadiusOfThecone20 = 1.3*cm;
		G4double outerMaxRadiusOfThecone20 = 1.5*cm;
		G4double heightOfThecone20				 = 0.06*cm;
		G4double startAngleOfThecone20 = 0.*deg;
		G4double spanningAngleOfThecone20 = 360.*deg;
		G4Cons* FlatFilter_cone20 = new G4Cons("FlatFilter_cone20",innerMinRadiusOfThecone20,innerMaxRadiusOfThecone20,
										outerMinRadiusOfThecone20,outerMaxRadiusOfThecone20,
									 heightOfThecone20/2., startAngleOfThecone20, spanningAngleOfThecone20);
		G4LogicalVolume *FlatFilter_cone20_log = new G4LogicalVolume(FlatFilter_cone20,OFECu,"FlatFilter_cone20_log",0,0,0);

		G4double FlatFilter_cone20_PosX = 0.*cm;
		G4double FlatFilter_cone20_PosY = 0.*cm;
		G4double FlatFilter_cone20_PosZ = ZdistanceofFlatFilter + (heightOfThecone20/2.);
		ZdistanceofFlatFilter += heightOfThecone20;
		G4VPhysicalVolume *FlatFilter_cone20_phys=0;
		FlatFilter_cone20_phys = new G4PVPlacement(0,
						   G4ThreeVector(FlatFilter_cone20_PosX,FlatFilter_cone20_PosY,
								   FlatFilter_cone20_PosZ),"FlatFilter_cone20",
								   FlatFilter_cone20_log,this->PVWorld,false,0);



		// ***********  REGIONS for CUTS

		G4Region *regVol;
		regVol= new G4Region("FFL_R");
		G4ProductionCuts* cuts = new G4ProductionCuts;
		cuts->SetProductionCut(0.5*cm);
		regVol->SetProductionCuts(cuts);

		FlatFilter_cone1_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone1_log);
		FlatFilter_cone2_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone2_log);
		FlatFilter_cone3_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone3_log);
		FlatFilter_cone4_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone4_log);
		FlatFilter_cone5_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone5_log);
		FlatFilter_cone6_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone6_log);
		FlatFilter_cone7_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone7_log);
		FlatFilter_cone8_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone8_log);
		FlatFilter_cone9_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone9_log);
		FlatFilter_cone10_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone10_log);
		FlatFilter_cone11_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone11_log);
		FlatFilter_cone12_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone12_log);
		FlatFilter_cone13_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone13_log);
		FlatFilter_cone14_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone14_log);
		FlatFilter_cone15_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone15_log);
		FlatFilter_cone16_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone16_log);
		FlatFilter_cone17_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone17_log);
		FlatFilter_cone18_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone18_log);
		FlatFilter_tube19_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_tube19_log);
		FlatFilter_cone20_log->SetRegion(regVol);
		regVol->AddRootLogicalVolume(FlatFilter_cone20_log);



		// *********** Visualization attributes

		G4VisAttributes* simpleOFECuVisAtt;
		simpleOFECuVisAtt= new G4VisAttributes(G4Colour::Cyan());
		simpleOFECuVisAtt->SetVisibility(true);
		simpleOFECuVisAtt->SetForceSolid(true);


		FlatFilter_cone1_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone2_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone3_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone4_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone5_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone6_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone7_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone8_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone9_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone10_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone11_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone12_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone13_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone14_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone15_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone16_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone17_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone18_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_tube19_log->SetVisAttributes(simpleOFECuVisAtt);
		FlatFilter_cone20_log->SetVisAttributes(simpleOFECuVisAtt);


		return true;
		break;

	}
	return false;

}




bool CML2Acc1::flatteningFilter_modify_10MV()
{
	switch (this->idEnergy)
	{
		case 10:
				//------------------------target 10MV------------------------
				//    materials

				G4Material* OFECu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

				G4double ZdistanceofFlatFilter = 11.776*cm;

				 //  ------------------------1------------------------ //
				G4double innerMinRadiusOfThecone1 = 0.*cm;
				G4double innerMaxRadiusOfThecone1 = 0.025*cm;
				G4double outerMinRadiusOfThecone1 = 0.*cm;
				G4double outerMaxRadiusOfThecone1 = 0.063*cm;
				G4double heightOfThecone1 				= 0.048*cm;
				G4double startAngleOfThecone1 = 0.*deg;
				G4double spanningAngleOfThecone1 = 360.*deg;
				G4Cons* FlatFilter_cone1 = new G4Cons("FlatFilter_cone1",innerMinRadiusOfThecone1,innerMaxRadiusOfThecone1,
												outerMinRadiusOfThecone1,outerMaxRadiusOfThecone1,
											 heightOfThecone1/2., startAngleOfThecone1, spanningAngleOfThecone1);
				G4LogicalVolume *FlatFilter_cone1_log = new G4LogicalVolume(FlatFilter_cone1,OFECu,"FlatFilter_cone1_log",0,0,0);

				G4double FlatFilter_cone1_PosX = 0.*cm;
				G4double FlatFilter_cone1_PosY = 0.*cm;
				G4double FlatFilter_cone1_PosZ = ZdistanceofFlatFilter + (heightOfThecone1/2.);
				ZdistanceofFlatFilter += heightOfThecone1;
				G4VPhysicalVolume *FlatFilter_cone1_phys=0;
				FlatFilter_cone1_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone1_PosX,FlatFilter_cone1_PosY,
										   FlatFilter_cone1_PosZ),"FlatFilter_cone1",
										   FlatFilter_cone1_log,this->PVWorld,false,0);


				 //  ------------------------2------------------------ //
				G4double innerMinRadiusOfThecone2 = 0.*cm;
				G4double innerMaxRadiusOfThecone2 = 0.063*cm;
				G4double outerMinRadiusOfThecone2 = 0.*cm;
				G4double outerMaxRadiusOfThecone2 = 0.1*cm;
				G4double heightOfThecone2 = 0.055*cm;
				G4double startAngleOfThecone2 = 0.*deg;
				G4double spanningAngleOfThecone2 = 360.*deg;
				G4Cons* FlatFilter_cone2 = new G4Cons("FlatFilter_cone2",innerMinRadiusOfThecone2,innerMaxRadiusOfThecone2,
												outerMinRadiusOfThecone2,outerMaxRadiusOfThecone2,
											 heightOfThecone2/2., startAngleOfThecone2, spanningAngleOfThecone2);
				G4LogicalVolume *FlatFilter_cone2_log = new G4LogicalVolume(FlatFilter_cone2,OFECu,"FlatFilter_cone2_log",0,0,0);

				G4double FlatFilter_cone2_PosX = 0.*cm;
				G4double FlatFilter_cone2_PosY = 0.*cm;
				G4double FlatFilter_cone2_PosZ = ZdistanceofFlatFilter + (heightOfThecone2/2.);
				ZdistanceofFlatFilter += heightOfThecone2;
				G4VPhysicalVolume *FlatFilter_cone2_phys=0;
				FlatFilter_cone2_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone2_PosX,FlatFilter_cone2_PosY,
										   FlatFilter_cone2_PosZ),"FlatFilter_cone2",
										   FlatFilter_cone2_log,this->PVWorld,false,0);


				 //  ------------------------3------------------------ //
				G4double innerMinRadiusOfThecone3 = 0.*cm;
				G4double innerMaxRadiusOfThecone3 = 0.1*cm;
				G4double outerMinRadiusOfThecone3 = 0.*cm;
				G4double outerMaxRadiusOfThecone3 = 0.15*cm;
				G4double heightOfThecone3 = 0.084*cm;
				G4double startAngleOfThecone3 = 0.*deg;
				G4double spanningAngleOfThecone3 = 360.*deg;
				G4Cons* FlatFilter_cone3 = new G4Cons("FlatFilter_cone3",innerMinRadiusOfThecone3,innerMaxRadiusOfThecone3,
												outerMinRadiusOfThecone3,outerMaxRadiusOfThecone3,
											 heightOfThecone3/2., startAngleOfThecone3, spanningAngleOfThecone3);
				G4LogicalVolume *FlatFilter_cone3_log = new G4LogicalVolume(FlatFilter_cone3,OFECu,"FlatFilter_cone3_log",0,0,0);

				G4double FlatFilter_cone3_PosX = 0.*cm;
				G4double FlatFilter_cone3_PosY = 0.*cm;
				G4double FlatFilter_cone3_PosZ = ZdistanceofFlatFilter + (heightOfThecone3/2.);
				ZdistanceofFlatFilter += heightOfThecone3;
				G4VPhysicalVolume *FlatFilter_cone3_phys=0;
				FlatFilter_cone3_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone3_PosX,FlatFilter_cone3_PosY,
										   FlatFilter_cone3_PosZ),"FlatFilter_cone3",
										   FlatFilter_cone3_log,this->PVWorld,false,0);


				 //  ------------------------4------------------------ //
				G4double innerMinRadiusOfThecone4 = 0.*cm;
				G4double innerMaxRadiusOfThecone4 = 0.15*cm;
				G4double outerMinRadiusOfThecone4 = 0.*cm;
				G4double outerMaxRadiusOfThecone4 = 0.2*cm;
				G4double heightOfThecone4 = 0.08*cm;
				G4double startAngleOfThecone4 = 0.*deg;
				G4double spanningAngleOfThecone4 = 360.*deg;
				G4Cons* FlatFilter_cone4 = new G4Cons("FlatFilter_cone4",innerMinRadiusOfThecone4,innerMaxRadiusOfThecone4,
												outerMinRadiusOfThecone4,outerMaxRadiusOfThecone4,
											 heightOfThecone4/2., startAngleOfThecone4, spanningAngleOfThecone4);
				G4LogicalVolume *FlatFilter_cone4_log = new G4LogicalVolume(FlatFilter_cone4,OFECu,"FlatFilter_cone4_log",0,0,0);

				G4double FlatFilter_cone4_PosX = 0.*cm;
				G4double FlatFilter_cone4_PosY = 0.*cm;
				G4double FlatFilter_cone4_PosZ = ZdistanceofFlatFilter + (heightOfThecone4/2.);
				ZdistanceofFlatFilter += heightOfThecone4;
				G4VPhysicalVolume *FlatFilter_cone4_phys=0;
				FlatFilter_cone4_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone4_PosX,FlatFilter_cone4_PosY,
										   FlatFilter_cone4_PosZ),"FlatFilter_cone4",
										   FlatFilter_cone4_log,this->PVWorld,false,0);

				 //  ------------------------5------------------------ //
				G4double innerMinRadiusOfThecone5 = 0.*cm;
				G4double innerMaxRadiusOfThecone5 = 0.2*cm;
				G4double outerMinRadiusOfThecone5 = 0.*cm;
				G4double outerMaxRadiusOfThecone5 = 0.3*cm;
				G4double heightOfThecone5 = 0.142*cm;
				G4double startAngleOfThecone5 = 0.*deg;
				G4double spanningAngleOfThecone5 = 360.*deg;
				G4Cons* FlatFilter_cone5 = new G4Cons("FlatFilter_cone5",innerMinRadiusOfThecone5,innerMaxRadiusOfThecone5,
												outerMinRadiusOfThecone5,outerMaxRadiusOfThecone5,
											 heightOfThecone5/2., startAngleOfThecone5, spanningAngleOfThecone5);
				G4LogicalVolume *FlatFilter_cone5_log = new G4LogicalVolume(FlatFilter_cone5,OFECu,"FlatFilter_cone5_log",0,0,0);

				G4double FlatFilter_cone5_PosX = 0.*cm;
				G4double FlatFilter_cone5_PosY = 0.*cm;
				G4double FlatFilter_cone5_PosZ = ZdistanceofFlatFilter + (heightOfThecone5/2.);
				ZdistanceofFlatFilter += heightOfThecone5;
				G4VPhysicalVolume *FlatFilter_cone5_phys=0;
				FlatFilter_cone5_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone5_PosX,FlatFilter_cone5_PosY,
										   FlatFilter_cone5_PosZ),"FlatFilter_cone5",
										   FlatFilter_cone5_log,this->PVWorld,false,0);


				 //  ------------------------6------------------------ //
				G4double innerMinRadiusOfThecone6 = 0.*cm;
				G4double innerMaxRadiusOfThecone6 = 0.3*cm;
				G4double outerMinRadiusOfThecone6 = 0.*cm;
				G4double outerMaxRadiusOfThecone6 = 0.4*cm;
				G4double heightOfThecone6 = 0.123*cm;
				G4double startAngleOfThecone6 = 0.*deg;
				G4double spanningAngleOfThecone6 = 360.*deg;
				G4Cons* FlatFilter_cone6 = new G4Cons("FlatFilter_cone6",innerMinRadiusOfThecone6,innerMaxRadiusOfThecone6,
												outerMinRadiusOfThecone6,outerMaxRadiusOfThecone6,
											 heightOfThecone6/2., startAngleOfThecone6, spanningAngleOfThecone6);
				G4LogicalVolume *FlatFilter_cone6_log = new G4LogicalVolume(FlatFilter_cone6,OFECu,"FlatFilter_cone6_log",0,0,0);

				G4double FlatFilter_cone6_PosX = 0.*cm;
				G4double FlatFilter_cone6_PosY = 0.*cm;
				G4double FlatFilter_cone6_PosZ = ZdistanceofFlatFilter + (heightOfThecone6/2.);
				ZdistanceofFlatFilter += heightOfThecone6;
				G4VPhysicalVolume *FlatFilter_cone6_phys=0;
				FlatFilter_cone6_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone6_PosX,FlatFilter_cone6_PosY,
										   FlatFilter_cone6_PosZ),"FlatFilter_cone6",
										   FlatFilter_cone6_log,this->PVWorld,false,0);


				 //  ------------------------7------------------------ //
				G4double innerMinRadiusOfThecone7 = 0.*cm;
				G4double innerMaxRadiusOfThecone7 = 0.4*cm;
				G4double outerMinRadiusOfThecone7 = 0.*cm;
				G4double outerMaxRadiusOfThecone7 = 0.5*cm;
				G4double heightOfThecone7 = 0.113*cm;
				G4double startAngleOfThecone7 = 0.*deg;
				G4double spanningAngleOfThecone7 = 360.*deg;
				G4Cons* FlatFilter_cone7 = new G4Cons("FlatFilter_cone7",innerMinRadiusOfThecone7,innerMaxRadiusOfThecone7,
												outerMinRadiusOfThecone7,outerMaxRadiusOfThecone7,
											 heightOfThecone7/2., startAngleOfThecone7, spanningAngleOfThecone7);
				G4LogicalVolume *FlatFilter_cone7_log = new G4LogicalVolume(FlatFilter_cone7,OFECu,"FlatFilter_cone7_log",0,0,0);

				G4double FlatFilter_cone7_PosX = 0.*cm;
				G4double FlatFilter_cone7_PosY = 0.*cm;
				G4double FlatFilter_cone7_PosZ = ZdistanceofFlatFilter + (heightOfThecone7/2.);
				ZdistanceofFlatFilter += heightOfThecone7;
				G4VPhysicalVolume *FlatFilter_cone7_phys=0;
				FlatFilter_cone7_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone7_PosX,FlatFilter_cone7_PosY,
										   FlatFilter_cone7_PosZ),"FlatFilter_cone7",
										   FlatFilter_cone7_log,this->PVWorld,false,0);

				 //  ------------------------8------------------------ //
				G4double innerMinRadiusOfThecone8 = 0.*cm;
				G4double innerMaxRadiusOfThecone8 = 0.5*cm;
				G4double outerMinRadiusOfThecone8 = 0.*cm;
				G4double outerMaxRadiusOfThecone8 = 0.6*cm;
				G4double heightOfThecone8 = 0.11*cm;
				G4double startAngleOfThecone8 = 0.*deg;
				G4double spanningAngleOfThecone8 = 360.*deg;
				G4Cons* FlatFilter_cone8 = new G4Cons("FlatFilter_cone8",innerMinRadiusOfThecone8,innerMaxRadiusOfThecone8,
												outerMinRadiusOfThecone8,outerMaxRadiusOfThecone8,
											 heightOfThecone8/2., startAngleOfThecone8, spanningAngleOfThecone8);
				G4LogicalVolume *FlatFilter_cone8_log = new G4LogicalVolume(FlatFilter_cone8,OFECu,"FlatFilter_cone8_log",0,0,0);

				G4double FlatFilter_cone8_PosX = 0.*cm;
				G4double FlatFilter_cone8_PosY = 0.*cm;
				G4double FlatFilter_cone8_PosZ = ZdistanceofFlatFilter + (heightOfThecone8/2.);
				ZdistanceofFlatFilter += heightOfThecone8;
				G4VPhysicalVolume *FlatFilter_cone8_phys=0;
				FlatFilter_cone8_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone8_PosX,FlatFilter_cone8_PosY,
										   FlatFilter_cone8_PosZ),"FlatFilter_cone8",
										   FlatFilter_cone8_log,this->PVWorld,false,0);


				 //  ------------------------9------------------------ //
				G4double innerMinRadiusOfThecone9 = 0.*cm;
				G4double innerMaxRadiusOfThecone9 = 0.6*cm;
				G4double outerMinRadiusOfThecone9 = 0.*cm;
				G4double outerMaxRadiusOfThecone9 = 0.7*cm;
				G4double heightOfThecone9 = 0.113*cm;
				G4double startAngleOfThecone9 = 0.*deg;
				G4double spanningAngleOfThecone9 = 360.*deg;
				G4Cons* FlatFilter_cone9 = new G4Cons("FlatFilter_cone9",innerMinRadiusOfThecone9,innerMaxRadiusOfThecone9,
												outerMinRadiusOfThecone9,outerMaxRadiusOfThecone9,
											 heightOfThecone9/2., startAngleOfThecone9, spanningAngleOfThecone9);
				G4LogicalVolume *FlatFilter_cone9_log = new G4LogicalVolume(FlatFilter_cone9,OFECu,"FlatFilter_cone9_log",0,0,0);

				G4double FlatFilter_cone9_PosX = 0.*cm;
				G4double FlatFilter_cone9_PosY = 0.*cm;
				G4double FlatFilter_cone9_PosZ = ZdistanceofFlatFilter + (heightOfThecone9/2.);
				ZdistanceofFlatFilter += heightOfThecone9;
				G4VPhysicalVolume *FlatFilter_cone9_phys=0;
				FlatFilter_cone9_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone9_PosX,FlatFilter_cone9_PosY,
										   FlatFilter_cone9_PosZ),"FlatFilter_cone9",
										   FlatFilter_cone9_log,this->PVWorld,false,0);


				 //  ------------------------10----------------------- //
				G4double innerMinRadiusOfThecone10 = 0.*cm;
				G4double innerMaxRadiusOfThecone10 = 0.7*cm;
				G4double outerMinRadiusOfThecone10 = 0.*cm;
				G4double outerMaxRadiusOfThecone10 = 0.8*cm;
				G4double heightOfThecone10 = 0.108*cm;
				G4double startAngleOfThecone10 = 0.*deg;
				G4double spanningAngleOfThecone10 = 360.*deg;
				G4Cons* FlatFilter_cone10 = new G4Cons("FlatFilter_cone10",innerMinRadiusOfThecone10,innerMaxRadiusOfThecone10,
												outerMinRadiusOfThecone10,outerMaxRadiusOfThecone10,
											 heightOfThecone10/2., startAngleOfThecone10, spanningAngleOfThecone10);
				G4LogicalVolume *FlatFilter_cone10_log = new G4LogicalVolume(FlatFilter_cone10,OFECu,"FlatFilter_cone10_log",0,0,0);

				G4double FlatFilter_cone10_PosX = 0.*cm;
				G4double FlatFilter_cone10_PosY = 0.*cm;
				G4double FlatFilter_cone10_PosZ = ZdistanceofFlatFilter + (heightOfThecone10/2.);
				ZdistanceofFlatFilter += heightOfThecone10;
				G4VPhysicalVolume *FlatFilter_cone10_phys=0;
				FlatFilter_cone10_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone10_PosX,FlatFilter_cone10_PosY,
										   FlatFilter_cone10_PosZ),"FlatFilter_cone10",
										   FlatFilter_cone10_log,this->PVWorld,false,0);


				 //  ------------------------11----------------------- //
				G4double innerMinRadiusOfThecone11 = 0.*cm;
				G4double innerMaxRadiusOfThecone11 = 0.8*cm;
				G4double outerMinRadiusOfThecone11 = 0.*cm;
				G4double outerMaxRadiusOfThecone11 = 0.9*cm;
				G4double heightOfThecone11 = 0.092*cm;
				G4double startAngleOfThecone11 = 0.*deg;
				G4double spanningAngleOfThecone11 = 360.*deg;
				G4Cons* FlatFilter_cone11 = new G4Cons("FlatFilter_cone11",innerMinRadiusOfThecone11,innerMaxRadiusOfThecone11,
												outerMinRadiusOfThecone11,outerMaxRadiusOfThecone11,
											 heightOfThecone11/2., startAngleOfThecone11, spanningAngleOfThecone11);
				G4LogicalVolume *FlatFilter_cone11_log = new G4LogicalVolume(FlatFilter_cone11,OFECu,"FlatFilter_cone11_log",0,0,0);

				G4double FlatFilter_cone11_PosX = 0.*cm;
				G4double FlatFilter_cone11_PosY = 0.*cm;
				G4double FlatFilter_cone11_PosZ = ZdistanceofFlatFilter + (heightOfThecone11/2.);
				ZdistanceofFlatFilter += heightOfThecone11;
				G4VPhysicalVolume *FlatFilter_cone11_phys=0;
				FlatFilter_cone11_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone11_PosX,FlatFilter_cone11_PosY,
										   FlatFilter_cone11_PosZ),"FlatFilter_cone11",
										   FlatFilter_cone11_log,this->PVWorld,false,0);


				 //  ------------------------12----------------------- //
				G4double innerMinRadiusOfThecone12 = 0.*cm;
				G4double innerMaxRadiusOfThecone12 = 0.9*cm;
				G4double outerMinRadiusOfThecone12 = 0.*cm;
				G4double outerMaxRadiusOfThecone12 = 1.*cm;
				G4double heightOfThecone12 = 0.07*cm;
				G4double startAngleOfThecone12 = 0.*deg;
				G4double spanningAngleOfThecone12 = 360.*deg;
				G4Cons* FlatFilter_cone12 = new G4Cons("FlatFilter_cone12",innerMinRadiusOfThecone12,innerMaxRadiusOfThecone12,
												outerMinRadiusOfThecone12,outerMaxRadiusOfThecone12,
											 heightOfThecone12/2., startAngleOfThecone12, spanningAngleOfThecone12);
				G4LogicalVolume *FlatFilter_cone12_log = new G4LogicalVolume(FlatFilter_cone12,OFECu,"FlatFilter_cone12_log",0,0,0);

				G4double FlatFilter_cone12_PosX = 0.*cm;
				G4double FlatFilter_cone12_PosY = 0.*cm;
				G4double FlatFilter_cone12_PosZ = ZdistanceofFlatFilter + (heightOfThecone12/2.);
				ZdistanceofFlatFilter += heightOfThecone12;
				G4VPhysicalVolume *FlatFilter_cone12_phys=0;
				FlatFilter_cone12_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone12_PosX,FlatFilter_cone12_PosY,
										   FlatFilter_cone12_PosZ),"FlatFilter_cone12",
										   FlatFilter_cone12_log,this->PVWorld,false,0);


				 //  ------------------------13----------------------- //
				G4double innerMinRadiusOfThecone13 = 0.*cm;
				G4double innerMaxRadiusOfThecone13 = 1.0*cm;
				G4double outerMinRadiusOfThecone13 = 0.*cm;
				G4double outerMaxRadiusOfThecone13 = 1.1*cm;
				G4double heightOfThecone13 = 0.065*cm;
				G4double startAngleOfThecone13 = 0.*deg;
				G4double spanningAngleOfThecone13 = 360.*deg;
				G4Cons* FlatFilter_cone13 = new G4Cons("FlatFilter_cone13",innerMinRadiusOfThecone13,innerMaxRadiusOfThecone13,
												outerMinRadiusOfThecone13,outerMaxRadiusOfThecone13,
											 heightOfThecone13/2., startAngleOfThecone13, spanningAngleOfThecone13);
				G4LogicalVolume *FlatFilter_cone13_log = new G4LogicalVolume(FlatFilter_cone13,OFECu,"FlatFilter_cone13_log",0,0,0);

				G4double FlatFilter_cone13_PosX = 0.*cm;
				G4double FlatFilter_cone13_PosY = 0.*cm;
				G4double FlatFilter_cone13_PosZ = ZdistanceofFlatFilter + (heightOfThecone13/2.);
				ZdistanceofFlatFilter += heightOfThecone13;
				G4VPhysicalVolume *FlatFilter_cone13_phys=0;
				FlatFilter_cone13_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone13_PosX,FlatFilter_cone13_PosY,
										   FlatFilter_cone13_PosZ),"FlatFilter_cone13",
										   FlatFilter_cone13_log,this->PVWorld,false,0);


				 //  ------------------------14----------------------- //
				G4double innerMinRadiusOfThecone14 = 0.*cm;
				G4double innerMaxRadiusOfThecone14 = 1.1*cm;
				G4double outerMinRadiusOfThecone14 = 0.*cm;
				G4double outerMaxRadiusOfThecone14 = 1.2*cm;
				G4double heightOfThecone14				 = 0.062*cm;
				G4double startAngleOfThecone14 = 0.*deg;
				G4double spanningAngleOfThecone14 = 360.*deg;
				G4Cons* FlatFilter_cone14 = new G4Cons("FlatFilter_cone14",innerMinRadiusOfThecone14,innerMaxRadiusOfThecone14,
												outerMinRadiusOfThecone14,outerMaxRadiusOfThecone14,
											 heightOfThecone14/2., startAngleOfThecone14, spanningAngleOfThecone14);
				G4LogicalVolume *FlatFilter_cone14_log = new G4LogicalVolume(FlatFilter_cone14,OFECu,"FlatFilter_cone14_log",0,0,0);

				G4double FlatFilter_cone14_PosX = 0.*cm;
				G4double FlatFilter_cone14_PosY = 0.*cm;
				G4double FlatFilter_cone14_PosZ = ZdistanceofFlatFilter + (heightOfThecone14/2.);
				ZdistanceofFlatFilter += heightOfThecone14;
				G4VPhysicalVolume *FlatFilter_cone14_phys=0;
				FlatFilter_cone14_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone14_PosX,FlatFilter_cone14_PosY,
										   FlatFilter_cone14_PosZ),"FlatFilter_cone14",
										   FlatFilter_cone14_log,this->PVWorld,false,0);


				//  ------------------------15----------------------- //
				// TUBE //

				G4double innerRadiusOfThetube15 = 0.*cm;
				G4double outerRadiusOfThetube15 = 1.5*cm;
				G4double heightOfThetube15			= 0.115*cm;
				G4double startAngleOfThetube15 = 0.*deg;
				G4double spanningAngleOfThetube15 = 360.*deg;
				G4Tubs* FlatFilter_tube15 = new G4Tubs("FlatFilter_tube15",innerRadiusOfThetube15,
								outerRadiusOfThetube15,heightOfThetube15/2., startAngleOfThetube15, spanningAngleOfThetube15);
				G4LogicalVolume *FlatFilter_tube15_log = new G4LogicalVolume(FlatFilter_tube15,OFECu,"FlatFilter_tube15_log",0,0,0);

				G4double FlatFilter_tube15_PosX = 0.*cm;
				G4double FlatFilter_tube15_PosY = 0.*cm;
				G4double FlatFilter_tube15_PosZ = ZdistanceofFlatFilter + (heightOfThetube15/2.);
				ZdistanceofFlatFilter += heightOfThetube15;
				G4VPhysicalVolume *FlatFilter_tube15_phys=0;
				FlatFilter_tube15_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_tube15_PosX,FlatFilter_tube15_PosY,
										   FlatFilter_tube15_PosZ),"FlatFilter_tube15",
										   FlatFilter_tube15_log,this->PVWorld,false,0);

				 //  ------------------------16----------------------- //
				G4double innerMinRadiusOfThecone16 = 0.*cm;
				G4double innerMaxRadiusOfThecone16 = 1.25*cm;
				G4double outerMinRadiusOfThecone16 = 0.*cm;
				G4double outerMaxRadiusOfThecone16 = 1.16*cm;
				G4double heightOfThecone16				 = 0.035*cm;
				G4double startAngleOfThecone16 = 0.*deg;
				G4double spanningAngleOfThecone16 = 360.*deg;
				G4Cons* FlatFilter_cone16 = new G4Cons("FlatFilter_cone16",innerMinRadiusOfThecone16,innerMaxRadiusOfThecone16,
												outerMinRadiusOfThecone16,outerMaxRadiusOfThecone16,
											 heightOfThecone16/2., startAngleOfThecone16, spanningAngleOfThecone16);
				G4LogicalVolume *FlatFilter_cone16_log = new G4LogicalVolume(FlatFilter_cone16,OFECu,"FlatFilter_cone16_log",0,0,0);

				G4double FlatFilter_cone16_PosX = 0.*cm;
				G4double FlatFilter_cone16_PosY = 0.*cm;
				G4double FlatFilter_cone16_PosZ = ZdistanceofFlatFilter + (heightOfThecone16/2.);
				ZdistanceofFlatFilter += heightOfThecone16;
				G4VPhysicalVolume *FlatFilter_cone16_phys=0;
				FlatFilter_cone16_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone16_PosX,FlatFilter_cone16_PosY,
										   FlatFilter_cone16_PosZ),"FlatFilter_cone16",
										   FlatFilter_cone16_log,this->PVWorld,false,0);


				 //  ------------------------17----------------------- //
				G4double innerMinRadiusOfThecone17 = 0*cm;
				G4double innerMaxRadiusOfThecone17 = 0.9*cm;
				G4double outerMinRadiusOfThecone17 = 0.*cm;
				G4double outerMaxRadiusOfThecone17 = 0.8*cm;
				G4double heightOfThecone17				 = 0.007*cm;
				G4double startAngleOfThecone17 = 0.*deg;
				G4double spanningAngleOfThecone17 = 360.*deg;
				G4Cons* FlatFilter_cone17 = new G4Cons("FlatFilter_cone17",innerMinRadiusOfThecone17,innerMaxRadiusOfThecone17,
												outerMinRadiusOfThecone17,outerMaxRadiusOfThecone17,
											 heightOfThecone17/2., startAngleOfThecone17, spanningAngleOfThecone17);
				G4LogicalVolume *FlatFilter_cone17_log = new G4LogicalVolume(FlatFilter_cone17,OFECu,"FlatFilter_cone17_log",0,0,0);

				G4double FlatFilter_cone17_PosX = 0.*cm;
				G4double FlatFilter_cone17_PosY = 0.*cm;
				G4double FlatFilter_cone17_PosZ = ZdistanceofFlatFilter + (heightOfThecone17/2.);
				ZdistanceofFlatFilter += heightOfThecone17;
				G4VPhysicalVolume *FlatFilter_cone17_phys=0;
				FlatFilter_cone17_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone17_PosX,FlatFilter_cone17_PosY,
										   FlatFilter_cone17_PosZ),"FlatFilter_cone17",
										   FlatFilter_cone17_log,this->PVWorld,false,0);


				 //  ------------------------18----------------------- //
				G4double innerMinRadiusOfThecone18 = 0*cm;
				G4double innerMaxRadiusOfThecone18 = 0.8*cm;
				G4double outerMinRadiusOfThecone18 = 0.*cm;
				G4double outerMaxRadiusOfThecone18 = 0.7*cm;
				G4double heightOfThecone18				 = 0.008*cm;
				G4double startAngleOfThecone18 = 0.*deg;
				G4double spanningAngleOfThecone18 = 360.*deg;
				G4Cons* FlatFilter_cone18 = new G4Cons("FlatFilter_cone18",innerMinRadiusOfThecone18,innerMaxRadiusOfThecone18,
												outerMinRadiusOfThecone18,outerMaxRadiusOfThecone18,
											 heightOfThecone18/2., startAngleOfThecone18, spanningAngleOfThecone18);
				G4LogicalVolume *FlatFilter_cone18_log = new G4LogicalVolume(FlatFilter_cone18,OFECu,"FlatFilter_cone18_log",0,0,0);

				G4double FlatFilter_cone18_PosX = 0.*cm;
				G4double FlatFilter_cone18_PosY = 0.*cm;
				G4double FlatFilter_cone18_PosZ = ZdistanceofFlatFilter + (heightOfThecone18/2.);
				ZdistanceofFlatFilter += heightOfThecone18;
				G4VPhysicalVolume *FlatFilter_cone18_phys=0;
				FlatFilter_cone18_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone18_PosX,FlatFilter_cone18_PosY,
										   FlatFilter_cone18_PosZ),"FlatFilter_cone18",
										   FlatFilter_cone18_log,this->PVWorld,false,0);


				 //  ------------------------19----------------------- //
				G4double innerMinRadiusOfThecone19 = 0*cm;
				G4double innerMaxRadiusOfThecone19 = 0.7*cm;
				G4double outerMinRadiusOfThecone19 = 0.*cm;
				G4double outerMaxRadiusOfThecone19 = 0.6*cm;
				G4double heightOfThecone19				 = 0.02*cm;
				G4double startAngleOfThecone19 = 0.*deg;
				G4double spanningAngleOfThecone19 = 360.*deg;
				G4Cons* FlatFilter_cone19 = new G4Cons("FlatFilter_cone19",innerMinRadiusOfThecone19,innerMaxRadiusOfThecone19,
												outerMinRadiusOfThecone19,outerMaxRadiusOfThecone19,
											 heightOfThecone19/2., startAngleOfThecone19, spanningAngleOfThecone19);
				G4LogicalVolume *FlatFilter_cone19_log = new G4LogicalVolume(FlatFilter_cone19,OFECu,"FlatFilter_cone19_log",0,0,0);

				G4double FlatFilter_cone19_PosX = 0.*cm;
				G4double FlatFilter_cone19_PosY = 0.*cm;
				G4double FlatFilter_cone19_PosZ = ZdistanceofFlatFilter + (heightOfThecone19/2.);
				ZdistanceofFlatFilter += heightOfThecone19;
				G4VPhysicalVolume *FlatFilter_cone19_phys=0;
				FlatFilter_cone19_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone19_PosX,FlatFilter_cone19_PosY,
										   FlatFilter_cone19_PosZ),"FlatFilter_cone19",
										   FlatFilter_cone19_log,this->PVWorld,false,0);


				 //  ------------------------20----------------------- //
				G4double innerMinRadiusOfThecone20 = 0*cm;
				G4double innerMaxRadiusOfThecone20 = 0.6*cm;
				G4double outerMinRadiusOfThecone20 = 0.*cm;
				G4double outerMaxRadiusOfThecone20 = 0.5*cm;
				G4double heightOfThecone20				 = 0.035*cm;
				G4double startAngleOfThecone20 = 0.*deg;
				G4double spanningAngleOfThecone20 = 360.*deg;
				G4Cons* FlatFilter_cone20 = new G4Cons("FlatFilter_cone20",innerMinRadiusOfThecone20,innerMaxRadiusOfThecone20,
												outerMinRadiusOfThecone20,outerMaxRadiusOfThecone20,
											 heightOfThecone20/2., startAngleOfThecone20, spanningAngleOfThecone20);
				G4LogicalVolume *FlatFilter_cone20_log = new G4LogicalVolume(FlatFilter_cone20,OFECu,"FlatFilter_cone20_log",0,0,0);

				G4double FlatFilter_cone20_PosX = 0.*cm;
				G4double FlatFilter_cone20_PosY = 0.*cm;
				G4double FlatFilter_cone20_PosZ = ZdistanceofFlatFilter + (heightOfThecone20/2.);
				ZdistanceofFlatFilter += heightOfThecone20;
				G4VPhysicalVolume *FlatFilter_cone20_phys=0;
				FlatFilter_cone20_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone20_PosX,FlatFilter_cone20_PosY,
										   FlatFilter_cone20_PosZ),"FlatFilter_cone20",
										   FlatFilter_cone20_log,this->PVWorld,false,0);



				 //  ------------------------21----------------------- //
				G4double innerMinRadiusOfThecone21 = 0.*cm;
				G4double innerMaxRadiusOfThecone21 = 0.5*cm;
				G4double outerMinRadiusOfThecone21 = 0.*cm;
				G4double outerMaxRadiusOfThecone21 = 0.4*cm;
				G4double heightOfThecone21 = 0.043*cm;
				G4double startAngleOfThecone21 = 0.*deg;
				G4double spanningAngleOfThecone21 = 360.*deg;
				G4Cons* FlatFilter_cone21 = new G4Cons("FlatFilter_cone21",innerMinRadiusOfThecone21,innerMaxRadiusOfThecone21,
												outerMinRadiusOfThecone21,outerMaxRadiusOfThecone21,
											 heightOfThecone21/2., startAngleOfThecone21, spanningAngleOfThecone21);
				G4LogicalVolume *FlatFilter_cone21_log = new G4LogicalVolume(FlatFilter_cone21,OFECu,"FlatFilter_cone21_log",0,0,0);

				G4double FlatFilter_cone21_PosX = 0.*cm;
				G4double FlatFilter_cone21_PosY = 0.*cm;
				G4double FlatFilter_cone21_PosZ = ZdistanceofFlatFilter + (heightOfThecone21/2.);
				ZdistanceofFlatFilter += heightOfThecone21;
				G4VPhysicalVolume *FlatFilter_cone21_phys=0;
				FlatFilter_cone21_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone21_PosX,FlatFilter_cone21_PosY,
										   FlatFilter_cone21_PosZ),"FlatFilter_cone21",
										   FlatFilter_cone21_log,this->PVWorld,false,0);


				 //  ------------------------22----------------------- //
				G4double innerMinRadiusOfThecone22 = 0.*cm;
				G4double innerMaxRadiusOfThecone22 = 0.4*cm;
				G4double outerMinRadiusOfThecone22 = 0.*cm;
				G4double outerMaxRadiusOfThecone22 = 0.3*cm;
				G4double heightOfThecone22 = 0.045*cm;
				G4double startAngleOfThecone22 = 0.*deg;
				G4double spanningAngleOfThecone22 = 360.*deg;
				G4Cons* FlatFilter_cone22 = new G4Cons("FlatFilter_cone22",innerMinRadiusOfThecone22,innerMaxRadiusOfThecone22,
												outerMinRadiusOfThecone22,outerMaxRadiusOfThecone22,
											 heightOfThecone22/2., startAngleOfThecone22, spanningAngleOfThecone22);
				G4LogicalVolume *FlatFilter_cone22_log = new G4LogicalVolume(FlatFilter_cone22,OFECu,"FlatFilter_cone22_log",0,0,0);

				G4double FlatFilter_cone22_PosX = 0.*cm;
				G4double FlatFilter_cone22_PosY = 0.*cm;
				G4double FlatFilter_cone22_PosZ = ZdistanceofFlatFilter + (heightOfThecone22/2.);
				ZdistanceofFlatFilter += heightOfThecone22;
				G4VPhysicalVolume *FlatFilter_cone22_phys=0;
				FlatFilter_cone22_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone22_PosX,FlatFilter_cone22_PosY,
										   FlatFilter_cone22_PosZ),"FlatFilter_cone22",
										   FlatFilter_cone22_log,this->PVWorld,false,0);


				 //  ------------------------23----------------------- //
				G4double innerMinRadiusOfThecone23 = 0.*cm;
				G4double innerMaxRadiusOfThecone23 = 0.3*cm;
				G4double outerMinRadiusOfThecone23 = 0.*cm;
				G4double outerMaxRadiusOfThecone23 = 0.2*cm;
				G4double heightOfThecone23 = 0.05*cm;
				G4double startAngleOfThecone23 = 0.*deg;
				G4double spanningAngleOfThecone23 = 360.*deg;
				G4Cons* FlatFilter_cone23 = new G4Cons("FlatFilter_cone23",innerMinRadiusOfThecone23,innerMaxRadiusOfThecone23,
												outerMinRadiusOfThecone23,outerMaxRadiusOfThecone23,
											 heightOfThecone23/2., startAngleOfThecone23, spanningAngleOfThecone23);
				G4LogicalVolume *FlatFilter_cone23_log = new G4LogicalVolume(FlatFilter_cone23,OFECu,"FlatFilter_cone23_log",0,0,0);

				G4double FlatFilter_cone23_PosX = 0.*cm;
				G4double FlatFilter_cone23_PosY = 0.*cm;
				G4double FlatFilter_cone23_PosZ = ZdistanceofFlatFilter + (heightOfThecone23/2.);
				ZdistanceofFlatFilter += heightOfThecone23;
				G4VPhysicalVolume *FlatFilter_cone23_phys=0;
				FlatFilter_cone23_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone23_PosX,FlatFilter_cone23_PosY,
										   FlatFilter_cone23_PosZ),"FlatFilter_cone23",
										   FlatFilter_cone23_log,this->PVWorld,false,0);


				 //  ------------------------24----------------------- //
				G4double innerMinRadiusOfThecone24 = 0.*cm;
				G4double innerMaxRadiusOfThecone24 = 0.2*cm;
				G4double outerMinRadiusOfThecone24 = 0.*cm;
				G4double outerMaxRadiusOfThecone24 = 0.15*cm;
				G4double heightOfThecone24				 = 0.022*cm;
				G4double startAngleOfThecone24 = 0.*deg;
				G4double spanningAngleOfThecone24 = 360.*deg;
				G4Cons* FlatFilter_cone24 = new G4Cons("FlatFilter_cone24",innerMinRadiusOfThecone24,innerMaxRadiusOfThecone24,
												outerMinRadiusOfThecone24,outerMaxRadiusOfThecone24,
											 heightOfThecone24/2., startAngleOfThecone24, spanningAngleOfThecone24);
				G4LogicalVolume *FlatFilter_cone24_log = new G4LogicalVolume(FlatFilter_cone24,OFECu,"FlatFilter_cone24_log",0,0,0);

				G4double FlatFilter_cone24_PosX = 0.*cm;
				G4double FlatFilter_cone24_PosY = 0.*cm;
				G4double FlatFilter_cone24_PosZ = ZdistanceofFlatFilter + (heightOfThecone24/2.);
				ZdistanceofFlatFilter += heightOfThecone24;
				G4VPhysicalVolume *FlatFilter_cone24_phys=0;
				FlatFilter_cone24_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone24_PosX,FlatFilter_cone24_PosY,
										   FlatFilter_cone24_PosZ),"FlatFilter_cone24",
										   FlatFilter_cone24_log,this->PVWorld,false,0);


				 //  ------------------------25----------------------- //
				G4double innerMinRadiusOfThecone25 = 0.*cm;
				G4double innerMaxRadiusOfThecone25 = 0.15*cm;
				G4double outerMinRadiusOfThecone25 = 0.*cm;
				G4double outerMaxRadiusOfThecone25 = 0.1*cm;
				G4double heightOfThecone25				 = 0.02*cm;
				G4double startAngleOfThecone25 = 0.*deg;
				G4double spanningAngleOfThecone25 = 360.*deg;
				G4Cons* FlatFilter_cone25 = new G4Cons("FlatFilter_cone25",innerMinRadiusOfThecone25,innerMaxRadiusOfThecone25,
												outerMinRadiusOfThecone25,outerMaxRadiusOfThecone25,
											 heightOfThecone25/2., startAngleOfThecone25, spanningAngleOfThecone25);
				G4LogicalVolume *FlatFilter_cone25_log = new G4LogicalVolume(FlatFilter_cone25,OFECu,"FlatFilter_cone25_log",0,0,0);

				G4double FlatFilter_cone25_PosX = 0.*cm;
				G4double FlatFilter_cone25_PosY = 0.*cm;
				G4double FlatFilter_cone25_PosZ = ZdistanceofFlatFilter + (heightOfThecone25/2.);
				ZdistanceofFlatFilter += heightOfThecone25;
				G4VPhysicalVolume *FlatFilter_cone25_phys=0;
				FlatFilter_cone25_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone25_PosX,FlatFilter_cone25_PosY,
										   FlatFilter_cone25_PosZ),"FlatFilter_cone25",
										   FlatFilter_cone25_log,this->PVWorld,false,0);

				 //  ------------------------26----------------------- //
				G4double innerMinRadiusOfThecone26 = 0.*cm;
				G4double innerMaxRadiusOfThecone26 = 0.1*cm;
				G4double outerMinRadiusOfThecone26 = 0.*cm;
				G4double outerMaxRadiusOfThecone26 = 0.05*cm;
				G4double heightOfThecone26				 = 0.015*cm;
				G4double startAngleOfThecone26 = 0.*deg;
				G4double spanningAngleOfThecone26 = 360.*deg;
				G4Cons* FlatFilter_cone26 = new G4Cons("FlatFilter_cone26",innerMinRadiusOfThecone26,innerMaxRadiusOfThecone26,
												outerMinRadiusOfThecone26,outerMaxRadiusOfThecone26,
											 heightOfThecone26/2., startAngleOfThecone26, spanningAngleOfThecone26);
				G4LogicalVolume *FlatFilter_cone26_log = new G4LogicalVolume(FlatFilter_cone26,OFECu,"FlatFilter_cone26_log",0,0,0);

				G4double FlatFilter_cone26_PosX = 0.*cm;
				G4double FlatFilter_cone26_PosY = 0.*cm;
				G4double FlatFilter_cone26_PosZ = ZdistanceofFlatFilter + (heightOfThecone26/2.);
				ZdistanceofFlatFilter += heightOfThecone26;
				G4VPhysicalVolume *FlatFilter_cone26_phys=0;
				FlatFilter_cone26_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone26_PosX,FlatFilter_cone26_PosY,
										   FlatFilter_cone26_PosZ),"FlatFilter_cone26",
										   FlatFilter_cone26_log,this->PVWorld,false,0);

				 //  ------------------------27----------------------- //
				G4double innerMinRadiusOfThecone27 = 0.*cm;
				G4double innerMaxRadiusOfThecone27 = 0.05*cm;
				G4double outerMinRadiusOfThecone27 = 0.*cm;
				G4double outerMaxRadiusOfThecone27 = 0.0*cm;
				G4double heightOfThecone27				 = 0.009*cm;
				G4double startAngleOfThecone27 = 0.*deg;
				G4double spanningAngleOfThecone27 = 360.*deg;
				G4Cons* FlatFilter_cone27 = new G4Cons("FlatFilter_cone27",innerMinRadiusOfThecone27,innerMaxRadiusOfThecone27,
												outerMinRadiusOfThecone27,outerMaxRadiusOfThecone27,
											 heightOfThecone27/2., startAngleOfThecone27, spanningAngleOfThecone27);
				G4LogicalVolume *FlatFilter_cone27_log = new G4LogicalVolume(FlatFilter_cone27,OFECu,"FlatFilter_cone27_log",0,0,0);

				G4double FlatFilter_cone27_PosX = 0.*cm;
				G4double FlatFilter_cone27_PosY = 0.*cm;
				G4double FlatFilter_cone27_PosZ = ZdistanceofFlatFilter + (heightOfThecone27/2.);
				ZdistanceofFlatFilter += heightOfThecone27;
				G4VPhysicalVolume *FlatFilter_cone27_phys=0;
				FlatFilter_cone27_phys = new G4PVPlacement(0,
								   G4ThreeVector(FlatFilter_cone27_PosX,FlatFilter_cone27_PosY,
										   FlatFilter_cone27_PosZ),"FlatFilter_cone27",
										   FlatFilter_cone27_log,this->PVWorld,false,0);


				// ***********  REGIONS for CUTS

				G4Region *regVol;
				regVol= new G4Region("FFL_R");
				G4ProductionCuts* cuts = new G4ProductionCuts;
				cuts->SetProductionCut(0.5*cm);
				regVol->SetProductionCuts(cuts);

				FlatFilter_cone1_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone1_log);
				FlatFilter_cone2_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone2_log);
				FlatFilter_cone3_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone3_log);
				FlatFilter_cone4_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone4_log);
				FlatFilter_cone5_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone5_log);
				FlatFilter_cone6_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone6_log);
				FlatFilter_cone7_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone7_log);
				FlatFilter_cone8_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone8_log);
				FlatFilter_cone9_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone9_log);
				FlatFilter_cone10_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone10_log);
				FlatFilter_cone11_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone11_log);
				FlatFilter_cone12_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone12_log);
				FlatFilter_cone13_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone13_log);
				FlatFilter_cone14_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone14_log);
				FlatFilter_tube15_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_tube15_log);
				FlatFilter_cone16_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone16_log);
				FlatFilter_cone17_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone17_log);
				FlatFilter_cone18_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone18_log);
				FlatFilter_cone19_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone19_log);
				FlatFilter_cone20_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone20_log);
				FlatFilter_cone21_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone21_log);
				FlatFilter_cone22_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone22_log);
				FlatFilter_cone23_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone23_log);
				FlatFilter_cone24_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone24_log);
				FlatFilter_cone25_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone25_log);
				FlatFilter_cone26_log->SetRegion(regVol);
				regVol->AddRootLogicalVolume(FlatFilter_cone26_log);
				FlatFilter_cone27_log->SetRegion(regVol);

				// *********** Visualization attributes

				G4VisAttributes* simpleOFECuVisAtt;
				simpleOFECuVisAtt= new G4VisAttributes(G4Colour::Gray());
				simpleOFECuVisAtt->SetVisibility(true);
				//simpleOFECuVisAtt->SetForceSolid(true);


				FlatFilter_cone1_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone2_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone3_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone4_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone5_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone6_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone7_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone8_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone9_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone10_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone11_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone12_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone13_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone14_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_tube15_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone16_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone17_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone18_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone19_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone20_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone21_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone22_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone23_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone24_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone25_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone26_log->SetVisAttributes(simpleOFECuVisAtt);
				FlatFilter_cone27_log->SetVisAttributes(simpleOFECuVisAtt);


				return true;
				break;
	}
	return false;
}



bool CML2Acc1::ionizationChamber()
{
	bool bCreated=false;

	G4Material* Kapton = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");

	G4double ZdistanceofChamber = 14.224*cm;

	// Logical Volume Setting
	 //  ------------------------1------------------------ //
	G4double innerRadiusOfTheTube1 = 0.*cm;
	G4double outerRadiusOfTheTube1 = 3.81*cm;
	G4double heightOfTheTube1 = 0.152*cm;
	G4double startAngleOfTheTube1 = 0.*deg;
	G4double spanningAngleOfTheTube1 = 360.*deg;
	G4Tubs* Chamber_Tube1 = new G4Tubs("Chamber_Tube1",innerRadiusOfTheTube1,
								 outerRadiusOfTheTube1,heightOfTheTube1/2.,
				startAngleOfTheTube1,spanningAngleOfTheTube1);

	 //  ------------------------2------------------------ //
	G4double innerRadiusOfTheTube2 = 3.429*cm;
	G4double outerRadiusOfTheTube2 = 3.81*cm;
	G4double heightOfTheTube2 = 0.184*cm;
	G4double startAngleOfTheTube2 = 0.*deg;
	G4double spanningAngleOfTheTube2 = 360.*deg;
	G4Tubs* Chamber_Tube2 = new G4Tubs("Chamber_Tube2",innerRadiusOfTheTube2,
								 outerRadiusOfTheTube2,heightOfTheTube2/2.,
				startAngleOfTheTube2,spanningAngleOfTheTube2);



	// LogicalVolume & Placement Setting
	 //  ------------------------1------------------------ //
	G4LogicalVolume *Chamber_Tube1_log = new G4LogicalVolume(Chamber_Tube1,Kapton,"Chamber_Tube1_log",0,0,0);
	G4double Chamber_Tube1_PosX = 0.*cm;
	G4double Chamber_Tube1_PosY = 0.*cm;
	G4double Chamber_Tube1_PosZ = ZdistanceofChamber + (heightOfTheTube1/2.);
	ZdistanceofChamber += heightOfTheTube1;
	G4VPhysicalVolume *Chamber_Tube1_phys=0;
	Chamber_Tube1_phys = new G4PVPlacement(0,
					   G4ThreeVector(Chamber_Tube1_PosX,Chamber_Tube1_PosY,
							   Chamber_Tube1_PosZ),"Chamber_Tube1",
							   Chamber_Tube1_log,this->PVWorld,false,0);


	 //  ------------------------2------------------------ //
	G4LogicalVolume *Chamber_Tube2_log = new G4LogicalVolume(Chamber_Tube2,Kapton,"Chamber_Tube2_log",0,0,0);
	G4double Chamber_Tube2_PosX = 0.*cm;
	G4double Chamber_Tube2_PosY = 0.*cm;
	G4double Chamber_Tube2_PosZ = ZdistanceofChamber + (heightOfTheTube2/2.);
	ZdistanceofChamber += heightOfTheTube2;
	G4VPhysicalVolume *Chamber_Tube2_phys=0;
	Chamber_Tube2_phys = new G4PVPlacement(0,
					   G4ThreeVector(Chamber_Tube2_PosX,Chamber_Tube2_PosY,
							   Chamber_Tube2_PosZ),"Chamber_Tube2",
							   Chamber_Tube2_log,this->PVWorld,false,0);

	 //  ------------------------3------------------------ //
	G4LogicalVolume *Chamber_Tube3_log = new G4LogicalVolume(Chamber_Tube1,Kapton,"Chamber_Tube3_log",0,0,0);
	G4double Chamber_Tube3_PosX = 0.*cm;
	G4double Chamber_Tube3_PosY = 0.*cm;
	G4double Chamber_Tube3_PosZ = ZdistanceofChamber + (heightOfTheTube1/2.);
	ZdistanceofChamber += heightOfTheTube1;
	G4VPhysicalVolume *Chamber_Tube3_phys=0;
	Chamber_Tube3_phys = new G4PVPlacement(0,
					   G4ThreeVector(Chamber_Tube3_PosX,Chamber_Tube3_PosY,
							   Chamber_Tube3_PosZ),"Chamber_Tube3",
							   Chamber_Tube3_log,this->PVWorld,false,0);


	 //  ------------------------4------------------------ //
	G4LogicalVolume *Chamber_Tube4_log = new G4LogicalVolume(Chamber_Tube2,Kapton,"Chamber_Tube4_log",0,0,0);
	G4double Chamber_Tube4_PosX = 0.*cm;
	G4double Chamber_Tube4_PosY = 0.*cm;
	G4double Chamber_Tube4_PosZ = ZdistanceofChamber + (heightOfTheTube2/2.);
	ZdistanceofChamber += heightOfTheTube2;
	G4VPhysicalVolume *Chamber_Tube4_phys=0;
	Chamber_Tube4_phys = new G4PVPlacement(0,
					   G4ThreeVector(Chamber_Tube4_PosX,Chamber_Tube4_PosY,
							   Chamber_Tube4_PosZ),"Chamber_Tube4",
							   Chamber_Tube4_log,this->PVWorld,false,0);

	 //  ------------------------5------------------------ //
	G4LogicalVolume *Chamber_Tube5_log = new G4LogicalVolume(Chamber_Tube1,Kapton,"Chamber_Tube5_log",0,0,0);
	G4double Chamber_Tube5_PosX = 0.*cm;
	G4double Chamber_Tube5_PosY = 0.*cm;
	G4double Chamber_Tube5_PosZ = ZdistanceofChamber + (heightOfTheTube1/2.);
	ZdistanceofChamber += heightOfTheTube1;
	G4VPhysicalVolume *Chamber_Tube5_phys=0;
	Chamber_Tube5_phys = new G4PVPlacement(0,
					   G4ThreeVector(Chamber_Tube5_PosX,Chamber_Tube5_PosY,
							   Chamber_Tube5_PosZ),"Chamber_Tube5",
							   Chamber_Tube5_log,this->PVWorld,false,0);



	// ***********  REGIONS for CUTS

	G4Region *regVol;
	regVol= new G4Region("ionizationChamber");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*cm);
	regVol->SetProductionCuts(cuts);

	Chamber_Tube1_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Chamber_Tube1_log);
	Chamber_Tube2_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Chamber_Tube2_log);
	Chamber_Tube3_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Chamber_Tube3_log);
	Chamber_Tube4_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Chamber_Tube4_log);
	Chamber_Tube5_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Chamber_Tube5_log);


	// *********** Visualization attributes

	G4VisAttributes* simpleKaptonVisAtt;
	simpleKaptonVisAtt= new G4VisAttributes(G4Colour(255./255.,218./255.,185./255.));  // Peach Puff - WESGOAL
	simpleKaptonVisAtt->SetVisibility(true);
	//simpleKaptonVisAtt->SetForceSolid(true);


	Chamber_Tube1_log->SetVisAttributes(simpleKaptonVisAtt);
	Chamber_Tube2_log->SetVisAttributes(simpleKaptonVisAtt);
	Chamber_Tube3_log->SetVisAttributes(simpleKaptonVisAtt);
	Chamber_Tube4_log->SetVisAttributes(simpleKaptonVisAtt);
	Chamber_Tube5_log->SetVisAttributes(simpleKaptonVisAtt);


	bCreated=true;
	return true;
}
bool CML2Acc1::mirror()
{
	bool bCreated=false;



	G4Material *MYLAR = G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");

	G4double 	ZdistanceofMirror = 22.098 * cm;
  G4double half_width_mirror = 4.*cm;
  //G4double zspan = 9.404*cm;
  G4double length_mirror = 16.*cm;
  G4double heightOfTheBox = 0.00508 * cm;

// Mirror World Box
  G4Box* MirrorSolid = new G4Box("MirrorWorldSolid", (length_mirror/2.), (half_width_mirror), heightOfTheBox/2.);
  G4LogicalVolume*  MirrorLogical = new G4LogicalVolume(MirrorSolid,	MYLAR,	 "MirrorWorldLogical");

	G4RotationMatrix *cRotation=new G4RotationMatrix();
	cRotation->rotateY(36.0*deg);
	G4double Mirror_Box1_PosX = 0.*cm;
	G4double Mirror_Box1_PosY = 0.*cm;
	G4double Mirror_Box1_PosZ = ZdistanceofMirror + (heightOfTheBox/2.);
	G4VPhysicalVolume *MirrorTubePV=0;
	MirrorTubePV=new G4PVPlacement(cRotation, G4ThreeVector(Mirror_Box1_PosX, Mirror_Box1_PosY, Mirror_Box1_PosZ), "MirrorTubePV", MirrorLogical,this->PVWorld, false, 0);



	// ***********  REGIONS for CUTS

	G4Region *regVol;
	regVol= new G4Region("Mirror");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*cm);
	regVol->SetProductionCuts(cuts);

	MirrorLogical->SetRegion(regVol);
	regVol->AddRootLogicalVolume(MirrorLogical);

	// *********** Visualization attributes

	G4VisAttributes* simpleMYLARVisAtt;
	simpleMYLARVisAtt= new G4VisAttributes(G4Colour::Gray());
	simpleMYLARVisAtt->SetVisibility(true);
	simpleMYLARVisAtt->SetForceSolid(true);


	MirrorLogical->SetVisAttributes(simpleMYLARVisAtt);

	bCreated=true;
	return true;
}

void CML2Acc1::SetJawAperture(G4int idJaw, G4ThreeVector &centre, G4ThreeVector halfSize, G4double aperture, G4RotationMatrix *cRotation)
{
	using namespace std;
	G4double theta, x, y, z, dx, dy, dz, beta, R, top;
	x=centre.getX();
	y=centre.getY();
	z=centre.getZ();
	top=z-78.74/2.;
	theta=fabs(atan(aperture/((this->isoCentre)-200)));
	dx=halfSize.getX();
	dy=halfSize.getY();
	dz=halfSize.getZ();
	
	G4double p1x, p1y, p2x, p2y, dist;
	
	switch (idJaw)
	{
	case 1: //idJaw1XV2100:
		centre.set(z*sin(theta)+dx*cos(theta), y, z*cos(theta)-dx*sin(theta));
		beta=fabs(atan(dx/dz));
		R=std::sqrt(dx*dx+dz*dz);
		p1x=centre.getX()-R*sin(theta+beta);
		p1y=centre.getZ()-R*cos(theta+beta);
		p2x=centre.getX()+R*sin(theta-beta);
		p2y=centre.getZ()+R*cos(theta-beta);
		dist=std::sqrt((p1x-p2x)*(p1x-p2x)+(p1y-p2y)*(p1y-p2y));
		
		cRotation->rotateY(-theta);
		halfSize.set(fabs(dx*cos(theta)+dz*sin(theta)), fabs(dy), fabs(dz*cos(theta)+dx*sin(theta)));
		break;
	case 2: //idJaw2XV2100:
		centre.set(-(z*sin(theta)+dx*cos(theta)), y, z*cos(theta)-dx*sin(theta));
		beta=fabs(atan(dx/dz));
		R=std::sqrt(dx*dx+dz*dz);
		p1x=centre.getX()+R*sin(theta+beta);
		p1y=centre.getZ()-R*cos(theta+beta);
		p2x=centre.getX()-R*sin(theta-beta);
		p2y=centre.getZ()+R*cos(theta-beta);
		dist=std::sqrt((p1x-p2x)*(p1x-p2x)+(p1y-p2y)*(p1y-p2y));
		
		cRotation->rotateY(theta);
		halfSize.set(fabs(dx*cos(theta)+dz*sin(theta)), fabs(dy), fabs(dz*cos(theta)+dx*sin(theta)));
		break;
	case 3: //idJaw1YV2100:
		centre.set(x, z*sin(theta)+dy*cos(theta), z*cos(theta)-dy*sin(theta));
		beta=fabs(atan(dy/dz));
		R=std::sqrt(dy*dy+dz*dz);
		p1x=centre.getY()-R*sin(theta+beta);
		p1y=centre.getZ()-R*cos(theta+beta);
		p2x=centre.getY()+R*sin(theta-beta);
		p2y=centre.getZ()+R*cos(theta-beta);
		
		cRotation->rotateX(theta);
		halfSize.set(fabs(dx), fabs(dy*cos(theta)+dz*sin(theta)), fabs(dz*cos(theta)+dy*sin(theta)));
		break;
	case 4: //idJaw2YV2100:
		centre.set(x, -(z*sin(theta)+dy*cos(theta)), z*cos(theta)-dy*sin(theta));
		beta=fabs(atan(dy/dz));
		R=std::sqrt(dy*dy+dz*dz);
		p1x=centre.getY()+R*sin(theta+beta);
		p1y=centre.getZ()-R*cos(theta+beta);
		p2x=centre.getY()-R*sin(theta-beta);
		p2y=centre.getZ()+R*cos(theta-beta);
		dist=std::sqrt((p1x-p2x)*(p1x-p2x)+(p1y-p2y)*(p1y-p2y));
		
		cRotation->rotateX(-theta);
		halfSize.set(fabs(dx), fabs(dy*cos(theta)+dz*sin(theta)), fabs(dz*cos(theta)+dy*sin(theta)));
		break;
	}
}



bool CML2Acc1::Jaw1X()
{
	bool bCreated=false;

	G4Material *W=G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

	G4String name="Jaws1X";
	G4Box *box;
	G4LogicalVolume *logVol;
	G4VPhysicalVolume *phVol;
	G4VisAttributes* simpleAlSVisAtt;

	G4ThreeVector centre, halfSize;
	G4RotationMatrix *cRotation=new G4RotationMatrix();
	G4double ZDistanceofJawsXZ = 36.7 * cm;
	G4double Thickness = 7.874* cm;
	centre.set(0.,0.,(ZDistanceofJawsXZ+Thickness/2.));
	halfSize.set(45.*mm, 93.*mm, Thickness/2.);
	box = new G4Box(name+"Box", halfSize.getX(), halfSize.getY(), halfSize.getZ());
	logVol = new G4LogicalVolume(box, W, name+"LV", 0, 0, 0);
	this->SetJawAperture(1, centre, halfSize, this->jaw1XAperture, cRotation);
	phVol= new G4PVPlacement(cRotation, centre, name+"PV", logVol, this->PVWorld, false, 0);

	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region(name+"R");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(2.*cm);
	regVol->SetProductionCuts(cuts);
	logVol->SetRegion(regVol);
	regVol->AddRootLogicalVolume(logVol);

	// Visibility
	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Blue());
	simpleAlSVisAtt->SetVisibility(true);
 	simpleAlSVisAtt->SetForceSolid(true);
	logVol->SetVisAttributes(simpleAlSVisAtt);

	bCreated=true;
	return bCreated;
}
bool CML2Acc1::Jaw2X()
{
	bool bCreated=false;
	G4Material *W=G4NistManager::Instance()->FindOrBuildMaterial("G4_W");

	G4String name="Jaws2X";
	G4Box *box;
	G4LogicalVolume *logVol;
	G4VPhysicalVolume *phVol;
	G4VisAttributes* simpleAlSVisAtt;

	G4ThreeVector centre, halfSize;
	G4RotationMatrix *cRotation=new G4RotationMatrix();
	G4double ZDistanceofJawsXZ = 36.7 * cm;
	G4double Thickness = 7.874*cm;
	centre.set(0.,0.,(ZDistanceofJawsXZ+Thickness/2.));
	halfSize.set(45.*mm, 93.*mm, Thickness/2.);
	box = new G4Box(name+"Box", halfSize.getX(), halfSize.getY(), halfSize.getZ());
	logVol = new G4LogicalVolume(box, W, name+"LV", 0, 0, 0);
	this->SetJawAperture(2, centre, halfSize, this->jaw2XAperture, cRotation);
	phVol= new G4PVPlacement(cRotation, centre, name+"PV", logVol, this->PVWorld, false, 0);

	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region(name+"R");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(2.*cm);
	regVol->SetProductionCuts(cuts);
	logVol->SetRegion(regVol);
	regVol->AddRootLogicalVolume(logVol);

	// Visibility
	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Cyan());
	simpleAlSVisAtt->SetVisibility(true);
 	simpleAlSVisAtt->SetForceSolid(true);
	logVol->SetVisAttributes(simpleAlSVisAtt);

	bCreated=true;
	return bCreated;
}
bool CML2Acc1::Jaw1Y()
{
	bool bCreated=false;
	G4Material *W=G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
	G4String name="Jaws1Y";
	G4Box *box;
	G4LogicalVolume *logVol;
	G4VPhysicalVolume *phVol;
	G4VisAttributes* simpleAlSVisAtt;

	G4ThreeVector centre, halfSize;
	G4RotationMatrix *cRotation=new G4RotationMatrix();
	G4double ZDistanceofJawsYZ = 28.0 * cm;
	G4double Thickness = 7.874* cm;
	centre.set(0.,0.,(ZDistanceofJawsYZ+Thickness/2.));
	halfSize.set(93.*mm, 35.*mm, Thickness/2.);
	box = new G4Box(name+"Box", halfSize.getX(), halfSize.getY(), halfSize.getZ());
	logVol = new G4LogicalVolume(box, W, name+"LV", 0, 0, 0);
	this->SetJawAperture(3, centre, halfSize, this->jaw1YAperture, cRotation);
	phVol= new G4PVPlacement(cRotation, centre, name+"PV", logVol, this->PVWorld, false, 0);

	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region(name+"R");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(2.*cm);
	regVol->SetProductionCuts(cuts);
	logVol->SetRegion(regVol);
	regVol->AddRootLogicalVolume(logVol);

	// Visibility
	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Red());
	simpleAlSVisAtt->SetVisibility(true);
 	simpleAlSVisAtt->SetForceSolid(true);
	logVol->SetVisAttributes(simpleAlSVisAtt);

	bCreated=true;
	return bCreated;
}
bool CML2Acc1::Jaw2Y()
{
	bool bCreated=false;
	G4Material *W=G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
	G4String name="Jaws2Y";
	G4Box *box;
	G4LogicalVolume *logVol;
	G4VPhysicalVolume *phVol;
	G4VisAttributes* simpleAlSVisAtt;

	G4ThreeVector centre, halfSize;
	G4RotationMatrix *cRotation=new G4RotationMatrix();
	G4double ZDistanceofJawsYZ = 28.0 * cm;
	G4double Thickness = 7.874* cm;
	centre.set(0.,0.,(ZDistanceofJawsYZ+Thickness/2.));
	halfSize.set(93.*mm, 35.*mm, Thickness/2.);
	box = new G4Box(name+"Box", halfSize.getX(), halfSize.getY(), halfSize.getZ());
	logVol = new G4LogicalVolume(box, W, name+"LV", 0, 0, 0);
	this->SetJawAperture(4, centre, halfSize, this->jaw2YAperture, cRotation);
	phVol= new G4PVPlacement(cRotation, centre, name+"PV", logVol, this->PVWorld, false, 0);

	// Region for cuts

	G4Region *regVol;
	regVol= new G4Region(name+"R");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(2.*cm);
	regVol->SetProductionCuts(cuts);
	logVol->SetRegion(regVol);
	regVol->AddRootLogicalVolume(logVol);

	// Visibility
	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Magenta());
	simpleAlSVisAtt->SetVisibility(true);
 	simpleAlSVisAtt->SetForceSolid(true);
	logVol->SetVisAttributes(simpleAlSVisAtt);

	bCreated=true;
	return bCreated;
}
bool CML2Acc1::DYNVMLC()
{
	bool bCreated=false;
	 //    material
	G4Material* W = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
	G4Material* Vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

	G4double ZdistanceofDYNVMLC = 50.8*cm;
	G4double precision_err = 0.001*cm;

	// dimension table

	G4double Quarter_target_wl = 0.122*cm;
	G4double Quarter_target_wt = 0.04*cm;
	G4double Quarter_target_wg = 0.04*cm;
	G4double Quarter_target_wtip = 0.05*cm;
	//G4double Quarter_target_wts = 0.089*cm;
	G4double Quarter_target_wbs = 0.089*cm;

	G4double Quarter_target_ztip = 6.75*cm;
	G4double Quarter_target_zl = 6.63*cm;
	G4double Quarter_target_zt = 3.488*cm;
	G4double Quarter_target_zg = 3.488*cm;
	G4double Quarter_target_zts = 0.1*cm;
	G4double Quarter_target_zbs = 0.33*cm;
	G4double Quarter_target_zth = 0.92*cm;
	G4double Quarter_target_zbh = 1.12*cm;

	G4double Quarter_isocenter_wl = 0.122*cm;
	G4double Quarter_isocenter_wt = 0.04*cm;
	G4double Quarter_isocenter_wg = 0.04*cm;
	G4double Quarter_isocenter_wtip = 0.035*cm;
	//G4double Quarter_isocenter_wts = 0.090*cm;
	G4double Quarter_isocenter_wbs = 0.090*cm;

	G4double Quarter_isocenter_ztip = 6.75*cm;
	G4double Quarter_isocenter_zl = 0.12*cm;
	G4double Quarter_isocenter_zt = 3.295*cm;
	G4double Quarter_isocenter_zg = 3.283*cm;
	G4double Quarter_isocenter_zts = 6.41*cm;
	G4double Quarter_isocenter_zbs = 6.65*cm;
	G4double Quarter_isocenter_zth = 5.63*cm;
	G4double Quarter_isocenter_zbh = 5.83*cm;

	G4double Half_target_wl = 0.249*cm;
	G4double Half_target_wt = 0.04*cm;
	G4double Half_target_wg = 0.04*cm;
	G4double Half_target_wtip = 0.105*cm;
	//G4double Half_target_wts = 0.137*cm;
	G4double Half_target_wbs = 0.138*cm;

	G4double Half_target_ztip = 6.70*cm;
	G4double Half_target_zl = 6.58*cm;
	G4double Half_target_zt = 3.47*cm;
	G4double Half_target_zg = 3.48*cm;
	G4double Half_target_zts = 0.1*cm;
	G4double Half_target_zbs = 0.36*cm;
	G4double Half_target_zth = 2.09*cm;
	G4double Half_target_zbh = 2.42*cm;

	G4double Half_isocenter_wl = 0.250*cm;
	G4double Half_isocenter_wt = 0.04*cm;
	G4double Half_isocenter_wg = 0.04*cm;
	G4double Half_isocenter_wtip = 0.075*cm;
	//G4double Half_isocenter_wts = 0.141*cm;
	G4double Half_isocenter_wbs = 0.141*cm;

	G4double Half_isocenter_ztip = 6.70*cm;
	G4double Half_isocenter_zl = 0.12*cm;
	G4double Half_isocenter_zt = 3.25*cm;
	G4double Half_isocenter_zg = 3.29*cm;
	G4double Half_isocenter_zts = 6.34*cm;
	G4double Half_isocenter_zbs = 6.60*cm;
	G4double Half_isocenter_zth = 4.48*cm;
	G4double Half_isocenter_zbh = 4.81*cm;

	G4double Outboard1_wl 			= 0.272*cm;
	G4double Outboard1_wt 			= 0.158*cm;
	G4double Outboard1_wg 			= 0.040*cm;
	G4double Outboard1_wtip 		= 0.105*cm;
	G4double Outboard1_wos	 		= 0.225*cm;
	//G4double Outboard1_wts	 		= 0.137*cm;
	G4double Outboard1_wbs	 		= 0.137*cm;

	G4double Outboard1_ztip 		= 6.700*cm;
	G4double Outboard1_zl 			= 0.670*cm;
	G4double Outboard1_zt 			= 6.370*cm;
	G4double Outboard1_zg 			= 3.480*cm;
	G4double Outboard1_zts 			= 0.360*cm;
	G4double Outboard1_zbs 			= 0.100*cm;
	G4double Outboard1_zos 			= 6.580*cm;
	G4double Outboard1_zth 			= 2.090*cm;
	G4double Outboard1_zbh 			= 2.420*cm;

	G4double Outboard120_wl 		= 0.390*cm;
	G4double Outboard120_wt 		= 0.040*cm;
	G4double Outboard120_wg 		= 0.152*cm;
	G4double Outboard120_wtip 		= 0.075*cm;
	//G4double Outboard120_wos	 	= 0.194*cm;
	G4double Outboard120_wts 		= 0.141*cm;
	//G4double Outboard120_wbs 		= 0.141*cm;

	G4double Outboard120_ztip		= 6.690*cm;
	G4double Outboard120_zl 		= 0.390*cm;
	G4double Outboard120_zt 		= 3.240*cm;
	G4double Outboard120_zg 		= 6.090*cm;
	G4double Outboard120_zts 		= 6.340*cm;
	G4double Outboard120_zbs 		= 6.600*cm;
	G4double Outboard120_zos 		= 0.120*cm;
	G4double Outboard120_zth 		= 3.630*cm;
	G4double Outboard120_zbh 		= 3.950*cm;

	// ----------------------------------------------------- //
	// Quarter_Leaf_Target//
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Quarter_target_rotation=new G4RotationMatrix();
	Quarter_target_rotation->rotateY(12.*deg);
	Quarter_target_rotation->rotateX(90.*deg);

	G4double innerRadiusOfTheTube = 0.*cm;
	G4double outerRadiusOfTheTube = 16.0*cm;
	G4double heightOfTheTube = Quarter_target_wl+Quarter_target_wt;
	G4double startAngleOfTheTube = 0.*deg;
	G4double spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Quarter_target_Tube = new G4Tubs("Quarter_target_Tube",innerRadiusOfTheTube,
									outerRadiusOfTheTube,heightOfTheTube/2.,
									startAngleOfTheTube,spanningAngleOfTheTube); // a pie shape for the rounded shape
	G4LogicalVolume * Quarter_target_Tube_log = 0;
	Quarter_target_Tube_log=new G4LogicalVolume(Quarter_target_Tube,W,"Quarter_target_Tube_log",0,0,0);
	G4double Quarter_target_Box1_Dim_x = 15.65 *cm;
	G4double Quarter_target_Box1_Dim_y = heightOfTheTube;
	G4double Quarter_target_Box1_Dim_z = Quarter_target_ztip;
	G4Box* Quarter_target_Box1 = new G4Box("Quarter_target_Box1",Quarter_target_Box1_Dim_x/2.,Quarter_target_Box1_Dim_y/2.,Quarter_target_Box1_Dim_z/2.);
	G4LogicalVolume * Quarter_target_Box1_log = 0;
	Quarter_target_Box1_log = new G4LogicalVolume(Quarter_target_Box1,W,"Quarter_target_Box1_log",0,0,0);

	G4VSolid* Quarter_target_Leaf1 = new G4UnionSolid("Quarter_target_Leaf1", 
								Quarter_target_Box1, Quarter_target_Tube, 
								Quarter_target_rotation,G4ThreeVector(-Quarter_target_Box1_Dim_x/2.,0,0) ); // union of the pie and a box

	G4double Quarter_target_Box2_Dim_x = 17. *cm;
	G4double Quarter_target_Box2_Dim_y = heightOfTheTube;
	G4double Quarter_target_Box2_Dim_z = Quarter_target_ztip+precision_err;
	G4Box* Quarter_target_Box2 = new G4Box("Quarter_target_Box1",
						Quarter_target_Box2_Dim_x/2.,Quarter_target_Box2_Dim_y/2.,Quarter_target_Box2_Dim_z/2.);
	G4LogicalVolume * Quarter_target_Box2_log =0;
	Quarter_target_Box2_log= new G4LogicalVolume(Quarter_target_Box2,Vacuum,"Quarter_target_Box2_log",0,0,0);


	G4VSolid* Quarter_target_Leaf2_1 = new G4SubtractionSolid("Quarter_target_Leaf2_1",
								   Quarter_target_Leaf1,Quarter_target_Box2,0,
								   G4ThreeVector(0,heightOfTheTube - Quarter_target_wt,+Quarter_target_zt)); // tongue subtraction
	G4VSolid* Quarter_target_Leaf2_2 = new G4SubtractionSolid("Quarter_target_Leaf2_2",
								   Quarter_target_Leaf2_1,Quarter_target_Box2,0,
								   G4ThreeVector(0,-heightOfTheTube + Quarter_target_wg,+Quarter_target_zg)); // groove subtraction


	G4double Quarter_target_Box3_Dim_x = 17 *cm;
	G4double Quarter_target_Box3_Dim_y = heightOfTheTube;
	G4double Quarter_target_Box3_Dim_z = Quarter_target_zbs-Quarter_target_zts;
	G4Box* Quarter_target_Box3 = new G4Box("Quarter_target_Box3",Quarter_target_Box3_Dim_x/2.,Quarter_target_Box3_Dim_y/2.,Quarter_target_Box3_Dim_z/2.); // support rail 
	G4LogicalVolume * Quarter_target_Box3_log=0;
	Quarter_target_Box3_log= new G4LogicalVolume(Quarter_target_Box3,Vacuum,"Quarter_target_Box3_log",0,0,0);

	G4VSolid* Quarter_target_Leaf3 = new G4SubtractionSolid("Quarter_target_Leaf3",Quarter_target_Leaf2_2,Quarter_target_Box3,0,
			G4ThreeVector(0,- heightOfTheTube + Quarter_target_wbs, -(Quarter_target_ztip/2. - Quarter_target_Box3_Dim_z/2. - Quarter_target_zbs))); // support rail subtraction.

	G4double Quarter_target_Box4_Dim_x = 17. *cm;
	G4double Quarter_target_Box4_Dim_y = heightOfTheTube;
	G4double Quarter_target_Box4_Dim_z = Quarter_target_ztip+precision_err;
	G4Box* Quarter_target_Box4 = new G4Box("Quarter_target_Box5",Quarter_target_Box4_Dim_x/2.,Quarter_target_Box4_Dim_y/2.,Quarter_target_Box4_Dim_z/2.); // end tip
	G4LogicalVolume * Quarter_target_Box4_log=0;
	Quarter_target_Box4_log= new G4LogicalVolume(Quarter_target_Box4,Vacuum,"Quarter_target_Box4_log",0,0,0);
	G4VSolid* Quarter_target_Leaf4 = new G4SubtractionSolid("Quarter_target_Leaf4",Quarter_target_Leaf3,Quarter_target_Box4,0,
			G4ThreeVector(0, heightOfTheTube - (Quarter_target_wt+(Quarter_target_wl-Quarter_target_wg-Quarter_target_wtip)), Quarter_target_zl)); // end tip subtraction

	G4double Quarter_target_Box5_Dim_x = (14.3)*cm;
	G4double Quarter_target_Box5_Dim_y = heightOfTheTube+100; // 100 ?????
	G4double Quarter_target_Box5_Dim_z = Quarter_target_zbh-Quarter_target_zth;
	G4Box* Quarter_target_Box5 = new G4Box("Quarter_target_Box5",Quarter_target_Box5_Dim_x/2.,Quarter_target_Box5_Dim_y/2.,Quarter_target_Box5_Dim_z/2.); // drive screw hole 
	G4LogicalVolume * Quarter_target_Box5_log=0;
	Quarter_target_Box5_log= new G4LogicalVolume(Quarter_target_Box5,Vacuum,"Quarter_target_Box5_log",0,0,0);
	G4VSolid* Quarter_target_Leaf5 = new G4SubtractionSolid("Quarter_target_Leaf5",Quarter_target_Leaf4,Quarter_target_Box5,0,
						G4ThreeVector(0, 0,-(Quarter_target_ztip/2. - Quarter_target_Box5_Dim_z/2. - Quarter_target_zth)  ));


	G4LogicalVolume *Quarter_target_Leaf_log = new G4LogicalVolume(Quarter_target_Leaf5,W,"Quarter_target_Leaf_log",0,0,0);

	// ----------------------------------------------------- //
	// Quarter_Leaf_Isocenter//
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Quarter_isocenter_rotation=new G4RotationMatrix();
	Quarter_isocenter_rotation->rotateY(12.*deg);
	Quarter_isocenter_rotation->rotateX(90.*deg);

	innerRadiusOfTheTube = 0.*cm;
	outerRadiusOfTheTube = 16.0*cm;
	heightOfTheTube = Quarter_isocenter_wl+Quarter_isocenter_wt;
	startAngleOfTheTube = 0.*deg;
	spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Quarter_isocenter_Tube = new G4Tubs("Quarter_isocenter_Tube",innerRadiusOfTheTube,
										outerRadiusOfTheTube,heightOfTheTube/2.,
										startAngleOfTheTube,spanningAngleOfTheTube);
	G4LogicalVolume * Quarter_isocenter_Tube_log = 0;
	Quarter_isocenter_Tube_log=new G4LogicalVolume(Quarter_isocenter_Tube,W,"Quarter_isocenter_Tube_log",0,0,0);
	G4double Quarter_isocenter_Box1_Dim_x = 15.65 *cm;
	G4double Quarter_isocenter_Box1_Dim_y = heightOfTheTube;
	G4double Quarter_isocenter_Box1_Dim_z = Quarter_isocenter_ztip;
	G4Box* Quarter_isocenter_Box1 = new G4Box("Quarter_isocenter_Box1",Quarter_isocenter_Box1_Dim_x/2.,Quarter_isocenter_Box1_Dim_y/2.,Quarter_isocenter_Box1_Dim_z/2.);
	G4LogicalVolume * Quarter_isocenter_Box1_log = 0;
	Quarter_isocenter_Box1_log = new G4LogicalVolume(Quarter_isocenter_Box1,W,"Quarter_isocenter_Box1_log",0,0,0);

	G4VSolid* Quarter_isocenter_Leaf1 = new G4UnionSolid("Quarter_isocenter_Leaf1", 
							      Quarter_isocenter_Box1, Quarter_isocenter_Tube, Quarter_isocenter_rotation,
							      G4ThreeVector(-Quarter_isocenter_Box1_Dim_x/2.,0,0) );

	G4double Quarter_isocenter_Box2_Dim_x = 17. *cm;
	G4double Quarter_isocenter_Box2_Dim_y = heightOfTheTube;
	G4double Quarter_isocenter_Box2_Dim_z = Quarter_isocenter_ztip+precision_err;
	G4Box* Quarter_isocenter_Box2 = new G4Box("Quarter_isocenter_Box1",Quarter_isocenter_Box2_Dim_x/2.,Quarter_isocenter_Box2_Dim_y/2.,Quarter_isocenter_Box2_Dim_z/2.);
	G4LogicalVolume * Quarter_isocenter_Box2_log =0;
	Quarter_isocenter_Box2_log= new G4LogicalVolume(Quarter_isocenter_Box2,Vacuum,"Quarter_isocenter_Box2_log",0,0,0);


	G4VSolid* Quarter_isocenter_Leaf2_1 = new G4SubtractionSolid("Quarter_isocenter_Leaf2_1",
								      Quarter_isocenter_Leaf1,Quarter_isocenter_Box2,0,
								      G4ThreeVector(0,heightOfTheTube - Quarter_isocenter_wt,-(Quarter_isocenter_ztip-Quarter_isocenter_zt)));
	G4VSolid* Quarter_isocenter_Leaf2_2 = new G4SubtractionSolid("Quarter_isocenter_Leaf2_2",
								      Quarter_isocenter_Leaf2_1,Quarter_isocenter_Box2,0,
								      G4ThreeVector(0,-heightOfTheTube + Quarter_isocenter_wg,-(Quarter_isocenter_ztip-Quarter_isocenter_zg)));


	G4double Quarter_isocenter_Box3_Dim_x = 17 *cm;
	G4double Quarter_isocenter_Box3_Dim_y = heightOfTheTube;
	G4double Quarter_isocenter_Box3_Dim_z = Quarter_isocenter_zbs-Quarter_isocenter_zts;
	G4Box* Quarter_isocenter_Box3 = new G4Box("Quarter_isocenter_Box3",Quarter_isocenter_Box3_Dim_x/2.,Quarter_isocenter_Box3_Dim_y/2.,Quarter_isocenter_Box3_Dim_z/2.);
	G4LogicalVolume * Quarter_isocenter_Box3_log=0;
	Quarter_isocenter_Box3_log= new G4LogicalVolume(Quarter_isocenter_Box3,Vacuum,"Quarter_isocenter_Box3_log",0,0,0);

	G4VSolid* Quarter_isocenter_Leaf3 = new G4SubtractionSolid("Quarter_isocenter_Leaf3",Quarter_isocenter_Leaf2_2,Quarter_isocenter_Box3,0,
				G4ThreeVector(0,heightOfTheTube - Quarter_isocenter_wbs, -(Quarter_isocenter_ztip/2. + Quarter_isocenter_Box3_Dim_z/2. - Quarter_isocenter_zbs)));

	G4double Quarter_isocenter_Box4_Dim_x = 17. *cm;
	G4double Quarter_isocenter_Box4_Dim_y = heightOfTheTube;
	G4double Quarter_isocenter_Box4_Dim_z = Quarter_isocenter_ztip+precision_err;
	G4Box* Quarter_isocenter_Box4 = new G4Box("Quarter_isocenter_Box5",Quarter_isocenter_Box4_Dim_x/2.,Quarter_isocenter_Box4_Dim_y/2.,Quarter_isocenter_Box4_Dim_z/2.);
	G4LogicalVolume * Quarter_isocenter_Box4_log=0;
	Quarter_isocenter_Box4_log= new G4LogicalVolume(Quarter_isocenter_Box4,Vacuum,"Quarter_isocenter_Box4_log",0,0,0);
	G4VSolid* Quarter_isocenter_Leaf4 = new G4SubtractionSolid("Quarter_isocenter_Leaf4",Quarter_isocenter_Leaf3,Quarter_isocenter_Box4,0,
       	  G4ThreeVector(0, -(heightOfTheTube - (Quarter_isocenter_wt+(Quarter_isocenter_wl-Quarter_isocenter_wg-Quarter_isocenter_wtip))), -(Quarter_isocenter_ztip-Quarter_isocenter_zl)));

	G4double Quarter_isocenter_Box5_Dim_x = (14.3)*cm;
	G4double Quarter_isocenter_Box5_Dim_y = heightOfTheTube+100;
	G4double Quarter_isocenter_Box5_Dim_z = Quarter_isocenter_zbh-Quarter_isocenter_zth;
	G4Box* Quarter_isocenter_Box5 = new G4Box("Quarter_isocenter_Box5",Quarter_isocenter_Box5_Dim_x/2.,Quarter_isocenter_Box5_Dim_y/2.,Quarter_isocenter_Box5_Dim_z/2.);
	G4LogicalVolume * Quarter_isocenter_Box5_log=0;
	Quarter_isocenter_Box5_log= new G4LogicalVolume(Quarter_isocenter_Box5,Vacuum,"Quarter_isocenter_Box5_log",0,0,0);
	G4VSolid* Quarter_isocenter_Leaf5 = new G4SubtractionSolid("Quarter_isocenter_Leaf5",Quarter_isocenter_Leaf4,Quarter_isocenter_Box5,0,
																														G4ThreeVector(0, 0,-(Quarter_isocenter_ztip/2. - Quarter_isocenter_Box5_Dim_z/2. - Quarter_isocenter_zth)  ));


	G4LogicalVolume *Quarter_isocenter_Leaf_log = new G4LogicalVolume(Quarter_isocenter_Leaf5,W,"Quarter_isocenter_Leaf_log",0,0,0);

	// ----------------------------------------------------- //
	// Half_Leaf_Target //
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Half_target_rotation=new G4RotationMatrix();
	Half_target_rotation->rotateY(12.*deg);
	Half_target_rotation->rotateX(90.*deg);

	innerRadiusOfTheTube = 0.*cm;
	outerRadiusOfTheTube = 16.0*cm;
	heightOfTheTube = Half_target_wl+Half_target_wt;
	startAngleOfTheTube = 0.*deg;
	spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Half_target_Tube = new G4Tubs("Half_target_Tube",innerRadiusOfTheTube,
										outerRadiusOfTheTube,heightOfTheTube/2.,
										startAngleOfTheTube,spanningAngleOfTheTube);
	G4LogicalVolume * Half_target_Tube_log = 0;
	Half_target_Tube_log=new G4LogicalVolume(Half_target_Tube,W,"Half_target_Tube_log",0,0,0);
	G4double Half_target_Box1_Dim_x = 15.65 *cm;
	G4double Half_target_Box1_Dim_y = heightOfTheTube;
	G4double Half_target_Box1_Dim_z = Half_target_ztip;
	G4Box* Half_target_Box1 = new G4Box("Half_target_Box1",Half_target_Box1_Dim_x/2.,Half_target_Box1_Dim_y/2.,Half_target_Box1_Dim_z/2.);
	G4LogicalVolume * Half_target_Box1_log = 0;
	Half_target_Box1_log = new G4LogicalVolume(Half_target_Box1,W,"Half_target_Box1_log",0,0,0);

	G4VSolid* Half_target_Leaf1 = new G4UnionSolid("Half_target_Leaf1", Half_target_Box1, Half_target_Tube, Half_target_rotation,G4ThreeVector(-Half_target_Box1_Dim_x/2.,0,0) );

	G4double Half_target_Box2_Dim_x = 17. *cm;
	G4double Half_target_Box2_Dim_y = heightOfTheTube;
	G4double Half_target_Box2_Dim_z = Half_target_ztip+precision_err;
	G4Box* Half_target_Box2 = new G4Box("Half_target_Box1",Half_target_Box2_Dim_x/2.,Half_target_Box2_Dim_y/2.,Half_target_Box2_Dim_z/2.);
	G4LogicalVolume * Half_target_Box2_log =0;
	Half_target_Box2_log= new G4LogicalVolume(Half_target_Box2,Vacuum,"Half_target_Box2_log",0,0,0);


	G4VSolid* Half_target_Leaf2_1 = new G4SubtractionSolid("Half_target_Leaf2_1",
						Half_target_Leaf1,Half_target_Box2,0,G4ThreeVector(0,heightOfTheTube - Half_target_wt,+Half_target_zt));
	G4VSolid* Half_target_Leaf2_2 = new G4SubtractionSolid("Half_target_Leaf2_2",
						Half_target_Leaf2_1,Half_target_Box2,0,G4ThreeVector(0,-heightOfTheTube + Half_target_wg,+Half_target_zg));


	G4double Half_target_Box3_Dim_x = 17 *cm;
	G4double Half_target_Box3_Dim_y = heightOfTheTube;
	G4double Half_target_Box3_Dim_z = Half_target_zbs-Half_target_zts;
	G4Box* Half_target_Box3 = new G4Box("Half_target_Box3",Half_target_Box3_Dim_x/2.,Half_target_Box3_Dim_y/2.,Half_target_Box3_Dim_z/2.);
	G4LogicalVolume * Half_target_Box3_log=0;
	Half_target_Box3_log= new G4LogicalVolume(Half_target_Box3,Vacuum,"Half_target_Box3_log",0,0,0);

	G4VSolid* Half_target_Leaf3 = new G4SubtractionSolid("Half_target_Leaf3",Half_target_Leaf2_2,Half_target_Box3,0,
																														G4ThreeVector(0,- heightOfTheTube + Half_target_wbs, -(Half_target_ztip/2. - Half_target_Box3_Dim_z/2. - Half_target_zbs)));

	G4double Half_target_Box4_Dim_x = 17. *cm;
	G4double Half_target_Box4_Dim_y = heightOfTheTube;
	G4double Half_target_Box4_Dim_z = Half_target_ztip+precision_err;
	G4Box* Half_target_Box4 = new G4Box("Half_target_Box5",Half_target_Box4_Dim_x/2.,Half_target_Box4_Dim_y/2.,Half_target_Box4_Dim_z/2.);
	G4LogicalVolume * Half_target_Box4_log=0;
	Half_target_Box4_log= new G4LogicalVolume(Half_target_Box4,Vacuum,"Half_target_Box4_log",0,0,0);
	G4VSolid* Half_target_Leaf4 = new G4SubtractionSolid("Half_target_Leaf4",Half_target_Leaf3,Half_target_Box4,0,
																														G4ThreeVector(0, heightOfTheTube - (Half_target_wt+(Half_target_wl-Half_target_wg-Half_target_wtip)), Half_target_zl));

	G4double Half_target_Box5_Dim_x = (14.3)*cm;
	G4double Half_target_Box5_Dim_y = heightOfTheTube+100;
	G4double Half_target_Box5_Dim_z = Half_target_zbh-Half_target_zth;
	G4Box* Half_target_Box5 = new G4Box("Half_target_Box5",Half_target_Box5_Dim_x/2.,Half_target_Box5_Dim_y/2.,Half_target_Box5_Dim_z/2.);
	G4LogicalVolume * Half_target_Box5_log=0;
	Half_target_Box5_log= new G4LogicalVolume(Half_target_Box5,Vacuum,"Half_target_Box5_log",0,0,0);
	G4VSolid* Half_target_Leaf5 = new G4SubtractionSolid("Half_target_Leaf5",Half_target_Leaf4,Half_target_Box5,0,
																														G4ThreeVector(0, 0,-(Half_target_ztip/2. - Half_target_Box5_Dim_z/2. - Half_target_zth)  ));


	G4LogicalVolume *Half_target_Leaf_log = new G4LogicalVolume(Half_target_Leaf5,W,"Half_target_Leaf_log",0,0,0);

	// ----------------------------------------------------- //
	// Half_Leaf_Isocenter //
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Half_isocenter_rotation=new G4RotationMatrix();
	Half_isocenter_rotation->rotateY(12.*deg);
	Half_isocenter_rotation->rotateX(90.*deg);

	innerRadiusOfTheTube = 0.*cm;
	outerRadiusOfTheTube = 16.0*cm;
	heightOfTheTube = Half_isocenter_wl+Half_isocenter_wt;
	startAngleOfTheTube = 0.*deg;
	spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Half_isocenter_Tube = new G4Tubs("Half_isocenter_Tube",innerRadiusOfTheTube,
										outerRadiusOfTheTube,heightOfTheTube/2.,
										startAngleOfTheTube,spanningAngleOfTheTube);
	G4LogicalVolume * Half_isocenter_Tube_log = 0;
	Half_isocenter_Tube_log=new G4LogicalVolume(Half_isocenter_Tube,W,"Half_isocenter_Tube_log",0,0,0);
	G4double Half_isocenter_Box1_Dim_x = 15.65 *cm;
	G4double Half_isocenter_Box1_Dim_y = heightOfTheTube;
	G4double Half_isocenter_Box1_Dim_z = Half_isocenter_ztip;
	G4Box* Half_isocenter_Box1 = new G4Box("Half_isocenter_Box1",Half_isocenter_Box1_Dim_x/2.,Half_isocenter_Box1_Dim_y/2.,Half_isocenter_Box1_Dim_z/2.);
	G4LogicalVolume * Half_isocenter_Box1_log = 0;
	Half_isocenter_Box1_log = new G4LogicalVolume(Half_isocenter_Box1,W,"Half_isocenter_Box1_log",0,0,0);

	G4VSolid* Half_isocenter_Leaf1 = new G4UnionSolid("Half_isocenter_Leaf1", 
					Half_isocenter_Box1, Half_isocenter_Tube, Half_isocenter_rotation,G4ThreeVector(-Half_isocenter_Box1_Dim_x/2.,0,0) );

	G4double Half_isocenter_Box2_Dim_x = 17. *cm;
	G4double Half_isocenter_Box2_Dim_y = heightOfTheTube;
	G4double Half_isocenter_Box2_Dim_z = Half_isocenter_ztip+precision_err;
	G4Box* Half_isocenter_Box2 = new G4Box("Half_isocenter_Box1",Half_isocenter_Box2_Dim_x/2.,Half_isocenter_Box2_Dim_y/2.,Half_isocenter_Box2_Dim_z/2.);
	G4LogicalVolume * Half_isocenter_Box2_log =0;
	Half_isocenter_Box2_log= new G4LogicalVolume(Half_isocenter_Box2,Vacuum,"Half_isocenter_Box2_log",0,0,0);


	G4VSolid* Half_isocenter_Leaf2_1 = new G4SubtractionSolid("Half_isocenter_Leaf2_1",
			Half_isocenter_Leaf1,Half_isocenter_Box2,0,G4ThreeVector(0,heightOfTheTube - Half_isocenter_wt,-(Half_isocenter_ztip-Half_isocenter_zt)));
	G4VSolid* Half_isocenter_Leaf2_2 = new G4SubtractionSolid("Half_isocenter_Leaf2_2",
			Half_isocenter_Leaf2_1,Half_isocenter_Box2,0,G4ThreeVector(0,-heightOfTheTube + Half_isocenter_wg,-(Half_isocenter_ztip-Half_isocenter_zg)));


	G4double Half_isocenter_Box3_Dim_x = 17 *cm;
	G4double Half_isocenter_Box3_Dim_y = heightOfTheTube;
	G4double Half_isocenter_Box3_Dim_z = Half_isocenter_zbs-Half_isocenter_zts;
	G4Box* Half_isocenter_Box3 = new G4Box("Half_isocenter_Box3",Half_isocenter_Box3_Dim_x/2.,Half_isocenter_Box3_Dim_y/2.,Half_isocenter_Box3_Dim_z/2.);
	G4LogicalVolume * Half_isocenter_Box3_log=0;
	Half_isocenter_Box3_log= new G4LogicalVolume(Half_isocenter_Box3,Vacuum,"Half_isocenter_Box3_log",0,0,0);

	G4VSolid* Half_isocenter_Leaf3 = new G4SubtractionSolid("Half_isocenter_Leaf3",Half_isocenter_Leaf2_2,Half_isocenter_Box3,0,
				G4ThreeVector(0,heightOfTheTube - Half_isocenter_wbs, -(Half_isocenter_ztip/2. + Half_isocenter_Box3_Dim_z/2. - Half_isocenter_zbs)));

	G4double Half_isocenter_Box4_Dim_x = 17. *cm;
	G4double Half_isocenter_Box4_Dim_y = heightOfTheTube;
	G4double Half_isocenter_Box4_Dim_z = Half_isocenter_ztip+precision_err;
	G4Box* Half_isocenter_Box4 = new G4Box("Half_isocenter_Box5",Half_isocenter_Box4_Dim_x/2.,Half_isocenter_Box4_Dim_y/2.,Half_isocenter_Box4_Dim_z/2.);
	G4LogicalVolume * Half_isocenter_Box4_log=0;
	Half_isocenter_Box4_log= new G4LogicalVolume(Half_isocenter_Box4,Vacuum,"Half_isocenter_Box4_log",0,0,0);
	G4VSolid* Half_isocenter_Leaf4 = new G4SubtractionSolid("Half_isocenter_Leaf4",Half_isocenter_Leaf3,Half_isocenter_Box4,0,
		G4ThreeVector(0, -(heightOfTheTube - (Half_isocenter_wt+(Half_isocenter_wl-Half_isocenter_wg-Half_isocenter_wtip))), -(Half_isocenter_ztip-Half_isocenter_zl)));

	G4double Half_isocenter_Box5_Dim_x = (14.3)*cm;
	G4double Half_isocenter_Box5_Dim_y = heightOfTheTube+100;
	G4double Half_isocenter_Box5_Dim_z = Half_isocenter_zbh-Half_isocenter_zth;
	G4Box* Half_isocenter_Box5 = new G4Box("Half_isocenter_Box5",Half_isocenter_Box5_Dim_x/2.,Half_isocenter_Box5_Dim_y/2.,Half_isocenter_Box5_Dim_z/2.);
	G4LogicalVolume * Half_isocenter_Box5_log=0;
	Half_isocenter_Box5_log= new G4LogicalVolume(Half_isocenter_Box5,Vacuum,"Half_isocenter_Box5_log",0,0,0);
	G4VSolid* Half_isocenter_Leaf5 = new G4SubtractionSolid("Half_isocenter_Leaf5",Half_isocenter_Leaf4,Half_isocenter_Box5,0,
					G4ThreeVector(0, 0,-(Half_isocenter_ztip/2. - Half_isocenter_Box5_Dim_z/2. - Half_isocenter_zth)  ));

	G4LogicalVolume *Half_isocenter_Leaf_log = new G4LogicalVolume(Half_isocenter_Leaf5,W,"Half_isocenter_Leaf_log",0,0,0);

	// ----------------------------------------------------- //
	//      Outboard1      //
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Outboard1_rotation=new G4RotationMatrix();
	Outboard1_rotation->rotateY(12.*deg);
	Outboard1_rotation->rotateX(90.*deg);

	innerRadiusOfTheTube = 0.*cm;
	outerRadiusOfTheTube = 16.0*cm;
	heightOfTheTube = Outboard1_wl+Outboard1_wt;
	startAngleOfTheTube = 0.*deg;
	spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Outboard1_Tube = new G4Tubs("Outboard1_Tube",innerRadiusOfTheTube,
										outerRadiusOfTheTube,heightOfTheTube/2.,
										startAngleOfTheTube,spanningAngleOfTheTube);
	G4LogicalVolume * Outboard1_Tube_log = 0;
	Outboard1_Tube_log=new G4LogicalVolume(Outboard1_Tube,W,"Outboard1_Tube_log",0,0,0);
	G4double Outboard1_Box1_Dim_x = 15.65 *cm;
	G4double Outboard1_Box1_Dim_y = heightOfTheTube;
	G4double Outboard1_Box1_Dim_z = Outboard1_ztip;
	G4Box* Outboard1_Box1 = new G4Box("Outboard1_Box1",Outboard1_Box1_Dim_x/2.,Outboard1_Box1_Dim_y/2.,Outboard1_Box1_Dim_z/2.);
	G4LogicalVolume * Outboard1_Box1_log = 0;
	Outboard1_Box1_log = new G4LogicalVolume(Outboard1_Box1,W,"Outboard1_Box1_log",0,0,0);

	G4VSolid* Outboard1_Leaf1 = new G4UnionSolid("Outboard1_Leaf1", Outboard1_Box1, Outboard1_Tube, Outboard1_rotation,G4ThreeVector(-Outboard1_Box1_Dim_x/2.,0,0) );

	G4double Outboard1_Box2_Dim_x = 17. *cm;
	G4double Outboard1_Box2_Dim_y = heightOfTheTube;
	G4double Outboard1_Box2_Dim_z = Outboard1_ztip+precision_err;
	G4Box* Outboard1_Box2 = new G4Box("Outboard1_Box1",Outboard1_Box2_Dim_x/2.,Outboard1_Box2_Dim_y/2.,Outboard1_Box2_Dim_z/2.);
	G4LogicalVolume * Outboard1_Box2_log =0;
	Outboard1_Box2_log= new G4LogicalVolume(Outboard1_Box2,Vacuum,"Outboard1_Box2_log",0,0,0);


	G4VSolid* Outboard1_Leaf2_1 = new G4SubtractionSolid("Outboard1_Leaf2_1",
					Outboard1_Leaf1,Outboard1_Box2,0,G4ThreeVector(0,heightOfTheTube - Outboard1_wt,-(Outboard1_ztip-Outboard1_zl)));
	G4VSolid* Outboard1_Leaf2_2 = new G4SubtractionSolid("Outboard1_Leaf2_2",
					Outboard1_Leaf2_1,Outboard1_Box2,0,G4ThreeVector(0,-heightOfTheTube + Outboard1_wg,+Outboard1_zg));
	G4VSolid* Outboard1_Leaf2_3 = new G4SubtractionSolid("Outboard1_Leaf2_3",
					Outboard1_Leaf2_2,Outboard1_Box2,0,G4ThreeVector(0,heightOfTheTube - (Outboard1_wt + Outboard1_wl - Outboard1_wos),+Outboard1_zt));


	G4double Outboard1_Box3_Dim_x = 17 *cm;
	G4double Outboard1_Box3_Dim_y = heightOfTheTube;
	G4double Outboard1_Box3_Dim_z = Outboard1_zts-Outboard1_zbs;
	G4Box* Outboard1_Box3 = new G4Box("Outboard1_Box3",Outboard1_Box3_Dim_x/2.,Outboard1_Box3_Dim_y/2.,Outboard1_Box3_Dim_z/2.);
	G4LogicalVolume * Outboard1_Box3_log=0;
	Outboard1_Box3_log= new G4LogicalVolume(Outboard1_Box3,Vacuum,"Outboard1_Box3_log",0,0,0);

	G4VSolid* Outboard1_Leaf3 = new G4SubtractionSolid("Outboard1_Leaf3",Outboard1_Leaf2_3,Outboard1_Box3,0,
				G4ThreeVector(0,- heightOfTheTube + Outboard1_wbs, -(Outboard1_ztip/2. - Outboard1_Box3_Dim_z/2. - Outboard1_zbs)));

	G4double Outboard1_Box4_Dim_x = 17. *cm;
	G4double Outboard1_Box4_Dim_y = heightOfTheTube;
	G4double Outboard1_Box4_Dim_z = Outboard1_ztip+precision_err;
	G4Box* Outboard1_Box4 = new G4Box("Outboard1_Box5",Outboard1_Box4_Dim_x/2.,Outboard1_Box4_Dim_y/2.,Outboard1_Box4_Dim_z/2.);
	G4LogicalVolume * Outboard1_Box4_log=0;
	Outboard1_Box4_log= new G4LogicalVolume(Outboard1_Box4,Vacuum,"Outboard1_Box4_log",0,0,0);
	G4VSolid* Outboard1_Leaf4 = new G4SubtractionSolid("Outboard1_Leaf4",Outboard1_Leaf3,Outboard1_Box4,0,
				G4ThreeVector(0, heightOfTheTube - (Outboard1_wt+(Outboard1_wl-Outboard1_wg-Outboard1_wtip)), Outboard1_zos));

	G4double Outboard1_Box5_Dim_x = (14.3)*cm;
	G4double Outboard1_Box5_Dim_y = heightOfTheTube+100;
	G4double Outboard1_Box5_Dim_z = Outboard1_zbh-Outboard1_zth;
	G4Box* Outboard1_Box5 = new G4Box("Outboard1_Box5",Outboard1_Box5_Dim_x/2.,Outboard1_Box5_Dim_y/2.,Outboard1_Box5_Dim_z/2.);
	G4LogicalVolume * Outboard1_Box5_log=0;
	Outboard1_Box5_log= new G4LogicalVolume(Outboard1_Box5,Vacuum,"Outboard1_Box5_log",0,0,0);
	G4VSolid* Outboard1_Leaf5 = new G4SubtractionSolid("Outboard1_Leaf5",Outboard1_Leaf4,Outboard1_Box5,0,
						G4ThreeVector(0, 0,-(Outboard1_ztip/2. - Outboard1_Box5_Dim_z/2. - Outboard1_zth)  ));

	G4LogicalVolume *Outboard1_Leaf_log = new G4LogicalVolume(Outboard1_Leaf5,W,"Outboard1_Leaf_log",0,0,0);

	// ----------------------------------------------------- //
	// Outboard120         //
	// ----------------------------------------------------- //
	//---------rotation matrix  --------

	G4RotationMatrix*  Outboard120_rotation=new G4RotationMatrix();
	Outboard120_rotation->rotateY(12.*deg);
	Outboard120_rotation->rotateX(90.*deg);

	innerRadiusOfTheTube = 0.*cm;
	outerRadiusOfTheTube = 16.0*cm;
	heightOfTheTube = Outboard120_wl+Outboard120_wt;
	startAngleOfTheTube = 0.*deg;
	spanningAngleOfTheTube = 24.*deg;

	G4Tubs* Outboard120_Tube = new G4Tubs("Outboard120_Tube",innerRadiusOfTheTube,
										outerRadiusOfTheTube,heightOfTheTube/2.,
										startAngleOfTheTube,spanningAngleOfTheTube);
	G4LogicalVolume * Outboard120_Tube_log = 0;
	Outboard120_Tube_log=new G4LogicalVolume(Outboard120_Tube,W,"Outboard120_Tube_log",0,0,0);
	G4double Outboard120_Box1_Dim_x = 15.65 *cm;
	G4double Outboard120_Box1_Dim_y = heightOfTheTube;
	G4double Outboard120_Box1_Dim_z = Outboard120_ztip;
	G4Box* Outboard120_Box1 = new G4Box("Outboard120_Box1",Outboard120_Box1_Dim_x/2.,Outboard120_Box1_Dim_y/2.,Outboard120_Box1_Dim_z/2.);
	G4LogicalVolume * Outboard120_Box1_log = 0;
	Outboard120_Box1_log = new G4LogicalVolume(Outboard120_Box1,W,"Outboard120_Box1_log",0,0,0);

	G4VSolid* Outboard120_Leaf1 = new G4UnionSolid("Outboard120_Leaf1", Outboard120_Box1, Outboard120_Tube, Outboard120_rotation,G4ThreeVector(-Outboard120_Box1_Dim_x/2.,0,0) );

	G4double Outboard120_Box2_Dim_x = 17. *cm;
	G4double Outboard120_Box2_Dim_y = heightOfTheTube;
	G4double Outboard120_Box2_Dim_z = Outboard120_ztip+precision_err;
	G4Box* Outboard120_Box2 = new G4Box("Outboard120_Box1",Outboard120_Box2_Dim_x/2.,Outboard120_Box2_Dim_y/2.,Outboard120_Box2_Dim_z/2.);
	G4LogicalVolume * Outboard120_Box2_log =0;
	Outboard120_Box2_log= new G4LogicalVolume(Outboard120_Box2,Vacuum,"Outboard120_Box2_log",0,0,0);


	G4VSolid* Outboard120_Leaf2_1 = new G4SubtractionSolid("Outboard120_Leaf2_1",
			Outboard120_Leaf1,Outboard120_Box2,0,G4ThreeVector(0,heightOfTheTube - Outboard120_wt,-(Outboard120_ztip-Outboard120_zt)));
	G4VSolid* Outboard120_Leaf2_2 = new G4SubtractionSolid("Outboard120_Leaf2_2",
			Outboard120_Leaf2_1,Outboard120_Box2,0,G4ThreeVector(0,-(heightOfTheTube - (Outboard1_wt + Outboard1_wl - Outboard1_wos)),-(Outboard1_ztip-Outboard120_zl)));
	G4VSolid* Outboard120_Leaf2_3 = new G4SubtractionSolid("Outboard120_Leaf2_3",
			Outboard120_Leaf2_2,Outboard120_Box2,0,G4ThreeVector(0,-heightOfTheTube + Outboard120_wg,+Outboard120_zg));


	G4double Outboard120_Box3_Dim_x = 17 *cm;
	G4double Outboard120_Box3_Dim_y = heightOfTheTube;
	G4double Outboard120_Box3_Dim_z = Outboard120_zbs-Outboard120_zts;
	G4Box* Outboard120_Box3 = new G4Box("Outboard120_Box3",Outboard120_Box3_Dim_x/2.,Outboard120_Box3_Dim_y/2.,Outboard120_Box3_Dim_z/2.);
	G4LogicalVolume * Outboard120_Box3_log=0;
	Outboard120_Box3_log= new G4LogicalVolume(Outboard120_Box3,Vacuum,"Outboard120_Box3_log",0,0,0);

	G4VSolid* Outboard120_Leaf3 = new G4SubtractionSolid("Outboard120_Leaf3",Outboard120_Leaf2_3,Outboard120_Box3,0,
					G4ThreeVector(0,heightOfTheTube - Outboard120_wts, -(Outboard120_ztip/2. + Outboard120_Box3_Dim_z/2. - Outboard120_zbs)));

	G4double Outboard120_Box4_Dim_x = 17. *cm;
	G4double Outboard120_Box4_Dim_y = heightOfTheTube;
	G4double Outboard120_Box4_Dim_z = Outboard120_ztip+precision_err;
	G4Box* Outboard120_Box4 = new G4Box("Outboard120_Box5",Outboard120_Box4_Dim_x/2.,Outboard120_Box4_Dim_y/2.,Outboard120_Box4_Dim_z/2.);
	G4LogicalVolume * Outboard120_Box4_log=0;
	Outboard120_Box4_log= new G4LogicalVolume(Outboard120_Box4,Vacuum,"Outboard120_Box4_log",0,0,0);
	G4VSolid* Outboard120_Leaf4 = new G4SubtractionSolid("Outboard120_Leaf4",Outboard120_Leaf3,Outboard120_Box4,0,
									G4ThreeVector(0, -Outboard120_wtip, -(Outboard120_ztip-Outboard120_zos)));

	G4double Outboard120_Box5_Dim_x = (14.3)*cm;
	G4double Outboard120_Box5_Dim_y = heightOfTheTube+100;
	G4double Outboard120_Box5_Dim_z = Outboard120_zbh-Outboard120_zth;
	G4Box* Outboard120_Box5 = new G4Box("Outboard120_Box5",Outboard120_Box5_Dim_x/2.,Outboard120_Box5_Dim_y/2.,Outboard120_Box5_Dim_z/2.);
	G4LogicalVolume * Outboard120_Box5_log=0;
	Outboard120_Box5_log= new G4LogicalVolume(Outboard120_Box5,Vacuum,"Outboard120_Box5_log",0,0,0);
	G4VSolid* Outboard120_Leaf5 = new G4SubtractionSolid("Outboard120_Leaf5",Outboard120_Leaf4,Outboard120_Box5,0,
																														G4ThreeVector(0, 0,-(Outboard120_ztip/2. - Outboard120_Box5_Dim_z/2. - Outboard120_zth)  ));


	G4LogicalVolume *Outboard120_Leaf_log = new G4LogicalVolume(Outboard120_Leaf5,W,"Outboard120_Leaf_log",0,0,0);

	// ----------------------- //
	///MLC Left///
	// ----------------------- //
	G4double DYNVMLC_A_Dim_x = 15.*cm;
	G4double DYNVMLC_A_Dim_y = 20.*cm;
	G4double DYNVMLC_A_Dim_z = 11.6*cm;
	G4Box* DYNVMLC_A_box = new G4Box("DYNVMLC_A_box",DYNVMLC_A_Dim_x,DYNVMLC_A_Dim_y,DYNVMLC_A_Dim_z/2.);
	G4LogicalVolume *DYNVMLC_A_log = new G4LogicalVolume(DYNVMLC_A_box,Vacuum,"DYNVMLC_A_log",0,0,0);

	// MLC Left Location
	G4double DYNVMLC_A_Pos_x = -15.*cm;             
	G4double DYNVMLC_A_Pos_y = 0.*cm;
	G4double DYNVMLC_A_Pos_z = ZdistanceofDYNVMLC;

	G4VPhysicalVolume *DYNVMLC_A_phys=0;
	DYNVMLC_A_phys = new G4PVPlacement(0, G4ThreeVector(DYNVMLC_A_Pos_x,DYNVMLC_A_Pos_y,DYNVMLC_A_Pos_z), "DYNVMLC_A",DYNVMLC_A_log,this->PVWorld,false,0);

	G4double Leaf_Gap = 0.0047*cm;
	//G4double Outboard120_PosY1 = -11.81855*cm;
	G4double Outboard120_PosY1 = -5.76285*cm;
	G4double Outboard120_to_Half_tar = Outboard120_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_target_wg;

	new G4PVPlacement(0, G4ThreeVector(leavesA[1],Outboard120_PosY1,0), "Outboard120_Leaf", Outboard120_Leaf_log, DYNVMLC_A_phys,false,0);

	G4double Half_PosY1 = Outboard120_PosY1 + Outboard120_to_Half_tar;
	G4double Half_PosZ1 = -0.24*cm;
	G4double Half_Step_iso_to_tar = Half_isocenter_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_target_wg;
	G4double Half_Step_tar_to_iso = Half_isocenter_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_isocenter_wg;

	for(G4int Half_Loop=1;Half_Loop<=14;Half_Loop+=2)
	{
          new G4PVPlacement(0, G4ThreeVector(leavesA[Half_Loop],Half_PosY1,Half_PosZ1),	"Half_Target_Leaf", Half_target_Leaf_log, DYNVMLC_A_phys,false,0);
		Half_PosY1+= Half_Step_tar_to_iso;
	  new G4PVPlacement(0, G4ThreeVector(leavesA[Half_Loop+1],Half_PosY1,0), "Half_Isocenter_Leaf", Half_isocenter_Leaf_log, DYNVMLC_A_phys,false,0);
		Half_PosY1+= Half_Step_iso_to_tar;
	}
	
	Half_PosY1 -= Half_Step_iso_to_tar;

	G4double Quarter_PosY1 = Half_PosY1+ Half_target_Box1_Dim_y/2. + Quarter_isocenter_Box1_Dim_y/2. + Leaf_Gap - Quarter_target_wg;
	G4double Quarter_PosZ1 = -0.24*cm;
	G4double Quarter_Step_iso_to_tar = Quarter_isocenter_Box1_Dim_y/2. + Quarter_target_Box1_Dim_y/2. + Leaf_Gap - Quarter_target_wg;
	G4double Quarter_Step_tar_to_iso = Quarter_isocenter_Box1_Dim_y/2. + Quarter_target_Box1_Dim_y/2. + Leaf_Gap - Quarter_isocenter_wg;

	for(G4int Quarter_Loop=15;Quarter_Loop<=46;Quarter_Loop+=2)
	{
          new G4PVPlacement(0, G4ThreeVector(leavesA[Quarter_Loop],Quarter_PosY1,0), "Quarter_Isocenter_Leaf", Quarter_isocenter_Leaf_log, DYNVMLC_A_phys,false,0);
		Quarter_PosY1+= Quarter_Step_tar_to_iso;
	  new G4PVPlacement(0, G4ThreeVector(leavesA[Quarter_Loop+1],Quarter_PosY1,Quarter_PosZ1), "Quarter_Tarcenter_Leaf", Quarter_target_Leaf_log, DYNVMLC_A_phys,false,0);
		Quarter_PosY1+= Quarter_Step_iso_to_tar;
	}

	G4double Half_PosY2 = Quarter_PosY1+ Quarter_target_Box1_Dim_y/2. + Half_isocenter_Box1_Dim_y/2. + Leaf_Gap - Half_isocenter_wg - Quarter_Step_iso_to_tar;
	G4double Half_PosZ2 = -0.24*cm;

	for(G4int Half_Loop=47;Half_Loop<=60;Half_Loop+=2)
	{
	  new G4PVPlacement(0, G4ThreeVector(leavesA[Half_Loop],Half_PosY2,0), "Half_Isocenter_Leaf", Half_isocenter_Leaf_log, DYNVMLC_A_phys,false,0);
		Half_PosY2+= Half_Step_iso_to_tar;
	  new G4PVPlacement(0, G4ThreeVector(leavesA[Half_Loop+1],Half_PosY2,Half_PosZ2),	"Half_Tarcenter_Leaf", Half_target_Leaf_log, DYNVMLC_A_phys,false,0);
		Half_PosY2+= Half_Step_tar_to_iso;
	}

	Half_PosY2 -= Half_Step_iso_to_tar;
	
	G4double Outboard1_PosY1 = Half_PosY2 + Outboard1_Box1_Dim_y/2. + Half_isocenter_Box1_Dim_y/2. + Leaf_Gap - Outboard1_wg;
	G4double Outboard1_PosZ1 = -0.24*cm;

	new G4PVPlacement(0, G4ThreeVector(leavesA[60],Outboard1_PosY1,Outboard1_PosZ1), "Outboard1_Leaf", Outboard1_Leaf_log, DYNVMLC_A_phys,false,0);

	// ----------------------- //
	///MLC Right///
	// ----------------------- //
	G4RotationMatrix*  MLC_rotation=new G4RotationMatrix();
	MLC_rotation->rotateY(180*deg);
	G4double DYNVMLC_B_Dim_x = 15.*cm;
	G4double DYNVMLC_B_Dim_y = 20.*cm;
	G4double DYNVMLC_B_Dim_z = 11.6*cm;
	G4Box* DYNVMLC_B_box = new G4Box("DYNVMLC_B_box",DYNVMLC_B_Dim_x,DYNVMLC_B_Dim_y,DYNVMLC_B_Dim_z/2.);
	G4LogicalVolume *DYNVMLC_B_log = new G4LogicalVolume(DYNVMLC_B_box,Vacuum,"DYNVMLC_B_log",0,0,0);
	G4double DYNVMLC_B_Pos_x = 15.*cm;
	G4double DYNVMLC_B_Pos_y = 0.*cm;
	G4double DYNVMLC_B_Pos_z = ZdistanceofDYNVMLC;

	G4VPhysicalVolume *DYNVMLC_B_phys=0;
	DYNVMLC_B_phys = new G4PVPlacement(MLC_rotation, G4ThreeVector(DYNVMLC_B_Pos_x,DYNVMLC_B_Pos_y,DYNVMLC_B_Pos_z), "DYNVMLC_B",DYNVMLC_B_log,this->PVWorld,false,0);

	Leaf_Gap = 0.0047*cm;
	//Outboard120_PosY1 = -11.81855*cm;
	Outboard120_PosY1 = -5.76285*cm;
	Outboard120_to_Half_tar = Outboard120_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_target_wg;

	new G4PVPlacement(0, G4ThreeVector(leavesB[1],Outboard120_PosY1,0),	"Outboard120_Leaf", Outboard120_Leaf_log, DYNVMLC_B_phys,false,0);



	Half_PosY1 = Outboard120_PosY1 + Outboard120_to_Half_tar;
	Half_PosZ1 = -0.24*cm;
	Half_Step_iso_to_tar = Half_isocenter_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_target_wg;
	Half_Step_tar_to_iso = Half_isocenter_Box1_Dim_y/2. + Half_target_Box1_Dim_y/2. + Leaf_Gap - Half_isocenter_wg;


	for(G4int Half_Loop=1;Half_Loop<=14;Half_Loop+=2)
	{
		new G4PVPlacement(0, G4ThreeVector(leavesB[Half_Loop],Half_PosY1,Half_PosZ1),	"Half_Target_Leaf", Half_target_Leaf_log, DYNVMLC_B_phys,false,0);
		Half_PosY1+= Half_Step_tar_to_iso;
		new G4PVPlacement(0, G4ThreeVector(leavesB[Half_Loop+1],Half_PosY1,0), "Half_Isocenter_Leaf", Half_isocenter_Leaf_log, DYNVMLC_B_phys,false,0);
		Half_PosY1+= Half_Step_iso_to_tar;
	}
	
	Half_PosY1 -= Half_Step_iso_to_tar;

	Quarter_PosY1 = Half_PosY1+ Half_target_Box1_Dim_y/2. + Quarter_isocenter_Box1_Dim_y/2. + Leaf_Gap - Quarter_target_wg;
	Quarter_PosZ1 = -0.24*cm;
	Quarter_Step_iso_to_tar = Quarter_isocenter_Box1_Dim_y/2. + Quarter_target_Box1_Dim_y/2. + Leaf_Gap - Quarter_target_wg;
	Quarter_Step_tar_to_iso = Quarter_isocenter_Box1_Dim_y/2. + Quarter_target_Box1_Dim_y/2. + Leaf_Gap - Quarter_isocenter_wg;

	for(G4int Quarter_Loop=15;Quarter_Loop<=46;Quarter_Loop+=2)
	{
		new G4PVPlacement(0, G4ThreeVector(leavesB[Quarter_Loop],Quarter_PosY1,Quarter_PosZ1),	"Quarter_Tarcenter_Leaf", Quarter_target_Leaf_log, DYNVMLC_B_phys,false,0);
		Quarter_PosY1+= Quarter_Step_iso_to_tar;
		new G4PVPlacement(0, G4ThreeVector(leavesB[Quarter_Loop+1],Quarter_PosY1,0), "Quarter_Isocenter_Leaf", Quarter_isocenter_Leaf_log, DYNVMLC_B_phys,false,0);
		Quarter_PosY1+= Quarter_Step_tar_to_iso;
	}

	Half_PosY2 = Quarter_PosY1+ Quarter_target_Box1_Dim_y/2. + Half_isocenter_Box1_Dim_y/2. + Leaf_Gap - Half_isocenter_wg - Quarter_Step_iso_to_tar;
	Half_PosZ2 = -0.24*cm;

	for(G4int Half_Loop=47;Half_Loop<=60;Half_Loop+=2)
	{
		new G4PVPlacement(0, G4ThreeVector(leavesB[Half_Loop],Half_PosY2,Half_PosZ2),	"Half_Tarcenter_Leaf", Half_target_Leaf_log, DYNVMLC_B_phys,false,0);
		Half_PosY2+= Half_Step_tar_to_iso;
		new G4PVPlacement(0, G4ThreeVector(leavesB[Half_Loop+1],Half_PosY2,0), "Half_Isocenter_Leaf", Half_isocenter_Leaf_log, DYNVMLC_B_phys,false,0);
		Half_PosY2+= Half_Step_iso_to_tar;
	}

	Half_PosY2 -= Half_Step_iso_to_tar;

	Outboard1_PosY1 = Half_PosY2 + Outboard1_Box1_Dim_y/2. + Half_isocenter_Box1_Dim_y/2. + Leaf_Gap - Outboard1_wg;
	Outboard1_PosZ1 = -0.24*cm;

	new G4PVPlacement(0, G4ThreeVector(leavesB[60],Outboard1_PosY1,Outboard1_PosZ1),	"Outboard1_Leaf", Outboard1_Leaf_log, DYNVMLC_B_phys,false,0);

	// ***********  REGIONS for CUTS

	G4Region *regVol;
	regVol= new G4Region("DYNVMLC");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*cm);
	regVol->SetProductionCuts(cuts);

	Quarter_target_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Quarter_target_Leaf_log);
	Quarter_isocenter_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Quarter_isocenter_Leaf_log);
	Half_target_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Half_target_Leaf_log);
	Half_isocenter_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Half_isocenter_Leaf_log);
	Outboard1_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Outboard1_Leaf_log);
	Outboard120_Leaf_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Outboard120_Leaf_log);

	// *********** Visualization attributes

	G4VisAttributes* simpleWVisAtt;
	simpleWVisAtt= new G4VisAttributes(G4Colour::Magenta());
	simpleWVisAtt->SetVisibility(true);
	simpleWVisAtt->SetForceSolid(true);

	Quarter_target_Leaf_log->SetVisAttributes(simpleWVisAtt);
	Quarter_isocenter_Leaf_log->SetVisAttributes(simpleWVisAtt);
	Half_target_Leaf_log->SetVisAttributes(simpleWVisAtt);
	Half_isocenter_Leaf_log->SetVisAttributes(simpleWVisAtt);
	Outboard1_Leaf_log->SetVisAttributes(simpleWVisAtt);
	Outboard120_Leaf_log->SetVisAttributes(simpleWVisAtt);


	bCreated=true;
	return bCreated;
}
bool CML2Acc1::MLC()
{
	bool bCreated=false;
 //    material
	G4Material *Fe=G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
	G4VisAttributes* simpleAlSVisAtt;
	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region("MLCR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(1.0*cm);
	regVol->SetProductionCuts(cuts);

	G4ThreeVector boxSize;

	G4ThreeVector centreStart;
	centreStart.set(0.,0.,50.8*cm);

	boxSize.set(6./2.*mm, 180./2.*mm, 50./2.*mm);

	// single leaf
	G4Box* boxLeaf =new G4Box("LeafBox", boxSize.getX(), boxSize.getY(), boxSize.getZ());

	G4LogicalVolume *leafLVA = new G4LogicalVolume(boxLeaf, Fe, "leafSolidALV", 0, 0, 0);
	G4LogicalVolume *leafLVB = new G4LogicalVolume(boxLeaf, Fe, "leafSolidBLV", 0, 0, 0);

	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Cyan());
	simpleAlSVisAtt->SetVisibility(true);
// 	simpleAlSVisAtt->SetForceSolid(true);
	leafLVA->SetVisAttributes(simpleAlSVisAtt);
	leafLVA->SetRegion(regVol);
	regVol->AddRootLogicalVolume(leafLVA);
	
	simpleAlSVisAtt= new G4VisAttributes(G4Colour::Green());
	simpleAlSVisAtt->SetVisibility(true);
// 	simpleAlSVisAtt->SetForceSolid(true);
	leafLVB->SetVisAttributes(simpleAlSVisAtt);
	leafLVB->SetRegion(regVol);
	regVol->AddRootLogicalVolume(leafLVB);

	int i;
	G4String PVname;
	G4VPhysicalVolume *leafPhys; 
	int j=0;

	G4ThreeVector centre;
	int nhalfLeaves=(int)(this->leavesA.size()/2.);
	centre= centreStart + G4ThreeVector(-nhalfLeaves*boxSize.getX(), 0.,0.);
	for (i=1;i<(int)this->leavesA.size(); i++)
	{
		G4String s;
		char appo[10];
		sprintf(appo,"%d",i);
		s=appo;
		PVname="leafA"+s;
		centre.setX(centre.getX()+boxSize.getX()*2.);
		centre.setY(-boxSize.getY()-this->leavesA[i]);
		leafPhys=new G4PVPlacement(0, centre, PVname, leafLVA, this->PVWorld, false, i);
		j++;
	}
	nhalfLeaves=(int)(this->leavesB.size()/2.);
	centre=centreStart+G4ThreeVector(-nhalfLeaves*boxSize.getX(), 0.,0.);
	for (i=1;i<(int)this->leavesB.size(); i++)
	{
		G4String s;
		char appo[10];
		sprintf(appo,"%d",i);
		s=appo;
		PVname="leafB"+s;
		centre.setX(centre.getX()+boxSize.getX()*2.);
		centre.setY(+boxSize.getY()+this->leavesB[i]);
		leafPhys=new G4PVPlacement(0, centre, PVname, leafLVB, this->PVWorld, false, i);
		j++;
	}
	bCreated=true;
	return bCreated;
}

bool CML2Acc1::Upper_Wedge()		//20cm X 40cm, 15'
{
	bool bCreated=false;
	  //    materials

	G4Material *LowCarbon=G4NistManager::Instance()->FindOrBuildMaterial("G4_C");


	G4double ZdistanceofUpper_Wedge = 57.404*cm;
	G4double Standard_Dimx =62.5*mm;

	  //   Upper_Wedge1 volumes
	G4double Upper_WedgeDim1_x1 = 62.5*mm;
	G4double Upper_WedgeDim1_x2 = Upper_WedgeDim1_x1;
	G4double Upper_WedgeDim1_x3 = 62.5*mm;
	G4double Upper_WedgeDim1_x4 = Upper_WedgeDim1_x3;
	G4double Upper_WedgeDim1_y1 = 126.7 *mm;
	G4double Upper_WedgeDim1_y2 = Upper_WedgeDim1_y1;
	G4double Upper_WedgeDim1_z 	= 2.7 / 2. *mm ;
	G4double Upper_WedgepTheta1 = 0;
	G4Trap* Upper_Wedge_box1 = new  G4Trap( "Upper_Wedge_box1", Upper_WedgeDim1_z, Upper_WedgepTheta1, 0, 		// pName, pDz, pTheta, pPhi,
						 Upper_WedgeDim1_y1, Upper_WedgeDim1_x1, Upper_WedgeDim1_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Upper_WedgeDim1_y2, Upper_WedgeDim1_x3, Upper_WedgeDim1_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Upper_Wedge_log1 = new G4LogicalVolume(Upper_Wedge_box1,LowCarbon,"Upper_Wedge_log1",0,0,0);
	G4double Upper_WedgePos1_x = 0.0*m;
	G4double Upper_WedgePos1_y = 0.0*m;
	G4double Upper_WedgePos1_z = ZdistanceofUpper_Wedge + (Upper_WedgeDim1_z);
	ZdistanceofUpper_Wedge += (Upper_WedgeDim1_z*2.);
	G4VPhysicalVolume *Upper_Wedge_phys1=0;
	Upper_Wedge_phys1 = new G4PVPlacement(0, G4ThreeVector(Upper_WedgePos1_x,Upper_WedgePos1_y,Upper_WedgePos1_z),"Upper_Wedge1",Upper_Wedge_log1,this->PVWorld,false,0);


	  //   Upper_Wedge2 volumes
	G4double Upper_WedgeDim2_x1 = 62.5*mm;
	G4double Upper_WedgeDim2_x2 = Upper_WedgeDim2_x1;
	G4double Upper_WedgeDim2_x3 = 59.7*mm;
	G4double Upper_WedgeDim2_x4 = Upper_WedgeDim2_x3;
	G4double Upper_WedgeDim2_y1 = 126.7 *mm;
	G4double Upper_WedgeDim2_y2 = Upper_WedgeDim2_y1;
	G4double Upper_WedgeDim2_z = 0.5 / 2. *mm ;
	G4double Upper_WedgepTheta2 =  (90*degree) - (atan(Upper_WedgeDim2_z*2./(Upper_WedgeDim2_x1-Upper_WedgeDim2_x3))) ;
	G4Trap* Upper_Wedge_box2 = new  G4Trap( "Upper_Wedge_box2", Upper_WedgeDim2_z, Upper_WedgepTheta2, 0, 		// pName, pDz, pTheta, pPhi,
						 Upper_WedgeDim2_y1, Upper_WedgeDim2_x1, Upper_WedgeDim2_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Upper_WedgeDim2_y2, Upper_WedgeDim2_x3, Upper_WedgeDim2_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Upper_Wedge_log2 = new G4LogicalVolume(Upper_Wedge_box2,LowCarbon,"Upper_Wedge_log2",0,0,0);
	G4double Upper_WedgePos2_x = Standard_Dimx-((Upper_WedgeDim2_x1-Upper_WedgeDim2_x3)/2 + Upper_WedgeDim2_x3);
	G4double Upper_WedgePos2_y = 0.0*m;
	G4double Upper_WedgePos2_z = ZdistanceofUpper_Wedge + (Upper_WedgeDim2_z);
	ZdistanceofUpper_Wedge += (Upper_WedgeDim2_z*2.);
	G4VPhysicalVolume *Upper_Wedge_phys2=0;
	Upper_Wedge_phys2 = new G4PVPlacement(0, G4ThreeVector(Upper_WedgePos2_x,Upper_WedgePos2_y,Upper_WedgePos2_z),"Upper_Wedge2",Upper_Wedge_log2,this->PVWorld,false,0);

	  //   Upper_Wedge3 volumes
	G4double Upper_WedgeDim3_x1 = 59.7*mm;
	G4double Upper_WedgeDim3_x2 = Upper_WedgeDim3_x1;
	G4double Upper_WedgeDim3_x3 = 49.2*mm;
	G4double Upper_WedgeDim3_x4 = Upper_WedgeDim3_x3;
	G4double Upper_WedgeDim3_y1 = 126.7 *mm;
	G4double Upper_WedgeDim3_y2 = Upper_WedgeDim3_y1;
	G4double Upper_WedgeDim3_z = 1.8 / 2. *mm ;
	G4double Upper_WedgepTheta3 = (90*degree) - (atan(Upper_WedgeDim3_z*2./(Upper_WedgeDim3_x1-Upper_WedgeDim3_x3)))  ;
	G4Trap* Upper_Wedge_box3 = new  G4Trap( "Upper_Wedge_box3", Upper_WedgeDim3_z, Upper_WedgepTheta3, 0, 		// pName, pDz, pTheta, pPhi,
						 Upper_WedgeDim3_y1, Upper_WedgeDim3_x1, Upper_WedgeDim3_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Upper_WedgeDim3_y2, Upper_WedgeDim3_x3, Upper_WedgeDim3_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Upper_Wedge_log3 = new G4LogicalVolume(Upper_Wedge_box3,LowCarbon,"Upper_Wedge_log3",0,0,0);
	G4double Upper_WedgePos3_x = Standard_Dimx-((Upper_WedgeDim3_x1-Upper_WedgeDim3_x3)/2 + Upper_WedgeDim3_x3);
	G4double Upper_WedgePos3_y = 0.0*m;
	G4double Upper_WedgePos3_z = ZdistanceofUpper_Wedge + (Upper_WedgeDim3_z);
	ZdistanceofUpper_Wedge += (Upper_WedgeDim3_z*2.);
	G4VPhysicalVolume *Upper_Wedge_phys3=0;
	Upper_Wedge_phys3 = new G4PVPlacement(0, G4ThreeVector(Upper_WedgePos3_x,Upper_WedgePos3_y,Upper_WedgePos3_z),"Upper_Wedge2",Upper_Wedge_log3,this->PVWorld,false,0);


	  //   Upper_Wedge4 volumes
	G4double Upper_WedgeDim4_x1 = 49.2*mm;
	G4double Upper_WedgeDim4_x2 = Upper_WedgeDim4_x1;
	G4double Upper_WedgeDim4_x3 = 1e-90*mm;
	G4double Upper_WedgeDim4_x4 = Upper_WedgeDim4_x3;
	G4double Upper_WedgeDim4_y1 = 126.7 *mm;
	G4double Upper_WedgeDim4_y2 = Upper_WedgeDim4_y1;
	G4double Upper_WedgeDim4_z = 6.9 / 2. *mm ;
	G4double Upper_WedgepTheta4 = (90*degree) - (atan(Upper_WedgeDim4_z*2./(Upper_WedgeDim4_x1-Upper_WedgeDim4_x3))) ;
	G4Trap* Upper_Wedge_box4 = new  G4Trap( "Upper_Wedge_box4", Upper_WedgeDim4_z, Upper_WedgepTheta4, 0, 		// pName, pDz, pTheta, pPhi,
						 Upper_WedgeDim4_y1, Upper_WedgeDim4_x1, Upper_WedgeDim4_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Upper_WedgeDim4_y2, Upper_WedgeDim4_x3, Upper_WedgeDim4_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Upper_Wedge_log4 = new G4LogicalVolume(Upper_Wedge_box4,LowCarbon,"Upper_Wedge_log4",0,0,0);
	G4double Upper_WedgePos4_x = Standard_Dimx-((Upper_WedgeDim4_x1-Upper_WedgeDim4_x3)/2 + Upper_WedgeDim4_x3);
	G4double Upper_WedgePos4_y = 0.0*m;
	G4double Upper_WedgePos4_z = ZdistanceofUpper_Wedge + (Upper_WedgeDim4_z);
	ZdistanceofUpper_Wedge += (Upper_WedgeDim4_z*2.);
	G4VPhysicalVolume *Upper_Wedge_phys4=0;
	Upper_Wedge_phys4 = new G4PVPlacement(0, G4ThreeVector(Upper_WedgePos4_x,Upper_WedgePos4_y,Upper_WedgePos4_z),"Upper_Wedge4",Upper_Wedge_log4,this->PVWorld,false,0);


	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region("Upper_WedgeR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*mm);
	regVol->SetProductionCuts(cuts);
	Upper_Wedge_log1->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Upper_Wedge_log1);
	Upper_Wedge_log2->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Upper_Wedge_log2);
	Upper_Wedge_log3->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Upper_Wedge_log3);
	Upper_Wedge_log4->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Upper_Wedge_log4);

	// Visualization attributes

	G4VisAttributes* simpleLowCarbonVisAtt;
	simpleLowCarbonVisAtt= new G4VisAttributes(G4Colour::Blue());
	simpleLowCarbonVisAtt->SetVisibility(true);
	simpleLowCarbonVisAtt->SetForceSolid(true);
	Upper_Wedge_log1->SetVisAttributes(simpleLowCarbonVisAtt);
	Upper_Wedge_log2->SetVisAttributes(simpleLowCarbonVisAtt);
	Upper_Wedge_log3->SetVisAttributes(simpleLowCarbonVisAtt);
	Upper_Wedge_log4->SetVisAttributes(simpleLowCarbonVisAtt);
	bCreated=true;
	return bCreated;
}

bool CML2Acc1::Lower_Wedge()		//20cm X 40cm, 15'
{
	bool bCreated=false;
	  //    materials

	G4Material *LowCarbon=G4NistManager::Instance()->FindOrBuildMaterial("G4_C");


	G4double ZdistanceofLower_Wedge = 69.85*cm - 11.8*mm;
	G4double Standard_Dimx =70.1*mm;

	  //   Lower_Wedge1 volumes
	G4double Lower_WedgeDim1_x1 = 1e-90*mm;
	G4double Lower_WedgeDim1_x2 = Lower_WedgeDim1_x1;
	G4double Lower_WedgeDim1_x3 = 10.15*mm;
	G4double Lower_WedgeDim1_x4 = Lower_WedgeDim1_x3;
	G4double Lower_WedgeDim1_y1 = 150. *mm;
	G4double Lower_WedgeDim1_y2 = Lower_WedgeDim1_y1;
	G4double Lower_WedgeDim1_z 	= 1 / 2. *mm ;
	G4double Lower_WedgepTheta1 = (90*degree) - (atan(Lower_WedgeDim1_z*2./(Lower_WedgeDim1_x3-Lower_WedgeDim1_x1))) ;
	G4Trap* Lower_Wedge_box1 = new  G4Trap( "Lower_Wedge_box1", Lower_WedgeDim1_z, Lower_WedgepTheta1, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim1_y1, Lower_WedgeDim1_x1, Lower_WedgeDim1_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim1_y2, Lower_WedgeDim1_x3, Lower_WedgeDim1_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log1 = new G4LogicalVolume(Lower_Wedge_box1,LowCarbon,"Lower_Wedge_log1",0,0,0);
	G4double Lower_WedgePos1_x = Standard_Dimx-((Lower_WedgeDim1_x3-Lower_WedgeDim1_x1)/2. + Lower_WedgeDim1_x1);
	G4double Lower_WedgePos1_y = 0.0*m;
	G4double Lower_WedgePos1_z = ZdistanceofLower_Wedge + (Lower_WedgeDim1_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim1_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys1=0;
	Lower_Wedge_phys1 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos1_x,Lower_WedgePos1_y,Lower_WedgePos1_z),"Lower_Wedge1",Lower_Wedge_log1,this->PVWorld,false,0);


	  //   Lower_Wedge2 volumes
	G4double Lower_WedgeDim2_x1 = 10.15*mm;
	G4double Lower_WedgeDim2_x2 = Lower_WedgeDim2_x1;
	G4double Lower_WedgeDim2_x3 = 35.65*mm;
	G4double Lower_WedgeDim2_x4 = Lower_WedgeDim2_x3;
	G4double Lower_WedgeDim2_y1 = 150.*mm;
	G4double Lower_WedgeDim2_y2 = Lower_WedgeDim2_y1;
	G4double Lower_WedgeDim2_z = 2.8 / 2. *mm ;
	G4double Lower_WedgepTheta2 =  (90*degree) - (atan(Lower_WedgeDim2_z*2./(Lower_WedgeDim2_x3-Lower_WedgeDim2_x1))) ;
	G4Trap* Lower_Wedge_box2 = new  G4Trap( "Lower_Wedge_box2", Lower_WedgeDim2_z, Lower_WedgepTheta2, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim2_y1, Lower_WedgeDim2_x1, Lower_WedgeDim2_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim2_y2, Lower_WedgeDim2_x3, Lower_WedgeDim2_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log2 = new G4LogicalVolume(Lower_Wedge_box2,LowCarbon,"Lower_Wedge_log2",0,0,0);
	G4double Lower_WedgePos2_x = Standard_Dimx-((Lower_WedgeDim2_x3-Lower_WedgeDim2_x1)/2 + Lower_WedgeDim2_x1);
	G4double Lower_WedgePos2_y = 0.0*m;
	G4double Lower_WedgePos2_z = ZdistanceofLower_Wedge + (Lower_WedgeDim2_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim2_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys2=0;
	Lower_Wedge_phys2 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos2_x,Lower_WedgePos2_y,Lower_WedgePos2_z),"Lower_Wedge2",Lower_Wedge_log2,this->PVWorld,false,0);

	  //   Lower_Wedge3 volumes
	G4double Lower_WedgeDim3_x1 = 35.65*mm;
	G4double Lower_WedgeDim3_x2 = Lower_WedgeDim3_x1;
	G4double Lower_WedgeDim3_x3 = 60.*mm;
	G4double Lower_WedgeDim3_x4 = Lower_WedgeDim3_x3;
	G4double Lower_WedgeDim3_y1 = 150. *mm;
	G4double Lower_WedgeDim3_y2 = Lower_WedgeDim3_y1;
	G4double Lower_WedgeDim3_z = 3.4 / 2. *mm ;
	G4double Lower_WedgepTheta3 = (90*degree) - (atan(Lower_WedgeDim3_z*2./(Lower_WedgeDim3_x3-Lower_WedgeDim3_x1)))  ;
	G4Trap* Lower_Wedge_box3 = new  G4Trap( "Lower_Wedge_box3", Lower_WedgeDim3_z, Lower_WedgepTheta3, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim3_y1, Lower_WedgeDim3_x1, Lower_WedgeDim3_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim3_y2, Lower_WedgeDim3_x3, Lower_WedgeDim3_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log3 = new G4LogicalVolume(Lower_Wedge_box3,LowCarbon,"Lower_Wedge_log3",0,0,0);
	G4double Lower_WedgePos3_x = Standard_Dimx-((Lower_WedgeDim3_x3-Lower_WedgeDim3_x1)/2 + Lower_WedgeDim3_x1);
	G4double Lower_WedgePos3_y = 0.0*m;
	G4double Lower_WedgePos3_z = ZdistanceofLower_Wedge + (Lower_WedgeDim3_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim3_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys3=0;
	Lower_Wedge_phys3 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos3_x,Lower_WedgePos3_y,Lower_WedgePos3_z),"Lower_Wedge2",Lower_Wedge_log3,this->PVWorld,false,0);


	  //   Lower_Wedge4 volumes
	G4double Lower_WedgeDim4_x1 = 60.*mm;
	G4double Lower_WedgeDim4_x2 = Lower_WedgeDim4_x1;
	G4double Lower_WedgeDim4_x3 = 67.25*mm;
	G4double Lower_WedgeDim4_x4 = Lower_WedgeDim4_x3;
	G4double Lower_WedgeDim4_y1 = 150. *mm;
	G4double Lower_WedgeDim4_y2 = Lower_WedgeDim4_y1;
	G4double Lower_WedgeDim4_z = 1.2 / 2. *mm ;
	G4double Lower_WedgepTheta4 = (90*degree) - (atan(Lower_WedgeDim4_z*2./(Lower_WedgeDim4_x3-Lower_WedgeDim4_x1))) ;
	G4Trap* Lower_Wedge_box4 = new  G4Trap( "Lower_Wedge_box4", Lower_WedgeDim4_z, Lower_WedgepTheta4, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim4_y1, Lower_WedgeDim4_x1, Lower_WedgeDim4_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim4_y2, Lower_WedgeDim4_x3, Lower_WedgeDim4_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log4 = new G4LogicalVolume(Lower_Wedge_box4,LowCarbon,"Lower_Wedge_log4",0,0,0);
	G4double Lower_WedgePos4_x = Standard_Dimx-((Lower_WedgeDim4_x3-Lower_WedgeDim4_x1)/2 + Lower_WedgeDim4_x1);
	G4double Lower_WedgePos4_y = 0.0*m;
	G4double Lower_WedgePos4_z = ZdistanceofLower_Wedge + (Lower_WedgeDim4_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim4_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys4=0;
	Lower_Wedge_phys4 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos4_x,Lower_WedgePos4_y,Lower_WedgePos4_z),"Lower_Wedge4",Lower_Wedge_log4,this->PVWorld,false,0);


	 //   Lower_Wedge5 volumes
	G4double Lower_WedgeDim5_x1 = 67.25*mm;
	G4double Lower_WedgeDim5_x2 = Lower_WedgeDim5_x1;
	G4double Lower_WedgeDim5_x3 = 70.1 *mm;
	G4double Lower_WedgeDim5_x4 = Lower_WedgeDim5_x3;
	G4double Lower_WedgeDim5_y1 = 150. *mm;
	G4double Lower_WedgeDim5_y2 = Lower_WedgeDim5_y1;
	G4double Lower_WedgeDim5_z = 0.6 / 2. *mm ;
	G4double Lower_WedgepTheta5 = (90*degree) - (atan(Lower_WedgeDim5_z*2./(Lower_WedgeDim5_x3-Lower_WedgeDim5_x1))) ;
	G4Trap* Lower_Wedge_box5 = new  G4Trap( "Lower_Wedge_box5", Lower_WedgeDim5_z, Lower_WedgepTheta5, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim5_y1, Lower_WedgeDim5_x1, Lower_WedgeDim5_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim5_y2, Lower_WedgeDim5_x3, Lower_WedgeDim5_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log5 = new G4LogicalVolume(Lower_Wedge_box5,LowCarbon,"Lower_Wedge_log5",0,0,0);
	G4double Lower_WedgePos5_x = Standard_Dimx-((Lower_WedgeDim5_x3-Lower_WedgeDim5_x1)/2 + Lower_WedgeDim5_x1);
	G4double Lower_WedgePos5_y = 0.0*m;
	G4double Lower_WedgePos5_z = ZdistanceofLower_Wedge + (Lower_WedgeDim5_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim5_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys5=0;
	Lower_Wedge_phys5 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos5_x,Lower_WedgePos5_y,Lower_WedgePos5_z),"Lower_Wedge5",Lower_Wedge_log5,this->PVWorld,false,0);

	 //   Lower_Wedge6 volumes
	G4double Lower_WedgeDim6_x1 = 70.1 *mm;
	G4double Lower_WedgeDim6_x2 = Lower_WedgeDim6_x1;
	G4double Lower_WedgeDim6_x3 = 70.1*mm;
	G4double Lower_WedgeDim6_x4 = Lower_WedgeDim6_x3;
	G4double Lower_WedgeDim6_y1 = 150. *mm;
	G4double Lower_WedgeDim6_y2 = Lower_WedgeDim6_y1;
	G4double Lower_WedgeDim6_z = 2.8 / 2. *mm ;
	G4double Lower_WedgepTheta6 = 0.*mm ;
	G4Trap* Lower_Wedge_box6 = new  G4Trap( "Lower_Wedge_box6", Lower_WedgeDim6_z, Lower_WedgepTheta6, 0, 		// pName, pDz, pTheta, pPhi,
						 Lower_WedgeDim6_y1, Lower_WedgeDim6_x1, Lower_WedgeDim6_x2, 0,		// pDy1,  pDx1,  pDx2, pAlp1,
						 Lower_WedgeDim6_y2, Lower_WedgeDim6_x3, Lower_WedgeDim6_x4, 0); 	// pDy2,  pDx3,  pDx4, pAlp2

	G4LogicalVolume *Lower_Wedge_log6 = new G4LogicalVolume(Lower_Wedge_box6,LowCarbon,"Lower_Wedge_log6",0,0,0);
	G4double Lower_WedgePos6_x = 0.0*m;
	G4double Lower_WedgePos6_y = 0.0*m;
	G4double Lower_WedgePos6_z = ZdistanceofLower_Wedge + (Lower_WedgeDim6_z);
	ZdistanceofLower_Wedge += (Lower_WedgeDim6_z*2.);
	G4VPhysicalVolume *Lower_Wedge_phys6=0;
	Lower_Wedge_phys6 = new G4PVPlacement(0, G4ThreeVector(-Lower_WedgePos6_x,Lower_WedgePos6_y,Lower_WedgePos6_z),"Lower_Wedge6",Lower_Wedge_log6,this->PVWorld,false,0);



	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region("Lower_WedgeR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*mm);
	regVol->SetProductionCuts(cuts);
	Lower_Wedge_log1->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log1);
	Lower_Wedge_log2->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log2);
	Lower_Wedge_log3->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log3);
	Lower_Wedge_log4->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log4);
	Lower_Wedge_log5->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log5);
	Lower_Wedge_log6->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Lower_Wedge_log6);

	// Visualization attributes

	G4VisAttributes* simpleLowCarbonVisAtt;
	simpleLowCarbonVisAtt= new G4VisAttributes(G4Colour::Blue());
	simpleLowCarbonVisAtt->SetVisibility(true);
	simpleLowCarbonVisAtt->SetForceSolid(true);
	Lower_Wedge_log1->SetVisAttributes(simpleLowCarbonVisAtt);
	Lower_Wedge_log2->SetVisAttributes(simpleLowCarbonVisAtt);
	Lower_Wedge_log3->SetVisAttributes(simpleLowCarbonVisAtt);
	Lower_Wedge_log4->SetVisAttributes(simpleLowCarbonVisAtt);
	Lower_Wedge_log5->SetVisAttributes(simpleLowCarbonVisAtt);
	Lower_Wedge_log6->SetVisAttributes(simpleLowCarbonVisAtt);

	bCreated=true;
	return bCreated;
}


bool CML2Acc1::Reticle()
{
	bool bCreated=false;
	  //    materials

	G4Material *MYLAR=G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");

	  //   Reticle volumes

	G4double ZdistanceofReticle = 40.*cm;
	G4double ReticleDim_x = 30.*cm;
	G4double ReticleDim_y = 30.*cm;
	G4double ReticleDim_z = 0.2997 / 2. *cm ;
	G4Box* Reticle_box = new G4Box("Reticle_box",ReticleDim_x,ReticleDim_y,ReticleDim_z);
	G4LogicalVolume *Reticle_log = new G4LogicalVolume(Reticle_box,MYLAR,"Reticle_log",0,0,0);
	G4double ReticlePos_x = 0.0*m;
	G4double ReticlePos_y = 0.0*m;
	G4double ReticlePos_z = ZdistanceofReticle + (ReticleDim_z);
	G4VPhysicalVolume *Reticle_phys=0;
	Reticle_phys = new G4PVPlacement(0,
	G4ThreeVector(ReticlePos_x,ReticlePos_y,ReticlePos_z),
	"Reticle",Reticle_log,this->PVWorld,false,0);


	// Region for cuts
	G4Region *regVol;
	regVol= new G4Region("ReticleR");
	G4ProductionCuts* cuts = new G4ProductionCuts;
	cuts->SetProductionCut(0.1*mm);
	regVol->SetProductionCuts(cuts);
	Reticle_log->SetRegion(regVol);
	regVol->AddRootLogicalVolume(Reticle_log);


	// Visualization attributes

	G4VisAttributes* simpleMYLARSVisAtt;
	simpleMYLARSVisAtt= new G4VisAttributes(G4Colour::Blue());
	simpleMYLARSVisAtt->SetVisibility(true);
	// 	simpleLexanSVisAtt->SetForceSolid(true);
	Reticle_log->SetVisAttributes(simpleMYLARSVisAtt);
	bCreated=true;
	return bCreated;
}


