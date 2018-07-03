#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		string vertexCode, fragmentCode;
		ifstream vShaderFile, fShaderFile;
		stringstream vShaderStream, fShaderStream;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(vertex, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use()
	{
		glUseProgram(ID);
	}

	int getProgramID() {
		if (ID == 0) {
			return -1;
		}
		return ID;
	}

	// ------------------------------------------------------------------------
	void setBoolU1(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setIntU1(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloatU1(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setBoolU2(const std::string &name, bool value, bool value2) const
	{
		glUniform2i(glGetUniformLocation(ID, name.c_str()), (int)value, (int)value2);
	}
	// ------------------------------------------------------------------------
	void setIntU2(const std::string &name, int value, int value2) const
	{
		glUniform2i(glGetUniformLocation(ID, name.c_str()), value, value2);
	}
	// ------------------------------------------------------------------------
	void setFloatU2(const std::string &name, float value, float value2) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), value, value2);
	}
	// ------------------------------------------------------------------------
	void setBoolU3(const std::string &name, bool value, bool value2, bool value3) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), (int)value, (int)value2, (int)value3);
	}
	// ------------------------------------------------------------------------
	void setIntU3(const std::string &name, int value, int value2, int value3) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), value, value2, value3);
	}
	// ------------------------------------------------------------------------
	void setFloatU3(const std::string &name, float value, float value2, float value3) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value, value2, value3);
	}
	// ------------------------------------------------------------------------
	void setBoolU4(const std::string &name, bool value, bool value2, bool value3, bool value4) const
	{
		glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)value, (int)value2, (int)value3, (int)value4);
	}
	// ------------------------------------------------------------------------
	void setIntU4(const std::string &name, int value, int value2, int value3, int value4) const
	{
		glUniform4i(glGetUniformLocation(ID, name.c_str()), value, value2, value3, value4);
	}
	// ------------------------------------------------------------------------
	void setFloatU4(const std::string &name, float value, float value2, float value3, float value4) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value, value2, value3, value4);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};





#endif