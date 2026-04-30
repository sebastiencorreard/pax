target=representation5
#include "author.inc"
#include "lang_titles.inc"
\text{name_enonce=Quelle inégalité les nombres représentés ci-dessous
  vérifient-ils&nbsp;}
\text{x=randitem(x,y,z,a,b,u,v)}
\integer{xsize=300}
\integer{ysize=80}
\integer{a=randint(-10..5)}
\integer{b=randint(4..9)+\a}
\text{syinf=shuffle(<,<=)}
\text{sysup=shuffle(<,<=)}
 \text{dessin=slib(repencadrement \a,\syinf[1],\sysup[1],\b,\xsize,\ysize,-15,15,black,red)}
 \text{good=draw(\xsize,\ysize
\dessin)}
\text{t1=texmath(\a \syinf[1] \x \sysup[1] \b)}
\text{t2=texmath(\a \syinf[2] \x \sysup[1] \b)}
\text{t3=texmath(\a \syinf[1] \x \sysup[2] \b)}
\text{t4=texmath(\a \syinf[2] \x \sysup[2] \b)}
\text{ine=\(\t1),\(\t2),\(\t3),\(\t4)}

\statement{ \name_enonce?
<div class="wimscenter"><img src="\good" alt=""></div>}
\choice{réponse}{\ine[1]}{\ine[2],\ine[3],\ine[4]}
