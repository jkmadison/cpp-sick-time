#include <iostream>
#include <cmath>
#include "concolors.h"
#include "record.h"
#include <fstream>

Record user;
void getMonthsOfService(Record &);
void printReport(Record);
void writeToFile(Record);

int main(int argc, char *argv[], char *envp[])
{
    if (argv[1] == NULL)
    {
        std::cout << "No arguments were supplied" << std::endl;
        return -1;
    }
    try
    {
        user.sicktime = std::stod(argv[1]);

        user.convertedToDays = floor(user.sicktime / 10.64);

        if (user.convertedToDays > 730)
        {
            throw 999;
        }
        getMonthsOfService(user);
        if (user.serviceMonths == -1)
        {
            throw 988;
        }
        printReport(user);
        writeToFile(user);
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

void getMonthsOfService(Record &u)
{
    if (u.convertedToDays <= 10)
    {
        return;
    }
    for (int i = 1; i < 37; i++)
    {
        const int lower = (i * 20) - 9;
        const int upper = (i * 20) + 10;
        if (u.convertedToDays >= lower && u.convertedToDays <= upper)
        {
            u.serviceMonths = i;
            u.unusedDays = u.convertedToDays - lower;
            u.unusedHours = u.unusedDays * 10.64;
            break;
        }
    }
}

void printReport(Record u)
{
    std::cout << GREEN
              << "Unconverted sick time hours: "
              << YELLOW << u.sicktime << RESET << std::endl;
    std::cout << GREEN
              << "Converted sick leave days: "
              << YELLOW << u.convertedToDays << RESET << std::endl;

    std::cout << GREEN << "Months of service credit: " << YELLOW << u.serviceMonths << RESET << std::endl;
    std::cout << MAGENTA << "Unused days: " << YELLOW << u.unusedDays << RESET << std::endl;
    std::cout << MAGENTA << "Unused days converted back to hours: " << YELLOW << u.unusedHours << RESET << std::endl;
}

void writeToFile(Record u)
{
    std::ofstream file("user.txt", std::ofstream::out);
    if (file.fail())
    {
        std::cout << "There was an error" << std::endl;
    }
    file << "Unconverted sick time hours: " << u.sicktime << "\n";
    file << "Converted sick leave days: " << u.convertedToDays << "\n";
    file << "Months of service credit: " << u.serviceMonths << "\n";
    file << "Unused days: " << u.unusedDays << "\n";
    file << "Unused days converted back to hours: " << u.unusedHours << "\n";

    file.close();
}