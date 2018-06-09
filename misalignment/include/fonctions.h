#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

//Define necessary variables
const double __RPC_L = 16.; //rpc «L»ength [mm]
const double __RPC_D = 5. ;  //«D»istance in between x&y rpc planes
const double __RPC_S = 2.; //Distance to the «S»creen (vertical distribution)
const double __RPC_W = 15; //Distance between the the 4 rpc planes
const double __muon_H  = 25; //top rpc plane «H»eight

//********************************************************************************************

//Function to cast an integer into a string
string intTostring(int value){
    string word;
    stringstream ss;
    ss << setw(2) << setfill('0') << value;
    ss >> word;

    return word;

}

//********************************************************************************************

//Definition of Coordinates
struct Point{
    double x;
    double y;
    double z;

};
typedef Point Vector;

//A (theta,phi) angle pair.
typedef std::pair<double,double> Direction;

//********************************************************************************************

//pi Definition
const double PI = 4*atan(1);

//********************************************************************************************

//function that builds a vector from 2 points
Vector makeVector(Point A, Point B){
    Vector AB;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AB.z = B.z - A.z;

    return AB;

}




//********************************************************************************************

//Shorthand notation to make the code more understadable and to allow for
//drop-in replacement by another C++11 random number generator.
typedef std::mt19937 Generator;

//A fonction that generate a random position within a certain rectangle
double getRandom(Generator& generator){
    return generate_canonical<double, 32>(generator);

}

double getRandomInRange(Generator& generator, double x0, double length){
    return length*getRandom(generator) + x0;

}

//********************************************************************************************

//A fonction that generates a cos^2 cosmics distribution
Direction getRandomDirection(Generator& generator){
    double phi = 2*PI*getRandom(generator);

    // Create cos²(theta) distribution
    double theta = PI*getRandom(generator)/2.;
    double test = getRandom(generator);

    while (test > cos(theta)*cos(theta)){
        theta = PI*getRandom(generator)/2.;
        test = getRandom(generator);

    }

    return make_pair(theta, phi);

}

//Generate a random hit in the cosmic plane that is defined to be situated
//right at the height of the lowest point of the rpcs via the
//variable height
Point getRandomMuonPosition(Generator& generator){
    Point muon;

    muon.x = getRandomInRange(generator, -50., 100.);
    muon.y = getRandomInRange(generator, -50., 100.);
    muon.z = __muon_H;

    return muon;

}

//********************************************************************************************

//Compute the hit position in the rpc planes knowing the equation of the planes
//calculated by hand and using the origin of the muon, its direction (details on calculation
//in the hand notebook)
Point getHitPosition(const Point& P, const Direction& D, string which){
    Point I;

    
    double t = 0.;

    if(which == "RPC1") t= ((__RPC_W+2*__RPC_D)-P.z)/cos(D.first);

    if(which == "RPC2") t= ((__RPC_W+__RPC_D)-P.z)/cos(D.first);

    if(which == "RPC3") t = (__RPC_D-P.z)/cos(D.first);

    if(which == "RPC4") t = -P.z/cos(D.first);

    if(which == "SCREEN") t =  ((__RPC_S+__RPC_W+2*__RPC_D)-P.z)/cos(D.first);


    I.x = P.x + sin(D.first)*cos(D.second)*t;
    I.y = P.y + sin(D.first)*sin(D.second)*t;
    I.z = P.z + cos(D.first)*t;

    return I;

}


//********************************************************************************************

int positionToStrip(const Point& hitposition,const Direction& D, string which){
    
    Point I = getHitPosition(hitposition,D,which);
    double x_hitposition = I.x;
    double y_hitposition = I.y; 
    int strip =0;
    if(which=="RPC1"||which=="RPC3") strip = floor(x_hitposition);
    if(which=="RPC2"||which=="RPC4") strip = floor(y_hitposition);

    
    return strip;
}


//********************************************************************************************

//Check if the muon is in the rpc surfaces
bool isInrpc(const Point& P, const Direction& D,string which){
    Point I = getHitPosition(P,D,which);
    //********************* X

    double x_low = -__RPC_L/2.;
    double x_high = __RPC_L/2.;
    bool x_condition = ( I.x > x_low && I.x < x_high  );

    //********************* Y

    double y_low = -__RPC_L/2.;
    double y_high = __RPC_L/2.;

    bool y_condition = ( I.y > y_low && I.y < y_high  );

    return (x_condition && y_condition);

}

#endif // FONCTIONS_H
