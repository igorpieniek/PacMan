#pragma once

#include "stb_image/stb_image.h"

#include "AdditionalTools.h"
#include <GL/glew.h>
#include <string>
#include <iostream>



class Texture{
public:
	Texture(std::string filename);
	~Texture();
	void bind(unsigned int slot =0) const;
	void unbind() const;

	void set();

	int getWidth()const { return width; };
	int getHeight()const { return height; };

	enum class WrappMethod:uint16_t {
		REPEAT = GL_REPEAT,
		REPEAT_MIRROR = GL_MIRRORED_REPEAT,
		CLAMP = GL_CLAMP_TO_EDGE,
		NO_REPEAT = GL_CLAMP_TO_BORDER
	};
	void setWrapping(WrappMethod method);
	void setWrapping(WrappMethod method, Color col);


private:
	unsigned int id{};
	int width{}, height{}, nrChannels{};
	unsigned char* imageData{nullptr};
	uint16_t colorFormat{};
	std::string filePath{};

	void loadTexture(std::string filename);
	void setWrapParameter(uint16_t method);
	void setColor(std::vector<float> col);
	void setMinFilter(uint16_t method);
	void setMaxFilter(uint16_t method);
	void setImageData();
	void createMipmap();

	void updateColorFormat();


};

