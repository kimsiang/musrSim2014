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
////////////////////////////////////////////////////////////////////////
// Reflection of Atoms Process Class Implementation
////////////////////////////////////////////////////////////////////////
//
// File:        Adapted from G4OpBoundaryProcess.cc
// Description: Discrete Process -- reflection of atoms at
//                                  interfaces
// Version:     1.1
// Created:     2011-09-07
// Modified:    
// Author:      Paolo Crivelli
// 	
// mail:        paolo.crivelli@cern.ch
//
////////////////////////////////////////////////////////////////////////

#include "G4ios.hh"
#include "G4MuReflection.hh"

/////////////////////////
// Class Implementation
/////////////////////////

//////////////
// Operators
//////////////

// G4MuReflection::operator=(const G4MuReflection &right)
// {
// }

/////////////////
// Constructors
/////////////////


G4MuReflection::G4MuReflection(const G4String& processName,
        G4ProcessType type)
: G4VDiscreteProcess(processName, type)
{
    if ( verboseLevel > 0) {
        G4cout << GetProcessName() << " is created " << G4endl;
    }

    theStatus = Undefined;
    theModel = glisur;
    theFinish = polished;
    theReflectivity = 1.;
    theEfficiency   = 0.;

    prob_sl = 0.;
    prob_ss = 0.;
    prob_bs = 0.;

}


// G4MuReflection::G4MuReflection(const G4MuReflection &right)
// {
// }

////////////////
// Destructors
////////////////

G4MuReflection::~G4MuReflection(){}

////////////
// Methods
////////////

// PostStepDoIt
// ------------
//
    G4VParticleChange*
G4MuReflection::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
    theStatus = Undefined;

    aParticleChange.Initialize(aTrack);

    G4StepPoint* pPreStepPoint  = aStep.GetPreStepPoint();
    G4StepPoint* pPostStepPoint = aStep.GetPostStepPoint();

    if (pPostStepPoint->GetStepStatus() != fGeomBoundary){
        theStatus = NotAtBoundary;
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    //Define this process only if the Mu is inside the BeamPipe
    if (pPreStepPoint  -> GetMaterial()->GetName()!="G4_Galactic"){
        //if (pPostStepPoint  -> GetMaterial()->GetName()="Vacuum"){
        theStatus = NotInBeamPipe;	
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }

    if (pPreStepPoint  -> GetMaterial()->GetName()=="G4_Galactic" && pPostStepPoint  -> GetMaterial()->GetName()=="G4_Galactic"){
        //if (pPostStepPoint  -> GetMaterial()->GetName()="Vacuum"){
        theStatus =InVacuum;	
        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }
    // 	if (aTrack.GetVolume()->GetName()!="Laser"){
    // 	  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    // 	}
    G4String PartName = aTrack.GetDefinition()->GetParticleName();
    //	if (pPreStepPoint  -> GetMaterial()->GetName()=="Vacuum" && pPostStepPoint  -> GetMaterial()->GetName()=="Vacuum"  && PartName=="excitedpositronium"){
    // 	if (aTrack.GetVolume()->GetName() =="world" && aTrack.GetNextVolume()->GetName()=="Laser" && PartName=="excitedpositronium"){
    // 	  G4cout<<"Excited ops  "<<G4endl;

    // 	  G4cout<<pPreStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<pPostStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetVolume()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetNextVolume()->GetName()<<G4endl;
    // 	  getchar();
    // 	  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    // 	}

    // 	if (pPreStepPoint  -> GetMaterial()->GetName()!="Laser"){
    // 	//if (aTrack.GetNextVolume()->GetName()!="VacuumInPipe"){
    // 	  theStatus = NotInBeamPipe;
    // 	  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    // 	}

    //	if (aTrack.GetStepLength()<=kCarTolerance/2){
    //	        theStatus = StepTooSmall;
    //	        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    //	}

    Material1 = pPreStepPoint  -> GetMaterial();
    Material2 = pPostStepPoint -> GetMaterial();


    // 	if(PartName == "positronium"){
    // 	  G4cout<<"Reflection of ops  "<<G4endl;
    // 	  G4cout<<pPreStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<pPostStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetVolume()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetNextVolume()->GetName()<<G4endl;
    // 	  getchar();
    // 	}
    // 	if(PartName == "excitedpositronium"){
    // 	  G4cout<<"Reflection of excited ops  "<<G4endl;
    // 	  G4cout<<pPreStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<pPostStepPoint  -> GetMaterial()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetVolume()->GetName()<<G4endl;
    // 	  G4cout<<aTrack.GetNextVolume()->GetName()<<G4endl;
    // 	  //G4cout<<"Material1 "<<Material1<<G4endl;
    // 	  //G4cout<<"Material2 "<<Material2<<G4endl;
    // 	  getchar();
    // 	}
    const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();

    theMuMomentum = aParticle->GetTotalMomentum();
    OldMomentum       = aParticle->GetMomentumDirection();
    KinEnergy       = aParticle->GetKineticEnergy();


    G4LogicalSurface* Surface = G4LogicalBorderSurface::GetSurface
        (pPreStepPoint ->GetPhysicalVolume(),
         pPostStepPoint->GetPhysicalVolume());

    if (Surface == NULL){
        G4bool enteredDaughter=(pPostStepPoint->GetPhysicalVolume()
                ->GetMotherLogical() == 
                pPreStepPoint->GetPhysicalVolume()
                ->GetLogicalVolume());
        if(enteredDaughter){
            Surface = G4LogicalSkinSurface::GetSurface
                (pPostStepPoint->GetPhysicalVolume()->
                 GetLogicalVolume());
            if(Surface == NULL)
                Surface = G4LogicalSkinSurface::GetSurface
                    (pPreStepPoint->GetPhysicalVolume()->
                     GetLogicalVolume());
        }
        else{
            Surface = G4LogicalSkinSurface::GetSurface
                (pPreStepPoint->GetPhysicalVolume()->
                 GetLogicalVolume());
            if(Surface == NULL)
                Surface = G4LogicalSkinSurface::GetSurface
                    (pPostStepPoint->GetPhysicalVolume()->
                     GetLogicalVolume());
        }
    }

    //	if (Surface) OpticalSurface = dynamic_cast <G4OpticalSurface*> (Surface->GetSurfaceProperty());

    if ( verboseLevel > 0 ) {
        G4cout << " Muonium at Boundary! " << G4endl;
        G4cout << " Old Momentum Direction: " << OldMomentum     << G4endl;
        G4cout << " Old Polarization:       " << OldPolarization << G4endl;
    }

    G4ThreeVector theGlobalPoint = pPostStepPoint->GetPosition();

    G4Navigator* theNavigator =
        G4TransportationManager::GetTransportationManager()->
        GetNavigatorForTracking();

    G4ThreeVector theLocalPoint = theNavigator->
        GetGlobalToLocalTransform().
        TransformPoint(theGlobalPoint);

    G4ThreeVector theLocalNormal;	// Normal points back into volume

    G4bool valid;
    theLocalNormal = theNavigator->GetLocalExitNormal(&valid);

    if (valid) {
        theLocalNormal = -theLocalNormal;
    }
    else {
        G4cerr << " G4MuReflection/PostStepDoIt(): "
            << " The Navigator reports that it returned an invalid normal" 
                 << G4endl;
    }

    theGlobalNormal = theNavigator->GetLocalToGlobalTransform().
        TransformAxis(theLocalNormal);
    if (OldMomentum * theGlobalNormal > 0.0) {
#ifdef G4DEBUG_OPTICAL
        G4cerr << " G4MuReflection/PostStepDoIt(): "
            << " theGlobalNormal points the wrong direction "
                 << G4endl;
#endif
        theGlobalNormal = -theGlobalNormal;
    }

    //G4cout << " theGlobalPoint: " <<theGlobalPoint<< G4endl;
    //	G4cout << " theLocalPoint:  " <<theLocalPoint<< G4endl;
    //	G4cout << "theLocalNormal : " << theLocalNormal << G4endl;
    //	G4cout << "theGlobalNormal :" << theGlobalNormal << G4endl;





    //  if ( verboseLevel > 0) {
    //	G4cout << " New Momentum Direction: " << NewMomentum     << G4endl;
    //	G4cout << " New Polarization:       " << NewPolarization << G4endl;
    //getchar();
    //	}


    // switch to other type of reflection by commenting out

    // Specular reflection
    /*       if(KinEnergy<0.01*keV){
             aParticleChange.ProposeMomentumDirection(OldMomentum-2*OldMomentum.dot(theGlobalNormal)*theGlobalNormal);
             }
             */

    // Diffuse reflection
    if(KinEnergy<1*keV){
        DoReflection();
        NewMomentum = NewMomentum.unit();
        NewPolarization = NewPolarization.unit();
        aParticleChange.ProposeMomentumDirection(NewMomentum);}

        return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    }



    // GetMeanFreePath
    // ---------------
    //
    G4double G4MuReflection::GetMeanFreePath(const G4Track& aTrack ,
            G4double ,
            G4ForceCondition* condition)
    {
        //  G4VPhysicalVolume* aVolume = aTrack.GetNextVolume();
        //  //G4Material *aMaterial= aTrack.GetMaterial();

        //  G4double SIGMA;
        //  if (pPreStepPoint  -> GetMaterial()->GetName()!="Vacuum"){
        //  if(aVolume->GetName()=="Laser"){
        //    SIGMA=0.;
        //  }
        //  }
        //   else{
        //     *condition = Forced;

        //     SIGMA=DBL_MAX;
        //   }


        //  MeanFreePath = SIGMA > DBL_MIN ? 1./SIGMA : DBL_MAX;
        //  G4cout<<"MeanFreePath reflection: "<<MeanFreePath<<G4endl;
        //  //getchar();
        //  return MeanFreePath;

        *condition = Forced;

        return DBL_MAX;

    }

