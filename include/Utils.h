#pragma once

#include <string>

namespace FootballManagement
{
    /// @brief Ім'я файлу, у якому зберігаються користувачі.
    const std::string USERS_FILE_NAME = "users.txt";

    /// @brief Ім'я файлу для збереження даних гравців.
    const std::string PLAYERS_DATA_FILE = "players.json";

    /// @brief Логін адміністратора за замовчуванням.
    const std::string DEFAULT_ADMIN_LOGIN = "admin";

    /// @brief Пароль адміністратора за замовчуванням.
    const std::string DEFAULT_ADMIN_PASSWORD = "admin123";

    /**
     * @brief Перелік ролей користувачів для системи авторизації.
     */
    enum class UserRole
    {
        Admin,
        StandardUser,
        Guest
    };

    /**
     * @brief Перелік ігрових позицій футболіста.
     */
    enum class Position
    {
        Goalkeeper,
        Defender,
        Midfielder,
        Forward
    };

    /**
     * @brief Представляє запис про травму гравця.
     */
    struct Injury
    {
        std::string injuryType;
        std::string dateOccurred;
        int recoveryDays;
    };
}