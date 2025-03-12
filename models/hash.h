#ifndef HASH_H
#define HASH_H

#include <opencv2/opencv.hpp>
#include <string>

class Hash {
public:
    Hash(const cv::Mat&);
    Hash();
    Hash(const std::string&);
    std::string getPhash() const;
    int hammingDistance(const Hash&) const;
private:
    std::string phash;
};

#endif // HASH_H
