// Pin definitions for TotTag Revision D

#pragma once

#include "nrf_gpio.h"

#ifndef DEVICE_NAME
#define DEVICE_NAME "tottag"
#endif

// BLE Address used to advertise
#define BLE_FLASH_ADDRESS 0x0003fff8


// Battery monitor
#define CARRIER_BATTERY_MONITOR NRF_GPIO_PIN_MAP(0,30)

// GPIOs
#define CARRIER_GPIO_0      NRF_GPIO_PIN_MAP(0,27)
#define CARRIER_GPIO_1      NRF_GPIO_PIN_MAP(0,26)

// LEDs
#define CARRIER_LED_RED     NRF_GPIO_PIN_MAP(0,5)
#define CARRIER_LED_BLUE    NRF_GPIO_PIN_MAP(0,4)
#define CARRIER_LED_GREEN   NRF_GPIO_PIN_MAP(0,6)

// SPI bus
#define CARRIER_SPI_SCLK    NRF_GPIO_PIN_MAP(0,17)
#define CARRIER_SPI_MISO    NRF_GPIO_PIN_MAP(0,15)
#define CARRIER_SPI_MOSI    NRF_GPIO_PIN_MAP(0,13)

// SD Card
#define CARRIER_CS_SD       NRF_GPIO_PIN_MAP(0,18)
#define CARRIER_SD_ENABLE   NRF_GPIO_PIN_MAP(0,14)
#define CARRIER_SD_DETECT   NRF_GPIO_PIN_MAP(1,0)

// Accelerometer
#define CARRIER_CS_ACC      NRF_GPIO_PIN_MAP(0,16)
#define CARRIER_ACC_INT1    NRF_GPIO_PIN_MAP(0,22)
#define CARRIER_ACC_INT2    NRF_GPIO_PIN_MAP(0,24)

// I2C connection to module
#define CARRIER_I2C_SCL     NRF_GPIO_PIN_MAP(1,9)
#define CARRIER_I2C_SDA     NRF_GPIO_PIN_MAP(0,12)

// Interrupt line to module (STM controller)
#define CARRIER_INTERRUPT_MODULE    NRF_GPIO_PIN_MAP(0,8)

// UART serial connection (to FTDI)
#define CARRIER_UART_RX     NRF_GPIO_PIN_MAP(0,7)
#define CARRIER_UART_TX     NRF_GPIO_PIN_MAP(0,11)
#define CARRIER_UART_RST    NRF_GPIO_PIN_MAP(1,8)
