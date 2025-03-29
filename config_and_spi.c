#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "include/config_and_spi.h"

// Display variables
const int X_origin = 0;
const int Y_origin = 0;
const int X_size = 240;
const int Y_size = 320;

// SPI functions
// SPI_START: 0x70, SPI_DATA: 0x72
void writeCMD(uint8_t reg) {
    bcm2835_gpio_write(CS_PIN, LOW);
    bcm2835_spi_transfer(0x70); // Inicio, escritura, índice
    bcm2835_spi_transfer(reg);
    bcm2835_gpio_write(CS_PIN, HIGH);
}

void writeDAT(uint16_t value) {
    bcm2835_gpio_write(CS_PIN, LOW);
    bcm2835_spi_transfer(0x72); // Inicio, escritura, dato
    bcm2835_spi_transfer((uint8_t)(value >> 8));   // Byte alto
    bcm2835_spi_transfer((uint8_t)(value & 0xFF));   // Byte bajo
    bcm2835_gpio_write(CS_PIN, HIGH);
}

void writeREG(uint8_t reg, uint16_t value) {
    writeCMD(reg);
    writeDAT(value);
}

uint16_t readREG(uint8_t reg) {
    writeCMD(reg);
    return 0x0000;
}

// TFT reboot and initialization secuence
void tftReset() {
    bcm2835_gpio_write(RESET_PIN, LOW);
    bcm2835_delay(500); // 250 ms
    bcm2835_gpio_write(RESET_PIN, HIGH);
    bcm2835_delay(200);   // 6 ms

    uint16_t driverCode = readREG(0x00); // Unused

    // Init sec
    writeREG(0xEA, 0x0000);    // Reset Power Control 1 
    writeREG(0xEB, 0x0020);    // Power Control 2   
    writeREG(0xEC, 0x000C);    // Power Control 3   
    writeREG(0xED, 0x00C4);    // Power Control 4   
    writeREG(0xE8, 0x0040);    // Source OPON_N     
    writeREG(0xE9, 0x0038);    // Source OPON_I     
    writeREG(0xF1, 0x0001);                
    writeREG(0xF2, 0x0010);                 
    writeREG(0x27, 0x00A3);    // Display Control 2 

    // Boot sec
    writeREG(0x1B, 0x001B);    // Power Control 2 
    writeREG(0x1A, 0x0001);    // Power Control 1
    writeREG(0x24, 0x002F);    // Vcom Control 2
    writeREG(0x25, 0x0057);    // Vcom Control 3                       
    writeREG(0x23, 0x008D);    // Vcom Control 1
  
    // Gamma adjustments
    writeREG(0x40, 0x00);
    writeREG(0x41, 0x00);
    writeREG(0x42, 0x01);
    writeREG(0x43, 0x13);
    writeREG(0x44, 0x10);
    writeREG(0x45, 0x26);
    writeREG(0x46, 0x08);
    writeREG(0x47, 0x51);
    writeREG(0x48, 0x02);
    writeREG(0x49, 0x12);
    writeREG(0x4A, 0x18);
    writeREG(0x4B, 0x19);
    writeREG(0x4C, 0x14);
    writeREG(0x50, 0x19);
    writeREG(0x51, 0x2F);
    writeREG(0x52, 0x2C);
    writeREG(0x53, 0x3E);
    writeREG(0x54, 0x3F);
    writeREG(0x55, 0x3F);
    writeREG(0x56, 0x2E);
    writeREG(0x57, 0x77);
    writeREG(0x58, 0x0B);
    writeREG(0x59, 0x06);
    writeREG(0x5A, 0x07);
    writeREG(0x5B, 0x0D);
    writeREG(0x5C, 0x1D);
    writeREG(0x5D, 0xCC);
  
    // Power + Oscilator 
    writeREG(0x18, 0x0036);      // OSC Control 1 
    writeREG(0x19, 0x0001);      // OSC Control 2
    writeREG(0x01, 0x0000);      // Display Mode Control
    writeREG(0x1F, 0x0088);      // Power Control 6
    bcm2835_delay(200);             
    writeREG(0x1F, 0x0080);      // Power Control 6              
    bcm2835_delay(200);                                      
    writeREG(0x1F, 0x0090);      // Power Control 6
    bcm2835_delay(200);             
    writeREG(0x1F, 0x00D0);      // Power Control 6
    bcm2835_delay(200);                                        
 
    // Appearance
    writeREG(0x17, 0x0005);      // Colmod 16Bit/Pixel
    writeREG(0x36, 0x0000);      // Panel Characteristic
    writeREG(0x28, 0x0038);      // Display Control 3        
    bcm2835_delay(800);                 
    writeREG(0x28, 0x003C);      // Display Control 3
    bcm2835_delay(100);             
    writeREG(0x16, 0x0008);      // Orientation
    writeREG(0x03, X_origin);    // Set Dimensions
    writeREG(0x02, X_origin >> 8);
    writeREG(0x05, (X_size - 1));
    writeREG(0x04, (X_size - 1) >> 8);
    writeREG(0x07, Y_origin);
    writeREG(0x06, Y_origin >> 8);
    writeREG(0x09, (Y_size - 1));
    writeREG(0x08, (Y_size - 1) >> 8);

    printf("TFT configuration end...\n\n");
}