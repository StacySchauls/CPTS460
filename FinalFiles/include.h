typedef unsigned long long  u64;
typedef unsigned long       u32;
typedef unsigned short      u16;
typedef unsigned char       u8;
typedef unsigned short      ushort;
typedef unsigned long       ulong;

#include "include/asm.h"
#include "include/isr.h"
#include "include/kernel.h"
#include "include/libcc.h"

int printk(char *fmt,...);

#define printf printk
#define DUMP  0
#define PANIC 1

typedef struct tss{
	unsigned int back_link;
	unsigned int esp0, ss0;
	unsigned int esp1, ss1;
	unsigned int esp2, ss2;
	unsigned int cr3;
	unsigned int eip;
	unsigned int eflags;
	unsigned int eax,ecx,edx,ebx;
	unsigned int esp, ebp;
	unsigned int esi, edi;
	unsigned int es, cs, ss, ds, fs, gs;
	unsigned int ldt;
	unsigned int iobitmap;
} TSS;

#define NPROC     8
#define SSIZE  1024

#define FREE      0           /* PROC status */
#define READY     1 
#define SLEEP     2
#define ZOMBIE    3
#define BLOCK     4

typedef struct proc{
  struct proc *next;                    /*   0 */
        int    *saved_sp;               /*   4 */
        int     pid;
        int     ppid;
        int     status;
        int     pri;           /* scheduling priority */

  struct proc *parent;         /* pointer to parent proc */
         int   event;          /* event to sleep on */  
         char *deathCry;       /* last gasp when dying */
  char name[32];

         TSS  tss;                      /* 104 */
  unsigned long long tss_entry;         /*   8 */
  unsigned long long ldt[2];            /*  16 */
  unsigned long long ldt_entry;         /*   8 */
  u32 paddress;
        int   kstack[SSIZE];  /* per task kstack is now in PROC */
}PROC;        

extern PROC *running;
