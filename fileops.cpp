// fileops.cpp
#include "fileops.h"
#include <fstream>
#include <vector>
using namespace std;

vector<char> readFile(const char* filename) {
    ifstream file(filename, ios::binary);
    vector<char> data;
    if (file) {
        file.seekg(0, ios::end);
        size_t size = file.tellg();
        data.resize(size);
        file.seekg(0, ios::beg);
        file.read(data.data(), size);
    }
    return data;
}

void writeFile(const char* filename, const vector<char>& data) {
    ofstream file(filename, ios::binary);
    file.write(data.data(), data.size());
}
