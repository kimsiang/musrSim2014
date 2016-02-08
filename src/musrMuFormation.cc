/***************************************************************************
 *  musrSim - the program for the simulation of (mainly) muSR instruments. *
 *          More info on http://lmu.web.psi.ch/simulation/index.html .     *
 *          musrSim is based od Geant4 (http://geant4.web.cern.ch/geant4/) *
 *                                                                         *
 *  Copyright (C) 2009 by Paul Scherrer Institut, 5232 Villigen PSI,       *
 *                                                       Switzerland       *
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              *
 ***************************************************************************/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//  Muonium Formation according to yield.cc function (through GetYields method).
//  Id    : musrMuFormation.cc, v 1.4
//  Author: Taofiq PARAISO, T. Shiroka
//  Date  : 2007-12
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include "musrMuFormation.hh"

using namespace std;

musrMuFormation::musrMuFormation (const G4String & name, G4ProcessType aType):
G4VDiscreteProcess (name, aType)
{
}

musrMuFormation::~musrMuFormation ()
{
}

G4VParticleChange *
musrMuFormation::PostStepDoIt (const G4Track & trackData, const G4Step & aStep)
{				// Initialize ParticleChange  (by setting all its members equal to
  //                             the corresponding members in G4Track)
  fParticleChange.Initialize (trackData);

  G4Track theNewTrack;
  if (CheckCondition (aStep))
    {
      GetDatas (&aStep);
      G4Step theStep;
      PrepareSecondary (trackData);

      fParticleChange.AddSecondary (aSecondary);
      fParticleChange.ProposeTrackStatus (fStopAndKill);
    }
  else
    {
      fParticleChange.ProposeTrackStatus (trackData.GetTrackStatus ());
    }
  return &fParticleChange;
}


G4bool
musrMuFormation::CheckCondition (const G4Step & aStep)
{				// Decide when to call the MuFormation process - i.e. for muons going through the C foil.
  G4bool condition = false;
  p_name = aStep.GetTrack ()->GetDefinition ()->GetParticleName ();	// particle name  
  //if(p_name == "mu+"&&aStep.GetTrack()->GetVolume()->GetLogicalVolume()->GetName()=="log_CFoil") 
  std::string logVolName = aStep.GetTrack ()->GetVolume ()->GetLogicalVolume ()->GetName ();
  if (p_name == "mu+" && ((logVolName == "log_refsample") ||(logVolName == "log_sample") || (logVolName == "log_CFoil")))
 // if (p_name == "mu+" && logVolName == "log_CFoil")
    {
      condition = true;
    }
  return condition;
}


G4double
musrMuFormation::GetMeanFreePath (const G4Track &, G4double, G4ForceCondition * condition)
{
  *condition = Forced;
  return DBL_MAX;
}


void
musrMuFormation::GetDatas (const G4Step * aStep)
{				// Particle generation according to yield table
  particleTable = G4ParticleTable::GetParticleTable ();
  rnd1 = G4UniformRand ();
  rnd2 = G4UniformRand ();
  G4double E = aStep->GetTrack ()->GetDynamicParticle ()->GetKineticEnergy () / keV;
  Gonin.GetYields (E, 105.658369 * 1000, yvector);	// Energy [keV], muon mass [keV/c2], yield table
  G4String p_new = "Mu";

  std::string logVolName = aStep->GetTrack ()->GetVolume ()->GetLogicalVolume ()->GetName ();

  /*    G4cout<<"Energy(keV): "<<aStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/keV<<G4endl;
     G4cout<<"ProperTime(ns): "<<aStep->GetTrack()->GetDynamicParticle()->GetProperTime()<<G4endl;
     G4cout<<"PreAssignedDecayProperTime(ns): "<<aStep->GetTrack()->GetDynamicParticle()->GetPreAssignedDecayProperTime()<<G4endl;
     G4cout<<"MomentumDirection: "<<aStep->GetTrack()->GetDynamicParticle()->GetMomentumDirection()<<G4endl;
   */
  // Positive muon

  if (p_name == "mu+" && logVolName == "log_CFoil")
    {
      if (rnd1 < yvector[0])
	{
	  particle = particleTable->FindParticle (p_name);
	}
      else
	{
	//   G4cout<<"### Muonium is formed at the Carbon Foil !"<<G4endl;
	      	particle = particleTable->FindParticle (p_new);
	}

      // Set the new dynamic particle DP
      DP = new G4DynamicParticle (particle,
				  aStep->GetTrack ()->GetDynamicParticle ()->GetMomentumDirection (),
				  aStep->GetTrack ()->GetDynamicParticle ()->GetKineticEnergy ());

      // IMPORTANT : COPY THOSE DATA TO GET THE SAME PARTICLE PROPERTIES!!!
      // SHOULD BE KEPT WHEN BUILDING A PARTICLE CHANGE  
      DP->SetProperTime (aStep->GetTrack ()->GetDynamicParticle ()->GetProperTime ());
      if (particle == particleTable->FindParticle ("mu+"))
	{
	  DP->SetPolarization (aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().x (),
			       aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().y (),
			       aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().z ());
	}
      if (particle == particleTable->FindParticle ("Mu"))
	{
	  DP->SetPolarization (0, 0, 0);
	}
      DP->SetPreAssignedDecayProperTime (aStep->GetTrack ()->GetDynamicParticle ()->GetPreAssignedDecayProperTime ());
    }



  if (p_name == "mu+" && logVolName == "log_sample")
    {
      if (rnd2 < 0.0)
	{
	  particle = particleTable->FindParticle (p_name);
	  DP = new G4DynamicParticle (particle,
				      aStep->GetTrack ()->GetDynamicParticle ()->GetMomentumDirection (),
				      aStep->GetTrack ()->GetDynamicParticle ()->GetKineticEnergy ());
	}
      else
	{
	  particle = particleTable->FindParticle (p_new);
	  G4double cosTheta = 0.;
	  G4double sinTheta = 0.;
	  cosTheta = -G4UniformRand ();	//send Mu in -z direction 
	  sinTheta = sqrt (-cosTheta);	// cos theta 
	  G4double phi = twopi * G4UniformRand ();
	G4ThreeVector newp = G4ThreeVector (sinTheta * cos (phi), sinTheta * sin (phi), cosTheta);
	  DP = new G4DynamicParticle (particle,
				      newp/newp.mag(),
				      this->GetMuEkin()*eV);
	 }


      DP->SetPolarization (aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().x (),
			   aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().y (),
			   aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().z ());
      DP->SetPreAssignedDecayProperTime (aStep->GetTrack ()->GetDynamicParticle ()->GetPreAssignedDecayProperTime ());
    }

  if (p_name == "mu+" && logVolName == "log_refsample")
    {
      if (rnd2 > 0.8)
	{
	  particle = particleTable->FindParticle (p_name);
	  DP = new G4DynamicParticle (particle,
				      aStep->GetTrack ()->GetDynamicParticle ()->GetMomentumDirection (),
				      aStep->GetTrack ()->GetDynamicParticle ()->GetKineticEnergy ());
	}
      else
	{
	  particle = particleTable->FindParticle (p_new);
	  DP = new G4DynamicParticle (particle, G4ThreeVector(0,0,-1),0*eV);
	 }


      DP->SetPolarization (aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().x (),
			   aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().y (),
			   aStep->GetTrack ()->GetDynamicParticle ()->GetPolarization ().z ());
      DP->SetPreAssignedDecayProperTime (aStep->GetTrack ()->GetDynamicParticle ()->GetPreAssignedDecayProperTime ());
    }



}




void
musrMuFormation::PrepareSecondary (const G4Track & track)
{
  if (p_name == "mu+")
    {
      aSecondary = new G4Track (DP, track.GetGlobalTime (), track.GetPosition ());
    }
}

G4double musrMuFormation::MuVelocity(G4double T){
  //          Calculate the energy distribution of the Muonium assuming a Maxwell-Boltzmann profile for a given temperature (Temp)

  G4double k_b=1.380658e-23; //Boltzmann constant
  G4double m_p=1.6e-27,M=m_p/7., pi=twopi/2.;
  G4double v_b_max; //v_b_max most probable velocity at temp T 
  v_b_max=sqrt((2*k_b*T)/(M));
  
  G4double N_v=0 , N_max;

  N_max=4*pi*pow(M/(2*pi*k_b*T),3./2.)*pow(v_b_max,2)*exp(-1*(M*pow(v_b_max,2))/(2*k_b*T));//Maximum of the distribution

  G4double v_limit; //v_limit maximum velocity for which the MB distribution will be simulated 
  v_limit=6*v_b_max;//set v limit 6 times bigger then v_b_max

  G4double rnd_v, rnd_N;
  G4int n=0;

  while(1){
    n++;
    rnd_v= G4UniformRand();
    rnd_N= G4UniformRand();
    //Maxwell distr. 
    v_b=rnd_v*v_limit;
    rnd_N*=N_max;
    N_v=4*pi*pow(M/(2*pi*k_b*T),3./2.)*pow(v_b,2)*exp(-1*(M*pow(v_b,2))/(2*k_b*T));
    if(rnd_N<=N_v){
      break;
    }
  
  }
  //cout<<"Number of iteration to get the MB_distr. "<<n<<endl;
  // G4cout<<"v_b "<<v_b<<G4endl;

  return v_b;
}

G4double musrMuFormation::GetMuEkin(){
  G4double m_p=1.6e-27,M=m_p/7.;//Muonium mass
  
//  G4double v_ops=MuVelocity(GetTemperature());//convert it to m/s
  G4double v_ops=MuVelocity(250);//convert it to m/s
  MuEkin=0.5*M*pow(v_ops,2)/1.6e-19;
// cout<<v_ops<<" m/s "<<MuEkin<<" eV"<<endl;
  return MuEkin;
}

G4double musrMuFormation::GetMuVelocity(){
  return v_b;
}
