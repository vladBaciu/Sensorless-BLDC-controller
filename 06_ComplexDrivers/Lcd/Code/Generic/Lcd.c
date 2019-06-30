/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Lcd.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Lcd.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#define LCD_PORT_DATA  (0b101010000000000)

#define LCD_PORT_CLEAR (~LCD_PORT_DATA)

#define LCD_LSB_MASK   (0b0001)

#define LCD_START_CGRAM_ADDRESS        (0x40)

#define LCD_NUMBER_OF_CUSTOM_SYMBOLS   (8U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
static uint8 auc_CustomUpArrow[] =
{
   0B00100,
   0B01110,
   0B10101,
   0B00100,
   0B00100,
   0B00100,
   0B00100,
   0B00100
};

static uint8 auc_CustomDownArrow[] =
{
   0B00000,
   0B00100,
   0B00100,
   0B00100,
   0B00100,
   0B10101,
   0B01110,
   0B00100
};

static uint8 auc_BatteryFullyCharged[] =
{
   0B00100,
   0B11111,
   0B11111,
   0B11111,
   0B11111,
   0B11111,
   0B11111,
   0B11111
};

static uint8 auc_BatteryAlmostCharged[] =
{
   0B00100,
   0B11111,
   0B10001,
   0B11111,
   0B11111,
   0B11111,
   0B11111,
   0B11111
};


static uint8 auc_BatteryDisCharged[] =
{
   0B00100,
   0B11111,
   0B10001,
   0B10001,
   0B10001,
   0B11111,
   0B11111,
   0B11111
};

static uint8 auc_IndicatorArrow[] =
{
   0B00010,
   0B00110,
   0B01110,
   0B11110,
   0B11110,
   0B01110,
   0B00110,
   0B00010
};

static uint8 auc_SubmenuArrow[] =
{
   0B00000,
   0B00000,
   0B00100,
   0B00010,
   0B11111,
   0B00010,
   0B00100,
   0B00000
};
static uint8 auc_SimleyFace[] =
{
   0B00000,
   0B00000,
   0B01010,
   0B00000,
   0B10001,
   0B01110,
   0B00000,
   0B00000
};
static uint8 *puc_LcdCustomCharacters[LCD_NUMBER_OF_CUSTOM_SYMBOLS] =
{
   auc_CustomUpArrow,
   auc_CustomDownArrow,
   auc_BatteryFullyCharged,
   auc_BatteryAlmostCharged,
   auc_BatteryDisCharged,
   auc_IndicatorArrow,
   auc_SubmenuArrow,
   auc_SimleyFace

};
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/
void Lcd_gv_Init()
{
   Delay_gv_Ms(1);
   Lcd_gv_SendCmd(0x03U);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x2CU);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x2CU);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x08U);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x01U);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x14U);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x06U);
   Delay_gv_Us(40);
   Lcd_gv_SendCmd(0x0CU);
   Delay_gv_Us(40);

}

void Lcd_gv_Send4BitCmd(uint8 uc_Command)
{
   /** Set RS pin state as LOW */
   Dio_WriteChannel(LCD_RS, STD_LOW);
   /** Set ENABLE pin state as LOW */
   Dio_WriteChannel(LCD_EN, STD_HIGH);

   /** Clear PE11, PE13, PE15,PB11 pins */
   Dio_WriteChannel(LCD_D4, STD_LOW);
   Dio_WriteChannel(LCD_D5, STD_LOW);
   Dio_WriteChannel(LCD_D6, STD_LOW);
   Dio_WriteChannel(LCD_D7, STD_LOW);

   uint8 uc_Lsb = 0x00;
   uint8 uc_MaskedCommand = uc_Command & 0x0F;
   /** e.g uc_MaskedCommand = b1110 => PB11|PE15|PE13|PE11 */
   for (uint8 i = LCD_D4; i <= LCD_D7; i++)
   {
      uc_Lsb = uc_MaskedCommand & LCD_LSB_MASK;
      Dio_WriteChannel(i, uc_Lsb);
      uc_MaskedCommand = uc_MaskedCommand >> 1;
   }
   Delay_gv_Us(1);
   Dio_WriteChannel(LCD_EN, STD_LOW);
   Delay_gv_Us(2);
}
void Lcd_gv_SendCmd(uint8 uc_Command)
{
   /* Send upper nibble from command parameter */
   Lcd_gv_Send4BitCmd(uc_Command >> 4);
   Delay_gv_Us(2);
   /* Send lower nibble from command parameter */
   Lcd_gv_Send4BitCmd(uc_Command);
   Delay_gv_Ms(5);
}
void Lcd_gv_Send4BitData(uint8 uc_Data)
{
   /** Set RS pin state as HIGH */
   Dio_WriteChannel(LCD_RS, STD_HIGH);
   /** Set ENABLE pin state as LOW */
   Dio_WriteChannel(LCD_EN, STD_HIGH);

   /** Clear PE11, PE13, PE15,PB11 pins */
   Dio_WriteChannel(LCD_D4, STD_LOW);
   Dio_WriteChannel(LCD_D5, STD_LOW);
   Dio_WriteChannel(LCD_D6, STD_LOW);
   Dio_WriteChannel(LCD_D7, STD_LOW);
   uint8 i = 0;
   uint8 uc_Lsb = 0x00;
   uint8 uc_MaskedCommand = uc_Data & 0x0F;
   /** e.g uc_MaskedCommand = b1110 => PB11|PE15|PE13|PE11 */
   for (i = LCD_D4; i <= LCD_D7; i++)
   {
      uc_Lsb = uc_MaskedCommand & LCD_LSB_MASK;
      Dio_WriteChannel(i, uc_Lsb);
      uc_MaskedCommand = uc_MaskedCommand >> 1;
   }
   Delay_gv_Us(1);
   Dio_WriteChannel(LCD_EN, STD_LOW);
   Delay_gv_Us(2);
}

void Lcd_gv_SendData(uint8 uc_Data)
{
   /* Send upper nibble from data parameter */
   Lcd_gv_Send4BitData(uc_Data >> 4);
   Delay_gv_Us(2);
   /* Send lower nibble from data parameter */
   Lcd_gv_Send4BitData(uc_Data);
   Delay_gv_Ms(5);
}

void Lcd_gv_Clear()
{
   Lcd_gv_SendCmd(0x01);
   Delay_gv_Ms(2);
   Lcd_gv_SendCmd(0x01);
}

void Lcd_gv_Cursor()
{
   Lcd_gv_SendCmd(0xFU);
   Delay_gv_Us(40);

}

void Lcd_gv_DisableCursor()
{
   Lcd_gv_SendCmd(0xCU);
   Delay_gv_Us(40);

}

void Lcd_gv_SendString(uint8 *puc_String)
{
   uint8 i = 0;
   for (i = 0; puc_String[i] != 0; i++)
   {
      Lcd_gv_SendData(puc_String[i]);
   }
}

void Lcd_gv_SendStringXY(uint8 uc_Row, uint8 uc_Position, uint8 *puc_String)
{
   if (uc_Row == 0 && uc_Position < 16)
   {
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0x80);
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0x80);
   }
   else if (uc_Row == 1 && uc_Position < 16)
   {
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0xC0);
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0xC0);
   }
   Delay_gv_Us(40);
   Lcd_gv_SendString(puc_String);
}

void Lcd_gv_CreateCustomCharacter(void)
{
   uint8 uc_CGRamAddress = LCD_START_CGRAM_ADDRESS;
   uint8 uc_I = 0;
   uint8 uc_J = 0;
   for (uc_J = 0; uc_J <= (LCD_NUMBER_OF_CUSTOM_SYMBOLS - 1); uc_J++)
   {
      Lcd_gv_SendCmd(uc_CGRamAddress);
      for (uc_I = 0; uc_I <= 7; uc_I++)
      {
         Lcd_gv_SendData(puc_LcdCustomCharacters[uc_J][uc_I]);

      }
      uc_CGRamAddress = uc_CGRamAddress + 8;
   }
}

void Lcd_gv_PutCustomCharacter(uint8 uc_Row, uint8 uc_Position, uint8 uc_Index)
{
   if (uc_Row == 0 && uc_Position < 16)
   {
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0x80);
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0x80);
   }
   else if (uc_Row == 1 && uc_Position < 16)
   {
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0xC0);
      Lcd_gv_SendCmd((uc_Position & 0x0F) | 0xC0);
   }
   Delay_gv_Us(40);
   Lcd_gv_SendData(uc_Index);
}
