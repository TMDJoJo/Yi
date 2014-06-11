/*
 * yi_server.h
 *
 *  Created on: May 15, 2014
 *      Author: tmdjojo
 */

#ifndef YI_SERVER_H_
#define YI_SERVER_H_

#include "yi_common.h"

class YiServer{
public:
    YiServer();
    virtual ~YiServer();
    INT Init(const CHAR* bind_ip,INT port);
    INT Loop();

    static VOID SigHandler(INT,SHORT,VOID*);

    inline struct event_base* event_base(){
        return event_base_;
    }

private:
    INT ShutDown();
    INT EvLoop();
    INT ListenTcp(const CHAR* bind_ip,INT port,INT& fd);

    static VOID OnAccept(INT,SHORT,VOID*);
private:
    CHAR is_shut_down_;
    CHAR bind_ip_[MAX_IP_LEN];
    INT listen_port_;
    INT listen_fd_;

    struct event_base* event_base_;
};

#endif /* YI_SERVER_H_ */
