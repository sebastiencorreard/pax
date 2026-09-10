target=oefrecpatron4

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\integer{ch=randint(1..4)}
\text{patron=wims(record \ch of src/patron)}
\text{patron=row(2,\patron)}

\text{pata=}
\for{i=1 to 9}{
   \text{pat=wims(record \patron[\i] of src/decoupe)}
   \text{pat1=row(2,\pat)}
   \text{pat2=row(3,\pat)}
   \text{pat3=row(4,\pat)}
   \text{pat4=row(5,\pat)}
   \text{pat5=row(6,\pat)}
   \text{pat6=row(7,\pat)}
   \text{pat7=row(8,\pat)}
   \text{pat8=row(9,\pat)}
   \text{pat9=row(10,\pat)}

   \text{pat1a=draw(100,100
   \pat1
   \pat2
   \pat3
   \pat4
   \pat5
   \pat6
   \pat7
   \pat8
   \pat9
    )}
   \text{pat0=<img src="\pat1a" alt="">}
   \text{pata=wims(append item \pat0 to \pata)}
}
\text{v=}
\for{i=1 to 9}{\if{\patron[\i]=1}{\integer{a=\i}}}

\for{i=1 to 9}{
    \if{\patron[\i]=1}{\text{v=wims(append item \a to \v)}}
                      {\text{v=wims(append item \i to \v)}}}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">\pata[1]\pata[2]\pata[3]
<br>\pata[4]\pata[5]\pata[6]
<br>\pata[7]\pata[8]\pata[9]
</div>
 <div class="medium_size text_col">
\name_enonce:
<div class="wimscenter">\special{imagefill \feuille,300x300,100x100
r1,0x0
r2,100x0
r3,200x0
r4,0x100
r5,100x100
r6,200x100
r7,0x200
r8,100x200
r9,200x200}</div>
</div></div>
}

\answer{}{\pata[\v[1]]}{type=clickfill}
\answer{}{\pata[\v[2]]}{type=clickfill}
\answer{}{\pata[\v[3]]}{type=clickfill}
\answer{}{\pata[\v[4]]}{type=clickfill}
\answer{}{\pata[\v[5]]}{type=clickfill}
\answer{}{\pata[\v[6]]}{type=clickfill}
\answer{}{\pata[\v[7]]}{type=clickfill}
\answer{}{\pata[\v[8]]}{type=clickfill}
\answer{}{\pata[\v[9]]}{type=clickfill}
