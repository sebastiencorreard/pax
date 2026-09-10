\text{ETAPE=}
#if defined TARGET_extrapol1
\if{\step=2}{
  \text{W=\var1}
  \text{ETAPE=\W issametext f? r7,r10}
  \text{ETAPE=\W issametext a? r3,r4,r6,r7,r8,r10}
  \text{ETAPE=\W issametext b? r2,r3,r4,r5,r7,r10}
  \text{ETAPE=\W issametext c? r2,r3,r4,r5,r6,r7,r9,r10}
  \text{ETAPE=\W issametext d? r2,r3,r4,r6,r7,r10}
  \text{ETAPE=\W issametext e? r2,r3,r4,r5,r6,r7,r10}
}
  \if{\step=3}{\text{ETAPE=}}
#endif
#if defined TARGET_meilleurtarif

\if{\step>=2}{\text{W=\var1}}
\if{\step=2 and \W = f}{\text{ETAPE = r9,r10}}

\if{\step=2 and \W = a}{\text{ETAPE = r7}}
\if{\step=3 and \W = a}{\text{ETAPE = r8}}

\if{\step=2 and \W = b}{\text{ETAPE = r2,r3}}
\if{\step=3 and \W = b}{\text{ETAPE = r4,r5}}

\if{\step=2 and \W = c}{\text{ETAPE = r2,r3}}
\if{\step=3 and \W = c}{\text{ETAPE = r7,r8}}

\if{\step=2 and \W = d}{\text{ETAPE = r2,r3}}
\if{\step=3 and \W = d}{\text{ETAPE = r4,r5,r6}}

\if{\step=4}{\text{ETAPE = r9,r10}}

\if{\step=5}{\text{ETAPE =}}

#endif

#if defined TARGET_vedette1
\text{W=\var1}
\if{\step=2}{
   \text{ETAPE=r2,r3,r4,r5,r6}
}
#endif

#if defined TARGET_vedette2

\if{\var1=répondre}{
  \if{\W=répondre}{\text{ETAPE=}}
  {
    \text{ETAPE=r2,r3,r4,r5,r6}
    \text{W=répondre}
  }
}
{
  \text{ETAPE=r1}
  \text{W=\var1}
  \if{\W=dessin}{\text{MM=wims(replace item number 2 by 1 in \MM)}}
  \if{\W=tableau}{\text{MM=wims(replace item number 3 by 1 in \MM)}}
  \if{\W=suite}{\text{MM=wims(replace item number 4 by 1 in \MM)}}
}

\if{\step=5}{
  \text{ETAPE=r2,r3,r4,r5,r6}
  \text{W=répondre}
}
\if{\step=6}{
  \text{ETAPE=}
  \text{W=répondre}
}

#endif
