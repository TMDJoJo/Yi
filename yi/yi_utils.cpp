/*
 * yi_utils.cpp
 *
 *  Created on: May 20, 2014
 *      Author: tmdjojo
 */

#include "yi_common.h"

namespace Yi_Utils{

INT SetNonblock(INT fd){
#ifdef WIN32
    unsigned long nonblocking = 1;
    ioctlsocket( fd, FIONBIO, (unsigned long*) &nonblocking );
#else
    INT flags;

    flags = fcntl(fd,F_GETFL);
    if(flags < 0) return flags;

    flags |= O_NONBLOCK;
    if(fcntl( fd, F_SETFL, flags) < 0) return -1;
#endif

    return 0;
}

VOID InetN2A(in_addr * addr,CHAR * ip,INT size){
#if defined (linux) || defined (__sgi) || defined (__hpux) \
        || defined (__FreeBSD__) || defined (__APPLE__)
    const unsigned char *p = (const unsigned char *) addr;
    snprintf(ip,size,"%i.%i.%i.%i",p[0],p[1],p[2],p[3] );
#else
    snprintf(ip,size,"%i.%i.%i.%i",
            addr->s_net,addr->s_host,addr->s_lh,addr->s_impno );
#endif
}

};

