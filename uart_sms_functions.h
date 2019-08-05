
const int BUFFER_SIZE = 512;

int bufferposition=0;
int sendsms=0;

char mybuffer[BUFFER_SIZE];

void init_uart_0(unsigned int MYUBRR)
{ 
  UBRR0H= MYUBRR>>8;
  UBRR0L=MYUBRR;
  UCSR0B|=(1<<RXCIE0|1<<TXEN0|1<<RXEN0);
  UCSR0C=(3<<UCSZ00);
  
}


void uart_0_print_char(char ch){
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = ch;
}

void write_uart_0(char const *data){
  for (;*data;++data) 
  {
    uart_0_print_char(*data);
  }
}

char uart_0_read_char(){
  char chr;
  chr=UDR0;
  return chr;
}

void read_uart_0()
{int i=0;
  mybuffer[bufferposition]= uart_0_read_char();
  bufferposition++;
  if(bufferposition==200)
  	{
  		bufferposition=0;
  	}
}

 void clear_buffer()
 {int i=0;
  for(i=0;i<BUFFER_SIZE;i++)
  {
    mybuffer[i]=0x00;
  }
  bufferposition=0;
 }
 void command_uart_0(char const *write,  char const *response)
{
	while(1)
	{
	write_uart_0(write);
	_delay_ms(1000);
	if((strstr(mybuffer,response)))
	{
		break;
	}
	
}

}

    void send_sms(unsigned int sms_flag,char const *sms)
{
  while(1)
  {
    switch(sms_flag)
{
  case 1:
    write_uart_0("AT\n\r");
    //read_uart_0();

     if((strstr(mybuffer,"OK")))
      {
        sms_flag++;
      }
  break;
    //check  for the response
  case 2:
    write_uart_0("AT+CMGF=1\r\n");

      if(!(strstr(mybuffer,"OK")))
    {
      sms_flag-=1;
    }
    else
    {
      sms_flag++;
    }
  break;

  case 3:
    write_uart_0("AT+CMGS=\"0792766237\"\r\n");

    if(!(strstr(mybuffer,">")))
    {
      sms_flag-=1;
    }
    else
    {
      sms_flag++;
    }
  break;

  case 4:
    write_uart_0(sms);
    uart_0_print_char(26);
  uart_0_print_char('\r');
      
  break;
  
  default:
  sendsms=0;
    sms_flag=0;
  break;
 
}
  }
}