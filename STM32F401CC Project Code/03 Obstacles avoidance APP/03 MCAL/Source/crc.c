/*******************************************************************************
 * @file    crc.c
 * @author  Mina Magdy
 * @email   mina.magdy.aziz.2698@gmail.com
 * @date    1 Nov 2023
 *          
 * @note    
 *
 *******************************************************************************/

/* Includes */

#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/MRCC_interface.h"


#include "../include/crc.h"
#include "../include/crc_Private.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup crc
 * @brief
 * @{
 */

/**
 * @defgroup crc_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_private_constants
 * @{
 */

/**
 * @brief   CRC-32 (Ethernet) Generator Polynomial
 */

/**
 * @brief   Calculates CRC32 for given bytes array using look up table
 * @note
 * @param
 * @retval  CRC32
 */
u32 CRC_CalculateCRC32_HW(const u32 * wordArray,
    const u8 arraySize)
{
  /* CRC32 value */
  u32 crc = 0;

  /* Check null pointer */
  if(NULL != wordArray)
  {
    

    /* Process all bytes */
    for(u32 byte_idx = 0; byte_idx < arraySize; ++byte_idx)
    {
      /* Write data register */
      CRC->DR = (u32)(wordArray[byte_idx]);
    }

    /* Read CRC data */
    crc = CRC->DR;
  }
  else
  {
    /* Null pointer detected */
  }

  /* Return */
  return crc;
}

/**
 * @brief   Initialization function
 * @note
 * @param
 * @retval  CRC32
 */
void CRC_Init(void)
{
  /* Enable CRC Clock */
	MRCC_voidEnable_Peripheral(RCC_AHB1, RCC_AHB1_CRCEN);
}



void CRC_Reset(void)
{
	/* Reset CRC hardware */
    CRC->CR = CRC_CR_RESET;
}


/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
