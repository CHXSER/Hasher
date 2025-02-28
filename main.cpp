#include "mainwindow.h"

#include <QApplication>

#include <fstream>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

std::string calculatePhash(const cv::Mat& frame) {
    cv::Mat resized, gray, hash;
    // Resize to 8x8 and convert to grayscale
    cv::resize(frame, resized, cv::Size(8, 8));
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    // Calculate average pixel value
    uchar avg = cv::mean(gray)[0];
    // Generate hash: 1 if pixel > avg, else 0
    hash = gray > avg;
    // Convert hash to string
    std::string phash;
    for (int i = 0; i < hash.rows; ++i) {
        for (int j = 0; j < hash.cols; ++j) {
            phash += (hash.at<uchar>(i, j) ? '1' : '0');
        }
    }
    return phash;
}

cv::Mat extractMiddleFrame(const std::string& videoPath) {
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        throw std::runtime_error("Could not open video: " + videoPath);
    }
    int totalFrames = cap.get(cv::CAP_PROP_FRAME_COUNT);
    int middleFrame = totalFrames / 2;
    cap.set(cv::CAP_PROP_POS_FRAMES, middleFrame);
    cv::Mat frame;
    cap >> frame;
    cap.release();
    return frame;
}

std::unordered_map<std::string, std::string> loadDatabase(const std::string& dbFile) {
    std::unordered_map<std::string, std::string> videoHashes;
    if (fs::exists(dbFile)) {
        std::ifstream in(dbFile);
        json j;
        in >> j;
        videoHashes = j.get<std::unordered_map<std::string, std::string>>();
    }
    return videoHashes;
}

// Function to save the hash database
void saveDatabase(const std::string& dbFile, const std::unordered_map<std::string, std::string>& videoHashes) {
    std::ofstream out(dbFile);
    json j = videoHashes;
    out << j;
}

// Function to find and handle duplicates
void handleDuplicates(std::unordered_map<std::string, std::string>& videoHashes) {
    std::unordered_map<std::string, std::vector<std::string>> hashToFiles;
    for (const auto& [file, hash] : videoHashes) {
        hashToFiles[hash].push_back(file);
    }
    for (const auto& [hash, files] : hashToFiles) {
        if (files.size() > 1) {
            std::cout << "Duplicate files with hash " << hash << ":\n";
            for (size_t i = 0; i < files.size(); ++i) {
                std::cout << i + 1 << ". " << files[i] << "\n";
            }
            int keepIndex;
            std::cout << "Enter the number of the file to keep (0 to keep all): ";
            std::cin >> keepIndex;
            if (keepIndex == 0) continue;
            for (size_t i = 0; i < files.size(); ++i) {
                if (i + 1 != keepIndex) {
                    std::cout << "Deleting " << files[i] << "...\n";
                    fs::remove(files[i]);
                    videoHashes.erase(files[i]);
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
