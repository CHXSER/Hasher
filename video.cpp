#include "video.h"

Video::Video(const std::string& fileName) : fileName(std::move(fileName)) {
    cv::Mat middle = extractMiddleFrame();
    phash = Hash(middle);
}

cv::Mat Video::extractMiddleFrame() const {
    cv::VideoCapture cap(fileName);
    int totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
    int middleFrame = totalFrames / 2;
    cap.set(cv::CAP_PROP_POS_FRAMES, middleFrame);
    cv::Mat frame;
    cap >> frame;
    cap.release();
    return frame;
}

std::string Video::getPhash() const {
    return phash.getPhash();
}

std::string Video::getFilePath() const {
    return fileName;
}
