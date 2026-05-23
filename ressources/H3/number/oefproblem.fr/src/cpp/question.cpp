target=1 2 3 4 5
#include "lang_titles.inc"

\text{genre=randitem(girl,boy)}
\text{name_ils=ils,elles}
\text{fname=slib(lang/fname ,\genre,2)}

#if defined TARGET_1
\integer{n1=2*randint(154..200)+1}
\integer{n2=\n1+2}
\integer{n3=\n1+4}
\integer{N=3*\n1+6}
#include "lang.inc"
\statement{
\instruction
<div class="wimscenter">\embed{r1}</div>
<div class="wims_instruction">\warning</div>
}
\answer{}{\n1,\n2,\n3}{type=set}
#endif
#if defined TARGET_2
\integer{n=randint(4..8)}
\text{a=randint(8..10)}
\text{b=randint(2..4)}
\integer{c=\a-randint(1..3)}
\integer{d=(\a-\c)*\n-\b}
\text{genre=randitem(girl,boy)}
\text{fname=slib(lang/fname \lang,\genre,2)}
#include "lang.inc"
\text{name_ils=\genre issametext boy ?\name_ils[1]:\name_ils[2]}
\text{name_Ils=\genre issametext boy ?\name_Ils[1]:\name_Ils[2]}
\text{instruction=wims(replace internal XXXXX by \fname[1] in \instruction)}
\text{instruction=wims(replace internal YYYYY by \fname[2] in \instruction)}
\text{instruction=wims(replace internal IIIII by \name_Ils in \instruction)}
\text{instruction=wims(replace internal iiiii by \name_ils in \instruction)}

\statement{<label for="reply1">\instruction</label>
  <div class="wimscenter">\embed{r1}</div>
}
\answer{}{\n}{type=numexp}
#endif
#if defined TARGET_3
\text{a=randint(10..13)}
\text{b=randint(2*\a+3..2*\a+20)}
2*(a+n)=b+n
\integer{n=\b-2*\a}

#include "lang.inc"
\text{instruction=wims(replace internal XXXXX by \fname[1] in \instruction)}
\text{instruction=wims(replace internal YYYYY by \fname[2] in \instruction)}

\statement{
  <label for="reply1">\instruction?</label>
  <div class="wimscenter">\embed{r1}</div>
}
\answer{}{\n}{type=numexp}
#endif
#if defined TARGET_4
\text{a=randint(25..30)}
\text{b=randint(14..23)}
\integer{b=pari((\b-\a)%2)=1?\b+1}
c=n+a:  c+b=3n
\integer{n=(\a+\b)/2}
\text{choix=randint(1..2)}
#include "lang.inc"
\statement{
  <label for="reply1">\instruction?</label>
  <div class="wimscenter">\embed{r1}</div>
}
\answer{}{\n}{type=numexp}
#endif
#if defined TARGET_5
\text{n1=randint(4..9)}
\integer{n2=\n1+1}
\integer{s=\n1+\n2}
\integer{t=\n2^2-\n1^2}
#include "lang.inc"
\statement{
  <label for="reply1">\instruction</label>
  <div class="wimscenter">\embed{r1}</div>
  <div class="wims_instruction">\warning</div>
}
\answer{}{\n1,\n2}{type=set}
#endif
