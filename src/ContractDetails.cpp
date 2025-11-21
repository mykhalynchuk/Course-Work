#include "../include/ContractDetails.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

namespace FootballManagement
{
    ContractDetails::ContractDetails() : clubName_("N/A"), salary_(0.0),
                                         contractUntil_("N/A"),
                                         isLoaned_(false), loanEndDate_("")
    {
    }

    ContractDetails::ContractDetails(const std::string& clubName, double salary,
                                     std::string contractUntil) :
        clubName_(clubName), salary_(salary), contractUntil_(contractUntil),
        isLoaned_(false), loanEndDate_("")
    {
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
        {
            throw std::invalid_argument("Club name cannot be empty.");
        }
        clubName_ = clubName;
    }

    void ContractDetails::SetContractUntil(const std::string& contractUntil)
    {
        if (contractUntil.length() != 10)
        {
            throw std::invalid_argument("Data format must be YYYY-MM-DD.");
        }
        contractUntil_ = contractUntil;
    }

    void ContractDetails::SetOnLoan(const std::string& loanEndDate)
    {
        if (loanEndDate.empty())
        {
            throw std::invalid_argument("Loan end date cannot be empty.");
        }

        isLoaned_ = true;
        loanEndDate_ = loanEndDate;
        std::cout << "[INFO] Player set on loan until " << loanEndDate <<
            std::endl;
    }

    void ContractDetails::ReturnFromLoan()
    {
        isLoaned_ = false;
        loanEndDate_ = "";
        std::cout << "[INFO] Player returned from loan." << std::endl;
    }

    bool ContractDetails::IsExpiringSoon() const
    {
        if (!IsContractValid() || isLoaned_) return false;
        return contractUntil_.substr(0, 4) < "2026";
    }

    void ContractDetails::AdjustSalary(double percentage)
    {
        if (salary_ <= 0.0)
        {
            throw std::logic_error(
                "Cannot adjust salary, current salary is zero or negative.");
        }

        double factor = 1.0 + (percentage / 100.0);
        salary_ = salary_ * factor;
        std::cout << "[INFO] Salary adjusted by " << percentage <<
            "%. New salary: " << salary_ << std::endl;
    }

    void ContractDetails::ExtendContractDate(const std::string& newDate)
    {
        if (newDate.length() < 10)
        {
            throw std::invalid_argument("Invalid date format. Use YYYY-MM-DD&");
        }
        contractUntil_ = newDate;
        std::cout << "[INFO] Contract extended until " << newDate << std::endl;
    }

    bool ContractDetails::IsContractValid() const
    {
        return contractUntil_ != "N/A" && contractUntil_.length() == 10;
    }

    void ContractDetails::ShowDetails() const
    {
        std::cout << " -Club: " << clubName_ << " | Salary: " << std::fixed <<
            std::setprecision(2) << salary_ << std::endl;
        std::cout << " -Contract Until: " << contractUntil_;

        if (isLoaned_)
        {
            std::cout << " (ON LOAN intil: " << loanEndDate_ << ")";
        }
        std::cout << std::endl;
    }
}
