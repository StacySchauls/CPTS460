// timer.c file
/***** timer confiuguration values *****/
#define CTL_ENABLE          ( 0x00000080 )
#define CTL_MODE            ( 0x00000040 )
#define CTL_INTR            ( 0x00000020 )
#define CTL_PRESCALE_1      ( 0x00000008 )
#define CTL_PRESCALE_2      ( 0x00000004 )
#define CTL_CTRLEN          ( 0x00000002 )
#define CTL_ONESHOT         ( 0x00000001 )

// timer register offsets from base address
/** u32 * offsets **/
#define TLOAD   0x0
#define TVALUE  0x1
#define TCNTL   0x2
#define TINTCLR 0x3
#define TRIS    0x4
#define TMIS    0x5
#define TBGLOAD 0x6

typedef volatile struct timer{
  u32 *base;            // timer's base address; as u32 pointer
  int tick, hh, mm, ss; // per timer data area
  char clock[16]; 
}TIMER;

volatile TIMER timer[4];  // 4 timers; 2 timers per unit; at 0x00 and 0x20

int kprintf(char *fmt, ...);
int kpchar(char, int, int);
int unkpchar(char, int, int);
void timer_stop(int n);
int timer_clearInterrupt(int n);
void timer_start(int n);
int clrcursor();
int putcursor();


int strcpy1(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}

void timer_init()
{
  int i;
  TIMER *tp;
  kprintf("timer_init()\n");

  for (i=0; i<4; i++){
    tp = &timer[i];
    if (i==0) tp->base = (u32 *)0x101E2000; 
    if (i==1) tp->base = (u32 *)0x101E2020; 
    if (i==2) tp->base = (u32 *)0x101E3000;//#include "pipe.c"0; 
    if (i==3) tp->base = (u32 *)0x101E3020;
    *(tp->base+TLOAD) = 0x0;   // reset
    *(tp->base+TVALUE)= 0xFFFFFFFF;
    *(tp->base+TRIS)  = 0x0;
    *(tp->base+TMIS)  = 0x0;
    *(tp->base+TLOAD) = 0x100;
    *(tp->base+TCNTL) = 0x62; //011-0000=|NOTEn|Pe|IntE|-|scal=00|32-bit|0=wrap|
    *(tp->base+TBGLOAD) = 0xF000;
    tp->tick = tp->hh = tp->mm = tp->ss = 0;
    strcpy1((char *)tp->clock, "00:00:00");
  }
}

void timer_handler(int n) {
    u32 ris, mis, value, load, bload, i;
    TIMER *t = &timer[n];
    //int sr = getsr();

    t->tick++; 
    t->tick %= 16;

    if (t->tick == 8) 
       clrcursor();
    if (t->tick == 0){
      //kprintf("timer mode=%x ", sr&0x1F);
      putcursor();
      t->ss++;
      t->ss %= 60;
      if (t->ss==0){
         t->mm++;
         t->mm %= 60;
  
        if (t->mm==0){
           t->hh++;
           t->hh %= 24;
        }
      }

      t->clock[7]='0'+(t->ss%10); t->clock[6]='0'+(t->ss/10);
      t->clock[4]='0'+(t->mm%10); t->clock[3]='0'+(t->mm/10);
      t->clock[1]='0'+(t->hh%10); t->clock[0]='0'+(t->hh/10);
    } 
    //color = GREEN;
    for (i=0; i<8; i++){
       kpchar(t->clock[i], n, 70+i);
    }
    // must clear timer interrupt
    timer_clearInterrupt(n);
    return;
} 

void timer_start(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];

  kprintf("timer_start %d base=%x\n", n, tp->base);
  *(tp->base+TCNTL) |= 0x80;  // set enable bit 7
}

int timer_clearInterrupt(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];
  *(tp->base+TINTCLR) = 0xFFFFFFFF;
}

void timer_stop(int n) // timer_start(0), 1, etc.
{
  TIMER *tp = &timer[n];
  *(tp->base+TCNTL) &= 0x7F;  // clear enable bit 7
}

