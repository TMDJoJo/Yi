#pragma once
#ifndef __YISERVICE_H__
#define __YISERVICE_H__

#include "YiType.h"
#include <condition_variable>
#include <vector>
#include <iostream>

class YiIService
{
	friend class YiServer;
public:
	typedef const yint32 service_id;
public:
	YiIService(service_id id, ystring name,yuint32 interval_time_millisecond = 1000/*defaut 1 second*/);
	void Elapse(yuint32 milliseconds);
	bool IsReady();
	service_id ServiceID() { return _service_id; }

    virtual ~YiIService(void) {}
    virtual ybool Init() {return true;}
    virtual ybool Destory() {return true;}
    static void Do(YiIService* self) {if(self != nullptr)self->Tick();}
	virtual void TickService() = 0;
private:
	virtual void Tick();
private:
    ystring     _service_name;
    service_id  _service_id;
    yuint32     _interval_time_millisecond;
    yint32      _elapse_time_millisecond;
};

class GeneralService : public YiIService
{
public:
	GeneralService(service_id id, ystring name, yuint32 interval_time_millisecond):
		YiIService(id, name, interval_time_millisecond)
	{
	}
	virtual void TickService()
	{
		//std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "tick in service id " << ServiceID() << std::endl;
	}

};

class YiServicePool
{
public:
    YiServicePool(){}
    YiServicePool(const YiServicePool&) = delete;
public:
	void Elapse(yuint32 miliseconds);
    ybool Push(YiIService*);
    YiIService* Top();
    std::vector<YiIService*> _pool;
};

#endif //__YISERVICE_H__
