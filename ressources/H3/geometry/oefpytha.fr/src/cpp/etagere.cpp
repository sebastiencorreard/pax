target=etagere1 etagere2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{dessin=xrange -1,5
yrange -1,5
dashed
segments red,3,0,0,4
linewidth 3
segments black,0,0,0,4,0,0,3,0
text black,0,-0.3,large,A
text black,3,-0.3,large,B
text black,0.2,4,large,C
linewidth 1
fcircles blue,2,0.2,0.2}
\text{a=randint(300..600)}
\text{b=randint(100..150)}
\text{lim=25}
\text{pyth=pari(pyth(A,B,lim)={for(a=A+B,A+lim+B, for(b=a,a+lim,N=sqrt(a^2+b^2); if(floor(N)==N, return([a,b,floor(N)]))))})}
\text{bca=pari(lim=25; pyth(\a,\b,lim))}
\text{bca=\bca[1]==0? pari(lim1=100; pyth(\a,\b+lim,lim1))}
\text{bca=\bca[1]==0? erreur}
\real{b=\bca[1]}
\real{c=\bca[2]}
\real{a=\bca[3]}
\text{s=randitem(1,1,-1,-1,0)}
\real{a1=\a+\s*randint(1..3)}
\text{bcaa=pari([\b,\c,\a,\a1]/10.)}
#if defined TARGET_etagere1
\text{choix=\name_choix}
\integer{rep=\s+2}
#endif
#if defined TARGET_etagere2
\text{choix0=\a-randint(1..2),\a,\a+randint(1..2)}
\text{rep1=randitem(1,2,3)}
\text{choix1=\rep1 iswordof 2 3? \choix0,\a-randint(3..4):\choix0,\a+randint(3..4)}
\text{choix0=pari([\choix1]/10.)}
\text{choix=shuffle(\choix0)}
\text{rep=position(\choix0[\rep1],\choix)}
#endif
\text{nom=slib(lang/fname fr,girl)}
\text{enonce=wims(replace internal Toto by \nom in \name_enonce)}
\text{long1=wims(replace internal Toto by \nom in \name_long1)}

\statement{
\enonce \name_long[1] \(AC=\bcaa[1]\) cm, \(AB=\bcaa[2]\) cm.
<div class="wimscenter">
\draw{300,300}{\dessin}
<div class="wims_warning">\name_warning</div>
</div>
#if defined TARGET_etagere2
\name_choix[\rep1]
#endif
\long1
#if defined TARGET_etagere1
\(BC=\bcaa[4]\) cm.
#endif
#if defined TARGET_etagere2
\(BC\).
#endif
\name_question?
<ul><li>\embed{r1,1}</li><li>\embed{r1,2}</li><li>\embed{r1,3}</li>
#if defined TARGET_etagere2
<li>\embed{r1,4}</li>
#endif
</ul>

}
#if defined TARGET_etagere1
\answer{}{\rep;\choix}{type=radio}
#endif
#if defined TARGET_etagere2
\answer{}{\rep;\choix}{type=radio}
#endif
