#ifndef RSA_H
#define RSA_H
#include <vector>
void rsaKeygen(int p, int q, int &n, int &e, int &d);
std::vector<long long> rsaEncrypt(const std::vector<char>& data, int e, int n);
std::vector<char> rsaDecrypt(const std::vector<long long>& data, int d, int n);
#endif
