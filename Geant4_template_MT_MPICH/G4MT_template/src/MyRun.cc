/*
 * MyRun.cc
 *
 *  Created on: Nov 9, 2015
 *      Author: jason
 */
#

#include "G4SDManager.hh"
#include "MyRun.hh"


MyRun::MyRun()
{

}

MyRun::~MyRun(){

}

void MyRun::Merge(const G4Run* aRun)
{

  G4Run::Merge(aRun);
}
