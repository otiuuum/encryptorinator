#include <vector>
#include "polybian.h"

std::vector<char> polybianEncrypt(const std::vector<char>& data, int size) {
    std::vector<char> cipher(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char val = static_cast<unsigned char>(data[i]);
        unsigned char key = (i * size + 17) % 256;  // простая зависимость от size
        cipher[i] = val ^ key;  // XOR
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