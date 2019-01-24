
#include "defines.h"
#include "vid.c"
#include "uart.c"
/*
typedef struct uart{
  char *base;
  int  n;
}UART;
*/
UART uart[4];

extern char _binary_wsu_bmp_start;

int color;
UART *up;


/*
int show_bmp(char *p, int start_row, int start_col)
{
  int h,w,pixel,rsize,i,j;
  unsigned char r, g, b;
  char *pp;
  int *q = (int *)(p+14);
  w = *(q + 1);
  h = *(q + 2);
  p += 54;

  rsize = 4*((3*w + 3) /4);
  p+= (h-1)*rsize;
  for(i = start_row; i<start_row + h; i++)
  {
    pp = p;
    for(j=start_col; j<start_col+w; j++)
    {
      b = *pp; g = *(pp+1); r = *(pp+2);
      pixel = (b << 16) | (g<<8) | r;
      fb[i*WIDTH + j] = pixel;
      pp += 3;
    }
    p -= rsize;
  }
  uprintf("\nBMP image height=%d width=%d\n",h,w);
}

*/


int main()
{
   char c, *p;
   int mode;
   uart_init();
   up = &uart[0];

   mode = 0;
   fbuf_init();

   p = &_binary_wsu_bmp_start;
   show_bmp(p, 0, 0); 

   while(1){
    // kprintf("enter a key from this UART : ");
     ugetc(up);
     p = &_binary_wsu_bmp_start;
     show_bmp(p, 0, 0);
   }
   while(1);   // loop here  
}
