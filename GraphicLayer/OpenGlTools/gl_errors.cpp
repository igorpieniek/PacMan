
#include "gl_errors.h"


void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* funName, int line, const char* file) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] "<< " ("<<file <<" L:" << line << " Function:"<< funName << ") Errror: "<<error << std::endl;
        return false;
    }
    return true;
}