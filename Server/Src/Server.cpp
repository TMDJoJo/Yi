#include "YiServer.h"
#include "YiService.h"
#include <random>

int main(int argc, char** argv)
{
	YiServicePool svcp;
	for (yint32 i = 0; i < 60; i++)
	{
		std::random_device rd;
		svcp.Push(new GeneralService(i, "default", (rd() % 5 + 1) * 1000));

	}
    return YiServer(&svcp, 32).Run();
}
