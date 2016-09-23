#pragma once
#ifndef __YISERVICE_H__
#define __YISERVICE_H__

#include "YiType.h"
#include <condition_variable>
#include <vector>

class YiIService
{
public:
    typedef yuint32 service_id;

public:
    YiIService(void) {}
    virtual ~YiIService(void) {}
    virtual ybool Init() {return true;}
    virtual ybool Destory() {return true;}
    static void Do(YiIService* self) {if(self != nullptr)self->Tick();}
    virtual void Tick() = 0;
private:
    ystring     _service_name;
    service_id  _service_id;
    yuint32     _interval_time_millisecond;
    yint32      _elapse_time_millisecond;
};

class YiServicePool
{
public:
    YiServicePool(){}
private:
    YiServicePool(const YiServicePool&);
public:
    ybool Push(YiIService*);
    YiIService* Pop();
    std::vector<YiIService*> _pool;
};

#endif //__YISERVICE_H__
