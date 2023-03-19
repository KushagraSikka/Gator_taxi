CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

GatorTaxi_project: GatorTaxi_project.o GatorTaxi.o
	$(CXX) $(CXXFLAGS) -o GatorTaxi_project GatorTaxi_project.o GatorTaxi.o

GatorTaxi_project.o: GatorTaxi_project.cpp GatorTaxi.h
	$(CXX) $(CXXFLAGS) -c GatorTaxi_project.cpp

GatorTaxi.o: GatorTaxi.cpp GatorTaxi.h
	$(CXX) $(CXXFLAGS) -c GatorTaxi.cpp

clean:
	rm -f GatorTaxi_project GatorTaxi_project.o GatorTaxi.o
