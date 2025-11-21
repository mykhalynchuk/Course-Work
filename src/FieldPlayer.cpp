#include "../include/FieldPlayer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace FootballManagement
{
    FieldPlayer::FieldPlayer() : Player(), totalGames_(0), totalGoals_(0),
                                 totalAssists_(0), totalShots_(0),
                                 totalTackles_(0), keyPasses_(0),
                                 position_(Position::Forward)
    {
    }

    FieldPlayer::FieldPlayer(const std::string& name, int age,
                             const std::string& nationality,
                             const std::string& origin, double height,
                             double weight, double marketValue,
                             Position position) :
        Player(name, age, nationality, origin, height, weight, marketValue),
        totalGames_(0), totalGoals_(0), totalAssists_(0), totalShots_(0),
        totalTackles_(0), keyPasses_(0), position_(position)
    {
    }

    FieldPlayer::FieldPlayer(const FieldPlayer& other) : Player(other),
        totalGames_(other.totalGames_), totalGoals_(other.totalGoals_),
        totalAssists_(other.totalAssists_), totalShots_(other.totalShots_),
        totalTackles_(other.totalTackles_), keyPasses_(other.keyPasses_),
        position_(other.position_)
    {
    }

    FieldPlayer::FieldPlayer(FieldPlayer&& other) noexcept :
        Player(std::move(other)), totalGames_(other.totalGames_),
        totalGoals_(other.totalGoals_), totalAssists_(other.totalAssists_),
        totalShots_(other.totalShots_), totalTackles_(other.totalTackles_),
        keyPasses_(other.keyPasses_), position_(other.position_)
    {
        other.totalGames_ = 0;
        other.totalGoals_ = 0;
    }

    FieldPlayer& FieldPlayer::operator=(const FieldPlayer& other)
    {
        if (this != &other)
        {
            Player::operator=(other);
            totalGames_ = other.totalGames_;
            totalGoals_ = other.totalGoals_;
            totalAssists_ = other.totalAssists_;
            totalShots_ = other.totalShots_;
            totalTackles_ = other.totalTackles_;
            keyPasses_ = other.keyPasses_;
            position_ = other.position_;
        }
        return *this;
    }

    FieldPlayer& FieldPlayer::operator=(FieldPlayer&& other) noexcept
    {
        if (this != &other)
        {
            Player::operator=(std::move(other));
            totalGames_ = other.totalGames_;
            totalGoals_ = other.totalGoals_;
            totalAssists_ = other.totalAssists_;
            totalShots_ = other.totalShots_;
            totalTackles_ = other.totalTackles_;
            keyPasses_ = other.keyPasses_;
            position_ = other.position_;

            other.totalGames_ = 0;
            other.totalGoals_ = 0;
        }
        return *this;
    }

    FieldPlayer::~FieldPlayer()
    {
        std::cout <<"[DEBUG] FieldPlayer " << GetName() << " destroyed." << std::endl;
    }

    int FieldPlayer::GetTotalGoals() const { return totalGoals_; }

    int FieldPlayer::GetTotalAssists() const { return totalAssists_; }

    int FieldPlayer::GetTotalShots() const { return totalShots_; }

    int FieldPlayer::GetTotalTackles() const { return totalTackles_; }

    int FieldPlayer::GetTotalGames() const { return totalGames_; }

    int FieldPlayer::GetKeyPasses() const { return keyPasses_; }

    Position FieldPlayer::GetPosition() const { return position_; }

    void FieldPlayer::SetPosition(Position position) { position_ = position; }

    void FieldPlayer::UpdateAttackingStats(int goals, int assists, int shots)
    {
        if (goals < 0 || assists < 0 || shots < 0)
        {
            throw std::invalid_argument("Statistics updates cannot be negative.");
        }

        totalGoals_ += goals;
        totalAssists_ += assists;
        totalShots_ += shots;
    }

    void FieldPlayer::UpdateDefensiveStats(int tackles)
    {
        if (tackles < 0)
        {
            throw std::invalid_argument("Tackles update cannot be negative.");
        }
        totalTackles_ += tackles;
    }

    void FieldPlayer::RegisterKeyPass()
    {
        keyPasses_ += 1;
    }

    double FieldPlayer::CalculateConversionRate() const
    {
        if (totalShots_ == 0) return 0.0;

        return ((double)totalGoals_ / totalShots_) * 100.0;
    }

    void FieldPlayer::RegisterMatchPlayed()
    {
        totalGames_ += 1;
    }

    void FieldPlayer::ResetSeasonStats()
    {
        totalGames_ = 0;
        totalGoals_ = 0;
        totalAssists_ = 0;
        totalShots_ = 0;
        totalTackles_ = 0;
        keyPasses_ = 0;

        std::cout << "[INFO] Season statistics reset for " << GetName() << "." << std::endl;
    }

    void FieldPlayer::ShowInfo() const
    {
        std::cout << "--- FIELD PLAYER (ID: " << GetPlayerId() << ") ---" << std::endl;
        std::cout << "Name: " << GetName() << " | Pos: " << (int)position_ << " | Age: " << GetAge() << std::endl;
        std::cout << "Stats (G/A/Shots): " << totalGoals_ << "/" << totalAssists_ << "/" << totalShots_ << std::endl;
        std::cout << "Defensive: Tackles=" << totalTackles_ << " | Key Passes=" << keyPasses_ << std::endl;
        std::cout << "Conversion Rate: " << std::fixed << setprecision(2) << CalculateConversionRate() << "%" << std::endl;
    }

    void FieldPlayer::CelebrateBirthday()
    {
        std::cout << "[INFO] Happy Birthday, " << GetName() << "! New age (in derived class)." << std::endl;
    }
}



