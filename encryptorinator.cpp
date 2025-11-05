#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include "rsa.h"

using namespace std;

int main() {
    cout << "=== Encryptorinator (RSA only) ===\n";
    while (true) {
        cout << "\nКоманды: g - сгенерировать ключи, e - зашифровать, d - расшифровать, q - выход\nВыберите: ";
        char opt; if (!(cin >> opt)) break;
        if (opt == 'q' || opt == 'Q') break;

        if (opt == 'g' || opt == 'G') {
            unsigned seed = 0;
            cout << "Введите seed (0 - случайный): ";
            cin >> seed;
            cmd_genkeys(seed);
        } else if (opt == 'e' || opt == 'E') {
            unsigned long long n, e;
            cout << "Введите n и e через пробел: ";
            cin >> n >> e;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите сообщение (строка): ";
            string message;
            getline(cin, message);
            cmd_encrypt(n, e, message);
        } else if (opt == 'd' || opt == 'D') {
            unsigned long long n, d;
            cout << "Введите n и d через пробел: ";
            cin >> n >> d;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите последовательность чисел (через пробел): ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            unsigned long long x;
            vector<unsigned long long> cipher;
            while (ss >> x) cipher.push_back(x);
            cmd_decrypt(n, d, cipher);
        } else {
            cout << "Неизвестная опция.\n";
        }
    }

    cout << "Выход.\n";
    return 0;
}