#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Externals.h"

#include "Utility.h"

class EventHandler {
public:
	const std::string eventhandlerOutputLogLocation = "resources/logs/eventHandlerLog.txt";
	OutputLog* eventhandlerOutputLog;

	EventHandler();
	~EventHandler();
	bool cycle(bool* run);
};

#endif