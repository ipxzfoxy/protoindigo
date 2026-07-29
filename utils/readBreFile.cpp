#include "readBreFile.h"
#include <filesystem>

namespace wave {
	std::string readBreFile(const std::string& path) {
		std::filesystem::path filePath = std::filesystem::current_path() / path;
		std::ifstream file(filePath);

		if (!std::filesystem::exists(filePath))
		{
			std::filesystem::path extension = std::filesystem::current_path() / (path + ".bre");
			
			if (std::filesystem::exists(extension))
			{
				file = std::ifstream(extension);
			} else {
				std::cerr << "Error to read file: File not Found:" << std::endl;
				std::cout << filePath << std::endl;
				exit(1);
			}
		}
		if (!file.is_open()) {
			std::cerr << "Error to read file: Unknown" << std::endl;
			std::cout << filePath << std::endl;
			exit(1);
		}

		std::string code;
		std::string line;

		while (std::getline(file, line)) code += line + "\n";

		

		return code;
	}

}

// copyright (c) 2026 Victor Botelho Anunciação