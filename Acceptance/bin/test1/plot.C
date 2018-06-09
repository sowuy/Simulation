#include "TCanvas.h"

#include "TROOT.h"
#include "TGraphErrors.h"

#include "TF1.h"

#include "TLegend.h"



int plot(){
    auto c=new TCanvas();c->SetGrid();
    TMultiGraph *mg = new TMultiGraph();

    //TH100
    TGraph* plot = new TGraph("efficiency0.txt");
    plot->SetMarkerStyle(20);
    plot->SetMarkerSize(0.8);
    plot->SetMarkerColor(kGreen-3);
    plot->SetLineColor(kGreen-3);
    plot->SetLineWidth(3);

    mg->Add(plot);

    //TH105

    TGraph* plot2 = new TGraph("angularResolution0.txt");
    plot2->SetMarkerStyle(20);
    plot2->SetMarkerSize(0.8);
    plot2->SetMarkerColor(kOrange+7);
    plot2->SetLineColor(kOrange+7);
    plot2->SetLineWidth(3);

    mg->Add(plot2);

    
    
    mg->SetTitle("Efficiency and angular resolution studies (normalized)");
    gPad->Update();
    gPad->Modified();


     mg->Draw("ACP"); 
mg->GetXaxis()->SetTitle("Distance between detectors (cm)");
     


    TLegend *leg = new TLegend(.15,.25,.4,.15,"Profils");
    leg->SetFillColor(0);
    leg->AddEntry(plot, "Efficiency curve", "l");
    leg->AddEntry(plot2, "Angular resolution curve", "l");
   
    
    leg->DrawClone("Same");    

    //plot->Print();
    return 0;

}
