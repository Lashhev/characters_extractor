
#include "functions_impl.hpp"

namespace fs = std::filesystem;
using namespace std;

void glob_files_in_dir(const string& dir, vector<string>& files)
{
    for (const auto & entry : fs::directory_iterator(dir))
        files.push_back(entry.path().string());
}

