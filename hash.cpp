#include "hash.h"

Hash::Hash(const cv::Mat& frame) {
    cv::Mat gray, resized, hash;

    cv::resize(frame, resized, cv::Size(8, 8));
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);

    uchar avg = cv::mean(gray)[0];

    hash = gray > avg;

    std::string shash;
    for (int i = 0; i < hash.rows; ++i) {
        for (int j = 0; j < hash.cols; ++j)
            shash += (hash.at<uchar>(i, j) ? '1' : '0');
    }

    phash = std::move(shash);
}

std::string_view Hash::getPhash() const {
    return phash;
}

bool Hash::operator==(const Hash& other) const {
    return other.phash == phash;
}

bool Hash::operator!=(const Hash& other) const {
    return other.phash != phash;
}
