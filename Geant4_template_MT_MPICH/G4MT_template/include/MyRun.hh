/*
 * MyRun.hh
 *
 *  Created on: Nov 9, 2015
 *      Author: jason
 */

#ifndef MyRun_h
#define MyRun_h 1

#include "G4Run.hh"

class MyRun : public G4Run
{
 public:
  MyRun();
  virtual ~MyRun();
  virtual void Merge(const G4Run*);
 private:

};



#endif
