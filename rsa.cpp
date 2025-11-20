#include "rsa.h"
#include <cmath>
using namespace std;

// Вычисление НОД (е. Алгоритм Евклида)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
// Расширенный алгоритм Евклида для обратного элемента
int modInverse(int e, int phi) {
    int a = e, m = phi, m0 = m, x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    if (x1 < 0) x1 += phi;
    return x1;
}
long long modPow(long long base, long long exp, long long mod) {
    long long res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

void rsaKeygen(int p, int q, int &n, int &e, int &d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    // выбираем e: взаимно простое с phi
    e = 3;
    while (gcd(e, phi) != 1) e += 2;
    d = modInverse(e, phi);
}

vector<long long> rsaEncrypt(const vector<char>& data, int e, int n) {
    vector<long long> cipher;
    for (char c : data) {
        long long m = (unsigned char)c;
        cipher.push_back(modPow(m, e, n));
    }
    return cipher;
}
vector<char> rsaDecrypt(const vector<long long>& data, int d, int n) {
    vector<char> plain;
    for (long long C : data) {
        long long m = modPow(C, d, n);
        plain.push_back((char)m);
    }
    return plain;
}
