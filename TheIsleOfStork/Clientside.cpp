#include "Clientside.h"

int main(int argc, char** argv)
{
	Client* client = new Client();
	int returnValue = client->run();
	delete client;

	return returnValue;
}

Client::Client() {

	this->clientOutputLog = new OutputLog("client", this->clientOutputLogLocation);

	//Log some information about the program.
	this->clientOutputLog->log(Client::gameName, true);
	this->clientOutputLog->log(std::string("Created by ").append(Client::gameDeveloper), true);
	this->clientOutputLog->log(std::string("Version: ").append(Client::gameVersion), true);
	this->clientOutputLog->log(std::string("(There's no point in having a version number this early on.)\n"), false);

	//Initialise SDL.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		this->clientOutputLog->log(std::string("SDL has failed to initialise!"), true);
		this->initSuccess = false;
		return;
	}

	//Create a window.
	mainWindow = SDL_CreateWindow(
		std::string(Client::gameName).append(" (").append(Client::gameVersion).append(")").c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL);

	if (mainWindow == nullptr) {
		this->clientOutputLog->log(std::string("SDL has failed to initialise a window!"), true);
		this->initSuccess = false;
		return;
	}

	//Set main window's GL layer and set basic attributes.
	mainWindowContext = SDL_GL_CreateContext(mainWindow);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//Initialise glew.
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		this->clientOutputLog->log(std::string("GLEW has failed to initialise!"), true);
		this->initSuccess = false;
		return;
	}

	//Initialise event handler.
	if (this->eventHandler == nullptr) {
		this->eventHandler = new EventHandler();
		this->clientOutputLog->log("Initialised event handler.", true);
	}

	//Initialise render.
	if (this->render == nullptr) {
		this->render = new Render(this->mainWindow);
		this->clientOutputLog->log("Initialised render.", true);
	}
}

bool Client::run() {
	if (!this->initSuccess) {
		return this->initSuccess;
	}

	while (this->runUpdate) {

		/*HANDLE CYCLES*/
		if (!this->eventHandler->cycle(&this->runUpdate) || !this->render->cycle()) {
			this->runUpdate = false;
			this->runSuccess = false;
		}
	}
	return this->runSuccess;
}

Client::~Client() {
	delete this->eventHandler;
	delete this->render;

	this->clientOutputLog->log(std::string("Client terminated ").append(this->initSuccess && this->runSuccess ? "successfully." : "unsuccessfully."), true);
	delete this->clientOutputLog;

	SDL_Quit();
}