/**
 * @file rsa.h
 * @brief RSA шифрование - самый популярный алгоритм с открытым ключом
 * @details Этот код реализует базовую версию RSA для шифрования чисел.
 *          RSA работает на основе сложности факторизации больших чисел -
 *          легко перемножить два числа, но сложно разложить результат обратно
 */

#ifndef RSA_H
#define RSA_H

#include <cctype>  // Для tolower()
#include <conio.h> // Для kbhit() и getch()
#include <iostream>
#include <limits>
#include <string>

using namespace std;

/**
 * @brief Находит модульную обратную величину числа
 * @param a Число, для которого ищем обратную величину
 * @param m Модуль (обычно это функция Эйлера)
 * @return Число, которое при умножении на a даёт остаток 1 при делении на m
 * @details Простой способ найти обратное число - перебираем все варианты.
 *          Нужно для вычисления секретного ключа RSA
 */
int mod_inverse(int a, int m) {
  a = a % m;
  for (int x = 1; x < m; x++) {
    if ((a * x) % m == 1) {
      return x;
    }
  }
  return 1;
}

/**
 * @brief Быстрое возведение в степень по модулю
 * @param base Основание степени
 * @param exp Показатель степени
 * @param mod Модуль для вычислений
 * @return Результат (base^exp) mod mod
 * @details Обычное возведение в степень для больших чисел займёт вечность.
 *          Этот алгоритм делает это быстро, используя двоичное представление
 * степени. Основа всех вычислений в RSA
 */
long long stepen(long long base, long long exp, long long mod) {
  /** @brief Результат возведения в степень */
  long long result = 1;
  base = base % mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}

/**
 * @brief Основная функция RSA шифрования и расшифрования
 * @param key Строка с двумя простыми числами через пробел (например "17 19")
 * @param e Открытая экспонента - часть публичного ключа
 * @param text Число для шифрования или расшифрования
 * @param mod Режим: 0 - интерактивный выбор, 1 - шифрование, 2 - расшифрование
 * @return Результат операции - зашифрованное или расшифрованное число
 * @details RSA использует пару ключей: публичный (n,e) для шифрования и
 *          приватный (n,d) для расшифрования. Безопасность основана на том,
 *          что сложно найти d, зная только n и e
 */
int main_RSA(string key_vvod, int e_vvod, int text_vvod, int mod) {
  setlocale(LC_ALL, "en_US.UTF-8");
  cout << "\nПравила выбора параметров для использования алгоритма:" << endl;
  cout << "1. Ключ вводится как пара простых чисел одинаковой размерности - "
          "через пробел;"
       << endl;
  cout << "2. Значение открытой экспоненты выбирается в диапазоне от 2 до "
          "значения функции Эйлера от произведения ключей n и должно быть "
          "взаимно простым с ним;"
       << endl;
  cout << "3. Сообщением является целое число в интервале от 0 до n-1;" << endl;
  cout << "4. При расшифровании используются те же параметры, что и при "
          "зашифровании."
       << endl;

  try {
    cout << "\nВведите ключи шифрования - два простых числа:" << endl;
    /** @brief Ключи, введенные пользователем */
    string key;
    if (key_vvod == "-1") {
      getline(cin, key);
    } else {
      key = key_vvod;
    }

    /** @brief Позиция пробела между двумя простыми числами */
    size_t pos = key.find(' ');
    if (pos == string::npos) {
      throw runtime_error("Некорректный ключ");
    }
    /** @brief Первое простое число */
    int p = stoi(key.substr(0, pos));
    /** @brief Второе простое число */
    int q = stoi(key.substr(pos + 1));

    /** @brief Модуль RSA - произведение двух простых чисел */
    int n = p * q;
    /** @brief Функция Эйлера - количество чисел, взаимно простых с n */
    int f_n = (p - 1) * (q - 1); // Функция Эйлера
    cout << "\nВведите открытую экспоненту - число от 1 до " +
                std::to_string(f_n) + ":"
         << endl;
    int e;
    if (e_vvod == -1) {
      /** @brief Открытая экспонента, введенная пользователем */
      cin >> e;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      e = e_vvod;
    }
    /** @brief Секретная экспонента - обратная к e по модулю f_n */
    int d;
    d = mod_inverse(e, f_n);

    cout << "\nДля зашифрования нажмите -->" << endl;
    cout << "Для расшифрования нажмите <--" << endl;

    while (true) {
      if (_kbhit() || mod != 0) {
        /** @brief Код нажатой стрелки для выбора операции */
        int arrow;
        if (mod == 0) {
          arrow = _getch();
        }
        if (arrow == 77 || mod == 1) {
          cout << "\nВведите открытый текст:" << endl;
          /** @brief Исходное число для шифрования */
          int open_text;
          if (text_vvod == -1) {
            cin >> open_text;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          } else {
            open_text = text_vvod;
          }

          /** @brief Зашифрованное число */
          int shifr;
          shifr = stepen(open_text, e, n);

          cout << "\nШифр-сообщение:" << endl;
          cout << shifr << endl;
          return shifr;
          break;
        } else if (arrow == 75 || mod == 2) {
          cout << "\nВведите шифр-сообщение:" << endl;
          /** @brief Зашифрованное число для расшифрования */
          int shifr;
          if (text_vvod == -1) {
            cin >> shifr;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          } else {
            shifr = text_vvod;
          }

          /** @brief Расшифрованное исходное число */
          int open_text;
          open_text = stepen(shifr, d, n);

          cout << "\nИсходное сообщение:" << endl;
          cout << open_text << endl;
          return open_text;
          break;
        }
      }
    }
  } catch (exception &f) {
    cout << "\nОшибка при проведении криптографической операции." << endl;
    cout << "Проверьте корректность введенных данных." << endl;
  }
  return 0;
}
#endif