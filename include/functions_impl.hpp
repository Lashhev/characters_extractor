#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

void glob_files_in_dir(const std::string& dir, std::vector<std::string>& files);
