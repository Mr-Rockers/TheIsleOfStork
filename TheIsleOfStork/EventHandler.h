#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Module.h"

class EventHandler : public Module {
public:

	EventHandler();
	~EventHandler();
	bool cycle(bool &loop);
};

#endif