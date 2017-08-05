#ifndef UTILITY_H
#define UTILITY_H

#ifndef UTILITY_FAIL
#define UTILITY_FAIL "[null]"
#endif

#include "Externals.h"

struct Utility {
	static std::string loadText(std::string location);
};

class OutputLog {
	bool initialised;
	std::string _name, _location;
	std::ofstream stream;
public:
	OutputLog();
	OutputLog(std::string name, std::string location);
	virtual ~OutputLog();
	void logOut(std::string message, bool toFile);
	std::string getOutputLogName();
	std::string getOutputLogLocation();
};

#endif