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
//
// $Id: G4OpBoundaryProcess.hh,v 1.14 2006/06/29 21:08:38 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//
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
//////////////////////////////////////////////////////////////////////////


#ifndef G4MuReflection_h
#define G4MuReflection_h 1

/////////////
// Includes
/////////////

#include "globals.hh"
#include "templates.hh"
#include "geomdefs.hh"
#include "Randomize.hh"
#include "G4Step.hh"
#include "G4VDiscreteProcess.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "musrMuonium.hh"
#include "G4TransportationManager.hh"

// Class Description:
// Discrete Process -- reflection/refraction at optical interfaces.
// Class inherits publicly from G4VDiscreteProcess.                  
// Class Description - End:             

/////////////////////
// Class Definition
/////////////////////

enum G4MuReflectionStatus {  Undefined,
			      FresnelRefraction, FresnelReflection,
			      TotalInternalReflection,
			      LambertianReflection, LobeReflection,
			      SpikeReflection, BackScattering,
			      Absorption, Detection, NotAtBoundary, NotInBeamPipe,InVacuum,
			      SameMaterial, StepTooSmall, NoRINDEX };

class G4MuReflection : public G4VDiscreteProcess 
{

private:

        //////////////
        // Operators
        //////////////

        // G4MuReflection& operator=(const G4MuReflection &right);

        // G4MuReflection(const G4MuReflection &right);

public: // Without description

        ////////////////////////////////
        // Constructors and Destructor
        ////////////////////////////////

        G4MuReflection(const G4String& processName = "MuReflection",
                                     G4ProcessType type = fUserDefined);

	~G4MuReflection();

	////////////
	// Methods
        ////////////

public: // With description

        G4bool IsApplicable(const G4ParticleDefinition& aParticleType);
        // Returns true -> 'is applicable' only for an Mu atom.

	G4double GetMeanFreePath(const G4Track& aTrack,
				 G4double ,
				 G4ForceCondition* condition);
        // Returns infinity; i. e. the process does not limit the step,
        // but sets the 'Forced' condition for the DoIt to be invoked at
        // every step. However, only at a boundary will any action be
        // taken. 

	G4VParticleChange* PostStepDoIt(const G4Track& aTrack,
				       const G4Step&  aStep);
        // This is the method implementing boundary processes.


        G4MuReflectionStatus GetStatus() const;
        // Returns the current status.


private:
         G4double MeanFreePath;        // actual Mean Free Path (current medium)

	void G4Swap(G4double* a, G4double* b) const;

	void G4Swap(G4Material* a, G4Material* b) const;

	void G4VectorSwap(G4ThreeVector* vec1, G4ThreeVector* vec2) const;

	G4bool G4BooleanRand(const G4double prob) const;

	G4ThreeVector G4IsotropicRand() const;

	G4ThreeVector G4LambertianRand(const G4ThreeVector& normal);

	G4ThreeVector G4KnudsenRand(const G4ThreeVector& normal);

	G4ThreeVector G4PlaneVectorRand(const G4ThreeVector& normal) const; 


	void DoReflection();

private:

	G4double theMuMomentum;
	G4double KinEnergy;

	G4ThreeVector OldMomentum;
	G4ThreeVector OldPolarization;

	G4ThreeVector NewMomentum;
	G4ThreeVector NewPolarization;

	G4ThreeVector theGlobalNormal;
	G4ThreeVector theFacetNormal;

	G4Material* Material1;
	G4Material* Material2;

	G4OpticalSurface* OpticalSurface;

	G4double Rindex1;
	G4double Rindex2;

	G4double cost1, cost2, sint1, sint2;

	G4MuReflectionStatus theStatus;

	G4OpticalSurfaceModel theModel;

	G4OpticalSurfaceFinish theFinish;

	G4double theReflectivity;
	G4double theEfficiency;
	G4double prob_sl, prob_ss, prob_bs;

};

////////////////////
// Inline methods
////////////////////

inline
void G4MuReflection::G4Swap(G4double* a, G4double* b) const
{
	// swaps the contents of the objects pointed 
	// to by 'a' and 'b'!

  G4double temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

inline
void G4MuReflection::G4Swap(G4Material* a, G4Material* b) const
{
	// ONLY swaps the pointers; i.e. what used to be pointed
	// to by 'a' is now pointed to by 'b' and vice versa!

   G4Material* temp = a;

   a = b;
   b = temp;
}

inline
void G4MuReflection::G4VectorSwap(G4ThreeVector* vec1,
				       G4ThreeVector* vec2) const
{
        // swaps the contents of the objects pointed
        // to by 'vec1' and 'vec2'!

  G4ThreeVector temp;

  temp = *vec1;
  *vec1 = *vec2;
  *vec2 = temp;
}

inline
G4bool G4MuReflection::G4BooleanRand(const G4double prob) const
{
  /* Returns a random boolean variable with the specified probability */

  return (G4UniformRand() < prob);
}

inline
G4ThreeVector G4MuReflection::G4IsotropicRand() const
{
  /* Returns a random isotropic unit vector. */

  G4ThreeVector vect;
  G4double len2;

  do {

    vect.setX(G4UniformRand() - 0.5);
    vect.setY(G4UniformRand() - 0.5);
    vect.setZ(G4UniformRand() - 0.5);

    len2 = vect.mag2();

  } while (len2 < 0.01 || len2 > 0.25);

  return vect.unit();
}

inline
G4ThreeVector G4MuReflection::
	      G4LambertianRand(const G4ThreeVector& normal)
{
  /* Returns a random lambertian unit vector. */

  G4ThreeVector vect;
  G4double ndotv;

  do {
    vect = G4IsotropicRand();

    ndotv = normal * vect;

    if (ndotv < 0.0) {
      vect = -vect;
      ndotv = -ndotv;
    }

  } while (!G4BooleanRand(ndotv));
  return vect;
}

inline
G4ThreeVector G4MuReflection::
	      G4KnudsenRand(const G4ThreeVector& normal)
{
  /* Returns a random unit vector. */

  G4ThreeVector vect;
  G4double ndotv;

  //do {
    vect = G4IsotropicRand();

    ndotv = normal * vect;

    if (ndotv < 0.0) {
      vect = -vect;
      ndotv = -ndotv;
    }

    //} while (!G4BooleanRand(ndotv));
  return vect;
}

inline
G4ThreeVector G4MuReflection::
	      G4PlaneVectorRand(const G4ThreeVector& normal) const

  /* This function chooses a random vector within a plane given
     by the unit normal */
{
  G4ThreeVector vec1 = normal.orthogonal();

  G4ThreeVector vec2 = vec1.cross(normal);

  G4double phi = twopi*G4UniformRand();
  G4double cosphi = std::cos(phi);
  G4double sinphi = std::sin(phi);

  return cosphi * vec1 + sinphi * vec2;
}

inline
G4bool G4MuReflection::IsApplicable(const G4ParticleDefinition& 
					               aParticleType)
{
  //return ( &aParticleType == G4Positronium::Positronium());
      return ( &aParticleType == musrMuonium::Muonium());
}


inline
G4MuReflectionStatus G4MuReflection::GetStatus() const
{
   return theStatus;
}



inline
void G4MuReflection::DoReflection()
{

  //NewMomentum = G4LambertianRand(theGlobalNormal);
  NewMomentum = G4KnudsenRand(theGlobalNormal);
  //NewMomentum = G4PlaneVectorRand(theGlobalNormal);
   theFacetNormal = (NewMomentum - OldMomentum).unit();

}

#endif /* G4MuReflection_h */
