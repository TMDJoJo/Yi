/*
 * yi_message_encoder.h
 *
 *  Created on: May 20, 2014
 *      Author: tmdjojo
 */

#ifndef YI_MESSAGE_ENCODER_H_
#define YI_MESSAGE_ENCODER_H_

#include "yi_common.h"

class YiMessageEncoder {
public:
    YiMessageEncoder();
    virtual ~YiMessageEncoder();
    virtual INT Encode(VOID* ) = 0;
};

#endif /* YI_MESSAGE_ENCODER_H_ */
