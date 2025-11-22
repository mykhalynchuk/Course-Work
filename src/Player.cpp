#include "../include/Player.h"
#include<iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace FootballManagement
{
    Player::Player() : playerId_(0), name_("Невідомо"), age_(0),
                       nationality_("Невідомо"), origin_("Невідомо"),
                       height_(0.0),
                       weight_(0.0), marketValue_(0.0), injured_(false)
    {
    }

    Player::Player(const std::string& name, int age,
                   const std::string& nationality, const std::string& origin,
                   double height,
                   double weight,
                   double marketValue) : playerId_(0), name_(name),
                                         age_(age),
                                         nationality_(nationality),
                                         origin_(origin),
                                         height_(height),
                                         weight_(weight),
                                         marketValue_(marketValue),
                                         injured_(false)
    {
        if (age <= 0) throw std::invalid_argument("Вік повинен бути додатним.");
        if (height <= 0)
            throw std::invalid_argument(
                "Зріст повинен бути додатним.");
        if (weight <= 0)
            throw std::invalid_argument(
                "Вага повинна бути додатною.");
    }

    Player::Player(const Player& other) : playerId_(other.playerId_),
                                          name_(other.name_),
                                          age_(other.age_),
                                          nationality_(other.nationality_),
                                          origin_(other.origin_),
                                          height_(other.height_),
                                          weight_(other.weight_),
                                          marketValue_(other.marketValue_),
                                          injured_(other.injured_),
                                          injuryHistory_(other.injuryHistory_)
    {
    }

    Player::Player(Player&& other) noexcept : playerId_(other.playerId_),
                                              name_(std::move(other.name_)),
                                              age_(other.age_),
                                              nationality_(
                                                  std::move(
                                                      other.nationality_)),
                                              origin_(std::move(other.origin_)),
                                              height_(other.height_),
                                              weight_(other.weight_),
                                              marketValue_(other.marketValue_),
                                              injured_(false),
                                              injuryHistory_(std::move(
                                                  other.injuryHistory_))
    {
        other.playerId_ = 0;
    }

    Player& Player::operator=(const Player& other)
    {
        if (this != &other)
        {
            playerId_ = other.playerId_;
            name_ = other.name_;
            age_ = other.age_;
            nationality_ = other.nationality_;
            origin_ = other.origin_;
            height_ = other.height_;
            weight_ = other.weight_;
            marketValue_ = other.marketValue_;
            injured_ = other.injured_;
            injuryHistory_ = other.injuryHistory_;
        }
        return *this;
    }

    Player& Player::operator=(Player&& other) noexcept
    {
        if (this != &other)
        {
            playerId_ = other.playerId_;
            name_ = std::move(other.name_);
            age_ = other.age_;
            nationality_ = std::move(other.nationality_);
            origin_ = std::move(other.origin_);
            height_ = other.height_;
            weight_ = other.weight_;
            marketValue_ = other.marketValue_;
            injured_ = other.injured_;
            injuryHistory_ = std::move(other.injuryHistory_);
        }
        return *this;
    }

    Player::~Player() noexcept
    {
        std::cout << "[DEBUG] Гравець \"" << name_
            << "\" (ID: " << playerId_ << ") видалений.\n";
    }


    int Player::GetPlayerId() const { return playerId_; }
    std::string Player::GetName() const { return name_; }
    int Player::GetAge() const { return age_; }
    std::string Player::GetNationality() const { return nationality_; }
    std::string Player::GetOrigin() const { return origin_; }
    double Player::GetHeight() const { return height_; }
    double Player::GetWeight() const { return weight_; }
    double Player::GetMarketValue() const { return marketValue_; }
    bool Player::IsInjured() const { return injured_; }

    const std::vector<Injury>& Player::GetInjuryHistory() const
    {
        return injuryHistory_;
    }

    void Player::SetPlayerId(int playerId)
    {
        if (playerId <= 0)
            throw std::invalid_argument(
                "Ідентифікатор гравця повинен бути позитивним.");
        playerId_ = playerId;
    }

    void Player::SetName(const std::string& name)
    {
        if (name.empty())
            throw std::invalid_argument(
                "Ім'я гравця не може бути порожнім.");
        name_ = name;
    }


    void Player::SetNationality(const std::string& nationality)
    {
        if (nationality.empty())
            throw std::invalid_argument(
                "Національність не може бути порожньою.");
        nationality_ = nationality;
    }


    void Player::SetOrigin(const std::string& origin)
    {
        if (origin.empty())
        {
            origin_ = "Невідомий";
            return;
        }
        origin_ = origin;
    }

    void Player::SetHeight(double height)
    {
        if (height <= 0.0)
            throw std::invalid_argument(
                "Висота повинна бути позитивною.");
        height_ = height;
    }


    void Player::SetWeight(double weight)
    {
        if (weight <= 0.0)
            throw std::invalid_argument(
                "Вага повинна бути позитивною.");
        weight_ = weight;
    };


    void Player::SetMarketValue(double marketValue)
    {
        if (marketValue <= 0.0)
            throw std::invalid_argument(
                "Ринкова вартість не може бути негативною.");
        marketValue_ = marketValue;
    }


    void Player::ReportInjury(const std::string& type, int recoveryDays)
    {
        if (type.empty())
            throw std::invalid_argument(
                "Тип травми не може бути порожнім.");

        if (recoveryDays <= 0)
            throw std::invalid_argument(
                "Дні відновлення повинні бути більше нуля.");

        injured_ = true;

        Injury newInjury;
        newInjury.injuryType = type;
        newInjury.recoveryDays = recoveryDays;
        newInjury.dateOccurred = "Сьогодні.";

        injuryHistory_.push_back(std::move(newInjury));

        std::cout << "Гравець \"" << name_ << "\" отримав травму: "
            << type << ". Орієнтовне відновлення: "
            << recoveryDays << " днів.\n";
    }

    void Player::ReturnToFitness()
    {
        injured_ = false;
        std::cout << "Гравець \"" << name_ << "\" відновився після травми.\n";
    }

    void Player::UpdateMarketValue(double percentageChange)
    {
        double factor = 1.0 + (percentageChange / 100.0);
        marketValue_ *= factor;

        if (marketValue_ < 0.0) marketValue_ = 0.0;
    }

    std::string Player::Serialize() const
    {
        std::stringstream ss;
        ss << "\"id\":" << playerId_ << ","
            << "\"name\":\"" << name_ << "\","
            << "\"age\":" << age_ << ","
            << "\"nationality\":\"" << nationality_ << "\","
            << "\"origin\":\"" << origin_ << "\","
            << "\"height\":" << height_ << ","
            << "\"weight\":" << weight_ << ","
            << "\"value\":" << marketValue_ << ","
            << "\"injured\":" << (injured_ ? "true" : "false");
        return ss.str();
    }

    void Player::DeserializeBase(const std::string& json)
    {
        std::regex r("\"(.*?)\":\"?(.*?)\"?(,|})");
        auto begin = std::sregex_iterator(json.begin(), json.end(), r);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it)
        {
            std::string key = (*it)[1];
            std::string value = (*it)[2];

            if (key == "name") name_ = value;
            else if (key == "nationality") nationality_ = value;
            else if (key == "origin") origin_ = value;
            else if (key == "age") age_ = std::stoi(value);
            else if (key == "height") height_ = std::stod(value);
            else if (key == "weight") weight_ = std::stod(value);
            else if (key == "value") marketValue_ = std::stod(value);
            else if (key == "id") playerId_ = std::stoi(value);
            else if (key == "injured") injured_ = (value == "true");
        }
    }
}
