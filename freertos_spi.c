/*
 * freertos_spi.c
 *
 *  Created on: Aug 20, 2021
 *      Author: edgardo
 */

#include "freertos_spi.h"

#include "fsl_port.h"
#include "fsl_dspi.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"

typedef struct
{
  uint8_t is_init;
  dspi_master_handle_t fsl_spi_handle;
  SemaphoreHandle_t mutex_rx;
  SemaphoreHandle_t mutex_tx;
  SemaphoreHandle_t rx_sem;
  SemaphoreHandle_t tx_sem;
} freertos_spi_handle_t;

static freertos_spi_handle_t freertos_spi_handles[2] = {0};

static void fsl_spi_callback(SPI_Type *base, dspi_master_handle_t *handle, status_t status, void *userData);

static inline PORT_Type * freertos_spi_get_port_base(freertos_spi_port_t port);

static inline SPI_Type * freertos_spi_get_spi_base(freertos_spi_number_t spi_number);

freertos_spi_flag_t freertos_spi_init (freertos_spi_config_t config)
{
	freertos_spi_flag_t retval = freertos_spi_fail;

	dspi_master_config_t fsl_spi_config;

	freertos_spi_handles[config.spi_number].mutex_tx = xSemaphoreCreateMutex();

	freertos_spi_handles[config.spi_number].mutex_rx = xSemaphoreCreateMutex();

	freertos_spi_handles[config.spi_number].tx_sem = xSemaphoreCreateBinary();

	freertos_spi_handles[config.spi_number].rx_sem = xSemaphoreCreateBinary();

	// vQueueAddToRegistry(freertos_uart_handles[0].mutex_tx, "Mutex TX UART");
  //
	// vQueueAddToRegistry(freertos_uart_handles[0].mutex_rx, "Mutex RX UART");
  //
	// vQueueAddToRegistry(freertos_uart_handles[0].tx_sem, "Semaphore TX UART");
  //
	// vQueueAddToRegistry(freertos_uart_handles[0].rx_sem, "Semaphore RX UART");

	switch(config.port)
	{
		case freertos_spi_portA:
			CLOCK_EnableClock(kCLOCK_PortA);
			break;
		case freertos_spi_portB:
			CLOCK_EnableClock(kCLOCK_PortB);
			break;
	   case freertos_spi_portC:
		   CLOCK_EnableClock(kCLOCK_PortC);
		   break;
	   case freertos_spi_portD:
		   CLOCK_EnableClock(kCLOCK_PortD);
		   break;
	   case freertos_spi_portE:
		   CLOCK_EnableClock(kCLOCK_PortE);
		   break;
	}

	PORT_SetPinMux(freertos_spi_get_port_base(config.port), config.miso_pin, config.pin_mux);
	PORT_SetPinMux(freertos_spi_get_port_base(config.port), config.mosi_pin, config.pin_mux);
	PORT_SetPinMux(freertos_spi_get_port_base(config.port), config.clk_pin, config.pin_mux);
	PORT_SetPinMux(freertos_spi_get_port_base(config.port), config.cs_pin, config.pin_mux);


	fsl_spi_config.whichCtar = kDSPI_Ctar0;
	fsl_spi_config.ctarConfig.baudRate = config.baudRate;
	fsl_spi_config.ctarConfig.bitsPerFrame = 8;
	fsl_spi_config.ctarConfig.cpol = kDSPI_ClockPolarityActiveHigh;
	fsl_spi_config.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
	fsl_spi_config.ctarConfig.direction = kDSPI_MsbFirst;
	fsl_spi_config.ctarConfig.pcsToSckDelayInNanoSec = 1000000000U / fsl_spi_config.ctarConfig.baudRate ;
	fsl_spi_config.ctarConfig.lastSckToPcsDelayInNanoSec = 1000000000U / fsl_spi_config.ctarConfig.baudRate ;
	fsl_spi_config.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / fsl_spi_config.ctarConfig.baudRate ;
	fsl_spi_config.whichPcs = kDSPI_Pcs0;
	fsl_spi_config.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
	fsl_spi_config.enableContinuousSCK = false;
	fsl_spi_config.enableRxFifoOverWrite = false;
	fsl_spi_config.enableModifiedTimingFormat = false;
	fsl_spi_config.samplePoint = kDSPI_SckToSin0Clock;

	if(freertos_spi0 == config.spi_number)
	{
		DSPI_MasterInit(freertos_spi_get_spi_base(freertos_spi0), &fsl_spi_config, CLOCK_GetFreq(DSPI0_CLK_SRC));
		NVIC_SetPriority(SPI0_IRQn,6);
	}
	else
	{
		DSPI_MasterInit(freertos_spi_get_spi_base(freertos_spi1), &fsl_spi_config, CLOCK_GetFreq(DSPI1_CLK_SRC));
		NVIC_SetPriority(SPI1_IRQn,6);
	}

	DSPI_MasterTransferCreateHandle(
			freertos_spi_get_spi_base(config.spi_number),
			&freertos_spi_handles[config.spi_number].fsl_spi_handle,
			fsl_spi_callback,
			NULL);

	 retval = freertos_spi_sucess;
//
	 return retval;
}

freertos_spi_flag_t freertos_spi_transfer(freertos_spi_number_t spi_number, uint8_t * bufferTX, uint8_t * bufferRX, uint16_t lenght)
{
	freertos_spi_flag_t flag = freertos_spi_fail;
	dspi_transfer_t xfer;

	xfer.txData = bufferTX;
    xfer.rxData = bufferRX;
	xfer.dataSize = lenght;
    xfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous;;

	xSemaphoreTake(freertos_spi_handles[spi_number].mutex_tx, portMAX_DELAY);

	// UART_TransferSendNonBlocking(freertos_uart_get_uart_base(uart_number), &freertos_uart_handles[uart_number].fsl_uart_handle, &xfer);
    DSPI_MasterTransferNonBlocking (freertos_spi_get_spi_base(spi_number), &freertos_spi_handles[spi_number].fsl_spi_handle, &xfer );

	xSemaphoreTake(freertos_spi_handles[spi_number].tx_sem, portMAX_DELAY);

	xSemaphoreGive(freertos_spi_handles[spi_number].mutex_tx);

	flag = freertos_spi_sucess;

	return flag;
}

//freertos_uart_flag_t freertos_uart_receive(freertos_uart_number_t uart_number, uint8_t * buffer, uint16_t lenght)
//{
//	freertos_uart_flag_t flag = freertos_uart_fail;
//
//	uart_transfer_t xfer;
//
//	xfer.data = buffer;
//	xfer.dataSize = lenght;
//
//	xSemaphoreTake(freertos_uart_handles[uart_number].mutex_rx, portMAX_DELAY);
//
//	UART_TransferReceiveNonBlocking(freertos_uart_get_uart_base(uart_number), &freertos_uart_handles[uart_number].fsl_uart_handle, &xfer, NULL);
//
//	xSemaphoreTake(freertos_uart_handles[uart_number].rx_sem, portMAX_DELAY);
//
//	xSemaphoreGive(freertos_uart_handles[uart_number].mutex_rx);
//
//	flag = freertos_uart_sucess;
//
//	return flag;
//}

static void fsl_spi_callback(SPI_Type *base, dspi_master_handle_t *handle, status_t status, void *userData)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if (SPI0 == base)
	{
		xSemaphoreGiveFromISR(freertos_spi_handles[freertos_spi0].tx_sem, &xHigherPriorityTaskWoken);
	}
	else
	{
		xSemaphoreGiveFromISR(freertos_spi_handles[freertos_spi1].tx_sem, &xHigherPriorityTaskWoken);
	}

	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

static inline PORT_Type * freertos_spi_get_port_base(freertos_spi_port_t port)
{
 PORT_Type * port_base = PORTA;

 switch(port)
 {
   case freertos_spi_portA:
     port_base = PORTA;
     break;
   case freertos_spi_portB:
     port_base = PORTB;
     break;
   case freertos_spi_portC:
     port_base = PORTC;
     break;
   case freertos_spi_portD:
     port_base = PORTD;
     break;
   case freertos_spi_portE:
     port_base = PORTE;
     break;
 }

  return port_base;
}

static inline SPI_Type * freertos_spi_get_spi_base(freertos_spi_number_t spi_number)
{
	SPI_Type * retval = SPI0;

	switch(spi_number)
	{
   case freertos_spi0:
     retval = SPI0;
     break;
   case freertos_spi1:
     retval = SPI1;
     break;
	}

	return retval;
}


