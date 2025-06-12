/**
 * @file affin_shifr.h
 * @brief Реализация аффинного шифра для криптографических операций
 * @details Данный файл содержит функции для шифрования и расшифрования текста 
 *          с использованием аффинного шифра с заданным алфавитом и ключами
 */

#ifndef AFFIN_SHIFR_H
#define AFFIN_SHIFR_H

#include <iostream>
#include <string>
#include <conio.h>   // Для kbhit() и getch()
#include <cctype>    // Для tolower()

using namespace std;

/**
 * @brief Вычисляет модульную мультипликативную обратную величину
 * @param a Число, для которого ищется обратная величина
 * @param m Модуль (основание модульной арифметики)
 * @return Модульная обратная величина числа a по модулю m
 * @details Использует простой алгоритм перебора для нахождения числа x,
 *          такого что (a * x) ≡ 1 (mod m)
 */
int mod_inv(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

/**
 * @brief Основная функция для выполнения операций аффинного шифрования/расшифрования
 * @param alphabet Алфавит для криптографических операций
 * @param key Строка с ключами шифрования (два числа через пробел: "a b")
 * @param text Текст для обработки (открытый или зашифрованный)
 * @param mod Режим работы: 0 - интерактивный, 1 - шифрование, 2 - расшифрование
 * @return Результат криптографической операции (зашифрованный или расшифрованный текст)
 * @details Реализует аффинный шифр с формулами:
 *          - Шифрование: E(x) = (a*x + b) mod m
 *          - Расшифрование: D(y) = ((y - b) * a^(-1)) mod m
 *          где a, b - ключи шифрования, m - размер алфавита
 */
string main_Aff(string alphabet, string key, string text, int mod) {
    setlocale(LC_ALL, "en_US.UTF-8");
    cout << "\nПравила выбора параметров для использования алгоритма:" << endl;
    cout << "1. Алфавит может состоять из любого количества любых символов;" << endl;
    cout << "2. Ключ вводится как пара положительных чисел через пробел - числа не должны превышать размерность алфавита, первое число должно быть взаимно простым с размерностью алфавита;" << endl;
    cout << "3. Открытый текст должен состоять ТОЛЬКО из символов введенного алфавита;" << endl;
    cout << "4. При расшифровании используются те же параметры, что и при зашифровании." << endl;
    try {
        cout << "\nВведите алфавит для проведения криптографических операций:" << endl;
        if(alphabet == "-1")
        {
            /** @brief Локальная переменная для хранения введенного алфавита */
            string alphabet;
            getline(cin, alphabet);
        }
        /** @brief Размер алфавита (модуль для аффинного шифра) */
        int m = alphabet.length();

        cout << "\nВведите ключи шифрования:" << endl;
        if(key == "-1")
        {
            /** @brief Локальная переменная для хранения введенного ключа */
            string key;
            getline(cin, key);
        }

        /** @brief Позиция пробела в строке ключа для разделения параметров a и b */
        size_t pos = key.find(' ');
        if (pos == string::npos) {
            throw runtime_error("Некорректный ключ");
        }
        /** @brief Первый ключ аффинного шифра (мультипликативный) */
        int a = stoi(key.substr(0, pos)) % m;
        /** @brief Второй ключ аффинного шифра (аддитивный) */
        int b = stoi(key.substr(pos + 1)) % m;

        cout << "\nДля зашифрования нажмите -->" << endl;
        cout << "Для расшифрования нажмите <--" << endl;

        while (true) {
            if (_kbhit() || mod != 0) {
                /** @brief Код нажатой клавиши для выбора операции */
                int arrow;
                if(mod == 0){arrow = _getch();}
                if (arrow == 77 || mod == 1) {
                    cout << "\nВведите открытый текст:" << endl;
                    /** @brief Открытый текст для шифрования */
                    string open_text;
                    if(text == "-1"){getline(cin, open_text);}
                    else {open_text = text;}
                    
                    for (auto &c : open_text) {
                        c = tolower(c);
                    }
                    
                    /** @brief Результирующий зашифрованный текст */
                    string shifr_text = "";
                    for (size_t i = 0; i < open_text.length(); i++) {
                        /** @brief Индекс символа в алфавите */
                        size_t index = alphabet.find(open_text[i]);
                        if (index == string::npos) {
                            shifr_text += "";
                        } else {
                            /** @brief Индекс зашифрованного символа */
                            int shifr_ind = (a * index + b) % m;
                            shifr_text += alphabet[shifr_ind];
                        }
                    }
                    
                    cout << "\nШифртекст:" << endl;
                    cout << shifr_text << endl;
                    return shifr_text;
                    break;
                } 
                else if (arrow == 75 || mod == 2) {
                    cout << "\nВведите шифртекст:" << endl;
                    /** @brief Зашифрованный текст для расшифрования */
                    string shifr_text;
                    if(text == "-1"){getline(cin, shifr_text);}
                    else {shifr_text = text;}
                    
                    for (auto &c : shifr_text) {
                        c = tolower(c);
                    }
                    
                    /** @brief Результирующий расшифрованный текст */
                    string open_text = "";
                    /** @brief Модульная обратная величина ключа a */
                    int inv_a = mod_inv(a, m);
                    
                    for (size_t i = 0; i < shifr_text.length(); i++) {
                        /** @brief Индекс зашифрованного символа в алфавите */
                        size_t index = alphabet.find(shifr_text[i]);
                        if (index == string::npos) {
                            open_text += "";
                        } else {
                            // Формула расшифрования: D(y) = ((y - b) * a^(-1)) mod m
                            /** @brief Индекс расшифрованного символа */
                            int open_ind = (index - b + m) % m;
                            open_ind = (open_ind * inv_a) % m;
                            open_text += alphabet[open_ind];
                        }
                    }
                    
                    cout << "\nОткрытый текст:" << endl;
                    cout << open_text << endl;
                    return open_text;
                    break;
                }
            }
        }
    }
    catch (exception &e) {
        cout << "\nОшибка при проведении криптографической операции;" << endl;
        cout << "Проверьте корректность введенных данных." << endl;
    }
    return 0;
}
#endif