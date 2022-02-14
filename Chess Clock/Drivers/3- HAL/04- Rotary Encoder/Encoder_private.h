/*
 * Encoder_private.h
 *
 *  Created on: Jan 17, 2022
 *      Author: 20109
 */

#ifndef ROTARY_ENCODER_ENCODER_PRIVATE_H_
#define ROTARY_ENCODER_ENCODER_PRIVATE_H_

void PENCODERChanged(void);

void (*PENCODERChangeCallBack)(EncoderChange_t);

void (*PENCODERSwitchCallBack)(void);

#endif /* 3__HAL_04__ROTARY_ENCODER_ENCODER_PRIVATE_H_ */
