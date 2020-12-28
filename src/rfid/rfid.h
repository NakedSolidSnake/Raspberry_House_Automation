#ifndef RFID_H_
#define RFIDT_H_

void RFID_Init(void);
void RFID_NewCardPresent(void);
void RFID_Read(char *buffer);
void RFID_Write(const char *text);

#endif /* RFIDT_H_ */