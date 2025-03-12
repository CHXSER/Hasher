#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <opencv2/opencv.hpp>

#include "hash.h"

class Image {
public:
    Image(const std::string&);
    std::string getFilePath() const;
    std::string getPhash() const;
private:
    std::string fileName;
    Hash phash;
    cv::Mat loadImage() const;
};

#endif // IMAGE_H
