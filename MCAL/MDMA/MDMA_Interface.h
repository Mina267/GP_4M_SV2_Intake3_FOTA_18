/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MDMA                                                */
/* Version : 1.0                                                 */
/* Date    : 23 Sep 2023                                         */
/*****************************************************************/
#ifndef MDMA_INTERFACE_H_
#define MDMA_INTERFACE_H_






/************** Stream ID ******************/
typedef enum
{
	DMA_STREAM0_ID = 0,
	DMA_STREAM1_ID = 1,
	DMA_STREAM2_ID = 2,
	DMA_STREAM3_ID = 3,
	DMA_STREAM4_ID = 4,
	DMA_STREAM5_ID = 5,
	DMA_STREAM6_ID = 6,
	DMA_STREAM7_ID = 7
}DMA_StreamID_t;

/**************** Channel ID ****************/
typedef enum
{
	DMA_CHANNEL_0 = 0,
	DMA_CHANNEL_1 = 1,
	DMA_CHANNEL_2 = 2,
	DMA_CHANNEL_3 = 3,
	DMA_CHANNEL_4 = 4,
	DMA_CHANNEL_5 = 5,
	DMA_CHANNEL_6 = 6,
	DMA_CHANNEL_7 = 7
}DMA_ChannelID_t;



/***************** Element Size **************/
typedef enum
{
	BYTE_8BIT       = 0,
	HALF_WORD_16BIT = 1,
	WORD_32BIT      = 2
}DMA_ElementSize_t;

/*****************************************************************************************/
/******************************* DMA APIs Prototypes *************************************/
/*****************************************************************************************/

/* initialization */
void MDMA2_Init(u8 Copy_u8StreamID);
/* Configuration of Streaming */
void MDMA2_SetStreamConfiguration(	DMA_StreamID_t Copy_enuStreamID,
									DMA_ChannelID_t Copy_enuChannelID,
									u32 *Copy_pu32SourceAddress,
									u32 *Copy_pu32DestinationAddress,
									DMA_ElementSize_t Copy_enuElementSize,
									u16 Copy_u16BlockSize);
/* Set callBack of interrupt Handler of DMA */
void MDMA2_SetCallBack(DMA_StreamID_t Copy_enuStreamID, void(*ptr)(void));
/* Enable Streaming */
void MDMA2_EnableStream(DMA_StreamID_t Copy_enuStreamID);



#endif
