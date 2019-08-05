#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart_sms_functions.h"


ISR(USART_RX_vect)
{
  read_uart_0();
}
int main()
{
   sei();
   init_uart_0(103);
  while(1)
{
  send_sms(1,"how are you?");
  break;
}
  
}
