#include "TCanvas.h"

#include "TROOT.h"
#include "TGraphErrors.h"

#include "TF1.h"

#include "TLegend.h"



int plot(){
    auto c=new TCanvas();c->SetGrid();
    TMultiGraph *mg = new TMultiGraph();

    //TH100
    TGraphErrors* plot = new TGraphErrors("eff0.txt","%lg %lg %lg");
    plot->SetMarkerStyle(20);
    plot->SetMarkerSize(0.8);
    plot->SetMarkerColor(kGreen-3);
    plot->SetLineColor(kGreen-3);
    plot->SetLineWidth(2);

    mg->Add(plot);

    //TH105

    TGraphErrors* plot2 = new TGraphErrors("angular0.txt","%lg %lg %lg");
    plot2->SetMarkerStyle(20);
    plot2->SetMarkerSize(0.8);
    plot2->SetMarkerColor(kOrange+7);
    plot2->SetLineColor(kOrange+7);
    plot2->SetLineWidth(2);

    mg->Add(plot2);

    
    
    mg->SetTitle("Acceptance and angular resolution studies (normalized)");
    gPad->Update();
    gPad->Modified();


     mg->Draw("ACP"); 
mg->GetXaxis()->SetTitle("Distance between detectors (cm)");
     


    TLegend *leg = new TLegend(.15,.25,.4,.15,"Curves");
    leg->SetFillColor(0);
    leg->AddEntry(plot, "Acceptance ", "l");
    leg->AddEntry(plot2, "Angular resolution : #frac{1}{#sigma_{#theta}}", "l");
   
    
    leg->DrawClone("Same");    

    //plot->Print();
    return 0;

}
