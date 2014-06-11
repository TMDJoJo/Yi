/*
 * tristana.cpp
 *
 *  Created on: Mar 6, 2014
 *      Author: tmdjojo
 */

#include <signal.h>
#include "tristana.h"
//#include <glog/logging.h>
#include "../yi/yi_session_manager.h"
#include "../yi/yi_server.h"


Tristana::Tristana() {
	// TODO Auto-generated constructor stub

}

Tristana::~Tristana() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char *argv[])
{

    g_yi_session_manager = new YiSessionManager(64);
    g_yi_session_manager->Init();

    YiServer *server = new YiServer;
    server->Init("127.0.0.1",8888);
    server->Loop();

    return 0;
}

