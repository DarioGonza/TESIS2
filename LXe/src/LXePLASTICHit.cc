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
// $Id: LXeScintHit.cc 72250 2013-07-12 08:59:26Z gcosmo $
//
/// \file optical/LXe/src/LXeScintHit.cc
/// \brief Implementation of the LXeScintHit class
//
//
#include "LXePLASTICHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"


G4ThreadLocal G4Allocator<LXePLASTICHit>* LXePLASTICHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICHit::LXePLASTICHit() : fEdepPL(0.), fPosPL(0.), fPhysVolPL(0), fparticlePL(0), fTime1(0) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICHit::LXePLASTICHit(G4VPhysicalVolume* pVol, G4ParticleDefinition* pPart, G4double time1) : fPhysVolPL(pVol), fparticlePL(pPart), fTime1(time1) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICHit::~LXePLASTICHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICHit::LXePLASTICHit(const LXePLASTICHit &right) : G4VHit()
{
  fEdepPL = right.fEdepPL;
  fPosPL = right.fPosPL;
  fPhysVolPL = right.fPhysVolPL;
  fparticlePL = right.fparticlePL;
  fTime1 = right.fTime1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const LXePLASTICHit& LXePLASTICHit::operator=(const LXePLASTICHit &right){
  fEdepPL = right.fEdepPL;
  fPosPL = right.fPosPL;
  fPhysVolPL = right.fPhysVolPL;
  fparticlePL = right.fparticlePL;
  fTime1 = right.fTime1;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int LXePLASTICHit::operator==(const LXePLASTICHit&) const{
  return false;
  //returns false because there currently isnt need to check for equality yet
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICHit::Draw() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICHit::Print() {}
