/*
 * at24c_xxx.c
 *
 *  Created on: Jul 27, 2023
 *      Author: Daniel Meneses
 */

#include "at24c_xxx.h"
#include "i2c.h"

void at24c_write_byte(uint8_t device_addr, uint16_t memory_addr, uint8_t data){
	uint8_t aux[3];

	aux[0] = (memory_addr & 0xFF00) >> 8;
	aux[1] = memory_addr & 0x00FF;
	aux[2] = data;

	HAL_I2C_Master_Transmit(&hi2c1, device_addr, aux, 3, 200);
	HAL_Delay(5);
}

void at24c_read_byte(uint8_t device_addr, uint16_t memory_addr, uint8_t *data_rcv){
	uint8_t aux[2], rcv_aux;

	aux[0] = (memory_addr & 0xFF00) >> 8;
	aux[1] = memory_addr & 0x00FF;
	HAL_I2C_Master_Transmit(&hi2c1, device_addr, aux, 2, 200);

	HAL_Delay(5);

	HAL_I2C_Master_Receive(&hi2c1, device_addr, &rcv_aux, 1, 200);
	*data_rcv = rcv_aux;
}
at24c_status_t at24c_write_word(uint8_t device_addr, uint16_t memory_addr, uint32_t data){
	uint8_t aux[6];
	HAL_StatusTypeDef ref_status;
	if((memory_addr&0x007F) > 124){
		return AT24_INVALID_MEMORY_ADDR;
	}
	else{
		aux[0] = (memory_addr & 0xFF00) >> 8;
		aux[1] = memory_addr & 0x00FF;
		aux[2] = (data&0xFF000000) >> 24;
		aux[3] = (data&0x00FF0000) >> 16;
		aux[4] = (data&0x0000FF00) >> 8;
		aux[5] = (data&0x000000FF);

		ref_status = HAL_I2C_Master_Transmit(&hi2c1, device_addr, aux, 6, 200);
		if(ref_status != HAL_OK){
			return AT24_I2C_WRITE_ERROR;
		}
		HAL_Delay(5);
	}
	return AT24_OPERATION_OK;
}

at24c_status_t at24c_read_word(uint8_t device_addr, uint16_t memory_addr, uint32_t *data_rcv){
	uint8_t aux[2], rcv_aux[4];
	uint32_t aux_data;
	HAL_StatusTypeDef ref_status;
	if((memory_addr&0x007F) > 124){
		return AT24_INVALID_MEMORY_ADDR;
	}
	else{
		aux[0] = (memory_addr & 0xFF00) >> 8;
		aux[1] = memory_addr & 0x00FF;
		ref_status = HAL_I2C_Master_Transmit(&hi2c1, device_addr, aux, 2, 200);
		if(ref_status != HAL_OK){
			return AT24_I2C_WRITE_ERROR;
		}

		HAL_Delay(5);

		ref_status = HAL_I2C_Master_Receive(&hi2c1, device_addr, rcv_aux, 4, 200);
		if(ref_status != HAL_OK){
			return AT24_I2C_READ_ERROR;
		}
		aux_data = ((rcv_aux[0] << 24) & 0xFF000000) + ((rcv_aux[1] << 16) & 0x00FF0000)
				+ ((rcv_aux[2] << 8) & 0x0000FF00) + (rcv_aux[3]&0xFF);
		*data_rcv = aux_data;
	}
	return AT24_OPERATION_OK;
}
