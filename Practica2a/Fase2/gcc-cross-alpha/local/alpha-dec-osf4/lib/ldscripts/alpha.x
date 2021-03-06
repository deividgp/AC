/* Default linker script, for normal executables */
OUTPUT_FORMAT("ecoff-littlealpha")
SEARCH_DIR("$GCC_CROSS_ALPHA/local/alpha-dec-osf4/lib");
/* sree: fix missing symbols error for _DYNAMIC_LINK and _BASE_ADDRESS
   when linking. Note values are correct only for static 64-bit
   binaries
*/
/* supports only 0=non-shared (static); other possible
   vals: 1=call_shared, 2=shared, see _DYNAMIC_LINK(3) on
   OSF/1
*/
_DYNAMIC_LINK = 0;
/* ZMAGIC 64-bit start, it's 0x12000000 for 32-bit, see end(3) */
_BASE_ADDRESS = 0x120000000;
ENTRY(__start)
SECTIONS
{
  . = 0x120000000 + SIZEOF_HEADERS;
  .text : {
     _ftext = . ;
     __istart = . ;
     *(.init)
     LONG (0x6bfa8001)
     eprol  =  .;
    *(.text)
     __fstart = . ;
     *(.fini)
     LONG (0x6bfa8001)
     _etext  =  .;
  }
  .rdata : {
    *(.rdata)
  }
  .rconst : {
    *(.rconst)
  }
  .pdata : {
     _fpdata = .;
    *(.pdata)
  }
  . = 0x140000000;
  .data : {
     _fdata = .;
    *(.data)
    CONSTRUCTORS
  }
  .xdata : {
    *(.xdata)
  }
   _gp = ALIGN (16) + 0x8000;
  .lit8 : {
    *(.lit8)
  }
  .lita : {
    *(.lita)
  }
  .sdata : {
    *(.sdata)
  }
   _EDATA  =  .;
   _FBSS = .;
  .sbss : {
    *(.sbss)
    *(.scommon)
  }
  .bss : {
    *(.bss)
    *(COMMON)
  }
   _end = .;
}
/* sree: more undefined symbols */
PROVIDE(_fpdata_size = SIZEOF(.pdata) / 8);
/* have no clue of what these really are */
PROVIDE(_gpinfo = 0);
PROVIDE(_DYNAMIC = 0);
