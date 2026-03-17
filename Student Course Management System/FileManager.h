#pragma once
#include <string>
#include <vector>
#include <optional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>

class FileManager {
public:
    FileManager() = default;

    // File checks and clears
    bool fileExists(const std::string& path) const;
    void clearFile(const std::string& path) const;

    // Line access
    std::optional<std::string> readLine(const std::string& path, size_t index) const;
    std::optional<std::vector<std::string>> readAllLines(const std::string& path) const;

    // Lazy column parsing: return only requested columns
    std::optional<std::vector<std::string>> readLineColumns(
        const std::string& path,
        size_t index,
        const std::vector<size_t>& columns,
        char delimiter = '|'
    ) const;

    // Write / append / delete lines
    void appendLine(const std::string& path, const std::string& line) const;
    void writeLine(const std::string& path, size_t index, const std::string& newLine) const;
    void writeAllLines(const std::string& path, const std::vector<std::string>& lines) const;
    void deleteLine(const std::string& path, size_t index) const;

    // Metadata
    size_t getLineCount(const std::string& path) const;
};