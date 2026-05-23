target=decalage decalage2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}

\text{lteno1=}
\text{ltsol=}
\text{lteno2=}
\text{st=}
\for{i=1 to \confparm1}{
  \text{sg=shuffle(1,-1)}
  \text{sg1=item(1,\sg)}
  \text{sg2=item(2,\sg)}
  \integer{a=randitem(1,1,-1)*randint(10..1000)}
  \integer{b=\sg1*randint(2..3)}
  \integer{c=\sg2*randint(2..3)}
  \real{b=\b<0?\a*10^(\b):\a}
  \integer{d=randitem(1,-1)*randint(1..3)}
#if defined TARGET_decalage2
  \integer{d=\d=\c?\c+1}
#endif
  \text{enonce1=\b \times 10^{\c}}
#if defined TARGET_decalage
  \integer{dec=\c+(\d)}
  \integer{d=\dec=0?\d+1}
  \integer{dec=\dec=0?1}
  \text{enonce2=10^{\dec}}
  \real{rep=\b*10^(-(\d))}
#endif
#if defined TARGET_decalage2
  \integer{dec=\c-(\d)}
  \real{enonce2=\b*10^(\dec)}
#endif
  \text{lteno1=wims(append item \enonce1 to \lteno1)}
  \text{lteno2=wims(append item \enonce2 to \lteno2)}
#if defined TARGET_decalage
  \text{ltsol=wims(append item \rep to \ltsol)}
#endif
#if defined TARGET_decalage2
  \text{ltsol=wims(append item \d to \ltsol)}
#endif
  \text{st=wims(append item r\i to \st)}
}
\steps{\st}

\statement{
\if{\confparm1=1}{
  \name_question[1]:
  <div class="wimscenter">
#if defined TARGET_decalage
  <label for="reply1">\(\lteno1[1] = \)</label> \embed{r1,10} \(\times \lteno2[1]).
#else
  <label for="reply1">\(\lteno1[1] = \lteno2[1] \times 10\)</label><sup>\embed{r1,3}</sup>.
#endif
  </div>
}{
  \name_question[2]:
  <ul>
  \for{k=1 to \confparm1}{
    <li>
#if defined TARGET_decalage
    <label for="reply\k">\(\lteno1[\k] = \)</label> \embed{r\k,10} \(\times \lteno2[\k]).
#endif
#if defined TARGET_decalage2
  <label for="reply\k">\(\lteno1[\k] = \lteno2[\k] \times 10\)</label><sup>\embed{r\k,3}</sup>.
#endif
  </li>
  }
  </ul>
}}

\answer{\(\lteno[1]\)}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2]\)}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3]\)}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4]\)}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5]\)}{\ltsol[5]}{type=numexp}
