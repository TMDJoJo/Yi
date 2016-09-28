#include "YiServer.h"
#include "YiService.h"

int main(int argc, char** argv)
{
	YiServicePool svcp;
	svcp.Push(new GeneralService(1, "default", 1000));
	svcp.Push(new GeneralService(2, "default", 2000));
	svcp.Push(new GeneralService(3, "default", 1000));
    return YiServer(&svcp, 4).Run();
}
