#include "../include/ContractedPlayer.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <utility>

namespace FootballManagement
{
    ContractedPlayer::ContractedPlayer() : FieldPlayer(), contract_details_(),
                                           listedForTransfer_(false),
                                           transferFee_(0.0),
                                           transferConditions_("")
    {
    }

    ContractedPlayer::ContractedPlayer(const std::string& name, int age,
                                       const std::string& nationality,
                                       std::string& origin,
                                       double height,
                                       double weight,
                                       double marketValue,
                                       Position position,
                                       double salary,
                                       const std::string& contractUntil) :
        FieldPlayer(name, age, nationality, origin, height, weight, marketValue,
                    position),
        contract_details_(FieldPlayer::GetName(), salary, contractUntil),
        listedForTransfer_(false), transferFee_(0.0),
        transferConditions_("")
    {
    }

    ContractedPlayer::ContractedPlayer(const ContractedPlayer& other) :
        FieldPlayer(other), contract_details_(other.contract_details_),
        listedForTransfer_(other.listedForTransfer_),
        transferFee_(other.transferFee_),
        transferConditions_(other.transferConditions_)
    {
    }

    ContractedPlayer::ContractedPlayer(ContractedPlayer&& other) noexcept :
        FieldPlayer(std::move(other)),
        contract_details_(std::move(other.contract_details_)),
        listedForTransfer_(other.listedForTransfer_),
        transferFee_(other.transferFee_),
        transferConditions_(std::move(other.transferConditions_))
    {
        other.transferFee_ = 0.0;
        other.listedForTransfer_ = false;
    }


    ContractedPlayer& ContractedPlayer::operator=(const ContractedPlayer& other)
    {
        if (this != &other)
        {
            FieldPlayer::operator=(other);
            contract_details_ = other.contract_details_;
            listedForTransfer_ = other.listedForTransfer_;
            transferFee_ = other.transferFee_;
            transferConditions_ = other.transferConditions_;
        }

        return *this;
    }

    ContractedPlayer& ContractedPlayer::operator=(
        ContractedPlayer&& other) noexcept
    {
        if (this != &other)
        {
            FieldPlayer::operator=(std::move(other));
            contract_details_ = std::move(other.contract_details_);
            listedForTransfer_ = other.listedForTransfer_;
            transferFee_ = other.transferFee_;
            transferConditions_ = std::move(other.transferConditions_);

            other.transferFee_ = 0.0;
            other.listedForTransfer_ = false;
        }

        return *this;
    }

    ContractedPlayer::~ContractedPlayer()
    {
        std::cout << "[DEBUG] ContractedPlayer " << GetName() << " destroyed."
            << std::endl;
    }

    bool ContractedPlayer::IsListedForTransfer() const
    {
        return listedForTransfer_;
    }

    double ContractedPlayer::GetTransferFee() const
    {
        return transferFee_;
    }

    ContractDetails ContractedPlayer::GetContractDetails() const
    {
        return contract_details_;
    }


    void ContractedPlayer::ListForTransfer(double fee,
                                           const std::string& conditions)
    {
        if (fee <= 0.0)
        {
            throw std::invalid_argument("Transfer fee must be positive.");
        }
        listedForTransfer_ = true;
        transferFee_ = fee;
        transferConditions_ = conditions;
        std::cout << "[INFO]" << GetName() <<
            " listed for transfer with minimum fee  " << fee << std::endl;
    }

    void ContractedPlayer::RemoveFromTransferList()
    {
        listedForTransfer_ = false;
        transferFee_ = 0.0;
        transferConditions_ = "";
        std::cout << "[INFO] " << GetName() << " removed from transfer list." <<
            std::endl;
    }

    void ContractedPlayer::TransferToClub(const std::string& newClub,
                                          double fee)
    {
        if (!listedForTransfer_ || fee < transferFee_)
        {
            std::cout << "[FAIL] Cannot sell " << GetName() <<
                ": Either not listed or fee is too low" << std::endl;
            return;
        }
        contract_details_.SetClubName(newClub);
        listedForTransfer_ = false;
        std::cout << "[SUCCESS] " << GetName() << " sold to " << newClub <<
            " for " << fee << "!" << std::endl;
    }

    void ContractedPlayer::ExtendContract(const std::string& newDate,
                                          double newSalary)
    {
        if (newSalary <= 0)
        {
            throw std::invalid_argument
                ("New salary must be positive.");
        }

        contract_details_.ExtendContractDate(newDate);
        double percentage = (newSalary / contract_details_.GetSalary() - 1.0) * 100.0;
        contract_details_.AdjustSalary(percentage);

        std::cout << "[SUCCESS] Contract for " << GetName() << " extended until " << newDate << std::endl;
    }

    void ContractedPlayer::TerminateContract(const std::string& reason)
    {
        contract_details_.SetClubName("N/A (Terminated)");
        std::cout << "[WARNING] Contract for " << GetName() << " terminated due to: " << reason << std::endl;
    }

    void ContractedPlayer::SendOnLoan(const std::string& otherClub, const std::string& endDate)
    {
        contract_details_.SetOnLoan(otherClub + " - " + endDate);
        std::cout << "[INFO] " << GetName() << " sent on loan to " << otherClub << " until " << endDate << std::endl;
    }

    void ContractedPlayer::ShowInfo() const
    {
        FieldPlayer::ShowInfo();
        std::cout << "--- CONTRACT DETAILS---" << std::endl;
        contract_details_.ShowDetails();
        if (listedForTransfer_){
            std::cout << "TRANSFER STATUS: Listed for Transfer | Fee: " << std::fixed << std::setprecision(0) << transferFee_ << std::endl;
        }
    }

    double ContractedPlayer::CalculateValue() const
    {
        double performanceFactor = CalculatePerformanceRating() / 10;
        double baseValue = GetMarketValue();

        double contractMultiplier = contract_details_.GetSalary() * 3.0;

        return baseValue * (1.0 + performanceFactor) + contractMultiplier;
    }

    void ContractedPlayer::CelebrateBirthday()
    {
        Player::CelebrateBirthday();
        if (GetAge() > 30)
        {
            UpdateMarketValue(-5.0);
        }
    }

    double ContractedPlayer::CalculatePerformanceRating() const
    {
        return FieldPlayer::CalculatePerformanceRating();
    }

    std::string ContractedPlayer::Serialize() const
    {
        std::stringstream ss;

        ss << FieldPlayer::Serialize() << "," << contract_details_.GetClubName() << "," << contract_details_.GetSalary() << "," << contract_details_.GetContractUntil() << "," << listedForTransfer_ << "," << transferFee_ << "," << transferConditions_;
        return ss.str();
    }

    void ContractedPlayer::Deserialize(const std::string& data)
    {
        FieldPlayer::Deserialize(data);
        std::cout << "[WARNING] ContractedPlayer::Deserialize requires full parsing logic." << std::endl;
    }




}
