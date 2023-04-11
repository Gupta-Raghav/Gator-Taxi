# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
TARGET = gatorTaxi

# Default rule
all: $(TARGET)

# Rule to build the program
$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean rule
clean:
	rm -f $(TARGET)

.PHONY: all clean