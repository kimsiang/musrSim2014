void
plot2014_250K_sim2mm()
{
  gStyle->SetOptStat(0000);
 gStyle->SetLabelFont(22,"xyz");
 gStyle->SetTextFont(22);
 gStyle->SetStatFont(22);
 gStyle->SetTitleFont(22,"xyz");
 gStyle->SetTitleFont(22,"h");
 gStyle->SetTitleSize(0.07,"h");
 gStyle->SetLegendFont(22);
 gROOT->ForceStyle();



  char title1[50], title2[50], title3[50], title4[50], title5[50], title6[50];
  TCanvas *c1 = new TCanvas ("c1", "c1", 800, 600);

  sprintf (title1, "musr_200200.root.root");
  sprintf (title2, "musr_2500200.root.root");
  sprintf (title3, "musr_2500202.root.root");

  TFile *f[3];

  f[0] = new TFile (title1);
  f[1] = new TFile (title2);
  f[2] = new TFile (title3);


  TH1F *h[3];

  for (int i = 0; i < 3; i++)
    {
      h[i] = (TH1F *) f[i]->FindObjectAny ("forward");
      h[i]->Rebin (4);
      for (int k = 1; k < 1301; k++)
	{
	  h[i]->SetBinContent (k, h[i]->GetBinContent (k) / exp (-h[i]->GetBinCenter (k) / 2.198));
	}

      if (i == 0)
	{
	  h[i]->Draw ();
	}
      h[i]->Draw ("sames");
      h[i]->SetLineWidth (2);
      h[i]->GetXaxis ()->SetRangeUser (-0.5, 8);
//  h[i] ->Scale(h[0]->GetBinContent(101)/h[i]->GetBinContent(101));
    }
 
      h[0]->SetTitle("Downstream detector"); 
      h[0]->GetXaxis()->SetTitle("time [#mus]"); 
      h[0]->GetYaxis()->SetTitle("count"); 

      h[0]->SetLineColor (1);
      h[1]->SetLineColor (2);
      h[2]->SetLineColor (3);

  leg_hist = new TLegend (0.33, 0.13, 0.68, 0.35);
  leg_hist->AddEntry (h[0], "SiO2-porous/SiN-2mm/20K (sim)", "l");
  leg_hist->AddEntry (h[1], "SiO2-porous/SiN-2mm/250K (sim,adsorption)", "l");
  leg_hist->AddEntry (h[2], "SiO2-porous/SiN-2mm/250K (sim,reflection)", "l");
  leg_hist->SetFillColor (0);
// leg_hist->SetFontsStyle (2);
  leg_hist->SetLineColor (1);
  leg_hist->SetShadowColor (0);
  leg_hist->Draw ();

}
