#if defined TARGET_ratio2
\text{ETAPE=}
\if{\step=1}{\text{ETAPE=r1}
\text{conditions=1}}
\if{\step=2 and \var1==part}{
  \text{ETAPE=r2,r3,r4,r5,r6,r7}
  \text{conditions=1}}
\if{\step=2 and \var1==proportion}{
  \text{ETAPE=wims(makelist r x for x=8 to 24)}
  \text{conditions=1}}
\if{\step=2 and \var1==tableau}{
  \text{ETAPE=r25,r26,r27,r28,r29,r30,r31}
  \text{conditions=1}}
\if{\step=2 and \var1==répondre}{
\text{ETAPE=r32,r33}
\text{conditions=1}}
#endif
#if defined TARGET_ratio3
\text{ETAPE=}
\if{\step=1}{\text{ETAPE=r1}
\text{conditions=1}}
\if{\step=2 and \var1==part}{
\text{ETAPE=r2,r3,r4,r5,r6,r7,r8,r9}
\text{conditions=1}}
\if{\step=2 and \var1==répondre}{
\text{ETAPE=r48,r49,r50}
\text{conditions=1}}
\if{\step=2 and \var1==proportion}{
  \text{ETAPE=wims(makelist r x for x=10 to 37)}
  \text{conditions=1}}
\if{\step=2 and \var1==tableau}{
  \text{ETAPE=wims(makelist r x for x=38 to 47)}
  \text{conditions=1}}
#endif
#if defined TARGET_utilratio2
\text{ETAPE=}
\if{\step=1}{\text{ETAPE=r1}
\text{conditions=1}}
\if{\step=2 and \var1==part}{
  \text{ETAPE=r3,r4,r5,r6,r7}
  \text{conditions=1}}
\if{\step=2 and \var1==tableau}{
  \text{ETAPE=r8,r9,r10,r11,r12}
  \text{conditions=1}}
\if{\step=2 and \var1==répondre}{
\text{ETAPE=r2}
\text{conditions=1}}
#endif
#if defined TARGET_utilratio3
\text{ETAPE=}
\if{\step=1}{\text{ETAPE=r1}
\text{conditions=1}}
\if{\step=2 and \var1==part}{
  \text{ETAPE=r4,r5,r6,r7,r8,r9,r10,r11}
  \text{conditions=1}}
\if{\step=2 and \var1==tableau}{
  \text{ETAPE=r12,r13,r14,r15,r16,r17,r18,r19}
  \text{conditions=1}}
\if{\step=2 and \var1==répondre}{
\text{ETAPE=r2,r3}
\text{conditions=1}}
#endif
