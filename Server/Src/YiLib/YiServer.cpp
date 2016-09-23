#include "YiServer.h"
#include <iostream>

YiServer::YiServer(yint8 max_threads){
    _max_threads = max_threads;
    _ready = false;
}

yint32 YiServer::Run()
{
    for(yint32 i = 0; i < _max_threads; ++i)
    {
        _workers.push_back(std::thread(&YiServer::Tick, this));
    }

    _ready = true;
    _cv.notify_one();

    Tick();

    for (auto& th: _workers)
        th.join();

    system("pause");
    return 0;
}

void YiServer::Tick()
{
    std::unique_lock <std::mutex> lck(_mtx);
    while (!_ready)
        _cv.wait(lck);
    std::cout<<"tick "<<std::this_thread::get_id()<<std::endl;
    _cv.notify_one();
}
