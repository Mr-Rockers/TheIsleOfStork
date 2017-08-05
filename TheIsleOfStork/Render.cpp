#include "Render.h"

Render::Render(SDL_Window* window) : _window(window) {
	this->initOutputLog("render", "resources/logs/renderLog.txt");

	ShaderProgram basicShader = ShaderProgram(this, "basicShader", &this->shaderRegistry);
	basicShader.attachShader("fragment/basic.glsl", GL_FRAGMENT_SHADER);
	basicShader.attachShader("vertex/basic.glsl", GL_VERTEX_SHADER);
	basicShader.compileProgram();
	basicShader.getShaderProgramID();

	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
}

bool Render::cycle(bool &loop) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(this->_window);
	return true;
}

Render::~Render() {
}