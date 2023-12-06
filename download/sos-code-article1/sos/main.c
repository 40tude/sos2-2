/* Copyright (C) 2004  The SOS Team
   Copyright (C) 1999  Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. 
*/

/* Include definitions of the multiboot standard */
#include <bootstrap/multiboot.h>
#include <sos/klibc.h>
#include <sos/assert.h>
#include <drivers/x86_videomem.h>
#include <drivers/bochs.h>



/* The C entry point of our operating system */
void sos_main(unsigned long magic, unsigned long addr)
{
  unsigned i;

  /* Grub sends us a structure, called multiboot_info_t with a lot of
     precious informations about the system, see the multiboot
     documentation for more information. */
  multiboot_info_t *mbi;
  mbi = (multiboot_info_t *) addr;

  /* Setup bochs and console, and clear the console */
  sos_bochs_setup();

  sos_x86_videomem_setup();
  sos_x86_videomem_cls(SOS_X86_VIDEO_BG_BLUE);

  /* Greetings from SOS */
  if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
    /* Loaded with Grub */
    sos_x86_videomem_printf(1, 0,
			    SOS_X86_VIDEO_FG_YELLOW | SOS_X86_VIDEO_BG_BLUE,
			    "Welcome From GRUB to %s%c RAM is %dMB (upper mem = 0x%x kB)",
			    "SOS", ',',
			    (unsigned)(mbi->mem_upper >> 10) + 1,
			    (unsigned)mbi->mem_upper);
  else
    /* Not loaded with grub */
    sos_x86_videomem_printf(1, 0,
			    SOS_X86_VIDEO_FG_YELLOW | SOS_X86_VIDEO_BG_BLUE,
			    "Welcome to SOS");

  sos_bochs_putstring("Message in a bochs\n");


  /* An operatig system never ends */
  for (;;)
    continue;

  return;
}
