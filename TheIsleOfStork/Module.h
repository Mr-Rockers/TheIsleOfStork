#ifndef INTERFACE_MODULE
#define INTERFACE_MODULE

#include "Utility.h"

class Module {
	/*The OutputLog class.*/
	OutputLog* outputLog;
public:
	/*Convenience function to see if module has OutputLog.*/
	bool hasOutputLog();
	/*Returns OutputLog. Should be used in conjuction with hasOutputLog()*/
	OutputLog* getOutputLog();
	/*If the module allows it, perform one "cycle". Effectively just a run or update function.*/
	virtual bool cycle(bool &loop) = 0;
	/*Called on deletion of module. Deletes the output log pointer.*/
	virtual ~Module();
protected:
	/*Used to initialise the output log.*/
	bool initOutputLog(std::string name, std::string location);
};

#endif