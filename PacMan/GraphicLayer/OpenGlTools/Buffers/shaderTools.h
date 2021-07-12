#pragma once

#ifndef __SHADERTOOLS_H__
#define __SHADERTOOLS_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <sstream>
#include <unordered_map>

#include "GLBuffer.h"
#include "gl_errors.h"

class ShaderTools{
public:
	static std::vector<std::string> readFile(std::string shadersPath);
	static unsigned int compile(unsigned int type, const std::string& code);
	static unsigned int create(const std::string& vertexShader, const std::string& fragmentShader);

};


class Shader : public GLBuffer {
public:
	Shader(std::string filename);
	
	void bind() const override;
	void unbind() const override;

	void setUniform(std::string uni, std::vector<float> val);
	void setUniformMatrix(std::string uni, const float* dataPtr);

	~Shader();

private:
	std::unordered_map<std::string, int> uniformsLocation;

	int getUniformLocation(std::string uniform);

};

#endif

