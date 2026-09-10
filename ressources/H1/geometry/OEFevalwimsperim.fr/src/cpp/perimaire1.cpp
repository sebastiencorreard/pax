target=oefperimaire1
#include "lang_titles.inc"
#include "lang.inc"
\keywords{perimeter,area}
#include "author.inc"
\integer{a=8}
\integer{b=7}
\integer{lo=40}
\integer{xo=10}
\integer{yo=290}

\integer{e=randint(1..7)}
\integer{f=randint(1..6)}
\integer{g=randint(1..6)}
\if{\f=\g}{\integer{f=2}
\integer{g=randint(3..6)}}
\integer{h=randint(1..7)}
\if{\e=\h}{\integer{e=2}
\integer{h=randint(3..7)}}
\real{rep2=abs((\e-\h)*(\f-\g))}
\real{rep1=(abs(\e-\h)+abs(\f-\g))*2}
\integer{large=4}
\text{val=10+\lo*\e,10+\lo*\f,10+\lo*\h,10+\lo*\g}
\text{fig=linewidth 4
rect \val,red}
\text{t=}
\for{i=1 to \b}{
  \integer{y=\i}
  \for{j=0 to \a-1}{
    \text{t1=square \xo+\lo*\j,\yo-\y*\lo,\lo,black}
    \text{t=\t
\t1}
  }
  \text{t=\t
\t1}
}
\text{rect=draw(340,300
\t
\fig)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\rect" alt="">
 </div>
 <div class="medium_size text_col">
  <p>\name_enonce[1]</p>
  <div class="spacer"><label for="reply1">
 \name_enonce[2]:
  </label>
  \embed{r1,\large} \(cm\).
  </div>
  <div class="spacer">
  <label for="reply2">
  \name_enonce[3]:</label>
  \embed{r2,\large} \(cm^2\).
  </div>
  </div></div>
}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
