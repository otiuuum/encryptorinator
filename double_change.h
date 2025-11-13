#ifndef DOUBLE_CHANGE_H
#define DOUBLE_CHANGE_H
#include <vector>
std::vector<char> doubleEncrypt(const std::vector<char>& data, const std::vector<int>& keyRows, const std::vector<int>& keyCols);
std::vector<char> doubleDecrypt(const std::vector<char>& data, const std::vector<int>& keyRows, const std::vector<int>& keyCols);
#endif
