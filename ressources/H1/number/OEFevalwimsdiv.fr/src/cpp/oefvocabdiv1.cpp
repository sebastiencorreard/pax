target=oefvocabdiv1 oefvocabdiv2
\keywords{division}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\integer{d2=1}
\integer{d1=randint(2..5)}
\integer{d=\d2\d1}
\integer{r=randint(1..\d-1)}
\integer{q2=randint(2..10-\d1)}
\integer{q1=randint(2..9)}
\if{\d1=2 and \q2=8}{\integer{q1=2}}
\if{\d1=3 and \q2=7}{\integer{q1=randint(2..5)}}
\integer{q=\q2\q1}
\integer{dd=\q*\d+\r}
\text{sgn=-}
\text{ldd=}
\for{i=1 to 3}
   {\text{chif=wims(char \i to \i of \dd)}
    \text{ldd=wims(append item \ldd to \chif)}}
\integer{m=\d*\q2}
\text{rp=}
\integer{test=10-\m}
\if{\test>0}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to 2}
{\text{chif=wims(char \i to \i of \m)}
\text{rp=wims(append item \chif to \rp)}}
\text{rp=\rp,\q2,\q1}
\integer{rest=\ldd[3]\ldd[2]-\m}
\integer{test=10-\rest}
\if{\test>0}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rp=wims(append item \chif to \rp)}}}
\text{rp=\rp,\ldd[1]}
\integer{m=\d*\q1}
\integer{test=10-\m}
\if{\test>0}{\integer{l=1} \text{rp=\rp,0,0}}
   {\integer{test=100-\m}
    \if{\test>0}{
     \integer{l=2}
        \text{rp=\rp,0}}{\integer{l=3}}
        }
\for{i=1 to \l}
{\text{chif=wims(char \i to \i of \m)}
\text{rp=wims(append item \chif to \rp)}}
\integer{rest=\rp[5]\rp[6]\rp[7]-\m}
\integer{test=10-\rest}
\if{\test>0}
   {\integer{l=1}
     \text{\rp=\rp,0}}{\integer{l=2}}
\for{i=1 to \l}
   {\text{chif=wims(char \i to \i of \rest)}
       \if{chif=}{}{\text{rp=wims(append item \chif to \rp)}}}
#if defined TARGET_oefvocabdiv1
\integer{large=5}
\text{rep=\dd,\d,\q,\r}
\text{quest= \name_list}
\integer{k=randint(1..4)}
\text{enonc=\name_enonc[1] \quest[\k] \name_enonc[2] }
#endif
#if defined TARGET_oefvocabdiv2
\text{rep=\name_list}
\integer{large=12}
\text{quest=\dd,\d,\q,\r}
\integer{k=randint(1..4)}
\text{enonc=\name_enonc[1], \name_enonc[2] \quest[\k] \name_enonc[3]}
#endif

\statement{\name_question:
#include "table.inc"
<label for="reply1">\enonc</label> \embed{r1,\large}.}

\answer{}{\rep[\k]}
