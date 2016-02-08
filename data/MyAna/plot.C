void
plot ()
{

  char title1[50], title2[50], title3[50], title4[50], title5[50];
  TCanvas *c1 = new TCanvas ("c1", "c1", 1000, 500);

  sprintf (title1, "musr_2012021250.root.root");
  sprintf (title2, "musr_2012031250.root.root");
  sprintf (title3, "musr_2012051250.root.root");
  sprintf (title4, "musr_2012101250.root.root");
  sprintf (title5, "musr_2012141250.root.root");
  sprintf (title1, "musr_2012020.root.root");
  sprintf (title2, "musr_2012030.root.root");
  sprintf (title3, "musr_2012050.root.root");
  sprintf (title4, "musr_2012100.root.root");
  sprintf (title5, "musr_2012140.root.root");

  TFile *f[5];

  f[0] = new TFile (title1);
  f[1] = new TFile (title2);
  f[2] = new TFile (title3);
  f[3] = new TFile (title4);
  f[4] = new TFile (title5);


  TH1F *h[10];
  TH1F *etrig[10];
  c1->Divide (2, 1);


  c1->cd (1);
  for (int i = 0; i < 5; i++)
    {
      h[i] = (TH1F *) f[i]->FindObjectAny ("forward");
      etrig[i] = (TH1F *) f[i]->FindObjectAny ("etrig");
      cout<<"etrig: "<<etrig[i]->GetEntries()<<", Downstream: "<<h[i]->GetEntries()<<", Ratio(down/trig): "<<100*h[i]->GetEntries()/etrig[i]->GetEntries()<<endl;
      h[i]->Rebin (1);
/*      for (int k = 1; k < 1437; k++)
	{
	  h[i]->SetBinContent (k, h[i]->GetBinContent (k) / exp (-h[i]->GetBinCenter (k) / 2.198));
	}
*/
      if (i == 0)
	{
	  h[i]->Draw ("e");
	}
      h[i]->Draw ("sames");
      h[i]->SetLineColor (i + 1);
      h[i]->SetLineWidth (2);
      h[i]->GetXaxis ()->SetRangeUser (-0.2, 8);
//  h[i] ->Scale(h[0]->GetBinContent(101)/h[i]->GetBinContent(101));
    }


  c1->cd (2);
  for (int i = 0; i < 5; i++)
    {
      h[5 + i] = (TH1F *) f[i]->FindObjectAny ("backward");
      etrig[5+ i] = (TH1F *) f[i]->FindObjectAny ("etrig");
      cout<<"etrig: "<<etrig[5 +i]->GetEntries()<<", Upstream: "<<h[5+i]->GetEntries()<<", Ratio(up/trig): "<<100*h[5+i]->GetEntries()/etrig[5+i]->GetEntries()<<endl;
      h[5 + i]->Rebin (1);
      /*  for (int k = 1; k < 1437; k++)
         {
         h[5+i]->SetBinContent (k, h[5+i]->GetBinContent (k) / exp (-h[5+i]->GetBinCenter (k) / 2.198));
         }
       */ if (i == 0)
	{
	  h[5 + i]->Draw ();
	}
      h[5 + i]->Draw ("sames");
      h[5 + i]->SetLineColor (i + 1);
      h[5 + i]->SetLineWidth (2);
      h[5 + i]->GetXaxis ()->SetRangeUser (-0.2, 8);}

//  h[5]->GetYaxis ()->SetRangeUser (0, h[9]->GetBinContent (116) * 1.2);
//  h[0]->GetYaxis ()->SetRangeUser (0, h[4]->GetBinContent (116) * 1.2);
  h[4]->SetLineColor (6);
  h[9]->SetLineColor (6);


  h[0]->SetTitle (title1);
  h[1]->SetTitle (title2);
  h[2]->SetTitle (title3);
  h[3]->SetTitle (title4);
  h[4]->SetTitle (title5);
  h[5]->SetTitle (title1);
  h[6]->SetTitle (title2);
  h[7]->SetTitle (title3);
  h[8]->SetTitle (title4);
  h[9]->SetTitle (title5);
  h[9]->SetTitle (title5);



}
