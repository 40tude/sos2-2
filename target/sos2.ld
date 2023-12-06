ENTRY(start)

SECTIONS {
    . = 2M;

    .zoubida :
    {
      /* ensure that the multiboot header is at the beginning */
      *(.multiboot_header)
    }

    .text : ALIGN(CONSTANT(MAXPAGESIZE)) 
    {
      *(.text)
    }
    
    .data : ALIGN(CONSTANT(MAXPAGESIZE)) 
    {   
      *(.data*) 
    }

    .rodata : ALIGN(CONSTANT(MAXPAGESIZE)) 
    {   
      *(.rodata*)
    }

    .bss : ALIGN(CONSTANT(MAXPAGESIZE)) 
    {   
      *(.bss)
      /* *(COMMON) */
    }

    /DISCARD/ :{
      *(.comment)
    }
}
