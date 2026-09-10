target=plcoord1 plcoord2 plcoord3 plcoord4 plcoord5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\integer{xrange=400}
\integer{yrange=400}

#if defined TARGET_plcoord1
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=\l[1]}
 \integer{ya=\l[2]}
#endif
#if defined TARGET_plcoord2
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=-\l[1]}
 \integer{ya=-\l[2]}
#endif
#if defined TARGET_plcoord3
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \integer{xa=0}
 \integer{ya=randitem(1,-1)*\l[2]}
#endif
#if defined TARGET_plcoord4
 \text{l=wims(values v for v=1 to 5)}
 \text{l=shuffle(\l)}
 \text{s=shuffle(-1,1)}
 \integer{xa=\s[1]*\l[1]}
 \integer{ya=\s[2]*\l[2]}
#endif
#if defined TARGET_plcoord5
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

\text{dessin1=draw(\xrange,\yrange,
\repere)}

\statement{
\name_enonce \((\xa;\ya)).
<div>
<div class="wimscenter">\embed{r1}</div>
</div>
}

\answer{\name_point \(\A)}{\dessin1;circle,\Ax,\Ay,\ex}{type=coord}
