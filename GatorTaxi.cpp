#include "GatorTaxi.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>

void GatorTaxi::executeCommand(const std::string &command)
{
    std::smatch match;

    if (std::regex_match(command, match, std::regex("Insert\\((\\d+),(\\d+),(\\d+)\\)")))
    {
        int rideNumber = std::stoi(match[1]);
        int rideCost = std::stoi(match[2]);
        int tripDuration = std::stoi(match[3]);
        insert(rideNumber, rideCost, tripDuration);
    }
    else if (std::regex_match(command, match, std::regex("Print\\((\\d+),(\\d+)\\)")))
    {
        int rideNumber1 = std::stoi(match[1]);
        int rideNumber2 = std::stoi(match[2]);
        print(rideNumber1, rideNumber2);
    }
    else if (std::regex_match(command, match, std::regex("Print\\((\\d+)\\)")))
    {
        int rideNumber = std::stoi(match[1]);
        print(rideNumber);
    }
    else if (std::regex_match(command, match, std::regex("UpdateTrip\\((\\d+),(\\d+)\\)")))
    {
        int rideNumber = std::stoi(match[1]);
        int newTripDuration = std::stoi(match[2]);
        updateTrip(rideNumber, newTripDuration);
    }
    else if (std::regex_match(command, match, std::regex("GetNextRide\\(\\)")))
    {
        getNextRide();
    }
    else if (std::regex_match(command, match, std::regex("CancelRide\\((\\d+)\\)")))
    {
        int rideNumber = std::stoi(match[1]);
        cancelRide(rideNumber);
    }
    else
    {
        std::cerr << "Invalid command: " << command << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./gatorTaxi <input_file>" << std::endl;
        return 1;
    }

    GatorTaxi gatorTaxi;
    std::string inputFilename(argv[1]);
    std::ifstream inputFile(inputFilename);
    std::string command;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    while (std::getline(inputFile, command))
    {
        gatorTaxi.executeCommand(command);
    }

    inputFile.close();
    return 0;
}