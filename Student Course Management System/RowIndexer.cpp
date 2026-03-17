#include "RowIndexer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

RowIndexer::RowIndexer(size_t width) : w(width) {}

// ---------------- Build index for existing file ----------------
void RowIndexer::buildIndex(const std::string& dataFilePath, const std::string& offsetFilePath) const {
    std::ifstream dataFile(dataFilePath, std::ios::binary);
    std::ofstream indexFile(offsetFilePath, std::ios::binary | std::ios::trunc);

    if (!dataFile.is_open() || !indexFile.is_open()) {
        std::cout << "Failed to open data or index file\n";
        return;
    }

    uint64_t offset = 0;
    std::string line;
    while (std::getline(dataFile, line)) {
        std::vector<char> buffer(w + 1, 0);
        snprintf(buffer.data(), buffer.size(), "%0*llu", static_cast<int>(w), offset);
        indexFile.write(buffer.data(), w);
        indexFile.put('\n');

        offset = static_cast<uint64_t>(dataFile.tellg());
        if (offset == -1) offset = 0;
    }
}

// ---------------- Single offset operations ----------------
std::optional<uint64_t> RowIndexer::getOffset(const std::string& offsetFilePath, size_t index) const {
    std::ifstream file(offsetFilePath, std::ios::binary);
    if (!file.is_open()) return std::nullopt;

    file.seekg(index * (w + 1));
    std::vector<char> buffer(w + 1, 0);
    file.read(buffer.data(), w);
    if (!file) return std::nullopt;

    std::string s(buffer.data(), w);
    if (s.find_first_not_of(' ') == std::string::npos) return std::nullopt;

    try {
        return std::stoull(s);
    }
    catch (...) {
        return std::nullopt;
    }
}

void RowIndexer::appendOffset(const std::string& offsetFilePath, uint64_t offset) const {
    std::ofstream file(offsetFilePath, std::ios::app | std::ios::binary);
    if (!file.is_open()) return;

    std::vector<char> buffer(w + 1, 0);
    snprintf(buffer.data(), buffer.size(), "%0*llu", static_cast<int>(w), offset);
    file.write(buffer.data(), w);
    file.put('\n');
}

void RowIndexer::updateOffset(const std::string& offsetFilePath, size_t index, uint64_t newOffset) const {
    std::fstream file(offsetFilePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) return;

    std::vector<char> buffer(w + 1, 0);
    snprintf(buffer.data(), buffer.size(), "%0*llu", static_cast<int>(w), newOffset);
    file.seekp(index * (w + 1));
    file.write(buffer.data(), w);
    file.put('\n');
}

void RowIndexer::deleteOffset(const std::string& offsetFilePath, size_t index) const {
    std::fstream file(offsetFilePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) return;

    file.seekp(index * (w + 1));
    std::string empty(w, ' ');
    file.write(empty.c_str(), w);
    file.put('\n');
}

void RowIndexer::clearOffsets(const std::string& offsetFilePath) const {
    std::ofstream file(offsetFilePath, std::ios::out | std::ios::trunc);
}

// ---------------- Bulk operations ----------------
void RowIndexer::writeAllOffsets(const std::string& offsetFilePath, const std::vector<uint64_t>& offsets) const {
    std::ofstream file(offsetFilePath, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) return;

    std::vector<char> buffer(w + 1, 0);
    for (auto offset : offsets) {
        if (offset == std::numeric_limits<uint64_t>::max()) offset = 0; // empty
        snprintf(buffer.data(), buffer.size(), "%0*llu", static_cast<int>(w), offset);
        file.write(buffer.data(), w);
        file.put('\n');
    }
}

std::vector<uint64_t> RowIndexer::getAllOffsets(const std::string& offsetFilePath) const {
    std::ifstream file(offsetFilePath, std::ios::binary);
    std::vector<uint64_t> offsets;
    if (!file.is_open()) return offsets;

    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    if (size <= 0) return offsets;
    size_t count = static_cast<size_t>(size) / (w + 1);
    offsets.reserve(count);

    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(w + 1, 0);
    for (size_t i = 0; i < count; ++i) {
        file.read(buffer.data(), w);
        file.get(); // skip newline
        std::string s(buffer.data(), w);
        if (s.find_first_not_of(' ') == std::string::npos) {
            offsets.push_back(std::numeric_limits<uint64_t>::max());
        }
        else {
            try {
                offsets.push_back(std::stoull(s));
            }
            catch (...) {
                offsets.push_back(std::numeric_limits<uint64_t>::max());
            }
        }
    }
    return offsets;
}

// ---------------- Metadata ----------------
size_t RowIndexer::getTotalSlots(const std::string& offsetFilePath) const {
    std::ifstream file(offsetFilePath, std::ios::binary);
    if (!file.is_open()) return 0;

    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    if (size <= 0) return 0;
    return static_cast<size_t>(size) / (w + 1);
}