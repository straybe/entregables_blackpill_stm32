/*
 * at24c_xxx.h
 *
 *  Created on: Jul 27, 2023
 *      Author: Daniel Meneses
 */

#ifndef INC_AT24C_XXX_H_
#define INC_AT24C_XXX_H_

#include "main.h"
#include "stdint.h"

#define AT24C_ADDR 	0xA0

typedef enum{
	AT24_OPERATION_OK,
	AT24_I2C_WRITE_ERROR,
	AT24_I2C_READ_ERROR,
	AT24_INVALID_MEMORY_ADDR
}at24c_status_t;

typedef union{
	struct{
		uint16_t byte_addr : 7;
		uint16_t page_addr : 9;
	}partition_addr;

	uint16_t full_addr;
}at24_mem_addr_t;

void at24c_write_byte(uint8_t device_addr, uint16_t memory_addr, uint8_t data);
void at24c_read_byte(uint8_t device_addr, uint16_t memory_addr, uint8_t *data_rcv);

at24c_status_t at24c_write_4_bytes(uint8_t device_addr, uint16_t memory_addr, uint8_t *data);

at24c_status_t at24c_write_word(uint8_t device_addr, uint16_t memory_addr, uint32_t data);
at24c_status_t at24c_read_word(uint8_t device_addr, uint16_t memory_addr, uint32_t *data_rcv);

#endif /* INC_AT24C_XXX_H_ */
