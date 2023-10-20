#include"ReadFile.h"

ReadFile::ReadFile(fs::path filepath) {
	file.open(filepath, std::ios::binary);
	ReadFileToBuffer(0);
}

int64_t ReadFile::GetElement(int index)
{
	if (!IsElementInBuffer(index)) {
		ReadFileToBuffer(index);
	}

	return buffer[index - buffer_offset];
}

bool ReadFile::IsElementInBuffer(int index) {
	return (index >= buffer_offset) && (index <= buffer_size + buffer_offset - 1);
}

size_t ReadFile::GetElementCount()
{
	file.seekg(0, std::ios::end);
	size_t file_size = file.tellg();
	return file_size / sizeof(int64_t);
}

void ReadFile::ReadFileToBuffer(int index) {

	index = std::max(0, index - 2);

	int elements_left_to_read = GetElementCount() - index;
	int elements_to_read = std::min(buffer_size, elements_left_to_read);

	file.seekg(index * sizeof(int64_t), std::ios_base::beg);
	file.read((char*)&buffer, sizeof(int64_t) * elements_to_read);

	buffer_offset = index;
}