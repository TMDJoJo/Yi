/*
 * yi_session.cpp
 *
 *  Created on: Sep 1, 2014
 *      Author: tmdjojo
 */

#include "yi_session.h"

YiSession_::YiSession_(YiSessionPool* pool,INT index_in_pool):
session_pool_(pool),
index_in_pool_(index_in_pool),
socket_fd_(-1),
is_empty_(TRUE)
{

}

YiSession_::~YiSession_() {

}

INT YiSession_::Init(INT socket_fd){
    socket_fd_ = socket_fd;
    is_empty_ = FALSE;
    return 0;
}

INT YiSession_::Clean(){

    is_empty_ = TRUE;
    return 0;
}

INT YiSession_::Write(const CHAR* data,INT len){
    return 0;
}

INT YiSession_::Read(CHAR* data,INT len){
    return 0;
}

INT YiSession_::Peek(CHAR* data,INT len){
    return 0;
}


