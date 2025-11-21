#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Utils.h"
#include "IFileHandler.h"

namespace FootballManagement
{
    /**
     * @brif Клас, що представляє обліковий запис користувача системи.
     */
    class User : public IFileHandler
    {
    private:
        std::string userName_;
        std::string password_;
        UserRole userRole_;

    public:
        User();

        /**
         * @brief Конструктор з параметрами.
         * @param userName Логін користувача.
         * @param password пароль користувача.
         * @param userRole Роль (Admin/StandardUser).
         */
        User(const std::string& userName, const std::string& password, UserRole userRole);

        User(const User& other);
        User(User&& other) noexcept;
        User& operator=(const User& other);
        User& operator=(User&& other) noexcept;

        virtual ~User();

        std::string GetUserName() const;
        std::string GetPassword() const;
        UserRole GetUserRole() const;

        void SetUserName(const std::string& userName);

        /**
         * @brief Перевіряє, чи має користувач адміністративні права.
         * @return bool true, якщо користувач є Admin.
         */
        bool IsAdmin() const;

        /**
         * @brief Змінює пароль користувача.
         * @param oldPassword oldPassword Поточний пароль для валідації.
         * @param newPassword Новий пароль.
         * @return bool результат зміни.
         */
        bool ChangePassword(const std::string& oldPassword, const std::string& newPassword);

        /**
         * @brief Перервіряє наданий пароль на відповідність поточному.
         * @param inputPassword Пароль для перевірки.
         * @return bool Результат перевірки.
         */
        bool VerifyPassword(const std::string& inputPassword) const;

        /**
         * @brief Змінює роль користувача.
         * @param newRole Нова роль.
         */
        void SetRole(UserRole newRole);

        /**
         * @brief Виводить інформацію про користувача (логін та пароль).
         */
        void ShowUserInfo() const;

        /**
         * @brief Здійснює вихід із системи.
         */
        void Logout();

        std::string Serialize() const override;
        void Deserialize(const std::string& data) override;
    };

}