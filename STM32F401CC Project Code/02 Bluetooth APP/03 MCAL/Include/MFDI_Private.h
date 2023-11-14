/*
 * MFDI_Private.h
 *
 *  Created on: Sep 8, 2022
 *      Author: Khaled shehab
 */

#ifndef MFDI_PRIVATE_H_
#define MFDI_PRIVATE_H_


#define MFDI_BASE_ADDRESS          0x40023C00


typedef struct
{
 volatile u32 ACR ;
 volatile u32 KEYR ;
 volatile u32 OPTKEYR ;
 volatile u32 SR ;
 volatile u32 CR ;
 volatile u32 OPTCR ;
}FDI_t ;

#define MFDI     ((volatile FDI_t*)(MFDI_BASE_ADDRESS))


#define MFDI_KEY1     0x45670123
#define MFDI_KEY2     0xCDEF89AB


#define WRITE_HALF_WORD    1

#endif /* MFDI_PRIVATE_H_ */
