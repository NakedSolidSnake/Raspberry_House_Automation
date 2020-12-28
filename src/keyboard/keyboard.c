#include "keyboard"

void Keyboard_read(char *buffer)
{
    fgets(buffer, sizeof(buffer), stdin);
}