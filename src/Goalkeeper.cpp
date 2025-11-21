#include "../include/Goalkeepeer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>

#include "../include/Goalkeepeer.h"

namespace FootballManagement
{
    Goalkeeper::Goalkeeper() : Player(), matchesPlayed_(0),
                               cleanSheets_(0), savesTotal_(0),
                               goalsConceded_(0), penaltiesSaved_(0)
    {
    }

    Goalkeeper::Goalkeeper(const std::string& name, int age,
                           const std::string& nationality,
                           const std::string& origin, double height,
                           double weight, double marketValue) :
        Player(name, age, nationality, origin, height, weight, marketValue),
        matchesPlayed_(0), cleanSheets_(0), savesTotal_(0), goalsConceded_(0),
        penaltiesSaved_(0)
    {
    }

    Goalkeeper::Goalkeeper(const Goalkeeper& other) : Player(other),
        matchesPlayed_(other.matchesPlayed_), cleanSheets_(other.cleanSheets_),
        savesTotal_(0), goalsConceded_(other.goalsConceded_),
        penaltiesSaved_(other.penaltiesSaved_)
    {
    }

    Goalkeeper::Goalkeeper(Goalkeeper&& other) noexcept :
        Player(std::move(other)), matchesPlayed_(other.matchesPlayed_),
        cleanSheets_(other.cleanSheets_), savesTotal_(0),
        goalsConceded_(other.goalsConceded_),
        penaltiesSaved_(other.penaltiesSaved_)
    {
        other.matchesPlayed_ = 0;
        other.cleanSheets_ = 0;
    }

    Goalkeeper& Goalkeeper::operator=(const Goalkeeper& other)
    {
        if (this != &other)
        {
            Player::operator=(other);
            matchesPlayed_ = other.matchesPlayed_;
            cleanSheets_ = other.cleanSheets_;
            savesTotal_ = other.savesTotal_;
            goalsConceded_ = other.goalsConceded_;
            penaltiesSaved_ = other.penaltiesSaved_;
        }
        return *this;
    }

    Goalkeeper& Goalkeeper::operator=(Goalkeeper&& other) noexcept
    {
        if (this != &other)
        {
            Player::operator=(std::move(other));
            matchesPlayed_ = other.matchesPlayed_;
            cleanSheets_ = other.cleanSheets_;
            savesTotal_ = other.savesTotal_;
            goalsConceded_ = other.goalsConceded_;
            penaltiesSaved_ = other.penaltiesSaved_;

            other.matchesPlayed_ = 0;
            other.cleanSheets_ = 0;
        }
        return *this;
    }

    Goalkeeper::~Goalkeeper()
    {
        std::cout << "[DEBUG] Goalkeeper " << GetName() << " destroyed." <<
            std::endl;
    }

    int Goalkeeper::GetMatchesPlayed() const { return matchesPlayed_; }

    int Goalkeeper::GetCleanSheets() const { return savesTotal_; }

    int Goalkeeper::GetGoalsConceded() const { return goalsConceded_; }

    int Goalkeeper::GetPenaltiesSaved() const { return penaltiesSaved_; }

    void Goalkeeper::UpdateMatchStats(int goalsAgainst, int saves)
    {
        if (goalsAgainst < 0 || saves < 0)
        {
            throw std::invalid_argument(
                "Statistics updates cannot be negative.");
        }

        matchesPlayed_ += 1;
        goalsConceded_ += goalsAgainst;
        savesTotal_ += saves;

        if (goalsAgainst == 0)
        {
            RegisterCleanSheet();
        }
    }

    void Goalkeeper::RegisterCleanSheet()
    {
        cleanSheets_ += 1;
    }

    void Goalkeeper::RegisterPenaltySave()
    {
        penaltiesSaved_ += 1;
    }

    double Goalkeeper::CalculateSavePercentage() const
    {
        int totalShotsFaced = savesTotal_ + goalsConceded_;
        if (totalShotsFaced == 0) return 0.0;

        return ((double)savesTotal_ / totalShotsFaced) * 100.0;
    }

    bool Goalkeeper::IsVeteran() const
    {
        return GetAge() >= 35;
    }

    void Goalkeeper::ResetSeasonStats()
    {
        matchesPlayed_ = 0;
        cleanSheets_ = 0;
        savesTotal_ = 0;
        goalsConceded_ = 0;
        penaltiesSaved_ = 0;

        std::cout << "[INFO] Goalkeeper stats reset for " << GetName() << "." <<
            std::endl;
    }

    void Goalkeeper::ShowInfo() const
    {
        std::cout << "--- GOALKEEPER INFO (ID: " << GetPlayerId() << ") ---" <<
            std::endl;
        std::cout << "Name: " << GetName() << " | Status: " << GetStatus() <<
            " | Age: " << GetAge() << std::endl;
        std::cout << "Matches: " << matchesPlayed_ << " | Clean Sheets: " <<
            cleanSheets_ << std::endl;
        std::cout << "Saves Total: " << savesTotal_ << " | Goals Conceded: " <<
            goalsConceded_ << " | Penalties Saved: " << penaltiesSaved_ <<
            std::endl;
        std::cout << "Save %: " << std::fixed << std::setprecision(2) <<
            CalculateSavePercentage() << "%" << std::endl;
    }

    double Goalkeeper::CalculatePerformanceRating() const
    {
        if (matchesPlayed_ == 0) return 0.0;

        double savePercentageFactor = CalculatePerformanceRating() / 10.0;
        double goalsPerMatchPenalty = ((double)goalsConceded_ / matchesPlayed_)
            * 2.0;

        double rating = (cleanSheets_ * 5.0) + savePercentageFactor -
            goalsPerMatchPenalty;

        return (rating > 0) ? rating : 0.0;
    }

    double Goalkeeper::CalculateValue() const
    {
        double baseValue = GetMarketValue();
        return baseValue + (cleanSheets_ * 500000.0) + (penaltiesSaved_ *
            1000000.0);
    }

    std::string Goalkeeper::GetStatus() const
    {
        return IsInjured() ? "Goalkeeper (Injured)" : "Goalkeeper (Active)";
    }

    void Goalkeeper::CelebrateBirthday()
    {
        std::cout << "[INFO] Goalkeeper " << GetName() << " is now " << GetAge()
            << ". Checking duration." << std::endl;
    }

    std::string Goalkeeper::Serialize() const
    {
        std::stringstream ss;
        ss << Player::SerializeBase() << ","
            << matchesPlayed_ << "," << cleanSheets_ << "," << savesTotal_ <<
            ","
            << goalsConceded_ << "," << penaltiesSaved_;
        return ss.str();
    }

    void Goalkeeper::Deserialize(const std::string& data)
    {
        Player::DeserializeBase(data);
        std::cout <<
            "[WARNING] Goalkeeper::Deserialize requires full parsing logic." <<
            std::endl;
    }
}
