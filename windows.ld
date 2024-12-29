/**
 * Removes the spam of ".ident" strings (around 50 KB), such as:
 * "GCC: (Rev3, Built by MSYS2 project) 14.1.0",
 * found in every compiled object file (and some static libraries).
 */
SECTIONS
{
  /DISCARD/ : { *(.rdata$zzz) }
}
INSERT BEFORE .rdata;
