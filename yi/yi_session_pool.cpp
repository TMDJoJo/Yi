/*
 * yi_session_pool.cpp
 *
 *  Created on: Sep 1, 2014
 *      Author: tmdjojo
 */

#include "yi_session_pool.h"

YiSessionPool::YiSessionPool(INT max_session_count):
max_session_count_(max_session_count),
sessions_(NULL),
session_remain_count_(max_session_count),
current_free_index_(0)
{

}

YiSessionPool::~YiSessionPool() {

}

INT YiSessionPool::Init(){

    sessions_ = new YiSessionNode[max_session_count_];
    for(int index = 0;index < max_session_count_;++index){
        sessions_[index].session_ = new YiSession_(this,index);
        sessions_[index].next_ = index + 1;
        //TODO
    }
    sessions_[max_session_count_ - 1].next_ = -1;
    return 0;
}

YiSession_* YiSessionPool::NewSession(){
    YiSession_* session = NULL;
    if(max_session_count_ > 0
            &&current_free_index_ >= 0
            &&current_free_index_ < max_session_count_){
        --max_session_count_;
        session = sessions_[current_free_index_].session_;
        current_free_index_ = sessions_[current_free_index_].next_;
        sessions_[current_free_index_].next_ = -1;
    }

    return session;
}

YiSession_* YiSessionPool::NewSession(INT index){

    return NULL;
}

INT YiSessionPool::DeleteSession(YiSession_* session){

    if(NULL != session
            &&0 == session->Clean()){
        sessions_[session->index_in_pool_].next_ = current_free_index_;
        current_free_index_ = session->index_in_pool_;
        ++max_session_count_;
        return 0;
    }
    else{
        return -1;
    }
}

