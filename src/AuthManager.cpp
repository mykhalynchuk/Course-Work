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
            std::cout << "[FAIL] Registration failed: Username '" << userName <<
                "' already exists." << std::endl;
            return false;
        }

        if (userName.length() < 3 || password.length() < 6)
        {
            std::cout <<
                "[FAIL] Registration failed: Username (min 3) or Password (min 6) is too short."
                << std::endl;
            return false;
        }

        auto newUser = std::make_shared<User>(userName, password, userRole);
        registeredUsers_[userName] = newUser;

        std::cout << "[SUCCESS] User '" << userName << "' registered." <<
            std::endl;

        return true;
    }

    bool AuthManager::Login(const std::string& userName,
                            const std::string& password)
    {
        if (registeredUsers_.find(userName) == registeredUsers_.end())
        {
            std::cout << "[FAIL] Login failed: User '" << userName <<
                "' not found." << std::endl;
            return false;
        }

        auto user = registeredUsers_.at(userName);

        if (user->VerifyPassword(password))
        {
            currentUser_ = user;
            std::cout << "[SUCCESS] User '" << userName << "' logged in. Role: "
                << (user->IsAdmin() ? "Admin" : "Standard") << std::endl;
            return true;
        }
        else
        {
            std::cout << "[FAIL] Login failed: Incorrect password for user '" <<
                userName << "'." << std::endl;
            return false;
        }
    }

    void AuthManager::Logout()
    {
        if (IsLoggedIn())
        {
            currentUser_->Logout();
            currentUser_ = std::make_shared<User>();
        }
        else
        {
            std::cout << "[INFO] Already logged out." << std::endl;
        }
    }

    bool AuthManager::DeleteUser(const std::string& userName)
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout << "[FAIL] Deletion denied: Only Admin can delete users."
                << std::endl;
            return false;
        }

        if (userName == currentUser_->GetUserName())
        {
            std::cout <<
                "[FAIL] Deletion denied: Cannot delete your own active account."
                << std::endl;
            return false;
        }

        size_t initialSize = registeredUsers_.size();

        registeredUsers_.erase(userName);

        if (registeredUsers_.size() < initialSize)
        {
            std::cout << "[SUCCESS] User '" << userName << "' deleted by Admin."
                << std::endl;
            return true;
        }
        else
        {
            std::cout << "[FAIL] Deletion failed: User '" << userName <<
                "' not found." << std::endl;
            return false;
        }
    }

    bool AuthManager::ChangeUserRole(const std::string& userName,
                                     UserRole newRole)
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout <<
                "[FAIL] Role change denied: Only Admin can change user roles."
                << std::endl;
            return false;
        }

        auto it = registeredUsers_.find(userName);
        if (it != registeredUsers_.end())
        {
            it->second->SetRole(newRole);
            return true;
        }
        else
        {
            std::cout << "[FAIL] Role change failed: User '" << userName <<
                "' not found." << std::endl;
            return false;
        }
    }

    void AuthManager::ViewAllUsers() const
    {
        if (!IsLoggedIn() || !currentUser_->IsAdmin())
        {
            std::cout << "[FAIL] Access denied: Only Admin can view all users."
                << std::endl;
            return;
        }

        std::cout << "\n--- REGISTERED USERS (" << registeredUsers_.size() <<
            ") ---" << std::endl;
        for (const auto& pair : registeredUsers_)
        {
            pair.second->ShowUserInfo();
        }
        std::cout << "-----------------------------------\n" << std::endl;
    }

    std::shared_ptr<User> AuthManager::GetCurrentUser() const
    {
        return currentUser_;
    }

    bool AuthManager::IsLoggedIn() const
    {
        return currentUser_->GetUserRole() != UserRole::Guest;
    }

    std::string AuthManager::Serialize() const
    {
        std::stringstream ss;
        bool first = true;

        for (const auto& pair : registeredUsers_)
        {
            if (!first)
            {
                ss << "\n";
            }
            ss << pair.second->Serialize();
            first = false;
        }
        return ss.str();
    }

    void AuthManager::Deserialize(const std::string& data)
    {
        if (!data.empty())
        {
            std::cout <<
                "[WARNING] AuthManager::Deserialize called. Use DeserializeAllUsers."
                << std::endl;
        }
    }

    void AuthManager::DeserializeAllUsers(
        const std::vector<std::string>& userDatas)
    {
        registeredUsers_.clear();
        int loadedCount = 0;

        for (const std::string& data : userDatas)
        {
            try
            {
                if (data.empty()) continue;;

                auto tempUser = std::make_shared<User>();
                tempUser->Deserialize(data);

                if (!tempUser->GetUserName().empty() && tempUser->GetUserRole()
                    != UserRole::Guest && registeredUsers_.find(
                        tempUser->GetUserName()) == registeredUsers_.end())
                {
                    registeredUsers_[tempUser->GetUserName()] =
                        tempUser;
                    loadedCount++;
                }
            }
            catch (const exception& e)
            {
                std::cout << "[ERROR] Skipped user data due to error: " << e.
                    what() << std::endl;
            }
        }

        std::cout << "[INFO] AuthManager loaded " << loadedCount << " users." <<
            std::endl;

        if (registeredUsers_.empty())
        {
            std::cout <<
                "[WARNING] No users found. Creating default Admin user." <<
                std::endl;
            Register(DEFAULT_ADMIN_LOGIN, DEFAULT_ADMIN_PASSWORD,
                     UserRole::Admin);
        }

        currentUser_ = std::make_shared<User>();
    }
}
