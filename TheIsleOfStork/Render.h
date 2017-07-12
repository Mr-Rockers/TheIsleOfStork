#ifndef RENDER_H
#define RENDER_H

#include "Externals.h"

#include "Utility.h"

class Render {
	SDL_Window* _window;
public:
	const std::string renderOutputLogLocation = "resources/logs/renderLog.txt";
	OutputLog* renderOutputLog;

	Render(SDL_Window* window);
	~Render();
	bool cycle();
};

class Shader {
	const std::string baseShaderLocation = "resources/shaders/";

	Render* _render;
	std::string _name;

	std::vector<unsigned int> shaderIDs;
	bool initialised, compileCompleted;
	GLuint compiledShaderProgramID;
public:

	Shader();
	Shader(Render* render, std::string name);
	~Shader();
	//Compiles a single shader for the shader program and "attaches" it to the program.
	//Note, location is local. "resources/shaders/"
	void attachShader(std::string localLocation, GLenum shaderType);
	bool compileProgram();
	GLuint getShaderProgramID();
};

#endif