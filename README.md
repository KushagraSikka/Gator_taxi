# GatorTaxi Project

This project simulates a taxi service called GatorTaxi. It provides functionalities for managing taxi rides using a combination of a min-heap and a Red-Black Tree data structure.

## Features

- Insert a new ride with a given ride number, ride cost, and trip duration
- Print ride details for a single ride or a range of ride numbers
- Get the next ride and remove it from the data structure
- Cancel a ride with a given ride number
- Update the trip duration for a ride with a given ride number and new trip duration

## Prerequisites

- A modern C++ compiler that supports C++11 (e.g., GCC, Clang, or MSVC)

## Compilation

1. Clone the repository or download the source files.
2. Navigate to the project directory in a terminal or command prompt.
3. Run the following commands to compile the project:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic -c GatorTaxi_project.cpp
g++ -std=c++11 -Wall -Wextra -pedantic -c GatorTaxi.cpp
g++ -std=c++11 -Wall -Wextra -pedantic -o GatorTaxi_project GatorTaxi_project.o GatorTaxi.o


Alternatively, you can use the provided Makefile:

"make"


Usage

After compilation, you can run the GatorTaxi_project executable with an input file containing commands to be executed by the program:

./GatorTaxi_project input_file.txt


The input file should contain commands for the GatorTaxi service, one per line. The following commands are supported:

Insert(rideNumber, rideCost, tripDuration)
Print(rideNumber)
Print(rideNumber1, rideNumber2)
GetNextRide()
CancelRide(rideNumber)
UpdateTrip(rideNumber, newTripDuration)
