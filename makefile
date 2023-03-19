CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = GatorTaxi

all: $(TARGET)

$(TARGET): GatorTaxi.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) GatorTaxi.o

GatorTaxi.o: GatorTaxi.cpp GatorTaxi.h
	$(CXX) $(CXXFLAGS) -c GatorTaxi.cpp

clean:
	rm -f $(TARGET) *.o
