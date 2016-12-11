#ifndef _LCD_H
#define _LCD_H

//              LCD DEFINE SYMBOLS
//--COMMAND CONSTANTS
#define CLEAR           0x01    //requires delay cylce of min 57 NOPs
#define HOME            0x02
#define ENTRY_MODE      0x04
#define DISPLAY_CTRL    0x08
#define SHIFT           0x10
#define FUNCTION_SET    0x20
#define RAM_CG          0x40
#define RAM_DD          0x80
#define BF_AC           0x80    //Read Busy flag (DB7) and AC (DB6-0)
//--COMMAND OPTIONS
#define INCR            0x02
#define DISPLAY_SHIFT   0x01
#define DISPLAY_ON      0x04
#define CURSOR_ON       0x02
#define BLINK           0x01
#define DISPLAY         0x08
#define RIGHT           0x04
#define EIGHT_BITS      0x10
#define TWO_LINE        0x08
//--

extern void InitLCD(void);
extern void LCD_Clear(void);
extern void LCD_Putch(char ch);
extern void SwitchCurPosControl(bit o);//Switches on/off the current 
//position control when symbols are put through LCD_Putch() (on by default)
extern void LCD_SwitchCursor(bit cursor,bit blink);
extern void LCD_GotoXY(unsigned char x,bit y);
extern void LCD_Type(char *s);

extern void LCD_Print(unsigned char xdata *s, bit y, char last_position, char lenght);
extern void LCD_Print_char(unsigned char ch, unsigned char x, bit y);
extern void LCD_clean_data(bit y);

#endif //_LCD_H
