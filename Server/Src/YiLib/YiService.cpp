#include "YiService.h"

YiIService::YiIService(service_id id, ystring name, yuint32 interval_time_millisecond) :
	_service_id(id),
	_service_name(name),
	_interval_time_millisecond(interval_time_millisecond),
	_elapse_time_millisecond(interval_time_millisecond)
{

}

void YiIService::Tick()
{
	_elapse_time_millisecond += _interval_time_millisecond;
	TickService();
	std::cout << "tick " << std::this_thread::get_id() << std::endl;
}

void YiIService::Elapse(yuint32 milliseconds)
{
	_elapse_time_millisecond -= milliseconds;
}

bool YiIService::IsReady()
{
	return _elapse_time_millisecond <= 0;
}

void YiServicePool::Elapse(yuint32 miliseconds)
{
	for (auto& svc : _pool)
	{
		svc->Elapse(miliseconds);
	}
}

ybool YiServicePool::Push(YiIService* svc)
{
	if (svc != nullptr)
	{
		_pool.push_back(svc);
	}
	return true;
}

YiIService* YiServicePool::Top()
{
	for (auto& svc : _pool)
	{
		if (svc->IsReady())
		{
			return svc;
		}
	}
	return nullptr;
}
