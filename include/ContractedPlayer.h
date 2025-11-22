#pragma once

#include "FieldPlayer.h"
#include "ContractDetails.h"
#include <string>

namespace FootballManagement
{
    /**
    * @brief Клас, що представляє гравця з активним контрактом.
    * Наслідується від FieldPlayer і додає логіку трансферів, оренди та контрактів.
    */
    class ContractedPlayer : public FieldPlayer
    {
    private:
        ContractDetails contract_details_;

        bool listedForTransfer_;
        double transferFee_;
        std::string transferConditions_;

    public:
        /** @brief Конструктор за замовчуванням. */
        ContractedPlayer();
        ContractedPlayer(const std::string& name, int age,
                         const std::string& nationality, std::string& origin,
                         double height, double weight, double marketValue,
                         Position position, double salary,
                         const std::string& contractUntil);

        /**
         * @brief Конструктор із параметрами для ініціалізації контрактного гравця.
         * @param name Ім’я гравця.
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

        /** @brief Копіювальний конструктор. */
        ContractedPlayer(const ContractedPlayer& other);

        /** @brief Переміщувальний конструктор. */
        ContractedPlayer(ContractedPlayer&& other) noexcept;

        /** @brief Оператор копіювального присвоєння. */
        ContractedPlayer& operator=(const ContractedPlayer& other);

        /** @brief Оператор переміщувального присвоєння. */
        ContractedPlayer& operator=(ContractedPlayer&& other) noexcept;

        /** @brief Віртуальний деструктор. */
        ~ContractedPlayer() noexcept override;

        [[nodiscard]] bool IsListedForTransfer() const;
        [[nodiscard]] double GetTransferFee() const;
        [[nodiscard]] ContractDetails GetContractDetails() const;

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
        void SendOnLoan(const std::string& otherClub,
                        const std::string& endDate);


        [[nodiscard]] double CalculateValue() const override;
        [[nodiscard]] std::string GetStatus() const override;
        void ShowInfo() const override;
        void CelebrateBirthday() override = 0;
        [[nodiscard]] double CalculatePerformanceRating() const override = 0;
        [[nodiscard]] std::string Serialize() const override = 0;
        void Deserialize(const std::string& data) override = 0;
    };
}
