#include "../include/FreeAgent.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <utility>

namespace FootballManagement
{
    FreeAgent::FreeAgent() : FieldPlayer(), expectedSalary_(0.0),
                             lastClub_("Невідомо"), monthsWithoutClub_(0),
                             availableForNegotiation_(true)
    {
    }

    FreeAgent::FreeAgent(const std::string& name, int age,
                         const std::string& nationality,
                         const std::string& origin, double height,
                         double weight, double marketValue, Position position,
                         double expectedSalary, const std::string& lastClub) :
        FieldPlayer(name, age, nationality, origin, height, weight, marketValue,
                    position), expectedSalary_(expectedSalary),
        lastClub_(lastClub), monthsWithoutClub_(0),
        availableForNegotiation_(true)
    {
        if (expectedSalary < 0)
            throw std::invalid_argument(
                "Очікувана зарплата не може бути від’ємною.");
    }

    FreeAgent::FreeAgent(const FreeAgent& other) : FieldPlayer(other),
                                                   expectedSalary_(
                                                       other.expectedSalary_),
                                                   lastClub_(other.lastClub_),
                                                   monthsWithoutClub_(
                                                       other.
                                                       monthsWithoutClub_),
                                                   availableForNegotiation_(
                                                       other.
                                                       availableForNegotiation_)
    {
    }

    FreeAgent::FreeAgent(FreeAgent&& other) noexcept :
        FieldPlayer(std::move(other)), expectedSalary_(other.expectedSalary_),
        lastClub_(std::move(other.lastClub_)),
        monthsWithoutClub_(other.monthsWithoutClub_),
        availableForNegotiation_(other.availableForNegotiation_)
    {
        other.expectedSalary_ = 0.0;
        other.monthsWithoutClub_ = 0;
        other.availableForNegotiation_ = false;
    }

    FreeAgent& FreeAgent::operator=(const FreeAgent& other)
    {
        if (this != &other)
        {
            FieldPlayer::operator=(other);
            expectedSalary_ = other.expectedSalary_;
            lastClub_ = other.lastClub_;
            monthsWithoutClub_ = other.monthsWithoutClub_;
            availableForNegotiation_ = other.availableForNegotiation_;
        }
        return *this;
    }

    FreeAgent& FreeAgent::operator=(FreeAgent&& other) noexcept
    {
        if (this != &other)
        {
            FieldPlayer::operator=(std::move(other));
            expectedSalary_ = other.expectedSalary_;
            lastClub_ = std::move(other.lastClub_);
            monthsWithoutClub_ = other.monthsWithoutClub_;
            availableForNegotiation_ = other.availableForNegotiation_;

            other.expectedSalary_ = 0.0;
            other.monthsWithoutClub_ = 0;
        }
        return *this;
    }

    FreeAgent::~FreeAgent()
    {
        std::cout << "[DEBUG] Вільний агент \"" << GetName() << "\" видалений."
            << std::endl;
    }

    double FreeAgent::GetExpectedSalary() const { return expectedSalary_; }
    std::string FreeAgent::GetLastClub() const { return lastClub_; }

    bool FreeAgent::IsAvailableForNegotiation() const
    {
        return availableForNegotiation_;
    }

    int FreeAgent::GetMonthWithoutClub() const { return monthsWithoutClub_; }

    void FreeAgent::SetLastClub(std::string& lastClub) { lastClub_ = lastClub; }

    void FreeAgent::SetMonthWithoutClub(int months)
    {
        if (months < 0)
        {
            if (months < 0)
                throw std::invalid_argument(
                    "Кількість місяців без клубу не може бути від’ємною.");
            monthsWithoutClub_ = months;
        }
    }

    bool FreeAgent::NegotiateOffer(double offer)
    {
        if (!availableForNegotiation_)
        {
            std::cout << "[FAIL] " << GetName() << " не веде переговорів зараз."
                << std::endl;
            return false;
        }

        if (offer >= expectedSalary_)
        {
            std::cout << "[SUCCESS] " << GetName()
                << " прийняв пропозицію із зарплатою " << offer << " €." <<
                std::endl;
            availableForNegotiation_ = false;
            return true;
        }
        std::cout << "[INFO] " << GetName()
            << " відхилив пропозицію " << offer << " € (очікує "
            << expectedSalary_ << " €)." << std::endl;
        return false;
    }

    void FreeAgent::IncreaseExpectations(double percentage)
    {
        if (percentage <= 0.0) return;

        expectedSalary_ *= (1 + percentage / 100);
        std::cout << "[INFO] Очікування " << GetName()
            << " зросли на " << percentage << "%. Нова зарплата: "
            << expectedSalary_ << " €." << std::endl;
    }

    void FreeAgent::DecreaseExpectations(double percentage)
    {
        if (percentage <= 0) return;
        expectedSalary_ *= (1 - percentage / 100);
        std::cout << "[INFO] Очікування " << GetName()
            << " знижені на " << percentage << "%. Нова зарплата: "
            << expectedSalary_ << " €." << std::endl;
    }

    void FreeAgent::SetAvailability(bool isAvailable)
    {
        availableForNegotiation_ = isAvailable;
        std::cout << "[INFO] " << GetName()
            << (isAvailable ? " відкрив " : " закрив ")
            << "переговори." << std::endl;
    }

    void FreeAgent::AcceptContract(const std::string& club)
    {
        SetAvailability(false);
        lastClub_ = club;
        monthsWithoutClub_ = 0;
        std::cout << "[SUCCESS] " << GetName() <<
            " підписав контракт із клубом "
            << club << "." << std::endl;
    }

    bool FreeAgent::IsBargain() const
    {
        return CalculateValue() > expectedSalary_ * 1.3 && GetAge() <= 30;
    }

    void FreeAgent::ShowInfo() const
    {
        std::cout << "\n=== ВІЛЬНИЙ АГЕНТ ===" << std::endl;
        FieldPlayer::ShowInfo();
        std::cout << "Останній клуб: " << lastClub_
            << " | Місяців без клубу: " << monthsWithoutClub_ << std::endl;
        std::cout << "Очікувана зарплата: " << expectedSalary_
            << " € | Доступний до переговорів: "
            << (availableForNegotiation_ ? "Так" : "Ні") << std::endl;
    }

    double FreeAgent::CalculateValue() const
    {
        double penalty = 1.0 - (monthsWithoutClub_ * 0.05);
        penalty = std::max(0.5, penalty);
        return GetMarketValue() * penalty;
    }

    std::string FreeAgent::GetStatus() const
    {
        if (IsInjured()) return "Травмований вільний агент";
        if (!availableForNegotiation_) return "Контракт підписано";
        return "Вільний агент (активний)";
    }

    void FreeAgent::CelebrateBirthday()
    {
        int newAge = GetAge() + 1;
        SetAge(newAge);
        std::cout << "[INFO] З днем народження, " << GetName()
            << "! Тепер вам " << newAge << " років." << std::endl;
        IncreaseExpectations(3.0);
    }

    double FreeAgent::CalculatePerformanceRating() const
    {
        double rating = 70.0 - (monthsWithoutClub_ * 1.2);
        return std::max(40.0, rating);
    }

    std::string FreeAgent::Serialize() const
    {
        std::stringstream ss;
        ss << FieldPlayer::Serialize() << ","
           << expectedSalary_ << "," << lastClub_ << ","
           << monthsWithoutClub_ << "," << availableForNegotiation_;
        return ss.str();
    }

    void FreeAgent::Deserialize(const std::string& data)
    {
        FieldPlayer::Deserialize(data);
        std::cout << "[WARNING] Десеріалізація FreeAgent ще не реалізована." << std::endl;

    }
}
