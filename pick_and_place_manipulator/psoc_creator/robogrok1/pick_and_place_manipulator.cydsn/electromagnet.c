#include "electromagnet.h"

void electromagnet_on()
{
    electromagnet_1_Write(1);
}
void electromagnet_off()
{
    electromagnet_1_Write(0);
}