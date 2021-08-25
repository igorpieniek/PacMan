#include "ImageConcat.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void ImageConcat::addImage(std::string path){

    auto res = std::find_if(images.begin(), images.end(),
                            [&](const std::shared_ptr<ImageData>& img) {return img->path == path; });
    if (res == images.end()) {
        std::shared_ptr<ImageData> image = std::make_shared<ImageData>();
       
        stbi_set_flip_vertically_on_load(0);
        unsigned char* raw = stbi_load(path.c_str(), &image->width, &image->height, &image->stride, 0);
        if (raw == nullptr) {
            throw std::runtime_error("Cannot load map clapping file: " + path);
        }
        std::cout << "Image " << path<< " added to buffer"<< std::endl;
        image->path = path;
        image->saveImage(raw);
        stbi_image_free(raw);

        images.push_back(image);
        addToMatrix(image);
    }
    else {
        //std::cout << "Image " << path << " already stored" << std::endl;
        addToMatrix(*res);
    }
}

void ImageConcat::convert(){
    if (matrix.size() != (heightSize * widthSize)) {
        throw std::runtime_error("ImageConcat: Size of added map clappings is not equal size of declared new image");
    }

    // check if all images are the same size
    if (!isImagesDataValid()) {
        throw std::runtime_error("ImageConcat: Loaded images have diffrent sizes or stride (pixel format)");
    }
    // line concat
    std::vector<ImageData> lines(heightSize);
    for (int h = 0; h < heightSize; ++h) {
        lines[h].height = matrix[0]->height;
        lines[h].stride = matrix[0]->stride;
        for (int w = 0; w < widthSize; ++w) {
            //std::cout << "Pos (" << w << ", " << h << ") add img name: " << matrix[w + (h * widthSize)]->path << std::endl;
            lines[h].data = concatWidth(lines[h], matrix[w + (h * widthSize)]);
            lines[h].width = matrix[0]->width * (w + 1);
        }
    }

    // all lines concat into one
    result.data = concatHeight(lines);
    result.width = lines[0].width;
    result.height = lines.size() * matrix[0]->height;
    result.stride = matrix[0]->stride;

    save(savePath);
    
}

void ImageConcat::save(std::string res){
    int status = stbi_write_png(res.c_str(), result.width, result.height, result.stride, result.getDataPtr(), result.getByteWidth());
    std::cout << "Image Concat saving status : " << status << std::endl;
}



void ImageConcat::addToMatrix(std::shared_ptr<ImageData> img){
    if (matrix.size() < (size_t)(heightSize * widthSize)) {
        matrix.push_back(img);
    }
    else {
        std::cout << "All image added, start saving process..." << std::endl;
    }
}

bool ImageConcat::isImagesDataValid(){
    std::shared_ptr<ImageData> test = images[0];
    for (const auto& img : images) {
        if (!(*test == *img)) {
            return false;
        }
    }
    return true;
}

std::vector<unsigned char> ImageConcat::concatWidth(ImageData& one, const std::shared_ptr<ImageData> two){

    std::vector<unsigned char> res;
    if (one.width == 0) {
        res.insert(res.end(), two->data.begin(), two->data.end());
    }
    else {
        for (int i = 0; i < one.height; i++) {
            res.insert(res.end(), one.data.begin() + (i * one.getByteWidth()),
                one.data.begin() + (i * one.getByteWidth()) + one.getByteWidth());
            res.insert(res.end(), two->data.begin() + (i * two->getByteWidth()),
                two->data.begin() + (i * two->getByteWidth()) + two->getByteWidth());
        }
    }
	return res;
}

std::vector<unsigned char> ImageConcat::concatHeight(std::vector<ImageData>& imageLines){
    std::vector<unsigned char> res;

    for (auto& line : imageLines) {
        res.insert(res.end(), line.data.begin(), line.data.end() );
    }

    return res;
}
