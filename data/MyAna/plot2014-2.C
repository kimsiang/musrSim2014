void
plot2014_2()
{

 gStyle->SetOptStat(0000);

  char title1[50], title2[50], title3[50], title4[50], title5[50], title6[50];
  TCanvas *c1 = new TCanvas ("c1", "c1", 800, 600);

  sprintf (title1, "musr_200200.root.root");
  sprintf (title2, "musr_2500200.root.root");
  sprintf (title3, "musr_2500202.root.root");
  sprintf (title4, "musr_200600.root.root");
  sprintf (title5, "musr_2500600.root.root");
  sprintf (title6, "musr_2500602.root.root");

  TFile *f[6];

  f[0] = new TFile (title1);
  f[1] = new TFile (title2);
  f[2] = new TFile (title3);
  f[3] = new TFile (title4);
  f[4] = new TFile (title5);
  f[5] = new TFile (title6);


  TH1F *h[6];

  for (int i = 0; i < 6; i++)
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
      h[i]->GetXaxis ()->SetRangeUser (-0.2, 12);
//  h[i] ->Scale(h[0]->GetBinContent(101)/h[i]->GetBinContent(101));
    }
 
      h[0]->SetTitle("Downstream detector"); 
      h[0]->GetXaxis()->SetTitle("time [#mus]"); 
      h[0]->GetYaxis()->SetTitle("count"); 

      h[0]->SetLineColor (1);
      h[1]->SetLineColor (2);
      h[2]->SetLineColor (3);
      h[3]->SetLineColor (4);
      h[4]->SetLineColor (6);
      h[5]->SetLineColor (7);

  leg_hist = new TLegend (0.33, 0.13, 0.68, 0.35);
  leg_hist->AddEntry (h[0], " 20 K - 2 mm ", "lp");
  leg_hist->AddEntry (h[1], "250 K - 2 mm - Adsorbed", "lp");
  leg_hist->AddEntry (h[2], "250 K - 2 mm - Diffuse", "lp");
  leg_hist->AddEntry (h[3], " 20 K - 2 mm", "lp");
  leg_hist->AddEntry (h[4], "250 K - 6 mm - Adsorbed", "lp");
  leg_hist->AddEntry (h[5], "250 K - 6 mm - Diffuse", "lp");
  leg_hist->SetFillColor (0);
// leg_hist->SetFontsStyle (2);
  leg_hist->SetLineColor (1);
  leg_hist->SetShadowColor (0);
  leg_hist->Draw ();

}
