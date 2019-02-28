/*********** t.c file of A Multitasking System *********/

#include "type.h"
#include "string.c"
#define printf kprintf
#define putchar kputc
/******** function prototypes *****************/
int body();
int tswitch();
int do_exit();

PROC proc[NPROC];      // NPROC PROCs
PROC *freeList;        // freeList of PROCs 
PROC *readyQueue;      // priority queue of READY procs
PROC *running;         // current running proc pointer
PROC *sleepList;
int procsize = sizeof(PROC);

#include "kbd.c"
#include "queue.c"
#include "uart.c"
#include "pv.c"
#include "pipe.c"
#include "timer.c"
#include "vid.c"
#include "exceptions.c"
#include "wait.c" 

/*******************************************************
  kfork() creates a child process; returns child pid.
  When scheduled to run, child PROC resumes to body();
********************************************************/

// initialize the MT system; create P0 as initial running process
int init() 
{
  int i;
  PROC *p;
  for (i=0; i<NPROC; i++){ // initialize PROCs
    p = &proc[i];
    p->pid = i;            // PID = 0 to NPROC-1  
    p->status = FREE;
    p->priority = 0;      
    p->next = p+1;
  }
  proc[NPROC-1].next = 0;  
  freeList = &proc[0];     // all PROCs in freeList     
  readyQueue = 0;          // readyQueue = empty
  sleepList = 0;
  
  // create P0 as the initial running process
  p = running = dequeue(&freeList); // use proc[0] 
  p->status = READY;
  p->ppid = 0;             // P0 is its own parent

  p->parent = p;
  p->child = 0;
  p->sibling = 0;
  
  printList("freeList", freeList);
  printf("init complete: P0 running\n"); 
}

void copy_vectors(void) {
    extern u32 vectors_start;
    extern u32 vectors_end;
    u32 *vectors_src = &vectors_start;
    u32 *vectors_dst = (u32 *)0;
    while(vectors_src < &vectors_end)
       *vectors_dst++ = *vectors_src++;
}

TIMER *tp[4];


void IRQ_handler()
{
    int vicstatus, sicstatus;
    int ustatus, kstatus;

    // read VIC SIV status registers to find out which interrupt
    vicstatus = VIC_STATUS;
    sicstatus = SIC_STATUS;
    if(vicstatus & (1<<4)){
      if(*(tp[0]->base+TVALUE)==0){
        timer_handler(0);
      }
    }  
    if (vicstatus & 0x80000000){ // SIC interrupts=bit_31=>KBD at bit 3 
       if (sicstatus & 0x08){
          kbd_handler();
       }
    }
}


int INIT()
{
  int pid, status;
  PIPE *p = &pipe;
  pipe_init();
  printf("P1 running: create pipe and writer reader processes\n");
  kpipe();
  kfork(pipe_writer);
  kfork(pipe_reader);
  printf("P1 waits for ZOMBIE child\n");
  while(1){
    pid = kwait(&status);
    if (pid < 0){
      printf("no more child, P1 loops\n");
      while(1);
    }
    printf("P1 buried a ZOMBIE child %d\n", pid);
  }
}
  
int kfork(int func)
{
  int i;
  PROC *p = dequeue(&freeList);
  if (p==0){
    kprintf("kfork failed\n");
    return -1;
  }
  p->ppid = running->pid;
  p->parent = running;
  p->status = READY;
  p->priority = 1;


   if(p->parent->child == 0){
    p->parent->child = p;
  }else{  //if there is a child, go throught the siblings
    PROC *temp = p->parent->child;
    while(temp->sibling != 0){
      temp = temp->sibling;
    }
    temp->sibling = p;
  }

  p->sibling = 0;
  p->child = 0;

  
// set kstack to resume to body
//  HIGH    -1  -2  -3  -4  -5 -6 -7 -8 -9 -10 -11 -12 -13 -14
//        ------------------------------------------------------
// kstack=| lr,r12,r11,r10,r9,r8,r7,r6,r5, r4, r3, r2, r1, r0
//        -------------------------------------------------|----
//	                                              proc.ksp
  for (i=1; i<15; i++)
    p->kstack[SSIZE-i] = 0;        // zero out kstack

  p->kstack[SSIZE-1] = (int)func;  // saved lr -> body()
  p->ksp = &(p->kstack[SSIZE-14]); // saved ksp -> -14 entry in kstack
 
  enqueue(&readyQueue, p);
  return p->pid;
}
/*************** main() function ***************/
int main()
{
  int pid, status;
  fbuf_init();
  kbd_init();
     VIC_INTENABLE |= (1<<31); // SIC to VIC's IRQ31
   /* enable KBD IRQ */
  // VIC_INTENABLE |= (1<<4);  // timer0,1 at bit4 
   SIC_INTENABLE = (1<<3); // KBD int=bit3 on SIC
   SIC_ENSET = (1<<3);  // KBD int=3 on SIC
   printf("Welcome to the MT Multitasking System\n");
   init();    // initialize system; create and run P0

   kfork(INIT);

   printList("readyQueue", readyQueue);
   while(1){
     printf("P0 switch process\n");
     while(!readyQueue);
     tswitch();
   }
}

/*********** scheduler *************/
int scheduler()
{ 
  //  printf("proc %d in scheduler()\n", running->pid);
  if (running->status == READY)
     enqueue(&readyQueue, running);
  //printList("readyQueue", readyQueue);
  running = dequeue(&readyQueue);
  //printf("next running = %d\n", running->pid);  
}
