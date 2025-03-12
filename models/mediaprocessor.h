#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

#include <unordered_map>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


class MediaProcessor {
public:
    MediaProcessor(const std::string& directory);
    void processMediaFiles(int hammingDistance = 5);
    std::vector<std::pair<std::string, std::string>> getDuplicates() const;
private:
    std::string directory;
    std::unordered_map<std::string, std::string> mediaHashes;
    std::vector<std::pair<std::string, std::string>> duplicates;
    void findDuplicates(int hammingTreshold = 5);
    void calculateHashes();
};

#endif // MEDIAPROCESSOR_H
