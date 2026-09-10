#if TYPE==1

!! pour l'instant une seule étape à l'intérieur d'une méthode

\text{W=\var1}
\if{\step=2}{
  \if{\var1=\trep[1]}{
    \text{ETAPE=\rtotal[1;]}
  }{
    \for{tt=2 to \nb_meth}{
      \if{\W=\trep[\tt]}{
        \text{MM=wims(replace item number \tt by 1 in \MM)}
        \text{ETAPE=\rtotal[\tt;]}
      }
    }
  }
}
\if{\step=3}{
  \if{\W=\trep[1]}{
      \text{ETAPE=}
  }{
      \text{W=\trep[1]}
      \text{ETAPE=\rtotal[1;]}
  }
}
\if{\step>=4}{
  \text{W=\trep[1]}
  \text{ETAPE=}
}
#endif
#if TYPE==2
\text{ETAPE=}
\if{\var1=\trep[1]}{
  \if{\W=\trep[1]}{
    \text{ETAPE=}
  }{
    \text{ETAPE=\rtotal}
    \text{W=\trep[1]}
  }
}{
  \text{ETAPE=r1}
  \text{W=\var1}
  \for{t=2 to \nb_meth}{
    \if{\W=\trep[\t]}{\text{MM=wims(replace item number \t by 1 in \MM)}}
  }
}
\if{\step=\nb_meth+1}{
  \text{ETAPE=\rtotal}
  \text{W=\trep[1]}
}
\if{\step=\nb_meth+2}{
  \text{ETAPE=}
  \text{W=\trep[1]}
}
#endif
