#include "rfid.h"

bool RFID_Init(void)
{
    return true;
}

bool RFID_NewCardPresent(void)
{
    return true;
}

void RFID_Read(char *buffer)
{
    fgets(buffer, sizeof(buffer), stdin);
}

void RFID_Write(const char *text)
{
    printf("RFID: %s",text);
}

