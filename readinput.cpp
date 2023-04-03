#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
void error(string err, string arg) {
        cerr << err << arg << endl;
        exit(0);
}

int main (int argc, char* argv[]){

        //Open the input file
        //ifstream infile{argv[1]};
        ifstream infile;
        infile.open("input.txt");

        string parameter;
        double value;

        //Check if infile cannot be open
        if (!infile.is_open()){
                error("Unable to open the following file: ", argv[1]);
        }

        //Create a dictionary to store values
        map<string, double> dict;
        while (infile >> parameter >> value){
                //params.push_back(parameter);
                dict.insert({parameter, value});

        }
        //displaying the contents
        for (auto element : dict){
                cout<<element.first<< element.second << endl;
        }

        // example accessing value based on the variable name
        cout << dict["maximum_simulated_time:"] << endl;

        infile.close();

}
