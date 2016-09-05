#pragma once
#ifndef __YISERVER_H__
#define __YISERVER_H__

#include "YiType.h"

class YiIService;

class YiServer
{
public:
    ybool Init();
    void Run();
    ybool OnStart();
    ybool OnShutdown();
    ybool RegestService(YiIService* service);
};

#endif