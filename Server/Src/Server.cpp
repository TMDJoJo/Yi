#include <stdio.h>
#include <stdlib.h>
#include "YiType.h"
#include <thread>


yint32 f()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    printf("thread\n");
    return 0;
}

int main(int argc, char** argv)
{
    printf("hello world %d\n", sizeof(ybool));

    std::thread t(f);

    t.join();
    
    system("pause");
    return 0;
}
