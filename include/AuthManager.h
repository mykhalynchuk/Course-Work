#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "User.h"
#include "IFileHandler.h"
#include "Utils.h"

namespace FootballManagement
{
    /**
     * @brief Singleton клас, що відповідає за автентифікацію та управління обліковими записами.
     */
    class AuthManager : public IFileHandler
    {
    private:
        //Карта для зберігання користувачів: <userName, User object>
        std::map<std::string, std::shared_ptr<User>> registeredUsers_;

        //Поточний користувач. За замовчуванням - Guest.
        std::shared_ptr<User> currentUser_;

        AuthManager();
        AuthManager(const AuthManager&) = delete;
        AuthManager& operator=(const AuthManager&) = delete;

    public:
        /**
         * @brief Надає єдиний екземпляр класу AuthManager.
         */
        static AuthManager& GetInstance();

        /**
         * @brief Реєстрація нового користувача.
         * @return bool Результат реєстрації.
         */
        bool Register(const std::string& userName, const std::string& password,
                      UserRole userRole = UserRole::StandardUser);

        /**
         * @brief Автентифікація користувача.
         * @return bool Результат входу.
         */
        bool Login(const std::string& userName, const std::string& password);

        /**
         * @brief Вихід поточного користувача із системи.
         */
        void Logout();

        /**
         * @brief Видалення облікового запису.
         * @return bool Результат видалення.
         */
        bool DeleteUser(const std::string& userName);

        /**
         * @brief Зміна ролі іншого користувача (Admin функціонал).
         * @return bool Результати змін.
         */
        bool ChangeUserRole(const std::string& userName, UserRole newRole);

        /**
         * @brief Переглядає список зареєстрованих користувачів.
         */
        void ViewAllUsers() const;

        /**
         * @brief Повертає поточного залогіненого користувача.
         */
        std::shared_ptr<User> GetCurrentUser() const;

        /**
         * @brief Перевіряє, чи залогінений користувач (не Guest).
         */
        bool IsLoggedIn() const;

        std::string Serialize() const override;
        void Deserialize(const std::string& data) override;

        /**
         * @brief Спеціальний метод для завантаження повного списку користувачів мщ вектора рядків.
         */
        void DeserializeAllUsers(const std::vector<std::string>& userDatas);
    };
}
