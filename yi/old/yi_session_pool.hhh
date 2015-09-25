/*
 * yi_session_pool.h
 *
 *  Created on: Sep 1, 2014
 *      Author: tmdjojo
 */

#ifndef YI_SESSION_POOL_H_
#define YI_SESSION_POOL_H_

#include "yi_type.h"
#include "yi_session.h"

struct YiSessionNode{
    YiSession_* session_;
    INT next_;
    YiSessionNode(){
        session_ = NULL;
        next_ = -1;
    }
};

class YiSessionPool {
public:
    YiSessionPool(INT max_session_count);
    virtual ~YiSessionPool();
    INT Init();
    YiSession_* NewSession();
    YiSession_* NewSession(INT index);
    INT DeleteSession(YiSession_* session);
private:
    const INT max_session_count_;

    YiSessionNode* sessions_;
    //YiSession_** sessions_;
    INT session_remain_count_;
    INT current_free_index_;

};

#endif /* YI_SESSION_POOL_H_ */
