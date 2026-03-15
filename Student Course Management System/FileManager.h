#pragma once 
#include <vector>
#include <string>
#include <fstream>
#include <optional>
#include <iostream>

class FileManager
{
public:
	FileManager() = default;
	std::optional <std::vector<std::string>> readAllLines(const std::string& path) const;
	std::optional<std::string> readLine(const std::string& path, size_t index) const;

	void writeAllLines(const std::string& path, const std::vector<std::string>& lines) const;
	void writeLine(const std::string& path, size_t id, const std::string& newLine) const;
	void appendLine(const std::string& path,const std::string & line) const;


	bool fileExists(const std::string& path) const;
	void clearFile(const std::string& path) const;
};

