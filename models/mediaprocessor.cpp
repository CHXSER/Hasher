#include "mediaprocessor.h"
#include <filesystem>
#include "video.h"
#include "image.h"

#include <QThread>

MediaProcessor::MediaProcessor(const std::string& dir) : directory(std::move(dir)) {}

void MediaProcessor::startProcessing(int hammingTreshold) {
    QThread* thread = new QThread();
    this->moveToThread(thread);

    connect(thread, &QThread::started, this, &MediaProcessor::processMediaFiles);
    connect(this, &MediaProcessor::processingFinished, thread, &QThread::quit);
    connect(this, &MediaProcessor::processingFinished, this, &MediaProcessor::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void MediaProcessor::processMediaFiles() {
    calculateHashes();
    findDuplicates();
    emit processingFinished();
}

std::vector<std::pair<std::string, std::string> > MediaProcessor::getDuplicates() const
{
    return duplicates;
}

void MediaProcessor::calculateHashes() {
    int totalFiles = std::distance(std::filesystem::directory_iterator(directory),
                                   std::filesystem::directory_iterator{});
    int processedFiles = 0;

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

        processedFiles++;
        emit progressUpdated(processedFiles, totalFiles);
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
