target=oefvocabmult1 oefvocabmult2 oefvocabmult3

\keywords{division}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\integer{d2=1}
\integer{d1=randint(2..5)}
\integer{d=\d2\d1}
\integer{q2=randint(2..10-\d1)}
\integer{q1=randint(2..9)}
\if{\d1=2 and \q2=8}{\integer{q1=2}}
\if{\d1=3 and \q2=7}{\integer{q1=randint(2..5)}}
\integer{q=\q2\q1}
\integer{dd=\q*\d}
\text{sgn=-}
\text{ldd=}
\for{i=1 to 3}
   {\text{chif=wims(char \i to \i of \dd)}
    \text{ldd=wims(append item \ldd to \chif)}}
\integer{m=\d*\q2}
\text{rp=}
\if{\m<10}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to 2}
{\text{chif=wims(char \i to \i of \m)}
\text{rp=wims(append item \chif to \rp)}}
\text{rp=\rp,\q2,\q1}
\integer{rest=\ldd[3]\ldd[2]-\m}
\if{\rest<10}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rp=wims(append item \chif to \rp)}}}
\text{rp=\rp,\ldd[1]}
\integer{m=\d*\q1}
\if{\m<10}{\integer{l=1} \text{rp=\rp,0,0}}
   {\if{\m<100}{
     \integer{l=2}
        \text{rp=\rp,0}}{\integer{l=3}}}
\for{i=1 to \l}
{\text{chif=wims(char \i to \i of \m)}
\text{rp=wims(append item \chif to \rp)}}
\integer{rest=\rp[5]\rp[6]\rp[7]-\m}
\if{\rest<10}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rp=wims(append item \chif to \rp)}}}

#if defined TARGET_oefvocabmult1
\integer{large=5}
\integer{rep1=1}
\integer{rep2=2}
#endif
#if defined TARGET_oefvocabmult2
\integer{large=5}
\integer{rep1=1}
\integer{rep2=2}
#endif
#if defined TARGET_oefvocabmult3
\integer{large=5}
\integer{rep1=2}
\integer{rep2=1}
#endif
\statement{\name_question:
#include "table.inc"
\name_enonce[1] \embed{r1,\large} \name_enonce[2] \mot \name_enonce[3]  \embed{r2,\large},
\name_enonce[4] }

\answer{}{\rep1;\dd,\d}{type=menu}
\answer{}{\rep2;\dd,\d}{type=menu}