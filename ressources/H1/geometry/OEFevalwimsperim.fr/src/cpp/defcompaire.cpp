target=oefdefcompaire1 oefdefcompaire2 oefdefcompaire3 oefdefcompaire4 oefdefcompaire5
\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_oefdefcompaire1
\text{typ=radio}
\integer{a=8}
\integer{b=7}
\integer{lo=40}
\integer{xo=10}
\integer{yo=290}
\integer{e=randint(1..3)}
\integer{f=randint(1..3)}
\integer{g=randint(1..7-\e)}
\integer{h=randint(1..6-\f)}
\if{\g=\h and \g=4}{\integer{h=3}}
\if{\g=3 and \h=6}{\integer{h=5}}
\if{\g=6 and \h=3}{\integer{h=2}}
\integer{r1=(\h+\g)*2}
\integer{r2=\h*\g}
\integer{r3=\h+\g}
\integer{r4=(\h+\g)*4}
\real{r5=\g*\h/2}
\integer{ch=2}
\text{rep=\r1 \(cm^2),\r2 \(cm^2),\r3 \(cm^2),\r4 \(cm^2),\r5 \(cm^2)}
\integer{large=4}
\text{val=10+\lo*\e,10+\lo*\f,10+\lo*(\e+\g),10+\lo*(\f+\h)}
\text{fig=linewidth 4
rect \val,red}
\text{t=}
\for{i=1 to \b}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{t1=square \xo+\lo*\j,\yo-\y*\lo,\lo,black}
      \text{t=\t
\t1}}
      \text{t=\t
\t1}}
#endif
#if defined TARGET_oefdefcompaire2
\text{typ=radio}
\real{lo=34.64}
\integer{xo=10}
\integer{yo=290}
\integer{e=random(1,3,5,7)}
\integer{f=randint(1..\e)}
\if{\f=2}{\integer{e=random(3,5)}
\integer{g=randint(2..8-\e)}}
{\integer{g=randint(1..8-\e)}}
\integer{r1=3*\f+\g*2}
\integer{r2=0}
\for{i=1 to \f}
     {\integer{r2=(\g+\i-1)*2+1+\r2}}
\if{\f=\g and \f=1}{\integer{r3=2*\f+\g+1}}{\integer{r3=2*\f+\g}}
\integer{r4=\f}
\integer{r5=(\f+\g)*\f}
\integer{ch=2}
\text{rep=\r1 \(cm^2),\r2 \(cm^2),\r3 \(cm^2),\r4 \(cm^2),\r5 \(cm^2)}
\integer{large=4}
\text{val=40,\lo*\e,20*(\f+2),\lo*(\e-\f),20*(\g+2*\f+2),\lo*(\e+\g),20*(\g+2),\lo*(\e+\g)}
\text{fig=linewidth 4
poly red,\val}
\text{t=}
\for{j=0 to 5}
  {\text{t1=parallel 20,\lo*(\j*2-2),0,\lo*(\j*2-1),40,0,10,black
parallel 20,\lo*(\j*2-2),40,\lo*(\j*2-1),40,0,10,black
segment 0,\lo*(\j*2-2),340,\lo*(\j*2-2),black
parallel 40,\lo*\(\j*2-1),20,\lo*(\j*2),40,0,10,black
parallel 0,\lo*(\j*2-1),20,\lo*(\j*2),40,0,10,black
segment 0,\lo*(\j*2-1),340,\lo*(\j*2-1),black}
  \text{t=\t
\t1}}
#endif
#if defined TARGET_oefdefcompaire3
\text{typ=menu}
\integer{e=randint(5..30)}
\integer{f=randint(5..26)}
\integer{k=randint(2..\e-2)}
\integer{l=randint(2..\f-2)}
\integer{lo=10}
\integer{g=(34-\e)/2}
\integer{h=(30-\f)/2}
\integer{m=randint(1..\h)}

\text{rep=supérieure (sans être le double) à,inférieure (sans être la moitié) à,égale à,le double de,la moitié de}

\text{t=linewidth 2
rect \lo*\g,\lo*\h,\lo*(\e+\g),\lo*(\f+\h),black
text black,\lo*\g-10,\lo*\h-10,medium,A
text black,\lo*(\e+\g)+5,\lo*\h-10,medium,B
text black,\lo*(\e+\g)+5,\lo*(\f+\h),medium,C
text black,\lo*\g-10,\lo*(\f+\h),medium,D}

\matrix{fig=rect \lo*\g,\lo*\h,\lo*(\e/2+\g),\lo*(\f+\h),red
triangle \lo*\g,\lo*\h,\lo*\g,\lo*(\f+\h),\lo*(\e+\g),\lo*(\f+\h),red
triangle \lo*(\g+\k),\lo*\h,\lo*\g,\lo*(\f+\h),\lo*(\e+\g),\lo*(\f+\h),red
poly red,\lo*\g,\lo*(\f+\h),\lo*\g,\lo*(\f+\h-\l),\lo*(\k+\g),\lo*(\f+\h-\l),\lo*(\k+\g),\lo*\h,\lo*(\e+\g),\lo*\h,\lo*(\e+\g),\lo*(\f+\h)
poly red,\lo*\g,\lo*(\f+\h),\lo*\g,\lo*\h,\lo*(\k+\g),\lo*(\h-\m),\lo*(\e+\g),\lo*\h,\lo*(\e+\g),\lo*(\f+\h)}

\text{ch=5,5,5,2,1}
\integer{n=randint(1..5)}
\text{fig=row(\n,\fig)}
\integer{ch=\ch[\n]}

#endif
#if defined TARGET_oefdefcompaire4
\text{typ=menu}
\integer{a=16}
\integer{b=14}
\integer{lo=20}
\integer{xo=10}
\integer{yo=290}
\integer{e=randint(1..3)}
\integer{f=randint(0..2)}
\integer{g=randint(1..15-\e)}
\integer{h=randint(1..6-\f)}
\integer{ee=randint(1..3)}
\integer{ff=randint(7..9)}
\integer{l=randint(2..14-\ff)}
\integer{p=randint(1..5)}
\if{\p=1}{\integer{k=abs(\h+\g-\l)}}
\if{\p=2}{\integer{k=randint(1..15-\ee)}}
\if{\p=3}{\integer{l=randint(2..14-\ff)}
\integer{g=randint(1..5)}
\integer{ee=1}
\integer{k=\h*\g/\l}}
\if{\p=4}{\integer{k=abs(\h+\g-\l)}}
\if{\p=5}{\integer{k=abs((\h+\g)/2-\l)}}
\if{\k=0}{\integer{k=3}}
\if{\g=\k}{\integer{g=\g+1}}
\integer{rr=\h*\g}
\integer{rb=\k*\l}
\text{rep=supérieure (sans être le double) à,inférieure (sans être la moitié) à,égale à,le double de,la moitié de}
\if{\rb>\rr}{\integer{ch=1}}
\if{\rb<\rr}{\integer{ch=2}}
\if{\rb=\rr}{\integer{ch=3}}
\integer{r1=\rr*2}
\if{\rb=\r1}{\integer{ch=4}}
\integer{r1=\rr/2}
\if{\rb=\r1}{\integer{ch=5}}
\text{fig=linewidth 4
rect 10+\lo*\e,10+\lo*\f,10+\lo*(\e+\g),10+\lo*(\f+\h),red
rect 10+\lo*\ee,10+\lo*\ff,10+\lo*(\ee+\k),10+\lo*(\ff+\l),blue}
\text{t=}
\for{i=1 to \b}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{t1=square \xo+\lo*\j,\yo-\y*\lo,\lo,black}
      \text{t=\t
\t1}}
      \text{t=\t
\t1}}
#endif
#if defined TARGET_oefdefcompaire5
\text{typ=menu}
\integer{a=16}
\integer{b=14}
\integer{lo=20}
\integer{xo=10}
\integer{yo=290}
\integer{e=randint(1..4)}
\integer{x1=4}
\integer{y1=7}
\integer{x2=12}
\integer{y2=7}

\integer{h=(30-\f)/2}
\integer{m=randint(1..\h)}

\text{rep=supérieure (sans être le double) à,inférieure (sans être la moitié) à,égale à,le double de,la moitié de}

\matrix{figm=rect 10+\lo*(\x1-\e),10+\lo*(\y1-\e),10+\lo*(\x1+\e),10+\lo*(\y1+\e),red
circle 10+\lo*\x2,10+\lo*\y2,\lo*\e*2,blue
point
point
rect 10+\lo*(\x1-\e),10+\lo*\y1,10+\lo*(\x1+\e),10+\lo*(\y1-\e),red
arc 10+\lo*\x2,10+\lo*\y2,\lo*\e*2,\lo*\e*2,180,360,blue
segment 10+\lo*(\x2-\e),10+\lo*\y2,10+\lo*(\x2+\e),10+\lo*\y2,blue
point
rect 10+\lo*(8-\e),10+\lo*(7-\e),10+\lo*(8+\e),10+\lo*(7+\e),red
circle 10+\lo*8,10+\lo*7,\lo*\e*2*sqrt(2),blue
point
point
rect 10+\lo*(8-\e*sqrt(2)),10+\lo*14,10+\lo*(8+\e*sqrt(2)),10+\lo*(14-\e*sqrt(2)),red
arc 10+\lo*8,10+\lo*14,\lo*\e*4,\lo*\e*4,180,360,blue
segment 10+\lo*(8-\e*2),10+\lo*14,10+\lo*(8+\e*2),10+\lo*14,blue
point
rect 10+\lo*(\x1-\e),10+\lo*(\y1-\e),10+\lo*(\x1+\e),10+\lo*(\y1+\e),red
arc 10+\lo*(\x2+\e),10+\lo*(\y2+\e),\lo*\e*4,\lo*\e*4,180,270,blue
segment 10+\lo*(\x2-\e),10+\lo*(\y2+\e),10+\lo*(\x2+\e),10+\lo*(\y2+\e),blue
segment 10+\lo*(\x2+\e),10+\lo*(\y2-\e),10+\lo*(\x2+\e),10+\lo*(\y2+\e),blue
circle 10+\lo*\x1,10+\lo*\y1,\lo*\e*2,red
circle 10+\lo*\x2,10+\lo*\y2,\lo*\e*1.5,blue
point
point
arc 10+\lo*\x1,10+\lo*\y1,\lo*\e*2,\lo*\e*2,180,360,red
segment 10+\lo*(\x1-\e),10+\lo*\y1,10+\lo*(\x1+\e),10+\lo*\y1,red
circle 10+\lo*\x2,10+\lo*\y2,\lo*\e*2,blue
point
circle 10+\lo*\x1,10+\lo*\y1,\lo*\e*2,red
arc 10+\lo*\x2,10+\lo*\y2,\lo*\e*2,\lo*\e*2,0,180,blue
arc 10+\lo*(\x2-\e/2),10+\lo*\y2,\lo*\e,\lo*\e,180,360,blue
arc 10+\lo*(\x2+\e/2),10+\lo*\y2,\lo*\e,\lo*\e,180,360,blue
circle 10+\lo*\x1,10+\lo*\y1,\lo*\e*2,red
arc 10+\lo*\x2,10+\lo*\y2,\lo*\e*2,\lo*\e*2,0,180,blue
arc 10+\lo*(\x2-\e/2),10+\lo*\y2,\lo*\e,\lo*\e,180,360,blue
arc 10+\lo*(\x2+\e/2),10+\lo*\y2,\lo*\e,\lo*\e,0,180,blue}

\text{ch=1,1,2,2,1,1,5,1,5}
\integer{n=randint(1..9)}

\text{fig1=row((\n-1)*4+1,\figm)}
\text{fig2=row((\n-1)*4+2,\figm)}
\text{fig3=row((\n-1)*4+3,\figm)}
\text{fig4=row((\n-1)*4+4,\figm)}
\integer{ch=\ch[\n]}

\text{fig=linewidth 3
\fig1
\fig2
\fig3
\fig4
}
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
#endif
\text{rect=draw(340,300
\t
\fig
)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\rect" alt="">
 </div>
 <div class="medium_size text_col">
  \enonc1 \embed{r1} \enonc2
  </div>
</div>
}

\answer{}{\ch;\rep}{type=\typ}{option=shuffle}
