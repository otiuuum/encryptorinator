// fileops.h — работа с бинарными файлами
#ifndef FILEOPS_H
#define FILEOPS_H
#include <vector>
std::vector<char> readFile(const char* filename);
void writeFile(const char* filename, const std::vector<char>& data);
#endif
