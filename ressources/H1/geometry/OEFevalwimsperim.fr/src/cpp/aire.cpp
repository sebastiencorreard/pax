target=oefaire1 oefaire2 oefaire3 oefaire4 oefaire5

\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefaire1
\integer{a=randint(1..12)}
\integer{lo=\a*25}
\integer{la=\a*25}
\integer{xo=\lo/2}
\integer{yo=\la/2}

\integer{rep=\a*\a}
\integer{large=4}
\text{rect=draw(280,240
rect 140-\xo/2,110+\yo/2,140+\xo/2,110-\yo/2,black
)}
\text{enonc1=\name_enonc1[1] \a cm \name_enonc1[2]}
\text{enonc2=\(cm^2\)}
#endif
#if defined TARGET_oefaire2
\integer{a=randint(2..9)}
\integer{c=randint(2..9)}
\integer{lo=20}
\integer{xo=170-(\a)*10}
\integer{yo=150+(\c)*10}

\integer{rep=\a*\c}
\integer{large=4}
\text{t=}
\for{i=1 to \c}{
  \integer{y=\i}
  \for{j=0 to \a-1}{
    \text{t1=square \xo+20*\j,\yo-\y*\lo,\lo,black}
    \text{t=\t
\t1}}
  \text{t=\t
\t1}}
\text{rect=draw(340,300
\t
)}
\text{enonc1=\name_enonc1[1] 1 cm \name_enonc1[2]}
\text{enonc2=\(cm^2)}
#endif
#if defined TARGET_oefaire3
\integer{a=randint(2..9)}
\integer{c=randint(2..9)}
\integer{d=randint(2..9)}

\integer{lo=20}
\integer{xo=170-(\a)*10}
\integer{yo=150+(\c)*10}

\integer{rep=\a*\c*\d^2}
\integer{large=6}

\text{t=}
\for{i=1 to \c}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{t1=square \xo+20*\j,\yo-\y*\lo,\lo,black}
      \text{t=\t
\t1}}
      \text{t=\t
\t1}}

\text{rect=draw(340,300
\t
)}

\text{enonc1=\name_enonc1[1] \d cm \name_enonc1[2]}
\text{enonc2=\(cm^2)}
#endif
#if defined TARGET_oefaire4
\integer{a=randint(17..99)}
\integer{b=randint(6..\a-10)}
\integer{rep=\a*\b}
\integer{large=6}
\text{enonc1=\name_enonc1[1] \a cm, \name_enonc1[2] \b cm.}
\text{enonc2=\(cm^2)}
\text{rect=draw(150,100
rect 20,20,130,80,black
)}
#endif
#if defined TARGET_oefaire5
\integer{ua=randint(1..3)}
\integer{ub=randint(1..3)}
\integer{uc=randint(1..3)}
\if{\ua=1}{\integer{a=randint(2..9)*10}}{\integer{a=randint(17..99)}}
\if{\ub=1}{\integer{b=randint(1..\a/10)*10}}{\integer{b=randint(6..\a-10)}}
\real{afa=\a*10^(\ua-2)}
\real{afb=\b*10^(\ub-2)}

\text{unit=dm,cm,mm}
\integer{rep=\a*\b}
\integer{large=6}

\text{enonc1=\name_enonc1[1] \afa \unit[\ua], \name_enonc1[2] \afb \unit[\ub].}
\text{enonc2=\(cm^2)}

\text{rect=draw(150,100
rect 20,20,130,80,black
)}
#endif
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\rect" alt="">
 </div>
 <div class="medium_size text_col">\enonc1
  <div class="spacer">
  <label for="reply1">\enonc11</label> \embed{r1,\large} \enonc2.</div>
</div></div>
}

\answer{}{\rep}{type=numeric}
