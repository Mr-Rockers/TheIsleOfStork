#include "EventHandler.h"

EventHandler::EventHandler() {
	this->eventhandlerOutputLog = new OutputLog("event", this->eventhandlerOutputLogLocation);
}

EventHandler::~EventHandler() {
	delete this->eventhandlerOutputLog;
}

bool EventHandler::cycle(bool* run) {
	SDL_Event event = SDL_Event();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			*run = false;
		}
	}
	return true;
}