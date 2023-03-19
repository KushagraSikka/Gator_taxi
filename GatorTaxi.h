#ifndef GATORTAXI_H
#define GATORTAXI_H

#include <string>

class GatorTaxi
{
public:
    GatorTaxi();

    // Insert a ride with the given rideNumber, rideCost, and tripDuration
    void insert(int rideNumber, int rideCost, int tripDuration);

    // Print ride details for a single ride or a range of rideNumbers
    void print(int rideNumber);
    void print(int rideNumber1, int rideNumber2);

    // Get the next ride and remove it from the data structure
    void getNextRide();

    // Cancel a ride with the given rideNumber
    void cancelRide(int rideNumber);

    // Update the trip duration for a ride with the given rideNumber and newTripDuration
    void updateTrip(int rideNumber, int newTripDuration);

    // Parse and execute a command from the input file
    void executeCommand(const std::string &command);

private:
    // Your min-heap and Red-Black Tree data structures and any additional helper methods should be defined here
};

#endif // GATORTAXI_H
