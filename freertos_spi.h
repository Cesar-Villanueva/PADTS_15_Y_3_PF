/*
 * freertos_spi.h
 *
 *  Created on: Aug 20, 2021
 *      Author: edgardo
 */

#ifndef FREERTOS_SPI_H_
#define FREERTOS_SPI_H_

#include <stdint.h>

typedef enum
{
  freertos_spi_sucess,
  freertos_spi_fail
} freertos_spi_flag_t;

typedef enum
{
  freertos_spi_portA,
  freertos_spi_portB,
  freertos_spi_portC,
  freertos_spi_portD,
  freertos_spi_portE
} freertos_spi_port_t;

typedef enum
{
  freertos_spi0,
  freertos_spi1
} freertos_spi_number_t;

typedef struct
{
	uint32_t baudRate;
	freertos_spi_number_t spi_number;
	freertos_spi_port_t port;
	uint8_t mosi_pin;
	uint8_t miso_pin;
	uint8_t cs_pin;
	uint8_t clk_pin;
	uint8_t pin_mux;
} freertos_spi_config_t;

freertos_spi_flag_t freertos_spi_init (freertos_spi_config_t config);

freertos_spi_flag_t freertos_spi_transfer(freertos_spi_number_t spi_number, uint8_t * bufferTX, uint8_t * bufferRX, uint16_t lenght);

// freertos_spi_flag_t freertos_spi_receive(freertos_spi_number_t spi_number, uint8_t * buffer, uint16_t lenght);


#endif /* FREERTOS_SPI_H_ */
