#include <libgpsmm.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

#include <unistd.h>

#include "gps_sensor.hpp"

int main(void)
{
	
	gps_res gps(DEFAULT_GPSD_PORT); 
	struct gps_data_t newdata;
	
	std::cout << "Starting GPS thread" << std::endl;
	gps.thread_gps();


    	for (;;) {
		gps.get_gps_data(&newdata);
		gps_fix_t f = newdata.fix;
		std::cout << "[" << newdata.satellites_used << "]" << f.time << "\t (" << f.latitude << ", " << f.longitude << ", " << f.altitude << ")" << std::endl;
		usleep(10000);
    	}

	std::cout << "Exiting." << std::endl;
    return 0;
}
