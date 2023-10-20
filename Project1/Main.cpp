#include"Sorting.h"
#include"ReadFile.h"

int main() {
	
	fs::path input_file = "C:\\Users\\slden\\Desktop\\input_10mb.bin";
	fs::path output_file = "C:\\Users\\slden\\Desktop\\output.bin";

	fs::path  file_B = "C:\\Users\\slden\\Desktop\\file_B.bin";
	fs::path file_C = "C:\\Users\\slden\\Desktop\\file_C.bin";

	auto start = std::chrono::high_resolution_clock::now();

	SplitFile(input_file, file_B, file_C);
	while (true) {
		
		int seq_count = MargeFile(output_file, file_B, file_C);
		if (seq_count== 1) {
			break;
		}

		SplitFile(output_file, file_B, file_C);
	}
	auto end = std::chrono::high_resolution_clock::now();

	if (CheckSortedFile(output_file)) {
		std::cout << "File sorted!" << std::endl;
	}

	std::chrono::duration<float> duration = end - start;
	std::cout << "Duration = " << duration.count() <<  " s " << std::endl;

	return 0;
}
