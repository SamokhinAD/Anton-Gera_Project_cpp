/**
 * @file test_main.cpp
 * @brief Тесты для всех криптографических алгоритмов
 * @details Этот файл проверяет, что все шифры работают правильно.
 *          Каждый тест сначала шифрует текст, потом расшифровывает его обратно
 *          и проверяет, что получился исходный текст
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Affin_Shifr.h"
#include "RSA.h"
#include "Vij.h"

/**
 * @brief Тестирование аффинного шифра
 * @details Проверяем, что аффинный шифр корректно работает в обе стороны:
 *          - Шифруем фразу "hello world" с ключами (5, 8)
 *          - Расшифровываем полученный результат обратно
 *          - Убеждаемся, что получили исходный текст
 */
TEST_CASE("Testing Affin_Shifr functions") {
    /** @brief Проверка шифрования: "hello world" должно стать "qbjjydkymjx" */
    CHECK(main_Aff("abcdefghijklmnopqrstuvwxyz ", "5 8", "hello world", 1) == "qbjjydkymjx");
    
    /** @brief Проверка расшифрования: "qbjjydkymjx" должно вернуться к "hello world" */
    CHECK(main_Aff("abcdefghijklmnopqrstuvwxyz ", "5 8", "qbjjydkymjx", 2) == "hello world");
}

/**
 * @brief Тестирование шифра Виженера
 * @details Проверяем работу шифра Виженера с ключевым словом "rus":
 *          - Шифруем слово "helloworld" 
 *          - Расшифровываем результат обратно
 *          - Проверяем, что всё работает как надо
 */
TEST_CASE("Testing Vij functions") {
    /** @brief Проверка шифрования: "helloworld" с ключом "rus" должно дать "yydciofldu" */
    CHECK(main_Vij("abcdefghijklmnopqrstuvwxyz", "rus", "helloworld", 1) == "yydciofldu");
    
    /** @brief Проверка расшифрования: "yydciofldu" должно вернуться к "helloworld" */
    CHECK(main_Vij("abcdefghijklmnopqrstuvwxyz", "rus", "yydciofldu", 2) == "helloworld");
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