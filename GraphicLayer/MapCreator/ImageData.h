#pragma once
#include <vector>
#include <string>

struct ImageData{
	ImageData();
	std::vector<unsigned char> data;
	int width, height, stride;
	std::string path;

	void saveImage(unsigned char* ptr);
	bool operator==(const ImageData& data);
	int getByteWidth()const;
	int getByteSize()const;
	const void* getDataPtr();
};

