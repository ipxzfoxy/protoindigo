#include "filesys.h"

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
	std::string bre::internal::getExecutablePath() {
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);

		std::filesystem::path exepath(buffer);
		return exepath.parent_path().string();
	}
#elif defined(__linux__)
	#include <unistd.h>
	#include <limits.h>
	std::string bre::internal::getExecutablePath() {
		char buffer[PATH_MAX];
		
		ssize_t len = readlink("proc/self/exe", buffer, sizeof(buffer) - 1);

		if (len != -1) {
			buffer[len]  = '\0';
			std::filesystem::path exePath(buffer);
            return exePath.parent_path().string();
		}

		return "";
	}
#elif defined(__APPLE__)
	#include <mach-o/dyld.h>
    #include <climits>

	std::string bre::internal::getExecutablePath() {
        char buffer[PATH_MAX];
        uint32_t size = sizeof(buffer);      
        if (_NSGetExecutablePath(buffer, &size) == 0) {
            std::filesystem::path exePath(buffer);            
            return std::filesystem::canonical(exePath).parent_path().string();
        }
        return "";
    }
#endif

	std::pair<uint8_t, std::string> bre::internal::readFile(const std::string& path) {
		std::filesystem::path filePath = std::filesystem::current_path() / path;
		std::ifstream file(filePath);

		if (!std::filesystem::exists(filePath))
		{
			// In case you forget (or just don't wanna type .bre) :D
			std::filesystem::path extension = std::filesystem::current_path() / (path + ".bre");
			
			if (std::filesystem::exists(extension))
			{
				file = std::ifstream(extension);
			} else
				return {1, ""};
		}
		if (!file.is_open()) {
			return {2, ""};
		}

		std::string content;
		std::string line;

		while (std::getline(file, line)) content += line + "\n";
		return {0,content};
	}

// Copyright (c) 2026 Victor Botelho Anunciação