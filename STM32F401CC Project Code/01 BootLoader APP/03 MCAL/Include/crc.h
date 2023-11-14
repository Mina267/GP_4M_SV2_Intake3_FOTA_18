/*******************************************************************************
 * @file    crc.h
 * @author  Mina Magdy
 * @email   mina.magdy.aziz.2698@gmail.com
 * @date    1 Nov 2023
 *          
 * @note    
 *
 *******************************************************************************/

/* Define to prevent recursive inclusion */
#ifndef __INC_CRC_H_
#define __INC_CRC_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif



/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @addtogroup crc
 * @{
 */

/**
 * @defgroup crc_exported_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup crc_exported_functions
 * @{
 */

u32 CRC_CalculateCRC32_HW(const u32 *wordArray, const u8 arraySize);
void CRC_Init(void);

void CRC_Reset(void);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /*__INC_CRC_H_ */
