target=oefencadr1 oefencadr2 oefencadr3 oefencadr4 oefencadr5

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
\text{sign=\(\Large{< }\),\(\Large{>}\), \(\Large{=}\)}
#if defined TARGET_oefencadr1
\text{chif=randint(0..4),randint(1..9),randint(2..9)}

\text{chif1=\chif[1],\chif[2],0}
\text{chif4=\chif[1],\chif[2],randint(1..\chif[3]-1)}
\integer{a=random(1,2)}
\integer{nb=0}
\integer{nb1=0}
\integer{nb4=0}
\for{i=1 to 3}{\real{nb=\nb+\chif[\i]*10^(3-\i)}
     \real{nb1=\nb1+\chif1[\i]*10^(3-\i)}
     \real{nb4=\nb4+\chif4[\i]*10^(3-\i)}}
\integer{nb2=\nb1+10}
\integer{nb3=\nb+100}
\text{rep=\nb1,\nb2,\nb3,\nb4}
\if{\a=1}{\text{rep=wims(sort numeric items \rep)}}
    {\text{rep=wims(sort reverse numeric items \rep)}}
\text{enonc1= \name_enonc1}
\text{enonc2= \sign[\a] \nb \sign[\a] }

\matrix{rep1=\rep[2]
\rep[1]}
\matrix{rep2=\rep[3]
\rep[4]}
\text{size=50x32}
\text{typ=dragfill}
#endif
#if defined TARGET_oefencadr2
\text{chif=randint(0..9),randint(1..9),randint(1..9),randint(1..9)}
\text{chif1=\chif[1],\chif[2],0,0}
\text{chif4=\chif[1],0,0,0}
\integer{a=random(1,2)}
\integer{nb=0}
\integer{nb1=0}
\integer{nb2=0}
\integer{nb3=0}
\integer{nb4=0}
\for{i=1 to 4}{
  \real{nb=\nb+\chif[\i]/10^(\i-2)}
  \real{nb1=\nb1+\chif1[\i]/10^(\i-2)}
  \real{nb4=\nb4+\chif4[\i]/10^(\i-2)}}
\integer{nb2=\nb1+1}
\integer{nb3=\nb*100}
\text{rep=\nb1,\nb2,\nb3,\nb4}
\if{\a=1}{\text{rep=wims(sort numeric items \rep)}}
    {\text{rep=wims(sort reverse numeric items \rep)}}
\text{enonc1= \name_enonc1}
\text{enonc2= \sign[\a] \nb \sign[\a] }
\matrix{rep1=\rep[2]
\rep[1]}
\matrix{rep2=\rep[3]
\rep[4]}
\text{size=50x32}
\text{typ=dragfill}
#endif
#if defined TARGET_oefencadr3
\text{chif=randint(0..9),randint(1..9),randint(1..9),randint(1..9)}
\text{chif1=\chif[1],\chif[2],0,0}
\text{chif4=\chif[1],\chif[2],\chif[3],0}
\integer{a=random(1,2)}
\integer{nb=0}
\integer{nb1=0}
\integer{nb2=0}
\integer{nb3=0}
\integer{nb4=0}
\for{i=1 to 4}
   {\real{nb=\nb+\chif[\i]/10^(\i-2)}
     \real{nb1=\nb1+\chif1[\i]/10^(\i-2)}
     \real{nb4=\nb4+\chif4[\i]/10^(\i-2)}}
\real{nb2=\nb1+1}
\real{nb3=\nb4+0.1}
\text{rep=\nb1,\nb2,\nb3,\nb4}
\if{\a=1}{\text{rep=wims(sort numeric items \rep)}}
    {\text{rep=wims(sort reverse numeric items \rep)}}
\text{enonc1=\name_enonc1}
\text{enonc2= \sign[\a] \nb \sign[\a] }

\matrix{rep1=\rep[2]
\rep[1]}
\matrix{rep2=\rep[3]
\rep[4]}
\text{size=50x32}
\text{typ=dragfill}
#endif
#if defined TARGET_oefencadr4
\text{chif=randint(0..9),randint(1..9),randint(1..9),randint(1..9)}
\text{chif1=\chif[1],\chif[2],0,0}
\integer{nb=0}
\integer{rep1=0}
\for{i=1 to 4}{
  \real{nb=\nb+\chif[\i]/10^(\i-2)}
  \real{rep1=\rep1+\chif1[\i]/10^(\i-2)}}
\real{rep2=\rep1+1}
\text{enonc1= \name_enonc1}
\text{enonc2= \sign[1] \nb \sign[1] }
\text{size=6}
\text{typ=atext}
#endif
#if defined TARGET_oefencadr5
\text{chif=randint(0..9),randint(1..9),randint(1..9),randint(1..9),randint(1..9)}
\integer{a=randint(1..2)}
\if{\a=1}{\text{chif1=\chif[1],\chif[2],\chif[3],0,0}}
      {\text{chif1=\chif[1],\chif[2],\chif[3],\chif[4],0}}
\integer{nb=0}
\integer{rep1=0}
\for{i=1 to 5}{
  \real{nb=\nb+\chif[\i]/10^(\i-2)}
  \real{rep1=\rep1+\chif1[\i]/10^(\i-2)}}
\if{\a=1}{\real{rep2=\rep1+0.1}}{\real{rep2=\rep1+0.01}}
\text{enonc1= \name_enonc1[1] \rang[\a] \name_enonc1[2]}
\text{enonc2= \sign[1] \nb \sign[1] }
\text{size=6}
\text{typ=numeric}
#endif
#if defined TARGET_oefencadr1 || defined TARGET_oefencadr2 || defined TARGET_oefencadr3
\text{reptex=wims(replace internal ; by , in \rep1,\rep2)}
\text{reptex=shuffle(\reptex)}
\text{reptex=wims(replace internal , by ,$ $ in \reptex)}
#else
\text{reptex=}
#endif
\statement{\enonc1: <div class="wimscenter">\embed{r1,\size}
\enonc2 \embed{r2,\size}
</div>}

\answer{}{\rep1}{type=\typ}
\answer{}{\rep2}{type=\typ}
\latex{
\begin{statement}
\enonc1: \begin{center} \(\dots\dots\)
\enonc2 \(\dots\dots\)
\end{center}
\reptex
\end{statement}
}
