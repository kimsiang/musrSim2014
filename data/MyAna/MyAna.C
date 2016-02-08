#include "MyAna.h"
#include <iostream>
#include <cmath>
#include <omp.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TCanvas.h>

#include "TSystem.h"
void
MyAna::Loop (string filename)
{
//  cout << "Loop()" << endl;

// initialize ();
  initialize (filename);

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast ();
// nentries = 500000;
  Int_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      // if(muDecayTime==-1) continue;
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;

      clear ();
      execute ();


    }

  finalize (filename);

}

void
MyAna::initialize (string filename)
{

// cout << "initialize()" << endl;
  filename.append (".root");
  char *out = (char *) filename.c_str ();
  m_file = new TFile (out, "recreate");

  upstream = 0;
  downstream = 0;
  target = 0;
  nLU = 0;
  nBU = 0;
  nRU = 0;
  nTU = 0;
  nLD = 0;
  nBD = 0;
  nRD = 0;
  nTD = 0;
  nevent = 0;

  int nbin = 1300;

  f = new TH1F ("forward", "f", nbin, -1, 12);
  b = new TH1F ("backward", "b", nbin, -1, 12);
  ft = new TH1F ("forwardt", "ft", nbin, -1, 12);
  bt = new TH1F ("backwardt", "bt", nbin, -1, 12);
  finf = new TH1F ("forwardinf", "finf", nbin, -1, 12);
  binf = new TH1F ("backwardinf", "binf", nbin, -1, 12);
  f1 = new TH1F ("forward1", "f1", nbin, -1, 12);
  f2 = new TH1F ("forward2", "f2", nbin, -1, 12);
  f3 = new TH1F ("forward3", "f3", nbin, -1, 12);
  f4 = new TH1F ("forward4", "f4", nbin, -1, 12);
  b1 = new TH1F ("backward1", "b1", nbin, -1, 12);
  b2 = new TH1F ("backward2", "b2", nbin, -1, 12);
  b3 = new TH1F ("backward3", "b3", nbin, -1, 12);
  b4 = new TH1F ("backward4", "b4", nbin, -1, 12);
  f1t = new TH1F ("forward1t", "f1t", nbin, -1, 12);
  f2t = new TH1F ("forward2t", "f2t", nbin, -1, 12);
  f3t = new TH1F ("forward3t", "f3t", nbin, -1, 12);
  f4t = new TH1F ("forward4t", "f4t", nbin, -1, 12);
  b1t = new TH1F ("backward1t", "b1t", nbin, -1, 12);
  b2t = new TH1F ("backward2t", "b2t", nbin, -1, 12);
  b3t = new TH1F ("backward3t", "b3t", nbin, -1, 12);
  b4t = new TH1F ("backward4t", "b4t", nbin, -1, 12);
  tof = new TH1F ("tof", "tof", nbin, 0, 325);
  ke = new TH1F ("kinetic", "ke", nbin, 0, 40);
  polx = new TH1F ("polx", "polx", 200, -1, 1);
  poly = new TH1F ("poly", "poly", 200, -1, 1);
  polz = new TH1F ("polz", "polz", 200, -1, 1);
  etrig = new TH1F ("etrig", "etrig", 1000, 0, 20);
  edep_b1 = new TH1F ("edep_b1", "edep_b1", 1000, 0, 5);
  edep_f1 = new TH1F ("edep_f1", "edep_f1", 1000, 0, 5);
  edep_b2 = new TH1F ("edep_b2", "edep_b2", 1000, 0, 5);
  edep_f2 = new TH1F ("edep_f2", "edep_f2", 1000, 0, 5);
  ke_trig = new TH1F ("ke_trig", "ke_trig", nbin, 0, 24);
  ke_stop = new TH1F ("ke_stop", "ke_stop", nbin, 0, 24);
  lifetime = new TH1F ("lifetime", "lifetime", nbin, -1, 12);
  Afb = new TH1F ("Afb", "Afb", nbin, -1, 12);
  Afbt = new TH1F ("Afbt", "Afbt", nbin, -1, 12);
  decayZ_b = new TH1F ("decayZ_b", "decayZ_b", 4000, -380, 20);
  decayZ_f = new TH1F ("decayZ_f", "decayZ_f", 4000, -380, 20);
  decayXY = new TH2F ("decayXY", "decayXY", 200, -50, 50, 200, -50, 50);
  decayXY_b = new TH2F ("decayXY_b", "decayXY_b", 200, -50, 50, 200, -50, 50);
  decayXY_f = new TH2F ("decayXY_f", "decayXY_f", 200, -50, 50, 200, -50, 50);
  foilXY_b = new TH2F ("foilXY_b", "foilXY_b", 1000, -50, 50, 1000, -50, 50);
  foilXY_f = new TH2F ("foilXY_f", "foilXY_f", 1000, -50, 50, 1000, -50, 50);
  decayZf = new TH2F ("decayZf", "decayZf", nbin, -1, 12, 4000, -380, 20);
  decayZb = new TH2F ("decayZb", "decayZb", nbin, -1, 12, 4000, -380, 20);
  decayZr = new TH2F ("decayZr", "decayZr", 1000,-50,50, 4000, -380, 20);
  myfit = new TF1 ("myfit", "[0]", 1, 5);
  exp1 = new TF1 ("exp1", "[0]*exp(-x/2.2)+[1]", 1, 5);
  exp2 = new TF1 ("exp2", "[0]*exp(-x/2.2)+[1]", 1, 5);

}

void
MyAna::execute ()
{
//  cout << "execute()" << endl;
//  cout << "################################" << endl;
  if (eventID % 100000 == 0)
    {
      cout << "  [eventID: " << eventID << "]" << endl;
    }

  bool trig = false;
  bool stop = false;
  bool stop_f = false;
  bool stop_b = false;
  bool inside = false;
  // int ncount = 0;
  // int id[8] = { };
  double tstart = 0;
//  double tend = 0;
  double eCut = 0.6;

  lifetime->Fill (muDecayTime);

  //Set up the random number generator for smearing our data
  TRandom *rand = new TRandom ();
  rand->SetSeed (0);		//Set a random seed

  //  for(int i=0; i<save_n; i++){
//  if(save_detID[i]==901&&save_particleID[i]==-13&&save_ke[i]>0.003) 
//  break;  
  //  }
  double total_edep = 0;

  for (int i = 0; i < det_n; i++)
    {

      if (det_ID[i] == 65)
	{
	  total_edep += det_edep_mup[i] * 1000;
	  inside = true;
//	  tstart = det_time_start[i] + 0.0135 + 0.2478515625;	// for musr 2011
        tstart = det_time_start[i]+0.1120;  // for musr 2012

	}
      if (det_ID[i] == 66)
	{
	  // cout<<"####  Hit MCP 1st!!! ####"<<endl;
	  inside = true;
	  tstart = det_time_start[i] + 0.2478515625;	// for musr 2011
//  tstart = det_time_start[i]+0.151953125;  // for musr 2012
	}
    }
  if (inside)
    {
      trig = true;
    }

  if (inside)
    {
      etrig->Fill (total_edep);
    }


  for (Int_t i = 0; i < det_n; i++)
    {
      if (det_ID[i] >= 1 && det_ID[i] <= 16)
	{
	  edep_b1->Fill (det_edep[i]);
	}
      else if (det_ID[i] >= 33 && det_ID[i] <= 48)
	{
	  edep_b2->Fill (det_edep[i]);
	}
      else if (det_ID[i] >= 17 && det_ID[i] <= 32)
	{
	  edep_f1->Fill (det_edep[i]);
	}
      else if (det_ID[i] >= 49 && det_ID[i] <= 64)
	{
	  edep_f2->Fill (det_edep[i]);
	}
    }

  if (trig)
    {

      // Hist in Back detector (1-16) coincidence (33-48)
      for (Int_t i = 0; i < det_n; i++)
	{
	  if (det_ID[i] >= 1 && det_ID[i] <= 16 && !stop && det_edep[i] > eCut)
	    {
	      for (Int_t j = 0; j < det_n; j++)
		{
		  if (det_ID[j] >= 33 && det_ID[j] <= 48 && (det_ID[j] - det_ID[i] == 32) && det_edep[j] > eCut)
		    {
		      b->Fill (det_time_start[i] - tstart);
		      /*            if (det_time_start[i] - tstart < 0)
		         {
		         cout << "  eventID: " << eventID << endl;
		         cout << "i: " << det_ID[i] << ", tstart: " << tstart << ", det_time_start[i]: " << det_time_start[i] << ", det_time_start[i] - tstart (Backward): " << det_time_start[i] - tstart << endl;
		         } */
		      if (det_ID[j] >= 33 && det_ID[j] <= 36)
			{
			  b1->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 37 && det_ID[j] <= 40)
			{
			  b2->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 41 && det_ID[j] <= 44)
			{
			  b3->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 45 && det_ID[j] <= 48)
			{
			  b4->Fill (det_time_start[i] - tstart);
			}
		      decayZ_b->Fill (muDecayPosZ);
		      decayZb->Fill (det_time_start[i] - tstart, muDecayPosZ);
		      ++upstream;
		      decayXY->Fill (muDecayPosX, muDecayPosY);
		      if (muDecayPosZ < 0)
			{
			  binf->Fill (det_time_start[i] - tstart);
			}
		      if (abs (muDecayPosX) <= 10 && abs (muDecayPosY) <= 10 && muDecayPosZ > -1)
			{
			  ++target;
			  bt->Fill (det_time_start[i] - tstart);
			  if (det_ID[j] >= 33 && det_ID[j] <= 36)
			    {
			      b1t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 37 && det_ID[j] <= 40)
			    {
			      b2t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 41 && det_ID[j] <= 44)
			    {
			      b3t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 45 && det_ID[j] <= 48)
			    {
			      b4t->Fill (det_time_start[i] - tstart);
			    }
			}
		      stop = true;
		      stop_b = true;
		      polx->Fill (muDecayPolX);
		      poly->Fill (muDecayPolY);
		      polz->Fill (muDecayPolZ);
		      //cout<<"# Backward detector!"<<endl;
		      break;	//fill only once
		    }
		}
	    }
	}

      // Hist in Forw I detector (17-32) coincidence (49-64)
      for (Int_t i = 0; i < det_n; i++)
	{
	  if (det_ID[i] >= 17 && det_ID[i] <= 32 && !stop && det_edep[i] > eCut)
	    {
	      for (Int_t j = 0; j < det_n; j++)
		{
		  if (det_ID[j] >= 49 && det_ID[j] <= 64 && (det_ID[j] - det_ID[i] == 32) && det_edep[j] > eCut)
		    {
		      f->Fill (det_time_start[i] - tstart);
		      if (det_time_start[i] - tstart < 0)
			{
			  // cout << "  eventID: " << eventID << endl;
			  // cout << "i: " << det_ID[i] << ", tstart: " << tstart << ", det_time_start[i]: " << det_time_start[i] << ", det_time_start[i] - tstart (Forward): " << det_time_start[i] - tstart << endl;
			}
		      if (det_ID[j] >= 49 && det_ID[j] <= 52)
			{
			  f1->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 53 && det_ID[j] <= 56)
			{
			  f2->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 57 && det_ID[j] <= 60)
			{
			  f3->Fill (det_time_start[i] - tstart);
			}
		      if (det_ID[j] >= 61 && det_ID[j] <= 64)
			{
			  f4->Fill (det_time_start[i] - tstart);
			}
		      decayZ_f->Fill (muDecayPosZ);
		      decayZf->Fill (det_time_start[i] - tstart, muDecayPosZ);
		      ++downstream;
		      decayXY->Fill (muDecayPosX, muDecayPosY);
		      if (muDecayPosZ < 0)
			{
			  finf->Fill (det_time_start[i] - tstart);
			}
		      if (abs (muDecayPosX) <= 10 && abs (muDecayPosY) <= 10 && muDecayPosZ > -1)
			{
			  ++target;
			  ft->Fill (det_time_start[i] - tstart);
			  if (det_ID[j] >= 49 && det_ID[j] <= 52)
			    {
			      f1t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 53 && det_ID[j] <= 56)
			    {
			      f2t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 57 && det_ID[j] <= 60)
			    {
			      f3t->Fill (det_time_start[i] - tstart);
			    }
			  if (det_ID[j] >= 61 && det_ID[j] <= 64)
			    {
			      f4t->Fill (det_time_start[i] - tstart);
			    }
			}
		      stop = true;
		      stop_f = true;
		      polx->Fill (muDecayPolX);
		      poly->Fill (muDecayPolY);
		      polz->Fill (muDecayPolZ);
		      //cout<<"# Forward detector!"<<endl;
		      break;	//fill only once
		    }
		}
	    }
	}


      for (int i = 0; i < det_n; i++)
	{

	  if (det_ID[i] == 65 && stop_b == true)
	    {
	      foilXY_b->Fill (det_x[i], det_y[i]);
		      decayXY_b->Fill (muDecayPosX, muDecayPosY);
	    }
	  else if (det_ID[i] == 65 && stop_f == true)
	    {
	      foilXY_f->Fill (det_x[i], det_y[i]);
		      decayXY_f->Fill (muDecayPosX, muDecayPosY);
		      decayZr->Fill (sqrt(muDecayPosX*muDecayPosX+muDecayPosY*muDecayPosY),muDecayPosZ);
	    }


	}
    }

  for (int i = 0; i < save_n; i++)
    {
      if (save_detID[i] == 901 && (save_particleID[i] == -13 || save_particleID[i] == -1313))
	{
	  //  cout<<"ke:"<< save_ke[i] <<endl;
	  ke->Fill (save_ke[i] * 1000);
	  if (trig)
	    {
	      ke_trig->Fill (save_ke[i] * 1000);
	      tof->Fill ((save_time[i] - tstart) * 1000);
	      if (stop)
		{
		  //              cout<<"# Stopped!"<<endl;
		  ke_stop->Fill (save_ke[i] * 1000);
		  break;	//fill only once
		}
	    }
	}
    }

// cout<<"upstream: "<<upstream<<", downstream: "<<downstream<<endl;
  ++nevent;

  delete rand;

}

void
MyAna::finalize (string filename)
{
/*  cout << "finalize()" << endl;
  cout << "total: " << upstream+downstream << ", upstream: " << upstream << ", downstream: " << downstream << endl;
  cout << "asymmetry: " << (double) (upstream - downstream) / (upstream + downstream) 
       << ", target: " << target << "(" << (double) target / (upstream +  downstream) << ")" << endl;
*/
  cout << "Total events: " << nevent << endl;
  cout << "Downstream: " << downstream << endl;
  cout << "Upstream: " << upstream << endl;

  double fw = 0;
  double bw = 0;
  double fwt = 0;
  double bwt = 0;

//#pragma omp parallel for
  for (int i = 1; i < 1301; i++)
    {
      fw = f->GetBinContent (i);
      bw = b->GetBinContent (i);
      fwt = ft->GetBinContent (i);
      bwt = bt->GetBinContent (i);
      if (fw != 0 && bw != 0)
	{
	  Afb->SetBinContent (i, (bw - fw) / (bw + fw));
	}
      if (fw == 0 || bw == 0)
	{
	  Afb->SetBinContent (i, 0);
	}
      if (fwt != 0 && bwt != 0)
	{
	  Afbt->SetBinContent (i, (bwt - fwt) / (bwt + fwt));
	}
      if (fwt == 0 || bwt == 0)
	{
	  Afbt->SetBinContent (i, 0);
	}
    }

  exp1->SetParameters (100, 20);
  b->Fit ("exp1", "NQR");

  exp2->SetParameters (100, 20);
  f->Fit ("exp2", "NQR");

  myfit->SetParameter (0, 0.3);
  Afb->Fit ("myfit", "QR");
  cout << "Afb: " << myfit->GetParameter (0) << "(fit), " << (double) (upstream - downstream) / (upstream + downstream) << "(event ratio)" << endl;
  cout << "% hitting target: " << (double) target *100 / (upstream + downstream) << endl;
  Afbt->Fit ("myfit", "QR");
  cout << "Afbt: " << myfit->GetParameter (0) << "(fit), " << (double) (upstream - downstream) / (upstream + downstream) << "(event ratio)" << endl;
  cout << "% hitting target: " << (double) target *100 / (upstream + downstream) << endl;


  m_file->Write ();
  m_file->Close ();


}

void
MyAna::clear ()
{

  //  cout << "clear()" << endl;
}
