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
// $Id: LXeScintSD.cc 68752 2013-04-05 10:23:47Z gcosmo $
//
/// \file optical/LXe/src/LXeScintSD.cc
/// \brief Implementation of the LXeScintSD class
//
//
#include "LXePLASTICSD.hh"
#include "LXePLASTICHit.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"

#include "B5Analysis.hh"
#include "G4ParticleTable.hh"



#include "G4ios.hh"
#include "G4ParticleTypes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICSD::LXePLASTICSD(G4String name)
  : G4VSensitiveDetector(name)
{
  fPlasticCollection = NULL;
  collectionName.insert("plasticCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePLASTICSD::~LXePLASTICSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICSD::Initialize(G4HCofThisEvent* hitsCE){
  fPlasticCollection = new LXePlasticHitsCollection
                      (SensitiveDetectorName,collectionName[0]);
  //A way to keep all the hits of this event in one place if needed
  static G4int hitspCID = -1;
  if(hitspCID<0){
    hitspCID = GetCollectionID(0);
  }
  hitsCE->AddHitsCollection( hitspCID, fPlasticCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool LXePLASTICSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ){
 
 auto analysisManager = G4AnalysisManager::Instance();
 G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return false; //No edep so dont count as hit

  //need to know if this is an optical photon
  if(aStep->GetTrack()->GetDefinition()
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

  G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable =
    (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  G4VPhysicalVolume* thePrePV = theTouchable->GetVolume();
  G4ParticleDefinition* partId = aStep->GetTrack()->GetDefinition();
  G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
  G4double time2= aStep->GetPostStepPoint()->GetGlobalTime();

  /////////////////////////////////////////////////////////////

    G4int gamma=1;
    G4int Posit1=2;
    G4int Elect1=3;
    G4int Muonp1=5;
    G4int Muonm1=6;
    G4int particleName;

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  
   G4ParticleDefinition* Gamma = particleTable->FindParticle("gamma");
   G4ParticleDefinition* Posit  = particleTable->FindParticle("e+");
   G4ParticleDefinition* Elect = particleTable->FindParticle("e-");
   G4ParticleDefinition* Muonp = particleTable->FindParticle("mu+");
   G4ParticleDefinition* Muonm = particleTable->FindParticle("mu-");


   //Given a number for each particle
  if ( partId == Gamma)
            {
              particleName = 1;//gamma
           // analysisManager->FillH1(2,gamma);
            }
          else if (  partId ==Posit )
            {                       //e+
              particleName = 2;
             // analysisManager->FillH1(3,Posit1);
            }
          else if (  partId == Elect)
            {                       //e-
              particleName = 3 ;
              //analysisManager->FillH1(4,Elect1);
            }
          else if (  partId == Muonp)
            {                       //mu+
              particleName = 5;
              //analysisManager->FillH1(5,Muonp1);
            }
          else if (  partId == Muonm)
            {                       //mu-
              particleName = 6;
             // analysisManager->FillH1(6,Muonm1);
            }

analysisManager->FillH1(7,particleName);

//G4String fPartId = particleTable->GetParticleName(parId);


  //Given a number for each particle
 /* if ( partId == Gamma)
            {
              particleName = 1;//gamma
            analysisManager->FillH1(2,gamma);
            }
          else if (  partId ==Posit )
            {                       //e+
              particleName = 2;
              analysisManager->FillH1(3,Posit1);
            }
          else if (  partId == Elect)
            {                       //e-
              particleName = 3 ;
              analysisManager->FillH1(4,Elect1);
            }
          else if (  partId == Muonp)
            {                       //mu+
              particleName = 5;
              analysisManager->FillH1(5,Muonp1);
            }
          else if (  partId == Muonm)
            {                       //mu-
              particleName = 6;
              analysisManager->FillH1(6,Muonm1);
            }
          
   // fill histograms
  analysisManager->FillH1(1,particleName);*/

  //Get the average position of the hit
  G4ThreeVector pos = thePrePoint->GetPosition() + thePostPoint->GetPosition();
  pos/=2.;

  LXePLASTICHit* plasticHit = new LXePLASTICHit(thePrePV,partId,time2);

  analysisManager->FillH1(6, time2);
  plasticHit->SetEdepPL(edep);
  plasticHit->SetPosPL(pos);

  fPlasticCollection->insert(plasticHit);

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICSD::EndOfEvent(G4HCofThisEvent* ) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICSD::clear() {} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICSD::DrawAll() {} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePLASTICSD::PrintAll() {} 
