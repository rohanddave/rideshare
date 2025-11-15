#ifndef __HEARTBEAT_HANDLER_H__
#define __HEARTBEAT_HANDLER_H__

#include <memory>
#include "../common/ServerSocket.h"
#include "Messages.h"

class DriverHeartbeatHandler {
public:
	DriverHeartbeatHandler();
	void HandleConnection(std::unique_ptr<ServerSocket> socket, int connection_id);
};

#endif // end of #ifndef __HEARTBEAT_HANDLER_H__
