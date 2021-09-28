#include "ShaderTools.h"


std::string ShaderTools::readFile(std::string shaderPath) {
    std::string shaderCode;
    std::ifstream shaderStream(shaderPath.c_str(), std::ios::in);

    std::string line;
    bool isFragmentShaderStart = false;

    std::getline(shaderStream, line);
    while (!shaderStream.eof()) {
        std::getline(shaderStream, line);
        shaderCode.append(line + "\n");
    }
    shaderStream.close();
    return std::move(shaderCode);

}

unsigned int ShaderTools::compile(unsigned int type, const std::string& code) {
    unsigned int id = glCreateShader(type);
    const char* src = code.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << type << " with msg: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int ShaderTools::create(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShaderHandle = compile(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderHandle = compile(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderHandle);
    glAttachShader(program, fragmentShaderHandle);
    glLinkProgram(program);
    glValidateProgram(program);


    glDeleteShader(vertexShaderHandle);
    glDeleteShader(fragmentShaderHandle);


    return program;

}

Shader::Shader(std::string vertex, std::string fragment){
    std::string vertShader = ShaderTools::readFile(vertex);
    std::string fragShader = ShaderTools::readFile(fragment);
    id = ShaderTools::create(vertShader, fragShader);
    bind();
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform(const char* uni, std::vector<float>& val){
    int loc = getUniformLocation(uni);
    if (loc == -1) return;

    auto iter = uniformMeth.find(val.size());
    if (iter != uniformMeth.end()) {
        iter->second(loc, val);
    }
    else {
        std::cout << "Not supported uniform" << std::endl;
    }
}

void Shader::setUniformMatrix(const char* uni, const float* dataPtr){
    int loc = getUniformLocation(uni);
    if (loc == -1) return;

    ERROR_CHECK(glUniformMatrix4fv(loc, 1, GL_FALSE, dataPtr));

}

Shader::~Shader(){
    glDeleteProgram(id);
}

int Shader::getUniformLocation(const char* uniform){
    if (uniformsLocation.find(uniform) != uniformsLocation.end()) {
        return uniformsLocation[uniform];
    }

    unsigned int loc = glGetUniformLocation(id, uniform);
    if (loc == -1) {
        std::cout << "No uniform called " << uniform << "in program -id: " << id << std::endl;
    }
    return loc;
}
