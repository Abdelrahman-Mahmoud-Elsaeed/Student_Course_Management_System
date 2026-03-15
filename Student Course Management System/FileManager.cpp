#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include <string>

std::optional<std::vector<std::string>> FileManager::readAllLines(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file at path: " << path << "\n";
        return std::nullopt;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::optional<std::string> FileManager::readLine(const std::string& path, size_t index) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file at path: " << path << "\n";
        return std::nullopt;
    }

    std::string line;
    size_t current = 0;
    while (std::getline(file, line)) {
        if (current == index) return line;
        current++;
    }

    return std::nullopt;
}

void FileManager::writeAllLines(const std::string& path, const std::vector<std::string>& lines) const {
    std::ofstream file(path, std::ios::out);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file at path: " << path << "\n";
        return;
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }
}

void FileManager::writeLine(const std::string& path, size_t id, const std::string& newLine) const {
    auto optLines = readAllLines(path);
    if (!optLines) {
        std::cout << "Failed to open file\n";
        return;
    }

    auto& lines = *optLines;
    if (id >= lines.size()) {
        std::cout << "Invalid line index\n";
        return;
    }

    lines[id] = newLine;

    writeAllLines(path, lines);
}

void FileManager::appendLine(const std::string& path, const std::string& line) const {
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file at path: " << path << "\n";
        return;
    }
    file << line << "\n";
};


bool FileManager::fileExists(const std::string& path) const {
    std::ifstream file(path);
    return (bool)file;
};


void FileManager::clearFile(const std::string& path) const {
    std::ofstream file(path, std::ios::out);
    if (!file.is_open()) {
        std::cout << "Error: Cannot open file at path: " << path << "\n";
        return;
    }
};
