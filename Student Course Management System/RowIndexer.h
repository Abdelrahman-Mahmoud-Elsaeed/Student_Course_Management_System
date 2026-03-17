#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cstdint>

class RowIndexer {
private:
    size_t w; // offset width in bytes

public:
    RowIndexer(size_t width = 8);

    void buildIndex(const std::string& dataFilePath, const std::string& offsetFilePath) const;

    std::optional<uint64_t> getOffset(const std::string& offsetFilePath, size_t index) const;
    void appendOffset(const std::string& offsetFilePath, uint64_t offset) const;
    void updateOffset(const std::string& offsetFilePath, size_t index, uint64_t newOffset) const;
    void deleteOffset(const std::string& offsetFilePath, size_t index) const;
    void clearOffsets(const std::string& offsetFilePath) const;

    void writeAllOffsets(const std::string& offsetFilePath, const std::vector<uint64_t>& offsets) const;
    std::vector<uint64_t> getAllOffsets(const std::string& offsetFilePath) const;

    size_t getTotalSlots(const std::string& offsetFilePath) const;
};