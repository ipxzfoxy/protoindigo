#include "readBreFile.h"
#include <filesystem>

namespace indigo {
	std::string readBreFile(const std::string& path) {
		std::ifstream file(path);

	

		if (!file.is_open()) {
			std::cerr << "Error to readfile." << std::endl;
			std::cout << std::filesystem::current_path() << "\\" << path << std::endl;
			exit(0);
		}

		std::string code;
		std::string line;

		while (std::getline(file, line)) code += line + "\n";

		

		return code;
	}

}

// by Victor Botelho Anunciação