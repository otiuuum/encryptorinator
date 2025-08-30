#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Функция для возведения числа a в степень b по модулю n
unsigned long long  modExp(unsigned long long  a, unsigned long long  b, unsigned long long  n) {
    unsigned long long  result = 1;
    a = a % n;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % n;
        a = (a * a) % n;
        b = b / 2;
    }
    return result;
}

bool primecheck(unsigned long long  p) { // Изменен тип на unsigned long long 
    if (p <= 1) return false;
    if (p == 2) return false; // 2 нельзя использовать получается прикол
    if (p % 2 == 0) return false;
    for (unsigned long long  i = 3; i * i <= p; i += 2) // Изменен тип на unsigned long long 
        if (p % i == 0) return false;
    return true;
}

// Функция для проверки, является ли число первообразным корнем
bool is_primitive_root(unsigned long long  g, unsigned long long  p, const vector<unsigned long long >& factors) {
    for (unsigned long long  q : factors) {
        if (modExp(g, (p - 1) / q, p) == 1)
            return false;
    }
    return true;
}

// Функция для вычисления обратного элемента по модулю
unsigned long long  modInverse(unsigned long long  a, unsigned long long  m) {
    a = a % m;
    for (unsigned long long  x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

vector<unsigned long long > findPrimitiveRoots(unsigned long long  p) {
    vector<unsigned long long > roots;
    
    // Специальный случай для p = 2
    if (p == 2) {
        roots.push_back(1);
        return roots;
    }

    // Факторизация p-1
    unsigned long long  n = p - 1;
    vector<unsigned long long > factors;
    unsigned long long  temp = n;
    
    // Находим уникальные простые делители p-1
    for (unsigned long long  i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            factors.push_back(i);
            while (temp % i == 0)
                temp /= i;
        }
    }
    if (temp > 1)
        factors.push_back(temp);

    // Поиск первообразных корней
    for (unsigned long long  g = 2; g < p; ++g) {
        if (is_primitive_root(g, p, factors))
            roots.push_back(g);
    }

    return roots;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(0));

    // Параметры алгоритма (простые число и генератор)
    unsigned long long  g, p;
    
    // Ввод и проверка простого числа
    cout << "Введите большое простое целое число: ";
    cin >> p;
    while (!primecheck(p)) {
        cout << "Число не подходит, попробуйте другое: ";
        cin >> p;
    }
    
    // Находим первообразные корни
    vector<unsigned long long > primitive_roots = findPrimitiveRoots(p);
    cout << "Доступные первообразные корни по модулю " << p << ": ";
    for (size_t i = 0; i < min(primitive_roots.size(), static_cast<size_t>(10)); ++i) {
        cout << primitive_roots[i] << " ";
    }
    if (primitive_roots.size() > 10) cout << "...";
    cout << endl;
    
    // Ввод и проверка первообразного корня
    cout << "Введите первообразный корень по модулю p: ";
    cin >> g;
    
    // Факторизация p-1 для проверки
    unsigned long long  n = p - 1;
    vector<unsigned long long > factors;
    unsigned long long  temp = n;
    for (unsigned long long  i = 2; i * i <= temp; ++i) {
        if (temp % i == 0) {
            factors.push_back(i);
            while (temp % i == 0)
                temp /= i;
        }
    }
    if (temp > 1)
        factors.push_back(temp);
    
    while (!is_primitive_root(g, p, factors)) {
        cout << "Число не является первообразным корнем, попробуйте другое: ";
        cin >> g;
    }
    
    // Генерация ключей
    unsigned long long  x = rand() % (p - 2) + 1; // Секретный ключ (1 <= x <= p-2)
    unsigned long long  y = modExp(g, x, p);      // Открытый ключ

    cout << "Параметры системы:" << endl;
    cout << "p = " << p << endl;
    cout << "g = " << g << endl;
    cout << "Секретный ключ x = " << x << endl;
    cout << "Открытый ключ y = " << y << "\n" << endl;

    // Очистка буфера ввода
    cin.ignore();
    
    // Ввод исходного текста
    string message;
    cout << "Введите сообщение для шифрования: ";
    getline(cin, message);

    // Преобразование сообщения в числовой формат
    vector<unsigned long long > plaintext;
    for (char c : message) {
        plaintext.push_back(static_cast<unsigned long long >(c));
    }

    // Шифрование
    vector<pair<unsigned long long , unsigned long long >> ciphertext;
    for (unsigned long long  m : plaintext) {
        unsigned long long  k = rand() % (p - 2) + 1; // Случайное число k
        unsigned long long  a = modExp(g, k, p);
        unsigned long long  b = (modExp(y, k, p) * m) % p;
        ciphertext.emplace_back(a, b);
    }

    cout << "Зашифрованное сообщение (пары (a, b)):" << endl;
    for (const auto& pair : ciphertext) {
        cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    cout << "\n" << endl;

    // Дешифрование
    vector<unsigned long long > decrypted;
    for (const auto& pair : ciphertext) {
        unsigned long long  a = pair.first;
        unsigned long long  b = pair.second;
        unsigned long long  s = modExp(a, x, p);
        unsigned long long  inverse_s = modInverse(s, p);
        unsigned long long  m_decrypted = (b * inverse_s) % p;
        decrypted.push_back(m_decrypted);
    }

    // Преобразование числового формата обратно в текст
    string recovered_message;
    for (unsigned long long  num : decrypted) {
        recovered_message += static_cast<char>(num);
    }

    cout << "Расшифрованное сообщение: " << recovered_message << endl;

    return 0;
}