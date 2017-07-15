#ifndef RENDER_H
#define RENDER_H

#include "Externals.h"

#include "Utility.h"

class ShaderProgram;

class Render {
	SDL_Window* _window;
public:
	const std::string renderOutputLogLocation = "resources/logs/renderLog.txt";
	OutputLog* renderOutputLog;

	std::map<std::string, ShaderProgram*> shaderRegistry;

	Render(SDL_Window* window);
	~Render();
	bool cycle();
};

class ShaderProgram {
	const std::string baseShaderLocation = "resources/shaders/";

	Render* _render;
	std::string _name;
	std::map<std::string, ShaderProgram*>* _parentShaderRegistry;
	
	std::vector<GLuint> shaderIDs;
	bool initialised, compileCompleted;
	GLuint compiledShaderProgramID;
public:

	ShaderProgram();
	ShaderProgram(Render* render, std::string name, std::map<std::string, ShaderProgram*>* parentShaderRegistry);
	~ShaderProgram();
	//Compiles a single shader for the shader program and "attaches" it to the program.
	//Note, location is local. "resources/shaders/"
	void attachShader(std::string localLocation, GLenum shaderType);
	bool compileProgram();
	GLuint getShaderProgramID();
};

#endif