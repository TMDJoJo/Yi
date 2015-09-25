/*
 * yi_session_manager.cpp
 *
 *  Created on: May 16, 2014
 *      Author: tmdjojo
 */

#include "yi_session_manager.h"

YiSessionManager* g_yi_session_manager = NULL;

YiSession::YiSession():
read_event_(NULL),
write_event_(NULL),
base_event_(NULL),
port_(0),
in_buffer_(NULL),
out_buffer_(NULL),
yi_session_manager_(NULL),
decoder_(NULL),
encoder_(NULL)
{
    socket_fd_ = -1;
    memset(ip_,0,MAX_IP_LEN);
    is_empty_ = true;

    index_in_manager_ = -1;
}

YiSession::~YiSession(){

    ////TODO
    event_del(read_event_);
    event_del(read_event_);

    SAFE_DELETE(read_event_);
    SAFE_DELETE(write_event_);
    SAFE_DELETE(in_buffer_);
    SAFE_DELETE(out_buffer_);
    SAFE_DELETE(decoder_);
    SAFE_DELETE(encoder_);
    //close(socket_fd_);
}

INT YiSession::Init(YiSessionManager* manager,INT index){
    read_event_ = new struct event;
    write_event_ = new struct event;

//    in_buffer_ = new YiBuffer(MAX_INPUT_BUFFER_SIZE);
//    out_buffer_ = new YiBuffer(MAX_OUTPUT_BUFFER_SIZE);

    index_in_manager_ = index;
    yi_session_manager_ = manager;
    return 0;
}

INT YiSession::Clean(){

    evutil_closesocket(socket_fd_);
    is_empty_ = TRUE;
//    in_buffer_->Clean();
//    out_buffer_->Clean();
    base_event_ = NULL;
    return 0;
}

INT YiSession::Disconnect(){
    printf("Disconnect\n");
    Clean();
    return 0;
}

INT YiSession::Error(){
    printf("Error\n");
    Clean();
    return 0;
}

INT YiSession::AddEvent(SHORT events,
        INT time_out_sec /*= 0*/,INT time_out_msec /*= 0*/){
    if(base_event_ == NULL){
        return -1;
    }
    if(socket_fd_ < 0){
        return -1;
    }

    if( (events & EV_WRITE) && write_event_){

        event_set(write_event_,socket_fd_,events,onWrite,this);
        event_base_set(base_event_,write_event_);

        if(time_out_sec == 0&&time_out_msec == 0){
            event_add(write_event_,NULL);
        }
        else{
            struct timeval timeout;
            memset( &timeout, 0, sizeof(timeout) );
            timeout.tv_sec = time_out_sec;
            timeout.tv_usec = time_out_msec;
            event_add(write_event_,&timeout);
        }

    }

    if( (events & EV_READ) && read_event_ ){

        event_set(read_event_,socket_fd_,events,onRead,this);
        event_base_set(base_event_,read_event_);

        if(time_out_sec == 0&&time_out_msec == 0){
            event_add(read_event_,NULL);
        }
        else{
            struct timeval timeout;
            memset( &timeout, 0, sizeof(timeout) );
            timeout.tv_sec = time_out_sec;
            timeout.tv_usec = time_out_msec;
            event_add(read_event_,&timeout);
        }
    }
    return 0;
}

VOID YiSession::onRead(INT fd,SHORT events,VOID * arg){
    YiSession* session = static_cast<YiSession*>(arg);
    if(NULL == session){

        return ;
    }

    if(EV_READ & events){

        CHAR buffer[MAX_SOCKET_READ_SIZE] = {0};
        INT receive_len = 0;
        INT read_size = MAX_SOCKET_READ_SIZE;
        do{
//            INT buffer_free_size = session->in_buffer_->buffer_free_size();
            INT buffer_free_size = 0;
            read_size = MAX_SOCKET_READ_SIZE < buffer_free_size ?
                    MAX_SOCKET_READ_SIZE : buffer_free_size;
            receive_len = recv(session->socket_fd_,buffer,read_size,0);
            if(receive_len <= 0){
                printf("%d errno = %d\n",__LINE__,errno);
                break;
            }

            printf("read buf [%s]\n",buffer);

            if(0 != session->in_buffer_->Write(buffer,receive_len)){
                receive_len = -1;
                printf("%d errno = %d\n",__LINE__,errno);
                break;
            }
            memset(buffer,0,MAX_SOCKET_READ_SIZE);
        }while(1);

        if( receive_len > 0
                ||(receive_len < 0&&EWOULDBLOCK == errno) ){
            VOID* message = session->decoder_->Decode(session->in_buffer_);
            ////TODO execute
            session->AddEvent(EV_READ,5);
        }
        else if(receive_len == 0){
            ////disconnect
            session->Disconnect();
        }
        else{
            session->Error();
            ////error and disconnect
        }

    }
    else{
        //SP_EventHelper::doTimeout( session );
        printf("time out\n");
    }

}

VOID YiSession::onWrite(INT fd,SHORT events,VOID * arg){
    YiSession* session = static_cast<YiSession*>(arg);

    if(EV_WRITE & events) {
        CHAR buffer[MAX_SOCKET_READ_SIZE] = {0};
        INT send_len = 0;
        while( (send_len = send(session->socket_fd_,buffer,MAX_SOCKET_READ_SIZE,0))
                > 0){
            printf("fd=%u, send line: %s\n",session->socket_fd_, buffer);
            if(0 != session->in_buffer_->Write(buffer,send_len)){
                send_len = -1;
                printf("errno = %d\n",errno);
                break;
            }
            memset(buffer,0,MAX_SOCKET_READ_SIZE);
        }

        if( send_len > 0
                ||(send_len < 0&&EWOULDBLOCK == errno) ){
            //VOID* message = session->decoder_->Encode(session->in_buffer_);
        }
        else if(send_len == 0){
            ////disconnect
            session->Disconnect();
        }
        else{
            session->Error();
            ////error and disconnect
        }

    }
    else{
        printf("time out\n");
        //SP_EventHelper::doTimeout( session );
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

YiSessionManager::YiSessionManager(INT max_session_size):
        max_session_size_(max_session_size)
{
    sessions_ = NULL;
    current_session_size_ = 0;
    current_pos_ = 0;
}

YiSessionManager::~YiSessionManager(){
    SAFE_DELETE_ARRAY(sessions_);
}

INT YiSessionManager::Init(){
    if(max_session_size_ < 1){
        return -1;
    }
    sessions_ = new YiSession[max_session_size_];
    for(INT index = 0;index < max_session_size_;++index){
        sessions_[index].Init(this,index);
        ////TODO set decoder & encoder
//        sessions_[index].set_decoder(&decoder_);

    }
    return 0;
}

YiSession* YiSessionManager::New(){
    YiSession* session = NULL;
    if(max_session_size_ < current_session_size_){
        return session;
    }
    for(INT index = 0;index < max_session_size_;++index){
        INT pos = (current_pos_ + index)%max_session_size_;
        if(sessions_[pos].is_empty()){
            sessions_[pos].set_is_empty(FALSE);
            session = &sessions_[pos];
            current_pos_ = pos;
            ++current_session_size_;
            break;
        }
    }
    return session;
}

