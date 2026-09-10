target=lectcoord1 lectcoord2 lectcoord3 lectcoord4 lectcoord5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\integer{xrange=400}
\integer{yrange=400}
#if defined TARGET_lectcoord1
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=\l[1]}
 \integer{ya=\l[2]}
#endif
#if defined TARGET_lectcoord2
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=-\l[1]}
 \integer{ya=-\l[2]}
#endif
#if defined TARGET_lectcoord3
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=0}
 \integer{ya=randitem(1,-1)*\l[2]}
#endif

#if defined TARGET_lectcoord4
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \text{s=shuffle(-1,1)}
 \integer{xa=\s[1]*\l[1]}
 \integer{ya=\s[2]*\l[2]}
#endif

#if defined TARGET_lectcoord5
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=randitem(1,-1)*\l[1]}
 \integer{ya=0}
#endif

\text{A=randitem(A,B,C,D,E)}

\text{graph=slib(draw/repere \xrange,\yrange,20,-6,6,-6,6,1,1,black,grey)}
\text{ligne=row(1,\graph)}
\integer{x0=item(1,\ligne)}
\integer{y0=item(2,\ligne)}
\text{ligne=row(2,\graph)}
\real{ex=item(1,\ligne)}
\real{ey=item(2,\ligne)}
\text{repere=wims(line 3 to -1 of \graph)}
\text{repere=\repere
text black,\x0-10,\y0+4,small,0
text black,\x0+\ex-4,\y0+4,small,1
text black,\x0-12,\y0+\ey-4,small,1}
\integer{Ax=\x0+(\ex)*(\xa)}
\integer{Ay=\y0+(\ey)*(\ya)}
\text{dessin2=\repere
linewidth 1
segment \Ax-4,\Ay+4,\Ax+4,\Ay-4,red
segment \Ax-4,\Ay-4,\Ax+4,\Ay+4,red
text red,\Ax-10,\Ay+4,medium,\A}

\statement{\name_question[1] \(\A) \name_question[2]?
<div class="wimscenter">
\draw{\xrange,\yrange}{\dessin2}
</div>
<b>\name_answer:</b>
<div class="wimscenter">
\(\A) a pour coordonnées (\embed{r1,3} ; \embed{r2,3}).
</div>}

\answer{\name_absord[1] \(\A)}{\xa}{type=numexp}
\answer{\name_absord[2] \(\A)}{\ya}{type=numexp}
