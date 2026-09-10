target=oefformdisq2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\keywords{area}

\text{mot=\name_list[4],\name_list[3]}
\integer{ch=randint(1..2)}
\real{d=randint(8..80)*2/10}
\real{r=\d/2}
\if{\ch=1}{
  \real{rp=\r}
  \real{v=\d}
  \text{mot1=\name_list[3]}
  \text{mot2=\name_list[4]}
}{
  \real{rp=\d}
  \real{v=\r}
  \text{mot1=\name_list[4]}
  \text{mot2=\name_list[3]}
}

\text{rp=wims(replace internal . by , in \rp)}
\text{v=wims(replace internal . by , in \v)}

\statement{\name_enonc \mot1 \v cm.
  <div class="spacer"><label for="reply1">\name_question[3]
  \name_question \mot2</label> :
  \embed{r1,6} cm</div>
  <div class="wims_instruction">\name_instruction</div>
}
\answer{}{\rp}{type=raw}
