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
      * @brief Керує користувачами системи, їх реєстрацією, входом та ролями.
      *
      * Реалізовано як Singleton, щоб гарантувати наявність лише одного менеджера користувачів у системі.
      */
    class AuthManager : public IFileHandler
    {
    private:
        std::map<std::string, std::shared_ptr<User>> registeredUsers_;
        std::shared_ptr<User> currentUser_;

        AuthManager();

        AuthManager(const AuthManager&) = delete;
        AuthManager& operator=(const AuthManager&) = delete;
        ~AuthManager() noexcept override = default;

    public:
        /**
         * @brief Надає єдиний екземпляр класу AuthManager.
         */
        static AuthManager& GetInstance();

        /**
          * @brief Реєструє нового користувача.
          * @param userName Логін.
          * @param password Пароль.
          * @param userRole Роль користувача (Admin або StandardUser).
          * @return true, якщо користувача зареєстровано успішно.
          */
        bool Register(const std::string& userName, const std::string& password,
                      UserRole userRole = UserRole::StandardUser);

        /**
        * @brief Авторизує користувача в системі.
        * @param userName Ім’я користувача.
        * @param password Пароль.
        * @return true, якщо вхід успішний.
        */
        bool Login(const std::string& userName, const std::string& password);

        /**
         * @brief Вихід поточного користувача із системи.
         */
        void Logout();

        /**
        * @brief Видаляє користувача із системи (доступно лише адміну).
        * @param userName Ім’я користувача, якого потрібно видалити.
        * @return true, якщо видалення успішне.
        */
        bool DeleteUser(const std::string& userName);

        /**
        * @brief Змінює роль користувача (Admin-можливість).
        * @param userName Ім’я користувача.
        * @param newRole Нова роль.
        * @return true, якщо роль успішно змінено.
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
