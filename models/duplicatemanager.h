#ifndef DUPLICATEMANAGER_H
#define DUPLICATEMANAGER_H

#include <vector>
#include <utility>
#include <string>

class DuplicateManager {
public:
    DuplicateManager(
        const std::vector<std::pair<std::string, std::string>>&);
    void showNextDuplicate();
    void deleteFile(const std::string& filePath);
    void ignoreDuplicate(std::pair<std::string, std::string>& duplicates);
    std::pair<std::string, std::string> getCurrentDuplicate() const;
private:
    std::vector<std::pair<std::string, std::string>> duplicates;
    std::vector<std::pair<std::string, std::string>> ignoreDuplicates;
    size_t currentIndex;
};

#endif // DUPLICATEMANAGER_H
