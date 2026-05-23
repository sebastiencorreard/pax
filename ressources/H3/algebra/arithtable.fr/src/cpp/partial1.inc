\text{shr=shuffle(ROWS)}
\text{shc=shuffle(COLS)}
\text{matrix=wims(lines2rows \matrix[\shr;\shc])}
\text{mlist=wims(replace ; by , in \matrix)}
\text{replylist=wims(positionof item 0 in \mlist)}
\text{givenlist=wims(positionof item 1 in \mlist)}

\text{replies=item(1..(ROWS*COLS),r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16)}
\steps{\replies[\replylist]}
