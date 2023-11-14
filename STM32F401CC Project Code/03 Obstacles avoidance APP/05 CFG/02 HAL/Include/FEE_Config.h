/*
 * FEE_Config.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Khaled shehab
 */

#ifndef FEE_CONFIG_H_
#define FEE_CONFIG_H_

// FEE Sector configuration
#define FEE_SECTOR_NUMBER          1               //Sector 1 for FEE
#define FEE_BASE_ADDRESS           (0x08004000)    //Start address of FEE sector
#define FEE_SECTOR_SIZE            (16 * 1024)     //Size of FEE sector
#define FEE_EMPTY_DATA             (0xFFFF)        //Empty data in flash for 2 bytes

#endif
