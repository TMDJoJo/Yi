/*
 * yi_session_manager.h
 *
 *  Created on: May 16, 2014
 *      Author: tmdjojo
 */

#ifndef EV_SESSION_MANAGER_H_
#define EV_SESSION_MANAGER_H_

#include "yi_common.h"
#include "yi_buffer.h"
#include "yi_message_decoder.h"
#include "yi_message_encoder.h"

class YiSessionManager;

class YiSession{
public:
    YiSession();
    virtual ~YiSession();
    INT Init(YiSessionManager* manager,INT index);
    inline BOOL is_empty(){return is_empty_;}
    inline BOOL set_is_empty(BOOL is_empty){return (is_empty_ = is_empty);}

    INT set_ip(const CHAR* ip){
        strncpy(ip_,ip,MAX_IP_LEN);
        ip_[MAX_IP_LEN - 1] = '\0';
        return 0;
    }
    inline INT set_port(INT port){
        return (port_ = port);
    }
    inline INT set_socket_fd(INT fd){
        return (socket_fd_ = fd);
    }
    INT Clean();
    INT AddEvent(SHORT events,
            INT time_out_sec = 0,INT time_out_msec = 0);

    YiMessageDecoder* set_decoder(YiMessageDecoder* decoder){
        return (decoder_ = decoder);
    }

    YiMessageEncoder* set_encoder(YiMessageEncoder* encoder){
        return (encoder_ = encoder);
    }

    inline struct event_base* set_base_event(struct event_base* event){
        return (base_event_ = event);
    }


    INT Disconnect();
    INT Error();

private:
    static VOID onRead(INT fd,SHORT events,VOID * arg);
    static VOID onWrite(INT fd,SHORT events,VOID * arg);

public:
    struct event* read_event_;
    struct event* write_event_;
protected:
    INT socket_fd_;

    struct event_base* base_event_;

    CHAR ip_[MAX_IP_LEN];
    INT port_;
    YiBuffer* in_buffer_;
    YiBuffer* out_buffer_;
    BOOL is_empty_;

    INT index_in_manager_;
    YiSessionManager* yi_session_manager_;

    YiMessageDecoder* decoder_;
    YiMessageEncoder* encoder_;
};

class YiSessionManager{
public:
    YiSessionManager(INT max_session_size);
    virtual ~YiSessionManager();
    INT Init();
    YiSession* New();
private:
    YiSession* sessions_;
    const INT max_session_size_;
    INT current_session_size_;
    INT current_pos_;

//    DefaultDecoder decoder_;
};

extern YiSessionManager* g_yi_session_manager;

#endif /* EV_SESSION_MANAGER_H_ */
