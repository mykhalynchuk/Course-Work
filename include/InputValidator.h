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
        /**
           * @brief Отримує ціле число з консолі. Якщо введено некоректно — повторює запит.
           * @param prompt Підказка користувачу.
           * @return Коректне ціле число.
           */
        static int GetIntInput(const std::string& prompt);

        /**
         * @brief Отримує ціле число у заданому діапазоні.
         * @param prompt Текст підказки.
         * @param min Мінімальне дозволене значення.
         * @param max Максимальне дозволене значення.
         * @return Коректне ціле число в діапазоні.
         */
        static int GetIntInRange(const std::string& prompt, int min, int max);

        /**
       * @brief Отримує дробове (дійсне) число.
       * @param prompt Підказка користувачу.
       * @return Коректне число типу double.
       */
        static double GetDoubleInput(const std::string& prompt);

        /**
        /**
         * @brief Отримує непорожній рядок.
         * @param prompt Підказка користувачу.
         * @return Строка, яка не є пустою.
         */
        static std::string GetNonEmptyString(const std::string& prompt);

        /**
         * @brief Перевіряє чи є введення типу 'так'/'ні' (Y/N).
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