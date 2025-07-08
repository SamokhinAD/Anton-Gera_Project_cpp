/**
 * @file main.cpp
 * @brief Главная программа для работы с различными шифрами
 * @details Это основная программа, которая позволяет выбрать один из шести исторических криптографических
 * шифров: аффинный, Виженера, RSA, простой замены, Хилла, Вернама. После выбора запускается соответствующий
 *          алгоритм шифрования. Управление происходит через нажатие клавиш
 */

#include "Affin_Shifr.h"
#include "Hill.h"
#include "RSA.h"
#include "Simple_sub.h"
#include "Vernam.h"
#include "Vij.h"
#include <conio.h>
#include <iostream>
#include <limits>

/**
 * @brief Главная функция программы - точка входа
 * @return 0 при успешном завершении программы
 * @details Показывает меню выбора шифров и ждёт нажатия клавиш:
 *          - 1: запускает аффинный шифр
 *          - 2: запускает шифр Виженера
 *          - 3: запускает RSA
 *          - 4: запускает шифр простой замены
 *          - 5: запускает шифр Хилла
 *          - 6: запускает шифр Вернама
 *          - Esc: выход из программы
 */
int main() {
  setlocale(LC_ALL, "en_US.UTF-8");

  std::cout << "Выберите шифр:\n";
  std::cout << "1. Аффинный шифр\n";
  std::cout << "2. Шифр Виженера по лозунгу\n";
  std::cout << "3. RSA\n";
  std::cout << "4. Шифр простой замены\n";
  std::cout << "5. Шифр Хилла\n";
  std::cout << "6. Шифр Вернама\n";
  std::cout << "0. Выход\n";
  std::cout << "Введите номер (0-6): ";

  int flag = 1;
  while (true) {
    if (_kbhit()) {
      int num = _getch();
      if (num == 27) {
        break;
      }
      if (flag == 1) {
        if (num == 49) {
          std::cout << "\n";
          flag = 0;
          main_Aff("-1", "-1", "-1", 0);
        }
        if (num == 50) {
          std::cout << "\n";
          flag = 0;
          main_Vij("-1", "-1", "-1", 0);
        }
        if (num == 51) {
          std::cout << "\n";
          flag = 0;
          main_RSA("-1", -1, -1, 0);
        }
        if (num == 52) {
          std::cout << "\n";
          flag = 0;
          string key, text;
          cout
              << "Введите ключ для шифра простой замены (26 уникальных букв): ";
          getline(cin, key);
          cout << "Введите текст для шифрования: ";
          getline(cin, text);

          SimpleSubstitution cipher(key);
          string encrypted = cipher.encrypt(text);
          string decrypted = cipher.decrypt(encrypted);

          cout << "Зашифрованный текст: " << encrypted << endl;
          cout << "Расшифрованный текст: " << decrypted << endl;
        }
        if (num == 53) {
          std::cout << "\n";
          flag = 0;
          vector<vector<int>> key(2, vector<int>(2));
          cout << "Введите ключевую матрицу 2x2 для шифра Хилла (4 целых числа "
                  "через пробел): ";
          for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
              cin >> key[i][j];
            }
          }
          cin.ignore();

          string text;
          cout << "Введите текст для шифрования: ";
          getline(cin, text);

          HillCipher cipher(key);
          string encrypted = cipher.encrypt(text);
          string decrypted = cipher.decrypt(encrypted);

          cout << "Зашифрованный текст: " << encrypted << endl;
          cout << "Расшифрованный текст: " << decrypted << endl;
        }
        if (num == 54) {
          std::cout << "\n";
          flag = 0;
          string key, text;
          cout << "Введите ключ для шифра Вернама: ";
          getline(cin, key);
          cout << "Введите текст для шифрования: ";
          getline(cin, text);

          VernamCipher cipher(key);
          string encrypted = cipher.encrypt(text);
          string decrypted = cipher.decrypt(encrypted);

          cout << "Зашифрованный текст: " << encrypted << endl;
          cout << "Расшифрованный текст: " << decrypted << endl;
        }
      }
    }
  }
  return 0;
}
