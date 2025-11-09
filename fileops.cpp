// fileops.cpp
#include "fileops.h"
#include <fstream>
#include <vector>

std::vector<char> readFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<char> data;
    if (file) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        data.resize(size);
        file.seekg(0, std::ios::beg);
        file.read(data.data(), size);
    }
    return data;
}

void writeFile(const char* filename, const std::vector<char>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(data.data(), data.size());
}
