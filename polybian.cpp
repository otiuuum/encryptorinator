#include <vector>
#include <string>
#include "polybian.h"

std::vector<char> polybianEncrypt(const std::vector<char>& data, int size, const std::string& password_pol) {
    std::vector<char> cipher(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char val = static_cast<unsigned char>(data[i]);
        unsigned char key = password_pol[i % password_pol.length()];
        cipher[i] = val ^ key;  // цикличный XOR с каждым символом пароля
    }
    return cipher;
}

std::vector<char> polybianDecrypt(const std::vector<char>& data, int size) {
    std::vector<char> plain(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char key = (i * size + 17) % 256;
        plain[i] = data[i] ^ key;  // тот же XOR обратно
    }
    return plain;
}