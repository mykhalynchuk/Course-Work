#include "../include/ClubManager.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <typeinfo>

namespace FootballManagement
{
    ClubManager::ClubManager(const std::string& clubName,
                             double transferBudget) :
        transferBudget_(transferBudget), clubName_(clubName)
    {
        std::cout << "[INFO] Club Manager initialized for " << clubName_ <<
            " (Budget: " << transferBudget_ << ")." << std::endl;
    }

    double ClubManager::GetTransferBudget() const { return transferBudget_; }

    void ClubManager::SetTransferBudget(double transferBudget)
    {
        if (transferBudget < 0.0)
        {
            throw std::invalid_argument("Budget cannot be negative.");
            transferBudget_ = transferBudget;
        }
    }

    std::string ClubManager::GetClubName() const { return clubName_; }

    std::string ClubManager::generateUniqueId() const
    {
        if (players_.empty())
        {
            return 1001;
        }
        int maxId = 0;
        for (const auto& p : players_)
        {
            if (p->GetPlayerId() > maxId)
            {
                maxId = p->GetPlayerId();
            }
        }
        return maxId + 1;
    }

    void ClubManager::AddPlayer(std::shared_ptr<Player> p)
    {
        if (p->GetPlayerId() == 0)
        {
            p->SetPlayerId(generateUniqueId());
        }
        players_.push_back(p);
        std::cout << "[SUCCESS] Added player " << p->GetName() << " (ID: " << p
            ->GetPlayerId() << ")." << std::endl;
    }

    void ClubManager::ViewAllPlayers() const
    {
        std::cout << "\n--- ALL PLAYERS IN " << clubName_ << " (" << players_.
            size() << ") ---" << std::endl;
        for (const auto& p : players_)
        {
            p->ShowInfo();
            std::cout << "-----------------------------------" << std::endl;
        }
    }

    void ClubManager::RemovePlayers(int playerId)
    {
        auto initialSize = players_;

        auto it = std::remove_if(players_.begin(), players_.end(),
                                 [&](const auto& p)
                                 {
                                     return p->GetPlayerId() == playerId;
                                 });

        players_.erase(it, players_.end());

        if (players_.size() < initialSize)
        {
            std::cout << "[SUCCESS] Player ID " << playerId << " removed." <<
                std::endl;
        }
        else
        {
            std::cout << "[FAIL] Player with ID " << playerId << " not found."
                << std::endl;
        }
    }

    void ClubManager::SortByPerformanceRating()
    {
        std::sort(players_.begin(), players_.end(),
                  [](const auto& a, const auto& b)
                  {
                      return a->CalculatePerformanceRating() > b->
                          CalculatePerformanceRating();
                  });
        std::cout <<
            "[INFO] Players sorted by Performance Rating (highest first)." <<
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
            std::string lowerName = p->GetName();
            std::transform(lowerName.begin(), lowerName.end(),
                           lowerName.begin(), ::tolower);

            if (lowerName.find(lowerQuery) != std::string::npos)
            {
                results.push_back(p);
            }
        }
        return results;
    }

    std::vector<std::shared_ptr<Player>> ClubManager::SearchByName(
        const std::string& nameQuery) const
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
            {
                filtered.push_back(p);
            }
        }
        return filtered;
    }

    bool ClubManager::SignFreeAgent(std::shared_ptr<FreeAgent> player,
                                    double salaryOffer,
                                    const std::string& contractUntil)
    {
        if (!player || player->GetStatus().find("free agent") ==
            std::string::npos) return false;

        if (salaryOffer * 5.0 > transferBudget_)
        {
            std::cout << "[FAIL] Insufficient budget for contract commitment."
                << std::endl;
            return false;
        }

        if (!player->NegotiateOffer(salaryOffer))
        {
            std::cout << "[FAIL] Free agent rejected the offer." << std::endl;
            return false;
        }

        player->AcceptContract(clubName_);
        transferBudget_ -= (salaryOffer * 0.1);

        std::cout << "[SUCCESS] " << player->GetName() <<
            " SIGNED! Budget remaining: " << transferBudget_ << std::endl;

        return true;
    }

    std::string ClubManager::Serialize() const
    {
        std::stringstream ss;
        ss << clubName_ << "," << transferBudget_ << "\n";

        for (const auto& p : players_)
        {
            ss << p->Serialize() << "\n";
        }
        return ss.str();
    }

    void ClubManager::Deserialize(const std::string& data)
    {
        if (!data.empty())
        {
            std::cout <<
                "[WARNING] ClubManager::Deserialize called. Use DeserializeAllPlayers."
                << std::endl;
        }
    }

    void ClubManager::DeserializeAllPlaters(
        const std::vector<std::string>& lines)
    {
        players_.clear();
        if (lines.empty()) return;

        try
        {
            std::stringstream ss(lines[0]);
            std::string budgetStr;
            getline(ss, clubName_, ',');
            if (getline(ss, budgetStr))
            {
                transferBudget_ = stod(budgetStr);
            }
            std::cout << "[INFO] Loaded club metadata: " << clubName_ <<
                ", Budget: " << transferBudget_ << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] Failed to parse club metadata: " << e.what()
                << std::endl;
        }

        for (std::size_t i = 1; i < lines.size(); i++)
        {
        }
        std::cout <<
            "[WARNING] Player loading logic is incomplete. Need type identification."
            << std::endl;
    }
}
