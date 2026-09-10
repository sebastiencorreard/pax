target=oefperimaire2 oefperimaire3 oefperimaire4
\keywords{area,perimeter}
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"

\text{enonc2=\(cm\)}
\text{enonc4=\(cm^2)}
\text{rect=draw(150,100
rect 20,20,130,80,black
)}
#if defined TARGET_oefperimaire2
\integer{a=randint(17..99)}
\integer{b=randint(6..\a-10)}
\integer{rep1=(\a+\b)*2}
\integer{rep2=\a*\b}
\integer{large=6}
\text{enonc1=\name_enonc1[1] \a cm, \name_enonc1[2] \b cm.}
#endif
#if defined TARGET_oefperimaire3
\real{a=randint(60..199)/10}
\real{b=randint(10..\a*10-10)/10}
\real{rep1=(\a+\b)*2}
\real{rep2=\a*\b}
\integer{large=6}
\text{enonc1=\name_enonc1[1] \a cm, \name_enonc1[2] \b cm.}
#endif
#if defined TARGET_oefperimaire4
\text{u=shuffle(3)}
\integer{ua=\u[1]}
\integer{ub=\u[2]}
\if{\ua=1}{\integer{a=randint(2..9)*10}}{\integer{a=randint(17..99)}}
\if{\ub=1}{\integer{b=randint(1..\a/10)*10}}{\integer{b=randint(6..\a-10)}}
\real{afa=\a*10^(\ua-2)}
\real{afb=\b*10^(\ub-2)}

\text{unit=dm,cm,mm}
\real{rep1=(\a+\b)*2}
\real{rep2=\a*\b}
\integer{large=6}

\text{enonc1=\name_enonc1[1] \afa \unit[\ua], \name_enonc1[2] \afb \unit[\ub].}
#endif
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\rect" alt=""></div>
 <div class="medium_size text_col">
  \enonc1
  <div class="spacer"><label for="reply1">\enonc11</label>
  \embed{r1,\large} \enonc2.</div>
  <div class="spacer"><label for="reply2">\enonc3</label>
  \embed{r2,\large} \enonc4.</div>
  </div></div>
}

\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
