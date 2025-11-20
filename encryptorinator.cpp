#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include "rsa.h"
#include "polybian.h"
#include "doublechange.h"
#include "fileops.h"
using namespace std;

int main () {
    while (true) {
    cout << "Выберите действие:\n"
              << "1) Ввести текст и сохранить в файл\n"
              << "2) Зашифровать файл\n"
              << "3) Расшифровать файл\n"
              << "4) Напечатать файл\n"
              << "0) Выход\n";
    int action;
    cin >> action;
    
    switch(action) {
        case 0:
            return 0;
        case 1: {
            // ввод текста и сохранение
            string fname; 
            cout << "Имя файла для сохранения: "; 
            cin >> fname;
            cout << "Введите текст:\n";
            cin.ignore();
            string text;
            getline(cin, text);
            vector<char> data(text.begin(), text.end());
            writeFile(fname.c_str(), data);
            break;
        }
        case 4: {
            // печать файла
            string fname; 
            cout << "Имя файла: "; 
            cin >> fname;
            vector<char> data = readFile(fname.c_str());
            for (char c : data) cout << c;
            cout << "\n";
            break;
        }
        case 2:
        case 3: {
            // шифрование или дешифровка
            bool encrypt = (action == 2);
            string infile, outfile;
            cout << "Имя входного файла: "; cin >> infile;
            cout << "Имя выходного файла: "; cin >> outfile;
            vector<char> data = readFile(infile.c_str());
            
            cout << "Выберите способ (1-RSA, 2-Двойная перестановка, 3-Полибианский квадрат): ";
            int choice; cin >> choice;

            switch(choice) {
                case 1: {
                    int p, q; 
                    cout << "Введите два простых числа p и q: ";
                    cin >> p >> q;
                    int n,e,d; 
                    rsaKeygen(p,q,n,e,d);
                    if (encrypt) {
                        vector<long long> enc = rsaEncrypt(data, e, n);
                        ofstream out(outfile, ios::binary);
                        for(long long val : enc) out.write((char*)&val, sizeof(val));
                    } else {
                        ifstream in(outfile, ios::binary);
                        vector<long long> enc;
                        while (in) {
                            long long val;
                            in.read((char*)&val, sizeof(val));
                            if (!in) break;
                            enc.push_back(val);
                        }
                        vector<char> dec = rsaDecrypt(enc, d, n);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                case 2: {
                    int cols, rows;
                    cout << "Размер допустимых данных = <столбцы>*<строки> байт. Применяется блочное шифрование."; 
                    cin >> cols >> rows;
                    vector<int> keyCols(cols), keyRows(rows);
                    cout << "Ключ перестановки столбцов (" << cols << " чисел): ";
                    for(int i=0;i<cols;i++) cin>>keyCols[i];
                    cout << "Ключ перестановки строк (" << rows << " чисел): ";
                    for(int i=0;i<rows;i++) cin>>keyRows[i];
                    if (encrypt) {
                        vector<char> enc = doubleEncrypt(data, keyRows, keyCols); //с двух сторон нельзя использовать то ли string
                                                                                        //то ли vector char
                        writeFile(outfile.c_str(), enc);
                    } else {
                        vector<char> dec = doubleDecrypt(data, keyRows, keyCols);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                case 3: {
                    int size;
                    string password_pol;
                    cout << "Размер таблицы (напр., 10 для 10x10): "; 
                    cin >> size;
                    cout << "Введите пароль: ";
                    getline(cin, password_pol);
                    if (encrypt) {
                        vector<char> enc = polybianEncrypt(data, size, password_pol);
                        writeFile(outfile.c_str(), enc);
                    } else {
                        vector<char> dec = polybianDecrypt(data, size, password_pol);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                default:
                    cout << "Неверный вариант шифра\n";
            }
            break;
        }
        default:
            cout << "Неверный выбор\n";
    }
}
}