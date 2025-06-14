/**
 * @file test_main.cpp
 * @brief Тесты для всех криптографических алгоритмов
 * @details Этот файл проверяет, что все шифры работают правильно.
 *          Каждый тест сначала шифрует текст, потом расшифровывает его обратно
 *          и проверяет, что получился исходный текст
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Affin_Shifr.h"
#include "Hill.h"
#include "RSA.h"
#include "Simple_sub.h"
#include "Vernam.h"
#include "Vij.h"
#include "doctest.h"

/**
 * @brief Тестирование аффинного шифра
 * @details Проверяем, что аффинный шифр корректно работает в обе стороны:
 *          - Шифруем фразу "hello world" с ключами (5, 8)
 *          - Расшифровываем полученный результат обратно
 *          - Убеждаемся, что получили исходный текст
 */
TEST_CASE("Testing Affin_Shifr functions") {
  /** @brief Проверка шифрования: "hello world" должно стать "qbjjydkymjx" */
  CHECK(main_Aff("abcdefghijklmnopqrstuvwxyz ", "5 8", "hello world", 1) ==
        "qbjjydkymjx");

  /** @brief Проверка расшифрования: "qbjjydkymjx" должно вернуться к "hello
   * world" */
  CHECK(main_Aff("abcdefghijklmnopqrstuvwxyz ", "5 8", "qbjjydkymjx", 2) ==
        "hello world");
}

/**
 * @brief Тестирование шифра Виженера
 * @details Проверяем работу шифра Виженера с ключевым словом "rus":
 *          - Шифруем слово "helloworld"
 *          - Расшифровываем результат обратно
 *          - Проверяем, что всё работает как надо
 */
TEST_CASE("Testing Vij functions") {
  /** @brief Проверка шифрования: "helloworld" с ключом "rus" должно дать
   * "yydciofldu" */
  CHECK(main_Vij("abcdefghijklmnopqrstuvwxyz", "rus", "helloworld", 1) ==
        "yydciofldu");

  /** @brief Проверка расшифрования: "yydciofldu" должно вернуться к
   * "helloworld" */
  CHECK(main_Vij("abcdefghijklmnopqrstuvwxyz", "rus", "yydciofldu", 2) ==
        "helloworld");
}

/**
 * @brief Тестирование RSA шифрования
 * @details Проверяем RSA с простыми числами 3557 и 2579:
 *          - Шифруем число 111111 с открытой экспонентой 3
 *          - Расшифровываем полученный результат
 *          - Убеждаемся, что получили исходное число
 */
TEST_CASE("Testing RSA functions") {
  /** @brief Проверка шифрования: число 111111 должно стать 4051753 */
  CHECK(main_RSA("3557 2579", 3, 111111, 1) == 4051753);

  /** @brief Проверка расшифрования: 4051753 должно вернуться к 111111 */
  CHECK(main_RSA("3557 2579", 3, 4051753, 2) == 111111);
}

/**
 * @brief Тестирование простой замены
 * @details Проверяем работу шифра простой замены с алфавитом
 * "qwertyuiopasdfghjklzxcvbnm":
 *          - Шифруем слово "hello"
 *          - Расшифровываем результат обратно
 *          - Проверяем корректность работы алгоритма
 */
TEST_CASE("Testing SimpleSubstitution functions") {
  SimpleSubstitution sub("qwertyuiopasdfghjklzxcvbnm");
  /** @brief Проверка шифрования: "hello" должно стать "itssg" */
  CHECK(sub.encrypt("hello") == "itssg");
  /** @brief Проверка расшифрования: "itssg" должно вернуться к "hello" */
  CHECK(sub.decrypt("itssg") == "hello");
}

/**
 * @brief Тестирование шифра Хилла
 * @details Проверяем работу шифра Хилла с матрицей [[5, 8], [17, 3]]:
 *          - Шифруем слово "test"
 *          - Расшифровываем результат обратно
 *          - Убеждаемся в корректности преобразований
 */
TEST_CASE("Testing HillCipher functions") {
  HillCipher hill({{3, 3}, {2, 5}});
  /** @brief Проверка шифрования: "test" должно стать "qkiz" */
  CHECK(hill.encrypt("hellox") == "hiozhn");
  /** @brief Проверка расшифрования: "qkiz" должно вернуться к "test" */
  CHECK(hill.decrypt("hiozhn") == "hellox");
}

/**
 * @brief Тестирование шифра Вернама
 * @details Проверяем работу шифра Вернама с ключом "secret":
 *          - Шифруем слово "test"
 *          - Расшифровываем полученный результат
 *          - Проверяем совпадение с исходным текстом
 */
TEST_CASE("Testing VernamCipher functions") {
  VernamCipher vernam("secret");
  std::string encrypted = vernam.encrypt("test");
  /** @brief Проверка полного цикла шифрования-дешифрования */
  CHECK(vernam.decrypt(encrypted) == "test");
}