//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 26 15:19:45 2013 by ROOT version 5.34/00
// from TTree t1/a simple Tree with simple variables
// found on file: musr_201214202.root
//////////////////////////////////////////////////////////

#ifndef t1_h
#define t1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <TH1.h>
using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class t1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runID;
   Int_t           eventID;
   Double_t        weight;
   Double_t        timeToNextEvent;
   Double_t        BFieldAtDecay_Bx;
   Double_t        BFieldAtDecay_By;
   Double_t        BFieldAtDecay_Bz;
   Double_t        BFieldAtDecay_B3;
   Double_t        BFieldAtDecay_B4;
   Double_t        BFieldAtDecay_B5;
   Double_t        muIniTime;
   Double_t        muIniPosX;
   Double_t        muIniPosY;
   Double_t        muIniPosZ;
   Double_t        muIniMomX;
   Double_t        muIniMomY;
   Double_t        muIniMomZ;
   Double_t        muIniPolX;
   Double_t        muIniPolY;
   Double_t        muIniPolZ;
   Int_t           muDecayDetID;
   Double_t        muDecayPosX;
   Double_t        muDecayPosY;
   Double_t        muDecayPosZ;
   Double_t        muDecayTime;
   Double_t        muDecayPolX;
   Double_t        muDecayPolY;
   Double_t        muDecayPolZ;
   Double_t        muTargetTime;
   Double_t        muTargetPolX;
   Double_t        muTargetPolY;
   Double_t        muTargetPolZ;
   Double_t        muTargetMomX;
   Double_t        muTargetMomY;
   Double_t        muTargetMomZ;
   Double_t        posIniMomX;
   Double_t        posIniMomY;
   Double_t        posIniMomZ;
   Int_t           nFieldNomVal;
   Double_t        fieldNomVal[200];   //[nFieldNomVal]
   Int_t           det_n;
   Int_t           det_ID[200];   //[det_n]
   Double_t        det_edep[200];   //[det_n]
   Double_t        det_edep_el[200];   //[det_n]
   Double_t        det_edep_pos[200];   //[det_n]
   Double_t        det_edep_gam[200];   //[det_n]
   Double_t        det_edep_mup[200];   //[det_n]
   Int_t           det_nsteps[200];   //[det_n]
   Double_t        det_length[200];   //[det_n]
   Double_t        det_time_start[200];   //[det_n]
   Double_t        det_time_end[200];   //[det_n]
   Double_t        det_x[200];   //[det_n]
   Double_t        det_y[200];   //[det_n]
   Double_t        det_z[200];   //[det_n]
   Double_t        det_kine[200];   //[det_n]
   Int_t           save_n;
   Int_t           save_detID[5000];   //[save_n]
   Int_t           save_particleID[5000];   //[save_n]
   Double_t        save_ke[5000];   //[save_n]
   Double_t        save_time[5000];   //[save_n]
   Double_t        save_x[5000];   //[save_n]
   Double_t        save_y[5000];   //[save_n]
   Double_t        save_z[5000];   //[save_n]
   Double_t        save_px[5000];   //[save_n]
   Double_t        save_py[5000];   //[save_n]
   Double_t        save_pz[5000];   //[save_n]
   Double_t        save_polx[5000];   //[save_n]
   Double_t        save_poly[5000];   //[save_n]
   Double_t        save_polz[5000];   //[save_n]

   // List of branches
   TBranch        *b_runID;   //!
   TBranch        *b_eventID;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_timeToNextEvent;   //!
   TBranch        *b_BFieldAtDecay;   //!
   TBranch        *b_muIniTime;   //!
   TBranch        *b_muIniPosX;   //!
   TBranch        *b_muIniPosY;   //!
   TBranch        *b_muIniPosZ;   //!
   TBranch        *b_muIniMomX;   //!
   TBranch        *b_muIniMomY;   //!
   TBranch        *b_muIniMomZ;   //!
   TBranch        *b_muIniPolX;   //!
   TBranch        *b_muIniPolY;   //!
   TBranch        *b_muIniPolZ;   //!
   TBranch        *b_muDecayDetID;   //!
   TBranch        *b_muDecayPosX;   //!
   TBranch        *b_muDecayPosY;   //!
   TBranch        *b_muDecayPosZ;   //!
   TBranch        *b_muDecayTime;   //!
   TBranch        *b_muDecayPolX;   //!
   TBranch        *b_muDecayPolY;   //!
   TBranch        *b_muDecayPolZ;   //!
   TBranch        *b_muTargetTime;   //!
   TBranch        *b_muTargetPolX;   //!
   TBranch        *b_muTargetPolY;   //!
   TBranch        *b_muTargetPolZ;   //!
   TBranch        *b_muTargetMomX;   //!
   TBranch        *b_muTargetMomY;   //!
   TBranch        *b_muTargetMomZ;   //!
   TBranch        *b_posIniMomX;   //!
   TBranch        *b_posIniMomY;   //!
   TBranch        *b_posIniMomZ;   //!
   TBranch        *b_nFieldNomVal;   //!
   TBranch        *b_fieldNomVal;   //!
   TBranch        *b_det_n;   //!
   TBranch        *b_det_ID;   //!
   TBranch        *b_det_edep;   //!
   TBranch        *b_det_edep_el;   //!
   TBranch        *b_det_edep_pos;   //!
   TBranch        *b_det_edep_gam;   //!
   TBranch        *b_det_edep_mup;   //!
   TBranch        *b_det_nsteps;   //!
   TBranch        *b_det_length;   //!
   TBranch        *b_det_time_start;   //!
   TBranch        *b_det_time_end;   //!
   TBranch        *b_det_x;   //!
   TBranch        *b_det_y;   //!
   TBranch        *b_det_z;   //!
   TBranch        *b_det_kine;   //!
   TBranch        *b_save_n;   //!
   TBranch        *b_save_detID;   //!
   TBranch        *b_save_particleID;   //!
   TBranch        *b_save_ke;   //!
   TBranch        *b_save_time;   //!
   TBranch        *b_save_x;   //!
   TBranch        *b_save_y;   //!
   TBranch        *b_save_z;   //!
   TBranch        *b_save_px;   //!
   TBranch        *b_save_py;   //!
   TBranch        *b_save_pz;   //!
   TBranch        *b_save_polx;   //!
   TBranch        *b_save_poly;   //!
   TBranch        *b_save_polz;   //!

   t1(TTree *tree=0);
   virtual ~t1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef t1_cxx
t1::t1(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("musr_20120275.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("musr_20120275.root");
      }
      f->GetObject("t1",tree);

   }
   Init(tree);
}

t1::~t1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t t1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t t1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void t1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runID", &runID, &b_runID);
   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("timeToNextEvent", &timeToNextEvent, &b_timeToNextEvent);
   fChain->SetBranchAddress("BFieldAtDecay", &BFieldAtDecay_Bx, &b_BFieldAtDecay);
   fChain->SetBranchAddress("muIniTime", &muIniTime, &b_muIniTime);
   fChain->SetBranchAddress("muIniPosX", &muIniPosX, &b_muIniPosX);
   fChain->SetBranchAddress("muIniPosY", &muIniPosY, &b_muIniPosY);
   fChain->SetBranchAddress("muIniPosZ", &muIniPosZ, &b_muIniPosZ);
   fChain->SetBranchAddress("muIniMomX", &muIniMomX, &b_muIniMomX);
   fChain->SetBranchAddress("muIniMomY", &muIniMomY, &b_muIniMomY);
   fChain->SetBranchAddress("muIniMomZ", &muIniMomZ, &b_muIniMomZ);
   fChain->SetBranchAddress("muIniPolX", &muIniPolX, &b_muIniPolX);
   fChain->SetBranchAddress("muIniPolY", &muIniPolY, &b_muIniPolY);
   fChain->SetBranchAddress("muIniPolZ", &muIniPolZ, &b_muIniPolZ);
   fChain->SetBranchAddress("muDecayDetID", &muDecayDetID, &b_muDecayDetID);
   fChain->SetBranchAddress("muDecayPosX", &muDecayPosX, &b_muDecayPosX);
   fChain->SetBranchAddress("muDecayPosY", &muDecayPosY, &b_muDecayPosY);
   fChain->SetBranchAddress("muDecayPosZ", &muDecayPosZ, &b_muDecayPosZ);
   fChain->SetBranchAddress("muDecayTime", &muDecayTime, &b_muDecayTime);
   fChain->SetBranchAddress("muDecayPolX", &muDecayPolX, &b_muDecayPolX);
   fChain->SetBranchAddress("muDecayPolY", &muDecayPolY, &b_muDecayPolY);
   fChain->SetBranchAddress("muDecayPolZ", &muDecayPolZ, &b_muDecayPolZ);
   fChain->SetBranchAddress("muTargetTime", &muTargetTime, &b_muTargetTime);
   fChain->SetBranchAddress("muTargetPolX", &muTargetPolX, &b_muTargetPolX);
   fChain->SetBranchAddress("muTargetPolY", &muTargetPolY, &b_muTargetPolY);
   fChain->SetBranchAddress("muTargetPolZ", &muTargetPolZ, &b_muTargetPolZ);
   fChain->SetBranchAddress("muTargetMomX", &muTargetMomX, &b_muTargetMomX);
   fChain->SetBranchAddress("muTargetMomY", &muTargetMomY, &b_muTargetMomY);
   fChain->SetBranchAddress("muTargetMomZ", &muTargetMomZ, &b_muTargetMomZ);
   fChain->SetBranchAddress("posIniMomX", &posIniMomX, &b_posIniMomX);
   fChain->SetBranchAddress("posIniMomY", &posIniMomY, &b_posIniMomY);
   fChain->SetBranchAddress("posIniMomZ", &posIniMomZ, &b_posIniMomZ);
   fChain->SetBranchAddress("nFieldNomVal", &nFieldNomVal, &b_nFieldNomVal);
   fChain->SetBranchAddress("fieldNomVal", fieldNomVal, &b_fieldNomVal);
   fChain->SetBranchAddress("det_n", &det_n, &b_det_n);
   fChain->SetBranchAddress("det_ID", det_ID, &b_det_ID);
   fChain->SetBranchAddress("det_edep", det_edep, &b_det_edep);
   fChain->SetBranchAddress("det_edep_el", det_edep_el, &b_det_edep_el);
   fChain->SetBranchAddress("det_edep_pos", det_edep_pos, &b_det_edep_pos);
   fChain->SetBranchAddress("det_edep_gam", det_edep_gam, &b_det_edep_gam);
   fChain->SetBranchAddress("det_edep_mup", det_edep_mup, &b_det_edep_mup);
   fChain->SetBranchAddress("det_nsteps", det_nsteps, &b_det_nsteps);
   fChain->SetBranchAddress("det_length", det_length, &b_det_length);
   fChain->SetBranchAddress("det_time_start", det_time_start, &b_det_time_start);
   fChain->SetBranchAddress("det_time_end", det_time_end, &b_det_time_end);
   fChain->SetBranchAddress("det_x", det_x, &b_det_x);
   fChain->SetBranchAddress("det_y", det_y, &b_det_y);
   fChain->SetBranchAddress("det_z", det_z, &b_det_z);
   fChain->SetBranchAddress("det_kine", det_kine, &b_det_kine);
   fChain->SetBranchAddress("save_n", &save_n, &b_save_n);
   fChain->SetBranchAddress("save_detID", save_detID, &b_save_detID);
   fChain->SetBranchAddress("save_particleID", save_particleID, &b_save_particleID);
   fChain->SetBranchAddress("save_ke", save_ke, &b_save_ke);
   fChain->SetBranchAddress("save_time", save_time, &b_save_time);
   fChain->SetBranchAddress("save_x", save_x, &b_save_x);
   fChain->SetBranchAddress("save_y", save_y, &b_save_y);
   fChain->SetBranchAddress("save_z", save_z, &b_save_z);
   fChain->SetBranchAddress("save_px", save_px, &b_save_px);
   fChain->SetBranchAddress("save_py", save_py, &b_save_py);
   fChain->SetBranchAddress("save_pz", save_pz, &b_save_pz);
   fChain->SetBranchAddress("save_polx", save_polx, &b_save_polx);
   fChain->SetBranchAddress("save_poly", save_poly, &b_save_poly);
   fChain->SetBranchAddress("save_polz", save_polz, &b_save_polz);
   Notify();
}

Bool_t t1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t t1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef t1_cxx
