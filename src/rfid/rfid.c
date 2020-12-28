#include "rfid.h"

void RFID_Init(void)
{

}

void RFID_NewCardPresent(void)
{

}

void RFID_Read(char *buffer)
{
    fgets(buffer, sizeof(buffer), stdin);
}

void RFID_Write(const char *text)
{
    printf("RFID: %s",text);
}

