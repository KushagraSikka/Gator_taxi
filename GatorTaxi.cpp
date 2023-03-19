#include "GatorTaxi.h"
#include <sstream>
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
GatorTaxi::GatorTaxi()
{
    // Constructor implementation
}

void GatorTaxi::insert(int rideNumber, int rideCost, int tripDuration)
{
    // Insert method implementation
    std::cout << "Insert called with rideNumber: " << rideNumber << ", rideCost: " << rideCost << ", tripDuration: " << tripDuration << std::endl;
}

void GatorTaxi::print(int rideNumber)
{
    // Print method implementation (single rideNumber)
    std::cout << "Print called with rideNumber: " << rideNumber << std::endl;
}

void GatorTaxi::print(int rideNumber1, int rideNumber2)
{
    // Print method implementation (range of rideNumbers)
    std::cout << "Print called with rideNumber1: " << rideNumber1 << ", rideNumber2: " << rideNumber2 << std::endl;
}

void GatorTaxi::getNextRide()
{
    // GetNextRide method implementation
    std::cout << "getNextRide called" << std::endl;
}

void GatorTaxi::cancelRide(int rideNumber)
{
    // CancelRide method implementation
    std::cout << "cancelRide called with rideNumber: " << rideNumber << std::endl;
}

void GatorTaxi::updateTrip(int rideNumber, int newTripDuration)
{
    // UpdateTrip method implementation
    std::cout << "updateTrip called with rideNumber: " << rideNumber << ", newTripDuration: " << newTripDuration << std::endl;
}