#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
private:
	GLuint m_Program;
public:
	Shader(const char*vertexShaderPath, const char*fragmentShaderPath)
	{
		std::string vertexCode, fragmentCode;
		std::ifstream vertexFile, fragmentFile;

		vertexFile.exceptions(std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::badbit);

		try
		{
			vertexFile.open(vertexShaderPath);
			fragmentFile.open(fragmentShaderPath);

			std::stringstream vertexStream, fragmentStream;
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			vertexFile.close();
			fragmentFile.close();

			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Fail to open shader files" << std::endl;
		}

		const GLchar *vertexShaderCode = vertexCode.c_str();
		const GLchar *fragmentShaderCode = fragmentCode.c_str();
		
		GLuint vertexShader, fragmentShader;
		GLint success;
		GLchar infoLog[512];

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout<<"Error vertex shader\n" << infoLog << std::endl;
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Error fragment shader\n" << infoLog << std::endl;
		}

		m_Program = glCreateProgram();
		glAttachShader(m_Program, vertexShader);
		glAttachShader(m_Program, fragmentShader);
		glLinkProgram(m_Program);

		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_Program, 512, NULL, infoLog);
			std::cout << "Error link program shader\n" << infoLog << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(m_Program);
	}

	GLuint getProgram() const
	{
		return m_Program;
	}
};
