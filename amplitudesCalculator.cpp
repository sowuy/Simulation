#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <random>

using namespace std;
//pi Definition
const double PI = 4*atan(1);


//Shorthand notation to make the code more understadable and to allow for
//drop-in replacement by another C++11 random number generator.
typedef mt19937 Generator;

//A fonction that generate a random position within a certain rectangle
double getRandom(Generator& generator){
	return generate_canonical<double, 32>(generator);

}

double getRandomInRange(Generator& generator, double x0, double length){
	return length*getRandom(generator) + x0;

}


/**************************************************************************************/

vector <double> misalignment (double delta, vector <double> aligned, int detectorPlan){


	vector <double> outputVector;
	for(unsigned int i=0;i<aligned.size();i++){
		aligned[i] = aligned[i] + delta; 
		outputVector.push_back(aligned[i]);
	}       

	return outputVector;



}

/****************************************************************************************/

pair<vector   <double>, vector<double> > generalCase(vector <double> x1, vector <double> y2, vector <double> x3, vector <double> y4, double w, double delta1, double delta2, double delta3, double delta4){
	if(x1.size() == 0 || x1.size() != y2.size() || x1.size() != x3.size() 
			|| x1.size()!= y4.size()){
		cerr << "Error with data." << endl;
		cerr << "The files must contain the same number(>0) of values." << endl;
		cerr << "Data01 : " << x1.size() << " read values" << endl;
		cerr << "Data02 : " << y2.size() << " read values" << endl;
		cerr << "Data03 : " << x3.size() << " read values" << endl;
		cerr << "Data04 : " << y4.size() << " read values" << endl;
		exit(EXIT_FAILURE);
	}

	double x, y,z,r;
	vector<double> rho(x1.size()), theta(x1.size());
	vector<double> rhoInDeg(x1.size()), thetaInDeg(x1.size());

	vector<double> x1Mis = misalignment(delta1,x1,1);
	vector<double> y2Mis = misalignment(delta2,y2,2);
	vector<double> x3Mis = misalignment(delta3,x3,3);
	vector<double> y4Mis = misalignment(delta4,y4,4);
	;
	for(unsigned int i=0; i< x1.size(); i++){

		x = x3Mis[i] - x1Mis[i];
		y = y4Mis[i] - y2Mis[i];
		z = w + 7.4;
		r = sqrt(x * x + y * y + z * z);

		rho[i] = x == 0.0 ? 0.0 : atan(y / x);
		theta[i] = acos(z / r);
		rhoInDeg[i]= rho[i]*180/PI;
		thetaInDeg[i]= theta[i]*180/PI;


	}

	return make_pair(rhoInDeg, thetaInDeg); 
}


/*****************************************************************************************/
void writeFile(string filename, vector<double> v){
	ofstream outFile(filename.c_str());

	if(!outFile.is_open()){
		std::cerr << "Error while writing the file \'" << filename << "\'" << endl;
		return;
	}

	for(unsigned int i=0; i< v.size(); i++)
		outFile << v[i] << endl;

	outFile.close();
}
/******************************************************************************************/
vector<vector <double> > readFile(string filename){
	vector<double> line;
	vector<vector<double> > matrix;
	double value;

	ifstream myFile(filename.c_str());
	if(!myFile.is_open()){
		cerr << "Error while opening the file \'" << filename << "\'." << endl;
		exit(EXIT_FAILURE);
	}

	if(!myFile.good()){
		cerr << "Error with the file \'" << filename << "\'."<< endl;
		cerr << "Reading cancelled." << endl;
		exit(EXIT_FAILURE);
	}

	while(!myFile.eof()){
		myFile >> value;
		line.push_back(value);
		if(myFile.peek() == '\n'){
			matrix.push_back(line);
			line.clear();
		}
	} 

	myFile.close();

	return matrix;
}
/****************************************************************************************/
string getHelpPage(char* scriptName){
	string name(scriptName);
	string out = "Usage: " + name + " -w w  file \n";
	out += "\t-w w\t Gap between detectors\n";
	out += "\tfile\t file containing data\n";

	out += "The program applies the following formulas :\n";
	out += "All rho will be printed in the outfile \'rho_X\' and all theta\n";
	out += "in the outfile \'theta_X\' (where X is the initial outfile name).\n";
	return out;
}


/*************************************************************************************/

/*vector<double> conversion(vector<double> stripNumber){
  vector<double> position;
  double stripWidth=0.9;
  double interstrip = 0.15;
  double firstStrip = 0.45;
  double strip=stripNumber[0];
  double value=0;
  double lengthVector = stripNumber.size();
  for(int i=0;i<lengthVector;i++){
  value = firstStrip + (stripNumber[i]-1)*(stripWidth+interstrip);
  position.push_back(value); 
  }

  return position;


  }*/

/*****************************************************************************************/
double conversion(double stripNumber){
	double position;
	double stripWidth=0.9;
	double interstrip = 0.15;
	double firstStrip = 0.45;

	position = firstStrip + (stripNumber-1)*(stripWidth+interstrip);

	return position;


}
/*************************************************************************************************************************************************************************************************************************************************************************************/


int main(int argc, char** argv){


	    // Start with random seed
	    random_device rd;
	    Generator generator(rd());
	
            // Get the thing started
            generator.discard(100);


            int opt;
            char* endptr;

	string outfileName1 = "alignedAmplitudes.txt";
	string outfileName2 = "misalignedAmplitudes.txt";

	string outfileName3 = "misalignEffect.txt";


	vector < vector <double> > dataIn;

	double w = -1;

	const double delta1 = getRandomInRange(generator,-1,2);
	const double delta2 = getRandomInRange(generator,-1,2);

	const double delta3 =  getRandomInRange(generator,-1,2);


	const double delta4 = getRandomInRange(generator,-1,2);



	cout << "delta1 = " << delta1 << endl;
	cout << "delta2 = " << delta2 << endl;
	cout << "delta3 = " << delta3 << endl;
	cout << "delta4 = " << delta4 << endl;




	string filename;
	vector<double> data01, data02, data03, data04, outputS;

	double data1, data2, data3, data4;
	pair<vector<double>, vector<double> > outputAligned;
	pair<vector<double>, vector<double> > outputMisaligned;
	pair<vector<double>, vector<double> > outputDifference;


	while((opt = getopt(argc, argv, "w:h")) != -1){
		switch(opt){
			case 'w':
				endptr = optarg;
				w = strtof(optarg,&endptr);
				if(optarg == endptr || w<0){
					cerr << "invalid value for option -w" << endl;
					return EXIT_FAILURE;
				}
				break;
			case 'h':
				cout << getHelpPage(argv[0]);
				return EXIT_SUCCESS;
			default:
				cerr << getHelpPage(argv[0]);
				return EXIT_FAILURE;
		}
	}

	if(argc < 2){
		cerr << "Some arguments (or options) are missing" << endl;
		cerr << "\n" << getHelpPage(argv[0]);
		return EXIT_FAILURE;
	}

	if( w == -1){
		cerr << "The options -w must be set !" << endl;
		cerr << "\n" << getHelpPage(argv[0]);
		return EXIT_FAILURE;
	}


	filename = argv[optind];

	cout << "Reading file..." << endl;

	dataIn = readFile(filename);


	// Aligned detectors configuration

	for(int i=0; i<dataIn.size();i++){
		if(dataIn[i].size()!=4){
			cerr<<"Data n° "<< (i+1)<< " do not have 4 values. \nData ignored."<<endl;
		}

		else{

			data1 = conversion(dataIn[i][0]);
			data2 = conversion(dataIn[i][1]);
			data3 = conversion(dataIn[i][2]);
			data4 = conversion(dataIn[i][3]);

			data01.push_back(data1); 
			data02.push_back(data2); 
			data03.push_back(data3); 
			data04.push_back(data4); 



		}
	}
	//cout << "Calculating the amplitudes in aligned case.." << endl;
	outputAligned = generalCase(data01, data02, data03, data04,w,0,0,0,0);
	//cout << "Writing the results (1/2)..." << endl;
	//writeFile("rho_"+outfileName1, outputAligned.first);
	//cout << "Writing the results (2/2)..." << endl;
	//writeFile("theta_"+outfileName1, outputAligned.second);

	// Misaligned detectors configuration with random delta in x and y

	for(int i=0; i<dataIn.size();i++){
		if(dataIn[i].size()!=4){
			cerr<<"Data n° "<< (i+1)<< " do not have 4 values. \nData ignored."<<endl;
		}

		else{

			data1 = conversion(dataIn[i][0]);
			data2 = conversion(dataIn[i][1]);
			data3 = conversion(dataIn[i][2]);
			data4 = conversion(dataIn[i][3]);

			data01[i]=data1; 
			data02[i]=data2; 
			data03[i]=data3; 
			data04[i]=data4; 



		}
	}
	//cout << "Calculating the amplitudes in misaligned case..." << endl;
	outputMisaligned = generalCase(data01, data02, data03, data04,w,delta1,delta2,delta3,delta4);
	cout << "length data01 : " << data01.size() << endl;
	//cout << "Writing the results (1/2)..." << endl;
	//writeFile("rho_"+outfileName2, outputMisaligned.first);
	//cout << "Writing the results (2/2)..." << endl;
	//writeFile("theta_"+outfileName2, outputMisaligned.second);

	outputDifference.first = vector<double>(outputMisaligned.first.size());
	outputDifference.second = vector<double>(outputMisaligned.first.size());

	for(unsigned int k = 0; k < outputAligned.first.size();k++){
	    outputDifference.first[k] = outputMisaligned.first[k] - outputAligned.first[k];
	    outputDifference.second[k] = outputMisaligned.second[k] - outputAligned.second[k];
	    	}
//cout << "Writing the results (1/2)..." << endl;
	    writeFile("rho_"+outfileName3, outputDifference.first);
	    //cout << "Writing the results (2/2)..." << endl;
	    writeFile("theta_"+outfileName3, outputDifference.second);

	return EXIT_SUCCESS;
}
