#ifndef CONFIG_AND_SPI_H
#define CONFIG_AND_SPI_H

#include <bcm2835.h>

/* The Raspberry Pi GPIO pins used for SPI are:

    P1-19 (MOSI)
    P1-21 (MISO)
    P1-23 (CLK)
    P1-24 (CE0)
    P1-26 (CE1)

https://www.airspayce.com/mikem/bcm2835/index.html */

// PINS INFO
#define CS_PIN    8    // 24 → BCM 8
#define RESET_PIN 17   // 11 → BCM 17
#define SCLK_PIN  11   // 23 → BCM 11 * DECLARED AND CONNECTED TO IT BUT NOT USED IN CODE*
#define SDO_PIN   9    // 21 → BCM 9  (MISO) * DECLARED AND CONNECTED TO IT BUT NOT USED IN CODE *
#define SDI_PIN   10   // 19 → BCM 10 (MOSI) * DECLARED AND CONNECTED TO IT BUT NOT USED IN CODE*

// Display variables
#define X_ORIGIN 0
#define Y_ORIGIN 0
#define X_SIZE 240
#define Y_SIZE 320
#define BUFFER_SIZE 512

void writeCMD(uint8_t reg);
void writeDAT(uint16_t value);
void writeREG(uint8_t reg, uint16_t value);
uint16_t readREG(uint8_t reg);
void tftReset(void);

#endif // CONFIG_AND_SPI_H