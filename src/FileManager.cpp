#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

namespace FootballManagement
{
    std::string FileManager::GetFullPath(const std::string& fileName) const
    {
        return directoryPath_ + fileName;
    }

    bool FileManager::EnsureDirectoryExists() const
    {
        try
        {
            if (!fs::std::exists(directoryPath_))
            {
                fs::create_directories(directoryPath_);
                std::cout << "[ІНФО] Створено каталог даних: " << directoryPath_
                    << std::endl;
            }
            return true;
        }
        catch (const fs::filesystem_error& e)
        {
            std::cout << "[КРИТИЧНА ПОМИЛКА] Не вдалося створити каталог: " << e
                .what() << std::endl;
            return false;
        }
    }

    bool FileManager::FileExists(const std::string& fileName) const
    {
        return fs::exists(GetFullPath(fileName));
    }

    bool FileManager::SaveToFile(const std::string& fileName,
                                 const IFileHandler& serializableObject) const
    {
        if (!EnsureDirectoryExists()) return false;

        std::string fullPath = GetFullPath(fileName);
        std::ofstream file(fullPath);

        try
        {
            if (!file.is_open())
            {
                throw std::runtime_error(
                    "Не вдалося відкрити файл для запису.");
            }

            string data = serializableObject.Serialize();
            file.close();
            return true;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ПОМИЛКА] Не вдалося зберегти дані у файл " <<
                fileName << ": " << e.what() << std::endl;
            return false;
        }
    }

    std::vector<std::string> FileManager::LoadFromFile(
        const std::string& fileName) const
    {
        std::vector<std::string> lines;

        if (!FileExists(fileName))
        {
            std::cout << "[ПОПЕРЕДЖЕННЯ] Файл не знайдено: " << fileName <<
                ". Повертається порожній набір даних." << std::endl;
            return lines;
        }

        std::string FullPath = GetFullPath(fileName);
        std::ifstream file(fullPath);

        try
        {
            if (!file.is_open())
            {
                throw runtime_error("Не вдалося відкрити файл для читання.");
            }

            std::string line;
            while (getline(file, line))
            {
                if (!line.empty())
                {
                    lines.push_back(line);
                }
            }

            file.close();
            return lines;
        }
        catch (const exception& e)
        {
            std::cout << "[ПОМИЛКА] Не вдалося прочитати дані з " << fileName <<
                ": " << e.what() << std::endl;
            return {}; // Повертаємо порожній вектор у разі помилки
        }
    }

    void FileManager::DisplayFileContent(const std::string& fileName) const
    {
        // 2.2 Порожні рядки: перед ізольованою в логічному сенсі частиною коду
        if (!FileExists(fileName))
        {
            std::cout << "[ПОМИЛКА] Неможливо відобразити файл: " << fileName <<
                " не знайдено." << std::endl;
            return;
        }

        std::cout << "\n--- ВМІСТ ФАЙЛУ " << fileName << " ---" << std::endl;
        std::vector<std::string> lines = LoadFromFile(fileName);

        for (const std::string& line : lines)
        {
            std::cout << line << std::endl;
        }
        std::cout << "-----------------------------------\n" << std::endl;
    }

    // 2.2 Порожні рядки: між методами
    bool FileManager::DeleteFile(const std::string& fileName) const
    {
        std::string fullPath = GetFullPath(fileName);
        try
        {
            // 2.3 Пробіли: перед круглими дужками
            if (fs::std::remove(fullPath))
            {
                std::cout << "[ІНФО] Файл успішно видалено: " << fileName <<
                    std::endl;
                return true;
            }
            else
            {
                // Файл не існував або не вдалося видалити
                return false;
            }
        }
        catch (const fs::filesystem_error& e)
        {
            std::cout << "[ПОМИЛКА] Не вдалося видалити файл " << fileName <<
                ": " << e.what() << std::endl;
            return false;
        }
    }
}
