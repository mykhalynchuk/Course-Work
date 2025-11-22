#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "include/AuthManager.h"
#include "include/ClubManager.h"
#include "include/FileManager.h"
#include "include/Menu.h"
#include "include/Utils.h"

using namespace FootballManagement;

/**
 * @brief Завантажує користувачів і гравців із файлів.
 * @param fm Об’єкт класу FileManager.
 * @param cm Менеджер клубу.
 */
void initializeDataLoad(FileManager& fm, ClubManager& cm)
{
    try
    {
        std::vector<std::string> usrLines = fm.LoadFromFile(USERS_FILE_NAME);

        AuthManager::GetInstance().DeserializeAllUsers(usrLines);

        if (AuthManager::GetInstance().GetCurrentUser() == nullptr ||
            !AuthManager::GetInstance().GetCurrentUser()->IsAdmin())
        {
            AuthManager::GetInstance().Register(
                DEFAULT_ADMIN_LOGIN, DEFAULT_ADMIN_PASSWORD, UserRole::Admin);
            std::cout << "[ІНФО] Створено адміністратора за замовчуванням.\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "[ПОМИЛКА] Неможливо завантажити користувачів: " << e.
            what() << std::endl;
    }

    try
    {
        std::vector<std::string> playerLines = fm.LoadFromFile(
            PLAYERS_DATA_FILE);
        cm.DeserializeAllPlayers(playerLines);
        std::cout << "[ІНФО] Завантажено гравців.\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "[ПОМИЛКА] Неможливо завантажити гравців: " << e.what() <<
            std::endl;
    }
}

/**
 * @brief Зберігає користувачів і гравців у файли.
 * @param fm Об’єкт класу FileManager.
 * @param cm Менеджер клубу.
 */
void initializeDataSave(FileManager& fm, ClubManager& cm)
{
    try
    {
        fm.SaveToFile(USERS_FILE_NAME, AuthManager::GetInstance());
        fm.SaveToFile(PLAYERS_DATA_FILE, cm);
        std::cout << "[ІНФО] Дані успішно збережено.\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "[ПОМИЛКА ЗБЕРЕЖЕННЯ] Не вдалося зберегти всі дані: " << e.
            what() << std::endl;
    }
}

/**
 * @brief Точка входу в програму Football Management System.
 */
int main()
{
    try
    {
        FileManager fileManager;
        auto clubManager = std::make_shared<ClubManager>(
            "Динамо Київ", 50000000.0);

        initializeDataLoad(fileManager, *clubManager);

        Menu mainMenu(clubManager);
        mainMenu.Run();

        initializeDataLoad(fileManager, *clubManager);
    }
    catch (const std::exception& e)
    {
        std::cout << "\n[КРИТИЧНА ПОМИЛКА] Програма завершена через виняток: "
            << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout <<
            "\n[КРИТИЧНА ПОМИЛКА] Програма завершена через невідомий виняток."
            << std::endl;
        return 1;
    }
    std::cout << "\n[ІНФО] Програму завершено коректно.\n";
    return 0;
}
