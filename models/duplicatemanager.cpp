#include "duplicatemanager.h"

#include <filesystem>

DuplicateManager::DuplicateManager(
    const std::vector<std::pair<std::string, std::string>>& duplicates)
    : duplicates(std::move(duplicates)) {}





