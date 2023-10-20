#pragma once 
#include<fstream>
#include<filesystem>

namespace fs = std::filesystem;

class WriteFile
{
private:
	static constexpr int buffer_size = 1024 *8;
	int64_t buffer[buffer_size];
	int current_position = 0;
	std::ofstream file;

	void WriteBufferToFile();
	bool IsBufferFull();

public:
	WriteFile(fs::path filepath);
	void AddElementToEnd(int64_t num);
	void Flush();
};
