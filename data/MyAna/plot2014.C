void
plot2014 ()
{

    //   gStyle->SetOptStat(0000);
    gStyle->SetLabelFont(22,"xyz");
    gStyle->SetTextFont(22);
    gStyle->SetStatFont(22);
    gStyle->SetTitleFont(22,"xyz");
    gStyle->SetTitleFont(22,"h");
    gStyle->SetTitleSize(0.07,"h");
    gStyle->SetLegendFont(22);
    gROOT->ForceStyle();


    char title1[50], title2[50], title3[50], title4[50], title5[50], title6[50], title7[50];
    TCanvas *c1 = new TCanvas ("c1", "c1", 800, 600);
    TCanvas *c2 = new TCanvas ("c2", "c2", 800, 600);
    c2->Divide(2,2);

    /*  sprintf (title1, "musr_2500000.root.root");
        sprintf (title2, "musr_2500102.root.root");
        sprintf (title3, "musr_2500302.root.root");
        sprintf (title4, "musr_2500502.root.root");
        */
    sprintf (title1, "musr_119.root.root");
    sprintf (title2, "musr_117.root.root");
    sprintf (title3, "musr_114.root.root");
    sprintf (title4, "musr_109.root.root");

    TFile *f[4];

    f[0] = new TFile (title1);
    f[1] = new TFile (title2);
    f[2] = new TFile (title3);
    f[3] = new TFile (title4);


    TH1F *h[4];
    TH2F *h2[4];

    for (int i = 0; i < 4; i++)
    {
        c1->cd();
        h[i] = (TH1F *) f[i]->FindObjectAny ("forward");
        h2[i] = (TH2F *) f[i]->FindObjectAny ("decayXY");
        h[i]->Rebin (5);
        for (int k = 1; k < 1301; k++)
        {
            h[i]->SetBinContent (k, h[i]->GetBinContent (k) / exp (-h[i]->GetBinCenter (k) / 2.198));
        }

        if (i == 0)
        {
            h[i]->Draw ();
        }
        h[i]->Draw ("same");
        h[i]->SetLineWidth (2);
        h[i]->GetXaxis ()->SetRangeUser (-0.1, 5);
        h[i]->GetYaxis ()->SetRangeUser (-0.5, 3000);
        h[i]->GetXaxis ()->SetTitle ("time [#mus]");
        h[i]->GetYaxis ()->SetTitle ("count");

        c2->cd(i+1);
        c2->cd(i+1)->SetLogz();
        h2[i]->GetXaxis()->SetRangeUser (-20, 20);
        h2[i]->GetYaxis()->SetRangeUser (-20, 20);
        h2[i]->Draw("colz");
    }

    h2[0]->SetTitle("Decay XY (11.9 kV)");
    h2[1]->SetTitle("Decay XY (11.7 kV)");
    h2[2]->SetTitle("Decay XY (11.4 kV)");
    h2[3]->SetTitle("Decay XY (10.9 kV)");


    h[1]->Scale(h[0]->GetBinContent(21)/h[1]->GetBinContent(21));
    h[2]->Scale(h[0]->GetBinContent(21)/h[2]->GetBinContent(21));
    h[3]->Scale(h[0]->GetBinContent(21)/h[3]->GetBinContent(21));

    c1->cd();
    h[0]->SetTitle ("Downstream detector");
    h[1]->SetTitle ("Downstream detector");
    h[2]->SetTitle ("Downstream detector");
    h[3]->SetTitle ("Downstream detector");
    h[0]->SetName ("Downstreamdetector1");
    h[1]->SetName ("Downstreamdetector2");
    h[2]->SetName ("Downstreamdetector3");
    h[3]->SetName ("Downstreamdetector4");


    h[0]->SetLineColor (2);
    h[1]->SetLineColor (3);
    h[2]->SetLineColor (4);
    h[3]->SetLineColor (6);

    leg_hist = new TLegend (0.68, 0.68, 0.88, 0.88);
    /*  leg_hist->AddEntry (h[0], "250 K ", "l");
        leg_hist->AddEntry (h[1], "250 K - 1 mm - Diffuse reflection", "l");
        leg_hist->AddEntry (h[2], "250 K - 3 mm - Diffuse reflection", "l");
        leg_hist->AddEntry (h[3], "250 K - 5 mm - Diffuse reflection", "l");
        */  
    leg_hist->AddEntry (h[0], "V_{RA} = 11.9 kV", "l");
    leg_hist->AddEntry (h[1], "V_{RA} = 11.7 kV", "l");
    leg_hist->AddEntry (h[2], "V_{RA} = 11.4 kV", "l");
    leg_hist->AddEntry (h[3], "V_{RA} = 10.9 kV", "l");
    leg_hist->SetFillColor (0);
    leg_hist->SetLineColor (1);
    leg_hist->SetShadowColor (0);
    leg_hist->Draw ();

}
