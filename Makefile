CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lboost_system -lboost_thread -lpthread

all: gatorTaxi

gatorTaxi: main.o gatorTaxi.o
	$(CXX) $(LDFLAGS) $^ -o $@


main.o: gatorTaxi.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f gatorTaxi *.o
