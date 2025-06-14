#ifndef HILL_CIPHER_H
#define HILL_CIPHER_H

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @class HillCipher
 * @brief Реализация шифра Хилла для 2x2 матриц
 */
class HillCipher {
private:
  std::vector<std::vector<int>> keyMatrix;
  std::vector<std::vector<int>> inverseMatrix;
  int matrixSize;

  /**
   * @brief Вычисление значения по модулю 26
   * @param value Исходное значение
   * @return Значение по модулю 26
   */
  int mod26(int value) { return (value % 26 + 26) % 26; }

  /**
   * @brief Вычисление обратной матрицы
   * @throw std::runtime_error Если матрица не 2x2 или необратима
   */
  void calculateInverse() {
    if (matrixSize != 2) {
      throw std::runtime_error("Поддерживаются только матрицы 2x2");
    }

    int det =
        keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    det = mod26(det);

    int detInverse = -1;
    for (int i = 1; i < 26; ++i) {
      if ((det * i) % 26 == 1) {
        detInverse = i;
        break;
      }
    }
    if (detInverse == -1) {
      throw std::runtime_error("Матрица необратима");
    }

    inverseMatrix = {{mod26(keyMatrix[1][1] * detInverse),
                      mod26(-keyMatrix[0][1] * detInverse)},
                     {mod26(-keyMatrix[1][0] * detInverse),
                      mod26(keyMatrix[0][0] * detInverse)}};
  }

  /**
   * @brief Подготовка текста для шифрования/дешифрования
   * @param text Исходный текст
   * @return Обработанный текст (только буквы в нижнем регистре, дополненные 'x'
   * при необходимости)
   */
  std::string processText(const std::string &text) {
    std::string result;
    for (char c : text) {
      if (isalpha(c)) {
        result += tolower(c);
      }
    }
    while (result.size() % matrixSize != 0) {
      result += 'x';
    }
    return result;
  }

public:
  /**
   * @brief Конструктор класса HillCipher
   * @param key Матрица ключа 2x2
   * @throw std::invalid_argument Если ключ не является матрицей 2x2
   */
  HillCipher(const std::vector<std::vector<int>> &key) : keyMatrix(key) {
    matrixSize = key.size();
    if (matrixSize != 2 || key[0].size() != 2) {
      throw std::invalid_argument("Ключ должен быть матрицей 2x2");
    }
    calculateInverse();
  }

  /**
   * @brief Шифрование текста
   * @param plaintext Исходный текст
   * @return Зашифрованный текст
   */
  std::string encrypt(const std::string &plaintext) {
    std::string processed = processText(plaintext);
    std::string ciphertext;

    for (size_t i = 0; i < processed.size(); i += matrixSize) {
      int c1 = processed[i] - 'a';
      int c2 = processed[i + 1] - 'a';

      int e1 = mod26(keyMatrix[0][0] * c1 + keyMatrix[0][1] * c2);
      int e2 = mod26(keyMatrix[1][0] * c1 + keyMatrix[1][1] * c2);

      ciphertext += static_cast<char>(e1 + 'a');
      ciphertext += static_cast<char>(e2 + 'a');
    }
    return ciphertext;
  }

  /**
   * @brief Дешифрование текста
   * @param ciphertext Зашифрованный текст
   * @return Расшифрованный текст
   */
  std::string decrypt(const std::string &ciphertext) {
    std::string plaintext;

    for (size_t i = 0; i < ciphertext.size(); i += matrixSize) {
      int c1 = ciphertext[i] - 'a';
      int c2 = ciphertext[i + 1] - 'a';

      int p1 = mod26(inverseMatrix[0][0] * c1 + inverseMatrix[0][1] * c2);
      int p2 = mod26(inverseMatrix[1][0] * c1 + inverseMatrix[1][1] * c2);

      plaintext += static_cast<char>(p1 + 'a');
      plaintext += static_cast<char>(p2 + 'a');
    }
    return plaintext;
  }
};

#endif // HILL_CIPHER_H