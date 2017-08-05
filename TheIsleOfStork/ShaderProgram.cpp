#include "Render.h"

ShaderProgram::ShaderProgram() : initialised(false) {}
ShaderProgram::ShaderProgram(Render* render, std::string name, std::map<std::string, ShaderProgram*>* parentShaderRegistry) : _render(render), _name(name), _parentShaderRegistry(parentShaderRegistry), shaderIDs(std::vector<unsigned int>()), initialised(true), compileCompleted(false) {
	this->compiledShaderProgramID = glCreateProgram();
	this->_render->getOutputLog()->logOut(std::string("Shader program \'").append(this->_name).append("\' initialised."), true);
	
	ShaderProgram::_parentShaderRegistry->insert({ this->_name, this });
}

ShaderProgram::~ShaderProgram() {
	if (this->initialised) {
		if (this->compileCompleted) {
			glDeleteProgram(this->compiledShaderProgramID);
		}
		else {
			for (GLuint i = 0; i < this->shaderIDs.size(); i++) {
				glDeleteShader(this->shaderIDs.at(i));
			}
		}
		this->_parentShaderRegistry->erase(this->_name);
	}
}

void ShaderProgram::attachShader(std::string localLocation, GLenum shaderType) {
	if (this->initialised) {
		std::string location = std::string(this->baseShaderLocation).append(localLocation);
		std::string data = Utility::loadText(location);

		if (data == UTILITY_FAIL) {
			this->_render->getOutputLog()->logOut(std::string("Failed to read \"").append(location).append("\" to \'").append(this->_name).append("\' shader."), true);
			return;
		}

		unsigned int shaderID = glCreateShader(shaderType);
		const char* dataCString = data.c_str();
		glShaderSource(shaderID, 1, &dataCString, NULL);
		glCompileShader(shaderID);

		int shaderCompileSuccess;
		char shaderCompileInfoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileSuccess);

		if (!shaderCompileSuccess) {
			this->_render->getOutputLog()->logOut(std::string("Failed to compile \"").append(location).append("\" to \'").append(this->_name).append("\' shader."), true);
			
			glGetShaderInfoLog(shaderID, 512, NULL, shaderCompileInfoLog);	
			this->_render->getOutputLog()->logOut(std::string("Error log from OpenGL:\n").append(shaderCompileInfoLog), true);
			
			return;
		}

		this->shaderIDs.push_back(shaderID);
		this->_render->getOutputLog()->logOut(std::string("Attached \"").append(location).append("\" to \'").append(this->_name).append("\' shader."), true);
	}
}

bool ShaderProgram::compileProgram() {
	if (this->initialised && this->compileCompleted == false) {

		for (GLuint i = 0; i < this->shaderIDs.size(); i++) {
			glAttachShader(this->compiledShaderProgramID, this->shaderIDs.at(i));
		}
		glLinkProgram(this->compiledShaderProgramID);

		int programLinkSuccess;
		char programLinkInfoLog[512];

		glGetProgramiv(this->compiledShaderProgramID, GL_LINK_STATUS, &programLinkSuccess);

		if (programLinkSuccess) {
			for (GLuint i = 0; i < this->shaderIDs.size(); i++) {
				glDeleteShader(this->shaderIDs.at(i));
			}
			this->compileCompleted = true;
			this->_render->getOutputLog()->logOut(std::string("Linked \'").append(this->_name).append("\' shader program."), true);
			return true;
		}

		this->_render->getOutputLog()->logOut(std::string("Failed to link \'").append(this->_name).append("\' shader program."), true);

		glGetProgramInfoLog(this->compiledShaderProgramID, 512, NULL, programLinkInfoLog);
		this->_render->getOutputLog()->logOut(std::string("Error log from OpenGL:\n").append(programLinkInfoLog), true);
	}
	return false;
}

GLuint ShaderProgram::getShaderProgramID() {
	if (this->initialised) {
		if (this->compileCompleted) {
			return this->compiledShaderProgramID;
		}
		else
		{
			this->_render->getOutputLog()->logOut(std::string("Cannot retrieve shader program ID for \"").append(this->_name).append("\' as shader program has not been compiled correctly."), true);
		}
	}
	return NULL;
}