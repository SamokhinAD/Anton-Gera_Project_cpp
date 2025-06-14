#ifndef SIMPLE_SUBSTITUTION_H
#define SIMPLE_SUBSTITUTION_H

#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @class SimpleSubstitution
 * @brief Реализация простой подстановочной криптосистемы
 *
 * Класс предоставляет функциональность для шифрования и дешифрования текста
 * с использованием алфавитной подстановки.
 */
class SimpleSubstitution {
  std::unordered_map<char, char>
      encryptMap; ///< Карта для шифрования (символ → замена)
  std::unordered_map<char, char>
      decryptMap; ///< Карта для дешифрования (замена → символ)

public:
  /**
   * @brief Конструктор, инициализирующий подстановочные таблицы
   * @param key Строка из 26 уникальных символов - подстановочный алфавит
   * @throw std::invalid_argument Если ключ не соответствует требованиям
   */
  SimpleSubstitution(const std::string &key) {
    if (key.length() != 26) {
      throw std::invalid_argument("Ключ должен содержать ровно 26 символов");
    }

    for (char c = 'a'; c <= 'z'; ++c) {
      encryptMap[c] = key[c - 'a'];
      decryptMap[key[c - 'a']] = c;
    }
  }

  /**
   * @brief Шифрует текст методом простой подстановки
   * @param plaintext Исходный текст для шифрования
   * @return Зашифрованная строка (неалфавитные символы остаются без изменений)
   */
  std::string encrypt(const std::string &plaintext) {
    std::string ciphertext;
    for (char c : plaintext) {
      if (isalpha(c)) {
        char lower = tolower(c);
        ciphertext += encryptMap[lower];
      } else {
        ciphertext += c;
      }
    }
    return ciphertext;
  }

  /**
   * @brief Дешифрует текст, зашифрованный методом простой подстановки
   * @param ciphertext Зашифрованный текст для дешифрования
   * @return Расшифрованная строка (неалфавитные символы остаются без изменений)
   */
  std::string decrypt(const std::string &ciphertext) {
    std::string plaintext;
    for (char c : ciphertext) {
      if (isalpha(c)) {
        char lower = tolower(c);
        plaintext += decryptMap[lower];
      } else {
        plaintext += c;
      }
    }
    return plaintext;
  }
};

#endif // SIMPLE_SUBSTITUTION_H