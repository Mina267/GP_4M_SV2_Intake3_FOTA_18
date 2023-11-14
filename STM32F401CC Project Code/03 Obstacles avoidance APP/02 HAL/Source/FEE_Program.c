/*
 * FEE_Program.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Khaled shehab
 */

#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/FEE_Private.h"
#include "../include/FEE_Config.h"
#include "../include/FEE_Interface.h"

#include "../include/MFDI_Interface.h"

/* To specify write position */
static u16 Write_Position = 0;

/* To get write position after any reset happen */
void FEE_voidSetInit(void)
{
	/* Initially write position equal to zero */
	Write_Position=0;

	/* loop find index for last data written */
	u16 Counter;
	for(Counter=(FEE_SECTOR_SIZE-2);Counter>(FEE_SECTOR_SIZE/2);Counter-=2)
	{
		if((*(volatile u16*)(FEE_BASE_ADDRESS+Counter)) != FEE_EMPTY_DATA)
			Write_Position++;
		else
			break;
	}
}

/* To write data in flash */
void FEE_voidSetData(u16 data)
{
	/* Check if Sector is full */
	if(Write_Position == ((FEE_SECTOR_SIZE/4)-1)) //check if write position equal to half sector size for flashing with 2 bytes
	{
		/* Get last data written if FEE Sector was full */
		u16 Recovery = *(volatile u16*)(FEE_BASE_ADDRESS+((Write_Position-1)*2));

		/* Erase Sector */
		MFDI_voidSectorErase(FEE_SECTOR_NUMBER);

		/* Add last data was written */
		MFDI_voidFlashWrite(FEE_BASE_ADDRESS, &Recovery, 1);

		/* Save current position in the last 2 bytes of FEE sector */
		/* Address for last 2 bytes in FEE sector = base Address + (Fee sector size - (write position*2)) */
		Write_Position = 1;
		MFDI_voidFlashWrite((FEE_BASE_ADDRESS+(FEE_SECTOR_SIZE-(Write_Position*2))), &Write_Position, 1);
	}
	else
	{
		/* Do Nothing */
	}
	/* With same sequence write data in it's position then write index for this data in reverse way in FEE sector */
	u16 *ptr = &data;
	MFDI_voidFlashWrite(FEE_BASE_ADDRESS+(Write_Position*2), ptr, 1);
	Write_Position++;
	MFDI_voidFlashWrite((FEE_BASE_ADDRESS+(FEE_SECTOR_SIZE-(Write_Position*2))), &Write_Position, 1);

}

/* read data from FEE sector */
u16 FEE_u16GetData(void)
{
	u16 data;
	/* Check if no data stored */
	if(Write_Position == 0)
	{
		data = FEE_EMPTY_DATA;
	}
	else
	{
	/* To get current position in FEE sector */
	/* Adding (write position-1)*2 to base address --> as we write and read with 2 bytes */
	data = *(volatile u16*)(FEE_BASE_ADDRESS+((Write_Position-1)*2));
	}
	return data;
}
