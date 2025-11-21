#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "Utils.h"
#include "IFileHandler.h"

namespace FootballManagement
{
    /**
     * @brief Абстрактний базовий клас для всіх футболістів у системі.
    * Містить базові антропометричні та біографічні дані,
     * а також підтримує серіалізацію/десеріалізацію.
     */
    class Player : public IFileHandler
    {
    private:
        int playerId_;
        std::string name_;
        int age_;
        std::string nationality_;
        std::string origin_;
        double height_;
        double weight_;
        double marketValue_;
        bool injured_;
        std::vector<Injury> injuryHistory_;

    public:
        /**
         * @brief Конструктор за замовчуванням.
         */
        Player();

        /**
         * @brief Конструктор із параметрами.
         *
         * @param name П.І.Б. гравця.
         * @param age Вік.
         * @param nationality Громадянство.
         * @param origin Походження.
         * @param height Зріст у метрах.
         * @param weight Вага у кг.
         * @param value Початкова ринкова вартість.
         */
        Player(const std::string& name, int age, const std::string& nationality,
               const std::string& origin, double height, double weight,
               double value);

        Player(const Player& other);
        Player(Player&& other) noexcept;

        Player& operator=(const Player& other);
        Player& operator=(Player&& other) noexcept;

        /**
         * @brief Віртуальний деструктор.
         */
        virtual ~Player();

        int GetPlayerId() const;
        std::string GetName() const;
        int GetAge() const;
        std::string GetNationality() const;
        std::string GetOrigin() const;
        double GetHeight() const;
        double GetWeight() const;
        double GetMarketValue() const;
        bool IsInjured() const;
        const std::vector<Injury>& GetInjuryHistory() const;

        void SetPlayerId(int playerId);
        void SetName(const std::string& name);
        void SetNationality(const std::string& nationality);
        void SetOrigin(const std::string& origin);
        void SetHeight(double height);
        void SetWeight(double weight);
        void SetMarketValue(double value);

        /**
         * @brief Відображає інформацію про гравця.
         */
        virtual void ShowInfo() const = 0;

        /**
        * @brief Обчислює поточну ринкову вартість на основі статистики.
         * @return Розрахункова вартість.
         */
        virtual double CalculateValue() const = 0;

        /**
        * @brief @brief Обчислює рейтинг продуктивності гравця.
         * @return Рейтинг продуктивності.
         */
        virtual double CalculatePerformanceRating() const = 0;

        /**
         * Повертає поточний статус гравця (на контракті, вільний агент, в оренді).
         * @return Статус у вигляді рядка.
         */
        virtual std::string GetStatus() const = 0;

        /**
         * @brief Повідомити про травму гравця.
         *
         * Додається запис до injuryHistory_ і статус injured_ ставиться у true.
         *
         * @param type Тип травми.
         * @param recoveryDays Очікувані дні для відновлення (повинні бути > 0).
         */
        void ReportInjury(const std::string& type, int recoveryDays);

        /**
         * @brief Повернути гравця до форми.
         */
        void ReturnToFitness();

        /**
         * @brief Оновити ринкову вартість на певний відсоток (може бути негативним).
         *
         * @param percentageChange Відсоток зміни (наприклад, 10.0 => +10%).
         */
        void UpdateMarketValue(double percentageChange);

        /**
         * @brief Відзначити день народження (логіка збільшення віку у реалізації нащадків).
         */
        virtual void CelebrateBirthday() = 0;

        /**
         * @brief Відзначити день народження (логіка збільшення віку у реалізації нащадків).
         */
        std::string Serialize() const override = 0;

        /**
         * @brief Десеріалізує об'єкт з рядка.
         *
         * Нащадки повинні викликати DeserializeBase(data) для парсингу базових полів.
         *
         * @param data Вхідний рядок (JSON або інший формат).
         */
        virtual void Deserialize(const std::string& data) override = 0;

    protected:
        /**
         * @brief Серіалізує базові поля в JSON-рядок (частина серіалізації для нащадків).
         * @return JSON-подібний рядок із базовими полями (без зовнішніх фігурних дужок).
         */
        std::string SerializeBase() const;

        /**
         * @brief Десеріалізує базові поля з JSON-рядка.
         *
         * Простий, стійкий до помилок парсер. Рекомендується в майбутньому замінити на
         * перевірену JSON-бібліотеку.
         *
         * @param data JSON-рядок або частина; функція міняє поля базового класу.
         */
        void DeserializeBase(const std::string& data);
    };
}
