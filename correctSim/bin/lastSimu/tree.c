#include "Riostream.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"


void tree(){

    TString dir = gSystem->UnixPathName("test.dat");
    dir.ReplaceAll("tree.C","");
    dir.ReplaceAll("/.","/");

    
    TFile *f = new TFile("test.root","RECREATE");
     
    TTree *T = new TTree("T", "data from csv file");
    Int_t currentIgnoreLevel = gErrorIgnoreLevel;
    T-> ReadFile("test.dat", "theta:phi:screenx:screeny:screenz:x1:y1:z1:x2:y2:z2:x3:y3:z3:x4:y4:z4:stripx1:stripy1:stripx2:stripy2:stripx3:stripy3:stripx4:stripy4");

    gErrorIgnoreLevel = currentIgnoreLevel;


      
    
    //f->Write();

}
