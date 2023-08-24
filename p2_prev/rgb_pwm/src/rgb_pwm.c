/*
 * reg_pwm.c
 *
 *  Created on: Aug 1, 2023
 *      Author: Daniel Meneses
 */

#include "rgb_pwm.h"

void rgb_pwm_star(void){
	HAL_TIM_PWM_Start(RGB_HANDLER, TIM_CHANNEL_RED);
	HAL_TIM_PWM_Start(RGB_HANDLER, TIM_CHANNEL_GREEN);
	HAL_TIM_PWM_Start(RGB_HANDLER, TIM_CHANNEL_BLUE);
}

void rgb_pwm_stop(void){
	HAL_TIM_PWM_Stop(RGB_HANDLER, TIM_CHANNEL_RED);
	HAL_TIM_PWM_Stop(RGB_HANDLER, TIM_CHANNEL_GREEN);
	HAL_TIM_PWM_Stop(RGB_HANDLER, TIM_CHANNEL_BLUE);
}

void rgb_pwm_update(rgb_color_t *rgb_color){
	uint8_t r,g,b;

	r = (uint8_t)(255 - rgb_color->colors.red);
	g = (uint8_t)(255 - rgb_color->colors.green);
	b = (uint8_t)(255 - rgb_color->colors.blue);
	__HAL_TIM_SET_COMPARE(RGB_HANDLER, TIM_CHANNEL_RED, r);
	__HAL_TIM_SET_COMPARE(RGB_HANDLER, TIM_CHANNEL_GREEN, g);
	__HAL_TIM_SET_COMPARE(RGB_HANDLER, TIM_CHANNEL_BLUE, b);
}
