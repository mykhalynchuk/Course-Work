#pragma once

#include "Player.h"
#include <string>

namespace FootballManagement
{
    class Goalkeeper : public Player
    {
    private:
        int matchesPlayed_;
        int cleanSheets_;
        int savesTotal_;
        int goalsConceded_;
        int penaltiesSaved_;

    public:
        Goalkeeper();

        Goalkeeper(const std::string& name, int age,
                    const std::string& nationality, const std::string& origin,
                    double height, double weight, double marketValue);

        Goalkeeper(const Goalkeeper& other);
        Goalkeeper(Goalkeeper&& other) noexcept;
        Goalkeeper& operator=(const Goalkeeper& other);
        Goalkeeper& operator=(Goalkeeper&& other) noexcept;

        virtual ~Goalkeeper();

        int GetMatchesPlayed() const;
        int GetCleanSheets() const;
        int GetSavesTotal() const;
        int GetGoalsConceded() const;
        int GetPenaltiesSaved() const;

        /**
         * @brief Оновлює статистику воротаря після матчу.
         * @param goalsAgainst Кількість пропущених голів.
         * @param saves Кількість зроблених сейвів.
         */
        void UpdateMatchStats(int goalsAgainst, int saves);

        /**
         * @brief Реєструє сухий матч.
         */
        void RegisterCleanSheet();

        /**
         * @brief Реєструє відбитий пенальті.
         */
        void RegisterPenaltySave();

        /**
         * @brief Розраховує відсоток сейвів.
         * @return double відсоток відбитих ударів.
         */
        double CalculateSavePercentage() const;

        /**
         * @brief Перевіряє, чи є воротар "віковим" (старше за 35).
         * @return bool True, якщо воротар старший за 35 років.
         */
        bool IsVeteran() const;

        /**
         * @brief Скидає сезонну статистику.
         */
        void ResetSeasonStats();

        void ShowInfo() const override;
        double CalculateValue() const override;
        std::string GetStatus() const override;
        void CelebrateBirthday() override;

        /**
         * @brief Розрахування показник ефективності на основі унікадьних метрик воротаря.
         * @return double Рейтинг ефективності воротаря.
         */
        double CalculatePerformanceRating() const override;

        std::string Serialize() const override;
        void Deserialize(const std::string& data) override;

    };
}
