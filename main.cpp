#include <iostream>
#include <cmath>
#include "concolors.h"

int getMonthsOfService(int);

int main(int argc, char *argv[], char *envp[])
{
    if (argv[1] == NULL)
    {
        std::cout << "No arguments were supplied" << std::endl;
        return -1;
    }
    try
    {
        const double input = std::stod(argv[1]);
        std::cout << GREEN
                  << "Unconverted sick time hours: "
                  << YELLOW << input << RESET << std::endl;
        const double days = floor(input / 10.64);
        std::cout << GREEN
                  << "Converted sick leave days: "
                  << YELLOW << days << RESET << std::endl;
        if (days > 730)
        {
            throw 999;
        }
        const int months = getMonthsOfService(days);
        if (months == -1)
        {
            throw 988;
        }
        std::cout << GREEN << "Months of service credit: " << YELLOW << months << RESET << std::endl;
    }
    catch (int error)
    {
        switch (error)
        {
        case 977:
        {
            std::cout << "ERROR: Entered time should only contain numbers." << std::endl;
            break;
        }
        case 988:
        {
            std::cout << "ERROR: Something went wrong converting days to service credit." << std::endl;
            break;
        }
        case 999:
        {
            std::cout << "WARNING: Converted hours exceeds chart" << std::endl;
            break;
        }
        default:
            std::cout << "ERROR: " << error << std::endl;
        }
    }
    return 0;
}

int getMonthsOfService(int days)
{
    if (days <= 10)
    {
        return 0;
    }
    for (int i = 1; i < 37; i++)
    {
        const int lower = (i * 20) - 9;
        const int upper = (i * 20) + 10;
        if (days >= lower && days <= upper)
        {
            std::cout << MAGENTA << "Unused days: " << YELLOW << (days - lower) << RESET << std::endl;
            std::cout << MAGENTA << "Unused days converted back to hours: " << YELLOW << (days - lower) * 10.64 << RESET << std::endl;
            return i;
            break;
        }
    }
    return -1;
}