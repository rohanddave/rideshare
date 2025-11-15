#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include <condition_variable>
#include <future>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "DriverSocket.h"

class DriverServerThread {
public:
	DriverServerThread();
	void Init(std::unique_ptr<DriverSocket> socket, int id);
};

#endif // end of #ifndef __SERVERTHREAD_H__

