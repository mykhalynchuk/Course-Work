#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Player.h"
#include "FreeAgent.h"
#include "ContractedPlayer.h"
#include "IFileHandler.h"
#include "Utils.h"

namespace FootballManagement
{
    /**
     * @brief Клас-менеджер для управління колекцією об'єктів Player.
     */
    class ClubManager : public IFileHandler
    {
    private:
        std::vector<std::shared_ptr<Player> > players_;
        double transferBudget_;
        std::string clubName_;

        /**
       * @brief Генерує унікальний ID для нового гравця.
       * @return Новий унікальний ID.
       */
        int generateUniqueId() const;

    public:
        /**
       * @brief Конструктор із параметрами.
       * @param name Назва клубу.
       * @param budget Початковий бюджет.
       */
        explicit ClubManager(const std::string& name = "Default Club",
                    double budget = 10000000.0);

        /** @brief Віртуальний деструктор. */
        ~ClubManager() noexcept override = default;

        double GetTransferBudget() const;
        void SetTransferBudget(double budget);
        std::string GetClubName() const;

        /**
         * @brief Додає нового гравця до колекції та присвоює ID.
         * @param p Вказівник на об'єкт Player.
         */
        void AddPlayer(std::shared_ptr<Player> p);

        /**
         * @brief Виводить повний список усіх гравців у консоль.
         */
        void ViewAllPlayers() const;

        /**
         * @brief Видаляє гравця за його ID.
         * @param playerId ID гравця для видалення.
         */
        void RemovePlayers(int playerId);

        /**
         * @brief Сортує гравців за показником ефективності.
         */
        void SortByPerformanceRating();

        /**
         * @brief Шукає гравців за частиною імені.
         * @param nameQuery Частина імені для пошуку.
         * @return std::vector<std::shared_ptr<Player>> Знайдені гравці.
         */
        std::vector<std::shared_ptr<Player> > SearchByName(
            const std::string& nameQuery) const;

        /**
         * @brief Фільтрує гравців за статусом.
         * @param status Статус для фільтрації.
         * @return std::vector<std::shared_ptr<Player>> Відфільтровані гравці.
         */
        std::vector<std::shared_ptr<Player> > FilterByStatus(
            const std::string& status) const;

        /**
         * @brief Реалізує логіку підписання вільного агента та перетворює його на ContractedPlayer.
         * @param player Вільний агент для підписання.
         * @param salaryOffer Запропонована зарплата.
         * @param contractUntil Термін дії контракту.
         * @return bool True, якщо підписання успішне.
         */
        bool SignFreeAgent(std::shared_ptr<FreeAgent> player,
                           double salaryOffer,
                           const std::string& contractUntil);

        std::string Serialize() const override;
        void Deserialize(const std::string& data) override;

        /**
         * @brief Спеціальний метод для завантаження даних із вектора рядків, отриманих з FileManager.
         * @param lines Вектор рядків, прочитаних із файлу.
         */
        void DeserializeAllPlaters(const std::vector<std::string>& lines);
    };
}
