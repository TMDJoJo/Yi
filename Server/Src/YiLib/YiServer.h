#pragma once
#ifndef __YISERVER_H__
#define __YISERVER_H__

#include "YiType.h"
#include <condition_variable>
#include <vector>
#include <thread>
#include "YiService.h"

//class YiIService;

class YiServer
{
public:
    YiServer(YiServicePool* svcp, yint8 max_threads);
	YiServer(const YiServer&) = delete;
public:
    ybool Init();
    yint32 Run();
    ybool OnStart();
    ybool OnShutdown();

    //ybool RegestService(YiIService* service);
private:
    void Tick();

private:
    std::mutex _mtx;
    std::condition_variable _cv;
    std::vector<std::thread> _workers;
    yint8 _max_threads;
    ybool _ready;
	ybool _shutdown;
	YiServicePool* _service_pool;
};

#endif
