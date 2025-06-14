/**
 * @file vij.h
 * @brief Шифр Виженера - простой и надежный способ шифрования текста
 * @details Этот код позволяет зашифровать или расшифровать любой текст
 *          с помощью ключевого слова. Принцип работы: каждая буква текста
 *          сдвигается на позицию соответствующей буквы ключа
 */

#ifndef VIJ_H
#define VIJ_H

#include <cctype>  // Для tolower()
#include <conio.h> // For _kbhit() and _getch()
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Главная функция для работы с шифром Виженера
 * @param alphabet Набор символов, которые можно шифровать (обычно буквы
 * алфавита)
 * @param key_text Ключевое слово для шифрования (будет повторяться по кругу)
 * @param text Текст, который нужно зашифровать или расшифровать
 * @param mod Режим работы: 0 - выбор с клавиатуры, 1 - шифрование, 2 -
 * расшифрование
 * @return Результат работы - зашифрованный или расшифрованный текст
 * @details Шифр работает по принципу: каждая буква исходного текста
 * складывается с соответствующей буквой ключа (для шифрования) или вычитается
 * (для расшифрования)
 */
string main_Vij(string alphabet_vvod, string key_text_vvod, string text_vvod,
                int mod) {
  setlocale(LC_ALL, "en_US.UTF-8");
  cout << "\nПравила выбора параметров для использования алгоритма:" << endl;
  cout << "1. Алфавит может состоять из любого количества любых символов;"
       << endl;
  cout << "2. Ключ составляется из символов веденного алфавита, его длина не "
          "должна превышать размеров будущего открытого текста;"
       << endl;
  cout << "3. Открытый текст должен состоять ТОЛЬКО из символов введенного "
          "алфавита;"
       << endl;
  cout << "4. При расшифровании используются те же параметры, что и при "
          "зашифровании."
       << endl;

  cout << "\nВведите алфавит для проведения криптографических операций:"
       << endl;
  string alphabet;
  if (alphabet_vvod == "-1") {
    /** @brief Алфавит, введенный пользователем */
    getline(cin, alphabet);
  } else {
    alphabet = alphabet_vvod;
  }
  /** @brief Размер алфавита - сколько всего символов можно использовать */
  int m = alphabet.length();

  cout << "\nВведите ключ шифрования:" << endl;
  string key_text;
  if (key_text_vvod == "-1") {
    /** @brief Ключевое слово, введенное пользователем */
    getline(cin, key_text);
  } else {
    key_text = key_text_vvod;
  }
  /** @brief Длина ключевого слова */
  int len_key_text = key_text.length();

  cout << "\nДля зашифрования нажмите -->" << endl;
  cout << "Для расшифрования нажмите <--" << endl;

  while (true) {
    if (_kbhit() || mod != 0) {
      /** @brief Код нажатой стрелки (влево или вправо) */
      int arrow;
      if (mod == 0) {
        arrow = _getch();
      }
      if (arrow == 77 || mod == 1) {
        cout << "\nВведите открытый текст:" << endl;
        /** @brief Текст, который нужно зашифровать */
        string open_text;
        if (text_vvod == "-1") {
          getline(cin, open_text);
        } else {
          open_text = text_vvod;
        }

        for (auto &c : open_text) {
          c = tolower(c);
        }
        /** @brief Длина текста для шифрования */
        int len_open_text = open_text.length();

        /** @brief Гамма - ключевое слово, растянутое на всю длину текста */
        string gamma_text;
        for (int i = 0; i < len_open_text / len_key_text; ++i) {
          gamma_text += key_text;
        }
        gamma_text += key_text.substr(0, len_open_text % len_key_text);

        /** @brief Массив индексов зашифрованных символов */
        vector<int> shifr_array(len_open_text);
        for (int i = 0; i < len_open_text; ++i) {
          shifr_array[i] =
              (alphabet.find(open_text[i]) + alphabet.find(gamma_text[i])) % m;
        }

        /** @brief Итоговый зашифрованный текст */
        string shifr_text = "";
        for (int i : shifr_array) {
          shifr_text += alphabet[i];
        }

        cout << "\nШифртекст:" << endl;
        cout << shifr_text << endl;
        return shifr_text;
        break;
      } else if (arrow == 75 || mod == 2) {
        cout << "\nВведите шифртекст:" << endl;
        /** @brief Зашифрованный текст, который нужно расшифровать */
        string shifr_text;
        if (text_vvod == "-1") {
          getline(cin, shifr_text);
        } else {
          shifr_text = text_vvod;
        }
        /** @brief Длина зашифрованного текста */
        int len_shifr_text = shifr_text.length();

        /** @brief Гамма для расшифрования - то же ключевое слово, растянутое на
         * длину текста */
        string gamma_text;
        for (int i = 0; i < len_shifr_text / len_key_text; ++i) {
          gamma_text += key_text;
        }
        gamma_text += key_text.substr(0, len_shifr_text % len_key_text);

        /** @brief Массив индексов расшифрованных символов */
        vector<int> open_array(len_shifr_text);
        for (int i = 0; i < len_shifr_text; ++i) {
          open_array[i] = (alphabet.find(shifr_text[i]) -
                           alphabet.find(gamma_text[i]) + m) %
                          m;
        }

        /** @brief Итоговый расшифрованный текст */
        string open_text;
        for (int i : open_array) {
          open_text += alphabet[i];
        }

        cout << "\nОткрытый текст:" << endl;
        cout << open_text << endl;
        return open_text;
        break;
      }
    }
  }

  return 0;
}
#endif