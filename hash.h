#ifndef HASH_H
#define HASH_H

#include <opencv2/opencv.hpp>
#include <string_view>

class Hash {
public:
    Hash(const cv::Mat&);
    std::string_view getPhash() const;
    bool operator==(const Hash&) const;
    bool operator!=(const Hash&) const;
private:
    std::string_view phash;
};

#endif // HASH_H
