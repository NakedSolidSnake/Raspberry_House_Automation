#ifndef OUTPUT_H_
#define OUTPUT_H_

typedef enum
{
    output, 
    input
} Output;

typedef enum
{
    State_Off,
    State_On
} State;

void Output_Init(void);
void Output_SetState(State state);



#endif /* OUTPUT_H_ */
