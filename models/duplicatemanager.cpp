#include "duplicatemanager.h"

#include <filesystem>

DuplicateManager::DuplicateManager(
    const std::vector<std::pair<std::string, std::string>>& duplicates)
    : duplicates(std::move(duplicates)), currentIndex(0) {}

void DuplicateManager::showNextDuplicate() {
    if (currentIndex < duplicates.size())
        currentIndex++;
}

void DuplicateManager::deleteFile(const std::string& filePath) {
    std::filesystem::remove(filePath);
}

void DuplicateManager::ignoreDuplicate(std::pair<std::string, std::string>& dup) {
    ignoreDuplicates.push_back(dup);
}

std::pair<std::string, std::string> DuplicateManager::getCurrentDuplicate() const {
    if (currentIndex < duplicates.size())
        return duplicates[currentIndex];
    return { "", "" };
}



