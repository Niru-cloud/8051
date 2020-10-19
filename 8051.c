
/*

8051 Family C Library
Introduction
This library can be used for anyone starting with 8051 family of microcontrollers. The code has been tested on Ultra_X51 development board by xplore labz. The schematic can be downloaded from product page. If you're testing it on any other platform please refer to its schematic. Overview: This manual is designed to help embedded programmers and students, rapidly exploit the 8051-Controller for embedded applications. This manual has been targeted at embedded systems programmers and Students who have basic knowledge of 8051 architecture and C-Language. This manual provides the reference to all the library functions which are grouped under respective .c file. The .c files convention is as per the peripherals. The peripherals (lcd, keypad..) are connected to default PORTs which can be connected to required PORTs by changing the #defines and sbit.
Reference:
It is recommended to go through the below reference documents and datasheets before interfacing any peripherals.

The 8051 Microcontroller and Embedded Systems by Muhammad Ali Mazidi.
The 8051 microcontroller by Kenneth J Ayela.
Embedded C by Michael J Pont .
Any of the 16x2 lcd datasheet.
ADC0808/ADC0809 datasheet from National Semiconductors.
RTC-DS1307 from Dallas Semiconductors.
Serial Eeprom AT24C04/02 from Atmel.

Feedback:
Suggestions for additions and improvements in code and documentation are always welcome. Please send your feedback via e-mail to feedback@xplorelabz.com To keep the libraries clean, only administrators are authorized to edit them. If you wish to contribute drop in a email with code changes for review.

Disclaimer:
The libraries have been tested for P89v51rd2/AT89s52 on different development boards. We strongly believe that the library works on any 8051 boards running at 11.0592 MHz. However, Xplore Labz disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly. Documentation may be subject to change without prior notice.

The usage of tools and software demonstrated in the document are for educational purpose only, all rights pertaining to these belong to the respective owners. Users must ensure license terms are adhered to, for any use of the demonstrated software.

GNU GENERAL PUBLIC LICENSE:

The library code in this document is licensed under GNU General Public License (GPL) Copyright (C) 2012.
Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.
Since the library is licensed free of charge, there is no warranty for the libraries and the entire risk of the quality and performance is with the user.
Errors and omissions should be reported to feedback@xplorelabz.com

adc.c- ADC 0808/0809 C Library
                                  8051 ADC0808/9 library.
Filename: adc.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com
Note:

The Databus and Control lines are connected as below
The code can be modified to connect the ADC to any of the PORTs by changing the "#define and sbit".

          Databus  ---> P1
          adc_A    ---> P3.0
          adc_B    ---> P3.1
          adc_C    ---> P3.2
          adc_ALE  ---> P3.3
          adc_Start---> P3.4
          adc_EOC  ---> P3.5
          adc_OE   ---> P3.6
*/
#include<reg51.h>
#include"delay.h"
#define adc_databus P1
 
sbit adc_A    = P3^0;
sbit adc_B    = P3^1;
sbit adc_C    = P3^2;
sbit adc_ALE  = P3^3;
sbit adc_Start= P3^4;
sbit adc_EOC  = P3^5;
sbit adc_OE   = P3^6;

void ADC_Init()
Description :This function initializes the ADC control lines and databus.
I/P Arguments: none
Return value : none

void ADC_Init()
{
         adc_Start=0;                //Initialize all the control lines to zero.
         adc_ALE=0;
         adc_OE=0;
         adc_EOC=1;                  //Configure the EOC pin as I/P
       adc_databus=0xff;             //configure adc_databus as input
}


unsignaed char ADC_StartConversion(char channel)
Input Argument	char(channel number)
Output Argument	None
Description	This function does the ADC conversioin for the Selected Channel and returns the converted 8bit result
User Guide	None


unsigned char ADC_StartConversion(char channel)
{
     unsigned char adc_result;
 
       adc_A=((channel>>0) & 0x01);   //Selectthe channel
       adc_B=((channel>>1) & 0x01);   //for which the conversion needs to be done
       adc_C=((channel>>2) & 0x01);
 
        adc_ALE=1;         // Latch the address by making the ALE high.
        delay_us(50);
        adc_Start=1;       //Start the conversion after latching the channel address
        delay_us(25);
 
        adc_ALE=0;         //Pull ALE line to zero after starting the conversion.
        delay_us(50);
        adc_Start=0;       //Pull Start line to zero after starting the conversion.
 
     while(adc_EOC==0);    // Wait till the ADC conversion is completed,
                           // EOC will be pulled to HIGH by the hardware(ADC0809)
                           // once conversion is completed.
 
         adc_OE=1;         //Make the Output Enable high
                           //to bring the ADC data to port pins
         delay_us(25);
     adc_result=adc_databus;  //Read the ADC data from ADC bus
          adc_OE=0;           //After reading the data, disable th ADC output line.
 
      return(adc_result) ;
 
  }
Delay.c: 8051 delay C-Library
 
 
/*----------------------------------------------------------------------------------
                      8051 delay library  with the crystal frequency 11.0592MHz
Filename: delay.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ----------------------------------------------------------------------------------*/
 
 
#include<reg51.h>
 
 
 
 
/*----------------------------------------------------------------------------------
                         void delay_us(unsigned int n)
 ----------------------------------------------------------------------------------
 * I/P Arguments: unsigned int.
 * Return value : none
 
 * description : This function is used generate delay in us.
         It genarates a approximate delay of 10us for each count,
         if 5000 is passed as the argument then it generates a delay of apprx 50ms.
 
-----------------------------------------------------------------------------------*/
void delay_us(unsigned int us_count)
 {  
    while(us_count!=0)
      {
         us_count--;
       }
   }
 
 
 
 
 
/*----------------------------------------------------------------------------------
                         void delay_ms(unsigned int n)
 -----------------------------------------------------------------------------------
 * I/P Arguments: unsigned int.
 * Return value : none
 
 * description:  This function is used generate delay in ms.
     It genarates a approximate delay of 1ms for each count,
     if 1000 is passed as the argument then it generates delay of apprx 1000ms(1sec)
-----------------------------------------------------------------------------------*/
void delay_ms(unsigned int ms_count)
 {
        while(ms_count!=0)
         {
            delay_us(112);   //delay_us is called to generate 1ms delay
             ms_count--;
            }
   }
 
 
 
 
 
 
 
 /*----------------------------------------------------------------------------------
                        void delay_sec(unsigned char sec_count)
  -----------------------------------------------------------------------------------
  * I/P Arguments: unsigned char.
  * Return value    : none
 
  * description:
      This function is used generate delay in sec .
      It genarates a approximate delay of 1sec for each count,
      if 10 is passed as the argument then it generates delay of apprx 10sec
 
    note: A max of 255 sec delay can be generated using this function.
 -----------------------------------------------------------------------------------*/
void delay_sec(unsigned char sec_count)
 {
 
 
     while(sec_count!=0)
      {
         delay_ms(1000);    //delay_ms is called to generate 1sec delay
         sec_count--;
        }
 }
/*-------------------------------------------------*/

LCD 16x2 8 bit mode
                /*---------------------------------------------------------------------------------
                        8051 LCD library for 8-bit mode
Filename: lcd_8_bit.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ----------------------------------------------------------------------------------
 
 Note:
   1.Pin connection for LCD display in 8-bit mode is as shown below.
      By default the LCD is connected to Port2.
   2.The code can be modified to connect the LCD to any of the PORTs
     by changing the  "#define databus P2".
 
-----------------------------------------------------------------------------------*/
 
 
#include<reg51.h>
#include "delay.h"
#include "lcd.h"
 
#define databus P2   // LCD databus connected to PORT2
 
sbit rs= P0^0;       // Register select pin connected to P0.0
sbit rw= P0^1;       // Read Write pin connected to P0.1
sbit en= P0^2;       // Enable pin connected to P0.2
 
 
/* 16x2 LCD Specification */
#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
 
#define BlankSpace ' '
 
 
 
/*---------------------------------------------------------------------------------
                         void LCD_Init()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to initialize the lcd in 8-bit mode
-----------------------------------------------------------------------------------*/
void LCD_Init()
{
    delay_us(5000);
   LCD_CmdWrite(0x38);   // LCD 2lines, 5*7 matrix
   LCD_CmdWrite(0x0E);  // Display ON cursor ON
   LCD_CmdWrite(0x01);  // Clear the LCD
   LCD_CmdWrite(0x80);  // Move the Cursor to First line First Position
 
}
 
/*---------------------------------------------------------------------------------
                         void LCD_Clear()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function clears the LCD and moves the cursor to first Position
-----------------------------------------------------------------------------------*/
void LCD_Clear()
{
   LCD_CmdWrite(0x01);  // Clear the LCD and go to First line First Position
   LCD_CmdWrite(LineOne);
}
 
 
 
/*---------------------------------------------------------------------------------
                         void LCD_GoToLineOne()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function moves the Cursor to First line First Position
-----------------------------------------------------------------------------------*/
void LCD_GoToLineOne()
{
   LCD_CmdWrite(LineOne);   // Move the Cursor to First line First Position
}
 
 
/*---------------------------------------------------------------------------------
                         void LCD_GoToLineTwo()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function moves the Cursor to Second line First Position
-----------------------------------------------------------------------------------*/
void LCD_GoToLineTwo()
{
   LCD_CmdWrite(LineTwo);   // Move the Cursor to Second line First Position
}
 
 
 
/*---------------------------------------------------------------------------------
                         void LCD_GoToXY(char row,char col)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char row,char col
                 row -> line number(line1=0, line2=1),
                        For 2line LCD the I/P argument should be either 0 or 1.
                 col -> char number.
                        For 16-char LCD the I/P argument should be betwen 0-15.
 * Return value : none
 
 * description  :This function moves the Cursor to specified position
 
-----------------------------------------------------------------------------------*/
void LCD_GoToXY(char row, char col)
{
   char pos;
 
    if(row<LCDMaxLines)
      {
         pos= LineOne | (row << 6); // take the line number
                                    //row0->pos=0x80  row1->pos=0xc0
 
        if(col<LCDMaxChars)
           pos= pos+col;            //take the char number
                                    //now pos points to the given XY pos
 
         LCD_CmdWrite(pos);        // Move the Cursor to specified Position
       }
}
 
 
/*---------------------------------------------------------------------------------
                       void LCD_CmdWrite( char cmd)
* ---------------------------------------------------------------------------------
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value : none
 
 * description :This function sends a command to LCD in the following steps.
     step1: Send the I/P command to LCD.
     step2: Select the Control Register by making RS low.
     step3: Select Write operation making RW low.
     step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
----------------------------------------------------------------------------------*/
void LCD_CmdWrite( char cmd)
{
 
   databus=cmd;        // Send the command to LCD
     rs=0;             // Select the Command Register by pulling RS LOW
     rw=0;             // Select the Write Operation  by pulling RW LOW
     en=1;             // Send a High-to-Low Pusle at Enable Pin
    delay_us(10);
     en=0;
 
   delay_ms(1);
}
 
 
 
 
 
/*---------------------------------------------------------------------------------
                       void LCD_DataWrite( char dat)
 ----------------------------------------------------------------------------------
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value : none
 
 * description  :
    This function sends a character to be displayed on LCD in the following steps.
      step1: Send the character to LCD.
      step2: Select the Data Register by making RS high.
      step3: Select Write operation making RW low.
      step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 
-----------------------------------------------------------------------------------*/
void LCD_DataWrite( char dat)
{
 
   databus=dat;     // Send the data to LCD
     rs=1;          // Select the Data Register by pulling RS HIGH
     rw=0;          // Select the Write Operation  by pulling RW LOW
     en=1;          // Send a High-to-Low Pusle at Enable Pin
    delay_us(10);
     en=0;
 
   delay_ms(1);
 
}
 
 
 
 
 
/*---------------------------------------------------------------------------------
                       void LCD_DisplayString(char *string_ptr)
 ----------------------------------------------------------------------------------
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value : none
 
 * description  :
               This function is used to display the ASCII string on the lcd.
                 1.The string_ptr points to the first char of the string
                    and traverses till the end(NULL CHAR).
                 2.Each time a char is sent to LCD_DataWrite funtion to display.
-----------------------------------------------------------------------------------*/
void LCD_DisplayString(char *string_ptr)
{
   while(*string_ptr)
    LCD_DataWrite(*string_ptr++);
    }
 
 
/*---------------------------------------------------------------------------------
                      void  LCD_DisplayNumber(unsigned int num)
 ----------------------------------------------------------------------------------
 * Function name:  LCD_DisplayNumber()
 * I/P Arguments: unsigned int.
 * Return value : none
 
 * description  :This function is used to display a 5-digit integer(0-65535).
                 ex: if the number is 12345 then 12345 is displayed.
                     if the number is 123 then 00123 is displayed.
 
 
 ----------Take 1 by dividing by 10000 and add 0X30 to obtain the ASCII value,
|           then take the 4-digit remainder(2345).
|
| ---------Take 2 by dividing by 1000  and add 0X30 to obtain the ASCII value,
||           then take the 3-digit remainder(345)
||
|| --------Take 3 by dividing by 100   and add 0X30 to obtain the ASCII value,
|||           then take the 2-digit remainder(45).
|||
||| -------Take 4 by dividing by 10    and add 0X30 to obtain the ASCII value,
|||| ------Take 5 the remainder of 45  and add 0X30 to obtain the ASCII value,.
|||||
12345
-----------------------------------------------------------------------------------*/
void LCD_DisplayNumber(unsigned int num)
{
   LCD_DataWrite((num/10000)+0x30);
   num=num%10000;
 
   LCD_DataWrite((num/1000)+0x30);
   num=num%1000;
 
   LCD_DataWrite((num/100)+0x30);
   num=num%100;
 
   LCD_DataWrite((num/10)+0x30);
 
   LCD_DataWrite((num%10)+0x30);
 
 }
 
 
/*---------------------------------------------------------------------------------
                  void LCD_ScrollMessage(char *msg_ptr)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char *msg_ptr
                 msg_ptr -> pointer to the string to be scrolled
 
 * Return value : none
 
 * description  :This function scrolls the given message on the first line.
        1.16 chars are displayed at atime.
        2.Pointer is incremented to skip a char each time to give the illusion of
           moving chars
        3.If the chars are less than 16, then the BlankSpaces are displayed.
 
-----------------------------------------------------------------------------------*/
 
void LCD_ScrollMessage(char *msg_ptr)
{
  unsigned char i,j;
  LCD_CmdWrite(0x0c);            //Disable the Cursor
  for(i=0;msg_ptr[i];i++)        //Loop to display the complete string
    {                            //each time 16 chars are displayed and
                                 //pointer is incremented to point to next char
 
      LCD_GoToLineOne();                   //Move the Cursor to first line
 
      for(j=0;j<LCDMaxChars && msg_ptr[i+j];j++) //loop to Display first 16 Chars
        LCD_DataWrite(msg_ptr[i+j]);                 //or till Null char
 
      for(j=j; j<LCDMaxChars; j++)               //If the chars are below 16
        LCD_DataWrite(BlankSpace);              //then display blank spaces
 
       delay_ms(125);
    }
   LCD_CmdWrite(0x0E);            //Enable the Cursor
}
 
 
/*---------------------------------------------------------------------------------
                  void LCD_DisplayRtcTime(char hour,char min,char sec)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char hour,char min,char sec
             hour,min,sec should be packed BCD format, as read from DS1307
 
 * Return value : none
 
 * description  :This function display hour,min,sec read from DS1307.
 
   ---------- Display the higher nibble of hour after adding 0x30(ASCII conversion)
  |           Display the lower nibble of hour after adding 0x30(ASCII conversion)
  |
  |   -------- Display the higher nibble of min after adding 0x30(ASCII conversion)
  |  |         Display the lower nibble of min after adding 0x30(ASCII conversion)
  |  |
  |  |   -----Display the higher nibble of sec after adding 0x30(ASCII conversion)
  |  |  |     Display the lower nibble of sec after adding 0x30(ASCII conversion)
  |  |  |
  10;10;40
 
-----------------------------------------------------------------------------------*/
void LCD_DisplayRtcTime(char hour,char min,char sec)
{
    LCD_DataWrite(((hour>>4) & 0x0f) + 0x30);
    LCD_DataWrite((hour & 0x0f) + 0x30);
    LCD_DataWrite(':');
 
    LCD_DataWrite(((min>>4) & 0x0f) + 0x30);
    LCD_DataWrite((min & 0x0f) + 0x30);
    LCD_DataWrite(':');
 
    LCD_DataWrite(((sec>>4) & 0x0f) + 0x30);
    LCD_DataWrite((sec & 0x0f) + 0x30);
 
 }
 
 
 
 
/*---------------------------------------------------------------------------------
                  LCD_DisplayRtcDate(char day,char month,char year)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char day,char month,char year
             day,month,year should be packed BCD format, as read from DS1307
 
 * Return value : none
 
 * description  :This function display day,month,year read from DS1307.
 
   ----------- Display the higher nibble of day after adding 0x30(ASCII conversion)
  |            Display the lower nibble of day after adding 0x30(ASCII conversion)
  |
  |   -------- Display the higher nibble of month after adding 0x30(ASCII conversion)
  |  |         Display the lower nibble of month after adding 0x30(ASCII conversion)
  |  |
  |  |   ----- Display the higher nibble of year after adding 0x30(ASCII conversion)
  |  |  |      Display the lower nibble of year after adding 0x30(ASCII conversion)
  |  |  |
  01/01/12 (1st-Jan 2012)
 
-----------------------------------------------------------------------------------*/
void LCD_DisplayRtcDate(char day,char month,char year)
 {
     LCD_DataWrite(((day>>4) & 0x0f) + 0x30);
     LCD_DataWrite((day & 0x0f) + 0x30);
     LCD_DataWrite('/');
 
     LCD_DataWrite(((month>>4) & 0x0f) + 0x30);
     LCD_DataWrite((month & 0x0f) + 0x30);
     LCD_DataWrite('/');
 
     LCD_DataWrite(((year>>4) & 0x0f) + 0x30);
    LCD_DataWrite((year & 0x0f) + 0x30);
 
 }
LCD 4 bit mode
 
 
 
 /*----------------------------------------------------------------------------------
                        8051 LCD library for 4-bit mode
Filename: lcd_4_bit.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 
 ----------------------------------------------------------------------------------
Note:
 1.Pin connection for LCD display in 4-bit mode.
 2.By default the LCD is connected to Port0.
 3.The code can be modified to connect the LCD to any of the PORTs by changing the
   "#define databus P0".
 
 
 
----------------------------------------------------------------------------------*/
 
 
#include<reg51.h>
#include "delay.h"
 
#define databus P0       // LCD databus connected to PORT0
 
sbit rs= databus^0;      // Register select pin connected to P0.0
sbit rw= databus^1;      // Read Write pin connected to P0.1
sbit en= databus^2;      // Enable pin connected to P0.2
 
 
 
/* 16x2 LCD Specification */
#define LCDMaxLines 2
#define LCDMaxChars 16
#define LineOne 0x80
#define LineTwo 0xc0
 
#define BlankSpace ' '
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
                         void LCD_Init()
 ----------------------------------------------------------------------------------
 * Function name:  LCD_Init()
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to initialize the lcd in 4-bit mode
----------------------------------------------------------------------------------*/
void LCD_Init()
{
    delay_us(5000);
   LCD_CmdWrite(0x02);  //Initilize the LCD in 4bit Mode
   LCD_CmdWrite(0x28);
   LCD_CmdWrite(0x0E);  // Display ON cursor ON
   LCD_CmdWrite(0x01);  // Clear the LCD
   LCD_CmdWrite(0x80);  // Move the Cursor to First line First Position
 
}
 
 
/*----------------------------------------------------------------------------------
                       void LCD_CmdWrite( char cmd)
------------------------------------------------------------------------------------
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value : none
 
 * description  :This function sends a command to LCD in the following steps.
     step1: Send the Higher Nibble of the I/P command to LCD.
     step2: Select the Control Register by making RS low.
     step3: Select Write operation making RW low.
     step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 
     step5: Send the Lower Nibble of the I/P command to LCD.
     step6: Select the Control Register by making RS low.
     step7: Select Write operation making RW low.
     step8: Send a High-to-Low pulse on Enable PIN with some delay_us.
----------------------------------------------------------------------------------*/
void LCD_CmdWrite( char cmd)
{
 
   databus=(cmd & 0xf0);        // Send the Higher Nibble of the command to LCD
     rs=0;                      // Select the Command Register by pulling RS LOW
     rw=0;                      // Select the Write Operation  by pulling RW LOW
     en=1;                      // Send a High-to-Low Pusle at Enable Pin
    delay_us(1);
     en=0;
 
   delay_us(10);                   // wait for some time
 
   databus=((cmd<<4) & 0xf0);   // Send the Lower Nibble of the command to LCD
     rs=0;                      // Select the Command Register by pulling RS LOW
     rw=0;                      // Select the Write Operation  by pulling RW LOW
     en=1;                      // Send a High-to-Low Pusle at Enable Pin
    delay_us(1);
     en=0;
   delay_ms(1);
}
 
 
 
/*---------------------------------------------------------------------------------
                       void LCD_DataWrite( char dat)
 ----------------------------------------------------------------------------------
 * Function name: LCD_DataWrite()
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value : none
 
 * description  :
    This function sends a character to be displayed on LCD in the following steps.
       step1: Send the higher nibble of the character to LCD.
       step2: Select the Data Register by making RS high.
       step3: Select Write operation making RW low.
       step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 
       step5: wait for some time
 
       step6: Send the lower nibble of the character to LCD.
       step7: Select the Data Register by making RS high.
       step8: Select Write operation making RW low.
       step9: Send a High-to-Low pulse on Enable PIN with some delay_us.
----------------------------------------------------------------------------------*/
void LCD_DataWrite( char dat)
{
 
 
   databus=(dat & 0xf0);        // Send the Higher Nibble of the Data to LCD
     rs=1;                      // Select the Data Register by pulling RS HIGH
     rw=0;                      // Select the Write Operation  by pulling RW LOW
     en=1;                      // Send a High-to-Low Pusle at Enable Pin
    delay_us(1);
     en=0;
 
   delay_us(10);                 // wait for some time.
 
   databus=((dat <<4) & 0xf0);  // Send the Lower Nibble of the Data to LCD
     rs=1;                      // Select the Data Register by pulling RS HIGH
     rw=0;                      // Select the Write Operation  by pulling RW LOW
     en=1;                      // Send a High-to-Low Pusle at Enable Pin
    delay_us(1);
     en=0;
 
   delay_ms(1);
 
}
Keypad.c: 8051 Keypad C-library
/*----------------------------------------------------------------------------------
                        8051 4x4 Keypad Library
Filename: keypad.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ----------------------------------------------------------------------------------
 Note:
  1.Rows are connected to lower 4-bits of P1
  1.Cols are connected to higher 4-bits of P1
 
----------------------------------------------------------------------------------*/
 
 
#include <reg51.h>
#include "keypad.h"
#include "delay.h"
 
 
#define ROW P1   //Lower four bits of P1 are used as ROWs
#define COL P1   //Higher four bits of P1 are used as COLs
 
 
 
 
/*---------------------------------------------------------------------------------
                   void KEYPAD_Init()
 ----------------------------------------------------------------------------------
 * I/P Arguments:none
 * Return value : none
 
 * description  : This function the rows and colums for keypad scan
        1.ROW lines are configured as Output.
        2.Column Lines are configured as Input.
-----------------------------------------------------------------------------------*/
void KEYPAD_Init()
{
       ROW=0xF0;           // Configure Row lines as O/P and Column lines as I/P
}
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                   void KEYPAD_WaitForKeyRelease()
 ----------------------------------------------------------------------------------
 * I/P Arguments:none
 
 * Return value : none
 
 * description  : This function waits till the previous key is released.
        1.All the ROW lines are pulled low.
        2.Column Lines are read to check the key press.
        3.If all the Keys are released then Column lines will be High(0xF0)
-----------------------------------------------------------------------------------*/
void KEYPAD_WaitForKeyRelease()
{
   unsigned char key;
    do
      {
        ROW=0xF0;           // Pull the ROW lines to low and Column lines high.
        key=COL & 0xF0;     // Read the Columns, to check the key press
       }while(key!=0xF0);   // Wait till the Key is released,
                            // If no Key is pressed, Column lines will be High(0xF0)
}
 
 
 
/*---------------------------------------------------------------------------------
                   void KEYPAD_WaitForKeyPress()
 ----------------------------------------------------------------------------------
 * I/P Arguments:none
 * Return value : none
 
 * description  : This function waits till a new key is pressed.
        1.All the ROW lines are pulled low.
        2.Column Lines are read to check the key press.
        3.If any Key is pressed then corresponding Column Line goes low.
        4.Wait for Some time and perform the above operation to ensure
          the True Key Press before decoding the KEY.
-----------------------------------------------------------------------------------*/
void KEYPAD_WaitForKeyPress()
{
  unsigned char key;
  do
   {
     do
      {
        ROW=0xF0;         // Pull the ROW lines to low and Column lines high.
        key=COL & 0xF0;   // Read the Columns, to check the key press
       }while(key==0xF0); // Wait till the Key is pressed,If no Key is pressed
                          // if a Key is pressed the corresponding Column line go low
 
       delay_ms(1);       // Wait for some time(debounce Time);
 
       ROW=0xF0;          // After some time, perform the above action to ensure the
       key=COL & 0xF0;    // the Key press.
    }while(key==0xF0);
 
 }
 
 
 
 
 
/*---------------------------------------------------------------------------------
                   unsigned char KEYPAD_ScanKey()
 ----------------------------------------------------------------------------------
 * I/P Arguments:none
 
 * Return value : char--> Scancode of the Key Pressed
 
 * description  : This function scans all the rows to decode the key pressed.
        1.Each time a ROW line is pulled low to detect the KEY.
        2.Column Lines are read to check the key press.
        3.If any Key is pressed then corresponding Column Line goes low.
        4.Return the ScanCode(Combination of ROW & COL) for decoding the key.
-----------------------------------------------------------------------------------*/
unsigned char KEYPAD_ScanKey()
 {
 
     unsigned char ScanKey = 0xFE,i, key;
 
   for(i=0;i<0x04;i++)            // Scan All the 4-Rows for key press
    {
      ROW=ScanKey;                // Select 1-Row at a time for Scanning the Key
      key=COL & 0xF0;             // Read the Column, for key press
 
      if(key!=0xf0)               // If the KEY press is detected for the selected
         break;                   // ROW then stop Scanning,
 
     ScanKey=((ScanKey<<1)+0x01); // Rotate the ScanKey to SCAN the remaining Rows
    }
 
 
    key = COL;                    // Retun the COL status to decode the key
    return(key);
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                   unsigned char KEYPAD_GetKey()
 ----------------------------------------------------------------------------------
 * I/P Arguments:none
 
 * Return value : char--> ASCII value of the Key Pressed
 
 * description: This function waits till a key is pressed and retuns its ASCII Value
 
        1.Wait till the previous key is released..
        2.Wait for the new key press.
        3.Scan all the rows one at atime for the pressed key.
        4.Decode the key pressed depending on ROW-COL combination and retuns its
          ASCII value.
-----------------------------------------------------------------------------------*/
unsigned char KEYPAD_GetKey()
{
    unsigned char key;
 
      KEYPAD_WaitForKeyRelease();    // Wait for the previous key release
      delay_ms(1);
 
      KEYPAD_WaitForKeyPress();      // Wait for the new key press
      key = KEYPAD_ScanKey();        // Scan for the key pressed.
 
   switch(key)                       // Decode the key
     {
         case 0xe7: key='0'; break;
         case 0xeb: key='1'; break;
         case 0xed: key='2'; break;
         case 0xee: key='3'; break;
         case 0xd7: key='4'; break;
         case 0xdb: key='5'; break;
         case 0xdd: key='6'; break;
         case 0xde: key='7'; break;
         case 0xb7: key='8'; break;
         case 0xbb: key='9'; break;
         case 0xbd: key='A'; break;
         case 0xbe: key='B'; break;
         case 0x77: key='C'; break;
         case 0x7b: key='D'; break;
         case 0x7d: key='E'; break;
         case 0x7e: key='F'; break;
         default: key='z';
      }
   return(key);                      // Return the key
}
Uart.c: 8051 Uart C-Libraray
/*--------------------------------------------------------------------------------
   8051 UART library for Serial Communication at 9600 baud rate
   with the crystal frequency 11.0592MHz
 
Filename: uart.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ---------------------------------------------------------------------------------*/
 
 
 #include<reg51.h>
 
 
 
/*-------------------------------------------------------------------------------
                         void UART_Init()
----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to initialize the UART at 9600 baud rate
                  by below configuration.
    1.Timer 1 is run in Mode2(auto reload mode) to generate the required Baud Rate.
    2.9600 baud rate is generate by loading -3(0XFD) in TH1 register.
    3.SCON is configured in MODE1 ie. 8bit Data 1-Start and 1-Stop bit.
    4.Finally the timer is turned ON by setting TR1 bit to generate the baud rate.
----------------------------------------------------------------------------------*/
void UART_Init()
{
      TMOD |=0x20; //Timer1 in Mode2.
      TH1=-3;    // 9600 Baud rate at 11.0592MHz
      SCON=0x50; // Asynchronous mode 8-bit data and 1-stop bit
      TR1=1;     //Turn ON the timer.
  }
 
 
 
 
 
/*----------------------------------------------------------------------------------
                              char UART_RxChar()
  ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : char
 
 * description :This function is used to receive a char from UART module.
                It waits till a char is received ie.till RI is set,
                RI will be set once a CHAR is received.
              Finally it clears the RI for next cycle and returns the received char.
----------------------------------------------------------------------------------_*/
char UART_RxChar()
{
  while(RI==0);   // Wait till the data is received
     RI=0;        // Clear Receive Interrupt Flag for next cycle
  return(SBUF);   // return the received char
}
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
                         void UART_TxChar(char ch)
------------------------------------------------------------------------------------
 * I/P Arguments: char--> data to be transmitted.
 * Return value : none.
 
 * description  :This function is used to transmit a char through UART module.
                 The Char to be transmitted is loaded into SBUF.
                 It waits till char is transmitted ie.till TI is set.
                 TI will be set once a CHAR is transmitted.
                 Finally it clears the TI for next operation.
 ----------------------------------------------------------------------------------*/
 void UART_TxChar(char ch)
{
    SBUF=ch;       // Load the data to be transmitted
  while(TI==0);    // Wait till the data is trasmitted
     TI=0;         //Clear the flag for next cycle.
}
 
 
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
                         void UART_TxString(char *string_ptr)
 -----------------------------------------------------------------------------------
 * I/P Arguments: String(Address of the string) to be transmitted.
 * Return value : none
 
 * description :This function is used to transmit the ASCII string through UART..
                The string_ptr points to the first char of the string.
                And it is incremented each time to traverse till the end(NULL CHAR).
               Each time a char is sent to UART_TxChar() fun to transmit it through UART
----------------------------------------------------------------------------------_*/
void UART_TxString(char *string_ptr)
 {
          while(*string_ptr)
           UART_TxChar(*string_ptr++);
   }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                         void UART_RxString(char *string_ptr)
 ----------------------------------------------------------------------------------
 * I/P Arguments: *string_ptr
                   Address of the string where the received data needs to be stored
 * Return value : none
 
 * description  :
                1.This function is used to receive a ASCII string through UART
                  till the carriage_return/New_line
                2.The string_ptr points to the begining of the string and each
                  time UART_RxChar() function is called to receive a char and copy
                  it into the buffer(STRING) and incrment string_ptr.
                3.Once the carriage_return/New_line is encountered the loop
                  is breaked and the String is NULL terminated.
 
 *****NOTE*******:
  1.The received char is ECHOED back,
    if not required then comment UART_TxChar(ch) in the code.
  2.BackSlash is not taken care.
----------------------------------------------------------------------------------_*/
void UART_RxString(char *string_ptr)
 {
     char ch;
     while(1)
       {
          ch=UART_RxChar();    //Reaceive a char
          UART_TxChar(ch);     //Echo back the received char
 
         if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
           {                          //once enter key is pressed
              *string_ptr=0;          //null terminate the string
                break;                //and break the loop
             }
         *string_ptr=ch;              //copy the char into string.
         string_ptr++;                //and increment the pointer
      }
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
                      void  UART_TxNumber(unsigned int num)
------------------------------------------------------------------------------------
 * I/P Arguments: unsigned int.
 * Return value : none
 
 * description  :This function is used to transmit a 5-digit integer(0-65535).
                 ex: if the number is 12345 then 12345 is transmitted.
                     if the number is 123 then 00123 is transmitted.
 
 
 ----------Take 1 by dividing by 10000 and add 0X30 to obtain the ASCII value,
|          then take the 4-digit remainder(2345).
|
| ---------Take 2 by dividing by 1000  and add 0X30 to obtain the ASCII value,
||         then take the 3-digit remainder(345)
||
|| --------Take 3 by dividing by 100   and add 0X30 to obtain the ASCII value,
|||        then take the 2-digit remainder(45).
|||
||| -------Take 4 by dividing by 10    and add 0X30 to obtain the ASCII value,
|||| ------Take 5 the remainder of 45  and add 0X30 to obtain the ASCII value,.
|||||
12345
------------------------------------------------------------------------------------*/
 
void UART_TxNumber(unsigned int num)
{
 
       UART_TxChar((num/10000)+0x30);
       num=num%10000;
 
       UART_TxChar((num/1000)+0x30);
       num=num%1000;
 
       UART_TxChar((num/100)+0x30);
       num=num%100;
 
       UART_TxChar((num/10)+0x30);
 
       UART_TxChar((num%10)+0x30);
}
                                                                       =I2c.c: 8051 I2c C-Library=
/*---------------------------------------------------------------------------------*
                                 8051 I2C  library
Filename: I2C.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 
Note:
1.The SDA and SCL lines are connected to P0.7 and P0.6
2.The code can be modified to connect the
  SDA and SCL to any of the PORTs by changing the "sbit".
 ----------------------------------------------------------------------------------*/
#include<reg51.h>
#include "delay.h"
#include "i2c.h"
 
sbit SCL=P0^6;      //SCL Connected to P0.6
sbit SDA=P0^7;      //SDA Connected to P0.7
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------*
                         void I2C_Clock()
 ----------------------------------------------------------------------------------*
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to generate a clock pulse on SCL line.
-----------------------------------------------------------------------------------*/
void I2C_Clock(void)
{
    delay_us(1);
    SCL = 1;        // Wait for Some time and Pull the SCL line High
 
    delay_us(1);        // Wait for Some time
    SCL = 0;        // Pull back the SCL line low to Generate a clock pulse
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------*
                         void I2C_Start()
 ----------------------------------------------------------------------------------*
 * I/P Arguments: none.
 * Return value : none
 * description  :This function is used to generate I2C Start Condition.
                 Start Condition: SDA goes low when SCL is High.
 
-----------------------------------------------------------------------------------*/
void I2C_Start()
{
    SCL = 0;        // Pull SCL low
 
    SDA = 1;        // Pull SDA High
    delay_us(1);
 
    SCL = 1;        //Pull SCL high
    delay_us(1);
 
    SDA = 0;        //Now Pull SDA LOW, to generate the Start Condition
    delay_us(1);
 
    SCL = 0;        //Finally Clear the SCL to complete the cycle
}
 
 
 
 
/*-----------------------------------------------------------------------------------
                         void I2C_Stop()
 ------------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 * description  :This function is used to generate I2C Stop Condition.
                 Stop Condition: SDA goes High when SCL is High.
 
------------------------------------------------------------------------------------*/
 
void I2C_Stop(void)
{
    SCL = 0;            // Pull SCL low
    delay_us(1);
 
    SDA = 0;            // Pull SDA  low
    delay_us(1);
 
    SCL = 1;            // Pull SCL High
    delay_us(1);
 
    SDA = 1;            // Now Pull SDA High, to generate the Stop Condition
}
 
 
/*---------------------------------------------------------------------------------*
                         void I2C_Write(unsigned char dat)
 ----------------------------------------------------------------------------------*
 * I/P Arguments: unsigned char-->8bit data to be sent.
 * Return value : none
 
 * description  :This function is used to send a byte on SDA line using I2C protocol
                 8bit data is sent bit-by-bit on each clock cycle.
                 MSB(bit) is sent first and LSB(bit) is sent at last.
                 Data is sent when SCL is low.
 
-----------------------------------------------------------------------------------*/
void I2C_Write(unsigned char dat)
{
    unsigned char i;
 
    for(i=0;i<8;i++)         // loop 8 times to send 1-byte of data
     {
        SDA = dat & 0x80;    // Send Bit by Bit on SDA line
        I2C_Clock();         // Generate Clock at SCL
        dat = dat<<1;
      }
        SDA = 1;                 // Set SDA at last
}
 
/*-----------------------------------------------------------------------------------*
                         unsigned char I2C_Read()
 ------------------------------------------------------------------------------------*
 * I/P Arguments: none.
 * Return value : Unsigned char(received byte)
 
 * description :This fun is used to receive a byte on SDA line using I2C protocol.
               8bit data is received bit-by-bit each clock and finally packed into Byte.
               MSB(bit) is received first and LSB(bit) is received at last.
 
-------------------------------------------------------------------------------------*/
unsigned char I2C_Read(void)
{
    unsigned char i, dat=0x00;
 
       SDA=1;               //Make SDA as I/P
    for(i=0;i<8;i++)        // loop 8times to read 1-byte of data
     {
       delay_us(1);
        SCL = 1;            // Pull SCL High
        delay_us(1);
 
        dat = dat<<1;       //dat is Shifted each time and
        dat = dat | SDA;    //ORed with the received bit to pack into byte
 
        SCL = 0;            // Clear SCL to complete the Clock
       }
   return dat;               // Finally return the received Byte*
}
 
 
 
/*---------------------------------------------------------------------------------*
                         void I2C_Ack()
 ----------------------------------------------------------------------------------*
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to generate a the Positive ACK
                 pulse on SDA after receiving a byte.
-----------------------------------------------------------------------------------*/
void I2C_Ack()
{
    SDA = 0;        //Pull SDA low to indicate Positive ACK
    I2C_Clock();    //Generate the Clock
    SDA = 1;        // Pull SDA back to High(IDLE state)
}
 
 
 
 
 
/*---------------------------------------------------------------------------------*
                         void I2C_NoAck()
 ----------------------------------------------------------------------------------*
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to generate a the Negative/NO ACK
                 pulse on SDA after receiving all bytes.
-----------------------------------------------------------------------------------*/
void I2C_NoAck()
{
    SDA = 1;        //Pull SDA high to indicate Negative/NO ACK
   I2C_Clock();     // Generate the Clock  
    SCL = 1;        // Set SCL */
}

Ds1307.c: 8051 ds1307-RTC C-Library
/*--------------------------------------------------------------------------------
                               8051 DS1307  library
Filename: DS1307.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 
 ---------------------------------------------------------------------------------*/
 
#include "ds1307.h"
#include "i2c.h"
#include "delay.h"
 
 
 
/* Below values are fixed and should not be changed.
    Refer Ds1307 DataSheet for more info*/
 
#define DS1307_ID 0xD0     // DS1307 ID
 
#define SEC_ADDRESS   0x00 // Address to access Ds1307 SEC register
#define DATE_ADDRESS  0x04 // Address to access Ds1307 DATE register
#define CONTROL 0x07       // Address to access Ds1307 CONTROL register
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                         void DS1307_Init()
 ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description :This function is used to initialize the Ds1307 RTC.
                Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                After selecting DS1307, write 0x00 into Control register of Ds1307
 
------------------------------------------------------------------------------------*/
void DS1307_Init()
{
    I2C_Start();            // Start I2C communication
 
    DS1307_Write(DS1307_ID);   // Connect to DS1307 by sending its ID on I2c Bus
    DS1307_Write(CONTROL);     // Select the Ds1307 ControlRegister to configure Ds1307
 
    DS1307_Write(0x00);        // Write 0x00 to Control register to disable SQW-Out
 
    I2C_Stop();             // Stop I2C communication after initilizing DS1307
 
 }
 
 
 
 
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                         void DS1307_Write(unsigned char dat)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char-> Data to be written into DS1307.
 * Return value : none
 
 * description :This function is used to initialize the Ds1307 RTC.
                Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                After selecting DS1307, write 0x00 into Control register of Ds1307
 
------------------------------------------------------------------------------------*/
void DS1307_Write(unsigned char dat)
{
    I2C_Write(dat);   // Connect to DS1307 by sending its ID on I2c Bus
    I2C_Clock();
 }
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
                         unsigned char DS1307_Read()
 ----------------------------------------------------------------------------------
 * I/P Arguments: char-> Data to be written into DS1307.
 * Return value : none
 
 * description :This function is used to initialize the Ds1307 RTC.
                Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                After selecting DS1307, write 0x00 into Control register of Ds1307
 
------------------------------------------------------------------------------------*/
unsigned char DS1307_Read()
{
    unsigned char dat;
    dat = I2C_Read();   // Connect to DS1307 by sending its ID on I2c Bus
    return(dat);
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
        void DS1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss)
 -----------------------------------------------------------------------------------
 * I/P Arguments: char,char,char-->hh,mm,ss to initilize the time into DS1307.
 * Return value : none
 
 * description  :This function is used to set Time(hh,mm,ss) into the Ds1307 RTC.
                 Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                 After selecting DS1307, select the RAM address 0x00 to point to sec
                 Initilze Sec, MIN, Hour one after the other.
                 Stop the I2c communication.
-----------------------------------------------------------------------------------*/
void DS1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss)
{
    I2C_Start();            // Start I2C communication
 
    DS1307_Write(DS1307_ID);    // connect to DS1307 by sending its ID on I2c Bus
    DS1307_Write(SEC_ADDRESS); // Select the SEC RAM address
 
    DS1307_Write(ss);           // Write sec on RAM address 00H
    DS1307_Write(mm);           // Write min on RAM address 01H
    DS1307_Write(hh);           // Write hour on RAM address 02H
 
    I2C_Stop();             // Stop I2C communication after Setting the Time
}
 
 
 
 
 
 
/*---------------------------------------------------------------------------------
          void DS1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
 ----------------------------------------------------------------------------------
 * I/P Arguments: char,char,char-->day,month,year to initilize the Date into DS1307.
 * Return value : none
 
 * description  :This function is used to set Date(dd,mm,yy) into the Ds1307 RTC.
                 Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                 After selecting DS1307, select the RAM address 0x04 to point to day
                 Initilze Day,Month and Year one after the other.
                 Stop the I2c communication.
----------------------------------------------------------------------------------*/
void DS1307_SetDate(unsigned char dd, unsigned char mm, unsigned char yy)
{
    I2C_Start();            // Start I2C communication
 
    DS1307_Write(DS1307_ID);    // connect to DS1307 by sending its ID on I2c Bus
    DS1307_Write(DATE_ADDRESS);     // Request DAY RAM address at 04H
 
    DS1307_Write(dd);           // Write date on RAM address 04H
    DS1307_Write(mm);           // Write month on RAM address 05H
    DS1307_Write(yy);           // Write year on RAM address 06h
 
    I2C_Stop();             // Stop I2C communication after Setting the Date
}
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
 void DS1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
 -----------------------------------------------------------------------------------
 * I/P Arguments: char *,char *,char *-->pointers to get the hh,mm,ss.
 * Return value : none
 
 * description  :This function is used to get the Time(hh,mm,ss) from Ds1307 RTC.
                 Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                 After selecting DS1307, select the RAM address 0x00 to point to sec
                 Get Sec, MIN, Hour one after the other.
                 Stop the I2c communication.
-----------------------------------------------------------------------------------*/
void DS1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr)
{
     I2C_Start();           // Start I2C communication
 
    DS1307_Write(DS1307_ID);    // connect to DS1307 by sending its ID on I2c Bus
    DS1307_Write(SEC_ADDRESS);          // Request Sec RAM address at 00H
 
     I2C_Stop();            // Stop I2C communication after selecting Sec Register
 
    I2C_Start();                // Start I2C communication
    DS1307_Write(0xD1);         // connect to DS1307( under Read mode)
                                //by sending its ID on I2c Bus
 
  *s_ptr = DS1307_Read();  I2C_Ack();     // read second and return Positive ACK
  *m_ptr = DS1307_Read();  I2C_Ack();      // read minute and return Positive ACK
  *h_ptr = DS1307_Read();  I2C_NoAck();   // read hour and return Negative/No ACK
 
  I2C_Stop();               // Stop I2C communication after reading the Time
 }
 
 
 
 
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
 void DS1307_GetDate(unsigned char *y_ptr,unsigned char *m_ptr,unsigned char *d_ptr)
 -----------------------------------------------------------------------------------
 * I/P Arguments: char *,char *,char *-->pointers to get the y,m,d.
 * Return value : none
 
 * description  :This function is used to get the Date(y,m,d) from Ds1307 RTC.
                 Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
                 After selecting DS1307, select the RAM address 0x00 to point to DAY
                 Get Day, Month, Year one after the other.
                 Stop the I2c communication.
-----------------------------------------------------------------------------------*/
void DS1307_GetDate(unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr)
{
    I2C_Start();            // Start I2C communication
 
    DS1307_Write(DS1307_ID);    // connect to DS1307 by sending its ID on I2c Bus
    DS1307_Write(DATE_ADDRESS);     // Request DAY RAM address at 04H
 
    I2C_Stop();             // Stop I2C communication after selecting DAY Register
 
 
   I2C_Start();             // Start I2C communication
   DS1307_Write(0xD1);          // connect to DS1307( under Read mode)
                            // by sending its ID on I2c Bus
 
  *d_ptr = DS1307_Read(); I2C_Ack();     // read Day and return Positive ACK
  *m_ptr = DS1307_Read(); I2C_Ack();     // read Month and return Positive ACK
  *y_ptr = DS1307_Read(); I2C_NoAck();   // read Year and return Negative/No ACK
 
  I2C_Stop();         // Stop I2C communication after reading the Time
 }

Eeprom.c: 8051 At2404/02 C-Library
/*---------------------------------------------------------------------------------------*
                                8051 At2404/02  library
Filename: eeprom.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 
 ----------------------------------------------------------------------------------------*/
 
#include<reg51.h>
#include"i2c.h"
#include"delay.h"
 
 
/* EEPROM_ID is fixed and should not be changed,
   Refer At2404/02 DataSheet for more info*/
#define EEPROM_ID 0xA0
 
 
 
 
 
/*---------------------------------------------------------------------------------------
  void EEPROM_WriteByte(unsigned char eeprom_Address, unsigned char eeprom_Data)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,char-->eeprom_address at which eeprom_data is to be written.
 * Return value : none
 
 * description:This function is used to write the data at specified EEPROM_address..
               At2404 ic is enabled by sending its ID on the i2c bus.
               After selecting At2404 ic,select the address where the data is to written
               Write the Data at selected EppromAddress
               Stop the I2c communication.
----------------------------------------------------------------------------------------*/
void EEPROM_WriteByte(unsigned char eeprom_Address, unsigned char eeprom_Data)
{
 
    I2C_Start();               // Start i2c communication
    I2C_Write(EEPROM_ID);      // connect to AT2404 by sending its ID on I2c Bus
    I2C_Ack();
    I2C_Write(eeprom_Address); // Select the Specified EEPROM address of AT2404
    I2C_Ack();
    I2C_Write(eeprom_Data);    // Write the data at specified address
    I2C_Ack();
    I2C_Stop();                // Stop i2c communication after Writing the data
    delay_ms(1);            // Write operation takes max 5ms, refer At2404 datasheet        
}
 
 
 
 
 
 
 
 
 
 
 
 
/*-----------------------------------------------------------------------------------------
               unsigned char EEPROM_ReadByte(unsigned char eeprom_Address)
 ------------------------------------------------------------------------------------------
 * I/P Arguments: char-->eeprom_address from where eeprom_data is to be read.
 * Return value : char-->data read from Eeprom.
 
 * description:
           This function is used to read the data from specified EEPROM_address.
           At2404 ic is enabled by sending its ID on the i2c bus.
           After selecting At2404 ic,select the address from where the data is to read
           Read the Data from selected EppromAddress
           Stop the I2c communication.
           Return the Data read from Eeprom
-----------------------------------------------------------------------------------------*/
unsigned char EEPROM_ReadByte(unsigned char eeprom_Address)
{
  unsigned char eeprom_Data;
 
    I2C_Start();               // Start i2c communication
    I2C_Write(EEPROM_ID);      // connect to AT2404(write) by sending its ID on I2c Bus
    I2C_Ack();
    I2C_Write(eeprom_Address); // Select the Specified EEPROM address of AT2404
    I2C_Ack();
 
    I2C_Start();               // Start i2c communication
    I2C_Write(0xA1);           // connect to AT2404(read) by sending its ID on I2c Bus
    I2C_Ack();
    eeprom_Data = I2C_Read();  // Read the data from specified address
    I2C_NoAck();
    I2C_Stop();                // Stop i2c communication after Reading the data
    delay_us(10);
  return eeprom_Data;          // Return the Read data
 
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------------
void EEPROM_WriteNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the N-bytes are to be written.
                  char*-->Pointer to the N-bytes of data to be written.
                  char --> Number of bytes to be written
 
 * Return value : none
 
 * description:
            This function is used to write N-bytes of data at specified EEPROM_address.
            EEPROM_WriteByte() function is called to write a byte at atime.
            Source(RAM) and destination(EEPROM) address are incremented after each write
            NoOfBytes is Decemented each time a byte is written.
            Above Operation is carried out till all the bytes are written(NoOfBytes!=0)
---------------------------------------------------------------------------------------*/
void EEPROM_WriteNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 {
  while(NoOfBytes !=  0)
   {
    EEPROM_WriteByte(EepromAddr,*RamAddr); //Write a byte from RAM to EEPROM
        EepromAddr++;                      //Incerement the Eeprom Address
        RamAddr++;                         //Increment the RAM Address
        NoOfBytes--;                       //Decrement NoOfBytes after writing each Byte
       }
 }
 
 
 
/*---------------------------------------------------------------------------------------
void EEPROM_ReadNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the N-bytes is to be read.
                  char*-->Pointer into which the N-bytes of data is to be read.
                  char --> Number of bytes to be Read
 
 * Return value : none
 
 * description:
            This function is used to Read N-bytes of data from specified EEPROM_address.
            EEPROM_ReadByte() func is called to read a byte at a time.
            Source(RAM) and destination(EEPROM) address are incremented each time.
            NoOfBytes is Decemented after a byte is read.
            Above Operation is carried out till all the bytes are read(NoOfBytes!=0)
---------------------------------------------------------------------------------------*/
void EEPROM_ReadNBytes(unsigned char EepromAddr, unsigned char *RamAddr, char NoOfBytes)
 {
   while(NoOfBytes !=  0)
    {
     *RamAddr = EEPROM_ReadByte(EepromAddr);//Read a byte from EEPROM to RAM
        EepromAddr++;                       //Incerement the Eeprom Address
        RamAddr++;                          //Increment the RAM Address
        NoOfBytes--;                        //Decrement NoOfBytes after Reading each Byte
     }
 }
 
 
 
 
 
 
 
/*---------------------------------------------------------------------------------------
 void EEPROM_WriteString(unsigned char eeprom_address, unsigned char * source_address)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address where the String is to be written.
                  char*-->Pointer to String which has to be written.
 
 * Return value : none
 
 * description:This function is used to Write a String at specified EEPROM_address.
               EEPROM_WriteByte() function is called to write a byte at a time.
               Source(RAM) and destination(EEPOM) address are incremented each time.
               Above Operation is carried out till Null char is identified.
 
   NOTE: Null char is also written into the eeprom.
---------------------------------------------------------------------------------------*/
void EEPROM_WriteString(unsigned char eeprom_address, unsigned char * source_address)
  {
 
   do 
    {
      EEPROM_WriteByte(eeprom_address,*source_address); //Write a byte from RAM to EEPROM
        source_address++;                               //Incerement the RAM Address
        eeprom_address++;                               //Increment the Eeprom Address
      } while(*(source_address-1) !=0);
  }
 
 
 
 
/*---------------------------------------------------------------------------------------
void EEPROM_ReadString(unsigned char eeprom_address, unsigned char * destination_address)
 ----------------------------------------------------------------------------------------
 * I/P Arguments: char,-->eeprom_address from where the String is to be read.
                  char*-->Pointer into which the String is to be read.
 
 * Return value : none
 
 * description:This function is used to Read a String from specified EEPROM_address.
               EEPROM_ReadByte() function is called to read a byte at a time.
               Source(EEPROM) and destination(RAM) address are incremented each time.
               Above Operation is carried out till Null char is identified.
---------------------------------------------------------------------------------------*/
void EEPROM_ReadString(unsigned char eeprom_address, unsigned char * destination_address)
  {
   char eeprom_data;
 
     do
     {
      eeprom_data = EEPROM_ReadByte(eeprom_address); //Read a byte from EEPROM to RAM
        *destination_address = eeprom_data;          //Copy the data into String Buffer
         destination_address++;                      //Incerement the RAM Address
         eeprom_address++;                           //Increment the Eeprom Address
        }while(eeprom_data!=0);
  }
 
 
 
 
 
 
 
 
/*-----------------------------------------------------------------------------------------
                                   void EEPROM_Erase()
 ------------------------------------------------------------------------------------------
 * I/P Arguments: none
 
 * Return value : none
 
 * description:This function is used to erase the entire Eeprom memory.
               Eeprom is filled with 0xFF to accomplish the Eeprom Erase.
               EEPROM_WriteByte() function is called to write a byte at a time.
               Whole memory(0-255) is traversed and filled with 0xFF
-----------------------------------------------------------------------------------------*/
  void EEPROM_Erase()
   {
     unsigned char eeprom_address;
 
     for(eeprom_address=0;eeprom_address<255;eeprom_address++)
        {
           EEPROM_WriteByte(eeprom_address,0xff); // Write Each memory location with OxFF
          }
   }
Category: Code Libraries
Announcements
image
Software Engineer Recruitment


 
