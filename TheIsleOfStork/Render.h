#ifndef RENDER_H
#define RENDER_H

#include "Module.h"

class ShaderProgram;

class Render : public Module{
	SDL_Window* _window;
public:

	std::map<std::string, ShaderProgram*> shaderRegistry;
	Render(SDL_Window* window);
	~Render();

	bool cycle(bool &loop);
};

class ShaderProgram {
	const std::string baseShaderLocation = "resources/shaders/";
	std::map<std::string, ShaderProgram*>* _parentShaderRegistry;

	Render* _render;
	std::string _name;
	
	std::vector<GLuint> shaderIDs;
	bool initialised, compileCompleted;
	GLuint compiledShaderProgramID;
public:

	ShaderProgram();
	ShaderProgram(Render* render, std::string name, std::map<std::string, ShaderProgram*>* parentShaderRegistry);
	~ShaderProgram();
	/*Compiles a single shader for the shader program and "attaches" it to the program.
	Note, location is local. "resources/shaders/"*/
	void attachShader(std::string localLocation, GLenum shaderType);
	bool compileProgram();
	GLuint getShaderProgramID();
};

#endif