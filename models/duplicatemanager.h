#ifndef DUPLICATEMANAGER_H
#define DUPLICATEMANAGER_H

#include <vector>
#include <utility>
#include <string>

class DuplicateManager {
public:
    DuplicateManager(
        const std::vector<std::pair<std::string, std::string>>&);
    void saveToDatabase();
    std::vector<std::pair<std::string, std::string>> readFromDatabase();
private:
    std::vector<std::pair<std::string, std::string>> duplicates;
};

#endif // DUPLICATEMANAGER_H
