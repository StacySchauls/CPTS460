ENTRY(start)
SECTIONS
{
   . = 0x10000;
   .start . : { ts.o(.text) }
   .text : { *(.text) }
   .data : { *(.data) }
   .bss : { *(.bss COMMON) }

   . = ALIGN(8);
   . = . + 0x10000; /* 0x1000 for 4KB; x10000=64kB of stack memory */
   stack_top = .;
}
