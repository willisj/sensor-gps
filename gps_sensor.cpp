#include <libgpsmm.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

#include <cstdlib>
#include <pthread.h>

#include "gps_sensor.hpp"

gps_res::gps_res(char * port): gps_rec("localhost", port){
	if (this->gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
		std::cerr << "No GPSD running.\n";
		exit(1);
	}

    this->data_changed = false;
}


bool gps_res::poll_gps(){
	static struct gps_data_t *tmp_gps_data;
	// it the gps times out 
	if (!this->gps_rec.waiting(50000000))
		return false;

	// if the read fails
	tmp_gps_data = this->gps_rec.read();
	if (tmp_gps_data == NULL)
		return false;

	// copy the data
	this->newdata_mtex.lock();
	memcpy(&(this->newdata), tmp_gps_data, sizeof(gps_data_t));	
    this->data_changed = true;
	this->newdata_mtex.unlock();
	
	return true;
}

bool gps_res::get_gps_data(struct gps_data_t *dest){
    if (!this->data_changed)
        return false;

	this->newdata_mtex.lock();
	memcpy(dest, &(this->newdata), sizeof(gps_data_t));	
    this->data_changed = false;
	this->newdata_mtex.unlock();

    return true;
}

static void * gps_loop(void *data){
	gps_res *gps = (gps_res *)data;
    	for (;;) {
		if (!gps->poll_gps()) {
			std::cerr << "Read error.\n";
            		continue;
        	}     
	}
}

void gps_res::thread_gps(){
	this->gps_thread = new pthread_t;
	pthread_create(this->gps_thread, NULL, gps_loop, (void *)this);

}




