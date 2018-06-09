#include "../include/fonctions.h"
#include <sstream>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

using namespace std;

int main(int argc, char *argv[]){

    stringstream converter;
    converter << argv[0];
    string program;
    converter >> program;
    converter.clear();

    if(argc != 3){
        cout << "Expects to have 3 parameters\n";
        cout << "[Offline] USAGE is : " << program << " Hoffset_low Hoffset_high\n";
        return -1;

    } else if(argc == 3){
        int Hoffset_low = 0;
        int Hoffset_high = 0;

        converter << argv[1];
        converter >> Hoffset_low;
        converter.clear();

        converter << argv[2];
        converter >> Hoffset_high;
        converter.clear();

        random_device rd0;
        Generator generator0(rd0());

        // Get the thing started
        generator0.discard(100);




        for(int h=Hoffset_low; h<=Hoffset_high; h++){
            for(int i=0;i<5;i++){
                double w = i*3.7;

                string ROOTName = "Distance-dependency_" +intTostring(h)+"_" + intTostring(w+3.7)+".root";
                TFile * ROOTFile = new TFile(ROOTName.c_str(),"recreate");

                //Write results into a csv file

                string CSVName = "Distance-dependency_" +intTostring(h)+"_" + intTostring(w+3.7)+".csv";
                ofstream CSVFile(CSVName.c_str(), ios::out);



                /** PROGRAM CODE **/
                // Start with random seed
                random_device rd;
                Generator generator(rd());

                // Get the thing started
                generator.discard(100);

                //Definitions of the coordinates and of the cosmic direction
                Point muonPos,ScreenPos,  muonRPC1, muonRPC2, muonRPC3, muonRPC4;
                Direction direction;

                //List of root IDs and root Titles for all triggered muons

                string scr_profilID = "scr_prof"; 
                string scr_profilIDX = "scr_prof_X"    ;
                string scr_profilIDY = "scr_prof_Y" ;
                string scr_profilTitle = "Triggered muon hit profil on the horizontal screen";
                string grd_profilID = "grd_prof"; 
                string grd_profilIDX = "grd_prof_X"    ;
                string grd_profilIDY = "grd_prof_Y" ;
                string grd_profilTitle = "Triggered muon hit profil on the ground";

                string muondirID = "direction";
                string muondirIDT = "direction_theta" ;
                string muondirIDP = "direction_phi" ;
                string muondirTitle = "Triggered muon direction components";



                TH2F* ScreenProfil = new TH2F(scr_profilID.c_str(),scr_profilTitle.c_str(),40,-50,50,40,-50,50);
                TH1F* ScreenProfilX = new TH1F(scr_profilIDX.c_str(),scr_profilTitle.c_str(),40,-50,50);
                TH1F* ScreenProfilY = new TH1F(scr_profilIDY.c_str(),scr_profilTitle.c_str(),40,-50,50);
                TH2F* GroundProfil = new TH2F(grd_profilID.c_str(),grd_profilTitle.c_str(),40,-20,20,40,-20,20);
                TH1F* GroundProfilX = new TH1F(grd_profilIDX.c_str(),grd_profilTitle.c_str(),40,-20,20);
                TH1F* GroundProfilY = new TH1F(grd_profilIDY.c_str(),grd_profilTitle.c_str(),40,-20,20);

                TH2F* MuonDir = new TH2F(muondirID.c_str(),muondirTitle.c_str(),10,0.,90.,40,0.,360.);
                TH1F* MuonDirT = new TH1F(muondirIDT.c_str(),muondirTitle.c_str(),10,0.,90.);
                TH1F* MuonDirP = new TH1F(muondirIDP.c_str(),muondirTitle.c_str(),40,0.,360.);



                //List of root IDs and root Titles for triggered forward muons
                string scr_profilIDF = "scr_prof_f_" ;
                string scr_profilIDXF = "scr_prof_X_f_" ;
                string scr_profilIDYF = "scr_prof_Y_f_" ;
                string scr_profilTitleF = "Forward muon hit profil on the  horizontal screen";
                string grd_profilIDF = "grd_prof_f_" ;
                string grd_profilIDXF = "grd_prof_X_f_" ;
                string grd_profilIDYF = "grd_prof_Y_f_" ;
                string grd_profilTitleF = "Forward muon hit profil on the ground";

                string muondirIDF = "direction_f_" ;
                string muondirIDTF = "direction_theta_f_" ;
                string muondirIDPF = "direction_phi_f_" ;
                string muondirTitleF = "Triggered forward muon direction components";

                TH2F* ScreenProfilF = new TH2F(scr_profilIDF.c_str(),scr_profilTitleF.c_str(),40,-50,50,40,-50,50);
                TH1F* ScreenProfilXF = new TH1F(scr_profilIDXF.c_str(),scr_profilTitleF.c_str(),40,-50,50);
                TH1F* ScreenProfilYF = new TH1F(scr_profilIDYF.c_str(),scr_profilTitleF.c_str(),40,-50,50);
                TH2F* GroundProfilF = new TH2F(grd_profilIDF.c_str(),grd_profilTitleF.c_str(),40,-20,20,40,-20,20);
                TH1F* GroundProfilXF = new TH1F(grd_profilIDXF.c_str(),grd_profilTitleF.c_str(),40,-20,20);
                TH1F* GroundProfilYF = new TH1F(grd_profilIDYF.c_str(),grd_profilTitleF.c_str(),40,-20,20);

                TH2F* MuonDirF = new TH2F(muondirIDF.c_str(),muondirTitleF.c_str(),10,0.,90.,40,0.,360.);
                TH1F* MuonDirTF = new TH1F(muondirIDTF.c_str(),muondirTitleF.c_str(),10,0.,90.);
                TH1F* MuonDirPF = new TH1F(muondirIDPF.c_str(),muondirTitleF.c_str(),40,0.,360.);

                //List of root IDs and root Titles for triggered backward muons
                string scr_profilIDB = "scr_prof_b_" ;
                string scr_profilIDXB = "scr_prof_X_b_" ;
                string scr_profilIDYB = "scr_prof_Y_b_" ;
                string scr_profilTitleB = "Backward muon hit profil on the horizontal screen";
                string grd_profilIDB = "grd_prof_b_" ;
                string grd_profilIDXB = "grd_prof_X_b_" ;
                string grd_profilIDYB = "grd_prof_Y_b_" ;
                string grd_profilTitleB = "Backward muon hit profil on the groung";

                string muondirIDB = "direction_b_" ;
                string muondirIDTB = "direction_theta_b_" ;
                string muondirIDPB = "direction_phi_b_" ;
                string muondirTitleB = "Triggered backward muon direction components";

                TH2F* ScreenProfilB = new TH2F(scr_profilIDB.c_str(),scr_profilTitleB.c_str(),40,-50,50,40,-50,50);
                TH1F* ScreenProfilXB = new TH1F(scr_profilIDXB.c_str(),scr_profilTitleB.c_str(),40,-50,50);
                TH1F* ScreenProfilYB = new TH1F(scr_profilIDYB.c_str(),scr_profilTitleB.c_str(),40,-50,50);
                
                TH2F* GroundProfilB = new TH2F(grd_profilIDB.c_str(),grd_profilTitleB.c_str(),40,-20,20,40,-20,20);
                TH1F* GroundProfilXB = new TH1F(grd_profilIDXB.c_str(),grd_profilTitleB.c_str(),40,-20,20);
                TH1F* GroundProfilYB = new TH1F(grd_profilIDYB.c_str(),grd_profilTitleB.c_str(),40,-20,20);

                TH2F* MuonDirB = new TH2F(muondirIDB.c_str(),muondirTitleB.c_str(),10,0.,90.,40,0.,360.);
                TH1F* MuonDirTB = new TH1F(muondirIDTB.c_str(),muondirTitleB.c_str(),10,0.,90.);
                TH1F* MuonDirPB = new TH1F(muondirIDPB.c_str(),muondirTitleB.c_str(),40,0.,360.);





                unsigned int Nmuons = 1e4;  //The number of muons to generate
                float Stat = float(Nmuons);
                float progress =0.0;
                double muon_H = __RPC_D*2 + double(w) + __RPC_S;
                double RPC_W=__RPC_D+double(w);
                unsigned int n = 0;

                double TotalMuonNumber=0;
                double TriggeredMuonNumber=0;

                while(n<Nmuons){
                    muonPos = getRandomMuonPosition(generator,muon_H);
                    direction = getRandomDirection(generator);

                    TotalMuonNumber+=1;


                    bool in_RPC1 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC1");
                    bool in_RPC2 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC2");
                    bool in_RPC3 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC3");
                    bool in_RPC4 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC4");


                    bool in_trigger = in_RPC1 && in_RPC2 && in_RPC3 && in_RPC4  ;


                    if (in_trigger){

                        TriggeredMuonNumber+=1;

                        ScreenPos = getHitPosition(muonPos,direction,RPC_W,muon_H,"SCREEN");
                        ScreenProfil->Fill(ScreenPos.x,ScreenPos.y);
                        ScreenProfilX->Fill(ScreenPos.x);
                        ScreenProfilY->Fill(ScreenPos.y);

                        MuonDir->Fill(direction.first*180./PI, direction.second*180./PI);
                        MuonDirT->Fill(direction.first*180./PI);
                        MuonDirP->Fill(direction.second*180./PI);

                        muonRPC1 = getHitPosition(muonPos,direction,RPC_W,muon_H,"RPC1");
                        muonRPC2 = getHitPosition(muonPos,direction,RPC_W,muon_H,"RPC2");
                        muonRPC3 = getHitPosition(muonPos,direction,RPC_W,muon_H,"RPC3");
                        muonRPC4 = getHitPosition(muonPos,direction,RPC_W,muon_H,"RPC4");
                        GroundProfil->Fill(muonRPC4.x,muonRPC4.y);
                        GroundProfilX->Fill(muonRPC4.x);
                        GroundProfilY->Fill(muonRPC4.y);

                        if(direction.second < PI){
                            ScreenProfilF->Fill(ScreenPos.x,ScreenPos.y);
                            ScreenProfilXF->Fill(ScreenPos.x);
                            ScreenProfilYF->Fill(ScreenPos.y);

                            GroundProfilF->Fill(muonRPC4.x,muonRPC4.y);
                            GroundProfilXF->Fill(muonRPC4.x);
                            GroundProfilYF->Fill(muonRPC4.y);

                            MuonDirF->Fill(direction.first*180./PI, direction.second*180./PI);
                            MuonDirTF->Fill(direction.first*180./PI);
                            MuonDirPF->Fill(direction.second*180./PI);

                        } else {
                            ScreenProfilB->Fill(ScreenPos.x,ScreenPos.y);
                            ScreenProfilXB->Fill(ScreenPos.x);
                            ScreenProfilYB->Fill(ScreenPos.y);

                            GroundProfilB->Fill(muonRPC4.x,muonRPC4.y);
                            GroundProfilXB->Fill(muonRPC4.x);
                            GroundProfilYB->Fill(muonRPC4.y);

                            MuonDirB->Fill(direction.first*180./PI, direction.second*180./PI);
                            MuonDirTB->Fill(direction.first*180./PI);
                            MuonDirPB->Fill(direction.second*180./PI);

                        } 

                        //Write in the CSV file...

                        CSVFile/* << intTostring(h)<<'\t'
                            << w+3.7<<'\t'

                            *<< ScreenMeanF << '\t'
                              << ScreenRMSF << '\t'
                              << ScreenMaxF << '\t'
                              << ScreenIntF << '\t'
                              << ScreenMeanB << '\t'
                              << ScreenRMSB << '\t'
                              << ScreenMaxB << '\t'
                              << ScreenIntB << '\t'
                              << ScreenPeakDist << '\t'
                              << ScreenPeakRatio << '\t'
                              << ScreenIntRatio << '\n';

                            << fmod((direction.first*180./PI),90.) << '\t'
                            << fmod((direction.second*180./PI),360.) << '\t'
                            << ScreenPos.x << '\t'
                            << ScreenPos.y << '\t'
                            << ScreenPos.z << '\t'
                            << muonRPC1.x << '\t'
                            << muonRPC1.y << '\t'
                            << muonRPC1.z << '\t'
                            << muonRPC2.x << '\t'
                            << muonRPC2.y << '\t'
                            << muonRPC2.z << '\t'    
                            << muonRPC3.x << '\t'
                            << muonRPC3.y << '\t'
                            << muonRPC3.z << '\t'
                            << muonRPC4.x << '\t'
                            << muonRPC4.y << '\t'
                            << muonRPC4.z << '\t'*/
                            << floor(muonRPC1.x+8) << '\t'
                           // << floor(muonRPC1.y+8) << '\t'
                           // << floor(muonRPC2.x+8) << '\t'
                            << floor(muonRPC2.y+8) << '\t'
                            << floor(muonRPC3.x+8) << '\t'
                           // << floor(muonRPC3.y+8) << '\t'
                            //<< floor(muonRPC4.x+8) << '\t'
                            << floor(muonRPC4.y+8) << '\n';

                        n++;
                    }


                    //Print progress bar
                    progress = float(n/Stat);

                    int barWidth = 25;

                    cout << "Progress " << ROOTName ;
                    cout << " [";
                    int pos = barWidth * progress;
                    for (int i = 0; i < barWidth; ++i) {
                        if (i < pos) cout << "=";
                        else if (i == pos) cout << ">";
                        else cout << " ";

                    }
                    cout << "] " << int(progress * 100.0) << " %\r";
                    cout.flush();


                }
                cout << endl;  


                //Get screen variables

                /*  double ScreenMeanF = ScreenProfilYF->GetMean();
                    double ScreenRMSF = ScreenProfilYF->GetRMS();
                    double ScreenMaxF = ScreenProfilYF->GetMaximum();
                    double ScreenIntF = ScreenProfilYF->Integral();

                    double ScreenMeanB = ScreenProfilYB->GetMean();
                    double ScreenRMSB = ScreenProfilYB->GetRMS();
                    double ScreenMaxB = ScreenProfilYB->GetMaximum();
                    double ScreenIntB = ScreenProfilYB->Integral();

                //Calculate other results

                double ScreenPeakDist = abs(ScreenMeanF-ScreenMeanB);
                double ScreenPeakRatio = ScreenMaxB/ScreenMaxF;
                double ScreenIntRatio = ScreenIntB/ScreenIntF;*/




                ROOTFile->cd();
                //Write histos



                ScreenProfil->Write();
                ScreenProfilX->Write();
                ScreenProfilY->Write();
                GroundProfil->Write();
                GroundProfilX->Write();
                GroundProfilY->Write();
                MuonDir->Write();
                MuonDirT->Write();
                MuonDirP->Write();

                ScreenProfilF->Write();
                  ScreenProfilXF->Write();
                  ScreenProfilYF->Write();
                    GroundProfilF->Write();
                  GroundProfilXF->Write();
                  GroundProfilYF->Write();

                  MuonDirF->Write();
                  MuonDirTF->Write();
                  MuonDirPF->Write();

                  ScreenProfilB->Write();
                  ScreenProfilXB->Write();
                  ScreenProfilYB->Write();
                  GroundProfilB->Write();
                  GroundProfilXB->Write();
                  GroundProfilYB->Write();

                  MuonDirB->Write();
                  MuonDirTB->Write();
                  MuonDirPB->Write();

                CSVFile.close();
                ROOTFile->Close();

            }
        }
    }   
    return 0;

}


