#include "macros.h"

.global _keyboard_handler_asm

.text
_keyboard_handler_asm:
       xor %eax, %eax
       inb $STAT_REG
       test $OBF, %eax
       jz  ERR
       test $PAR_ERR, %eax
       jnz ERR
       test $TO_ERR, %eax
       jnz ERR
       inb $OUT_BUFF
       jmp END
ERR:
       movl $-1, %eax
END:
       ret
