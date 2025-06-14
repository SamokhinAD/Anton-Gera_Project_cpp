#ifndef VERNAM_CIPHER_H
#define VERNAM_CIPHER_H

#include <algorithm>
#include <stdexcept>
#include <string>

/**
 * @class VernamCipher
 * @brief Реализация шифра Вернама (одноразовый блокнот)
 *
 * Класс предоставляет функциональность для шифрования и дешифрования
 * с использованием алгоритма Вернама (XOR-шифрование).
 * Примечание: Для реальной криптографической стойкости ключ должен быть
 * истинно случайным и равным по длине сообщению (одноразовый блокнот).
 */
class VernamCipher {
  std::string key; ///< Ключ для шифрования/дешифрования

public:
  /**
   * @brief Конструктор, инициализирующий ключ шифрования
   * @param k Ключевая строка
   * @throw std::invalid_argument Если ключ пустой
   */
  VernamCipher(const std::string &k) : key(k) {
    if (key.empty()) {
      throw std::invalid_argument("Ключ не может быть пустым");
    }
  }

  /**
   * @brief Шифрует текст с использованием ключа
   * @param plaintext Текст для шифрования
   * @return Зашифрованная строка (бинарные данные)
   */
  std::string encrypt(const std::string &plaintext) {
    return process(plaintext);
  }

  /**
   * @brief Дешифрует текст с использованием ключа
   * @param ciphertext Текст для дешифрования
   * @return Расшифрованная строка
   *
   * @note Для Vernam шифра операции шифрования и дешифрования идентичны
   */
  std::string decrypt(const std::string &ciphertext) {
    return process(ciphertext);
  }

private:
  /**
   * @brief Основная обработка данных (XOR с ключом)
   * @param input Входные данные (открытый текст или шифротекст)
   * @return Результат XOR-операции с ключом
   */
  std::string process(const std::string &input) {
    std::string output;
    for (size_t i = 0; i < input.size(); ++i) {
      char inputChar = input[i];
      char keyChar = key[i % key.size()];
      output += inputChar ^ keyChar;
    }
    return output;
  }
};

#endif // VERNAM_CIPHER_H