#pragma once

#include <string>
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
        /** @brief Конструктор за замовчуванням (гостьовий користувач). */
        User();

        /**
         * @brief Конструктор з параметрами.
         * @param userName Логін користувача.
         * @param password Пароль користувача.
         * @param userRole Роль (Admin / StandardUser / Guest).
         */
        User(const std::string& userName, const std::string& password,
             UserRole userRole);

        /** @brief Копіювальний конструктор. */
        User(const User& other);

        /** @brief Переміщувальний конструктор. */
        User(User&& other) noexcept;

        /** @brief Оператор копіювального присвоєння. */
        User& operator=(const User& other);

        /** @brief Оператор переміщувального присвоєння. */
        User& operator=(User&& other) noexcept;

        /** @brief Віртуальний деструктор (з відлагоджувальним повідомленням). */
        virtual ~User();

        /** @brief Повертає логін користувача. */
        std::string GetUserName() const;

        /** @brief Повертає пароль користувача. */
        std::string GetPassword() const;

        /** @brief Повертає роль користувача. */
        UserRole GetUserRole() const;

        /**
        * @brief Встановлює новий логін користувача.
        * @throws std::invalid_argument якщо логін порожній.
        */
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
         * @return true, якщо результат зміни.
         */
        bool ChangePassword(const std::string& oldPassword,
                            const std::string& newPassword);

        /**
         * @brief Перевіряє наданий пароль на відповідність поточному.
         * @param inputPassword Пароль для перевірки.
         * @return true, якщо паролі збігаються.
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

        /**
      * @brief Серіалізує користувача у рядок формату "username:password:role".
      * @return Рядок даних для запису у users.txt.
      */
        std::string Serialize() const override;

        /**
       * @brief Десеріалізує користувача з рядка "username:password:role".
       * @param data Вхідний рядок.
       * @details У разі помилки встановлюється гостьовий профіль.
       */
        void Deserialize(const std::string& data) override;
    };
}
