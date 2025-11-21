#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "AuthManager.h"
#include "ClubManager.h"
#include "InputValidator.h"
#include "FileManager.h"
#include "Utils.h"

namespace FootballManagement
{
    /**
     * @brief Клас, що керує текстовим меню, навігацією та користувацьким інтерфейсом.
     */
    class Menu
    {
    private:
        std::shared_ptr<ClubManager> clubManager_;
        FileManager fileManager_;
        bool isRunning_;

        void displayMainManu() const;
        void handleMainManu(int choice);

        void displayAdminMenu() const;
        void handleAdminMenu(int choice);

        void displayPlayerMenu() const;

        void authenticateUser();
        void saveAndExit();
        void displayHelp() const;

        void addPlayerFlow();
        void viewPlayersFlow() const;
        void searchPlayerFlow() const;
        void manageUsersFlow();
        void adminCreateUser();
        void transferFlow();

    public:
        /**
         * @brief Конструктор. Ініціалізує менеджери.
         * @param clubManager Менеджер клубу.
         */
        Menu(std::shared_ptr<ClubManager> clubManager);

        virtual ~Menu() = default;

        /**
         * @brief Запускається основний цикл програми.
         */
        void Run();

        /**
         * @brief Зупиняє цикл програми.
         */
        void Stop();

        /**
         * @brief Завантажує всі дані (користувачів та гравців).
         */
        void LoadAllData();

        /**
         * @brief Зберігає всі дані (користувачів та гравців).
         */
        void SaveAllData() const;


    };
}