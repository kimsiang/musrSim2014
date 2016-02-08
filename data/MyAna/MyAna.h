#ifndef MYANA_h
#define MYANA_h

#include "t1.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"

class MyAna : public t1 {
 public:
  MyAna(TTree *tree=0):t1(tree){};
  ~MyAna() {};
  virtual void Loop(string filename);
  void initialize(string filename);
  void execute();
  void finalize(string filename);
  void clear();
  string filename[1024];

 private:
 TFile *m_file;
  int upstream;
  int downstream;
  int target;
  int nLD;
  int nBD;
  int nRD;
  int nTD;
  int nLU;
  int nBU;
  int nRU;
  int nTU;
  int nevent;
 
  TH1F* f;
  TH1F* b;
  TH1F* ft;
  TH1F* bt;
  TH1F* finf;
  TH1F* binf;
  TH1F* f1;
  TH1F* f2;
  TH1F* f3;
  TH1F* f4;
  TH1F* b1;
  TH1F* b2;
  TH1F* b3;
  TH1F* b4;
  TH1F* f1t;
  TH1F* f2t;
  TH1F* f3t;
  TH1F* f4t;
  TH1F* b1t;
  TH1F* b2t;
  TH1F* b3t;
  TH1F* b4t;
  TH1F* Afb;
  TH1F* Afbt;
  TH1F* ke;
  TH1F* etrig;
  TH1F* edep_b1;
  TH1F* edep_f1;
  TH1F* edep_b2;
  TH1F* edep_f2;
  TH1F* polx;
  TH1F* poly;
  TH1F* polz;
  TH1F* tof;
  TH1F* ke_trig;
  TH1F* ke_stop;
  TH1F* lifetime;
  TH1F* decayZ_b;
  TH1F* decayZ_f;
  TH2F* decayXY;
  TH2F* decayXY_b;
  TH2F* decayXY_f;
  TH2F* foilXY_b;
  TH2F* foilXY_f;
  TH2F* decayZb;
  TH2F* decayZf;
  TH2F* decayZr;
  TF1* myfit;
  TF1* exp1;
  TF1* exp2;


};
#endif
