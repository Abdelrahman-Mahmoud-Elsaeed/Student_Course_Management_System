#pragma once
#include <string>
#include <optional>
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>

class FileIndexer {
private:
    size_t w;

public:
    FileIndexer(size_t w = 8);
    std::string formatOffset(uint64_t offset) const;


    void buildIndex(const std::string& dataFilePath, const std::string& offsetFilePath) const;

    std::optional<uint64_t> getOffset(const std::string& offsetFilePath, size_t index) const;

    void appendOffset(const std::string& offsetFilePath, uint64_t offset) const;

    std::vector<uint64_t> getAllOffsets(const std::string& offsetFilePath) const;

    void writeAllOffsets(const std::string& offsetFilePath, const std::vector<uint64_t>& offsets) const;

    void updateOffset(const std::string& offsetFilePath, size_t index, uint64_t newOffset) const;

    void deleteOffset(const std::string& offsetFilePath, size_t index) const;

    void clearOffsets(const std::string& offsetFilePath) const;

    size_t getTotalSlots(const std::string& offsetFilePath) const;

    size_t getActiveCount(const std::string& offsetFilePath) const;

};