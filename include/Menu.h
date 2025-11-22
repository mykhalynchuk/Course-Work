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

        void displayMainMenu() const;
        void handleMainMenu(int choice);

        void displayPlayerMenu() const;
        void deletePlayerFlow() const;
        void addPlayerFlow();

        void viewPlayersFlow() const;
        void searchPlayerFlow() const;
        void transferFlow() const;

        void manageUsersFlow();
        static void adminCreateUser();

        void authenticateUser();
        void saveAndExit();
        void displayHelp() const;

    public:
        /**
          * @brief Конструктор класу Menu.
          * @param clubManager Вказівник на об'єкт менеджера клубу.
          */
        explicit Menu(std::shared_ptr<ClubManager> clubManager);

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
        void LoadAllData() const;

        /**
         * @brief Зберігає всі дані (користувачів та гравців).
         */
        void SaveAllData() const;


    };
}