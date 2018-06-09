{

 using namespace std;
 
 #define Ve  1e4                                             //Vitesse des électrons en m/s
 #define Vi  1e3                                             //Vitesse des ions en m/s
 #define q		1.602177e-19	                     //charge élémentaire en C
 #define L 0.002	                                     //Epaisseur du detecteur	
 double tMax =1e-6;
 double  Np = 9.38*pow(10,-5);                                             //Nombre de paires ions/électrons par couche
 double nCouches = 1000;                                     //nombre de couches
 double  dy = L/(double)nCouches ;                           //Largeur couche0
 
 double eps_0 = 8.85*pow(10,-12); // vacuum permittivity
 double eps_r = 5; //dielectric constant glass

 double alpha = 5500; //Townsend coefficient [1/m]
 double eta = 3500; //Attachement coefficient [1/m]
 double d = 0.0011;
 
 double tau = 0.007;//eps_0/sigma*((d+(eps_r*L))/L);
 double Te = L/Ve;
 double Ti = L/Vi;
 int nTimes = 500;
 double dt=tMax/(double)nTimes;
 double Qe=0;
 double Qi=0;	
 std::vector<double> ts;
 std::vector<double> Ie_ts;
 std::vector<double> Ii_ts;
 std::vector<double> It_ts;
 std::vector<double> Electron;
 std::vector<double> Ion;
 std::vector<double> Total;
 
 
 for(int j=0;j<nTimes;j++){
   double Ie=0;
   double Ii=0;
   double t=(double)j*dt;
   
    for(int i=0; i<nCouches ; i++){
        double y=(double)i*dy;

	bool addElectron=false;
	if (t<=Te*(y/L)) addElectron=true;
	bool addIon=false;
	if (t<=Ti*(1-(y/L))) addIon=true;
	
	if(addElectron) Ie+= (Np*q)*Ve*exp((alpha-eta)*Ve*Te)*(1/(2*d+L*eps_r))*(eps_r+((2*d/L)*(1-exp(-Te/tau)))) ;
	//cout << endl << endl<<endl<< "t="<< t << "    "<< "Couche: "<< y<< "    "<< "Ie_t=" << Ie << "   " << "Ii_t=" << Ii << endl;
	if(addIon) Ii+=(Np*q)*Vi*exp((alpha-eta)*Vi*Ti)*(1/(2*d+L*eps_r))*(eps_r+((2*d/L)*(1-exp(-Ti/tau)))) ;
	
    }
   
   Qe += Ie;
   Qi+= Ii;
   Ie_ts.push_back(Ie);
   Ii_ts.push_back(Ii);
   It_ts.push_back(Ie+Ii);
   ts.push_back(t);
   Electron.push_back(Qe);
   Ion.push_back(Qi);
   Total.push_back(Qe+Qi);
   //cout <<endl << endl<< "Total sur une couche: "<< "    " << "t="<<t<<"    "<<"Ie_t="<<Ie<<"   "<<"Ii_t="<<Ii<<"    "<<"It_t="<<Ie+Ii <<endl;
 }
 
 c1=new TCanvas("c1", "My Root Plots",1500,500);
 c1->Divide(2,1);
	   
 
 


c1->cd(1);
 
TGraph* g1= new TGraph(ts.size(), &ts[0],&Ie_ts[0]);
g1->SetLineColor(kRed);
g1->GetYaxis()->SetTitle("Current (A)");
g1->SetLineWidth(2);
g1->GetXaxis()->SetTitle("Time (s)");
g1->SetTitle ("Induced current in planar electrode geometry");
g1->Draw("ACP");

//c1->cd(2);
TGraph* g2 = new TGraph(ts.size(), &ts[0],&Ii_ts[0]);
g2->SetLineColor(kBlue);
g2->SetLineWidth(2);

g2->GetYaxis()->SetTitle("Current (A)");
g2->GetXaxis()->SetTitle("Time (s)");
g2->Draw("SAME");

//c1->cd(3);
TGraph* g3 = new TGraph(ts.size(), &ts[0], &It_ts[0]);
g3->SetLineColor(kGreen+2);
g3->SetLineWidth(2); 
g3->GetYaxis()->SetTitle("Current (A)");
g3->GetXaxis()->SetTitle("Time (s)");
g3->Draw("SAME");


TLegend* legend = new TLegend(0.6,0.7,0.9,0.9);
legend->SetHeader("Legend" ); // option "C" allows to center the header
legend->AddEntry(g1,"Electrons","l");
legend->AddEntry(g2,"Ions","l");
legend->AddEntry(g3,"Total","l");
legend->Draw();



  c1->cd(2);

  /*TH1D *histo=new TH1D("histo","Accumulated charge on electrodes;Temps (ns) ;Counts",100,0,1e-4);
for(int i=0; i<1e4;i++) {
  histo->Fill(Q);
  histo->Draw();*/

 c1->cd(2);
 TGraph* g4= new TGraph(ts.size(), &ts[0],&Electron[0]);
 g4->GetYaxis()->SetTitle("Q");
g4->GetXaxis()->SetTitle("Time (s)");
g4->SetTitle ("Induced Charge");
 g4->SetLineWidth(2);
 g4->SetLineColor(kRed);
 g4->Draw("ACP");

 TGraph* g5= new TGraph(ts.size(), &ts[0],&Ion[0]);
 g5->SetLineColor(kBlue);
 g5->SetLineWidth(2);
 g5->Draw("SAME");

 TGraph* g6= new TGraph(ts.size(), &ts[0],&Total[0]);
 g6->SetLineColor(kGreen+2);
 g6->SetLineWidth(2);
 g6->Draw("SAME");

TLegend* legend2 = new TLegend(0.6,0.7,0.9,0.9);
legend2->SetHeader("Legend" ); // option "C" allows to center the header
legend2->AddEntry(g4,"Electrons","l");
legend2->AddEntry(g5,"Ions","l");
legend2->AddEntry(g6,"Total","l");
legend2->Draw();
}
  
 






