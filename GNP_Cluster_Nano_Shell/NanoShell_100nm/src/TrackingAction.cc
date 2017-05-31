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
// 	Author: mchan
//

#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "G4TrackingManager.hh"
#include "G4Electron.hh"
TrackingAction::TrackingAction()
:G4UserTrackingAction()
{;}


void TrackingAction::PreUserTrackingAction(const G4Track* pretrack) {

//	if(pretrack->GetParentID()!= 0){  //secondary particle only
//	if(pretrack->GetDefinition()->GetParticleName() == "e-"){ //electron only
//    if(pretrack->GetLogicalVolumeAtVertex()->GetName()== "Gold"){
//	G4cout<<pretrack->GetLogicalVolumeAtVertex()->GetName()<<G4endl;
//	//G4cout<<"GetKinetic E  : "<< pretrack->GetStep()->GetTotalEnergyDeposit()<<G4endl;
//    		}
//		}
//	}
}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {


}


