#pragma once

#include <string>

namespace FootballManagement
{
    /**
     * @brief Клас, що інкапсулює всі деталі контракту гравця.
     * * Використовується для композицій в класах, щ керують гравцями.
     */
    class ContractDetails
    {
    private:
        std::string clubName_;
        double salary_;
        std::string contractUntil_;
        bool isLoaned_;
        std::string loanEndDate_;

    public:
        /**
         * @brief Конструктор за замовчуванням.
         */
        ContractDetails();

        /**
         * @brief Конструктор з параметрами для ініціалізації контракту.
         */
        ContractDetails(const std::string& clubName, double salary,
                        std::string contractUntil);

        /**
         * Копіювальний конструктор.
         */
        ContractDetails(const ContractDetails& other);

        /**
         * Переміщувальний конструктор.
         */
        ContractDetails(ContractDetails&& other) noexcept;

        /**
         * @brief Оператор копіювального присвоєння.
         */
        ContractDetails& operator=(const ContractDetails& other);

        /**
         * @brief Оператор переміщувального присвоєння.
         */
        ContractDetails& operator=(ContractDetails&& other) noexcept;

        virtual ~ContractDetails() = default;

        std::string GetClubName() const;
        double GetSalary() const;
        std::string GetContractUntil() const;
        bool IsPlayerOnLoan() const;

        void SetClubName(const std::string& clubName);
        void SetContractUntil(const std::string& contractUntil);

        /**
         * @brief Встановлює статус гравця як орендованого.
         * @param loanEndDate Дата закінчення оренди.
         */
        void SetOnLoan(const std::string& loanEndDate);

        /**
         * @brief Повертає гравця з оренди.
         */
        void ReturnFromLoan();

        /**
         * @brief Перевіряє, чи залишилося менше 6 місяців до закінчення контракту.
         * @return bool True, якщо контракт скоро закінчиться.
         */
        bool IsExpiringSoon() const;

        /**
         * @brief Збільшує або зменшує зарплату на заданий відсоток.
         * @param percentage Відсоток зміни (позитивний або негативний).
         */
        void AdjustSalary(double percentage);

        /**
         * @brief Встановлює нову дату закінчення контракту (продовження).
         * @param newDate Нова дата закінчення контракту.
         */
        void ExtendContractDate(const std::string& newDate);

        /**
         * @brief Перевіряє чи дійсний контракт (не закінчився).
         */
        bool IsContractValid() const;


        /**
         * @brief Виводить стислу інформацію про контракт.
         */
        void ShowDetails() const;
    };
}
