target=arrondiunit arrondiunitguide
#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(0..999)}
\integer{b=randint(0..9999)}
\real{n=\a+\b/10000}
\integer{deci=floor(\b/1000)}
\text{nvirg=wims(replace internal . by , in \n)}
\integer{c=\a+1}
\integer{valdef=\a}
\integer{valex=\c}
\text{unite=<span style="color:red"><b>\name_precdix[1]</b></span>}
\text{dixiem=<span style="color:blue"><b>\name_precdix2[2]</b></span>}
\text{enonce=\name_enonce[1] \(\nvirg\). \name_enonce[2] \unite.}
\text{name_hint=wims(replace internal XXXX by \unite in \name_hint)}
\text{name_hint=wims(replace internal YYYY by \dixiem in \name_hint)}

\if{\deci<5}{\integer{rep=1}
\integer{arrond=\a}}{\integer{rep=2}
\integer{arrond=\c}}
#if defined TARGET_arrondiunit
\statement{\enonce<br>
  \name_question:<br>
  <label for="reply1">
  \name_statement0[1] \unite \name_statement0[2] \(\nvirg\)
  \name_statement0[3]</label> \embed{r1,3}.
}
\answer{\name_answer[2]}{\arrond}{type=numexp}
\feedback{(\deci<5 and \reply1=\c) or (\deci>4 and \reply1=\a)}{
  <div class="macss">\name_feed</div>}
#endif
#if defined TARGET_arrondiunitguide
\statement{\enonce
  <br>\name_question:
  <ul><li>
  <label for="reply1">\name_statement[1;1] \dixiem \name_statement[1;2] \(\nvirg\)
    \name_statement[1;3]</label> \embed{r1,3}.
  </li><li><label for="reply2">\name_statement[2;1] \unite \name_statement[2;2] \(\nvirg\)
  \name_statement[2;3] \unite</label> \embed{r2} <label for="reply3">
  \name_statement[2;4]</label> \embed{r3,3}.
  </li></ul>
}
\answer{\name_answer[1] \dixiem}{\deci}{type=numexp}
\answer{}{\rep;\liste}{type=menu}
\answer{\name_answer[2]}{\arrond}{type=numexp}
\feedback{(\deci<5 and \reply3=\c) or (\deci>4 and \reply3=\a)}{<div class="macss">
\name_feed</div>}
#endif
\help{\name_hint}

\solution{\name_statement[1;1] \dixiem \name_statement[1;3]\(\deci\).
  \name_statement[2;1] \unite \name_statement[2;2] \(\nvirg\)
  \name_statement[2;3] \liste[\rep] : \(\arrond\).<p>
  \name_note \(\nvirg \approx \arrond \).</p>}
