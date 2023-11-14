/*
 * MDMA_Program.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Khaled Shehab
 */

#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/MDMA_Private.h"
#include "../include/MDMA_Config.h"
#include "../include/MDMA_Interface.h"



static void (*DMA2_S0_Ptr[8])(void) = {NULLPTR};

void DMA2_Init(u8 Copy_u8StreamID)
{
	CLR_BIT(DMA2->S[Copy_u8StreamID].CR,WRITE_ENABLE);
	DMA2->S[Copy_u8StreamID].CR = (MEMORY_INCREMENT_MODE<<10) | (PERIPHERAL_INCREMENT_MODE<<9)
								  | (MEM_TO_MEM<<6)           | (TRANSFER_COMPLETE_INTERRUPT<<4);
	DMA2->S[Copy_u8StreamID].FCR = (DIRECT_MODE<<2) | (FIFO_SEL) ;
}

void DMA2_SetStreamConfiguration(DMA_StreamID_t Copy_enuStreamID,
								 DMA_ChannelID_t Copy_enuChannelID,
								 u32 *Copy_pu32SourceAddress,
								 u32 *Copy_pu32DestinationAddress,
								 DMA_ElementSize_t Copy_enuElementSize,
								 u16 Copy_u16BlockSize)
{
	CLR_BIT(DMA2->S[Copy_enuStreamID].CR,WRITE_ENABLE);
	DMA2->S[Copy_enuStreamID].CR |= (Copy_enuChannelID<<25);
	DMA2->S[Copy_enuStreamID].CR |= ((Copy_enuElementSize<<13) | (Copy_enuElementSize<<11));
	DMA2->S[Copy_enuStreamID].NDTR= Copy_u16BlockSize; //Block Size 0 -----> 2^16
	DMA2->S[Copy_enuStreamID].PAR = (u32)Copy_pu32SourceAddress;
	DMA2->S[Copy_enuStreamID].M0AR= (u32)Copy_pu32DestinationAddress;

}

void DMA2_SetCallBack(DMA_StreamID_t Copy_enuStreamID,void(*ptr)(void))
{
	if(ptr!=NULLPTR)
	{
		DMA2_S0_Ptr[Copy_enuStreamID] = ptr;
	}
	else
	{
		/* Nothing */
	}
}

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA2_S0_Ptr[0]!=NULLPTR)
	{
		DMA2_S0_Ptr[0]();
		DMA2->LIFCR |= (1<<CFEIF0) | (1<<CDMEIF0) | (1<<CTEIF0) | (1<<CHTIF0) | (1<<CTCIF0);
	}
	else
	{
		/* Nothing */
	}
}

void DMA2_EnableStream(DMA_StreamID_t Copy_enuStreamID)
{
	switch(Copy_enuStreamID)
	{
	case 0:
		DMA2->LIFCR |= (1<<CFEIF0) | (1<<CDMEIF0) | (1<<CTEIF0) | (1<<CHTIF0) | (1<<CTCIF0);
		break;
	case 1:
		DMA2->LIFCR |= (1<<CFEIF1) | (1<<CDMEIF1) | (1<<CTEIF1) | (1<<CHTIF1) | (1<<CTCIF1);
		break;
	case 2:
		DMA2->LIFCR |= (1<<CFEIF2) | (1<<CDMEIF2) | (1<<CTEIF2) | (1<<CHTIF2) | (1<<CTCIF2);
		break;
	case 3:
		DMA2->LIFCR |= (1<<CFEIF3) | (1<<CDMEIF3) | (1<<CTEIF3) | (1<<CHTIF3) | (1<<CTCIF3);
		break;
	case 4:
		DMA2->LIFCR |= (1<<CFEIF4) | (1<<CDMEIF4) | (1<<CTEIF4) | (1<<CHTIF4) | (1<<CTCIF4);
		break;
	case 5:
		DMA2->LIFCR |= (1<<CFEIF5) | (1<<CDMEIF5) | (1<<CTEIF5) | (1<<CHTIF5) | (1<<CTCIF5);
		break;
	case 6:
		DMA2->LIFCR |= (1<<CFEIF6) | (1<<CDMEIF6) | (1<<CTEIF6) | (1<<CHTIF6) | (1<<CTCIF6);
		break;
	case 7:
		DMA2->LIFCR |= (1<<CFEIF7) | (1<<CDMEIF7) | (1<<CTEIF7) | (1<<CHTIF7) | (1<<CTCIF7);
		break;
	default:
		break;
	}
	SET_BIT(DMA2->S[Copy_enuStreamID].CR,WRITE_ENABLE);
}


