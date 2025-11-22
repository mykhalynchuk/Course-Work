#pragma once

#include "Player.h"
#include <string>

namespace FootballManagement
{
    /**
    * @brief Клас, що представляє воротаря футбольної команди.
    * Містить статистику та методи, специфічні для воротарської позиції.
    */
    class Goalkeeper : public Player
    {
    private:
        int matchesPlayed_;
        int cleanSheets_;
        int savesTotal_;
        int goalsConceded_;
        int penaltiesSaved_;

    public:
        /** @brief Конструктор за замовчуванням. */
        Goalkeeper();

        /**
       * @brief Конструктор з параметрами.
       * @param name Ім'я гравця.
       * @param age Вік гравця.
       * @param nationality Громадянство.
       * @param origin Походження.
       * @param height Зріст.
       * @param weight Вага.
       * @param marketValue Ринкова вартість.
       */
        Goalkeeper(const std::string& name, int age,
                   const std::string& nationality, const std::string& origin,
                   double height, double weight, double marketValue);

        /** @brief Копіювальний конструктор. */
        Goalkeeper(const Goalkeeper& other);

        /** @brief Переміщувальний конструктор. */
        Goalkeeper(Goalkeeper&& other) noexcept;

        /** @brief Оператор копіювального присвоєння. */
        Goalkeeper& operator=(const Goalkeeper& other);

        /** @brief Оператор переміщувального присвоєння. */
        Goalkeeper& operator=(Goalkeeper&& other) noexcept;

        /** @brief Віртуальний деструктор. */
        virtual ~Goalkeeper() noexcept override;

        int GetMatchesPlayed() const;
        int GetCleanSheets() const;
        static void GetSavesTotal();
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

        /** @brief Виводить інформацію про воротаря. */
        void ShowInfo() const override;

        /** @brief Розраховує ринкову вартість гравця. */
        double CalculateValue() const override;

        /** @brief Повертає статус гравця (Active / Injured). */
        std::string GetStatus() const override;

        /** @brief Збільшує вік на 1 рік і виводить повідомлення. */
        void CelebrateBirthday() override;

        /** @brief Розраховує рейтинг ефективності воротаря. */
        double CalculatePerformanceRating() const override;

        /** @brief Серіалізує об’єкт у текстовий формат. */
        std::string Serialize() const override;

        /** @brief Десеріалізує об’єкт із рядка. */
        void Deserialize(const std::string& data) override;
    };
}
