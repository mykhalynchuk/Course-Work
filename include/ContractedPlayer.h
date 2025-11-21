#pragma once

#include "FieldPlayer.h"
#include "ContractDetails.h"
#include <string>

namespace FootballManagement
{
    /**
     * @brief Клас, що представляє гравця, який має діючий контракт із клубом.
     */
    class ContractedPlayer : public FieldPlayer
    {
    private:
        ContractDetails contract_details_;

        bool listedForTransfer_;
        double transferFee_;
        std::string transferConditions_;

    public:
        ContractedPlayer();

        /**
         * @brief Конструктор із параметрами для ініціалізації контрактного гравця.
         * @param name П.І.Б.
         * @param age Вік.
         * @param nationality Громадянство.
         * @param origin Походження.
         * @param height Зріст.
         * @param weight Вага.
         * @param marketValue Ринкова ціна.
         * @param position Ігрова позиція.
         * @param salary Зарплата.
         * @param contractUntil Дата закінчення контракту.
         */
        ContractedPlayer(const std::string& name, int age,
                         const std::string& nationality,
                         const std::string& origin,
                         double height, double weight, double marketValue,
                         Position position, double salary,
                         const std::string& contractUntil);

        ContractedPlayer(const ContractedPlayer& other);
        ContractedPlayer(ContractedPlayer&& other) noexcept;
        ContractedPlayer& operator=(const ContractedPlayer& other);
        ContractedPlayer& operator=(ContractedPlayer&& other) noexcept;

        ~ContractedPlayer() override;

       bool IsListedForTransfer() const;
        double GetTransferFee() const;
        ContractDetails GetContractDetails() const;

        /**
         * @brief Виставляє гравця на трансфер з вказаною ціною та умовами.
         * @param fee Мінімальна ціна продажу.
         * @param conditions Додаткові умови трансферу.
         */
        void ListForTransfer(double fee, const std::string& conditions);

        /**
         * @brief Знімає гравця з трансферу.
         */
        void RemoveFromTransferList();

        /**
         * @brief Логіка продажу гравця іншому клубу (трансфер).
         * @param newClub Назва нового клубу.
         * @param fee Сума трансферу.
         */
        void TransferToClub(const std::string& newClub, double fee);

        /**
         * @brief Продовжує контракт гравця.
         * @param newDate Нова дата закінчення контракту.
         * @param newSalary Нова річна зарплата, яка встановлюється для гравця.
         */
        void ExtendedContract(const std::string& newDate, double newSalary);

        /**
         * @brief Розірвання контракту.
         * @param reason Причина розірвання.
         */
        void TerminateContract(const std::string& reason);

        /**
         * @brief Надіслати гравця в оренду.
         * @param otherClub Клуб, куди відправляється гравець.
         * @param endDate Дата закінчення оренди.
         */
        void SendOnLoan(const std::string& otherClub, const std::string& endDate);


        double CalculateValue() const override;
        std::string GetStatus() const override;
        void ShowInfo() const override;
        void CelebrateBirthday() override = 0;
        double CalculatePerformanceRating() const override = 0;
        std::string Serialize() const override = 0;
        virtual void Deserialize(const std::string& data) override = 0;

    };
}
