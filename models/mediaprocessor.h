#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

#include <QObject>

#include <unordered_map>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


class MediaProcessor : public QObject {
    Q_OBJECT
public:
    explicit MediaProcessor(const std::string& directory);
    void startProcessing(int hammingDistance = 5);
    std::vector<std::pair<std::string, std::string>> getDuplicates() const;

signals:
    void progressUpdated(int processed, int total);
    void processingFinished();
public slots:
    void processMediaFiles();

private:
    std::string directory;
    std::unordered_map<std::string, std::string> mediaHashes;
    std::vector<std::pair<std::string, std::string>> duplicates;
    void findDuplicates(int hammingTreshold = 5);
    void calculateHashes();
};

#endif // MEDIAPROCESSOR_H
