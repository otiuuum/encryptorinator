#ifndef POLYBIAN_H
#define POLYBIAN_H
#include <string>
std::vector<char> polybianEncrypt(const std::vector<char>& data, int size, const std::string& password_pol);
std::vector<char> polybianDecrypt(const std::vector<char>& data, int size, const std::string& password_pol);
#endif
