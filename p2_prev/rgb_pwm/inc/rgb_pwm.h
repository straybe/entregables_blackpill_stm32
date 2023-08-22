/*
 * rgb_pwm.h
 *
 *  Created on: Aug 1, 2023
 *      Author: Daniel Meneses
 */

#ifndef INC_RGB_PWM_H_
#define INC_RGB_PWM_H_

#include "main.h"
#include "tim.h"

#define TIM_CHANNEL_RED 	TIM_CHANNEL_1
#define TIM_CHANNEL_GREEN 	TIM_CHANNEL_2
#define TIM_CHANNEL_BLUE 	TIM_CHANNEL_3
#define RGB_HANDLER			&htim2

typedef union{
	struct{
		uint32_t red 	: 8;
		uint32_t green 	: 8;
		uint32_t blue 	: 8;
		uint32_t dummy 	: 8;
	}colors;
	uint32_t all;
}rgb_color_t;

void rgb_pwm_star(void);
void rgb_pwm_stop(void);
void rgb_pwm_update(rgb_color_t *rgb_color);

#endif /* INC_RGB_PWM_H_ */
