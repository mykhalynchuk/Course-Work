#include "../include/FreeAgent.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <utility>

namespace FootballManagement
{
    FreeAgent::FreeAgent() : FieldPlayer(), expectedSalary_(0.0),
                             lastClub_("N/A"), monthsWithoutClub_(0),
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
        std::cout << "[DEBUG] FreeAgent " << GetName() << " destroyed." <<
            std::endl;
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
        if (month < 0)
        {
            throw std::invalid_argument("Months count cannot be negative.");
            monthsWithoutClub_ = months;
        }
    }

    void FreeAgent::IncreaseExpectations(double percentage)
    {
        if (percentage < 0.0) return;

        double factor = 1.0 + (percentage / 100.0);
        expectedSalary_ = expectedSalary_ * factor;
        std::cout << "[INFO] " << GetName() <<
            " increased expectations. New expected salary: " << expectedSalary_
            << std::endl;
    }

    void FreeAgent::DecreaseExpectations(double percentage)
    {
        if (percentage < 0.0) return;

        double factor = 1.0 - (percentage / 100.0);
        expectedSalary_ = expectedSalary_ * factor;
        std::cout << "[INFO] " << GetName() <<
            " decreased expectations. New expected salary: " << expectedSalary_
            << std::endl;
    }

    void FreeAgent::SetAvailability(bool isAvailable)
    {
        availableForNegotiation_ = isAvailable;
        std::cout << "[INFO] " << GetName() <<
            " negotiation availability set to: " << (isAvailable
                ? "Open"
                : "Closed") << std::endl;
    }

    void FreeAgent::AcceptContract(const std::string& club)
    {
        SetAvailability(false);
        SetLastClub(club);
        std::cout << "[SUCCESS] " << GetName() << " signed contract with " <<
            club << "." << std::endl;
    }

    bool FreeAgent::IsBargin() const
    {
        return CalculateValue() > expectedSalary_ * 1.5;
    }

    void FreeAgent::ShowInfo() const
    {
        FieldPlayer::ShowInfo();
        std::cout << "--- FREE AGENT DETAILS ---" << std::endl;
        std::cout << "Last Club: " << lastClub_ << " | Months Without Club: " <<
            monthsWithoutClub_ << std::endl;
        std::cout << "Expected Salary: " << std::fixed << std::setprecision(0)
            << expectedSalary_ << std::endl;
        std::cout << "Available: " << (availableForNegotiation_ ? "Yes" : "No")
            << std::endl;
    }

    double FreeAgent::CalculateValue() const
    {
        double reductionFactor = 1.0 - (monthsWithoutClub_ * 0.03);
        double marketValue = GetMarketValue() * reductionFactor;

        return (marketValue > 50000.0) ? marketValue : 50000.0;
    }

    std::string FreeAgent::GetStatus() const
    {
        if (!availableForNegotiation_)
            return
                "Free Agent (Negotiations Closed)";
        if (IsInjured()) return "Free Agent (Injured)";
        return "Free Agent (Available)";
    }

    void FreeAgent::CelebrateBirthday()
    {
        Player::CelebrateBirthday();
        SetMonthWithoutClub(GetMonthWithoutClub() + 1);
        std::cout << "[INFO] Free agent status prolonged." << std::endl;
    }

    double FreeAgent::CalculatePerformanceRating() const
    {
        double baseRating = FieldPlayer::CalculatePerformanceRating();
        return baseRating - (monthsWithoutClub_ * 0.5);
    }

    std::string FreeAgent::Serialize() const
    {
        std::stringstream ss;
        ss << FieldPlayer::Serialize() << ","
            << expectedSalary_ << "," << lastClub_ << "," << monthsWithoutClub_
            << ","
            << availableForNegotiation_;
        return ss.str();
    }

    void FreeAgent::Deserialize(const std::string& data)
    {
        FieldPlayer::Deserialize(data);
        std::cout <<
            "[WARNING] FreeAgent::Deserialize requires full parsing logic." <<
            std::endl;
    }
}


