target=puisdiv

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1=\confparm1>5?5}

\text{lteno=}
\text{ltsol=}
\text{st=}
\for{i=1 to \confparm1}{
 \text{sg=shuffle(1,-1)}
 \integer{a=randitem(\sg)*randint(2..9)}
 \integer{p=randint(2..5)}
 \text{enonce=(\a)^{\p}}
 \real{rep=(\a)^(\p)}
 \text{lteno=wims(append item \enonce to \lteno)}
 \text{ltsol=wims(append item \rep to \ltsol)}
 \text{st=wims(append item r\i to \st)}
}
\steps{\st}
\statement{
\if{\confparm1=1}{
  \name_question[1]:
  <div class="wimscenter"><label for="reply1">\(\lteno = \)</label> \embed{r1,8}.</div>}
  {\name_question[2]:
  <ul>
   \for{k=1 to \confparm1}{
    <li><label for="reply\k">\(\lteno[\k] = \)</label> \embed{r\k,8}.</li>
    }
  </ul>}
}
\answer{\(\lteno[1])}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2])}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3])}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4])}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5])}{\ltsol[5]}{type=numexp}
