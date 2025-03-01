#include "hash.h"
#include <algorithm>

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

Hash::Hash() {}

Hash::Hash(const std::string& hash) : phash(std::move(hash)) {}

std::string Hash::getPhash() const {
    return phash;
}

int Hash::hammingDistance(const Hash& other) const {
    int distance = 0;
    for (size_t i = 0; i < std::min(phash.size(), other.phash.size()); ++i) {
        if (phash[i] != other.phash[i]) {
            distance++;
        }
    }
    return distance;
}
