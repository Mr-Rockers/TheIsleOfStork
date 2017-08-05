#include "Module.h"

bool Module::initOutputLog(std::string name, std::string location) {
	this->outputLog = new OutputLog(name, location);
	return this->hasOutputLog();
}

bool Module::hasOutputLog() {
	return this->outputLog != nullptr;
}

OutputLog* Module::getOutputLog() {
	return this->outputLog;
}

Module::~Module() {
	delete Module::getOutputLog();
}