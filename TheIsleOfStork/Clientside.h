#ifndef CLIENTSIDE_H
#define CLIENTSIDE_H

#include "Externals.h"

#include "Utility.h"
#include "EventHandler.h"
#include "Render.h"

class Client {
	bool initSuccess = true, runUpdate = true, runSuccess = true;

public:
	const std::string gameName = "The Isle of Stork",
		gameVersion = "In-Development",
		gameDeveloper = "Lyes Oussaiden";

	SDL_Window* mainWindow;
	SDL_GLContext mainWindowContext;

	EventHandler* eventHandler;
	Render* render;

	const std::string clientOutputLogLocation = "resources/logs/clientLog.txt";
	OutputLog* clientOutputLog;

	bool run();
	Client();
	~Client();
};

#endif