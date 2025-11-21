#pragma once

#include <iostream>
#include <string>
#include <limits> // Для numeric_limits

namespace FootballManagement 
{
    /**
     * @brief Допоміжний клас для валідації введення користувача (формат, діапазон, тип).
     * * Це реалізує вимогу 3 "Кожен блок введення повинен перевіряти коректність даних".
     */
    class InputValidator 
    {
    public:
        // --- ВЛАСНІ МЕТОДИ (Мінімум 5) ---
        
        /**
         * @brief Отримує ціле число, повторюючи запит у разі некоректного типу.
         * @param prompt Текст підказки для користувача.
         * @return int Коректне ціле число.
         */
        static int GetIntInput(const std::string& prompt);

        /**
         * @brief Отримує ціле число у заданому діапазоні.
         * @param prompt Текст підказки.
         * @param min Мінімальне дозволене значення.
         * @param max Максимальне дозволене значення.
         * @return int Коректне ціле число в діапазоні.
         */
        static int GetIntInRange(const std::string& prompt, int min, int max);

        /**
         * @brief Отримує дробове число, повторюючи запит у разі некоректного типу.
         * @param prompt Текст підказки.
         * @return double Коректне дробове число.
         */
        static double GetDoubleInput(const std::string& prompt);

        /**
         * @brief Отримує строкове введення, яке не може бути порожнім.
         * @param prompt Текст підказки.
         * @return std::string Непорожня строка.
         */
        static std::string GetNonEmptyString(const std::string& prompt);

        /**
         * @brief Перевіряє чи є введення типу 'Yes'/'No' (Y/N).
         * @param prompt Текст підказки.
         * @return bool true для 'Y' або 'y'.
         */
        static bool GetYesNoInput(const std::string& prompt);
        
        /**
         * @brief Допоміжний метод для очищення буфера вводу після помилки.
         */
        static void ClearInputBuffer();
    };
} // namespace FootballManagement