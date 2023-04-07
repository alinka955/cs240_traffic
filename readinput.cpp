#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "readinput.h"
using namespace std;


ReadInput::ReadInput(){};


void ReadInput::error(string err, string arg) {
        cerr << err << arg << endl;
        exit(0);
}

map<string, double> ReadInput::getDict(string input){
		
	//Open the input file
	ifstream infile{input};	
	
	//Check if infile cannot be open
	if (!infile.is_open()){
        	error("Unable to open the following file: ", "input.txt");
        }
	string parameter;
	double value;
	
	
	
	//Create a dictionary to store values
 	map<string, double> dict;	
	while (infile >> parameter >> value){
		//params.push_back(parameter);
		dict.insert({parameter, value});

	}
	infile.close();
	return dict;
}



int main (int argc, char* argv[]){
	ReadInput readinput;
	map<string, double> dict = readinput.getDict(argv[1]);
	//displaying the contents
   	for (auto element : dict){
		cout<<element.first<< element.second << endl;
	}
	
	// example accessing value based on the variable name	
//	cout << dict["maximum_simulated_time:"] << endl;	
 
        //infile.close();
	    
}

