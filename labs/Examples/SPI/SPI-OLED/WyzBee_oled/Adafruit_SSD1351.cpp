/***************************************************
  This is a library for the 1.5" & 1.27" 16-bit Color OLEDs
  with SSD1331 driver chip

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1431
  ------> http://www.adafruit.com/products/1673

  These displays use SPI to communicate, 4 or 5 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "glcdfont.c"
#include "SPI_OLED.h"
#include "mfs.h"
#include  <WyzBee_spi.h>
#include  <WyzBee_gpio.h>
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

#define SPI_MODE3 3



void delayMicroseconds(uint32_t _delay) // microsecond delay
{
	uint32_t x;
	for(x=0;x<100*_delay;x++);
}
void delay(uint32_t _delay)  // delay
{
	uint32_t x;
	for(x=0;x<100*_delay;x++);
}





/********************************** low level pin interface */

inline void Adafruit_SSD1351::spiwrite(uint8_t c)
{

	WyzBeeSpi_Write(c);
	delayMicroseconds(1);
	return;
}


void Adafruit_SSD1351::writeCommand(uint8_t c)
{

	WyzBeeGpio_Put(GPIO_PWM2,GPIO_LOW);//DC
	spiwrite(c);
}


void Adafruit_SSD1351::writeData(uint8_t c)
{
	WyzBeeGpio_Put(GPIO_PWM2,GPIO_HIGH); //DC
	spiwrite(c);
}

/***********************************/

void Adafruit_SSD1351::goTo(int x, int y) {
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;

	// set x and y coordinate
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(SSD1351WIDTH-1);

	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(SSD1351HEIGHT-1);

	writeCommand(SSD1351_CMD_WRITERAM);
}

uint16_t Adafruit_SSD1351::Color565(uint8_t r, uint8_t g, uint8_t b) {
	uint16_t c;
	c = r >> 3;
	c <<= 6;
	c |= g >> 2;
	c <<= 5;
	c |= b >> 3;

	return c;
}

void Adafruit_SSD1351::fillScreen(uint16_t fillcolor) {
	fillRect(0, 0, SSD1351WIDTH, SSD1351HEIGHT, fillcolor);
}

/**************************************************************************/
/*!
    @brief  Draws a filled rectangle using HW acceleration
 */
/**************************************************************************/
void Adafruit_SSD1351::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t fillcolor)
{

	// Bounds check
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
		return;

	// Y bounds check
	if (y+h > SSD1351HEIGHT)
	{
		h = SSD1351HEIGHT - y - 1;
	}

	// X bounds check
	if (x+w > SSD1351WIDTH)
	{
		w = SSD1351WIDTH - x - 1;
	}

	// set location
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(x+w-1);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(y+h-1);
	// fill!
	writeCommand(SSD1351_CMD_WRITERAM);

	for (uint16_t i=0; i < w*h; i++) {
		writeData(fillcolor >> 8);
		writeData(fillcolor);
	}
}

void Adafruit_SSD1351::drawFastVLine(int16_t x, int16_t y,
		int16_t h, uint16_t color) {
	// Bounds check
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
		return;

	// X bounds check
	if (y+h > SSD1351HEIGHT)
	{
		h = SSD1351HEIGHT - y - 1;
	}

	if (h < 0) return;

	// set location
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(x);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(y+h-1);
	// fill!
	writeCommand(SSD1351_CMD_WRITERAM);

	for (uint16_t i=0; i < h; i++) {
		writeData(color >> 8);
		writeData(color);
	}
}



void Adafruit_SSD1351::drawFastHLine(int16_t x, int16_t y,
		int16_t w, uint16_t color) {
	// Bounds check
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT))
		return;

	// X bounds check
	if (x+w > SSD1351WIDTH)
	{
		w = SSD1351WIDTH - x - 1;
	}

	if (w < 0) return;

	// set location
	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(x);
	writeData(x+w-1);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(y);
	writeData(y);
	// fill!
	writeCommand(SSD1351_CMD_WRITERAM);

	for (uint16_t i=0; i < w; i++) {
		writeData(color >> 8);
		writeData(color);
	}
}



void Adafruit_SSD1351::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) return;
	if ((x < 0) || (y < 0)) return;

	goTo(x, y);

	// setup for data
	FM4_GPIO->PDOR4_f.P40 = TRUE;   // set to write data. DC

	spiwrite(color >> 8);
	spiwrite(color);
}

void Adafruit_SSD1351::begin(void) {


	WyzBeeGpio_InitOut(GPIO_PWM2,GPIO_HIGH); //DC
	FM4_GPIO->ADE=0;
	WyzBeeGpio_Put(GPIO_SPI2CS,GPIO_LOW);// P53 	CS LOW
	WyzBeeGpio_Init(GPIO_PWM1,GPIO_OUTPUT,GPIO_HIGH);//P41 reset
	WyzBeeGpio_Put(GPIO_PWM1,GPIO_HIGH);
	delay(500);
	WyzBeeGpio_Put(GPIO_PWM1,GPIO_LOW);
	delay(500);
	WyzBeeGpio_Put(GPIO_PWM1,GPIO_HIGH);
	delay(500);


	// Initialization Sequence
	writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
	writeData(0x12);
	writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
	writeData(0xB1);

	writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

	writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
	writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)

	writeCommand(SSD1351_CMD_MUXRATIO);
	writeData(127);

	writeCommand(SSD1351_CMD_SETREMAP);
	writeData(0x74);

	writeCommand(SSD1351_CMD_SETCOLUMN);
	writeData(0x00);
	writeData(0x7F);
	writeCommand(SSD1351_CMD_SETROW);
	writeData(0x00);
	writeData(0x7F);

	writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
	if (SSD1351HEIGHT == 96)
	{
		writeData(96);
	}
	else
	{
		writeData(0);
	}

	writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
	writeData(0x0);

	writeCommand(SSD1351_CMD_SETGPIO);
	writeData(0x00);

	writeCommand(SSD1351_CMD_FUNCTIONSELECT);
	writeData(0x01); // internal (diode drop)
	writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
	writeCommand(0x32);

	writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
	writeCommand(0x05);

	writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

	writeCommand(SSD1351_CMD_CONTRASTABC);
	writeData(0xC8);
	writeData(0x80);
	writeData(0xC8);

	writeCommand(SSD1351_CMD_CONTRASTMASTER);
	writeData(0x0F);

	writeCommand(SSD1351_CMD_SETVSL );
	writeData(0xA0);
	writeData(0xB5);
	writeData(0x55);

	writeCommand(SSD1351_CMD_PRECHARGE2);
	writeData(0x01);

	writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel
}

void  Adafruit_SSD1351::invert(boolean v) {
	if (v) {
		writeCommand(SSD1351_CMD_INVERTDISPLAY);
	} else {
		writeCommand(SSD1351_CMD_NORMALDISPLAY);
	}
}

/********************************* low level pin initialization */

Adafruit_SSD1351::Adafruit_SSD1351(void) : Adafruit_GFX(SSD1351WIDTH, SSD1351HEIGHT) {

}

