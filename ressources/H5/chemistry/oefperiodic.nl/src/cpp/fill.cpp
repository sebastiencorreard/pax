target=fill3 fill4 fill5 fill6 fill8 fill10 fill14 fill20 fill33 fill54 fill62 fill103 fill108

#include "header.inc"
#include "confparm.inc"

\integer{redund=0}

#if defined TARGET_fill3
# define NUM 3
#endif
#if defined TARGET_fill4
# define NUM 4
#endif
#if defined TARGET_fill5
# define NUM 5
#endif
#if defined TARGET_fill6
# define NUM 6
#endif
#if defined TARGET_fill8
# define NUM 8
#endif
#if defined TARGET_fill10
# define NUM 10
#endif
#if defined TARGET_fill14
# define NUM 14
#endif
#if defined TARGET_fill20
# define NUM 20
#endif
#if defined TARGET_fill33
# define NUM 3 + 3
 \integer{redund=3}
#endif
#if defined TARGET_fill54
# define NUM 5 + 4
 \integer{redund=4}
#endif
#if defined TARGET_fill62
# define NUM 6 + 2
 \integer{redund=2}
#endif
#if defined TARGET_fill103
# define NUM 10 + 3
 \integer{redund=3}
#endif
#if defined TARGET_fill108
# define NUM 10 + 8
 \integer{redund=8}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{cnt=wims(word 1 of NUM)}

#include "position.inc"

\integer{cnt=min(\cnt,\pdatacnt)}
\text{sh=item(1..\cnt+\redund,shuffle(\pdatacnt))}
\text{sh=wims(sort numeric items \sh)}
\text{data=row(\sh,\pdata)}
\text{symb=\data[;2]}
\text{rsymb=\redund>0 and \pdatacnt>\cnt?;\symb[\cnt+1..\cnt+\redund]:}
text{symb=wims(replace internal , by </small>,<small> in <small>\symb</small>)}
\text{fields=}
\integer{xs=35}
\integer{ys=30}
\for{t=1 to \cnt}{
 \integer{x=\data[\t;3]>8?\data[\t;4]*\xs+\xs*2+1:\data[\t;4]*\xs+1}
 \integer{y=\data[\t;3]>8?\data[\t;3]*\ys+6:\data[\t;3]*\ys+1}
 \text{fields=\fields
r\t,\x x \y}
}

\text{size=\xs-1 x \ys-1}
\text{answers=item(1..\cnt,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20)}
\steps{\answers}

\statement{\name_instruction
<div class="wimscenter">
\special{imagefill \imagedir/table2.gif,700x360,\size
\fields
}
</div>
}

\text{size=\xs x \ys-1}

\answer{\name_case 1}{\symb[1]\rsymb}{type=dragfill}
\answer{\name_case 2}{\symb[2]}{type=dragfill}
\answer{\name_case 3}{\symb[3]}{type=dragfill}
\answer{\name_case 4}{\symb[4]}{type=dragfill}
\answer{\name_case 5}{\symb[5]}{type=dragfill}
\answer{\name_case 6}{\symb[6]}{type=dragfill}
\answer{\name_case 7}{\symb[7]}{type=dragfill}
\answer{\name_case 8}{\symb[8]}{type=dragfill}
\answer{\name_case 9}{\symb[9]}{type=dragfill}
\answer{\name_case 10}{\symb[10]}{type=dragfill}
\answer{\name_case 11}{\symb[11]}{type=dragfill}
\answer{\name_case 12}{\symb[12]}{type=dragfill}
\answer{\name_case 13}{\symb[13]}{type=dragfill}
\answer{\name_case 14}{\symb[14]}{type=dragfill}
\answer{\name_case 15}{\symb[15]}{type=dragfill}
\answer{\name_case 16}{\symb[16]}{type=dragfill}
\answer{\name_case 17}{\symb[17]}{type=dragfill}
\answer{\name_case 18}{\symb[18]}{type=dragfill}
\answer{\name_case 19}{\symb[19]}{type=dragfill}
\answer{\name_case 20}{\symb[20]}{type=dragfill}

