#ifndef __YITHREAD_H__
#define __YITHREAD_H__

#include "YiType.h"
#include <thread>

class YiThread
{
public:
    YiThread(void);
    virtual ~YiThread(void);
    virtual ybool Run() = 0;
};

#endif //__YITHREAD_H__
