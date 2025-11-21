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

void initializeDataLoad(FileManager& fm, ClubManager& cm)
{
    try
    {
        std::vector<std::string> usrLines = fm.LoadFromFile(USERS_FILE_NAME);

        AuthManager::GetInstance().DeserializeAllUsers(usrLines);

        if (!AuthManager::GetInstance().GetCurrentUser() || !
            AuthManager::GetInstance().GetCurrentUser()->IsAdmin())
        {
            if (!AuthManager::GetInstance().Register(
                DEFAULT_ADMIN_LOGIN, DEFAULT_ADMIN_PASSWORD, UserRole::Admin))
            {
                std::cout <<
                    "[КРИТИЧНА ПОМИЛКА] Не вдалося створити адміністратора." <<
                    std::endl;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "[ПОМИЛКА ЗАВАНТАЖЕННЯ] Користувачі: " << e.what() <<
            std::endl;
    }

    try
    {
        std::vector<std::string> playerLines = fm.LoadFromFile(
            PLAYERS_DATA_FILE);
        cm.DeserializeAllPlaters(playerLines);
    }
    catch (const std::exception& e)
    {
        std::cout << "[ПОМИЛКА ЗАВАНТАЖЕННЯ] Гравці: " << e.what() << std::endl;
    }
}

    void initializeDataSave(FileManager& fm, ClubManager& cm)
    {
        try
        {
            fm.SaveToFile(USERS_FILE_NAME, AuthManager::GetInstance());
            fm.SaveToFile(PLAYERS_DATA_FILE, cm);
        }
        catch (const std::exception& e)
        {
            std::cout << "[ПОМИЛКА ЗБЕРЕЖЕННЯ] Не вдалося зберегти всі дані: "
                << e.what() << std::endl;
        }
    }


int main(int fileManager)
{
    try
    {
        auto clubManager = std::make_shared<ClubManager>("Динамо Київ", 50000000.0);

        initializeDataLoad(fileManager, *clubManager);

        Menu mainMenu(clubManager);
        mainMenu.Run();

        initializeDataLoad(fileManager, *clubManager);
    }
    catch (const std::exception& e)
    {
        std::cout << "\n[КРИТИЧНА ПОМИЛКА] Програма завершена через виняток: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "\n[КРИТИЧНА ПОМИЛКА] Програма завершена через невідомий виняток." << std::endl;
        return 1;
    }
    return 0;
}
