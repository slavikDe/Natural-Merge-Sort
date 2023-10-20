#include"Sorting.h"


void SplitFile(fs::path input_file, fs::path file_b, fs::path file_C)
{
	ReadFile input(input_file);
	WriteFile b_buffer(file_b), C_buffer(file_C);
	size_t element_count = input.GetElementCount();

	size_t offset = 0;
	int count = 0;

	while (true) {

		WriteSequenceToFile(input, b_buffer, offset);
		count++;
		if (offset + 1 >= element_count) {
			break;
		}
		WriteSequenceToFile(input, C_buffer, offset);

		count++;
		if (offset + 1 >= element_count) {
			break;
		}
	}

	b_buffer.Flush();
	C_buffer.Flush();
}

int MargeFile(fs::path output_file, fs::path file_b, fs::path file_c)
{
	size_t b_offset = 0, c_offset = 0;
	ReadFile b_buffer(file_b), c_buffer(file_c);
	WriteFile output(output_file);
	size_t b_buffer_size = b_buffer.GetElementCount();
	size_t c_buffer_size = c_buffer.GetElementCount();

	int in1 = 0;

	while (b_buffer_size > b_offset && c_buffer_size > c_offset) {
		MargeSequence(output, b_buffer, c_buffer, b_offset, c_offset);
		in1++;
	}

	output.Flush();

	return in1;
}

void MargeSequence(WriteFile& output, ReadFile& b_buffer, ReadFile& c_buffer, size_t& b_offset, size_t& c_offset)
{
	size_t b_buffer_size = b_buffer.GetElementCount();
	size_t c_buffer_size = c_buffer.GetElementCount();
	int64_t number_buffer_b, number_buffer_c;
	bool b_seq_end = true, c_seq_end = true;

	if (b_offset < b_buffer_size) {
		number_buffer_b = b_buffer.GetElement(b_offset);
		b_seq_end = false;
	}


	if (c_offset < c_buffer_size) {

		number_buffer_c = c_buffer.GetElement(c_offset);
		c_seq_end = false;
	}

	while (!b_seq_end || !c_seq_end)
	{
		if ((number_buffer_b < number_buffer_c || c_seq_end) && !b_seq_end) {
			output.AddElementToEnd(number_buffer_b);
			b_offset++;
			bool is_end_of_file = b_offset == b_buffer_size;
			if (is_end_of_file) {
				b_seq_end = true;
				continue;
			}
			int64_t next_element = b_buffer.GetElement(b_offset);
			b_seq_end = number_buffer_b > next_element;
			number_buffer_b = next_element;
		}
		else if (!c_seq_end) {
			output.AddElementToEnd(number_buffer_c);
			c_offset++;
			bool is_end_of_file = c_offset == c_buffer_size;
			if (is_end_of_file) {
				c_seq_end = true;
				continue;
			}
			int64_t next_element = c_buffer.GetElement(c_offset);
			c_seq_end = number_buffer_c > next_element;
			number_buffer_c = next_element;
		}
	}

}

void Pritbuffer(ReadFile& file) {
	size_t size = file.GetElementCount();

	for (size_t i = 0; i < size; i++)
	{
		std::cout << file.GetElement(i) << std::endl;
	}

	std::cout << std::endl;
}

void AddingbalanceToFile(ReadFile& src, WriteFile& dist, size_t& offset)
{
	size_t element_count = src.GetElementCount();
	int64_t num = src.GetElement(offset);

	while (true) {
		dist.AddElementToEnd(num);
		offset++;
		if (offset >= element_count) {
			return;
		}
		num = src.GetElement(offset);
	}
}

void WriteSequenceToFile(ReadFile& src, WriteFile& dst, size_t& offset)
{
	size_t element_count = src.GetElementCount();
	if (element_count == 0) {
		return;
	}
	int64_t num = src.GetElement(offset), next_num;
	dst.AddElementToEnd(num);

	for (; offset < element_count - 1; ) {
		offset++;
		next_num = src.GetElement(offset);
		if (num > next_num) {
			return;
		}

		num = next_num;
		dst.AddElementToEnd(num);
	}
}

bool CheckSortedFile(fs::path output_file)
{
	ReadFile output(output_file);
	size_t element_count = output.GetElementCount();
	int64_t number = output.GetElement(0), next_number;

	for (size_t i = 1; i < element_count; i++)
	{
		next_number = output.GetElement(i);
		if (number > next_number) {
			return false;
		}

		number = next_number;
	}
	return true;
}