/*
 * yi_session.h
 *
 *  Created on: Sep 1, 2014
 *      Author: tmdjojo
 */

#ifndef YI_SESSION_H_
#define YI_SESSION_H_

#include "yi_type.h"

class YiSessionPool;
class YiSession_ {
    friend YiSessionPool;
public:
    YiSession_(YiSessionPool* pool,INT index_in_pool);
    virtual ~YiSession_();
    INT Init(INT socket_fd);
    INT Clean();
    INT Write(const CHAR* data,INT len);
    INT Read(CHAR* data,INT len);
    INT Peek(CHAR* data,INT len);
private:
    const YiSessionPool* session_pool_;
    const INT index_in_pool_;

    INT socket_fd_;
    BOOL is_empty_;
};

#endif /* YI_SESSION_H_ */
