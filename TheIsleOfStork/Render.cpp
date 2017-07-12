#include "Render.h"

Render::Render(SDL_Window* window) : _window(window) {
	this->renderOutputLog = new OutputLog("render", this->renderOutputLogLocation);

	Shader basicShader = Shader(this, "basicShader");
	basicShader.attachShader("fragment/basic.glsl", GL_FRAGMENT_SHADER);
	basicShader.attachShader("vertex/basic.glsl", GL_VERTEX_SHADER);
	basicShader.compileProgram();
	basicShader.getShaderProgramID();

	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
}

bool Render::cycle() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(this->_window);
	return true;
}

Render::~Render() {
	delete this->renderOutputLog;
}