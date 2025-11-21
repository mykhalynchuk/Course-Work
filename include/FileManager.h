#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "IFileHandler.h"
#include "Utils.h"

namespace FootballManagement
{
    /**
     * @brief Клас, що відповідає за всі операції читання та запису файлів у системі.
     */
    class FileManager
    {
    private:
        std::string directoryPath_ = "data/";

    public:
        FileManager() = default;
        ~FileManager() = default;

        /**
         * @brief Зберігає вміст одного об'єкта у файл.
         * @param fileName Ім'я файлу.
         * @param serializableObject Об'єкт для серіалізації.
         * @return bool Результат операції.
         */
        bool SaveToFile(const std::string& fileName,
                        const IFileHandler& serializableObject) const;

        /**
         * @brief Зчитує вміст файлу та повертає його як вектор рядків.
         * @param fileName
         * @return
         */
        std::vector<std::string>
        LoadFromFile(const std::string& fileName) const;

        /**
         * @brief Перевіряє існування файлу.
         * @param fileName Ім'я файлу.
         * @return bool True, якщо файл існує.
         */
        bool FileExists(const std::string& fileName) const;

        /**
         * @brief Створює необхідну структуру каталогів, якщо вона не існує.
         * @return
         */
        bool EnsureDirectoryExists() const;

        /**
         * @brief Повертає повний шлях до файлу, включаючи каталог даних.
         * @param fileName Ім'я файлу.
         * @return std::string Повний шлях для видалення.
         */
        std::string GetFullPath(const std::string& fileName) const;

        /**
         * @brief Видаляє файл із системи.
         * @param fileName Ім'я файлу для видалення.
         * @return bool Результат видалення.
         */
        bool DeleteFile(const std::string& fileName) const;
    };
}
