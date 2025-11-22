#include "../include/FieldPlayer.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

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
        std::cout << "[DEBUG] Польовий гравець \"" << GetName()
            << "\" знищений." << std::endl;
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
            throw std::invalid_argument(
                "Помилка: статистика не може бути від’ємною.");

        totalGoals_ += goals;
        totalAssists_ += assists;
        totalShots_ += shots;
    }

    void FieldPlayer::UpdateDefensiveStats(int tackles)
    {
        if (tackles < 0)
            throw std::invalid_argument(
                "Помилка: кількість відборів не може бути від’ємною.");
        totalTackles_ += tackles;
    }

    void FieldPlayer::RegisterKeyPass()
    {
        keyPasses_ += 1;
    }

    double FieldPlayer::CalculateConversionRate() const
    {
        if (totalShots_ == 0) return 0.0;
        return (static_cast<double>(totalGoals_) / totalShots_) * 100.0;
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

        std::cout << "[INFO] Статистика сезону для гравця \"" << GetName()
            << "\" успішно обнулена." << std::endl;
    }

    void FieldPlayer::ShowInfo() const
    {
        std::cout << "\n=== Інформація про польового гравця ===" << std::endl;
        std::cout << "Ім’я: " << GetName()
                  << " | Вік: " << GetAge()
                  << " | Позиція: " << static_cast<int>(position_) << std::endl;

        std::cout << "Матчів: " << totalGames_
                  << " | Голів: " << totalGoals_
                  << " | Асистів: " << totalAssists_ << std::endl;

        std::cout << "Удари: " << totalShots_
                  << " | Відбори: " << totalTackles_
                  << " | Ключові паси: " << keyPasses_ << std::endl;

        std::cout << "Конверсія ударів: " << std::fixed << std::setprecision(2)
                  << CalculateConversionRate() << "%" << std::endl;
    }

    void SetAge(int newAge);

    void FieldPlayer::CelebrateBirthday()
    {
        int newAge = GetAge() + 1;
        SetAge(newAge);

        std::cout << "[INFO] З днем народження, " << GetName()
                  << "! Тепер вам " << newAge << " років. "
                  << "Бажаємо нових перемог!" << std::endl;}
}
