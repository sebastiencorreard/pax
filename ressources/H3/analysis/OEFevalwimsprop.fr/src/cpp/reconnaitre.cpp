target=reconnaitreA1 reconnaitreA2

#include "author.inc"
\keywords{proportionality}
#if defined TARGET_reconnaitreA1
# define NUM 1
#endif
#if defined TARGET_reconnaitreA2
# define NUM 2
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_reconnaitreA1
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
#if defined TARGET_reconnaitreA2
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
#if defined TARGET_reconnaitre3
 \text{name=slib(lang/fname fr,boy)}
 \text{enonce=Sur la vitrine d'une boulangerie, \name voit afficher :}
 \text{compenonce=}
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
\enonce?
<table class="wimscenter wimsborder">
 <tr>
  <td>\tab[1]</td>
  <td>\tab[2]</td>
  <td>\tab[3]</td>
 </tr><tr>
  <td>\tab2[1]</td>
  <td>\tab2[2]</td>
  <td>\tab2[3]</td>
 </tr>
 </table>}

\choice{}{\good}{\bad}
