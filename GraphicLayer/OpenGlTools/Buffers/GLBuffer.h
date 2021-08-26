#pragma once



#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_errors.h"

class GLBuffer{
public:
	virtual void bind() const = 0;
	virtual void unbind() const = 0;


protected:
	unsigned int id;
};

