#include"WriteFile.h"

WriteFile::WriteFile(fs::path filepath)
{
	file.open(filepath, std::ios::binary);
}

void WriteFile::Flush()
{
	WriteBufferToFile();
	file.flush();
}

void WriteFile::AddElementToEnd(int64_t num)
{
	if (IsBufferFull()) {
		WriteBufferToFile();
		current_position = 0;
	}

	buffer[current_position] = num;
	current_position++;
}

void WriteFile::WriteBufferToFile() {
	file.write((char*)buffer, sizeof(int64_t) * current_position);
}

bool WriteFile::IsBufferFull() {
	return current_position == buffer_size - 1;
}
