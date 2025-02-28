#include "hash.h"

Hash::Hash(const cv::Mat& frame) {
    cv::Mat gray, resized, hash;

    cv::resize(frame, resized, cv::Size(8, 8));
}
