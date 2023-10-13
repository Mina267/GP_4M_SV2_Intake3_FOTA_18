/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MDMA                                                */
/* Version : 1.0                                                 */
/* Date    : 23 Sep 2023                                         */
/*****************************************************************/
#ifndef MDMA_PRIVATE_H_
#define MDMA_PRIVATE_H_

#define MDMA1_BASE_ADDRESS   (0x40026000)
#define MDMA2_BASE_ADDRESS   (0x40026400)

typedef struct
{
	u32 CR;
	u32 NDTR;
	u32 PAR;
	u32 M0AR;
	u32 M1AR;
	u32 FCR;
}DMA_Stream_t;

typedef struct
{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;
	DMA_Stream_t S[8];

}MDMA_t;


#define DMA1  ((volatile MDMA_t*)MDMA1_BASE_ADDRESS)
#define DMA2  ((volatile MDMA_t*)MDMA2_BASE_ADDRESS)

/* CR register bits */
#define WRITE_ENABLE        0

/* MEMORY_INCREMENT_MODE */
#define MEM_INC_FIXED       0
#define MEM_INC_INCREASE    1

/* PERIPHERAL_INCREMENT_MODE */
#define PERI_INC_FIXED      0
#define PERI_INC_INCREASE   1

/* DATA_TRANSFER_DIRECTION */
#define PERI_TO_MEM         0
#define MEM_TO_PERI         1
#define MEM_TO_MEM          2

/* TRANSFER_COMPLETE_INTERRUPT */
#define TC_DISABLE          0
#define TC_ENABLE           1

/* DIRECT_MODE */
#define DM_ENABLE           0
#define DM_DISABLE          1

/* FIFO_SEL */
#define FULL_FIFO_1_TO_4    0
#define FULL_FIFO_2_TO_4    1
#define FULL_FIFO_3_TO_4    2
#define FULL_FIFO_4_TO_4    3

/* LIFCR Register Bits */
#define CFEIF0              0
#define CDMEIF0             2
#define CTEIF0              3
#define CHTIF0              4
#define CTCIF0              5
#define CFEIF1              6
#define CDMEIF1             8
#define CTEIF1              9
#define CHTIF1              10
#define CTCIF1              11
#define CFEIF2              16
#define CDMEIF2             18
#define CTEIF2              19
#define CHTIF2              20
#define CTCIF2              21
#define CFEIF3              22
#define CDMEIF3             24
#define CTEIF3              25
#define CHTIF3              26
#define CTCIF3              27

/* HIFCR Register Bits */
#define CFEIF4              0
#define CDMEIF4             2
#define CTEIF4              3
#define CHTIF4              4
#define CTCIF4              5
#define CFEIF5              6
#define CDMEIF5             8
#define CTEIF5              9
#define CHTIF5              10
#define CTCIF5              11
#define CFEIF6              16
#define CDMEIF6             18
#define CTEIF6              19
#define CHTIF6              20
#define CTCIF6              21
#define CFEIF7              22
#define CDMEIF7             24
#define CTEIF7              25
#define CHTIF7              26
#define CTCIF7              27


#endif
