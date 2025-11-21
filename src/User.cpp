#include "../include/User.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace FootballManagement
{
    User::User() : userName_(DEFAULT_ADMIN_LOGIN),
                   password_(DEFAULT_ADMIN_PASSWORD), userRole_(UserRole::Guest)
    {
    }

    User::User(const std::string& userName, const std::string& password,
               UserRole userRole) : userName_(userName), password_(password),
                                    userRole_(userRole)
    {
    }

    User::User(const User& other) : userName_(other.userName_),
                                    password_(other.password_),
                                    userRole_(other.userRole_)
    {
    }

    User::User(User&& other) noexcept : userName_(std::move(other.userName_)),
                                        password_(std::move(other.password_)),
                                        userRole_(other.userRole_)
    {
        other.userRole_ = UserRole::Guest;
    }

    User& User::operator=(const User& other)
    {
        if (this != &other)
        {
            userName_ = other.userName_;
            password_ = other.password_;
            userRole_ = other.userRole_;
        }
        return *this;
    }

    User& User::operator=(User&& other) noexcept
    {
        if (this != &other)
        {
            userName_ = std::move(other.userName_);
            password_ = std::move(other.password_);
            userRole_ = other.userRole_;

            other.userRole_ = UserRole::Guest;
        }
        return *this;
    }

    User::~User()
    {
        std::cout << "[DEBUG] User " << userName_ << " destroyed." << std::endl;
    }

    std::string User::GetUserName() const { return userName_; }

    std::string User::GetPassword() const { return password_; }

    void User::SetUserName(const std::string& userName)
    {
        if (userName.empty())
        {
            throw std::invalid_argument("Username cannot be empty.");
        }
        userName_ = userName;
    }

    bool User::IsAdmin() const
    {
        return userRole_ == UserRole::Admin;
    }

    bool User::ChangePassword(const std::string& oldPassword,
                              const std::string& newPassword)
    {
        if (!VerifyPassword(oldPassword))
        {
            std::cout << "[FAIL] Incorrect old password provided." << std::endl;
            return false;
        }

        if (newPassword.length() < 6)
        {
            std::cout << "[FAIL] New password is too short (min 6 chars)." <<
                std::endl;
            return false;
        }

        password_ = newPassword;
        std::cout << "[SUCCESS] Password for user " << userName_ << " changed."
            << std::endl;
        return true;
    }

    bool User::VerifyPassword(const std::string& inputPassword) const
    {
        return password_ == inputPassword;
    }

    void User::SetRole(UserRole newRole)
    {
        userRole_ = newRole;
        std::cout << "[INFO] Role for " << userName_ << " set." << std::endl;
    }

    void User::ShowUserInfo() const
    {
        std::string roleString = (userRole_ == UserRole::Admin)
                                     ? "Admin"
                                     : (userRole_ == UserRole::StandardUser)
                                     ? "standart"
                                     : "Guest";

        std::cout << "User: " << userName_ << " | Role: " << roleString <<
            std::endl;
    }

    std::string User::Serialize() const
    {
        std::stringstream ss;
        ss << userName_ << ":" << password_ << ":" << static_cast<int>(
            userRole_);
        return ss.str();
    }

    void User::Deserialize(const std::string& data)
    {
        try
        {
            std::stringstream ss(data);
            std::string token;
            std::vector<std::string> parts;

            while (std::getline(ss, token, ":"))
            {
                parts.push_back(token);
            }

            if (parts.size() != 3)
            {
                throw std::runtime_error(
                    "Incorrect format for user data (expected 3 parts).");
            }

            userName_ = parts[0];
            password_ = parts[1];
            userRole_ = static_cast<UserRole>(std::stoi(parts[2]));
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] Failed to deserialize User data: " << e.what()
                << std::endl;
            userName_ = "error_guest";
            password_ = "";
            userRole_ = UserRole::Guest;
        }
    }
}
