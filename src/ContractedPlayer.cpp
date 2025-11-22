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
        contract_details_(name, salary, contractUntil),
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

    ContractedPlayer::~ContractedPlayer() noexcept
    {
        std::cout << "[DEBUG] Контрактний гравець \"" << GetName()
            << "\" видалений." << std::endl;
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
            throw std::invalid_argument(
                "Трансферна сума має бути додатною.");

        listedForTransfer_ = true;
        transferFee_ = fee;
        transferConditions_ = conditions;

        std::cout << "[INFO] " << GetName() <<
            " виставлений на трансфер. Мінімальна сума: "
            << fee << " €." << std::endl;
    }

    void ContractedPlayer::RemoveFromTransferList()
    {
        listedForTransfer_ = false;
        transferFee_ = 0.0;
        transferConditions_.clear();

        std::cout << "[INFO] " << GetName() << " знятий із трансферного списку."
            << std::endl;
    }

    void ContractedPlayer::TransferToClub(const std::string& newClub,
                                          double fee)
    {
        if (!listedForTransfer_)
        {
            std::cout << "[FAIL] Гравець не виставлений на трансфер." <<
                std::endl;
            return;
        }

        if (fee < transferFee_)
        {
            std::cout << "[FAIL] Сума " << fee <<
                " € менша за мінімальну ціну (" << transferFee_ << " €)." <<
                std::endl;
            return;
        }

        contract_details_.SetClubName(newClub);
        listedForTransfer_ = false;

        std::cout << "[SUCCESS] " << GetName() << " проданий у клуб \"" <<
            newClub
            << "\" за " << fee << " €." << std::endl;
    }

    void ContractedPlayer::ExtendedContract(const std::string& newDate,
                                          double newSalary)
    {
        if (newSalary <= 0.0)
            throw std::invalid_argument(
                "Зарплата повинна бути додатною.");

        double oldSalary = contract_details_.GetSalary();
        contract_details_.ExtendContractDate(newDate);

        double percentageChange = ((newSalary - oldSalary) / oldSalary) * 100.0;
        contract_details_.AdjustSalary(percentageChange);

        std::cout << "[INFO] Контракт " << GetName() << " продовжено до " <<
            newDate
            << ". Нова зарплата: " << newSalary << " €." << std::endl;
    }

    void ContractedPlayer::TerminateContract(const std::string& reason)
    {
        contract_details_.SetClubName("Без клубу (контракт розірвано)");
        std::cout << "[WARNING] Контракт " << GetName() <<
            " розірвано. Причина: " << reason << std::endl;
    }

    void ContractedPlayer::SendOnLoan(const std::string& otherClub,
                                      const std::string& endDate)
    {
        contract_details_.SetOnLoan(endDate);
        std::cout << "[INFO] " << GetName() << " відправлений в оренду до " <<
            otherClub
            << " до " << endDate << "." << std::endl;
    }

    void ContractedPlayer::ShowInfo() const
    {
        std::cout << "\n=== КОНТРАКТНИЙ ГРАВЕЦЬ ===" << std::endl;
        FieldPlayer::ShowInfo();
        contract_details_.ShowDetails();

        if (listedForTransfer_)
        {
            std::cout << "Статус трансферу: У списку | Мін. сума: "
                << std::fixed << std::setprecision(2)
                << transferFee_ << " €" << std::endl;
        }
        else
        {
            std::cout << "Статус трансферу: Не виставлений" << std::endl;
        }
    }

    double ContractedPlayer::CalculateValue() const
    {
        double baseValue = GetMarketValue();
        double performanceBonus = CalculatePerformanceRating() * 50000.0;
        double salaryImpact = contract_details_.GetSalary() / 10000.0;

        return baseValue + performanceBonus + salaryImpact;
    }

    std::string ContractedPlayer::GetStatus() const
    {
        if (IsInjured())
            return "Травмований гравець";
        if (contract_details_.IsPlayerOnLoan())
            return "В оренді";
        return "Активний гравець";
    }

    void ContractedPlayer::CelebrateBirthday()
    {
        int newAge = GetAge() + 1;
        SetAge(newAge);
        std::cout << "[INFO] З днем народження, " << GetName()
            << "! Тепер вам " << newAge << " років." << std::endl;

        if (newAge > 30)
            UpdateMarketValue(-3.0);
    }

    double ContractedPlayer::CalculatePerformanceRating() const
    {
        return 0.0;
    }

    std::string ContractedPlayer::Serialize() const
    {
        std::stringstream ss;
        ss << FieldPlayer::Serialize()
            << "," << contract_details_.GetClubName()
            << "," << contract_details_.GetSalary()
            << "," << contract_details_.GetContractUntil()
            << "," << listedForTransfer_
            << "," << transferFee_
            << "," << transferConditions_;
        return ss.str();
    }

    void ContractedPlayer::Deserialize(const std::string& data)
    {
        FieldPlayer::Deserialize(data);
        std::cout <<
            "[WARNING] Логіка десеріалізації ContractedPlayer ще не реалізована."
            << std::endl;
    }
}
