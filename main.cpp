#include "mainwindow.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include "video.h"
#include "image.h"
#include <filesystem>
#include <unordered_map>

int hammingDistance(const std::string& hash1, const std::string& hash2) {
    int distance = 0;
    for (size_t i = 0; i < std::min(hash1.size(), hash2.size()); ++i) {
        if (hash1[i] != hash2[i]) {
            distance++;
        }
    }
    return distance;
}

int main(int argc, char *argv[])
{
    std::string path = "/home/chxser/Pictures/";
    int hammingTreshold = 5;
    std::unordered_map<std::string, std::string> hashes;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string filePath = entry.path().string();

        if (filePath.find(".mp4") != std::string::npos ||
            filePath.find(".gif") != std::string::npos ||
            filePath.find(".webm") != std::string::npos) {
            Video video(filePath);
            hashes[filePath] = video.getPhash();
        } else if (filePath.find(".png") != std::string::npos ||
                   filePath.find(".jpg") != std::string::npos ||
                   filePath.find(".jpeg") != std::string::npos) {
            Image image(filePath);
            hashes[filePath] = image.getPhash();
        }
    }

    for (auto it1 = hashes.begin(); it1 != hashes.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != hashes.end(); ++it2) {
            int distance = hammingDistance(it1->second, it2->second);
            if (distance <= hammingTreshold) {
                std::cout << "Duplicati trovati:" << std::endl;
                std::cout << "1. " << it1->first << std::endl;
                std::cout << "2. " << it2->first << std::endl;
            }
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
