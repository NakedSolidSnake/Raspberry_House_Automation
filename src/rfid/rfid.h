#ifndef RFID_H_
#define RFIDT_H_

#include <stdbool.h>

bool RFID_Init(void);
bool RFID_NewCardPresent(void);
void RFID_Read(char *buffer);
void RFID_Write(const char *text);

#endif /* RFIDT_H_ */