#pragma once
#pragma warning(disable : 4996)
//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION

//#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include <string>
#include <iostream>
#include <vector>

#include "ImageData.h"

class ImageConcat{
private:
	std::vector< std::shared_ptr<ImageData> > images;
	std::vector< std::shared_ptr<ImageData> > matrix;
	ImageData result;
	int widthSize, heightSize;

	void addToMatrix(std::shared_ptr<ImageData> img);

	std::vector<unsigned char> concat(ImageData& one, const std::shared_ptr<ImageData> two);
	std::vector<unsigned char> concatHeight(std::vector<ImageData>& imageLines);
	void save(std::string res);

public:
	ImageConcat(int amoutOfCellWidth, int amoutOfCellHeight) :
		widthSize(amoutOfCellWidth), heightSize(amoutOfCellHeight) {};
	void addImage(std::string path);
	void convert();

};

