#pragma once 
#include<fstream>
#include<filesystem>


namespace fs = std::filesystem;
	

class ReadFile
{
private:
	static constexpr int buffer_size = 1024 * 8;
	int64_t buffer[buffer_size];
	std::ifstream file;
	int buffer_offset;

	void ReadFileToBuffer(int index);
	bool IsElementInBuffer(int index);
public:

	ReadFile(fs::path filepath);
	int64_t GetElement(int index);
	size_t GetElementCount();

};

