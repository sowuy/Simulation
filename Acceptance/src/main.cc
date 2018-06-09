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






                unsigned int Nmuons = 1e4;  //The number of muons to generate
                float Stat = float(Nmuons);
                float progress =0.0;
                double muon_H = __muon_H + double(h);
                double RPC_W=__RPC_D+double(w);
                unsigned int n = 0;

                double TotalMuonNumber=0;
                double TriggeredMuonNumber=0;
                double TriggeredMuonNumberInRPC4 = 0;

                while(n<Nmuons){
                    muonPos = getRandomMuonPosition(generator,muon_H);
                    direction = getRandomDirection(generator);

                    TotalMuonNumber+=1;


                    bool in_RPC1 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC1");
                    bool in_RPC2 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC2");
                    bool in_RPC3 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC3");
                    bool in_RPC4 = isInrpc(muonPos,direction,RPC_W,muon_H,"RPC4");


                    bool in_trigger = in_RPC1;
                    bool in_trigger2 =  in_RPC2 && in_RPC3 && in_RPC4 ;
 



                    if (in_trigger){

                        TriggeredMuonNumber+=1;
                        if (in_trigger2){
                            TriggeredMuonNumberInRPC4+=1;
                        }
                        //Write in the CSV file...


                        n++;
                    }


                    //Print progress bar
                    progress = float(n/Stat);

                    int barWidth = 25;

                    cout << "Progress " << CSVName ;
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

                CSVFile << TriggeredMuonNumberInRPC4/TriggeredMuonNumber<<'\t'
                        << (w+3.7)/0.9<<'\n';


                CSVFile.close();

            }
        }
    }   
    return 0;

}


