#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/MGPIO_interface.h"
#include "../include/MRCC_interface.h"
#include "../include/MNVIC_Interface.h"
#include "../include/TIM_interface.h"

#include "../include/RGB_Cfg.h"
#include "../include/RGB_Interface.h"
#include "../include/RGB_Private.h"




static volatile bool_t EnableChange_Flag = TRUE;
static volatile bool_t ChangeColor_Flag = FALSE;
static volatile RGB_Color_type FirstColor;
static volatile RGB_Color_type SecondColor;
static u8 TmpColor[RGB_NUM];

void RGB_Init(void)
{
	/* Channel 1*/
	MGPIO_SetAlternativeFuncPin(PORTB, PIN6, TIM3_5);
	/* Channel 2*/
	MGPIO_SetAlternativeFuncPin(PORTB, PIN7, TIM3_5);
	/* Channel 3*/
	MGPIO_SetAlternativeFuncPin(PORTB, PIN8, TIM3_5);

}



void RGB_LedColor(RGB_Color_type Color)
{
	u8 Local_u8RED = RGB_ColorArray[Color][RED_INDEX];
	u8 Local_u8GREEN = RGB_ColorArray[Color][GREEN_INDEX];
	u8 Local_u8BLUE = RGB_ColorArray[Color][BLUE_INDEX];

	u8 RED_Duty = ((u32)100 * (u32)Local_u8RED) / (u32)255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, RED_Duty, RGB_RED_CHANNEL);

	u8 GREEN_Duty = ((u32)100 * (u32)Local_u8GREEN) / (u32)255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, GREEN_Duty, RGB_GRN_CHANNEL);

	u8 BLUE_Duty = ((u32)100 * (u32)Local_u8BLUE) / (u32)255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, BLUE_Duty, RGB_BLU_CHANNEL);
}


void RGB_LedColorAndIntensity(RGB_Color_type Color, u8 Copy_u8Intensity)
{
	u8 Local_u8RED = RGB_ColorArray[Color][RED_INDEX];
	u8 Local_u8GREEN = RGB_ColorArray[Color][GREEN_INDEX];
	u8 Local_u8BLUE = RGB_ColorArray[Color][BLUE_INDEX];

	if (100 >= Copy_u8Intensity)
	{
		u8 RED_Duty = ((((u32)((u32)100 * (u32)Local_u8RED) / (u32)255) * (u32)Copy_u8Intensity) / (u32)100);
		MTIM4_voidSetPWM(RGB_PWM_FREQ, RED_Duty, RGB_RED_CHANNEL);

		u8 GREEN_Duty = ((((u32)((u32)100 * (u32)Local_u8GREEN) / (u32)255) * (u32)Copy_u8Intensity) / (u32)100);
		MTIM4_voidSetPWM(RGB_PWM_FREQ, GREEN_Duty, RGB_GRN_CHANNEL);

		u8 BLUE_Duty = ((((u32)((u32)100 * (u32)Local_u8BLUE) / (u32)255) * (u32)Copy_u8Intensity) / (u32)100);
		MTIM4_voidSetPWM(RGB_PWM_FREQ, BLUE_Duty, RGB_BLU_CHANNEL);
	}
	else
	{

	}

}


void RGB_LedMakeColor(u8 red, u8 green, u8 blue)
{
	u8 Local_u8RED = red;
	u8 Local_u8GREEN = green;
	u8 Local_u8BLUE = blue;

	u8 RED_Duty = (100 * Local_u8RED) / 255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, RED_Duty, RGB_RED_CHANNEL);

	u8 GREEN_Duty = (100 * Local_u8GREEN) / 255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, GREEN_Duty, RGB_GRN_CHANNEL);

	u8 BLUE_Duty = (100 * Local_u8BLUE) / 255;
	MTIM4_voidSetPWM(RGB_PWM_FREQ, BLUE_Duty, RGB_BLU_CHANNEL);
}

RGB_Status RGB_ShowRoomSetColors(RGB_Color_type Color1, RGB_Color_type Color2)
{

	RGB_Status Status = RGB_NDONE;

	if (EnableChange_Flag)
	{
		/* Set First Color to RGB */
		RGB_LedColor(Color1);
		/* Save name of colors */
		FirstColor = Color1;
		SecondColor = Color2;

		/* save color in tmp to change in */
		TmpColor[RED_INDEX] = RGB_ColorArray[FirstColor][RED_INDEX];
		TmpColor[GREEN_INDEX] = RGB_ColorArray[FirstColor][GREEN_INDEX];
		TmpColor[BLUE_INDEX] = RGB_ColorArray[FirstColor][BLUE_INDEX];

		RGB_ShowRoom_Enable();

		/* Do not take another color until first finish */
		EnableChange_Flag = FALSE;
		/* Update status */
		Status = RGB_DONE;
	}

	return Status;
}


/* 19 us*/
void RGB_ShowRoom_Runnable (void)
{
	if (ChangeColor_Flag)
	{
		bool_t IsChange_Flag = FALSE;

		if (TmpColor[RED_INDEX] < RGB_ColorArray[SecondColor][RED_INDEX])
		{
			TmpColor[RED_INDEX]++;
			u8 Local_u8RED = TmpColor[RED_INDEX];
			u8 RED_Duty = (100 * Local_u8RED) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, RED_Duty, RGB_RED_CHANNEL);
			IsChange_Flag = TRUE;
		}
		else if (TmpColor[RED_INDEX] > RGB_ColorArray[SecondColor][RED_INDEX])
		{
			TmpColor[RED_INDEX]--;
			u8 Local_u8RED = TmpColor[RED_INDEX];
			u8 RED_Duty = (100 * Local_u8RED) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, RED_Duty, RGB_RED_CHANNEL);
			IsChange_Flag = TRUE;
		}

		if (TmpColor[GREEN_INDEX] < RGB_ColorArray[SecondColor][GREEN_INDEX])
		{
			TmpColor[GREEN_INDEX]++;
			u8 Local_u8GREEN = TmpColor[GREEN_INDEX];
			u8 GREEN_Duty = (100 * Local_u8GREEN) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, GREEN_Duty, RGB_GRN_CHANNEL);
			IsChange_Flag = TRUE;
		}
		else if (TmpColor[GREEN_INDEX] > RGB_ColorArray[SecondColor][GREEN_INDEX])
		{
			TmpColor[GREEN_INDEX]--;
			u8 Local_u8GREEN = TmpColor[GREEN_INDEX];
			u8 GREEN_Duty = (100 * Local_u8GREEN) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, GREEN_Duty, RGB_GRN_CHANNEL);
			IsChange_Flag = TRUE;
		}

		if (TmpColor[BLUE_INDEX] < RGB_ColorArray[SecondColor][BLUE_INDEX])
		{
			TmpColor[BLUE_INDEX]++;
			u8 Local_u8BLUE = TmpColor[BLUE_INDEX];
			u8 BLUE_Duty = (100 * Local_u8BLUE) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, BLUE_Duty, RGB_BLU_CHANNEL);
			IsChange_Flag = TRUE;
		}
		else if (TmpColor[BLUE_INDEX] > RGB_ColorArray[SecondColor][BLUE_INDEX])
		{
			TmpColor[BLUE_INDEX]--;
			u8 Local_u8BLUE = TmpColor[BLUE_INDEX];
			u8 BLUE_Duty = (100 * Local_u8BLUE) / 255;
			MTIM4_voidSetPWM(RGB_PWM_FREQ, BLUE_Duty, RGB_BLU_CHANNEL);
			IsChange_Flag = TRUE;
		}

		if (IsChange_Flag == FALSE)
		{
			EnableChange_Flag = TRUE;
			RGB_ShowRoom_Disable();
		}	
	}
}



void RGB_ShowRoom_Enable(void)
{
	ChangeColor_Flag = TRUE;
}

void RGB_ShowRoom_Disable(void)
{
	ChangeColor_Flag = FALSE;
}









RGB_Color_type RGB_LedColorIndex(s8 *StrColor)
{

	RGB_Color_type ColorIndex;
	for (ColorIndex = 0; ColorIndex < COLOR_NUM; ColorIndex++)
	{
		STR_Status StrStatus = Str_cmp(StrColor, (s8*)RGB_NamesColorArray[ColorIndex]);
		if (StrStatus == STR_MATCH)
		{
			return ColorIndex;
		}
	}
	return COLOR_NUM;
}


static void Str_toUpper(s8 *str)
{
	for (u8 Index = 0; str[Index]; Index++)
	{
		if (str[Index] >= 'a' && str[Index] <= 'z')
		{
			str[Index] = str[Index] - 'a' + 'A';
		}
	}
}

static STR_Status Str_cmp(s8 *strReceive, s8 *StrExpected)
{
	Str_toUpper(strReceive);
	for (u8 Index = 0; strReceive[Index] || StrExpected[Index]; Index++)
	{
		if (strReceive[Index] != StrExpected[Index])
		{
			return STR_NOMATCH;
		}
	}
	return STR_MATCH;
}











