/*
 * Iris_if_sub.c
 *
 *  Created on: Jan 8, 2021
 *      Author: Keshikan
 *    Modified: yswallow
 */


#include "Iris_if_Sub.h"

uint8_t subVRAM[IRIS_SUB_VRAM_SIZ * 2];


void sendCmdSub(uint8_t dat)
{
	IRIS_CONFIG->BSRR = (uint32_t)IRIS_SUB_DCX_PIN << 16;

	IRIS_DATABUS->ODR = (uint32_t)dat;

	IRIS_CONFIG->BSRR = (uint32_t)IRIS_SUB_WRX_PIN << 16;

	//greater than 15ns (c.f. 18.3. AC Characteristics [twrl])
	asm("NOP");asm("NOP");//asm("NOP");asm("NOP");

	IRIS_CONFIG->BSRR = IRIS_SUB_WRX_PIN;
}

void sendDatSub(uint8_t dat)
{
	IRIS_CONFIG->BSRR = IRIS_SUB_DCX_PIN;

	IRIS_DATABUS->ODR = (uint32_t)dat;

	IRIS_CONFIG->BSRR = (uint32_t)IRIS_SUB_WRX_PIN << 16;

	//greater than 15ns (c.f. 18.3. AC Characteristics [twrl])
	asm("NOP");asm("NOP");//asm("NOP");asm("NOP");

	IRIS_CONFIG->BSRR = IRIS_SUB_WRX_PIN;
}

void clearScrSub()
{
	sendCmdSub(0x2C);

	for(uint32_t i=0; i<(IRIS_SUB_SIZ_X * IRIS_SUB_SIZ_Y); i++){
		sendDatSub(0xFF);
	}

	for(uint32_t i=0; i<(IRIS_SUB_SIZ_X * IRIS_SUB_SIZ_Y); i++){
		sendDatSub(0x00);
	}
}

void initIrisSub()
{
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_SUB_WRX_PIN, 1);
	HAL_Delay(100);
	//Set EXTC: turn on external command
	sendCmdSub(0xEF);
	sendDatSub(0x03);
	sendDatSub(0x80);
	sendDatSub(0x92);

	sendCmdSub(0xCF);
	sendDatSub(0x00);
	sendDatSub(0xC1);
	sendDatSub(0x30);

	sendCmdSub(0xED);
	sendDatSub(0x64);
	sendDatSub(0x03);
	sendDatSub(0x12);
	sendDatSub(0x81);

	sendCmdSub(0xE8);
	sendDatSub(0x85);
	sendDatSub(0x00);
	sendDatSub(0x78);

	sendCmdSub(0xF7);
	sendDatSub(0x20);

	sendCmdSub(0xEA);
	sendDatSub(0x00);
	sendDatSub(0x00);


	//Column Address Set
	sendCmdSub(0x2A);
	sendDatSub(0x00);
	sendDatSub(0x00);
	sendDatSub(0x00);
	sendDatSub(0x81);

	//Page Address Set
	sendCmdSub(0x2B);
	sendDatSub(0x00);
	sendDatSub(0x00);
	sendDatSub(0x00);
	sendDatSub(0x83);

	//Memory Access Control: setting scanning direction.
	sendCmdSub(0x36);
	sendDatSub(0xC8);

	//Power Control 1
	sendCmdSub(0xC0);
	sendDatSub(0x23);

	//Power Control 2
	sendCmdSub(0xC1);
	sendDatSub(0x10);

	//VCOM Control
	sendCmdSub(0xC5);
	sendDatSub(0x3E);
	sendDatSub(0x28);

	sendCmdSub(0xC7);
	sendDatSub(0x86);

	//Pixel Format Set
	sendCmdSub(0x3A);
	sendDatSub(0x55);//RGB565 65K color

	//Frame Rate Control
	sendCmdSub(0xB1);
	sendDatSub(0x00);
	sendDatSub(0x13);

	sendCmdSub(0xF2);
	sendDatSub(0x00);

	sendCmdSub(0x26);
	sendDatSub(0x01);

	//Positive Gamma Correction
	sendCmdSub(0xE0);
	sendDatSub(0x00);
	sendDatSub(0x1C);
	sendDatSub(0x21);
	sendDatSub(0x02);
	sendDatSub(0x11);
	sendDatSub(0x07);
	sendDatSub(0x3D);
	sendDatSub(0x79);
	sendDatSub(0x4B);
	sendDatSub(0x07);
	sendDatSub(0x0F);
	sendDatSub(0x0C);
	sendDatSub(0x1B);
	sendDatSub(0x1F);
	sendDatSub(0x0F);

	//Negative Gamma Correction
	sendCmdSub(0xE1);
	sendDatSub(0x00);
	sendDatSub(0x1C);
	sendDatSub(0x20);
	sendDatSub(0x04);
	sendDatSub(0x0F);
	sendDatSub(0x04);
	sendDatSub(0x33);
	sendDatSub(0x45);
	sendDatSub(0x42);
	sendDatSub(0x04);
	sendDatSub(0x0C);
	sendDatSub(0x0A);
	sendDatSub(0x22);
	sendDatSub(0x29);
	sendDatSub(0x0F);

	//Sleep Out
	sendCmdSub(0x11);
	HAL_Delay(130);//greater than 120ms

	sendCmdSub(0x29);
	HAL_Delay(10);

	irisClearDispSub();
	clearScrSub();

}


void irisClearDispSub()
{
	for(uint32_t i=0; i<IRIS_SUB_VRAM_SIZ * 2; i++){
		subVRAM[i] = 0x00;
	}
}

void irisDrawDotSub(uint16_t x, uint16_t y, uint16_t color) {
	uint32_t pos = y * IRIS_SUB_SIZ_X + x;
	if(pos>IRIS_SUB_VRAM_SIZ) {
		return;
	}
	subVRAM[pos*2] = (color & 0xFF00) >> 8;
	subVRAM[pos*2+1] = (uint8_t)(color & 0x00FF);
}


void irisUpdateSub()
{
	//Write
	sendCmdSub(0x2C);
	for(uint32_t i=0; i<IRIS_SUB_SIZ_X * IRIS_SUB_SIZ_Y * 2; i++){
		sendDatSub(subVRAM[i]);
	}
}
