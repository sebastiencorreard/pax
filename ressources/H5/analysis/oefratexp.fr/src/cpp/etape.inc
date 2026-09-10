\text{ETAPE=}
\if{\var1=\trep[1]}{
  \if{\W=\trep[1]}{
    \text{ETAPE=}
  }{
    \text{ETAPE=r2}
    \text{W=\trep[1]}
  }
}{
  \text{ETAPE=r1}
  \text{W=\var1}
  \for{t=2 to \methcnt}{
    \if{\W=\trep[\t]}{\text{MM=wims(replace item number \t by 1 in \MM)}}
  }
}
\if{\step=\methcnt+1}{
  \text{ETAPE=r2}
  \text{W=\trep[1]}
}
\if{\step=\methcnt+2}{
  \text{ETAPE=}
  \text{W=\trep[1]}
}
