target=patron2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{donnees=\data[1],randint(1..11),src/patroncube.don
  \data[2],randint(1..9),src/patronpave.don
  \data[3],randint(1..9),src/pcarre.don
  \data[4],randint(1..2),src/ptriangle.don}

\text{ltname=}
\text{ltimage=}
\integer{nbl=rows(\donnees)}
\for{k=1 to \nbl}{
 \text{don=row(\k,\donnees)}
 \text{dessin=wims(record \don[2] of \don[3])}
 \text{image=draw(100,100
\dessin)}
 \text{image=<img src="\image" alt="">}
 \text{ltimage=wims(append item \image to \ltimage)}
 \text{ltname=wims(append item \don[1] to \ltname)}
}

\statement{
\name_enonce
<div class="wimscenter">\embed{r1,100x100x100}</div>
}
\answer{}{\ltname;\ltimage}{type=correspond}{options=shuffle split}
