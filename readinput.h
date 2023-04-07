#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class ReadInput{
	private:
		string input;
		void error(string err, string arg);
	public:
		ReadInput();
		//~ReadInput();	
		
		map<string, double> getDict(string input);
};
