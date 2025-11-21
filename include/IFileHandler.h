#pragma once

#include <string>

namespace FootballManagement
{
    /**
     * @brief Інтерфейс для класів, які підтримують серіалізацію та десеріалізацію.
     */
    class IFileHandler
    {
    public:
        /**
         * @brief Серіалізує об'єкт у рядкового представлення.
         * @return std::string Рядок у форматі, придатному для збереження у файл.
         */
        virtual std::string Serialize() const = 0;

        /**
         * @brief Десеріалізує об'єкт із рядкового представлення.
         *  @param data Рядок з даними, на основі яких здійснюється відновлення об’єкта.
         */
        virtual void Deserialize(const std::string& data) = 0;

        /**
        * @brief Віртуальний деструктор.
        */
        virtual ~IFileHandler() = default;
    };
}
