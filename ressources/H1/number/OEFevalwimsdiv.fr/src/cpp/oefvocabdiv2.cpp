target=oefvocabdiv3 oefvocabdiv4 oefvocabdiv5
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
        \text{rp=\rp,0}}{\integer{l=3}}}
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

#if defined TARGET_oefvocabdiv3
\integer{large=5}
\text{quest=\name_list}
\text{rep=\dd,\d,\q,\r}
\text{k=shuffle(4)}
\text{enon1= \name_enon <ul><li>\quest[\k[1]] :}
\text{enon2= </li><li>\quest[\k[2]] :}
\text{enon3= </li><li>\quest[\k[3]] :}
\text{enon4= </li><li>\quest[\k[4]] :}
#endif
#if defined TARGET_oefvocabdiv4
\integer{large=12}
\text{quest=\dd,\d,\q,\r}
\text{rep=\name_list}
\text{k=shuffle(4)}
\text{enon1= \name_enonc[1], <ul><li>\quest[\k[1]] \name_enonc[2]}
\text{enon2= </li><li>\quest[\k[2]] \name_enonc[2]}
\text{enon3= </li><li>\quest[\k[3]] \name_enonc[2]}
\text{enon4= </li><li>\quest[\k[4]] \name_enonc[2]}
#endif
#if defined TARGET_oefvocabdiv5
\integer{large=5}
\text{rep=\dd,\d,\q,\r}
\text{quest=\name_list}
\text{k=1,2,3,4}
\text{name_oper=\name_list}
\text{enon1= \name_enon1[1], \name_enon1[2]:
<div class="wimscenter">\name_oper[1] = \name_oper[2] \(\times) \name_oper[3] + \name_oper[4]</div>
\name_enon1[3]:
<ul><li>
}
\text{enon2= =}
\text{enon3= \(\times\) }
\text{enon4= +}
#endif

\statement{\name_question:
#include "table.inc"
\enon1 \embed{r1,\large}
\enon2 \embed{r2,\large}
\enon3 \embed{r3,\large}
\enon4 \embed{r4,\large}
</li></ul>
}


\answer{}{\rep[\k[1]]}
\answer{}{\rep[\k[2]]}
\answer{}{\rep[\k[3]]}
\answer{}{\rep[\k[4]]}
