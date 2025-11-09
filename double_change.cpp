#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Функция для шифрования методом двойной перестановки
string doublePermutationEncrypt(const string& text, const vector<int>& key1, const vector<int>& key2) {
    int n = key1.size();
    int m = key2.size();
    
    // Создаем и заполняем таблицу
    vector<vector<char>> table(n, vector<char>(m));
    int pos = 0;
    for (int i = 0; i < n && pos < text.length(); i++) {
        for (int j = 0; j < m && pos < text.length(); j++) {
            table[i][j] = text[pos++];
        }
    }
    
    // Применяем перестановки
    string result;
    // Вторая перестановка (по столбцам)
    for (int col : key2) {
        // Первая перестановка (по строкам)
        for (int row : key1) {
            if (row < n && col < m) {
                result += table[row][col];
            }
        }
    }
    
    return result;
}

// Функция для дешифрования методом двойной перестановки
string doublePermutationDecrypt(const string& text, const vector<int>& key1, const vector<int>& key2) {
    int n = key1.size();
    int m = key2.size();
    
    // Создаем пустую таблицу
    vector<vector<char>> table(n, vector<char>(m, ' '));
    
    // Обратное заполнение таблицы
    int pos = 0;
    for (int col : key2) {
        for (int row : key1) {
            if (row < n && col < m && pos < text.length()) {
                table[row][col] = text[pos++];
            }
        }
    }
    
    // Чтение текста по порядку
    string result;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] != ' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}
