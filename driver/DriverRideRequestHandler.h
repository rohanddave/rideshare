#ifndef __RIDE_REQUEST_HANDLER_H__
#define __RIDE_REQUEST_HANDLER_H__

#include <memory>
#include "../common/ServerSocket.h"
#include "Messages.h"

class DriverRideRequestHandler {
public:
	DriverRideRequestHandler();
	void HandleConnection(std::unique_ptr<ServerSocket> socket, int connection_id);
};

#endif // end of #ifndef __RIDE_REQUEST_HANDLER_H__
