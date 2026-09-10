target=oefairequad1 oefairequad2 oefairequad3 oefairequad4 oefairequad5

\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=8}
\integer{b=7}
\integer{lo=40}
\integer{xo=10}
\integer{yo=290}

#if defined TARGET_oefairequad1
\integer{e=randint(1..7)}
\integer{f=randint(1..6)}
\integer{g=randint(1..6)}
\if{\f=\g}{\integer{f=2}
\integer{g=randint(3..6)}}
\integer{h=randint(1..7)}
\if{\e=\h}{\integer{e=2}
\integer{h=randint(3..7)}}
\real{rep=abs((\e-\h)*(\f-\g))}
\integer{large=4}
\text{val=10+\lo*\e,10+\lo*\f,10+\lo*\h,10+\lo*\g}
\text{fig=linewidth 4
rect \val,red}
#endif
#if defined TARGET_oefairequad2
\integer{e=randint(1..7)}
\integer{f=randint(1..6)}
\integer{g=randint(1..6)}
\if{\f=\g}{\integer{f=2}
\integer{g=randint(3..6)}}
\integer{h=randint(1..7)}
\if{\e=\h}{\integer{e=2}
\integer{h=randint(3..7)}}
\real{rep=abs((\e-\h)*(\f-\g)/2)}
\integer{ch=randint(1..2)}
\integer{large=4}
\if{ch=1}{\text{val=10+\lo*\e,10+\lo*\f,10+\lo*\e,10+\lo*\g,10+\lo*\h,10+\lo*\g}}
{\text{val=10+\lo*\e,10+\lo*\f,10+\lo*\h,10+\lo*\f,10+\lo*\h,10+\lo*\g}}
\text{fig=linewidth 4
triangle \val,red}
#endif
#if defined TARGET_oefairequad3
\integer{e=randint(2..6)}
\integer{f=randint(1..\e-1)}
\integer{g=randint(\e+1..7)}

\real{rep=2*(\e*\f+\e*\g-\g*\f-\e*\e)}
\integer{large=4}
\text{val=10+\lo*\f,50+\lo*(\e-\f),10+\lo*\e,50,10+\lo*\g,50+\lo*(\g-\e),10+\lo*(\f+\g-\e),50+\lo*(\g-\f)}
\text{fig=linewidth 4
poly red,\val}
#endif
#if defined TARGET_oefairequad4
\integer{e=randint(1..3)}
\integer{h=randint(5..7)}
\integer{f=randint(\e+1..\h-1)}
\integer{g=randint(\e+1..\h-1)}
\integer{r=1}
\integer{u=randint(3..6)}
\integer{s=randint(2..\u-1)}
\integer{t=randint(2..\u-1)}

\real{rep=((\u-\r)*(\h-\e)+(\s-\t)*(\g-\f))/2}
\integer{large=4}
\text{val=10+\lo*\e,10+\lo*\s,10+\lo*\f,10+\lo*\r,10+\lo*\h,10+\lo*\t,10+\lo*\g,10+\lo*\u}
\text{fig=linewidth 4
poly red,\val}
#endif
#if defined TARGET_oefairequad5
\integer{e=randint(2..6)}
\integer{dd=randint(1..\e/2)*2}
\integer{f=randint(\dd/2..6-\dd/2)}
\integer{xx=ceil((8-\e)/2)}
\integer{yy=1+\dd/2}

\real{rep=\e*\f}
\integer{large=4}
\integer{ch=randint(1..2)}
\if{\ch=1}
{\text{fig=linewidth 3
arc 10+\lo*(\xx+\dd/2),10+\lo*\yy,\lo*\dd,\lo*\dd,180,360,red
segment 10+\lo*(\xx+\dd),10+\lo*\yy,10+\lo*(\xx+\e),10+\lo*\yy,red
segment 10+\lo*(\xx+\e),10+\lo*\yy,10+\lo*(\xx+\e),10+\lo*(\yy+\f),red
segment 10+\lo*(\xx+\e),10+\lo*(\yy+\f),10+\lo*(\xx+\dd),10+\lo*(\yy+\f),red
arc 10+\lo*(\xx+\dd/2),10+\lo*(\yy+\f),\lo*\dd,\lo*\dd,180,360,red
segment 10+\lo*\xx,10+\lo*(\yy+\f),10+\lo*\xx,10+\lo*\yy,red}}
{\text{fig=linewidth 3
arc 10+\lo*\yy,10+\lo*(\xx+\dd/2),\lo*\dd,\lo*\dd,90,270,red
segment 10+\lo*\yy,10+\lo*(\xx+\dd),10+\lo*\yy,10+\lo*(\xx+\e),red
segment 10+\lo*\yy,10+\lo*(\xx+\e),10+\lo*(\yy+\f),10+\lo*(\xx+\e),red
segment 10+\lo*(\yy+\f),10+\lo*(\xx+\e),10+\lo*(\yy+\f),10+\lo*(\xx+\dd),red
arc 10+\lo*(\yy+\f),10+\lo*(\xx+\dd/2),\lo*\dd,\lo*\dd,90,270,red
segment 10+\lo*(\yy+\f),10+\lo*\xx,10+\lo*\yy,10+\lo*\xx,red}}
#endif

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
\name_enonce
<div class="spacer">
<label for="reply1">\name_question:</label>
  \embed{r1,\large} \(cm^2\).
</div>
</div></div>
}

\answer{}{\rep}{type=numeric}
