#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
/*
class ReadInput(){
public:

int maximum_simulated_time;
int number_of_sections_before_intersection;
int green_north_south;
int yellow_north_south;
int green_east_west;
int yellow_east_west;
int prob_new_vehicle_northbound;
int prob_new_vehicle_southbound;
int prob_new_vehicle_eastbound;
int prob_new_vehicle_westbound;
int proportion_of_cars;
int proportion_of_SUVs;
int proportion_right_turn_cars;
int proportion_right_turn_SUVs;
int proportion_right_turn_trucks;

//int input();

}
*/
/*
void ReadInput::input(){
	ofstream file_obj;
	file_obj.open("input.txt", ios::app);
	ReadInput obj;
	std::ifstream inf(infile);
   std::string contents;
   int c;
   while ( (c = inf.get()) != EOF )
   {
      contents += c;
   }
}
*/
/*
void error(string err, string arg) {
        cerr << err << arg << endl;
        exit(0);
}
int main(int argc, char* argv[]){
        
        ifstream infile {argv[1]};

	string parameter;
	double value;
		
	if (!infile){
                error("Unable to open the following file: ", argv[1]);
        }
	
	while (infile >> parameter){
		cout << getline(infile, parameter) << endl;
	}

}
*/
int main (int argc, char* argv[]){
	//ReadInput file;
	//getline(cin, file.maximum_simulated_time);
	
	ifstream myfile{argv[1]};	
	string mystring;
	if ( myfile.is_open() ) {
		//myfile >> mystring;
		//cout << mystring << endl;
                //getline(myfile, mystring);
		while (myfile.good()) {
			myfile >> mystring;
			
		//	getline(myfile, mystring);
			//string s =  split(mystring, ":");
		//	cout << mystring << endl;
			cout << mystring.substr(0, mystring.find(":")) << endl;						
			//variable name
			

			//the value of a variable
		}
		//cout << mystring << endl;
	}
}


