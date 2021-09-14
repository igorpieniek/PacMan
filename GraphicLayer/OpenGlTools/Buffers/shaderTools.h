#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <sstream>
#include <unordered_map>
#include <map>
#include <functional>

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

	void setUniform(const char* uni, std::vector<float>& val);
	void setUniformMatrix(const char* uni, const float* dataPtr);

	~Shader();

private:
	std::unordered_map<const char*, int> uniformsLocation;

	const std::map<size_t, std::function<void(int, std::vector<float>&)>> uniformMeth = {
		/*vector size | gl uniform function */
		{2, [&](int loc, std::vector<float>& argc) { glUniform2f(argc[0], argc[1], argc[2]);}},
		{3, [&](int loc, std::vector<float>& argc) { glUniform3f(argc[0], argc[1], argc[2], argc[3]); }},
		{4, [&](int loc, std::vector<float>& argc) { glUniform4f(argc[0], argc[1], argc[2], argc[3],argc[4]); }}
	};

	int getUniformLocation(const char* uniform);

};