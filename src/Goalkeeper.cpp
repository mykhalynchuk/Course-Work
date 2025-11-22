#include "../include/Goalkeepeer.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>

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
        other.savesTotal_ = 0;
        other.goalsConceded_ = 0;
        other.penaltiesSaved_ = 0;
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
            other.savesTotal_ = 0;
            other.goalsConceded_ = 0;
            other.penaltiesSaved_ = 0;
        }
        return *this;
    }

    Goalkeeper::~Goalkeeper() noexcept
    {
        std::cout << "[DEBUG] Воротар \"" << GetName() << "\" знищений."
            << std::endl;
    }

    int Goalkeeper::GetMatchesPlayed() const { return matchesPlayed_; }
    int Goalkeeper::GetCleanSheets() const { return savesTotal_; }

    void Goalkeeper::GetSavesTotal()
    {
    }

    int Goalkeeper::GetGoalsConceded() const { return goalsConceded_; }
    int Goalkeeper::GetPenaltiesSaved() const { return penaltiesSaved_; }

    void Goalkeeper::UpdateMatchStats(int goalsAgainst, int saves)
    {
        if (goalsAgainst < 0 || saves < 0)
            throw std::invalid_argument(
                "Помилка: статистика не може бути від’ємною.");

        matchesPlayed_ += 1;
        goalsConceded_ += goalsAgainst;
        savesTotal_ += saves;

        if (goalsAgainst == 0) RegisterCleanSheet();
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
        return (static_cast<double>(savesTotal_) / totalShotsFaced) * 100.0;
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
        matchesPlayed_ = cleanSheets_ = savesTotal_ = goalsConceded_ =
            penaltiesSaved_ = 0;
        std::cout << "[INFO] Статистика воротаря \"" << GetName()
            << "\" успішно обнулена." << std::endl;
    }

    void Goalkeeper::ShowInfo() const
    {
        std::cout << "\n=== Інформація про воротаря ===" << std::endl;
        std::cout << "Ім’я: " << GetName() << " | Вік: " << GetAge()
                  << " | Статус: " << GetStatus() << std::endl;
        std::cout << "Матчів: " << matchesPlayed_
                  << " | Сухих матчів: " << cleanSheets_ << std::endl;
        std::cout << "Сейви: " << savesTotal_
                  << " | Пропущено голів: " << goalsConceded_
                  << " | Відбиті пенальті: " << penaltiesSaved_ << std::endl;
        std::cout << "Відсоток сейвів: " << std::fixed << std::setprecision(2)
                  << CalculateSavePercentage() << "%" << std::endl;
    }

    double Goalkeeper::CalculatePerformanceRating() const
    {
        if (matchesPlayed_ == 0) return 0.0;

        double saveFactor = CalculateSavePercentage() / 10.0;
        double goalPenalty = static_cast<double>(goalsConceded_) / matchesPlayed_;
        double rating = (cleanSheets_ * 4.0) + (penaltiesSaved_ * 3.0) +
                        saveFactor - (goalPenalty * 2.0);

        return (rating < 0.0) ? 0.0 : rating;
    }

    double Goalkeeper::CalculateValue() const
    {
        double baseValue = GetMarketValue();
        double performanceBonus = CalculatePerformanceRating() * 100000.0;
        double cleanSheetBonus = cleanSheets_ * 300000.0;
        return baseValue + performanceBonus + cleanSheetBonus;
    }

    std::string Goalkeeper::GetStatus() const
    {
      return IsInjured() ? "Травмований воротар" : "Активний воротар";
    }

    void SetAge(int newAge);

    void Goalkeeper::CelebrateBirthday()
    {
        int newAge = GetAge() + 1;
        SetAge(newAge);
        std::cout << "[INFO] З днем народження, воротарю " << GetName()
                  << "! Тепер вам " << newAge << " років." << std::endl;
    }

    std::string Goalkeeper::Serialize() const
    {
       std::stringstream ss;
      ss << Player::Serialize()
         << "," << matchesPlayed_
         << "," << cleanSheets_
         << "," << savesTotal_
         << "," << goalsConceded_
         << "," << penaltiesSaved_;
      return ss.str();
    }

    void Goalkeeper::Deserialize(const std::string& data)
    {
        Player::DeserializeBase(data);
        std::cout << "[WARNING] Логіка повного розбору даних воротаря ще не реалізована."
                  << std::endl;
    }
}
