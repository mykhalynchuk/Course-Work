#include "../include/InputValidator.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cctype>

namespace FootballManagement
{
    void InputValidator::ClearInputBuffer()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int InputValidator::GetIntInput(const std::string& prompt)
    {
        int value;
        while (true)
        {
            std::cout << prompt;

            if (std::cin >> value)
            {
                ClearInputBuffer();
                return value;
            }
            else
            {
                std::cout <<
                    "[ERROR] Invalid input type. Please enter a valid integer."
                    << std::endl;
                ClearInputBuffer();
            }
        }
    }

    int InputValidator::GetIntInRange(const std::string& prompt, int min,
                                      int max)
    {
        int value;

        while (true)
        {
            value = GetIntInput(
                prompt + " (" + std::to_string(min) + "-" + std::to_string(max)
                + "): ");

            if (value >= min && value <= max)
            {
                return value;
            }
            else
            {
                std::cout << "[ERROR] Value out of range. Must be between " <<
                    min << " and " << max << "." << std::endl;
            }
        }

        double InputValidator::GetDoubleInput(const std::string& prompt)
        {
            double value;
            while (true)
            {
                std::cout << prompt;
                if (std::cin >> value)
                {
                    ClearInputBuffer();
                    return value;
                }
                else
                {
                    std::cout <<
                        "[ERROR] Invalid input type. Please enter a valid number."
                        << std::endl;
                    ClearInputBuffer();
                }
            }
        }
    }
}
