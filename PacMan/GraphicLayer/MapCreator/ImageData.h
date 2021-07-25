#pragma once
#include <vector>
#include <string>

class ImageData{
public:
	std::vector<unsigned char> data;
	int width, height, stride;

	std::string path;

	void addRaw(unsigned char* ptr);
	bool operator==(const ImageData& data);
	int getByteWidth()const;
	int getByteSize()const;
	const void* getDataPtr();

private:
	unsigned char* raw;
	

};

