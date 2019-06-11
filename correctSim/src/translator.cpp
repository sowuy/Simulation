#TRANSLATOR FROM DECIMAL TO BINARY FILE
#USAGE : compilatio : g++ translator.cpp -o translator
#GOAL : Convert simulation decimal output datafiles to binary raw output format (data format) in order to run reconstruction code (reader.cpp) on it and compare apples to apples.



#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

vector<vector <int> > readFile(string filename){
	vector<int> line;
	vector<vector <int> > matrix;
	int value;
	
	ifstream myFile(filename.c_str(), ios::in);
	if(!myFile.is_open()){
		cerr << "Error while opening the file \'" << filename << "\'." << endl;
		exit(EXIT_FAILURE);
	}

	if(!myFile.good()){
		cerr << "Error with the file \'" << filename << "\'." << endl;
		cerr << "Reading cancelled." << endl;
		exit(EXIT_FAILURE); 
	}
	
	while(!myFile.eof()){
		myFile >> value;
		line.push_back(value);
		if(myFile.peek() == '\n') {
			matrix.push_back(line);
			line.clear();
		}
	}

	myFile.close();
	
	return matrix;
}

vector<int16_t> getOutput(vector< vector <int> > matrix){
	vector<int16_t> out;
	int16_t nb_part1;
	int16_t nb_part2;
	int16_t nb_part3;
	int16_t nb_part4;
	int16_t nb;
	int16_t time = 0;
	for(int i=0; i<matrix.size(); i++){
		if(matrix[i].size() != 4){
			cerr << "Data n°" << (i+1) << " do not have 4 values.\nData ignored." << endl;
		}
		else{
			nb_part1 = 1 << (matrix[i][0]);
			nb_part2 = 1 << (matrix[i][1]);	
			nb_part3 = 1 << (matrix[i][2]);
			nb_part4 = 1 << (matrix[i][3]);
			out.push_back(nb_part4);
			out.push_back(nb_part3);
			out.push_back(nb_part2);
			out.push_back(nb_part1);
			out.push_back(time);
			out.push_back(time);
			out.push_back(time);
			out.push_back(time);
		}
	}

	return out;
}

void writeBinaryFile(string filename, vector<int16_t> data){
	ofstream outFile(filename.c_str(), ios::out | ios::binary);
	if(!outFile.is_open()){
		cerr << "Error while opening the outfile \'" << filename << "\'" << endl;
		exit(EXIT_FAILURE);
	}

	if(!outFile.good()){
		cerr << "Error with the outfile \'" << filename << "\'" << endl;
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<data.size(); i++){
		outFile.write((char*) &data[i], sizeof(int16_t));
	}
	
	outFile.close();
}

int main(){
	string infile = "decTohexa.txt";
	string outfile = "data.dat";
	vector< vector <int> > dataIn; 
	vector<int16_t> dataOut;

	cout << "Reading infile (\'" << infile << "\')..." << endl;
	dataIn = readFile(infile);
	cout << "Computing the data..." << endl;
	dataOut = getOutput(dataIn);
	cout << "Writing outfile (\'" << outfile << "\')..." << endl;
	writeBinaryFile(outfile, dataOut);
	return EXIT_SUCCESS;
}
