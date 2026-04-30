target=vocabulaire1 vocabulaire2 vocabulaire3 vocabulaire4 vocabulaire5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{100}

\matrix{lt=3,5,7,9
2,4,6,8,7
3,5,7,9
2,3,4,6,7,8,9
5,7
2,3,4,5,6,8,9
3,5,7,9
2,4,5,7,8}
\integer{a=randint(2..9)}
\integer{b=randitem(row(\a-1,\lt))}
\integer{c=\a*\b}
#if defined TARGET_vocabulaire1
 \text{good=\a \name_divmult[1] \c}
 \text{bad=\a \name_divmult[1] \b,\c \name_divmult[1] \a}
#endif
#if defined TARGET_vocabulaire2
 \text{good=\c \name_divmult[2] \a}
 \text{bad=\a \name_divmult[2] \b,\a \name_divmult[2] \c}
#endif
#if defined TARGET_vocabulaire3
 \text{good=\c \name_divmult[3] \a}
 \text{bad=\a \name_divmult[3] \b,\a \name_divmult[3] \c}
#endif
#if defined TARGET_vocabulaire4
 \text{good=\a \name_divmult[1] \c,\c \name_divmult[2] \a}
 \text{bad=\a \name_divmult[1] \b,\c \name_divmult[1] \a,\a \name_divmult[2] \b,\a \name_divmult[2] \c}
#endif
#if defined TARGET_vocabulaire5
 \text{good=\a \name_divmult[1] \c,\c \name_divmult[3] \a}
 \text{bad=\a \name_divmult[1] \b,\c \name_divmult[1] \a,\a \name_divmult[3] \b,\a \name_divmult[3] \c}
#endif
#if defined TARGET_vocabulaire4|| defined TARGET_vocabulaire5
 \text{list=shuffle(\good,\bad)}
 \text{ch1=item(1,\good)}
 \text{ch2=item(2,\good)}
 \text{sol=position(\ch1,\list),position(\ch2,\list)}
 \statement{<div class="wimscenter">
 \(\c = \a \times \b\)
 </div>
 \name_question?
 <ul>
  \for{k=1 to 6}{
   <li>\embed{r1,\k}</li>
  }
  </ul>
}
 \answer{\name_answer}{\sol;\list}{type=checkbox}
#else
\statement{<div class="wimscenter">
 \(\c = \a \times \b\)
 </div>
 \name_question? }
\choice{\name_answer}{\good}{\bad}
#endif
