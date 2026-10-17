
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>


namespace bre::internal {

	std::pair<uint8_t, std::string> readFile(const std::string& path);
	std::string getExecutablePath();
}

// copyright (c) 2026 Victor Botelho Anunciação