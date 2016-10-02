
#ifndef GPS_SENSOR_HPP
#define GPS_SENSOR_HPP

#include <libgpsmm.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

#include <pthread.h>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


class gps_res{
	private:
		gpsmm gps_rec;
		struct gps_data_t newdata;
		pthread_t *gps_thread;
		std::mutex newdata_mtex;
        bool data_changed;
	public:
		gps_res(char * port);
		bool poll_gps();
		void thread_gps();
		bool get_gps_data(struct gps_data_t *dest);
};


#endif
