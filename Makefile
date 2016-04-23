
CXX = g++ -std=gnu++11
required_libs = -lgps -lpthread -I . -pthread

all: module

debug: debug_flags = -ggdb -O0
debug: module

module: 
	$(CXX) $(required_libs) $(debug_flags) -c gps_sensor.cpp gps_sensor.hpp
	$(CXX) $(required_libs) $(debug_flags) -o gps_sensor_test 	gps.cpp	gps_sensor.o

clean:
	rm gps_sensor.o&
	rm gps_sensor_test&
	rm gps_sensor.hpp.gch
