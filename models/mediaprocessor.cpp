#include "mediaprocessor.h"
#include <filesystem>
#include "video.h"
#include "image.h"

MediaProcessor::MediaProcessor(const std::string& dir) : directory(std::move(dir)) {
    processMediaFiles();
}

void MediaProcessor::processMediaFiles(int hammingTreshold) {
    calculateHashes();
    findDuplicates(hammingTreshold);
}

std::vector<std::pair<std::string, std::string> > MediaProcessor::getDuplicates() const
{
    return duplicates;
}

void MediaProcessor::calculateHashes() {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string filePath = entry.path().string();
        if (filePath.find(".mp4") != std::string::npos ||
            filePath.find(".webm") != std::string::npos ||
            filePath.find(".gif") != std::string::npos) {
            Video video(filePath);
            mediaHashes[filePath] = video.getPhash();
        } else if (filePath.find(".png") != std::string::npos ||
                   filePath.find(".jpg") != std::string::npos ||
                   filePath.find(".jpeg") != std::string::npos) {
            Image image(filePath);
            mediaHashes[filePath] = image.getPhash();
        }
    }
}

void MediaProcessor::findDuplicates(int hammingThreshold) {
    for (auto it1 = mediaHashes.begin(); it1 != mediaHashes.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != mediaHashes.end(); ++it2) {
            Hash hash1(it1->second);
            Hash hash2(it2->second);
            if (hash1.hammingDistance(hash2) <= hammingThreshold) {
                duplicates.push_back({it1->first, it2->first});
            }
        }
    }
}
