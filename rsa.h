#ifndef RSA_H
#define RSA_H

#include <string>
#include <vector>

// Простые объявления (прототипы) функций из rsa.cpp

// Быстрое возведение в степень по модулю
unsigned long long modexp(unsigned long long a, unsigned long long e, unsigned long long mod);

// Расширенный алгоритм Евклида
long long egcd(long long a, long long b, long long &x, long long &y);

// Модульная обратная
unsigned long long modinv(unsigned long long a, unsigned long long m);

// Вывод справки
void usage(const char *prog);

// Команды (обработчики)
int cmd_genkeys(unsigned seed);
int cmd_encrypt(unsigned long long n, unsigned long long e, const std::string &message);
int cmd_decrypt(unsigned long long n, unsigned long long d, const std::vector<unsigned long long> &cipher);

#endif // RSA_H
