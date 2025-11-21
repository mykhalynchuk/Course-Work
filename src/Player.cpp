#include "../include/Player.h"
#include<iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace FootballManagement
{
    Player::Player() : playerId_(0), name_("N/A"), age_(0),
                       nationality_("N/A"), origin_("N/A"), height_(0.0),
                       weight_(0.0), marketValue_(0.0), injured_(false),
                       injuryHistory_()
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
                                         injured_(false), injuryHistory_()
    {
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
                                              injuryHistory_(std::move(
                                                  other.injuryHistory_))
    {
        other.playerId_ = 0;
        other.age_ = 0;
        other.marketValue_ = 0;
        other.injured_ = false;
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

            other.playerId_ = 0;
            other.age_ = 0;
            other.marketValue_ = 0.0;
            other.injured_ = false;
        }
        return *this;
    }

    Player::~Player()
    {
    }


    int Player::GetPlayerId() const { return playerId_; }

    void Player::SetPlayerId(int playerId)
    {
        if (playerId <= 0)
        {
            throw std::invalid_argument(
                "Ідентифікатор гравця повинен бути позитивним.");
        }
        playerId_ = playerId;
    }

    std::string Player::GetName() const { return name_; }

    void Player::SetName(const std::string& name)
    {
        if (name.empty())
        {
            throw std::invalid_argument("Ім'я гравця не може бути порожнім.");
        }
        name_ = name;
    }

    int Player::GetAge() const { return age_; }

    std::string Player::GetNationality() const { return nationality_; }

    void Player::SetNationality(const std::string& nationality)
    {
        if (nationality.empty())
        {
            throw std::invalid_argument(
                "Національність не може бути порожньою.");
        }
        nationality_ = nationality;
    }

    std::string Player::GetOrigin() const { return origin_; }

    void Player::SetOrigin(const std::string& origin)
    {
        if (origin.empty())
        {
            origin_ = "Невідомий";
            return;
        }
        origin_ = origin;
    }

    double Player::GetHeight() const { return height_; }

    void Player::SetHeight(double height)
    {
        if (height <= 0.0)
        {
            throw std::invalid_argument("Висота повинна бути позитивною.");
        }
        height_ = height;
    }

    double Player::GetWeight() const { return weight_; }

    void Player::SetWeight(double weight)
    {
        if (weight <= 0.0)
        {
            throw std::invalid_argument("Вага повинна бути позитивною.");
        }
        weight_ = weight;
    };

    double Player::GetMarketValue() const { return marketValue_; }

    void Player::SetMarketValue(double marketValue)
    {
        if (marketValue <= 0.0)
        {
            throw std::invalid_argument(
                "Ринкова вартість не може бути негативною.");
        }
        marketValue_ = marketValue;
    }

    bool Player::IsInjured() const { return injured_; }

    const std::vector<Injury>& Player::GetInjuryHistory() const
    {
        return injuryHistory_;
    }


    const std::vector<Injury>& Player::GetInjuryHistory() const
    {
        return injuryHistory_;
    }

    void Player::ReportInjury(const std::string& type, int recoveryDays)
    {
        if (type.empty())
        {
            throw std::invalid_argument("Тип травми не може бути порожнім.");
        }

        if (recoveryDays <= 0)
        {
            throw std::invalid_argument(
                "Дні відновлення повинні бути більше нуля.");
        }

        injured_ = true;

        Injury newInjury;
        newInjury.injuryType = type;
        newInjury.recoveryDays = recoveryDays;
        newInjury.dateOccurred = "Today";

        injuryHistory_.push_back(std::move(newInjury));
    }

    void Player::ReturnToFitness()
    {
        injured_ = false;
    }

    void Player::UpdateMarketValue(double percentageChange)
    {
        double factor = 1.0 + (percentageChange / 100.0);
        marketValue_ = marketValue_ * factor;

        if (marketValue_ < 0.0)
        {
            marketValue_ = 0.0;
        }
    }

    std::string Player::Serialize() const
    {
        std::ostringstream ss;
        ss << "\"playerId\": " << playerId_ << ", ";
        ss << "\"name\": " << "\"" << name_ << "\", ";
        ss << "\"age\": " << age_ << ", ";
        ss << "\"nationality\": " << "\"" << nationality_ << "\", ";
        ss << "\"origin\": " << "\"" << origin_ << "\", ";
        ss << "\"height\": " << height_ << ", ";
        ss << "\"weight\": " << weight_ << ", ";
        ss << "\"marketValue\": " << marketValue_ << ", ";
        ss << "\"injured\": " << (injured_ ? "true" : "false") << ", ";

        ss << "\"injuryHistory\": [";
        for (size_t i = 0; i < injuryHistory_.size(); ++i)
        {
            const Injury& inj = injuryHistory_[i];
            ss << "{";
            ss << "\"injuryType\": " << "\"" << inj.injuryType << "\", ";
            ss << "\"dateOccurred\": " << "\"" << inj.dateOccurred << "\", ";
            ss << "\"recoveryDays\": " << inj.recoveryDays;
            ss << "}";
            if (i + 1 < injuryHistory_.size())
            {
                ss << ", ";
            }
        }
        ss << "]";

        return ss.str();
    }

    /**
     * @brief Проста допоміжна функція для пошуку ключа у JSON-подібному рядку.
     *
     * Повертає порожній рядок, якщо не знайдено.
     */
    static std::string ExtractJsonStringValue(const std::string& json, const std::string& key)
    {
        std::string pattern = "\"" + key + "\"";
        size_t pos = json.find(pattern);
        if (pos == std::string::npos) return std::string();

        pos = json.find(':', pos);
        if (pos == std::string::npos) return std::string();

        ++pos;
        // пропускаємо пробіли
        while (pos < json.size() && std::isspace(static_cast<unsigned char>(json[pos])))
        {
            ++pos;
        }

        if (pos < json.size() && json[pos] == '"')
        {
            ++pos;
            std::ostringstream out;
            while (pos < json.size() && json[pos] != '"')
            {
                if (json[pos] == '\\' && pos + 1 < json.size())
                {

                    ++pos;
                    out << json[pos];
                }
                else
                {
                    out << json[pos];
                }
                ++pos;
            }
            return out.str();
        }

        std::ostringstream out;
        while (pos < json.size() && json[pos] != ',' && json[pos] != '}' && json[pos] != ']')
        {
            out << json[pos++];
        }
        // trim
        std::string res = out.str();
        auto l = res.find_first_not_of(" \t\n\r");
        auto r = res.find_last_not_of(" \t\n\r");
        if (l == std::string::npos) return std::string();
        return res.substr(l, r - l + 1);
    }

    static int ExtractJsonIntValue(const std::string& json, const std::string& key, int defaultValue = 0)
    {
        std::string v = ExtractJsonStringValue(json, key);
        if (v.empty()) return defaultValue;
        try
        {
            return std::stoi(v);
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    static double ExtractJsonDoubleValue(const std::string& json, const std::string& key, double defaultValue = 0.0)
    {
        std::string v = ExtractJsonStringValue(json, key);
        if (v.empty()) return defaultValue;
        try
        {
            return std::stod(v);
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    static bool ExtractJsonBoolValue(const std::string& json, const std::string& key, bool defaultValue = false)
    {
        std::string v = ExtractJsonStringValue(json, key);
        if (v.empty()) return defaultValue;
        std::transform(v.begin(), v.end(), v.begin(), [](unsigned char c) { return std::tolower(c); });
        if (v == "true") return true;
        if (v == "false") return false;
        return defaultValue;
    }

    void Player::DeserializeBase(const std::string& data)
    {
        try
        {
            int id = ExtractJsonIntValue(data, "playerId", playerId_);
            playerId_ = id;

            std::string name = ExtractJsonStringValue(data, "name");
            if (!name.empty()) name_ = name;

            age_ = ExtractJsonIntValue(data, "age", age_);

            std::string nat = ExtractJsonStringValue(data, "nationality");
            if (!nat.empty()) nationality_ = nat;

            std::string orig = ExtractJsonStringValue(data, "origin");
            if (!orig.empty()) origin_ = orig;

            height_ = ExtractJsonDoubleValue(data, "height", height_);
            weight_ = ExtractJsonDoubleValue(data, "weight", weight_);
            marketValue_ = ExtractJsonDoubleValue(data, "marketValue", marketValue_);
            injured_ = ExtractJsonBoolValue(data, "injured", injured_);

            size_t pos = data.find("\"injuryHistory\"");
            if (pos != std::string::npos)
            {
                size_t arrStart = data.find('[', pos);
                size_t arrEnd = data.find(']', arrStart == std::string::npos ? pos : arrStart);
                if (arrStart != std::string::npos && arrEnd != std::string::npos && arrEnd > arrStart)
                {
                    std::string arrContent = data.substr(arrStart + 1, arrEnd - arrStart - 1);
                    injuryHistory_.clear();
                    size_t cur = 0;
                    while (cur < arrContent.size())
                    {
                        size_t objStart = arrContent.find('{', cur);
                        if (objStart == std::string::npos) break;
                        size_t objEnd = arrContent.find('}', objStart);
                        if (objEnd == std::string::npos) break;
                        std::string obj = arrContent.substr(objStart, objEnd - objStart + 1);

                        Injury inj;
                        inj.injuryType = ExtractJsonStringValue(obj, "injuryType");
                        inj.dateOccurred = ExtractJsonStringValue(obj, "dateOccurred");
                        inj.recoveryDays = ExtractJsonIntValue(obj, "recoveryDays", 0);

                        injuryHistory_.push_back(std::move(inj));
                        cur = objEnd + 1;
                    }
                }
            }
        }
        catch (...)
        {
        }
    }
}