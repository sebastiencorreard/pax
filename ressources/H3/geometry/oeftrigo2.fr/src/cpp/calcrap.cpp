target=calcrap

#define NUM 1
#include "lang_titles.inc"
#include "author.inc"

\precision{100000}

\integer{prec=randint(10,100,1000,10000)}
\real{precision=1/\prec}

\text{fonction=sin,cos,tan}
\text{fonction=shuffle(\fonction)}
\text{rep=}
\text{fonct=}
\for{i=1 to 3}{
  \integer{angle=random(15..75)}
  \text{fn=item(\i,\fonction)}
  \integer{tmp=\fn(\angle/180*pi)*\prec}
  \real{tmp=\tmp/\prec}
  \text{rep=wims(append item \tmp to \rep)}
  \text{tmp=\fn(\angle)}
  \text{fonct=wims(append item \tmp to \fonct)}
}

\statement{À l'aide de la calculette, donner les valeurs arrondies à \precision de :
<ul><li><label for="reply1">\(\fonct[1]\) =</label> \embed{r1,10}</li><li>
  <label for="reply2">\(\fonct[2]\) = </label>\embed{r2,10}</li><li>
  <label for="reply3">\(\fonct[3]\) = </label>\embed{r3,10}</li></ul>
}

\answer{\(\fonct[1]\)}{\rep[1]}{type=numexp}
\answer{\(\fonct[2]\)}{\rep[2]}{type=numexp}
\answer{\(\fonct[3]\)}{\rep[3]}{type=numexp}
