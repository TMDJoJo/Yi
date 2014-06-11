/*
 * yi_common.h
 *
 *  Created on: May 16, 2014
 *      Author: tmdjojo
 */

#ifndef YI_COMMON_H_
#define YI_COMMON_H_

#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/event_compat.h>

#include "yi_type.h"

#define MAX_IP_LEN  (64)

#define MAX_INPUT_BUFFER_SIZE   (512*1024)
#define MAX_OUTPUT_BUFFER_SIZE   (512*1024)

#define MAX_SOCKET_READ_SIZE    (2048)
#define MAX_SOCKET_WRITE_SIZE    (2048)


namespace Yi_Utils{


INT SetNonblock(INT fd);
VOID InetN2A(in_addr * addr,CHAR * ip,INT size);


};



#endif /* YI_COMMON_H_ */
