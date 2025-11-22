#pragma once

#include "FieldPlayer.h"
#include <string>


namespace FootballManagement
{
    /**
     * @brief Клас, що представляє вільного агента - гравця без контракту.
     */
    class FreeAgent : public FieldPlayer
    {
    private:
        double expectedSalary_;
        std::string lastClub_;
        int monthsWithoutClub_;
        bool availableForNegotiation_;

    public:
        /** @brief Конструктор за замовчуванням. */
        FreeAgent();

        /**
          * @brief Конструктор із параметрами.
          * @param name Ім’я гравця.
          * @param age Вік.
          * @param nationality Громадянство.
          * @param origin Походження.
          * @param height Зріст.
          * @param weight Вага.
          * @param marketValue Ринкова ціна.
          * @param position Позиція на полі.
          * @param expectedSalary Очікувана зарплата.
          * @param lastClub Останній клуб.
          */
        FreeAgent(const std::string& name, int age,
                  const std::string& nationality,
                  const std::string& origin, double height, double weight,
                  double marketValue, Position position, double expectedSalary,
                  const std::string& lastClub);

        /** @brief Копіювальний конструктор. */
        FreeAgent(const FreeAgent& other);

        /** @brief Переміщувальний конструктор. */
        FreeAgent(FreeAgent&& other) noexcept;

        /** @brief Оператор копіювального присвоєння. */
        FreeAgent& operator=(const FreeAgent& other);

        /** @brief Оператор переміщувального присвоєння. */
        FreeAgent& operator=(FreeAgent&& other) noexcept;

        /** @brief Віртуальний деструктор. */
        ~FreeAgent() override;

        double GetExpectedSalary() const;
        std::string GetLastClub() const;
        bool IsAvailableForNegotiation() const;
        int GetMonthWithoutClub() const;

        void SetLastClub(const std::string& lastClub);
        void SetMonthWithoutClub(int months);

        /**
         * @brief Гравець оцінює пропозицію клубу та приймає її, якщо вона відповідає очікуванням.
         * @param offer Пропозиція зарплати від клубу.
         * @return True^ Результат переговорів.
         */
        bool NegotiateOffer(double offer);

        /**
         * @brief Збільшує очікувану зарплату.
         * @param percentage Відсоток, на який збільшуються очікування.
         */
        void IncreaseExpectations(double percentage);

        /**
         * @brief Знижує очікувану зарплату.
         * @param percentage Відсоток, на який знижуються очікування.
         */
        void DecreaseExpectations(double percentage);

        /**
         * @brief Встановлює статус доступності для переговорів.
         * @param isAvailable Новий статус доступності.
         */
        void SetAvailability(bool isAvailable);

        /**
         * @brief Підписання контракту.
         * @param club Назва клубу.
         */
        void AcceptContract(const std::string& club);

        /**
         * @brief Перевіряє, чи є гравець вигідним для підписання (базуючись на очікуванях та віці).
         * @return bool True, якщо вигідний.
         */
        bool IsBargain() const;

        void ShowInfo() const override;
        double CalculateValue() const override;
        std::string GetStatus() const override;
        void CelebrateBirthday() override;
        double CalculatePerformanceRating() const override;

        std::string Serialize() const override;
        void Deserialize(const std::string& data) override;
    };
}
