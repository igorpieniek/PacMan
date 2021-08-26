#pragma once



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak(); 
#define ERROR_CHECK(fun)    glClearError(); \
                            fun; \
                            ASSERT(glLogCall(#fun,__LINE__, __FILE__));


void glClearError();

bool glLogCall(const char* funName, int line, const char* file);





