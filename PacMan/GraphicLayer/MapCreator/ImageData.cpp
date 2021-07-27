#include "ImageData.h"

void ImageData::saveImage(unsigned char* ptr){
    for (int i = 0; i < getByteSize(); i++) {
        data.push_back(ptr[i]);
    }
}

bool ImageData::operator==(const ImageData& data){
    return (height == data.height && 
            width  == data.width && 
            stride == data.stride);
}

int ImageData::getByteWidth() const{
    return stride * width;
}

int ImageData::getByteSize() const{
    return getByteWidth() * height;
}

const void* ImageData::getDataPtr(){
    return (const void*)&data[0];
}
