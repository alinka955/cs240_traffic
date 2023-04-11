#ifndef READINPUT_H
#define READINPUT_H

#include <map>
#include <string>

class ReadInput
{
public:
	ReadInput();
	void error(std::string err, std::string arg);
	std::map<std::string, double> getDict(std::string input);
};

#endif /* READINPUT_H */
