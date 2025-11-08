#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <wchar.h>

using namespace std;

class PolybianSquare {

private:
    wchar_t square[9][9];  // Размер квадрата
    void initializeSquare() {
        const wchar_t alphabet[] = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,!.\"?*:;-";
        int index = 0;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(index < 81) {  // 33 буквы + 10 цифр
                    square[i][j] = alphabet[index++];
                } else {
                    square[i][j] = L' ';
                }
            }
        }
    }
    
public:
    PolybianSquare() {
        initializeSquare();
    }
    
    void printSquare() {
        wcout << L"Квадрат Полибия:\n";
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                wcout << square[i][j] << L" ";
            }
            wcout << endl;
        }
    }
    
    wstring encrypt(wstring message) {
        wstring result = L"";
        for(wchar_t c : message) {
            // Обрабатываем буквы
            if(iswalpha(c)) {
                c = towupper(c);
                if(c == L'ё') c = L'Ё';
            }
            
            // Ищем символ в квадрате
            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    if(square[i][j] == c) {
                        result += to_wstring(i+1) + to_wstring(j+1);
                        //wcout << L"Найден символ '" << c << L"' на позиции " << (i+1) << (j+1) << endl;
                    }
                }
            }
        }
        return result;
    }
    
    wstring decrypt(wstring code) {
        wstring result = L"";
        for(int i = 0; i < code.length(); i += 2) {
            if(i+1 < code.length()) {
                int row = code[i] - L'1';
                int col = code[i+1] - L'1';
                if(row >= 0 && row < 9 && col >= 0 && col < 9) {
                    result += square[row][col];
                    wcout << L"Расшифровываем позицию " << (row+1) << (col+1) 
                          << L" -> '" << square[row][col] << L"'" << endl;
                }
            }
        }
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    PolybianSquare ps;
    ps.printSquare();
    
    wstring message;
    wcout << L"Введите сообщение для шифрования: ";
    getline(wcin, message);
    
    wcout << L"\nПроцесс шифрования:\n";
    wstring encrypted = ps.encrypt(message);
    wcout << L"\nЗашифрованное сообщение: " << encrypted << endl;
    
    wcout << L"\nПроцесс расшифровки:\n";
    wstring decrypted = ps.decrypt(encrypted);
    wcout << L"\nРасшифрованное сообщение: " << decrypted << endl;
    
    return 0;
}
