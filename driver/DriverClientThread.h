#ifndef __CLIENT_THREAD_H__
#define __CLIENT_THREAD_H__

#include <chrono>
#include <ctime>
#include <string>
#include <thread>

#include "DriverClientStub.h"

class DriverClientThread {
	DriverClientStub stub;

public:
	DriverClientThread();
	void ThreadBody(std::string ip, int port, int id);

	// Two separate thread functions
	void HeartbeatThread();
	void RequestHandlerThread();
};


#endif // end of #ifndef __CLIENT_THREAD_H__
