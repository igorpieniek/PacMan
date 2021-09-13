#pragma once
#pragma warning(disable : 4996)


#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "ImageData.h"
#include "stb_image/stb_image.h"



class ImageConcat{
public:
	ImageConcat(int amoutOfCellWidth, int amoutOfCellHeight, const std::string saveFilePath) :
		widthSize(amoutOfCellWidth), heightSize(amoutOfCellHeight), savePath(saveFilePath) 
	{
		matrix.reserve(widthSize * heightSize);
	};
	void addImage(std::string path);
	void convert();

private:
	std::vector< std::shared_ptr<ImageData> > images;
	std::vector< std::shared_ptr<ImageData> > matrix;
	ImageData result{};
	int widthSize{}, heightSize{};
	const std::string savePath{};

	void addToMatrix(std::shared_ptr<ImageData> img);
	bool isImagesDataValid();

	std::vector<unsigned char> concatWidth(ImageData& one, const std::shared_ptr<ImageData> two);
	std::vector<unsigned char> concatHeight(std::vector<ImageData>& imageLines);
	void save(std::string res);
};

