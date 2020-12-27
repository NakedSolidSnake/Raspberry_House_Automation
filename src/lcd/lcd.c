#include "lcd.h"

void LCD_Init(void)
{
    printf("Inicializando Display...");
}

void LCD_Clear(void)
{
    printf("\n");
}

void LCD_Out(char linha,char coluna, char *text )
{
    printf("%s",text);
}