#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "Utils.h"
#include "IFileHandler.h"

/**
 * @brief Простір імен системи управління футбольною командою.
 */
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

        /** @brief Копіювальний конструктор. */
        Player(const Player& other);

        /** @brief Переміщувальний конструктор. */
        Player(Player&& other) noexcept;

        /** @brief Оператор копіювального присвоєння. */
        Player& operator=(const Player& other);

        /** @brief Оператор переміщувального присвоєння. */
        Player& operator=(Player&& other) noexcept;

        /** @brief Віртуальний деструктор. */
        virtual ~Player();

        [[nodiscard]] int GetPlayerId() const;
        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] int GetAge() const;
        [[nodiscard]] std::string GetNationality() const;
        [[nodiscard]] std::string GetOrigin() const;
       [[nodiscard]] double GetHeight() const;
        [[nodiscard]] double GetWeight() const;
        [[nodiscard]] double GetMarketValue() const;
       [[nodiscard]] bool IsInjured() const;
        [[nodiscard]] const std::vector<Injury>& GetInjuryHistory() const;

        void SetPlayerId(int playerId);
        void SetName(const std::string& name);
        void SetNationality(const std::string& nationality);
        void SetOrigin(const std::string& origin);
        void SetHeight(double height);
        void SetWeight(double weight);
        void SetMarketValue(double value);

        /** @brief Абстрактний метод — повна інформація про гравця. */
        virtual void ShowInfo() const = 0;

        /** @brief Абстрактний метод — розрахунок ринкової вартості. */
        [[nodiscard]] virtual double CalculateValue() const = 0;

        /** @brief Абстрактний метод — ефективність гравця. */
       [[nodiscard]] virtual double CalculatePerformanceRating() const = 0;

        /** @brief Абстрактний метод — статус (контракт / вільний агент). */
        virtual std::string GetStatus() const = 0;

        /** @brief Абстрактний метод — день народження (збільшити вік). */
        virtual void CelebrateBirthday() = 0;

        /**
         * @brief Повідомити про травму гравця.
         * Додається запис до injuryHistory_ і статус injured_ ставиться у true.
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
         * @param percentageChange Відсоток зміни (наприклад, 10.0 => +10%).
         */
        void UpdateMarketValue(double percentageChange);


        [[nodiscard]] std::string Serialize() const override = 0;
        virtual void Deserialize(const std::string& data) override = 0;

    protected:
        /** @brief Серіалізація спільних полів для JSON. */
       [[nodiscard]] std::string SerializeBase() const;

        /** @brief Десеріалізація спільних полів. */
        void DeserializeBase(const std::string& json);
    };
}
