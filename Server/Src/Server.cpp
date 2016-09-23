#include "YiServer.h"
#include "YiService.h"

int main(int argc, char** argv)
{
    return YiServer(4).Run();
}