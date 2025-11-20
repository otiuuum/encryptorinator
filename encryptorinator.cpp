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

int main () {
    while (true) {
    std::cout << "Выберите действие:\n"
              << "1) Ввести текст и сохранить в файл\n"
              << "2) Зашифровать файл\n"
              << "3) Расшифровать файл\n"
              << "4) Напечатать файл\n"
              << "0) Выход\n";
    int action;
    std::cin >> action;
    
    switch(action) {
        case 0:
            return 0;
        case 1: {
            // ввод текста и сохранение
            std::string fname; 
            std::cout << "Имя файла для сохранения: "; 
            std::cin >> fname;
            std::cout << "Введите текст:\n";
            std::cin.ignore();
            std::string text;
            std::getline(std::cin, text);
            std::vector<char> data(text.begin(), text.end());
            writeFile(fname.c_str(), data);
            break;
        }
        case 4: {
            // печать файла
            std::string fname; 
            std::cout << "Имя файла: "; 
            std::cin >> fname;
            std::vector<char> data = readFile(fname.c_str());
            for (char c : data) std::cout << c;
            std::cout << "\n";
            break;
        }
        case 2:
        case 3: {
            // шифрование или дешифровка
            bool encrypt = (action == 2);
            std::string infile, outfile;
            std::cout << "Имя входного файла: "; std::cin >> infile;
            std::cout << "Имя выходного файла: "; std::cin >> outfile;
            std::vector<char> data = readFile(infile.c_str());
            
            std::cout << "Выберите способ (1-RSA, 2-Двойная перестановка, 3-Полибианский квадрат): ";
            int choice; std::cin >> choice;

            switch(choice) {
                case 1: {
                    int p, q; 
                    std::cout << "Введите два простых числа p и q: ";
                    std::cin >> p >> q;
                    int n,e,d; 
                    rsaKeygen(p,q,n,e,d);
                    if (encrypt) {
                        std::vector<long long> enc = rsaEncrypt(data, e, n);
                        std::ofstream out(outfile, std::ios::binary);
                        for(long long val : enc) out.write((char*)&val, sizeof(val));
                    } else {
                        std::ifstream in(outfile, std::ios::binary);
                        std::vector<long long> enc;
                        while (in) {
                            long long val;
                            in.read((char*)&val, sizeof(val));
                            if (!in) break;
                            enc.push_back(val);
                        }
                        std::vector<char> dec = rsaDecrypt(enc, d, n);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                case 2: {
                    int cols, rows;
                    std::cout << "Размер допустимых данных = <столбцы>*<строки> байт. Применяется блочное шифрование."; 
                    std::cin >> cols >> rows;
                    std::vector<int> keyCols(cols), keyRows(rows);
                    std::cout << "Ключ перестановки столбцов (" << cols << " чисел): ";
                    for(int i=0;i<cols;i++) std::cin>>keyCols[i];
                    std::cout << "Ключ перестановки строк (" << rows << " чисел): ";
                    for(int i=0;i<rows;i++) std::cin>>keyRows[i];
                    if (encrypt) {
                        std::vector<char> enc = doubleEncrypt(data, keyRows, keyCols); //с двух сторон нельзя использовать то ли string
                                                                                        //то ли vector char
                        writeFile(outfile.c_str(), enc);
                    } else {
                        std::vector<char> dec = doubleDecrypt(data, keyRows, keyCols);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                case 3: {
                    int size;
                    std::string password_pol;
                    std::cout << "Размер таблицы (напр., 10 для 10x10): "; 
                    std::cin >> size;
                    std::cout << "Введите пароль: ";
                    std::getline(std::cin, password_pol);
                    if (encrypt) {
                        std::vector<char> enc = polybianEncrypt(data, size, password_pol);
                        writeFile(outfile.c_str(), enc);
                    } else {
                        std::vector<char> dec = polybianDecrypt(data, size, password_pol);
                        writeFile(outfile.c_str(), dec);
                    }
                    break;
                }
                default:
                    std::cout << "Неверный вариант шифра\n";
            }
            break;
        }
        default:
            std::cout << "Неверный выбор\n";
    }
}
}