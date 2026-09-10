target=oefranger1 oefranger2 oefranger3 oefranger4 oefranger5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
text{inf=draw(32,32
linewidth 3
segment 8,16,24,8,black
segment 8,16,24,24,black)}
text{sup=draw(32,32
linewidth 3
segment 8,8,24,16,black
segment 8,24,24,16,black)}
text{ego=draw(32,32
linewidth 3
segment 8,12,24,12,black
segment 8,20,24,20,black)}

text{sign=<img src="\inf" alt="">,<img src="\sup" alt="">,<img src="\ego" alt="">}
\text{sign=\(\Large{<}\),\(\Large{>}\),\(\Large{=}\)}
#if defined TARGET_oefranger1
\text{nb=wims(values x/10 for x=1 to 99)}
\text{nb=shuffle(\nb)}
\text{nb=item(1..4,\nb)}
\integer{a=random(1,2)}
\if{\a=1}{\text{nb=wims(sort numeric items \nb)}}
    {\text{nb=wims(sort reverse numeric items \nb)}}
\text{enonc1= \nb[1]}
\text{enonc2= \nb[2]}
\text{enonc3= \nb[3] }
\text{enonc4= \nb[4]}
\text{rep=\sign[\a]}
\matrix{rep1=\rep
\sign[3],\sign[2/\a]}
\matrix{rep2=\rep
\sign[3],\sign[2/\a]}
\matrix{rep3=\rep
\sign[3],\sign[2/\a]}
\integer{rep4=\a}
\text{size=50x50}
\text{typ=menu}
#endif
#if defined TARGET_oefranger2
\text{voc1=\voc}
\text{chif=shuffle(9)}
\text{nb1=item(1..3,\chif)}
\text{nb2=}
\for{i=1 to 3}
   {\if{\i<>1}{\text{nb2=\nb2,\nb1[\i]}}{\text{nb2=\nb2,0}}}
\text{nb2=item(2..4,\nb2)}
\text{nb3=}
\for{i=1 to 3}
   {\if{\i<>2}{\text{nb3=\nb3,\nb1[\i]}}{\text{nb3=\nb3,0}}}
\text{nb3=item(2..4,\nb3)}
\text{nb4=}
\for{i=1 to 3}
   {\if{\i<>3}{\text{nb4=\nb4,\nb1[\i]}}{\text{nb4=\nb4,0}}}
\text{nb4=item(2..4,\nb4)}
\integer{v1=0}
\integer{v2=0}
\integer{v3=0}
\integer{v4=0}
\for{i=1 to 3}
   {\real{v1=\v1+\nb1[\i]*10^(3-\i)}
    \real{v2=\v2+\nb2[\i]*10^(3-\i)}
    \real{v3=\v3+\nb3[\i]*10^(3-\i)}
    \real{v4=\v4+\nb4[\i]*10^(3-\i)}
}
\text{nb=\v1,\v2,\v3,\v4}
\integer{a=random(1,2)}
\if{\a=1}{\text{nb=wims(sort numeric items \nb)}}
    {\text{nb=wims(sort reverse numeric items \nb)}}
\text{\enonc1=\voc1[\a]&nbsp;}
\text{\enonc2= ; }
\text{\enonc3= ; }
\text{\enonc4= ; }
\text{rep1=\nb[1]}
\text{rep2=\nb[2]}
\text{rep3=\nb[3]}
\text{rep4=\nb[4]}
\text{size=50x32}
\text{typ=dragfill}
\text{voc=}
#endif
#if defined TARGET_oefranger3
\text{chif=shuffle(9)}
\text{nb1=item(1..3,\chif)}
\text{nb2=}
\for{i=1 to 3}
   {\if{\i<>1}{\text{nb2=\nb2,\nb1[\i]}}{\text{nb2=\nb2,0}}}
\text{nb2=item(2..4,\nb2)}
\text{nb3=}
\for{i=1 to 3}
   {\if{\i<>2}{\text{nb3=\nb3,\nb1[\i]}}{\text{nb3=\nb3,0}}}
\text{nb3=item(2..4,\nb3)}
\text{nb4=}
\for{i=1 to 3}
   {\if{\i<>3}{\text{nb4=\nb4,\nb1[\i]}}{\text{nb4=\nb4,0}}}
\text{nb4=item(2..4,\nb4)}
\integer{v1=0}
\integer{v2=0}
\integer{v3=0}
\integer{v4=0}
\for{i=1 to 3}
   {\real{v1=\v1+\nb1[\i]*10^(3-\i)}
    \real{v2=\v2+\nb2[\i]*10^(3-\i)}
    \real{v3=\v3+\nb3[\i]*10^(3-\i)}
    \real{v4=\v4+\nb4[\i]*10^(3-\i)}
}
\text{nb=\v1,\v2,\v3,\v4}
\integer{a=random(1,2)}
\if{\a=1}{\text{nb=wims(sort numeric items \nb)}}
    {\text{nb=wims(sort reverse numeric items \nb)}}
\text{enonc1=\name_enonc1:}
\text{enonc2= \sign[\a] }
\text{enonc3= \sign[\a] }
\text{enonc4= \sign[\a] }
\text{rep1=\nb[1]}
\text{rep2=\nb[2]}
\text{rep3=\nb[3]}
\text{rep4=\nb[4]}
\text{size=50x50}
\text{typ=dragfill}
\text{voc=}
#endif
#if defined TARGET_oefranger4
\text{chif=shuffle(9)}
\text{nb1=item(1..4,\chif)}
\text{nb2=\nb1[1],\nb1[3],\nb1[2],\nb1[4]}
\text{nb3=\nb1[1],\nb1[2],\nb1[3],0}
\text{nb4=\nb1[1],\nb1[2],0,0}
\integer{v1=0}
\integer{v2=0}
\integer{v3=0}
\integer{v4=0}
\for{i=1 to 4}
   {\real{v1=\v1+\nb1[\i]/10^(\i-1)}
    \real{v2=\v2+\nb2[\i]/10^(\i-1)}
    \real{v3=\v3+\nb3[\i]/10^(\i-1)}
    \real{v4=\v4+\nb4[\i]/10^(\i-1)}
}
\text{nb=\v1,\v2,\v3,\v4}
\integer{a=random(1,2)}
\if{\a=1}{\text{nb=wims(sort numeric items \nb)}}
    {\text{nb=wims(sort reverse numeric items \nb)}}
\text{enonc1= \name_enonc1}
\text{enonc2= \sign[\a] }
\text{enonc3= \sign[\a] }
\text{enonc4= \sign[\a] }
\text{rep1=\nb[1]}
\text{rep2=\nb[2]}
\text{rep3=\nb[3]}
\text{rep4=\nb[4]}
\text{size=50x50}
\text{typ=dragfill}
\text{voc=}
#endif
#if defined TARGET_oefranger5
\text{chif=shuffle(9)}
\text{nb1=item(1..4,\chif)}
\text{nb2=\nb1[1],\nb1[2],0,\nb1[4]}
\text{nb3=\nb1[1],0,\nb1[3],\nb1[4]}
\text{nb4=\nb1[1],\nb1[2],\nb1[3],0}
\integer{v1=0}
\integer{v2=0}
\integer{v3=0}
\integer{v4=0}
\for{i=1 to 4}{
  \real{v1=\v1+\nb1[\i]/10^(\i-1)}
  \real{v2=\v2+\nb2[\i]/10^(\i-1)}
  \real{v3=\v3+\nb3[\i]/10^(\i-1)}
  \real{v4=\v4+\nb4[\i]/10^(\i-1)}
}
\text{nb=\v1,\v2,\v3,\v4}
\integer{a=random(1,2)}
\if{\a=1}{\text{nb=wims(sort numeric items \nb)}}
    {\text{nb=wims(sort reverse numeric items \nb)}}
\text{enonc1= \name_enonc1}
\text{enonc2= \sign[\a] }
\text{enonc3= \sign[\a] }
\text{enonc4= \sign[\a] }
\text{rep1=\nb[1]}
\text{rep2=\nb[2]}
\text{rep3=\nb[3]}
\text{rep4=\nb[4]}
\text{size=50x50}
\text{typ=dragfill}
\text{voc=}
#endif
#if defined TARGET_oefranger1
\text{reptex=}
#else
\text{reptex=\rep1,\rep2,\rep3,\rep4}
\text{reptex=wims(replace internal ; by , in \reptex)}
\text{reptex=wims(listuniq \reptex)}
\text{reptex=shuffle(\reptex)}
#endif
#if defined TARGET_oefranger1
\statement{
\name_enonc1:<div class="wimscenter">
\enonc1 \embed{r1,\size}
\enonc2 \embed{r2,\size}
\enonc3 \embed{r3,\size}
\enonc4
</div>
\name_enonc4 \embed{r4,\size}
}
\latex{
\begin{statement}
\name_enonc1
\begin{center}
\enonc1 \(\ldots\)
\enonc2 \(\ldots\)
\enonc3 \(\ldots\)
\enonc4
\end{center}
\name_enonc4 \(\ldots\)
\end{statement}
}
#endif
#if defined TARGET_oefranger2
\statement{
\name_enonc1[1] \name_enonc1[2] \enonc1:
<div class="wimscenter">
\embed{r1,\size}
\enonc2 \embed{r2,\size}
\enonc3 \embed{r3,\size}
\enonc4 \embed{r4,\size}
</div>
\name_enonc4
}
\latex{
\begin{statement}
\name_enonc1[1] \reptex \name_enonc1[2] \enonc1
\begin{center}
\(\ldots\)
\enonc2 \(\ldots\)
\enonc3 \(\ldots\)
\enonc4 \(\ldots\)
\end{center}
\name_enonc4
\end{statement}
}
#endif
#if defined TARGET_oefranger3 || defined TARGET_oefranger4 || defined TARGET_oefranger5
\statement{\name_enonc1
<div class="wimscenter">
\embed{r1,\size}
\enonc2 \embed{r2,\size}
\enonc3 \embed{r3,\size}
\enonc4 \embed{r4,\size}
</div>}
\latex{
\begin{statement}
\name_enonc1 \reptex
\begin{center}
\(\ldots\)
\enonc2 \(\ldots\)
\enonc3 \(\ldots\)
\enonc4 \(\ldots\)
\end{center}
\end{statement}
}
#endif

\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
\answer{}{\rep3}{type=dragfill}
\answer{}{\rep4;\voc}{type=\typ}
