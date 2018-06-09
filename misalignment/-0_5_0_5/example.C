#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "TH1.h"
#include "TH1F.h"
#include "TH1I.h"
using namespace std;

bool getLineFromFile(fstream & file,vector <float> & v){
  //Gets 1 line of data from the file and saves to "v"
  bool status = true;
  string line;
  status = (bool)getline(file,line);
  stringstream ss(line);
  float tmp = 0;
  while (ss>>tmp)
    v.push_back(tmp);
  return status;
}

vector < vector < float > > getData(fstream & file){
  // Gets data (assumed to be float) from file
  vector < vector < float > > data;
  vector < float > tmp;
  while(getLineFromFile(file,tmp)){
    data.push_back(tmp);
    tmp.clear();
  }
  return data;
}

void printLine( const vector <float>  & line){
  for (unsigned int i = 0; i < line.size(); i++){
    cout<<line[i]<<"-";
  }
  cout<<endl;
}


int example(string fName = ""){


    // Just checking the filename given makes sense
    if (fName == ""){
        cerr<<"Error, no filename given..."<<endl;
        return 1;
    }
    else
        cout<<"Will process "<<fName<<endl;

    fstream myFile(fName.c_str());
    if (! myFile.is_open()){
      cerr<<"Unable to open file..."<<endl;
      return 1;
    }

    // Getting the data
    vector < vector < float > > data = getData(myFile);
     
    // For example, I want to plot hist of the third column :
   
   
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111111); 
    TH1 * dataHist = new TH1I("dataHist","Misalignment study for -0.5 < #Delta_{x}, #Delta_{y} < 0.5",15,-30,30);
    for (unsigned int i = 0; i < data.size(); i++){
      vector < float > line = data[i];    
      if (line.size() ==0  ){
        cout<<"Ignoring line :"<<endl;
        printLine(line);
      }
      else{
        dataHist->Fill(line.at(0));
      }

    }
    dataHist->Draw();
    //dataHist->Fit("gaus");
    dataHist->GetYaxis()->SetTitle("Counts");
    dataHist->GetXaxis()->SetTitle("#theta-#theta_{True}");

    return 0;
}

 
