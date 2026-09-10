target=tableau1 tableau2 tableau3 tableau4 tableau5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_tableau1
  \integer{a=randitem(10,100)}
 \text{tab=shuffle(11,12,13,14,15,16,17,18,19)}
 \text{tab=item(1 to 3,\tab)}
 \text{tab2=}
 \integer{b=randint(1..3)*\a}
 \integer{ch=randint(1..2)}
 \for{k=1 to 3}{
  \integer{t=\ch=1 and \k=3?\tab[\k]*\a+\b:\tab[\k]*\a}
  \text{tab2=wims(append item \t to \tab2)}
 }
 \text{good=item(\ch,\bad)}
#endif
#if defined TARGET_tableau2
 \integer{a=randint(2..9)}
 \text{tab=shuffle(11,12,13,14,15,16,17,18,19)}
 \text{tab=item(1 to 3,\tab)}
 \text{tab2=}
 \integer{b=randint(1..5)}
 \integer{ch=randint(1..2)}
 \for{k=1 to 3}{
  \real{t=\ch=1 and \k=3?\tab[\k]*\a+\b:\tab[\k]*\a}
  \text{tab2=wims(append item \t to \tab2)}
 }
 \text{good=item(\ch,\bad)}
#endif
#if defined TARGET_tableau3
 \integer{a=randint(2..9)}
 \text{b=randint(2..6),randint(12..18)}
 \integer{ch=randint(1..2)}
 \integer{ch2=randint(1..2)}
 \if{\ch2=1}{
  \text{tab=shuffle(11,12,13,14,15,16,17,18,19)}
  \text{tab=item(1 to 3,\tab)}
 }{
  \text{tab=randint(11..17)}
  \integer{t1=\tab+\b[1]}
  \integer{t2=\tab+\b[2]}
  \text{tab=\tab,\t1,\t2}
 }
 \text{tab2=}
 \if{\ch=2}{
  \for{k=1 to 3}{
   \integer{t=\tab[\k]*\a}
   \text{tab2=wims(append item \t to \tab2)}
  }
 }{
  \if{\ch2=1}{
   \integer{c=randint(20..99)}
   \integer{t1=\c+\b[1]}
   \integer{t2=\c+\b[2]}
   \text{tab2=\c,\t1,\t2}
  }{
   \for{k=1 to 3}{
    \integer{t=\tab[\k]+\b[1]}
    \text{tab2=wims(append item \t to \tab2)}
   }
  }
 }
 \text{good=item(\ch,\bad)}
#endif
#if defined TARGET_tableau4
 \real{a=randint(2..9)}
 \text{tab=wims(values v/10 for v=11 to 99)}
 \text{tab=shuffle(\tab)}
 \text{tab=item(1 to 3,\tab)}
 \text{tab2=}
 \real{b=randint(1..9)/10}
 \integer{ch=randint(1..2)}
 \for{k=1 to 3}{
  \real{t=\ch=1 and \k=3?\tab[\k]*\a+\b:\tab[\k]*\a}
  \text{tab2=wims(append item \t to \tab2)}
 }
 \text{good=item(\ch,\bad)}
#endif

#if defined TARGET_tableau5
 \text{name=slib(lang/fname fr,boy)}
 \text{compenonce= \enonce}
 \text{enonce=\enonce1[1], \name \enonce1[2]}
 \integer{a=randint(2..9)}
 \text{tab=shuffle(11,12,13,14,15,16,17,18,19)}
 \text{tab=item(1 to 3,\tab)}
 \text{tab2=}
 \integer{b=randint(1..5)}
 \integer{ch=randint(1..2)}
 \for{k=1 to 3}{
  \integer{t=\ch=1 and \k=3?\tab[\k]*\a+\b:\tab[\k]*\a}
  \text{tab2=wims(append item \t to \tab2)}
 }
 \text{good=item(\ch,\bad)}
#endif
\statement{
\enonce
<table class="wimscenter wimsborder">
 <tr>
  <td>\tab[1]</td>
  <td>\tab[2]</td>
  <td>\tab[3]</td>
 </tr><tr>
  <td >\tab2[1]</td>
  <td >\tab2[2]</td>
  <td >\tab2[3]</td>
 </tr>
 </table>
\compenonce}

\choice{\name_answer}{\good}{\bad}
