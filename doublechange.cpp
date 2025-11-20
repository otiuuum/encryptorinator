#include <vector>
#include <string>
#include <algorithm>
#include "doublechange.h"

using namespace std;

// Функция для шифрования методом двойной перестановки
std::vector<char> doubleEncrypt(const std::vector<char>& data, const vector<int>& keyRows, const vector<int>& keyCols) {
    int n = keyRows.size();
    int m = keyCols.size();
    
    // Создаем и заполняем таблицу
    vector<vector<char>> table(n, vector<char>(m));
    int pos = 0;
    for (int i = 0; i < n && pos < data.size(); i++) {
        for (int j = 0; j < m && pos < data.size(); j++) {
            table[i][j] = data[pos++];
        }
    } //эт вообще че такое *убрал, случайно попало
    
    // Применяем перестановки
    std::vector<char> result;
    // Вторая перестановка (по столбцам)
    for (int col : keyCols) {
        // Первая перестановка (по строкам)
        for (int row : keyRows) {
            if (row < n && col < m) {
                result.push_back(table[row][col]);
            }
        }
    }
    
    return result;
}

// Функция для дешифрования методом двойной перестановки
std::vector<char> doubleDecrypt(const std::vector<char>& data, const vector<int>& keyRows, const vector<int>& keyCols) {
    int n = keyRows.size();
    int m = keyCols.size();
    
    // Создаем пустую таблицу
    vector<vector<char>> table(n, vector<char>(m, ' '));
    
    // Обратное заполнение таблицы
    int pos = 0;
    for (int col : keyCols) {
        for (int row : keyRows) {
            if (row < n && col < m && pos < data.size()) {
                table[row][col] = data[pos++];
            }
        }
    }
    
    // Чтение текста по порядку
    std::vector<char> result;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] != ' ') {
                result.push_back(table[i][j]);
            }
        }
    }
    
    return result;
}
