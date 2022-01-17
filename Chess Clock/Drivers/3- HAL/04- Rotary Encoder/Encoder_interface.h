/*
 * Encoder_interface.h
 *
 *  Created on: Jan 17, 2022
 *      Author: 20109
 */

#ifndef ROTARY_ENCODER_ENCODER_INTERFACE_H_
#define ROTARY_ENCODER_ENCODER_INTERFACE_H_


typedef enum{

	ENCODER_CHANGE_CLOCKWISE,
	ENCODER_CHANGE_COUNTER_CLOCKWISE
}EncoderChange_t;

void HENCODER_voidInit(void);

void HENCODER_voidSetChangeCallBack(void (*ChangeCallBack)(EncoderChange_t));

void HENCODER_voidEnableEncoder(void);

void HENCODER_voidDisableEncoder(void);



#endif /* 3__HAL_04__ROTARY_ENCODER_ENCODER_INTERFACE_H_ */
