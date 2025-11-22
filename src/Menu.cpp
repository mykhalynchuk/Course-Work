#include "../include/Menu.h"
#include "../include/InputValidator.h"
#include "../include/ContractedPlayer.h"
#include "../include/FreeAgent.h"
#include "../include/AuthManager.h"
#include "../include/FileManager.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

namespace FootballManagement
{
    Menu::Menu(std::shared_ptr<ClubManager> clubManager) :
        clubManager_(std::move(clubManager)), isRunning_(true)
    {
    }

    void Menu::LoadAllData()
    {
        try
        {
            std::vector<std::string> userLines = fileManager_.LoadFromFile(
                USERS_FILE_NAME);
            AuthManager::GetInstance().DeserializeAllUsers(userLines);
            std::cout << "[ІНФО] Дані користувачів завантажено." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ПОМИЛКА] Не вдалося завантажити користувачів: " << e.
                what() << std::endl;
        }

        try
        {
            std::vector<std::string> playerLines = fileManager_.LoadFromFile(
                PLAYERS_DATA_FILE);
            clubManager_->DeserializeAllPlayers(playerLines);
            std::cout << "[ІНФО] Дані гравців завантажено." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ПОМИЛКА] Не вдалося завантажити гравців: " << e.
                what() << std::endl;
        }
    }

    void Menu::SaveAllData() const
    {
        std::cout << "[ІНФО] Збереження даних..." << std::endl;
        fileManager_.SaveToFile(USERS_FILE_NAME, AuthManager::GetInstance());
        fileManager_.SaveToFile(PLAYERS_DATA_FILE, *clubManager_);
        std::cout << "[УСПІХ] Усі дані збережено." << std::endl;
    }

    void Menu::Run()
    {
        LoadAllData();
        authenticateUser();

        while (isRunning_ && AuthManager::GetInstance().IsLoggedIn())
        {
            displayMainMenu();
            int choice = InputValidator::GetIntInRange(
                "Введіть номер дії: ", 1, 9);
            handleMainMenu(choice);
        }

        if (!AuthManager::GetInstance().IsLoggedIn())
        {
            std::cout << "\nСесію завершено. Програму закрито." << std::endl;
        }
    }

    void Menu::Stop()
    {
        isRunning_ = false;
        std::cout << "[ІНФО] Завершення роботи програми..." << std::endl;
    }

    void Menu::authenticateUser()
    {
        std::cout << "========================================\n";
        std::cout << "     СИСТЕМА КЕРУВАННЯ ФУТБОЛЬНИМ КЛУБОМ\n";
        std::cout << "========================================\n";

        for (int attempts = 0; attempts < 3; ++attempts)
        {
            std::string login = InputValidator::GetNonEmptyString("Логін: ");
            std::string password =
                InputValidator::GetNonEmptyString("Пароль: ");


            if (AuthManager::GetInstance().Login(login, password))
            {
                return;
            }
        }

        std::cout << "[ПОМИЛКА] Перевищено кількість спроб входу.\n";
        Stop();
    }

    void Menu::displayMainMenu() const
    {
        std::cout << "\n=========== ГОЛОВНЕ МЕНЮ ===========" << std::endl;
        std::cout << "1. Керування гравцями (Додати / Видалити)" << std::endl;
        std::cout << "2. Переглянути всіх гравців" << std::endl;
        std::cout << "3. Пошук / Сортування / Фільтрація" << std::endl;
        std::cout << "4. Трансферний ринок (Підписати агента)" << std::endl;

        if (AuthManager::GetInstance().GetCurrentUser()->IsAdmin())
        {
            std::cout << "5. Керування користувачами (тільки Admin)" <<
                std::endl;
        }

        std::cout << "7. Довідка" << std::endl;
        std::cout << "8. Зберегти всі дані" << std::endl;
        std::cout << "9. Вихід" << std::endl;
        std::cout << "====================================" << std::endl;
    }

    void Menu::handleMainMenu(int choice)
    {
        auto user = AuthManager::GetInstance().GetCurrentUser();
        bool isAdmin = user->IsAdmin();

        switch (choice)
        {
        case 1: displayPlayerMenu();
            break;
        case 2: viewPlayersFlow();
            break;
        case 3: searchPlayerFlow();
            break;
        case 4: transferFlow();
            break;
        case 5:
            if (isAdmin) { manageUsersFlow(); }
            else std::cout << "[ВІДМОВА] Необхідні права адміністратора.\n";
            break;
        case 7: displayHelp();
            break;
        case 8: SaveAllData();
            break;
        case 9: saveAndExit();
            break;
        default: std::cout << "[ПОМИЛКА] Некоректний вибір.\n";
        }
    }

    void Menu::saveAndExit()
    {
        if (InputValidator::GetYesNoInput("Зберегти зміни перед виходом?"))
            SaveAllData();

        AuthManager::GetInstance().Logout();
        Stop();
    }

    void Menu::displayHelp() const
    {
        std::cout << "\n--- ДОВІДКА ---\n";
        std::cout <<
            "Ця програма дозволяє керувати складом футбольної команди:\n";
        std::cout << "* Додавати, редагувати або видаляти гравців.\n";
        std::cout << "* Пошук, сортування, фільтрація.\n";
        std::cout << "* Підписання вільних агентів.\n";
        std::cout << "-----------------------------------\n";
    }

    void Menu::displayPlayerMenu() const
    {
        std::cout << "\n==== МЕНЮ ГРАВЦІВ ====\n";
        std::cout << "1. Додати нового гравця\n";
        std::cout << "2. Видалити гравця за ID\n";
        std::cout << "3. Назад\n";

        int choice = InputValidator::GetIntInRange("Ваш вибір: ", 1, 3);
        if (choice == 1) const_cast<Menu*>(this)->addPlayerFlow();
        if (choice == 2) const_cast<Menu*>(this)->deletePlayerFlow();
    }

    void Menu::deletePlayerFlow()
    {
        int id = InputValidator::GetIntInput(
            "Введіть ID гравця для видалення: ");
        clubManager_->RemovePlayers(id);
    }

    void Menu::addPlayerFlow()
    {
        std::cout << "\n--- ДОДАВАННЯ ГРАВЦЯ ---\n";

        std::string name = InputValidator::GetNonEmptyString("Ім'я: ");
        int age = InputValidator::GetIntInRange("Вік: ", 16, 45);
        std::string nationality = InputValidator::GetNonEmptyString(
            "Національність: ");
        std::string origin = InputValidator::GetNonEmptyString("Походження: ");
        double height = InputValidator::GetDoubleInput("Зріст (см): ");
        double weight = InputValidator::GetDoubleInput("Вага (кг): ");
        double value = InputValidator::GetDoubleInput("Ринкова вартість: ");

        int pos = InputValidator::GetIntInRange(
            "Позиція (0=GK,1=DEF,2=MID,3=FWD): ", 0, 3);
        Position position = static_cast<Position>(pos);

        int type = InputValidator::GetIntInRange(
            "Тип (1=Контрактний, 2=Вільний агент): ", 1, 2);

        if (type == 1)
        {
            double salary = InputValidator::GetDoubleInput("Річна зарплата: ");
            std::string contractUntil = InputValidator::GetNonEmptyString(
                "Контракт до (YYYY-MM-DD): ");

            auto newPlayer = std::make_shared<YourDerivedPlayer>(
                name, age, nationality, origin, height, weight, value, position,
                salary, contractUntil);
            clubManager_->AddPlayer(newPlayer);
        }
        else
        {
            double expectedSalary = InputValidator::GetDoubleInput(
                "Очікувана зарплата: ");
            std::string lastClub = InputValidator::GetNonEmptyString(
                "Останній клуб: ");
            auto newAgent = std::make_shared<FreeAgent>(
                name, age, nationality, origin, height, weight, value, position,
                expectedSalary, lastClub);
            clubManager_->AddPlayer(newAgent);
        }
    }

    void Menu::viewPlayersFlow() const
    {
        clubManager_->ViewAllPlayers();
    }

    void Menu::searchPlayerFlow() const
    {
        std::cout << "\n--- ПОШУК ТА ФІЛЬТРАЦІЯ ---\n";
        std::cout << "1. Пошук за ім’ям\n";
        std::cout << "2. Сортування за рейтингом\n";
        std::cout << "3. Фільтрація за статусом\n";

        int choice = InputValidator::GetIntInRange("Ваш вибір: ", 1, 3);

        if (choice == 1)
        {
            std::string query = InputValidator::GetNonEmptyString(
                "Введіть ім’я або частину: ");
            auto results = clubManager_->SearchByName(query);
            for (const auto& p : results)
            {
                p->ShowInfo();
                std::cout << "------------------------\n";
            }
        }
        else if (choice == 2)
        {
            clubManager_->SortByPerformanceRating();
            clubManager_->ViewAllPlayers();
        }
        else if (choice == 3)
        {
            std::string status = InputValidator::GetNonEmptyString(
                "Введіть статус (Active, Injured...): ");
            auto results = clubManager_->FilterByStatus(status);
            for (const auto& p : results)
            {
                p->ShowInfo();
                std::cout << "------------------------\n";
            }
        }
    }

    void Menu::transferFlow()
    {
        std::cout << "\n--- ТРАНСФЕРНИЙ РИНОК ---\n";
        std::string nameQuery = InputValidator::GetNonEmptyString(
            "Пошук агента за ім’ям: ");
        auto found = clubManager_->SearchByName(nameQuery);

        std::shared_ptr<FreeAgent> agent = nullptr;
        for (const auto& p : found)
        {
            agent = std::dynamic_pointer_cast<FreeAgent>(p);
            if (agent && agent->IsAvailableForNegotiation()) break;
        }

        if (!agent)
        {
            std::cout << "[ПОМИЛКА] Вільного агента не знайдено.\n";
            return;
        }

        std::cout << "[ІНФО] Знайдено агента: " << agent->GetName() <<
            std::endl;
        double offer = InputValidator::GetDoubleInput(
            "Запропонована зарплата: ");
        std::string until = InputValidator::GetNonEmptyString(
            "Контракт до (YYYY-MM-DD): ");

        if (clubManager_->SignFreeAgent(agent, offer, until))
            std::cout << "[УСПІХ] Контракт підписано.\n";
        else
            std::cout << "[ПОМИЛКА] Не вдалося підписати контракт.\n";
    }

    void Menu::manageUsersFlow()
    {
        std::cout << "\n--- КЕРУВАННЯ КОРИСТУВАЧАМИ ---\n";
        AuthManager::GetInstance().ViewAllUsers();

        std::cout << "1. Створити користувача\n";
        std::cout << "2. Видалити користувача\n";
        int choice = InputValidator::GetIntInRange("Ваш вибір: ", 1, 2);

        if (choice == 1)
            adminCreateUser();
        else
        {
            std::string login = InputValidator::GetNonEmptyString(
                "Логін користувача для видалення: ");
            AuthManager::GetInstance().DeleteUser(login);
        }
    }

    void Menu::adminCreateUser()
    {
        std::string login = InputValidator::GetNonEmptyString("Новий логін: ");
        std::string password = InputValidator::GetNonEmptyString("Пароль: ");
        int role = InputValidator::GetIntInRange(
            "Роль (1=Admin, 2=User): ", 1, 2);

        AuthManager::GetInstance().Register(login, password,
                                            (role == 1
                                                 ? UserRole::Admin
                                                 : UserRole::StandardUser));
    }
}
