#ifndef POLYBIAN_H
#define POLYBIAN_H
#include <vector>
std::vector<char> polybiusEncrypt(const std::vector<char>& data, 
                                  int size); // размер таблицы (например 10 для 10×10)
std::vector<char> polybiusDecrypt(const std::vector<char>& data, 
                                  int size);
#endif
