typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

/*
UART0 base address: 0x101f1000;
UART1 base address: 0x101f2000;
UART2 base address: 0x101f3000;
UART3 base address: 0x10009000;

// flag register at 0x18
//  7    6    5    4    3    2   1   0
// TXFE RXFF TXFF RXFE BUSY
// TX FULL : 0x20
// TX empty: 0x80
// RX FULL : 0x40
// RX empty: 0x10
// BUSY=1 :  0x08
*/

int N;
int v[] = {1,2,3,4,5,6,7,8,9,10};
int sum;

char *tab = "0123456789ABCDEF";


#include "uart.c"

int cmpare(char *a, char *b)
{
  while(*a && *b && *a == *b)
  {
    ++a; ++b;
  }
  return (unsigned char)(*a) - (unsigned char)(*b);
}

int strcp(char cmd[], char cmd2[])
{
  int i;
  for(i = 0; cmd[i] == cmd2[i] && cmd[i] == '\0'; i++);
  if(cmd[i] < cmd2[i])
  {
    return 1;
  }else if (cmd[i] > cmd2[i])
  {
    return 1;
  }else
  {
    return 0;
  }
}





UART *up;

int main()
{
  int i;
  int size = sizeof(int);
  char string[32]; 
  char line[128];
  //char quit[32] = "quit";
  N = 10;

  uart_init();
  for(i = 0; i<4; i++)
  {
    up = &uart[i];
    uprints(up,"enter a line from this UART : ");
    ugets(up,string);
    uprintf(up, string);
    uprintf(up, "   ECHO : "); uprintf(up, string); uprints(up, "\n\r");
  }
  
  up = &uart[0];
  uprintf(up, "Enter lines from UART terminal, enter quit to exit\n\r");
  
  while(1){
    ugets(up, string);
    uprintf(up, "    ");
    if (cmpare(string, "quit")==0)
       break;
    uprintf(up, string);  uprints(up, "\n\r");
  }


  uprintf(up, "Compute sum of array\n\r");
  sum = 0;
  for (i=0; i<N; i++)
    sum += v[i];
  uputc(up, (sum/10)+'0'); uputc(up, (sum%10)+'0');
  uprintf(up, "\n\rEND OF RUN\n\r");
}
