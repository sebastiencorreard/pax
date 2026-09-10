#if defined TARGET_ratio2 || defined TARGET_ratio2confparm

%%Réalisation du tableau

\text{entetes=Nombre total de parts}
\text{ligne=}
\for{ k1=1 to \nbre1 }{
  \text{ligne=\ligne<div class="unepart part_1"> </div>}
  \if{ \k1 < \nbre1 }{
    text{entetes=\entetes,*}
    \text{ligne=\ligne,}
  }
}
\for{ k2=1 to \nbre2}{
    \if{ \k2 < \nbre2 }{
    text{entetes=\entetes,*}
    }
    \text{ligne=\ligne,<div class="unepart part_2"> </div>}
  }
\text{A=slib(text/matrixhtml
  [\ligne],
  wimscenter wimsborder,
  TH=1
  CAPTION="Nombre total de parts"
  COLSPAN=[1,1,\nbre1;1,\k1,\nbre2]
)}
#endif

#if defined TARGET_ratio3 || defined TARGET_ratio3confparm
\text{entetes=Nombre total de parts}
\text{ligne=}
\for{ k1=1 to \nbre1 }{
  \text{ligne=\ligne<div class="unepart part_1"> </div>}
  \if{ \k1 < \nbre1 }{
    text{entetes=\entetes,*}
    \text{ligne=\ligne,}
  }
}
\for{ k2=1 to \nbre2}{
    \if{ \k2 < \nbre2 }{
    text{entetes=\entetes,*}
    }
    \text{ligne=\ligne,<div class="unepart part_2"> </div>}
  }
\for{ k3=1 to \nbre3}{
    \if{ \k3 < \nbre3 }{
    text{entetes=\entetes,*}
    }
    \text{ligne=\ligne,<div class="unepart part_3"> </div>}
  }
\text{A=slib(text/matrixhtml
  [\ligne],
  wimscenter wimsborder,
  CAPTION="Nombre total de parts"
  COLSPAN=[1,1,\nbre1;1,\k1,\nbre2;1,\k2,\nbre3]
)}
#endif

# if defined TARGET_utilratio3
\text{entetes=Nombre total de parts}
\text{ligne=}
\for{ k1=1 to \nbre1 }{
  \text{ligne=\ligne<div class="unepart part_1"> </div>}
  \if{ \k1 < \nbre1 }{
    text{entetes=\entetes,*}
    \text{ligne=\ligne,}
  }
}
\for{ k2=1 to \nbre2}{
    \if{ \k2 < \nbre2 }{
    text{entetes=\entetes,*}
    }
    \text{ligne=\ligne,<div class="unepart part_2"> </div>}
  }
\text{A=slib(text/matrixhtml
  [\ligne],
  wimscenter wimsborder,
  TH=1
  CAPTION="Nombre total de parts"
  COLSPAN=[1,1,\nbre1;1,\k1,\nbre2]
)}
#endif
