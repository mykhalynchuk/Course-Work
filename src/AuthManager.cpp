#include "../include/AuthManager.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace FootballManagement
{
    AuthManager::AuthManager()
    {
        currentUser_ = std::make_shared<User>();
    }

    AuthManager& AuthManager::GetInstance()
    {
        static AuthManager instance;
        return instance;
    }

    bool AuthManager::Register(const std::string& userName,
                               const std::string& password, UserRole userRole)
    {
        if (registeredUsers_.count(userName) > 0)
        {
            std::cout << "[ПОМИЛКА] Користувач '" << userName
                << "' уже існує." << std::endl;
            return false;
        }

        if (userName.length() < 3 || password.length() < 6)
        {
            std::cout <<
                "[ПОМИЛКА] Логін має бути ≥3 символів, пароль ≥6 символів." <<
                std::endl;
            return false;
        }

        auto newUser = std::make_shared<User>(userName, password, userRole);
        registeredUsers_[userName] = newUser;

        std::cout << "[УСПІХ] Користувача '" << userName << "' зареєстровано."
            << std::endl;

        return true;
    }

    bool AuthManager::Login(const std::string& userName,
                            const std::string& password)
    {
        if (registeredUsers_.find(userName) == registeredUsers_.end())
        {
            std::cout << "[ПОМИЛКА] Користувача '" << userName <<
                "' не знайдено." << std::endl;
            return false;
        }

        auto user = registeredUsers_.at(userName);

        if (user->VerifyPassword(password))
        {
            currentUser_ = user;
            std::cout << "[ВХІД] Вітаємо, " << userName << "! Роль: "
                << (user->IsAdmin() ? "Адміністратор" : "Користувач") <<
                std::endl;
            return true;
        }
        else
        {
            std::cout << "[ПОМИЛКА] Невірний пароль для користувача '" <<
                userName << "'." << std::endl;
            return false;
        }
    }

    void AuthManager::Logout()
    {
        if (IsLoggedIn())
        {
            std::cout << "[INFO] Користувач '" << currentUser_->GetUserName() <<
                "' вийшов із системи." << std::endl;
            currentUser_ = std::make_shared<User>();
        }
        else
        {
            std::cout << "[INFO] Ви не залогінені." << std::endl;
        }
    }

    bool AuthManager::DeleteUser(const std::string& userName)
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout <<
                "[ВІДМОВА] Лише адміністратор може видаляти користувачів." <<
                std::endl;
            return false;
        }

        if (userName == currentUser_->GetUserName())
        {
            std::cout <<
                std::cout <<
                "[ПОМИЛКА] Ви не можете видалити свій активний обліковий запис."
                << std::endl;
            return false;
        }

        size_t initialSize = registeredUsers_.size();

        registeredUsers_.erase(userName);

        if (registeredUsers_.size() < before)
        {
            std::cout << "[УСПІХ] Користувача '" << userName << "' видалено." <<
                std::endl;
            return true;
        }
        std::cout << "[ПОМИЛКА] Користувача '" << userName << "' не знайдено."
            << std::endl;
        return false;
    }

    bool AuthManager::ChangeUserRole(const std::string& userName,
                                     UserRole newRole)
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout << "[ВІДМОВА] Тільки адміністратор може змінювати ролі."
                << std::endl;
            return false;
        }

        auto it = registeredUsers_.find(userName);
        if (it != registeredUsers_.end())
        {
            std::cout << "[ПОМИЛКА] Користувача '" << userName <<
                "' не знайдено." << std::endl;
            return false;
        }
        it->second->SetRole(newRole);
        std::cout << "[INFO] Роль користувача '" << userName << "' змінено." <<
            std::endl;
        return true;
    }

    void AuthManager::ViewAllUsers() const
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout <<
                "[ВІДМОВА] Лише адміністратор може переглядати список користувачів."
                << std::endl;
            return;
        }

        std::cout << "\n=== СПИСОК КОРИСТУВАЧІВ (" << registeredUsers_.size() <<
            ") ===" << std::endl;
        for (const auto& [name, user] : registeredUsers_)
        {
            user->ShowUserInfo();
        }
        std::cout << "==========================================" << std::endl;
    }

    std::shared_ptr<User> AuthManager::GetCurrentUser() const
    {
        return currentUser_;
    }

    bool AuthManager::IsLoggedIn() const
    {
        return currentUser_ && currentUser_->GetUserRole() != UserRole::Guest;
    }

    std::string AuthManager::Serialize() const
    {
        std::stringstream ss;
        bool first = true;
        for (const auto& [_, user] : registeredUsers_)
        {
            if (!first)
                ss << "\n";
            ss << user->Serialize();
            first = false;
        }
        return ss.str();
    }

    void AuthManager::Deserialize(const std::string& data)
    {
        if (!data.empty())
        {
            if (!data.empty())
            {
                std::cout <<
                    "[ПОПЕРЕДЖЕННЯ] Використовуйте DeserializeAllUsers для повного завантаження."
                    << std::endl;
            }
        }
    }

    void AuthManager::DeserializeAllUsers(
        const std::vector<std::string>& userDatas)
    {
        registeredUsers_.clear();
        int count = 0;

        for (const auto& data : userDatas)
        {
            if (data.empty()) continue;

            try
            {
                auto tempUser = std::make_shared<User>();
                tempUser->Deserialize(data);

                if (!tempUser->GetUserName().empty())
                {
                    registeredUsers_[tempUser->GetUserName()] = tempUser;
                    count++;
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "[ПОМИЛКА] Пропущено користувача через помилку: "
                    << e.what() << std::endl;
            }
        }

        if (count == 0)
        {
            std::cout <<
                "[ПОПЕРЕДЖЕННЯ] Користувачів не знайдено. Створюється обліковий запис адміністратора за замовчуванням."
                << std::endl;
            Register(DEFAULT_ADMIN_LOGIN, DEFAULT_ADMIN_PASSWORD,
                     UserRole::Admin);
        }

        std::cout << "[INFO] Завантажено користувачів: " << count << std::endl;
        currentUser_ = std::make_shared<User>();
    }
}
