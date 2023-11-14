/*******************************************************************************
 * @file    crc.Private
 * @author  Mina Magdy
 * @email   mina.magdy.aziz.2698@gmail.com
 * @date    1 Nov 2023
 *          
 * @note    
 *
 *******************************************************************************/
#ifndef CRC_PRIVATE_H_
#define CRC_PRIVATE_H_


/* CRC Start Base address */
#define CRC_BASE_ADDRSS					(0x40023000)

/* CRC register map */

typedef struct{

	volatile u32 DR;
	volatile u32 IDR;
	volatile u32 CR;

}CRC_Type;

#define CRC ((volatile CRC_Type *) CRC_BASE_ADDRSS)


#define CRC_CR_RESET	0x01



#endif /* CRC_PRIVATE_H_ */
