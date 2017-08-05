#include "Clientside.h"

//The entry point for the program. Not worth having its own seperate .cpp file.
int main(int argc, char** argv)
{
	Client* client = new Client();
	bool returnValue = client->run();
	delete client;

	return returnValue ? 1 : 0;
}

Client::Client() {

	//Create the log.
	this->clientOutputLog = new OutputLog("client", this->clientOutputLogLocation);

	//Log some information about the program.
	this->clientOutputLog->logOut(Client::gameName, true);
	this->clientOutputLog->logOut(std::string("Created by ").append(Client::gameDeveloper), true);
	this->clientOutputLog->logOut(std::string("Version: ").append(Client::gameVersion), true);
	this->clientOutputLog->logOut(std::string("(There's no point in having a version number this early on.)\n"), false);

	//Initialise SDL.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		this->clientOutputLog->logOut(std::string("SDL has failed to initialise!"), true);
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
		this->clientOutputLog->logOut(std::string("SDL has failed to initialise a window!"), true);
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
		this->clientOutputLog->logOut(std::string("GLEW has failed to initialise!"), true);
		this->initSuccess = false;
		return;
	}

	//Initialise event handler.
	if (this->eventHandler == nullptr) {
		this->eventHandler = new EventHandler();
		this->clientOutputLog->logOut("Initialised event handler.", true);
	}

	//Initialise render.
	if (this->render == nullptr) {
		this->render = new Render(this->mainWindow);
		this->clientOutputLog->logOut("Initialised render.", true);
	}
}

//The "update" section of the program. Any and all core initialisation should have finished by now.
bool Client::run() {

	//If init has failed for whatever reason, 
	if (!this->initSuccess) {
		return this->initSuccess;
	}

	//The actual loop in question.
	bool loop = true;
	while (loop) {

		/*HANDLE CYCLES*/
		if (!this->eventHandler->cycle(loop) || !this->render->cycle(loop)) {
			this->runSuccess = false;
		}
	}
	return this->runSuccess;
}

Client::~Client() {
	delete this->eventHandler;
	delete this->render;

	this->clientOutputLog->logOut(std::string("Client terminated ").append(this->initSuccess && this->runSuccess ? "successfully." : "unsuccessfully."), true);
	delete this->clientOutputLog;

	SDL_Quit();
}