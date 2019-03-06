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
// $Id: LXeScintHit.hh 72250 2013-07-12 08:59:26Z gcosmo $
//
/// \file optical/LXe/include/LXeScintHit.hh
/// \brief Definition of the LXeScintHit class
//
//
#ifndef LXePLASTICHit_h
#define LXePLASTICHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"

#include "tls.hh"

class LXePLASTICHit : public G4VHit
{
  public:
 
    LXePLASTICHit();
    LXePLASTICHit(G4VPhysicalVolume* pVol, G4ParticleDefinition* pPart, G4double t1);
    virtual ~LXePLASTICHit();
    LXePLASTICHit(const LXePLASTICHit &right);
    const LXePLASTICHit& operator=(const LXePLASTICHit &right);
    G4int operator==(const LXePLASTICHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetEdepPL(G4double dePL) { fEdepPL = dePL; }
    inline void AddEdepPL(G4double dePL) { fEdepPL += dePL; }
    inline G4double GetEdepPL() { return fEdepPL; }

    inline void SetPosPL(G4ThreeVector xyz) { fPosPL = xyz; }
    inline G4ThreeVector GetPosPL() { return fPosPL; }

    inline const G4VPhysicalVolume * GetPhysVPL() { return fPhysVolPL; }
    inline  G4ParticleDefinition * GetPartIdPL() const { return fparticlePL; }
    //G4double GetTime() const { return fTime; }
    
  private:
    G4double fEdepPL;
    G4ThreeVector fPosPL;
    const G4VPhysicalVolume* fPhysVolPL;
    G4ParticleDefinition* fparticlePL;
    G4double fTime1;

};

typedef G4THitsCollection<LXePLASTICHit> LXePlasticHitsCollection;

extern G4ThreadLocal G4Allocator<LXePLASTICHit>* LXePLASTICHitAllocator;

inline void* LXePLASTICHit::operator new(size_t)
{
  if(!LXePLASTICHitAllocator)
      LXePLASTICHitAllocator = new G4Allocator<LXePLASTICHit>;
  return (void *) LXePLASTICHitAllocator->MallocSingle();
}

inline void LXePLASTICHit::operator delete(void *aHit)
{
  LXePLASTICHitAllocator->FreeSingle((LXePLASTICHit*) aHit);
}

#endif
