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
        FieldPlayer();

        FieldPlayer(const std::string& name, int age,
                    const std::string& nationality, const std::string& origin,
                    double height, double weight, Position position);

        FieldPlayer(const FieldPlayer& other);
        FieldPlayer(FieldPlayer&& other) noexcept;
        FieldPlayer(const std::string& name, int age, const std::string& string, const std::string& origin,
                    double height, double weight, double market_value, Position position);
        FieldPlayer& operator=(const FieldPlayer& other);
        FieldPlayer& operator=(FieldPlayer&& other) noexcept;

        virtual ~FieldPlayer();

        int GetTotalGames() const;
        int GetKeyPasses() const;
        int GetTotalGoals() const;
        int GetTotalAssists() const;
        int GetTotalShots() const;
        int GetTotalTackles() const;
        Position GetPosition() const;

        void SetPosition(Position position);

        /**
         * @brief Оновлює актуальну статистику.
         * @param goals Кількість голів.
         * @param assists Кількість асистів.
         * @param shots Кількість ударів.
         */
        void UpdateAttackingStats(int goals, int assists, int shots);

        /**
         * @brief Оновлює захисну стататистику.
         * @param tackles Кількість успішних відбборів.
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
        double CalculateConversionRate() const;

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

        virtual double CalculateValue() const override = 0;
        virtual double CalculatePerformanceRating() const override = 0;
        virtual std::string GetStatus() const override = 0;

        virtual std::string Serialize() const override = 0;
        virtual void Deserialize(const std::string& data) override = 0;
    };
}
