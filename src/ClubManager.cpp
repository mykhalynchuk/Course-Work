#include "../include/ClubManager.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <typeinfo>

namespace FootballManagement
{
    ClubManager::ClubManager(const std::string& name,
                             double budget) :
        transferBudget_(budget), clubName_(name)
    {
        std::cout << "[INFO] Менеджер клубу \"" << clubName_
            << "\" ініціалізований (Бюджет: " << transferBudget_ << " €)." <<
            std::endl;
    }

    double ClubManager::GetTransferBudget() const { return transferBudget_; }

    void ClubManager::SetTransferBudget(double budget)
    {
        if (budget < 0.0)
            throw std::invalid_argument(
                "Бюджет не може бути від’ємним.");
        transferBudget_ = budget;
    }

    std::string ClubManager::GetClubName() const { return clubName_; }

    std::string ClubManager::GenerateUniqueId() const
    {
        int maxId = 1000;
        for (const auto& p : players_)
        {
            if (p->GetPlayerId() > maxId)
                maxId = p->GetPlayerId();
        }
        return maxId + 1;
    }

    void ClubManager::AddPlayer(std::shared_ptr<Player> p)
    {
        if (!p)
            throw std::invalid_argument("Неможливо додати порожнього гравця.");

        if (p->GetPlayerId() == 0)
            p->SetPlayerId(GenerateUniqueId());

        players_.push_back(p);
        std::cout << "[SUCCESS] Додано гравця: " << p->GetName()
            << " (ID: " << p->GetPlayerId() << ")." << std::endl;
    }

    void ClubManager::ViewAllPlayers() const
    {
        std::cout << "\n=== СКЛАД КЛУБУ \"" << clubName_ << "\" ===" <<
            std::endl;
        if (players_.empty())
        {
            std::cout << "Немає зареєстрованих гравців." << std::endl;
            return;
        }

        for (const auto& p : players_)
        {
            p->ShowInfo();
            std::cout << "--------------------------------------------" <<
                std::endl;
        }
    }

    void ClubManager::RemovePlayers(int playerId)
    {
        auto oldSize = players_.size();
        players_.erase(std::remove_if(players_.begin(), players_.end(),
                                      [playerId](const auto& p)
                                      {
                                          return p->GetPlayerId() == playerId;
                                      }),
                       players_.end());

        if (players_.size() < oldSize)
            std::cout << "[SUCCESS] Гравця з ID " << playerId << " видалено." <<
                std::endl;
        else
            std::cout << "[FAIL] Гравця з ID " << playerId << " не знайдено." <<
                std::endl;
    }

    void ClubManager::SortByPerformanceRating()
    {
        std::sort(players_.begin(), players_.end(),
                  [](const auto& a, const auto& b)
                  {
                      return a->CalculatePerformanceRating() > b->
                          CalculatePerformanceRating();
                  });
        std::cout << "[INFO] Гравці відсортовані за рейтингом ефективності." <<
            std::endl;
    }

    std::vector<std::shared_ptr<Player>> ClubManager::SearchByName(
        const std::string& nameQuery) const
    {
        std::vector<std::shared_ptr<Player>> results;
        std::string lowerQuery = nameQuery;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                       ::tolower);

        for (const auto& p : players_)
        {
            std::string name = p->GetName();
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

            if (name.find(lowerQuery) != std::string::npos)
                results.push_back(p);
        }
        return results;
    }

    std::vector<std::shared_ptr<Player>> ClubManager::FilterByStatus(
        const std::string& status) const
    {
        std::vector<std::shared_ptr<Player>> filtered;
        std::string lowerStatus = status;
        std::transform(lowerStatus.begin(), lowerStatus.end(),
                       lowerStatus.begin(), ::tolower);

        for (const auto& p : players_)
        {
            std::string playerStatus = p->GetStatus();
            std::transform(playerStatus.begin(), playerStatus.end(),
                           playerStatus.begin(), ::tolower);

            if (playerStatus.find(lowerStatus) != std::string::npos)
                filtered.push_back(p);
        }

        return filtered;
    }

    bool ClubManager::SignFreeAgent(std::shared_ptr<FreeAgent> player,
                                    double salaryOffer,
                                    const std::string& contractUntil)
    {
        if (!player)
        {
            std::cout << "[FAIL] Неможливо підписати: гравець не визначений." <<
                std::endl;
            return false;
        }

        if (salaryOffer <= 0)
        {
            std::cout << "[FAIL] Некоректна сума зарплати." << std::endl;
            return false;
        }

        if (salaryOffer > transferBudget_)
        {
            std::cout << "[FAIL] Недостатньо коштів у бюджеті для підписання."
                << std::endl;
            return false;
        }

        if (!player->NegotiateOffer(salaryOffer))
        {
            std::cout << "[FAIL] Гравець відхилив пропозицію." << std::endl;
            return false;
        }

        player->AcceptContract(clubName_);
        transferBudget_ -= salaryOffer;

        std::cout << "[SUCCESS] Вільний агент " << player->GetName()
            << " підписаний із клубом " << clubName_
            << ". Залишок бюджету: " << transferBudget_ << " €." << std::endl;

        return true;
    }

    std::string ClubManager::Serialize() const
    {
        std::stringstream ss;
        ss << clubName_ << "," << transferBudget_ << "\n";
        for (const auto& p : players_)
            ss << p->Serialize() << "\n";
        return ss.str();
    }

    void ClubManager::Deserialize(const std::string& data)
    {
        if (data.empty()) return;

        std::cout <<
            "[WARNING] Використовуйте DeserializeAllPlayers для повного завантаження."
            << std::endl;
    }

    void ClubManager::DeserializeAllPlayers(
        const std::vector<std::string>& lines)
    {
        players_.clear();

        if (lines.empty())
        {
            std::cout << "[WARNING] Порожній файл — гравців не знайдено." <<
                std::endl;
            return;
        }

        try
        {
            std::stringstream ss(lines[0]);
            std::string budgetStr;
            getline(ss, clubName_, ',');
            if (getline(ss, budgetStr))
                transferBudget_ = stod(budgetStr);

            std::cout << "[INFO] Завантажено дані клубу: " << clubName_
                << " | Бюджет: " << transferBudget_ << " €." << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] Помилка при розборі даних клубу: " << e.what()
                << std::endl;
        }

        std::cout <<
            "[WARNING] Логіка створення гравців при завантаженні поки не реалізована."
            << std::endl;
    }
}
