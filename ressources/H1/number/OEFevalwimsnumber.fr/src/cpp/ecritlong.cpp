target=oefecritlong1 oefecritlong2 oefecritlong3 oefecritlong4 oefecritlong5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

\text{rangdec=km,hm,dam,m,dm,cm,mm}
#if defined TARGET_oefecritlong1
\text{nb=randint(1..9)}
\integer{a=randint(0..1)}
\if{\a=0}{\text{nb=\nb ,0 ,randint(1..9),randint(0..9)}}
{\text{nb=\nb , randint(1..9), 0, randint(1..9)}}
\real{rep=\nb[1]+\nb[2]/10+\nb[3]/100+\nb[4]/1000}
\text{enonc=\name_enonc}
\text{enonc1=\nb[1] \rangdec[4]}
\for{i=2 to 4}{
  \if{\nb[\i]<>0}{\text{enonc1=\enonc1 + \nb[\i] \rangdec[\i+3]}}}
\integer{u=4}
\integer{larg=8}
#endif
#if defined TARGET_oefecritlong2
\text{nb=randint(1..9)}
\integer{a=randint(0..1)}
\if{\a=0}{\text{nb=\nb ,0 ,randint(1..9),randint(0..9)}}
{\text{nb=\nb , randint(1..9), 0, randint(1..9)}}
\real{rep=\nb[1]+\nb[2]/10+\nb[3]/100+\nb[4]/1000}
\integer{nb1=\rep*1000-\nb[1]*1000}
\text{enonc=\name_enonc}
\text{enonc1= \nb[1] \rangdec[4] + \nb1 \rangdec[7]}
\integer{u=4}
\integer{larg=8}
#endif
#if defined TARGET_oefecritlong3
\integer{r1=randint(1..4)}
\integer{r2=randint(\r1+1..6)}
\integer{r3=randint(\r2+1..7)}
\text{nb=randint(1..9),randint(1..9),randint(1..9)}
\real{rep=\nb[1]*10^(4-\r1)+\nb[2]*10^(4-\r2)+\nb[3]*10^(4-\r3)}
\text{enonc=\name_enonc}
\text{enonc1=\nb[1] \rangdec[\r1] + \nb[2] \rangdec[\r2] + \nb[3] \rangdec[\r3]}
\integer{u=4}
\integer{larg=8}
#endif
#if defined TARGET_oefecritlong4
\integer{r1=randint(1..4)}
\integer{r2=randint(\r1+1..6)}
\integer{r3=randint(\r2+1..7)}
\text{nb=randint(1..9),randint(1..9),randint(1..9)}
\real{nb1=\nb[1]*10^(4-\r1)+\nb[2]*10^(4-\r2)+\nb[3]*10^(4-\r3)}
\text{enonc=\name_enonc}
\text{enonc1=\nb1 m}
\integer{larg=8}
#endif
#if defined TARGET_oefecritlong5
\integer{r1=randint(1..4)}
\integer{r2=randint(\r1+1..6)}
\integer{r3=randint(\r2+1..7)}
\text{nb=randint(1..9),randint(1..9),randint(1..9)}
\real{nb1=\nb[1]*10^(\r1-\r1)+\nb[2]*10^(\r1-\r2)+\nb[3]*10^(\r1-\r3)}
\real{nb2=\nb[2]*10^(\r3-\r2)+\nb[3]*10^(\r3-\r3)}
\text{enonc=\name_enonc}
\text{enonc1=\nb1 \rangdec[\r1]}
#endif
#if defined TARGET_oefecritlong1 || defined TARGET_oefecritlong2 || defined TARGET_oefecritlong3
\statement{
\enonc: <div class="wimscenter">\enonc1 = \embed{r1,\larg} \rangdec[\u]</div>
}
\answer{}{\rep}{type=atext}
\latex{
\begin{statement}
\enonc \begin{center}\enonc1 = \(\dots\dots\) \rangdec[\u]\end{center}
\end{statement}
}
#endif
#if defined TARGET_oefecritlong4
\statement{
\enonc:
<div class="wimscenter">
\enonc1=\nb[1] \embed{r1,\larg} + \nb[2] \embed{r2,\larg} + \nb[3] \embed{r3,\larg}
</div>}

\answer{}{\r1;\rangdec}{type=menu}
\answer{}{\r2;\rangdec}{type=menu}
\answer{}{\r3;\rangdec}{type=menu}
\latex{
\begin{statement}
\enonc \begin{center}
\enonc1=\nb[1] \(\dots\dots\) + \nb[2] \(\dots\dots\) + \nb[3] \(\dots\dots\)?.
\end{center}
\end{statement}
}
#endif
#if defined TARGET_oefecritlong5
\statement{
\enonc:
<div class="wimscenter">
\enonc1=\nb[1] \embed{r1,\larg} + \nb2 \embed{r2,\larg}
</div>}
\answer{}{\r1;\rangdec}{type=menu}
\answer{}{\r3;\rangdec}{type=menu}
\latex{
\begin{statement}
\enonc \begin{center}
\enonc1=\nb[1] \(\dots\dots\) + \nb[2] \(\dots\dots\).
\end{center}
\end{statement}
}
#endif
