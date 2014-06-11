/*
 * yi_buffer.h
 *
 *  Created on: May 16, 2014
 *      Author: tmdjojo
 */

#ifndef YI_BUFFER_H_
#define YI_BUFFER_H_
#include "yi_common.h"

class YiBuffer{
public:
    virtual ~YiBuffer(){}
    virtual INT Peek(CHAR*,INT size) = 0;
    virtual INT Read(CHAR*,INT size) = 0;
    virtual INT Write(const CHAR*,INT size) = 0;
};

class YiDefaultBuffer : public YiBuffer{
public:
    YiDefaultBuffer(INT max_buffer_size);
    virtual ~YiDefaultBuffer();
    virtual INT Peek(CHAR*,INT size);
    virtual INT Read(CHAR*,INT size);
    virtual INT Write(const CHAR*,INT size);

    INT Clean();
    inline INT buffer_size(){return buffer_length_;}
    inline INT buffer_free_size(){return max_buffer_size_ - buffer_length_;}
private:
    CHAR* data_;
    const INT max_buffer_size_;
    INT buffer_head_;
    INT buffer_tail_;
    INT buffer_length_;
};

#endif /* YI_BUFFER_H_ */
