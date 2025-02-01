#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include"ReadFile.h"
#include"WriteFile.h"
#include<chrono>

//namespace fs = std::filesystem;
namespace fs = std::filesystem;

void SplitFile(fs::path input_file, fs::path file_B, fs::path file_C);
void WriteSequenceToFile(ReadFile& src, WriteFile& dst, size_t& offset);
int MargeFile(fs::path input_file, fs::path file_B, fs::path file_C);
void MargeSequence(WriteFile& output, ReadFile& B_buffer, ReadFile& C_buffer,  size_t& B_offset, size_t& C_offset);
void AddingBalanceToFile(ReadFile& src, WriteFile& dist, size_t& offset);
bool CheckSortedFile(fs::path output_file);
void PritBuffer(ReadFile& file);