/*
 * yi_server.cpp
 *
 *  Created on: May 15, 2014
 *      Author: tmdjojo
 */

#include "yi_server.h"
#include "yi_session_manager.h"

YiServer::YiServer(){

    is_shut_down_ = 0;
    memset(bind_ip_,0,MAX_IP_LEN);
    listen_port_ = -1;
    listen_fd_ = -1;

    event_base_ = NULL;
}

YiServer::~YiServer() {
    // TODO Auto-generated destructor stub
}

INT YiServer::Init(const CHAR* bind_ip,INT port){

    if(NULL == bind_ip){
        return -1;

    }
    if(MAX_IP_LEN < strlen(bind_ip)){
        return -1;
    }
    if(port > 65535){
        return -1;
    }
    strncpy(bind_ip_,bind_ip,MAX_IP_LEN);
    bind_ip_[MAX_IP_LEN - 1] = 0;
    listen_port_ = port;

    return 0;
}

INT YiServer::Loop(){

    if(0 == ListenTcp(bind_ip_,listen_port_,listen_fd_)){
        EvLoop();
    }
    else{
        return -1;
    }

    return 0;
}

VOID YiServer::SigHandler(INT,SHORT,VOID* arg){
    YiServer* server = static_cast<YiServer*>(arg);
    if(NULL != server)
        server->ShutDown();
}

INT YiServer::ShutDown(){
    is_shut_down_ = 1;
    return 0;
}

INT YiServer::EvLoop(){

    // Clean close on SIGINT or SIGTERM.

    event_base_ = event_base_new();

    struct event *listen_event;
    listen_event = event_new(event_base_,1,SIGINT,NULL,this);

    struct event ev_sig_int, ev_sig_term;
    signal_set(&ev_sig_int,SIGINT,SigHandler,this);
    event_base_set(event_base_, &ev_sig_int );
    signal_add(&ev_sig_int, NULL);

    signal_set(&ev_sig_term,SIGTERM,SigHandler,this);
    event_base_set(event_base_, &ev_sig_term );
    signal_add(&ev_sig_term, NULL);

    struct event ev_accept;
    event_set(&ev_accept,listen_fd_,EV_READ|EV_PERSIST,OnAccept,this);
    event_base_set(event_base_,&ev_accept);
    event_add(&ev_accept, NULL );

    while(0 == is_shut_down_){

        event_base_loop(event_base_,EVLOOP_ONCE );


    }

    event_del(&ev_accept);

    signal_del(&ev_sig_term);
    signal_del(&ev_sig_int);

    close(listen_fd_);

    return 0;
}

INT YiServer::ListenTcp(const CHAR* bind_ip,INT port,INT& fd){
    INT re = 0;
    if(NULL == bind_ip
            || '\0' == *bind_ip) {
        re = -1;
        return re;
    }
    do{
        fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0) {
            re = -1;
            break;
        }
        if(0 != evutil_make_socket_nonblocking(fd)){
            re = -1;
            break;
        }

        struct sockaddr_in addr;
        memset( &addr, 0, sizeof( addr ) );
        addr.sin_family = AF_INET;
        addr.sin_port = htons( port );

        addr.sin_addr.s_addr = INADDR_ANY;

        if(0 == inet_aton(bind_ip,&addr.sin_addr) ) {
            re = -1;
            break;
        }
        if( bind(fd,(struct sockaddr*)&addr,sizeof(addr) ) < 0 ) {
            re = -1;
            break;
        }
        if(listen(fd,1024) < 0) {
            re = -1;
            break;
        }
    }while(0);
    if( 0 != re && fd >= 0 ) close(fd);
    return re;
}

VOID YiServer::OnAccept(INT fd,SHORT events,VOID* arg){
    INT client_fd;
    struct sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);

    YiServer* server = static_cast<YiServer*>(arg);
    if(NULL == server)
        return ;

    client_fd = accept(fd,(struct sockaddr *)&addr,&addrLen);
    if( -1 == client_fd ) {
        return;
    }
    printf("accept client fd %d\n",client_fd);

    if(evutil_make_socket_nonblocking(client_fd) != 0) {
        printf("evutil_make_socket_nonblocking fail %d\n",client_fd);
        return ;
    }

    YiSession* session = g_yi_session_manager->New();
    if(NULL == session){
        printf("g_ev_session_manager->New fail\n");
        evutil_closesocket(client_fd);
        return ;
    }

    CHAR strip[MAX_IP_LEN] = {0};
    Yi_Utils::InetN2A( &(addr.sin_addr),strip,sizeof(strip) );
    session->set_ip(strip);
    session->set_port( ntohs(addr.sin_port) );
    session->set_socket_fd(client_fd);
    session->set_base_event(server->event_base_);
    //event_set(session->read_event_,client_fd,EV_READ,OnRead,session);
    //event_set(session->write_event_,client_fd,EV_WRITE,OnWrite,session);
    session->AddEvent(EV_READ,5);

}

