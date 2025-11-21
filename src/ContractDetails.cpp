#include "../include/ContractDetails.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

namespace FootballManagement
{
    ContractDetails::ContractDetails() : clubName_("Невідомо"), salary_(0.0),
                                         contractUntil_("Невідомо"),
                                         isLoaned_(false), loanEndDate_("")
    {
    }

    ContractDetails::ContractDetails(const std::string& clubName, double salary,
                                     const std::string& contractUntil) :
        clubName_(clubName), salary_(salary), contractUntil_(contractUntil),
        isLoaned_(false), loanEndDate_("")
    {
        if (clubName.empty())
            throw std::invalid_argument("Назва клубу не може бути порожньою.");
        if (salary < 0.0)
            throw std::invalid_argument("Зарплата не може бути від’ємною.");
        if (contractUntil.length() != 10)
            throw std::invalid_argument(
                "Невірний формат дати (потрібно YYYY-MM-DD).");
    }

    ContractDetails::ContractDetails(const ContractDetails& other) :
        clubName_(other.clubName_), salary_(other.salary_),
        contractUntil_(other.contractUntil_), isLoaned_(other.isLoaned_),
        loanEndDate_(other.loanEndDate_)
    {
    }

    ContractDetails::ContractDetails(ContractDetails&& other) noexcept :
        clubName_(std::move(other.clubName_)), salary_(other.salary_),
        contractUntil_(std::move(other.contractUntil_)),
        isLoaned_(other.isLoaned_), loanEndDate_(std::move(other.loanEndDate_))
    {
        other.salary_ = 0.0;
        other.isLoaned_ = false;
    }

    ContractDetails& ContractDetails::operator=(const ContractDetails& other)
    {
        if (this != &other)
        {
            clubName_ = other.clubName_;
            salary_ = other.salary_;
            contractUntil_ = other.contractUntil_;
            isLoaned_ = other.isLoaned_;
            loanEndDate_ = other.loanEndDate_;
        }
        return *this;
    }

    ContractDetails& ContractDetails::operator=(
        ContractDetails&& other) noexcept
    {
        if (this != &other)
        {
            clubName_ = std::move(other.clubName_);
            salary_ = other.salary_;
            contractUntil_ = std::move(other.contractUntil_);
            isLoaned_ = other.isLoaned_;
            loanEndDate_ = std::move(other.loanEndDate_);

            other.salary_ = 0.0;
            other.isLoaned_ = false;
        }
        return *this;
    }

    std::string ContractDetails::GetClubName() const { return clubName_; }
    double ContractDetails::GetSalary() const { return salary_; }

    std::string ContractDetails::GetContractUntil() const
    {
        return contractUntil_;
    }

    bool ContractDetails::IsPlayerOnLoan() const { return isLoaned_; }

    void ContractDetails::SetClubName(const std::string& clubName)
    {
        if (clubName.empty())
            throw std::invalid_argument("Назва клубу не може бути порожньою.");
        clubName_ = clubName;
    }

    void ContractDetails::SetContractUntil(const std::string& contractUntil)
    {
        if (contractUntil.length() != 10)
            throw std::invalid_argument(
                "Формат дати повинен бути YYYY-MM-DD.");

        contractUntil_ = contractUntil;
    }

    void ContractDetails::SetOnLoan(const std::string& loanEndDate)
    {
        if (loanEndDate.empty())
            throw std::invalid_argument(
                "Дата завершення оренди не може бути порожньою.");

        isLoaned_ = true;
        loanEndDate_ = loanEndDate;

        std::cout << "[INFO] Гравця орендовано до " << loanEndDate_ << "." <<
            std::endl;
    }

    void ContractDetails::ReturnFromLoan()
    {
        isLoaned_ = false;
        loanEndDate_.clear();
        std::cout << "[INFO] Гравець повернувся з оренди." << std::endl;
    }

    bool ContractDetails::IsExpiringSoon() const
    {
        if (!IsContractValid()) return false;

        std::string yearStr = contractUntil_.substr(0, 4);
        int year = std::stoi(yearStr);
        return (year <= 2025);
    }

    void ContractDetails::AdjustSalary(double percentage)
    {
        if (salary_ <= 0.0)
            throw std::logic_error(
                "Неможливо змінити зарплату, поточне значення ≤ 0.");

        double factor = 1.0 + (percentage / 100.0);
        salary_ = salary_ * factor;

        std::cout << "[INFO] Зарплата змінена на " << percentage
            << "%. Нова зарплата: " << std::fixed << std::setprecision(2)
            << salary_ << " €" << std::endl;
    }

    void ContractDetails::ExtendContractDate(const std::string& newDate)
    {
        if (newDate.length() < 10)
            throw std::invalid_argument(
                "Формат дати має бути YYYY-MM-DD.");
        contractUntil_ = newDate;

        std::cout << "[INFO] Контракт продовжено до " << newDate << "." <<
            std::endl;
    }

    bool ContractDetails::IsContractValid() const
    {
        return contractUntil_ != "Невідомо" && contractUntil_.length() == 10;
    }

    void ContractDetails::ShowDetails() const
    {
        std::cout << "\n=== Інформація про контракт ===" << std::endl;
        std::cout << "Клуб: " << clubName_
            << " | Зарплата: " << std::fixed << std::setprecision(2)
            << salary_ << " €" << std::endl;
        std::cout << "Контракт дійсний до: " << contractUntil_;

        if (isLoaned_)
            std::cout << " (Оренда до: " << loanEndDate_ << ")";
        std::cout << std::endl;
    }
}
