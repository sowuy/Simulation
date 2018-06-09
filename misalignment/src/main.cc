#include "../include/fonctions.h"
#include <sstream>

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

using namespace std;

int main(){

    string ROOTName = "CosmicMuonSimulation.root";
    TFile * ROOTFile = new TFile(ROOTName.c_str(),"recreate");

    //Write results into a csv file

    string CSVName = "CosmicMuonSimulation.csv";
    ofstream CSVFile(CSVName.c_str(), ios::out);

    for(unsigned int a=0;a<10;a+=5){
        
        double alpha=a*PI/180.;



        /** PROGRAM CODE **/
        // Start with random seed
        random_device rd;
        Generator generator(rd());

        // Get the thing started
        generator.discard(100);

        //Definitions of the coordinates and of the cosmic direction
        Point muonPos,ScreenPos, ScreenPosALL, muonRPC1, muonRPC2, muonRPC3, muonRPC4;
        Direction direction;

        //List of root IDs and root Titles for all triggered muons

        string scr_profilIDALL = "scr_prof_all" + intTostring(a); 
        string scr_profilIDXALL = "scr_prof_X_all" + intTostring(a)   ;
        string scr_profilIDYALL = "scr_prof_Y_all" + intTostring(a);
        string scr_profilTitleALL = "All muon hit profil on the horizontal screen";


        string muondirIDALL = "directionALL"+ intTostring(a);
        string muondirIDTALL = "direction_theta_all"+ intTostring(a);
        string muondirIDPALL = "direction_phi_all"+ intTostring(a) ;
        string muondirTitleALL = "All muon direction components";

        TH2F* ScreenProfilALL = new TH2F(scr_profilIDALL.c_str(),scr_profilTitleALL.c_str(),40,-100,100,40,-100,100);
        TH1F* ScreenProfilXALL = new TH1F(scr_profilIDXALL.c_str(),scr_profilTitleALL.c_str(),40,-100,100);
        TH1F* ScreenProfilYALL = new TH1F(scr_profilIDYALL.c_str(),scr_profilTitleALL.c_str(),40,-100,100);
        TH2F* MuonDirALL = new TH2F(muondirIDALL.c_str(),muondirTitleALL.c_str(),10,0.,90.,40,0.,360.);
        TH1F* MuonDirTALL = new TH1F(muondirIDTALL.c_str(),muondirTitleALL.c_str(),10,0.,90.);
        TH1F* MuonDirPALL = new TH1F(muondirIDPALL.c_str(),muondirTitleALL.c_str(),40,0.,360.);

        //List of root IDs and root Titles for all triggered muons

        string scr_profilID = "scr_prof"+ intTostring(a); 
        string scr_profilIDX = "scr_prof_X"+ intTostring(a)    ;
        string scr_profilIDY = "scr_prof_Y"+ intTostring(a) ;
        string scr_profilTitle = "Triggered muon hit profil on the horizontal screen";
        string muondirID = "direction"+ intTostring(a);
        string muondirIDT = "direction_theta" + intTostring(a);
        string muondirIDP = "direction_phi" + intTostring(a);
        string muondirTitle = "Triggered muon direction components";



        TH2F* ScreenProfil = new TH2F(scr_profilID.c_str(),scr_profilTitle.c_str(),40,-100,100,40,-100,100);
        TH1F* ScreenProfilX = new TH1F(scr_profilIDX.c_str(),scr_profilTitle.c_str(),40,-100,100);
        TH1F* ScreenProfilY = new TH1F(scr_profilIDY.c_str(),scr_profilTitle.c_str(),40,-100,100);
        TH2F* MuonDir = new TH2F(muondirID.c_str(),muondirTitle.c_str(),10,0.,90.,40,0.,360.);
        TH1F* MuonDirT = new TH1F(muondirIDT.c_str(),muondirTitle.c_str(),10,0.,90.);
        TH1F* MuonDirP = new TH1F(muondirIDP.c_str(),muondirTitle.c_str(),40,0.,360.);





        unsigned int Nmuons = 1e4;  //The number of muons to generate


        unsigned int n = 0;



        while(n<Nmuons){
            muonPos = getRandomMuonPosition(generator);
            direction = getRandomDirection(generator);


            ScreenPosALL = getHitPosition(muonPos,direction,"SCREEN");
            ScreenProfilALL->Fill(ScreenPosALL.x,ScreenPosALL.y);
            ScreenProfilXALL->Fill(ScreenPosALL.x);
            ScreenProfilYALL->Fill(ScreenPosALL.y);

            MuonDirALL->Fill(direction.first*180./PI, direction.second*180./PI);
            MuonDirTALL->Fill(direction.first*180./PI);
            MuonDirPALL->Fill(direction.second*180./PI);

            bool in_RPC1 = isInrpc(muonPos,direction,alpha,"RPC1");
            bool in_RPC2 = isInrpc(muonPos,direction,alpha,"RPC2");
            bool in_RPC3 = isInrpc(muonPos,direction,alpha,"RPC3");
            bool in_RPC4 = isInrpc(muonPos,direction,alpha,"RPC4");


            bool in_trigger = in_RPC1 && in_RPC2 && in_RPC3 && in_RPC4  ;

            if (in_trigger){

                ScreenPos = getHitPosition(muonPos,direction,alpha,"SCREEN");
                ScreenProfil->Fill(ScreenPos.x,ScreenPos.y);
                ScreenProfilX->Fill(ScreenPos.x);
                ScreenProfilY->Fill(ScreenPos.y);

                MuonDir->Fill(direction.first*180./PI, direction.second*180./PI);
                MuonDirT->Fill(direction.first*180./PI);
                MuonDirP->Fill(direction.second*180./PI);

                muonRPC1 = getHitPosition(muonPos,direction,alpha,"RPC1");
                muonRPC2 = getHitPosition(muonPos,direction,alpha,"RPC2");
                muonRPC3 = getHitPosition(muonPos,direction,alpha,"RPC3");
                muonRPC4 = getHitPosition(muonPos,direction,alpha,"RPC4");



                CSVFile << fmod((direction.first*180./PI),90.) << '\t'
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
                    << muonRPC4.z << '\t'
                    << floor(muonRPC1.x+8) << '\t'
                    << floor(muonRPC1.y+8) << '\t'
                    << floor(muonRPC2.x+8) << '\t'
                    << floor(muonRPC2.y+8) << '\t'
                    << floor(muonRPC3.x+8) << '\t'
                    << floor(muonRPC3.y+8) << '\t'
                    << floor(muonRPC4.x+8) << '\t'
                    << floor(muonRPC4.y+8) << '\n';



                n++;

            }


        }
        cout << endl;






        //Write histos
        ScreenProfilALL->Write();
        ScreenProfilXALL->Write();
        ScreenProfilYALL->Write();
        MuonDirALL->Write();
        MuonDirTALL->Write();
        MuonDirPALL->Write();



        ScreenProfil->Write();
        ScreenProfilX->Write();
        ScreenProfilY->Write();
        MuonDir->Write();
        MuonDirT->Write();
        MuonDirP->Write();


    }
    CSVFile.close();
    ROOTFile->Close();



    return 0;

}


