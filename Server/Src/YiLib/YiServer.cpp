#include "YiServer.h"
#include <iostream>
#include <assert.h>

YiServer::YiServer(YiServicePool* svcp, yint8 max_threads):
	_ready(false),
	_max_threads(max_threads),
	_shutdown(true)
{
	_service_pool = svcp;
}

yint32 YiServer::Run()
{
	assert(_service_pool);
	_shutdown = false;
    for(yint32 i = 0; i < _max_threads; ++i)
    {
        _workers.push_back(std::thread(&YiServer::Tick, this));
    }

    _ready = true;
    Tick();

    for (auto& th: _workers)
        th.join();

    system("pause");
    return 0;
}

void YiServer::Tick()
{
	while (!_shutdown)
	{
		{
			std::unique_lock <std::mutex> lck(_mtx);
			while (!_ready)
				_cv.wait(lck);
			_ready = false;
		}

		YiIService* sv = nullptr;
		while (nullptr == (sv = _service_pool->Top()))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			_service_pool->Elapse(10);
		}
		_ready = true;
		_cv.notify_one();
		
		sv->Tick();
	}
}
