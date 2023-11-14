/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Mina Magdy			*********************************/
/********************			Layer: LIB					*********************************/
/********************			Version: 2.00				*********************************/
/********************			Date: 09 Sep 2023			*********************************/
/********************************************************************************************/
/********************************************************************************************/
#ifndef	STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char      u8;
typedef signed char	       c8;
typedef unsigned short int u16;
typedef unsigned long int  u32;
typedef signed char        s8;
typedef signed short int   s16;
typedef signed long int    s32;
typedef float              f32;
typedef double             f64;
typedef long double        f128;




#define NULLPTR ((void*)0)
#define NULL_PTR ((void*)0)

#define NULL	(0)
#define MAX_U8 ((u8) 255)
#define MIN_U8 ((u8) 0)
#define MAX_S8 ((s8) 127)
#define MIN_S8 ((s8) -128)

#define MAX_U16 ((u16) 65535)
#define MIN_U16 ((u16) 0)
#define MAX_S16 ((s16) 32767)
#define MIN_S16 ((s16) -32768)

#define MAX_U32 ((u32) 4294967295)
#define MIN_U32 ((u32) 0)
#define MAX_S32 ((s32) 2147483647)
#define MIN_S32 ((s32) -2147483648)

#define SIZEOF_U8	(sizeof(u8) * 8)
#define SIZEOF_U16	(sizeof(u16) * 8)
#define SIZEOF_U32	(sizeof(u32) * 8)


typedef enum
{
	OK,
	NOK,
	ERROR,
	NULL_POINTER,
	OUT_OF_RANGE,
}Error_type;

typedef enum
{
	FALSE,
	TRUE
}bool_t;




#endif
