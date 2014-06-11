/*
 * yi_buffer.cpp
 *
 *  Created on: May 16, 2014
 *      Author: tmdjojo
 */

#include "yi_buffer.h"

YiDefaultBuffer::YiDefaultBuffer(INT max_buffer_size):
max_buffer_size_(max_buffer_size),
buffer_head_(0),
buffer_tail_(0),
buffer_length_(0)
{

    data_ = new CHAR[max_buffer_size];
    memset(data_,0,max_buffer_size);

}

YiDefaultBuffer::~YiDefaultBuffer() {
    SAFE_DELETE_ARRAY(data_);
}

INT YiDefaultBuffer::Peek(CHAR* buf,INT size){
    if(buffer_length_ < size){
        return -1;
    }

    INT remaind_len = max_buffer_size_ - buffer_head_;
    if(remaind_len < size){
        memcpy(buf,data_ + buffer_head_,remaind_len);
        memcpy(buf + remaind_len,data_,size - remaind_len);
    }
    else{
        memcpy(buf,data_ + buffer_head_,size);
    }
    return -1;
}

INT YiDefaultBuffer::Read(CHAR* buf,INT size){
    if(buffer_length_ < size){
        return -1;
    }

    INT remaind_len = max_buffer_size_ - buffer_head_;
    if(remaind_len < size){
        memcpy(buf,data_ + buffer_head_,remaind_len);
        memcpy(buf + remaind_len,data_,size - remaind_len);
    }
    else{
        memcpy(buf,data_ + buffer_head_,size);
    }
    buffer_length_ -= size;
    buffer_head_ = (buffer_head_ + size)%max_buffer_size_;
    return 0;
}

INT YiDefaultBuffer::Write(const CHAR* buf,INT size){
    if(max_buffer_size_ - buffer_length_ < size){
        return -1;
    }
    INT remaind_len = max_buffer_size_ - buffer_tail_;
    if( remaind_len < size ){
        memcpy(data_ + buffer_tail_,buf,remaind_len);
        memcpy(data_,buf + remaind_len,size - remaind_len);
        buffer_tail_ = size - remaind_len;
        buffer_length_ += size;
    }
    else{
        memcpy(&data_[buffer_tail_],buf,size);
        buffer_tail_ += size;
        buffer_length_ += size;
    }
    return 0;
}

INT YiDefaultBuffer::Clean(){
    memset(data_,0,max_buffer_size_);

    buffer_head_ = 0;
    buffer_tail_ = 0;
    buffer_length_ = 0;
    return 0;
}
