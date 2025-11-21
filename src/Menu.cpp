#include "../include/Menu.h"
#include "../include/InputValidator.h"
#include "../include/ContractedPlayer.h"
#include "../include/FreeAgent.h"
#include "../include/AuthManager.h"
#include "../include/FileManager.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

namespace FootballManagement
{
    Menu::Menu(std::shared_ptr<ClubManager> clubManager) :
        clubManager_(clubManager), isRunning_(true)
    {
    }

    void Menu::LoadAllData()
    {
        try
        {
            std::vector<std::string> userLines = fileManager_.LoadFromFile(
                USERS_FILE_NAME);
            AuthManager::GetInstance().DeserializeAllUsers(userLines);
            std::cout << "[INFO] Users data loaded." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] Error during user file load: " << e.what() <<
                std::endl;
        }

        try
        {
            std::vector<std::string> playerLines = fileManager_.LoadFromFile(
                PLAYERS_DATA_FILE);
            clubManager_->DeserializeAllPlayers(playerLines);
            std::cout << "[INFO] Players data load attempted." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] Error during player file load: " << e.what()
                << std::endl;
        }
    }

    void Menu::SaveAllData() const
    {
        std::cout << "[INFO] Attempting to save all data..." << std::endl;

        fileManager_.SaveToFile(USERS_FILE_NAME, AuthManager::GetInstance());

        fileManager_.SaveToFile(PLAYERS_DATA_FILE, *clubManager_);

        std::cout << "[INFO] All data saved successfully." << std::endl;
    }

    void Menu::Run()
    {
        LoadAllData();
        authenticateUser();

        while (isRunning_ && AuthManager::GetInstance().IsLoggedIn())
        {
            displayMainManu();
            int choice = InputValidator::GetIntInRange("Enter choice: ", 1, 9);
            handleMainMenu(choice);
        }

        if (!AuthManager::GetInstance().IsLoggedIn())
        {
            std::cout << "\nAccess denied or session ended. Application closed."
                << std::endl;
        }
    }

    void Menu::Stop()
    {
        isRunning_ = false;
        std::cout << "[INFO] Shutting down application..." << std::endl;
    }

    void Menu::authenticateUser()
    {
        std::cout << "========================================" << std::endl;
        std::cout << "  FOOTBALL TEAM MANAGEMENT SYSTEM (C++)" << std::endl;
        std::cout << "========================================" << std::endl;

        for (int attempts = 0; attempts < 3; ++attempts)
        {
            std::string login = InputValidator::GetNonEmptyString(
                "Enter Login: ");
            sstd::tring password = InputValidator::GetNonEmptyString(
                "Enter Password: ");

            if (AuthManager::GetInstance().Login(login, password))
            {
                return;
            }
        }
        Stop();
    }

    void Menu::displayMainMenu() const
    {
        std::cout << "\n=========== MAIN MENU ===========" << std::endl;
        std::cout << "1. Player Management (Add/Delete)" << std::endl;
        std::cout << "2. View All Players" << std::endl;
        std::cout << "3. Search, Sort & Filter Players" << std::endl;
        std::cout << "4. Transfer Market (Sign Free Agent)" << std::endl;

        if (AuthManager::GetInstance().GetCurrentUser()->IsAdmin())
        {
            std::cout << "5. Manage User Accounts (Admin Only)" << std::endl;
        }

        std::cout << "7. Help / User Instruction" << std::endl;
        std::cout << "8. Save All Data" << std::endl;
        std::cout << "9. Save and Exit" << std::endl;
        std::cout << "=================================" << std::endl;
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
            else
            {
                std::cout << "[ACCESS DENIED] Admin privileges required." <<
                    std::endl;
            }
            break;
        case 7: displayHelp();
            break;
        case 8: SaveAllData();
            break;
        case 9: saveAndExit();
            break;
        default: std::cout << "[ERROR] Invalid choice. Try again." << std::endl;
        }
    }

    void Menu::saveAndExit()
    {
        if (InputValidator::GetYesNoInput(
            "Do you want to save all changes before exiting?"))
        {
            SaveAllData();
        }
        AuthManager::GetInstance().Logout();
        Stop();
    }

    void Menu::displayHelp() const
    {
        std::cout << "\n============ HELP / USER INSTRUCTION ============" <<
            std::endl;
        std::cout <<
            "This application allows you to manage a football team roster." <<
            std::endl;

        std::cout << "\n--- Functionality ---" << std::endl;
        std::cout <<
            "* Player Management: Add, edit, or remove players (Contracted/Free Agent)."
            << std::endl;
        std::cout <<
            "* Search & Filter: Allows searching by name, sorting by performance rating, and filtering by status."
            << std::endl;
        std::cout <<
            "* Transfer Market: Perform operations like signing a free agent."
            << std::endl;

        std::cout << "\n--- Rules for Data Input ---" << std::endl;
        std::cout << "* Numerical inputs (Age, Salary, ID) must be positive." <<
            std::endl;
        std::cout << "* Dates must be entered in YYYY-MM-DD format." <<
            std::endl;
        std::cout << "=================================================\n" <<
            std::endl;
    }

    void Menu::displayPlayerMenu() const
    {
        std::cout << "\n======== PLAYER MANAGEMENT ========" << std::endl;
        std::cout << "1. Add New Player (Contracted/Free Agent)" << std::endl;
        std::cout << "2. Delete Player by ID" << std::endl;
        std::cout << "3. Back to Main Menu" << std::endl;

        int choice = InputValidator::GetIntInRange("Enter choice: ", 1, 3);

        if (choice == 1) addPlayerFlow();
        if (choice == 2) deletePlayerFlow();
    }

    void Menu::deletePlayerFlow()
    {
        int id = InputValidator::GetIntInput("Enter player ID to delete: ");
        clubManager_->RemovePlayer(id);
    }

    void Menu::addPlayerFlow()
    {
        std::cout << "\n--- ADD NEW PLAYER ---" << std::endl;

        std::string name = InputValidator::GetNonEmptyString("Enter player's name: ");
        int age = InputValidator::GetIntInRange("Enter player's age: ", 16, 45);
        std::string nationality = InputValidator::GetNonEmptyString("Enter nationality: ");
        std::string origin = InputValidator::GetNonEmptyString("Enter origin: ");
        double height = InputValidator::GetDoubleInput("Enter height (cm): ");
        double weight = InputValidator::GetDoubleInput("Enter weight (kg): ");
        double value = InputValidator::GetDoubleInput("Enter market value: ");

        std::cout << "Position options (0=GK, 1=Def, 2=Mid, 3=Fwd): " << std::endl;
        int pos_int = InputValidator::GetIntInRange("Enter position index: ", 0, 3);
        Position position = static_cast<Position>(pos_int);

        int type = InputValidator::GetIntInRange("1. Contracted Player / 2. Free Agent: ", 1, 2);

        if (type == 1)
        {
            double salary = InputValidator::GetDoubleInput("Enter annual salary: ");
            std::string contractUntil = InputValidator::GetNonEmptyString("Enter contract end date (YYYY-MM-DD): ");

            auto newPlayer = std::make_shared<ContractedPlayer>(
                name, age, nationality, origin, height, weight, value, position, salary, contractUntil
            );
            clubManager_->AddPlayer(newPlayer);
        }
        else
        {
            double expectedSalary = InputValidator::GetDoubleInput("Enter expected annual salary: ");
            std::string lastClub = InputValidator::GetNonEmptyString("Enter last club (N/A if none): ");

            auto newAgent = make_shared<FreeAgent>(
                name, age, nationality, origin, height, weight, value, position, expectedSalary, lastClub
            );
            clubManager_->AddPlayer(newAgent);
        }
    }

    void Menu::viewPlayersFlow() const
    {
        clubManager_->ViewAllPlayers();
    }

    void Menu::searchPlayerFlow() const
    {
        std::cout << "\n--- SEARCH, SORT & FILTER ---" << std::endl;
        std::cout << "1. Search by Name" << std::endl;
        std::cout << "2. Sort by Performance Rating (Descending)" << std::endl;
        std::cout << "3. Filter by Status (e.g., Active, Injured)" << std::endl;

        int choice = InputValidator::GetIntInRange("Enter choice: ", 1, 3);

        // 2.2 Порожні рядки: перед ізольованою в логічному сенсі частиною коду
        if (choice == 1)
        {
            std::string query = InputValidator::GetNonEmptyString("Enter name or part of name: ");
            auto results = clubManager_->SearchByName(query);

            std::cout << "\n--- Search Results (" << results.size() << ") ---" << std::endl;
            for (const auto& p : results) {
                p->ShowInfo();
                std::cout << "-----------------------------------" << std::endl;
            }
        }
        else if (choice == 2)
        {
            // Логіка сортування
            clubManager_->SortByPerformanceRating();
            clubManager_->ViewAllPlayers();
        }
        else if (choice == 3)
        {
            std::string status = InputValidator::GetNonEmptyString("Enter status to filter (e.g., Active, Injured, Free Agent): ");
            auto results = clubManager_->FilterByStatus(status);

            std::cout << "\n--- Filtered Results (" << results.size() << ") ---" << std::endl;
            for (const auto& p : results) {
                p->ShowInfo();
                std::cout << "-----------------------------------" << std::endl;
            }
        }
    }

    void Menu::transferFlow()
{
    std::cout << "\n--- TRANSFER MARKET: SIGN FREE AGENT ---" << endl;

    // 1. Пошук агента за ім'ям
    std::string nameQuery = InputValidator::GetNonEmptyString("Search Free Agent by name: ");
    auto agentsFound = clubManager_->SearchByName(nameQuery);

    // 2. Фільтрація результатів, щоб залишити лише FreeAgent
    // Використовуємо dynamic_pointer_cast для перевірки типу
    std::shared_ptr<FreeAgent> selectedAgent = nullptr;

    for (const auto& p : agentsFound)
    {
        // 2.2 Порожні рядки: перед ізольованою в логічному сенсі частиною коду
        selectedAgent = std::dynamic_pointer_cast<FreeAgent>(p);
        if (selectedAgent && selectedAgent->IsAvailableForNegotiation())
        {
             // Якщо знайдено першого доступного агента, беремо його ID
             std::cout << "[INFO] Found available Free Agent: " << selectedAgent->GetName() << std::endl;
             break;
        }
    }

    if (!selectedAgent)
    {
        std::cout << "[FAIL] No available Free Agents found matching your search." << std::endl;
        return;
    }

    // 3. Збір даних та пропозиція
    std::cout << "--- Offering contract to " << selectedAgent->GetName() << " ---" << std::endl;
    double expected = selectedAgent->GetExpectedSalary();

    std::cout << "Expected Salary: " << std::fixed << std::setprecision(0) << expected << std::endl;
    double salaryOffer = InputValidator::GetDoubleInput("Enter Annual Salary Offer: ");
    std::string contractUntil = InputValidator::GetNonEmptyString("Enter Contract End Date (YYYY-MM-DD): ");

    // 4. Спроба підписання через ClubManager
    bool success = clubManager_->SignFreeAgent(selectedAgent, salaryOffer, contractUntil);

    if (success)
    {
        // Після успішного підписання агент перетворюється на контрактного гравця
        std::cout << "\n[SUCCESS] Contract finalized. Player will be added to the roster." << std::endl;
    }
    else
    {
        std::cout << "\n[FAIL] Contract offer rejected or budget insufficient." << std::endl;
    }
}

    void Menu::manageUsersFlow()
    {
        std::cout << "\n--- ADMIN: MANAGE USERS ---" <<  std::endl;
        AuthManager::GetInstance().ViewAllUsers();

         std::cout << "1. Create New User" <<  std::endl;
         std::cout << "2. Delete User" <<  std::endl;

        int choice = InputValidator::GetIntInRange("Enter choice: ", 1, 2);

        if (choice == 1) adminCreateUser();
        else if (choice == 2)
        {
             std::string login = InputValidator::GetNonEmptyString("Enter login of user to delete: ");
            AuthManager::GetInstance().DeleteUser(login);
        }
    }

    void Menu::adminCreateUser()
    {
        std::cout << "\n--- CREATE NEW USER ---" << std::endl;
        std::string login = InputValidator::GetNonEmptyString("New Username (login): ");
        std::string password = InputValidator::GetNonEmptyString("New Password: ");
        int role_int = InputValidator::GetIntInRange("Role (1=Admin, 2=Standard): ", 1, 2);

        UserRole role = (role_int == 1) ? UserRole::Admin : UserRole::StandardUser;

        AuthManager::GetInstance().Register(login, password, role);
    }
}
