#include "FileManager.h"

// ---------------------- FILE CHECKS ----------------------
bool FileManager::fileExists(const std::string& path) const {
    std::ifstream file(path);
    return file.is_open();
}

void FileManager::clearFile(const std::string& path) const {
    std::ofstream file(path, std::ios::trunc);
}

// ---------------------- READ LINES ----------------------
std::optional<std::string> FileManager::readLine(const std::string& path, size_t index) const {
    std::ifstream file(path);
    if (!file.is_open()) return std::nullopt;

    std::string line;
    for (size_t i = 0; i <= index; ++i) {
        if (!std::getline(file, line)) return std::nullopt;
    }

    if (line.find_first_not_of(' ') == std::string::npos) return std::nullopt;

    return line;
}

std::optional<std::vector<std::string>> FileManager::readAllLines(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) return std::nullopt;

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find_first_not_of(' ') != std::string::npos) {
            lines.push_back(line);
        }
    }

    return lines;
}

// ---------------------- READ COLUMNS ----------------------
std::optional<std::vector<std::string>> FileManager::readLineColumns(
    const std::string& path,
    size_t index,
    const std::vector<size_t>& columns,
    char delimiter
) const {
    auto optLine = readLine(path, index);
    if (!optLine.has_value()) return std::nullopt;

    std::vector<std::string> result;
    std::stringstream ss(optLine.value());
    std::string token;
    size_t nextColumn = 0;

    for (size_t i = 0; i <= columns.back(); ++i) {
        if (!std::getline(ss, token, delimiter)) break;
        if (nextColumn < columns.size() && i == columns[nextColumn]) {
            result.push_back(token);
            ++nextColumn;
        }
    }

    return result;
}

// ---------------------- WRITE / APPEND ----------------------
void FileManager::appendLine(const std::string& path, const std::string& line) const {
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) return;
    file << line << "\n";
}

void FileManager::writeLine(const std::string& path, size_t index, const std::string& newLine) const {
    std::ifstream fileIn(path);
    if (!fileIn.is_open()) return;

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fileIn, line)) {
        lines.push_back(line);
    }
    fileIn.close();

    if (index >= lines.size()) return;
    lines[index] = newLine;

    std::ofstream fileOut(path, std::ios::trunc);
    for (const auto& l : lines) {
        fileOut << l << "\n";
    }
}

void FileManager::writeAllLines(const std::string& path, const std::vector<std::string>& lines) const {
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open()) return;

    for (const auto& line : lines) {
        file << line << "\n";
    }
}

// ---------------------- DELETE LINE ----------------------
void FileManager::deleteLine(const std::string& path, size_t index) const {
    std::ifstream fileIn(path);
    if (!fileIn.is_open()) return;

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fileIn, line)) {
        lines.push_back(line);
    }
    fileIn.close();

    if (index >= lines.size()) return;
    lines[index] = std::string(lines[index].size(), ' '); // mark deleted

    std::ofstream fileOut(path, std::ios::trunc);
    for (const auto& l : lines) {
        fileOut << l << "\n";
    }
}

// ---------------------- METADATA ----------------------
size_t FileManager::getLineCount(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) return 0;

    return std::count(std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>(), '\n');
}