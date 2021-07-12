#include "Texture.h"

Texture::Texture(std::string filename) : filePath(filename) {
    glGenTextures(1, &id);
    bind();
    stbi_set_flip_vertically_on_load(1);
    loadTexture(filePath);
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void Texture::setWrapping(WrappMethod method){
    setWrapParameter(static_cast<uint16_t>(method));
    if (method == WrappMethod::NO_REPEAT) {
        Color col{ 0.0f,0.0f,0.0f };
        setColor(col.getData());
    }
}

void Texture::setWrapping(WrappMethod method, Color col){
    if (method != WrappMethod::NO_REPEAT) {
        setWrapping(method);
    }
    else {
        setWrapParameter(static_cast<uint16_t>(method));
        setColor(col.getData());
    }
}




void Texture::bind(unsigned int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::set(){
    setImageData();
    createMipmap();
    //stbi_image_free(imageData);
}




void Texture::loadTexture(std::string filename){
    imageData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (imageData == nullptr) {
        std::cout << "Bad texture id:" << id << std::endl;

    }
    updateColorFormat();
}

void Texture::setWrapParameter(uint16_t method){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
}



void Texture::setColor(std::vector<float> col){
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, col.data());
}

void Texture::setMinFilter(uint16_t method){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, method);
}

void Texture::setMaxFilter(uint16_t method){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, method);
}

void Texture::setImageData(){
    glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, imageData);
}

void Texture::createMipmap(){
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::updateColorFormat(){
    if (nrChannels == 3) {
        colorFormat = GL_RGB;
    }
    else { //4
        colorFormat = GL_RGBA;
    }
}
