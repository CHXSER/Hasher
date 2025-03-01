#include "image.h"

Image::Image(const std::string& fileName) : fileName(std::move(fileName)) {
    cv::Mat image = loadImage();
    phash = Hash(image);
}

std::string Image::getPhash() const {
    return phash.getPhash();
}

cv::Mat Image::loadImage() const {
    cv::Mat image = cv::imread(fileName);
    return image;
}
