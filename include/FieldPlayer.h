#pragma once

#include "Player.h"
#include <string>

namespace FootballManagement
{
    /**
     * @brief Абстрактний клас-нащадок для всіх польових гравців (Defender, Midfielder, Forward).
     */
    class FieldPlayer : public Player
    {
    private:
        int totalGames_;
        int totalGoals_;
        int totalAssists_;
        int totalShots_;
        int totalTackles_;
        int keyPasses_;
        Position position_;

    public:
        /**
         * @brief Конструктор за замовчуванням.
         */
        FieldPlayer();

        /**
    * @brief Конструктор з параметрами.
    * @param name Ім'я гравця.
    * @param age Вік гравця.
    * @param nationality Громадянство.
    * @param origin Походження.
    * @param height Зріст.
    * @param weight Вага.
    * @param marketValue Ринкова вартість.
    * @param position Позиція на полі.
    */
        FieldPlayer(const std::string& name, int age,
                    const std::string& nationality, const std::string& origin,
                    double height, double weight,double marketValue, Position position);

        /** @brief Копіювальний конструктор. */
        FieldPlayer(const FieldPlayer& other);

        /** @brief Переміщувальний конструктор. */
        FieldPlayer(FieldPlayer&& other) noexcept;

        /** @brief Копіювальний оператор присвоєння. */
        FieldPlayer& operator=(const FieldPlayer& other);

        /** @brief Переміщувальний оператор присвоєння. */
        FieldPlayer& operator=(FieldPlayer&& other) noexcept;

        /** @brief Віртуальний деструктор. */
        ~FieldPlayer() override;

        [[nodiscard]] int GetTotalGames() const;
        [[nodiscard]] int GetKeyPasses() const;
        [[nodiscard]] int GetTotalGoals() const;
        [[nodiscard]] int GetTotalAssists() const;
        [[nodiscard]] int GetTotalShots() const;
        [[nodiscard]] int GetTotalTackles() const;
        [[nodiscard]] Position GetPosition() const;

        void SetPosition(Position position);

        /**
         * @brief Оновлює актуальну статистику.
         * @param goals Кількість голів.
         * @param assists Кількість асистів.
         * @param shots Кількість ударів.
         */
        void UpdateAttackingStats(int goals, int assists, int shots);

        /**
         * @brief Оновлює захисну статистику.
         * @param tackles Кількість успішних відборів.
         */
        void UpdateDefensiveStats(int tackles);

        /**
         * @brief Реєструє успішний ключавий пас.
         */
        void RegisterKeyPass();

        /**
         * @brief Розраховує відсоток реалізації ударів.
         * @return double Коефіцієнт конверсії.
         */
        [[nodiscard]] double CalculateConversionRate() const;

        /**
         * @brief Реєструє зіграний матч.
         */
        void RegisterMatchPlayed();

        /**
         * @brief Скидає сезонну статистику до нуля.
         */
        void ResetSeasonStats();

        void ShowInfo() const override;
        void CelebrateBirthday() override;

        [[nodiscard]] double CalculateValue() const override = 0;
        [[nodiscard]] double CalculatePerformanceRating() const override = 0;
        [[nodiscard]] std::string GetStatus() const override = 0;

        [[nodiscard]] std::string Serialize() const override = 0;
        void Deserialize(const std::string& data) override = 0;
    };
}
