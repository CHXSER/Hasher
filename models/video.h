#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <opencv2/opencv.hpp>
#include "hash.h"

class Video {
public:
    Video(const std::string&);
    std::string getFilePath() const;
    std::string getPhash() const;
private:
    std::string fileName;
    Hash phash;
    cv::Mat extractMiddleFrame() const;
};

#endif // VIDEO_H
