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

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"

#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"

#include "SensitiveDetector.hh"
#include "SensitiveDetectorOnScint.hh"


#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"

#include "G4PVReplica.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "PolygonDataImport.hh"
#include "G4TessellatedSolid.hh"

//
#include <vector>
#include <iostream>
using namespace std;

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}

void DetectorConstruction::SetMaterial(){
	G4double a;  // atomic mass
	G4double z;  // atomic number
	G4double density;
	const double universe_mean_density = 1.e-25*g/cm3;

	fH = new G4Element("H", "H", z=1., a=1.01*g/mole);
	fC = new G4Element("C", "C", z=6., a=12.01*g/mole);
	fN = new G4Element("N", "N", z=7., a= 14.01*g/mole);
	fO = new G4Element("O"  , "O", z=8., a= 16.00*g/mole);

	//Gd2O3
	elGd = new G4Element("Gadolinium", "Gd", 64,157.25*g/mole);
	elO = new G4Element("Oxygen", "O", 8.0, 15.9*g/mole);
	fGd2O3 = new G4Material("Gd2O3", 7.07*g/cm3,2);
	fGd2O3->AddElement(elGd,2);
	fGd2O3->AddElement(elO,3);

	G4Element *elEu = new G4Element("Europium","Eu",63,151.964*g/mole);
	G4_Eu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Eu");

	fGd2O3_Eu = new G4Material("Gd2O3_Eu",7.62*g/cm3,2);
	fGd2O3_Eu->AddMaterial(fGd2O3, 99.0*perCent);
	fGd2O3_Eu->AddMaterial(G4_Eu,1.0*perCent);

	const G4int Gd2O3_Eu_BufferSize = 501;
	G4double Gd2O3_Eu_Energy[Gd2O3_Eu_BufferSize] = {2.482268e+00*eV,2.479790e+00*eV,2.477318e+00*eV,2.474851e+00*eV,2.472388e+00*eV,2.469930e+00*eV,2.467478e+00*eV,2.465030e+00*eV,2.462587e+00*eV,2.460149e+00*eV,2.457715e+00*eV,2.455287e+00*eV,2.452863e+00*eV,2.450444e+00*eV,2.448030e+00*eV,2.445620e+00*eV,2.443215e+00*eV,2.440815e+00*eV,2.438420e+00*eV,2.436029e+00*eV,2.433643e+00*eV,2.431262e+00*eV,2.428886e+00*eV,2.426514e+00*eV,2.424146e+00*eV,2.421784e+00*eV,2.419426e+00*eV,2.417072e+00*eV,2.414723e+00*eV,2.412379e+00*eV,2.410039e+00*eV,2.407703e+00*eV,2.405373e+00*eV,2.403046e+00*eV,2.400725e+00*eV,2.398407e+00*eV,2.396095e+00*eV,2.393786e+00*eV,2.391482e+00*eV,2.389183e+00*eV,2.386888e+00*eV,2.384597e+00*eV,2.382311e+00*eV,2.380029e+00*eV,2.377751e+00*eV,2.375478e+00*eV,2.373209e+00*eV,2.370945e+00*eV,2.368684e+00*eV,2.366429e+00*eV,2.364177e+00*eV,2.361930e+00*eV,2.359687e+00*eV,2.357448e+00*eV,2.355213e+00*eV,2.352983e+00*eV,2.350757e+00*eV,2.348535e+00*eV,2.346317e+00*eV,2.344104e+00*eV,2.341894e+00*eV,2.339689e+00*eV,2.337488e+00*eV,2.335291e+00*eV,2.333099e+00*eV,2.330910e+00*eV,2.328725e+00*eV,2.326545e+00*eV,2.324369e+00*eV,2.322196e+00*eV,2.320028e+00*eV,2.317864e+00*eV,2.315704e+00*eV,2.313547e+00*eV,2.311395e+00*eV,2.309247e+00*eV,2.307103e+00*eV,2.304963e+00*eV,2.302827e+00*eV,2.300694e+00*eV,2.298566e+00*eV,2.296442e+00*eV,2.294321e+00*eV,2.292205e+00*eV,2.290092e+00*eV,2.287983e+00*eV,2.285879e+00*eV,2.283778e+00*eV,2.281680e+00*eV,2.279587e+00*eV,2.277498e+00*eV,2.275412e+00*eV,2.273330e+00*eV,2.271252e+00*eV,2.269178e+00*eV,2.267108e+00*eV,2.265041e+00*eV,2.262978e+00*eV,2.260919e+00*eV,2.258864e+00*eV,2.256812e+00*eV,2.254764e+00*eV,2.252720e+00*eV,2.250679e+00*eV,2.248643e+00*eV,2.246609e+00*eV,2.244580e+00*eV,2.242554e+00*eV,2.240532e+00*eV,2.238514e+00*eV,2.236499e+00*eV,2.234487e+00*eV,2.232480e+00*eV,2.230476e+00*eV,2.228475e+00*eV,2.226478e+00*eV,2.224485e+00*eV,2.222496e+00*eV,2.220509e+00*eV,2.218527e+00*eV,2.216548e+00*eV,2.214572e+00*eV,2.212600e+00*eV,2.210632e+00*eV,2.208667e+00*eV,2.206705e+00*eV,2.204747e+00*eV,2.202793e+00*eV,2.200841e+00*eV,2.198894e+00*eV,2.196950e+00*eV,2.195009e+00*eV,2.193071e+00*eV,2.191138e+00*eV,2.189207e+00*eV,2.187280e+00*eV,2.185356e+00*eV,2.183436e+00*eV,2.181519e+00*eV,2.179605e+00*eV,2.177695e+00*eV,2.175788e+00*eV,2.173885e+00*eV,2.171984e+00*eV,2.170087e+00*eV,2.168194e+00*eV,2.166303e+00*eV,2.164416e+00*eV,2.162533e+00*eV,2.160652e+00*eV,2.158775e+00*eV,2.156901e+00*eV,2.155030e+00*eV,2.153163e+00*eV,2.151299e+00*eV,2.149438e+00*eV,2.147580e+00*eV,2.145725e+00*eV,2.143874e+00*eV,2.142026e+00*eV,2.140181e+00*eV,2.138339e+00*eV,2.136500e+00*eV,2.134665e+00*eV,2.132833e+00*eV,2.131003e+00*eV,2.129177e+00*eV,2.127354e+00*eV,2.125535e+00*eV,2.123718e+00*eV,2.121904e+00*eV,2.120094e+00*eV,2.118286e+00*eV,2.116482e+00*eV,2.114681e+00*eV,2.112883e+00*eV,2.111088e+00*eV,2.109295e+00*eV,2.107506e+00*eV,2.105720e+00*eV,2.103937e+00*eV,2.102157e+00*eV,2.100380e+00*eV,2.098606e+00*eV,2.096835e+00*eV,2.095067e+00*eV,2.093302e+00*eV,2.091540e+00*eV,2.089781e+00*eV,2.088025e+00*eV,2.086272e+00*eV,2.084522e+00*eV,2.082775e+00*eV,2.081030e+00*eV,2.079289e+00*eV,2.077550e+00*eV,2.075815e+00*eV,2.074082e+00*eV,2.072352e+00*eV,2.070625e+00*eV,2.068901e+00*eV,2.067180e+00*eV,2.065461e+00*eV,2.063746e+00*eV,2.062033e+00*eV,2.060323e+00*eV,2.058616e+00*eV,2.056912e+00*eV,2.055211e+00*eV,2.053512e+00*eV,2.051817e+00*eV,2.050124e+00*eV,2.048434e+00*eV,2.046746e+00*eV,2.045062e+00*eV,2.043380e+00*eV,2.041701e+00*eV,2.040025e+00*eV,2.038351e+00*eV,2.036680e+00*eV,2.035012e+00*eV,2.033347e+00*eV,2.031684e+00*eV,2.030025e+00*eV,2.028367e+00*eV,2.026713e+00*eV,2.025061e+00*eV,2.023412e+00*eV,2.021766e+00*eV,2.020122e+00*eV,2.018481e+00*eV,2.016843e+00*eV,2.015207e+00*eV,2.013574e+00*eV,2.011943e+00*eV,2.010316e+00*eV,2.008690e+00*eV,2.007068e+00*eV,2.005448e+00*eV,2.003831e+00*eV,2.002216e+00*eV,2.000604e+00*eV,1.998994e+00*eV,1.997387e+00*eV,1.995783e+00*eV,1.994181e+00*eV,1.992582e+00*eV,1.990986e+00*eV,1.989392e+00*eV,1.987800e+00*eV,1.986211e+00*eV,1.984625e+00*eV,1.983041e+00*eV,1.981459e+00*eV,1.979880e+00*eV,1.978304e+00*eV,1.976730e+00*eV,1.975159e+00*eV,1.973590e+00*eV,1.972024e+00*eV,1.970460e+00*eV,1.968899e+00*eV,1.967340e+00*eV,1.965783e+00*eV,1.964229e+00*eV,1.962678e+00*eV,1.961129e+00*eV,1.959582e+00*eV,1.958038e+00*eV,1.956496e+00*eV,1.954957e+00*eV,1.953420e+00*eV,1.951885e+00*eV,1.950353e+00*eV,1.948824e+00*eV,1.947296e+00*eV,1.945771e+00*eV,1.944249e+00*eV,1.942729e+00*eV,1.941211e+00*eV,1.939696e+00*eV,1.938183e+00*eV,1.936672e+00*eV,1.935164e+00*eV,1.933658e+00*eV,1.932154e+00*eV,1.930653e+00*eV,1.929154e+00*eV,1.927657e+00*eV,1.926163e+00*eV,1.924671e+00*eV,1.923181e+00*eV,1.921694e+00*eV,1.920209e+00*eV,1.918726e+00*eV,1.917245e+00*eV,1.915767e+00*eV,1.914291e+00*eV,1.912818e+00*eV,1.911346e+00*eV,1.909877e+00*eV,1.908410e+00*eV,1.906946e+00*eV,1.905483e+00*eV,1.904023e+00*eV,1.902565e+00*eV,1.901109e+00*eV,1.899656e+00*eV,1.898205e+00*eV,1.896756e+00*eV,1.895309e+00*eV,1.893864e+00*eV,1.892422e+00*eV,1.890982e+00*eV,1.889544e+00*eV,1.888108e+00*eV,1.886674e+00*eV,1.885243e+00*eV,1.883813e+00*eV,1.882386e+00*eV,1.880961e+00*eV,1.879539e+00*eV,1.878118e+00*eV,1.876699e+00*eV,1.875283e+00*eV,1.873869e+00*eV,1.872457e+00*eV,1.871047e+00*eV,1.869639e+00*eV,1.868233e+00*eV,1.866829e+00*eV,1.865428e+00*eV,1.864029e+00*eV,1.862631e+00*eV,1.861236e+00*eV,1.859843e+00*eV,1.858452e+00*eV,1.857063e+00*eV,1.855676e+00*eV,1.854291e+00*eV,1.852908e+00*eV,1.851528e+00*eV,1.850149e+00*eV,1.848772e+00*eV,1.847398e+00*eV,1.846025e+00*eV,1.844655e+00*eV,1.843286e+00*eV,1.841920e+00*eV,1.840556e+00*eV,1.839193e+00*eV,1.837833e+00*eV,1.836475e+00*eV,1.835118e+00*eV,1.833764e+00*eV,1.832412e+00*eV,1.831061e+00*eV,1.829713e+00*eV,1.828366e+00*eV,1.827022e+00*eV,1.825680e+00*eV,1.824339e+00*eV,1.823001e+00*eV,1.821664e+00*eV,1.820330e+00*eV,1.818997e+00*eV,1.817666e+00*eV,1.816338e+00*eV,1.815011e+00*eV,1.813686e+00*eV,1.812363e+00*eV,1.811042e+00*eV,1.809723e+00*eV,1.808406e+00*eV,1.807091e+00*eV,1.805778e+00*eV,1.804466e+00*eV,1.803157e+00*eV,1.801849e+00*eV,1.800543e+00*eV,1.799240e+00*eV,1.797938e+00*eV,1.796638e+00*eV,1.795340e+00*eV,1.794043e+00*eV,1.792749e+00*eV,1.791456e+00*eV,1.790166e+00*eV,1.788877e+00*eV,1.787590e+00*eV,1.786305e+00*eV,1.785022e+00*eV,1.783740e+00*eV,1.782461e+00*eV,1.781183e+00*eV,1.779907e+00*eV,1.778633e+00*eV,1.777361e+00*eV,1.776090e+00*eV,1.774821e+00*eV,1.773555e+00*eV,1.772290e+00*eV,1.771026e+00*eV,1.769765e+00*eV,1.768505e+00*eV,1.767248e+00*eV,1.765991e+00*eV,1.764737e+00*eV,1.763485e+00*eV,1.762234e+00*eV,1.760985e+00*eV,1.759738e+00*eV,1.758493e+00*eV,1.757249e+00*eV,1.756007e+00*eV,1.754767e+00*eV,1.753529e+00*eV,1.752292e+00*eV,1.751057e+00*eV,1.749824e+00*eV,1.748593e+00*eV,1.747363e+00*eV,1.746135e+00*eV,1.744909e+00*eV,1.743684e+00*eV,1.742461e+00*eV,1.741240e+00*eV,1.740021e+00*eV,1.738803e+00*eV,1.737587e+00*eV,1.736373e+00*eV,1.735161e+00*eV,1.733950e+00*eV,1.732741e+00*eV,1.731533e+00*eV,1.730327e+00*eV,1.729123e+00*eV,1.727921e+00*eV,1.726720e+00*eV,1.725521e+00*eV,1.724323e+00*eV,1.723128e+00*eV,1.721933e+00*eV,1.720741e+00*eV,1.719550e+00*eV,1.718361e+00*eV,1.717173e+00*eV,1.715988e+00*eV,1.714803e+00*eV,1.713621e+00*eV,1.712440e+00*eV,1.711260e+00*eV,1.710083e+00*eV,1.708906e+00*eV,1.707732e+00*eV,1.706559e+00*eV,1.705388e+00*eV,1.704218e+00*eV,1.703050e+00*eV,1.701884e+00*eV,1.700719e+00*eV,1.699555e+00*eV,1.698394e+00*eV,1.697234e+00*eV,1.696075e+00*eV,1.694918e+00*eV,1.693763e+00*eV,1.692609e+00*eV,1.691457e+00*eV,1.690306e+00*eV,1.689157e+00*eV,1.688010e+00*eV,1.686864e+00*eV,1.685719e+00*eV,1.684576e+00*eV,1.683435e+00*eV,1.682295e+00*eV,1.681157e+00*eV,1.680020e+00*eV,1.678885e+00*eV,1.677752e+00*eV,1.676619e+00*eV,1.675489e+00*eV,1.674360e+00*eV,1.673232e+00*eV,1.672106e+00*eV,1.670982e+00*eV,1.669859e+00*eV,1.668737e+00*eV,1.667617e+00*eV,1.666499e+00*eV,1.665382e+00*eV,1.664267e+00*eV,1.663153e+00*eV,1.662040e+00*eV,1.660929e+00*eV,1.659820e+00*eV,1.658712e+00*eV,1.657605e+00*eV,1.656500e+00*eV,1.655396e+00*eV};
	G4double Gd2O3_Eu_SCINT[Gd2O3_Eu_BufferSize] = {1.506301e-03,1.199413e-03,1.100149e-03,9.918746e-04,1.000897e-03,8.475301e-04,9.738303e-04,7.573271e-04,9.106780e-04,7.212489e-04,8.385093e-04,7.392878e-04,9.738303e-04,8.655717e-04,9.196992e-04,8.294885e-04,9.918746e-04,1.036987e-03,1.109173e-03,1.181364e-03,1.181364e-03,1.334791e-03,1.100149e-03,7.573271e-04,9.467643e-04,9.106780e-04,9.828525e-04,1.036987e-03,1.244536e-03,9.557860e-04,1.055033e-03,9.828525e-04,7.663470e-04,8.836138e-04,1.154291e-03,1.046010e-03,8.385093e-04,8.926350e-04,8.655717e-04,8.204682e-04,1.055033e-03,9.377426e-04,7.483072e-04,7.122294e-04,7.753669e-04,6.310594e-04,8.745930e-04,7.663470e-04,4.777590e-04,8.926350e-04,5.949861e-04,6.581150e-04,6.040042e-04,6.490965e-04,8.385093e-04,8.836138e-04,8.475301e-04,1.000897e-03,7.212489e-04,6.400775e-04,6.040042e-04,8.294885e-04,7.392878e-04,9.738303e-04,9.557860e-04,1.118196e-03,1.912647e-03,2.590320e-03,3.612365e-03,5.424294e-03,5.623840e-03,4.463493e-03,2.039105e-03,1.704935e-03,2.021038e-03,2.608399e-03,3.250439e-03,4.019715e-03,3.485673e-03,2.274005e-03,1.542413e-03,1.100149e-03,1.118196e-03,8.385093e-04,1.100149e-03,9.648082e-04,8.655717e-04,1.136243e-03,9.738303e-04,1.027965e-03,7.934072e-04,1.018942e-03,7.934072e-04,9.287209e-04,8.926350e-04,7.573271e-04,8.024275e-04,1.018942e-03,9.918746e-04,9.106780e-04,1.154291e-03,1.055033e-03,1.334791e-03,1.759116e-03,1.867487e-03,1.506301e-03,1.732025e-03,1.804269e-03,1.966841e-03,2.066205e-03,1.957808e-03,1.741055e-03,1.145267e-03,1.109173e-03,8.745930e-04,7.934072e-04,8.836138e-04,7.753669e-04,8.655717e-04,8.565509e-04,8.655717e-04,7.302683e-04,9.377426e-04,7.122294e-04,9.467643e-04,1.163316e-03,1.461163e-03,1.199413e-03,1.488246e-03,1.334791e-03,1.425055e-03,1.262586e-03,1.154291e-03,1.479218e-03,1.388948e-03,1.515329e-03,1.750085e-03,1.786207e-03,2.644557e-03,2.581281e-03,2.274005e-03,1.948775e-03,1.732025e-03,1.560469e-03,1.659787e-03,1.334791e-03,1.082102e-03,1.217462e-03,1.452136e-03,1.614641e-03,1.668816e-03,2.012005e-03,2.246898e-03,2.581281e-03,3.178072e-03,3.205209e-03,3.612365e-03,4.010660e-03,4.309503e-03,6.894771e-03,1.129395e-02,1.897994e-02,3.020762e-02,4.179648e-02,3.218791e-02,1.981867e-02,1.815121e-02,1.624813e-02,1.049989e-02,9.688336e-03,9.651879e-03,9.223629e-03,1.051814e-02,1.215272e-02,1.745201e-02,2.613021e-02,4.381204e-02,5.901013e-02,7.805349e-02,6.335475e-02,2.967593e-02,2.004001e-02,2.245993e-02,2.853901e-02,3.847544e-02,5.220616e-02,6.741844e-02,7.615817e-02,8.033685e-02,6.122817e-02,3.898412e-02,2.793387e-02,2.392250e-02,2.558241e-02,2.514626e-02,2.535967e-02,2.824104e-02,3.397582e-02,4.476935e-02,5.088768e-02,5.677818e-02,5.083040e-02,3.962509e-02,3.151487e-02,2.451563e-02,2.059360e-02,1.999389e-02,1.956973e-02,2.097209e-02,2.137845e-02,2.074128e-02,2.159094e-02,2.207155e-02,2.484016e-02,2.904206e-02,3.299250e-02,4.188155e-02,5.300008e-02,7.505022e-02,1.015688e-01,1.747851e-01,2.811558e-01,4.452045e-01,6.466999e-01,8.554601e-01,1,8.776785e-01,5.494711e-01,3.932345e-01,3.626295e-01,3.511168e-01,3.175459e-01,2.542932e-01,1.780694e-01,1.220276e-01,8.875959e-02,6.803098e-02,5.320106e-02,4.273273e-02,3.577671e-02,3.158962e-02,2.840864e-02,2.620452e-02,2.598162e-02,2.600948e-02,2.720825e-02,3.017030e-02,3.385402e-02,3.837185e-02,4.121063e-02,4.225976e-02,4.318702e-02,4.527211e-02,4.694364e-02,5.001929e-02,5.276087e-02,5.743181e-02,6.507893e-02,7.314135e-02,8.448450e-02,9.539324e-02,1.042015e-01,1.059404e-01,9.411284e-02,6.105439e-02,3.620871e-02,2.163714e-02,1.645938e-02,1.331433e-02,1.136701e-02,1.133961e-02,1.038130e-02,9.870641e-03,9.232739e-03,9.005031e-03,8.677238e-03,8.085704e-03,7.149182e-03,7.340041e-03,6.922025e-03,7.031053e-03,7.003795e-03,7.194621e-03,6.994709e-03,6.613188e-03,6.649516e-03,6.295383e-03,5.877876e-03,5.596627e-03,5.152260e-03,4.934695e-03,5.007210e-03,4.880312e-03,4.807808e-03,4.508790e-03,4.137429e-03,4.110263e-03,4.273274e-03,4.961887e-03,5.052536e-03,5.778067e-03,8.222176e-03,1.155880e-02,1.630323e-02,2.168335e-02,2.480307e-02,1.799476e-02,1.228070e-02,1.135787e-02,1.295745e-02,1.070975e-02,7.212797e-03,5.179459e-03,5.143193e-03,4.590330e-03,5.360811e-03,6.704011e-03,7.376400e-03,6.931110e-03,5.315470e-03,3.956336e-03,4.409141e-03,6.277226e-03,8.568001e-03,1.208874e-02,1.512845e-02,1.503673e-02,9.396726e-03,6.204603e-03,4.961887e-03,3.929175e-03,2.988139e-03,3.530918e-03,3.187118e-03,3.259485e-03,3.413287e-03,3.223301e-03,3.892963e-03,3.150936e-03,2.834414e-03,3.006226e-03,2.644557e-03,2.961009e-03,2.554164e-03,2.436667e-03,2.255934e-03,2.319186e-03,2.319186e-03,2.436667e-03,2.409554e-03,2.644557e-03,2.508971e-03,2.355332e-03,2.481856e-03,2.355332e-03,2.427629e-03,2.246898e-03,2.201721e-03,2.183651e-03,2.427629e-03,2.219792e-03,2.400517e-03,2.391480e-03,2.445705e-03,2.436667e-03,2.518009e-03,2.915794e-03,2.545125e-03,2.825373e-03,2.834414e-03,2.870582e-03,3.169027e-03,3.521869e-03,4.327619e-03,5.188526e-03,7.285505e-03,9.660993e-03,1.148573e-02,1.096529e-02,8.859330e-03,5.587556e-03,4.028769e-03,3.313765e-03,3.141891e-03,3.313765e-03,4.037823e-03,4.907503e-03,6.131986e-03,8.285870e-03,9.014139e-03,7.440031e-03,4.173652e-03,2.545125e-03,2.237863e-03,2.283042e-03,1.822331e-03,2.147512e-03,2.183651e-03,2.084273e-03,1.966841e-03,2.328223e-03,2.111375e-03,1.912647e-03,2.183651e-03,2.319186e-03,2.463780e-03,2.508971e-03,2.617438e-03,3.060489e-03,3.757178e-03,5.170393e-03,5.932322e-03,8.977711e-03,1.171409e-02,1.665230e-02,2.039057e-02,2.678059e-02,2.528543e-02,2.160942e-02,2.167411e-02,2.349644e-02,1.669824e-02,1.093790e-02,1.120264e-02,1.540364e-02,1.940381e-02,1.843657e-02,1.196079e-02,5.279198e-03,2.807289e-03,2.319186e-03,1.903615e-03,1.677846e-03,1.704935e-03,1.434082e-03,1.352843e-03,1.461163e-03,1.370896e-03,1.551441e-03,1.208437e-03,1.145267e-03,1.479218e-03,1.199413e-03,1.316739e-03,1.091125e-03,1.334791e-03,1.199413e-03,1.298688e-03,1.289662e-03,9.738303e-04,1.298688e-03,1.163316e-03,1.127220e-03,1.100149e-03,1.136243e-03,1.073079e-03,1.163316e-03,1.073079e-03,1.036987e-03,1.145267e-03,1.136243e-03,1.181364e-03,9.738303e-04,1.055033e-03,1.027965e-03,1.100149e-03,1.009919e-03,1.181364e-03,9.557860e-04,8.385093e-04,1.082102e-03,1.127220e-03,9.738303e-04,1.109173e-03,9.738303e-04,1.009919e-03,7.753669e-04,7.212489e-04,9.467643e-04,9.016563e-04,1.000897e-03,9.287209e-04,1.073079e-03,1.000897e-03,1.064056e-03,9.467643e-04,1.036987e-03,1.316739e-03,1.316739e-03,1.416028e-03,1.533385e-03,1.199413e-03,1.163316e-03,1.027965e-03,9.918746e-04,9.106780e-04,8.475301e-04,9.016563e-04,7.934072e-04,8.475301e-04,9.648082e-04};
	G4double Gd2O3_Eu_RIND[Gd2O3_Eu_BufferSize]  = {2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00,2.200000e+00};
	G4double Gd2O3_Eu_ABSL[Gd2O3_Eu_BufferSize]  = {1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m,1*m};

	fGd2O3_Eu_mt= new G4MaterialPropertiesTable();
	fGd2O3_Eu_mt->AddProperty("FASTCOMPONENT", Gd2O3_Eu_Energy, Gd2O3_Eu_SCINT, Gd2O3_Eu_BufferSize);
	fGd2O3_Eu_mt->AddProperty("SLOWCOMPONENT", Gd2O3_Eu_Energy, Gd2O3_Eu_SCINT, Gd2O3_Eu_BufferSize);
	fGd2O3_Eu_mt->AddProperty("RINDEX",        Gd2O3_Eu_Energy, Gd2O3_Eu_RIND,  Gd2O3_Eu_BufferSize);
	fGd2O3_Eu_mt->AddProperty("ABSLENGTH",     Gd2O3_Eu_Energy, Gd2O3_Eu_ABSL,  Gd2O3_Eu_BufferSize);
	//fLXe_mt->AddConstProperty("SCINTILLATIONYIELD",12000./MeV);
	fGd2O3_Eu_mt->AddConstProperty("SCINTILLATIONYIELD",1200./MeV);
	fGd2O3_Eu_mt->AddConstProperty("RESOLUTIONSCALE",1.0);
	fGd2O3_Eu_mt->AddConstProperty("FASTTIMECONSTANT",0.5*ms);
	fGd2O3_Eu_mt->AddConstProperty("SLOWTIMECONSTANT",3.*ms);
	fGd2O3_Eu_mt->AddConstProperty("YIELDRATIO",1.0);
	fGd2O3_Eu->SetMaterialPropertiesTable(fGd2O3_Eu_mt);

	fGd2O3_Eu->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

	//Air
	fAir = new G4Material("Air", density= 1.29*mg/cm3, 2);
	fAir->AddElement(fN, 70*perCent);
	fAir->AddElement(fO, 30*perCent);

	//Vacuum
	fVacuum = new G4Material("Vacuum",z=1.,a=1.01*g/mole,
			density=universe_mean_density,kStateGas,0.1*kelvin,
			1.e-19*pascal);

	const G4int lxenum = 3;
	G4double vacuum_Energy[lxenum]={2.0*eV,7.0*eV,7.14*eV};
	G4double vacuum_RIND[lxenum]={1.,1.,1.};
	vacuum_mt = new G4MaterialPropertiesTable();
	vacuum_mt->AddProperty("RINDEX", vacuum_Energy, vacuum_RIND,lxenum);
	fVacuum->SetMaterialPropertiesTable(vacuum_mt);
	fAir->SetMaterialPropertiesTable(vacuum_mt);//Give air the same rindex


	G4_Pb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
	fPb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
	const G4int PbNum = 2;
	G4double Pb_Energy[PbNum] = {0*eV,10*eV};
	G4double Pb_RIND[PbNum] ={0.,0.};
	G4double Pb_ABS[PbNum] = {0.01*mm,0.01*mm};
	G4_Pb_mt = new G4MaterialPropertiesTable();
	G4_Pb_mt->AddProperty("RINDEX",Pb_Energy,Pb_RIND,PbNum);
	G4_Pb_mt->AddProperty("ABSLENGTH",Pb_Energy,Pb_ABS,PbNum);
	G4_Pb->SetMaterialPropertiesTable(G4_Pb_mt);


	//Fiducial marker
	G4double iz = 0;
	G4double ia = 0;
	G4double am = 0;
	G4Isotope *Zinc68_iso = new G4Isotope("ZINC68_iso",iz=30,ia=68,am=67.9*g/mole);
	G4Element *Zinc68_ele = new G4Element("ZINC68_ele","Zn68",1);
	Zinc68_ele->AddIsotope(Zinc68_iso,100.0*perCent);
	Zinc68_mat = new G4Material("Zinc68_mat",7.14*g/cm3,1,kStateSolid);
	Zinc68_mat->AddElement(Zinc68_ele,1);




}

void DetectorConstruction::SetSurfaceProperty(){

	// Surface
	G4double Energies[2] = {.1*eV, 10.*eV};

	// Cathode surface For Absorption.
	CathodeSurface = new G4OpticalSurface("CathodeSurface", unified);
	CathodeSurface->SetType(dielectric_metal);
	CathodeSurface->SetModel(unified);
	CathodeSurface->SetFinish(ground);
	CathodeSurface->SetSigmaAlpha(0.);
	G4MaterialPropertiesTable* CathodeSurface_Prop = new G4MaterialPropertiesTable();
	G4double CathodeSurface_Reflectivity[2] = {0., 0.};
	G4double CathodeSurface_Efficiency[2] = {0., 0.};
	CathodeSurface_Prop->AddProperty("REFLECTIVITY", Energies, CathodeSurface_Reflectivity, 2);
	CathodeSurface_Prop->AddProperty("EFFICIENCY", Energies, CathodeSurface_Efficiency, 2);
	CathodeSurface->SetMaterialPropertiesTable(CathodeSurface_Prop);





}

void DetectorConstruction::SetDimension(){

	WorldX = WorldY = WorldZ = 3.0*m;

	ScintX = 52*mm;
	ScintY = 52*mm;
	ScintZ = 1*mm;

	NumOfReplica = 16;

	SolidWaterX = 100*cm;
	SolidWaterY = 20*cm;
	SolidWaterZ = 30*cm;

	GammaCameraMotherX = 20*cm;
	GammaCameraMotherY = 20*cm;
	GammaCameraMotherZ = 20*cm;

	OpDetectorX = 52*mm;
	OpDetectorY = 52*mm;
	OpDetectorZ = 100*mm;

	CollimatorHeight = 20*mm;

	NumOfWaterPhantom =0;


}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	SetMaterial();
	SetDimension();

	// 1st position (with first G4PVPlacement constructor)
	// direction of rotation is un-clock-wise.
	//G4double thetaX = 45*deg;
	G4double thetaX = 0*deg;
	G4double thetaY = 0*deg;
	G4double thetaZ = 0*deg;
	G4RotationMatrix *rotM = new G4RotationMatrix();
	rotM->rotateX(thetaX);

	//G4double thetaXG2 = (45+90)*deg;
	G4double thetaXG2 = (0+180)*deg;
	G4double thetaYG2 = 0*deg;
	G4double thetaZG2 = 0*deg;
	G4RotationMatrix *rotMG2 = new G4RotationMatrix();
	rotMG2->rotateX(thetaXG2);

	//Patient to GammaCamera Distance P2D
	G4double P2D = 20*cm;
	G4double DistanceForP2D = P2D/sqrt(2);



	// World
	G4VSolid* sol_World = new G4Box("World", WorldX*0.5, WorldY*0.5, WorldZ*0.5);
	G4Material* AIR = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	G4LogicalVolume* lv_World = new G4LogicalVolume(sol_World, AIR, "World");
	G4VPhysicalVolume* pv_World =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_World, "World", 0, false, 0);


	//GammaCameraMother
	G4VSolid* sol_GammaCameraMother = new G4Box("GammaCameraMother", GammaCameraMotherX*0.5, GammaCameraMotherY*0.5, GammaCameraMotherZ*0.5);
	G4LogicalVolume* lv_GammaCameraMother= new G4LogicalVolume(sol_GammaCameraMother, AIR, "GammaCameraMother");
//	G4VPhysicalVolume* pv_GammaCameraMother =
//			new G4PVPlacement(rotM, G4ThreeVector(0.0, DistanceForP2D, DistanceForP2D), lv_GammaCameraMother, "GammaCameraMother", lv_World, false, 10);

	G4VPhysicalVolume* pv_GammaCameraMother =
				new G4PVPlacement(rotM, G4ThreeVector(0.0, 0.0, DistanceForP2D), lv_GammaCameraMother, "GammaCameraMother", lv_World, false, 10);

	G4VPhysicalVolume* pv_GammaCameraMother2 =
			new G4PVPlacement(rotMG2, G4ThreeVector(0.0, 0.0, -DistanceForP2D), lv_GammaCameraMother, "GammaCameraMother", lv_World, false, 11);


	// User geometry
	//Scinillator
	G4VSolid* sol_Scint = new G4Box("Scint", ScintX*0.5,ScintY*0.5,ScintZ*0.5);
	G4LogicalVolume* lv_Scint = new G4LogicalVolume(sol_Scint, fGd2O3_Eu, "Scint");
	G4VPhysicalVolume* pv_Scint =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_Scint, "Scint", lv_GammaCameraMother, false, 10);



	//PMT - Optical Detector
	G4VSolid *sol_OpDetector = new G4Box("OpDetector",OpDetectorX*0.5,OpDetectorY*0.5,OpDetectorZ*0.5);
	G4LogicalVolume* lv_OpDetector = new G4LogicalVolume(sol_OpDetector,G4_Pb,"OpDetector");
	G4VPhysicalVolume* pv_OpDetector =
			new G4PVPlacement(0,G4ThreeVector(0.0,0.0,(ScintZ*0.5+OpDetectorZ*0.5)),lv_OpDetector,"OpDetector",lv_GammaCameraMother,false,100);

	G4VSolid *sol_RepX = new G4Box("RepX",0.5*(OpDetectorX/NumOfReplica),0.5*OpDetectorY,0.5*OpDetectorZ);
	G4LogicalVolume *lv_RepX = new G4LogicalVolume(sol_RepX,G4_Pb,"RepX");
	G4VPhysicalVolume *pv_RepX = new G4PVReplica("RepX",lv_RepX,lv_OpDetector,kXAxis,NumOfReplica,OpDetectorX/NumOfReplica);

	G4VSolid *sol_RepY = new G4Box("RepY",0.5*(OpDetectorX/NumOfReplica),0.5*(OpDetectorY/NumOfReplica),0.5*OpDetectorZ);
	G4LogicalVolume *lv_RepY = new G4LogicalVolume(sol_RepY,G4_Pb,"RepY");
	G4VPhysicalVolume *pv_RepY = new G4PVReplica("RepY",lv_RepY,lv_RepX,kYAxis,NumOfReplica,OpDetectorY/NumOfReplica);





	//Collimator
	PolygonDataImport* polyData = new PolygonDataImport("./polygon/bee_20.ply");
	G4int numFacet = polyData->GetNumFacet();

	G4TessellatedSolid* sol_poly= new G4TessellatedSolid("HexagonalCollimator");
	for(G4int i=0;i<numFacet;i++){
		sol_poly->AddFacet(polyData->GetFacet(i));
	}
	sol_poly->SetSolidClosed(true);

	G4LogicalVolume* lv_poly= new G4LogicalVolume(sol_poly,fPb,"HexagonalCollimator");

	G4VPhysicalVolume* pv_poly =
			new G4PVPlacement(0,G4ThreeVector(-OpDetectorX/2,-OpDetectorY/2,-(CollimatorHeight+ScintZ/2) ),lv_poly,"HexagonalCollimator",lv_GammaCameraMother,false,110);



	//WATER BOX
	G4Material* WATER = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
	G4VSolid* sol_WaterPhantom = new G4Box("WaterPhantom",0.5*SolidWaterX,0.5*SolidWaterY,0.5*SolidWaterZ);
	G4LogicalVolume* lv_WaterPhantom = new G4LogicalVolume(sol_WaterPhantom, WATER, "WaterPhantom");
	//G4VPhysicalVolume *pv_WaterPhantom = new G4PVPlacement(0,G4ThreeVector(0.0,0.0,0.0
	//		),lv_WaterPhantom,"WaterPhantom",lv_World,false,1000);



	// Fiducial marker

	G4VSolid *sol_FiducialMarker = new G4Sphere("FiducialMarker",0.0*mm,1.0*mm,0.0*deg,360*deg,
			0.0*deg,360*deg);
	G4LogicalVolume* lv_FiducialMarker = new G4LogicalVolume(sol_FiducialMarker, Zinc68_mat, "FiducialMarker");
	G4VPhysicalVolume* pv_FiducialMarker =
			new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0), lv_FiducialMarker, "FiducialMarker", lv_World, false, 50);





	// Visualization
	G4VisAttributes* va_World = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_World->SetForceWireframe(true);
	lv_World->SetVisAttributes(va_World);

	G4VisAttributes* va_GammaCameraMother = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_GammaCameraMother->SetForceWireframe(true);
	lv_GammaCameraMother->SetVisAttributes(va_GammaCameraMother);


	G4VisAttributes* va_Scint = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
	va_Scint->SetForceWireframe(true);
	lv_Scint->SetVisAttributes(va_Scint);

	G4VisAttributes* va_WaterPhantom = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0,0.3));
	//va_WaterPhantom->SetForceWireframe(true);
	va_WaterPhantom->SetForceSolid(true);
	lv_WaterPhantom->SetVisAttributes(va_WaterPhantom);
	lv_WaterPhantom->SetVisAttributes(va_WaterPhantom);

	G4VisAttributes* va_Poly = new G4VisAttributes(G4Colour(0,1,0));
	va_Poly->SetForceSolid(true);
	lv_poly->SetVisAttributes(va_Poly);

	SetSurfaceProperty();

	new G4LogicalBorderSurface("CathodeSurface",
			pv_Scint, pv_OpDetector, CathodeSurface);
	new G4LogicalBorderSurface("CathodeSurface",
			pv_Scint, pv_poly, CathodeSurface);



	return pv_World;
}

void DetectorConstruction::CalRotationMatrix()
{



}

void DetectorConstruction::ConstructSDandField()
{
	// Set sensitive detector on "Geom"
	SetSensitiveDetector("RepY", new SensitiveDetector("OpDetector"));
	SetSensitiveDetector("Scint", new SensitiveDetectorOnScint("Scint"));
}
