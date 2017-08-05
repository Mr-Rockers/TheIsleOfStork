#include "EventHandler.h"

EventHandler::EventHandler() {
	this->initOutputLog("event", "resources/logs/eventHandlerLog.txt");
}

EventHandler::~EventHandler() {
}

bool EventHandler::cycle(bool &loop) {
	SDL_Event event = SDL_Event();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			this->getOutputLog()->logOut("The user has terminated the application. (SDL_QUIT)", true);
			loop = false;
		}
	}
	return true;
}