target=oefvolume1 oefvolume2 oefvolume3 oefvolume4 oefvolume5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefvolume1
\integer{a=randint(1..9)}
\integer{lo=\a*10}
\integer{la=\a*10}
\integer{ha=\a*5}
\integer{xo=\lo+\ha}
\integer{yo=\la+\ha}

\integer{rep=\a*\a*\a}
\integer{large=4}
\text{pave=draw(340,300
rect 170-\xo/2,130+\yo/2,170+\xo/2-\ha,130-\yo/2+\ha,black
segment 170+\xo/2-\lo,130-\yo/2,170+\xo/2,130-\yo/2,black
segment 170+\xo/2-\lo,130-\yo/2,170+\xo/2-\lo-\ha,130-\yo/2+\ha,black
segment 170+\xo/2,130-\yo/2,170+\xo/2-\ha,130-\yo/2+\ha,black
segment 170+\xo/2,130-\yo/2,170+\xo/2,130-\yo/2+\la,black
segment 170+\xo/2-\ha,130-\yo/2+\ha+\la,170+\xo/2,130-\yo/2+\la,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2,130-\yo/2+\la,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2-\lo-\ha,130-\yo/2+\la+\ha,black
dsegment 170+\xo/2-\lo,130-\yo/2+\la,170+\xo/2-\lo,130-\yo/2,black
)}
\text{enonc1=\name_enonce1[1] \a cm \name_enonce1[2]}
\text{enonc2=\name_enonce2}
#endif
#if defined TARGET_oefvolume2
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{c=randint(2..9)}
\integer{lo=20}
\integer{xo=170-(\a+\b/2)*10}
\integer{yo=150+(\c+\b/2)*10}

\integer{rep=\a*\b*\c}
\integer{large=4}

\text{t=}
\for{i=1 to \c}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{t1=square \xo+20*\j,\yo-\y*\lo,\lo,black}
      \text{t=\t
\t1}}
      \text{t=\t
\t1}}

\integer{xo=170-(\a+\b/2)*10+\a*20}
\integer{yo=150+(\c+\b/2)*10}
\text{tt=}
\for{i=1 to \c}
    {\integer{y=\i}
      \for{j=0 to \b-1}
       {\text{tt1=poly black,\xo+10*\j,\yo-\y*\lo-10*\j,\xo+10*\j+10,\yo-\y*\lo-10-10*\j,\xo+10*\j+10,\yo-\y*\lo+10-10*\j,\xo+10*\j,\yo-\y*\lo+20-10*\j}
      \text{tt=\tt
\tt1}}
      \text{tt=\tt
\tt1}}

\integer{xo=170-(\a+\b/2)*10}
\integer{yo=150+(\c+\b/2)*10-20*\c}
\text{ttt=}
\for{i=0 to \b-1}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{ttt1=poly black,\xo+20*\j+10*\i,\yo-\y*(\lo/2),\xo+20*\j+10+10*\i,\yo-\y*(\lo/2)-10,\xo+20*\j+30+10*\i,\yo-\y*(\lo/2)-10,\xo+20*\j+20+10*\i,\yo-\y*(\lo/2)}
      \text{ttt=\ttt
\ttt1}}
      \text{ttt=\ttt
\ttt1}}

\text{pave=draw(340,300
\ttt
\tt
\t
)}

\text{enonc1=\name_enonce1}
\text{enonc2=\name_enonce2}
#endif
#if defined TARGET_oefvolume3
\integer{a=randint(2..9)}
\integer{b=randint(2..9)}
\integer{c=randint(2..9)}
\integer{d=randint(2..9)}

\integer{lo=20}
\integer{xo=170-(\a+\b/2)*10}
\integer{yo=150+(\c+\b/2)*10}

\integer{rep=\a*\b*\c*\d^3}
\integer{large=6}

\text{t=}
\for{i=1 to \c}{
  \integer{y=\i}
  \for{j=0 to \a-1}{
    \text{t1=square \xo+20*\j,\yo-\y*\lo,\lo,black}
    \text{t=\t
\t1}}
  \text{t=\t
\t1}
}

\integer{xo=170-(\a+\b/2)*10+\a*20}
\integer{yo=150+(\c+\b/2)*10}
\text{tt=}
\for{i=1 to \c}
    {\integer{y=\i}
      \for{j=0 to \b-1}
       {\text{tt1=poly black,\xo+10*\j,\yo-\y*\lo-10*\j,\xo+10*\j+10,\yo-\y*\lo-10-10*\j,\xo+10*\j+10,\yo-\y*\lo+10-10*\j,\xo+10*\j,\yo-\y*\lo+20-10*\j}
      \text{tt=\tt
\tt1}}
      \text{tt=\tt
\tt1}}

\integer{xo=170-(\a+\b/2)*10}
\integer{yo=150+(\c+\b/2)*10-20*\c}
\text{ttt=}
\for{i=0 to \b-1}
    {\integer{y=\i}
      \for{j=0 to \a-1}
       {\text{ttt1=poly black,\xo+20*\j+10*\i,\yo-\y*(\lo/2),\xo+20*\j+10+10*\i,\yo-\y*(\lo/2)-10,\xo+20*\j+30+10*\i,\yo-\y*(\lo/2)-10,\xo+20*\j+20+10*\i,\yo-\y*(\lo/2)}
      \text{ttt=\ttt
\ttt1}}
      \text{ttt=\ttt
\ttt1}}

\text{pave=draw(340,300
\ttt
\tt
\t
)}

\text{enonc1=\name_enonce1[1] \d \name_enonce1[2]}
\text{enonc2=\name_enonce1[2]}
#endif
#if defined TARGET_oefvolume4
\integer{a=randint(17..99)}
\integer{b=randint(6..\a-10)}
\integer{c=randint(2..49)}
\integer{rep=\a*\b*\c}
\integer{large=6}
\text{enonc1=\name_enonce1[1] \a cm, \name_enonce1[2] \b cm \name_enonce1[3] \c cm.}
\text{enonc2=\name_enonce2}
\integer{lo=120}
\integer{la=60}
\integer{ha=50}
\integer{xo=\lo+\ha}
\integer{yo=\la+\ha}

\text{pave=draw(200,180
rect 100-\xo/2,80+\yo/2,100+\xo/2-\ha,80-\yo/2+\ha,black
segment 100+\xo/2-\lo,80-\yo/2,100+\xo/2,80-\yo/2,black
segment 100+\xo/2-\lo,80-\yo/2,100+\xo/2-\lo-\ha,80-\yo/2+\ha,black
segment 100+\xo/2,80-\yo/2,100+\xo/2-\ha,80-\yo/2+\ha,black
segment 100+\xo/2,80-\yo/2,100+\xo/2,80-\yo/2+\la,black
segment 100+\xo/2-\ha,80-\yo/2+\ha+\la,100+\xo/2,80-\yo/2+\la,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2,80-\yo/2+\la,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2-\lo-\ha,80-\yo/2+\la+\ha,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2-\lo,80-\yo/2,black
)}
#endif
#if defined TARGET_oefvolume5
\integer{ua=randint(1..3)}
\integer{ub=randint(1..3)}
\integer{uc=randint(1..3)}
\if{\ua=1}{\integer{a=randint(2..9)*10}}{\integer{a=randint(17..99)}}
\if{\ub=1}{\integer{b=randint(1..\a/10)*10}}{\integer{b=randint(6..\a-10)}}
\if{\uc=1}{\integer{c=randint(2..7)*10}}{\integer{c=randint(2..69)}}
\real{afa=\a*10^(\ua-2)}
\real{afb=\b*10^(\ub-2)}
\real{afc=\c*10^(\uc-2)}

\text{unit=dm,cm,mm}
\integer{rep=\a*\b*\c}
\integer{large=6}

\text{enonc1=\name_enonce1[1] \afa \unit[\ua], \name_enonce1[2] \afb \unit[\ub] et
  \name_enonce1[3] \afc \unit[\uc].}
\text{enonc2=\name_enonce2}
\integer{lo=120}
\integer{la=60}
\integer{ha=50}
\integer{xo=\lo+\ha}
\integer{yo=\la+\ha}

\text{pave=draw(200,180
rect 100-\xo/2,80+\yo/2,100+\xo/2-\ha,80-\yo/2+\ha,black
segment 100+\xo/2-\lo,80-\yo/2,100+\xo/2,80-\yo/2,black
segment 100+\xo/2-\lo,80-\yo/2,100+\xo/2-\lo-\ha,80-\yo/2+\ha,black
segment 100+\xo/2,80-\yo/2,100+\xo/2-\ha,80-\yo/2+\ha,black
segment 100+\xo/2,80-\yo/2,100+\xo/2,80-\yo/2+\la,black
segment 100+\xo/2-\ha,80-\yo/2+\ha+\la,100+\xo/2,80-\yo/2+\la,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2,80-\yo/2+\la,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2-\lo-\ha,80-\yo/2+\la+\ha,black
dsegment 100+\xo/2-\lo,80-\yo/2+\la,100+\xo/2-\lo,80-\yo/2,black
)}
#endif
\text{enonc3=\(\mathrm{cm}^3\)}
\statement{
  <div class="wims_columns">
  <div class="medium_size img_col"><img src="\pave" alt=""></div>
  <div class="medium_size text_col">
  \enonc1 <label for="reply1">\enonc2:</label> \embed{r1,\large} \enonc3:
  </div></div>
}

\answer{}{\rep}{type=numeric}
