target=oefecritdeclitt1 oefecritdeclitt2 oefecritdeclitt3 oefecritdeclitt4 oefecritdeclitt5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{1000000}
#if defined TARGET_oefecritdeclitt1
\matrix{rg=1,2,4
1,2,5
1,3,4
1,3,5
1,4,5}
\integer{a=randint(1..5)}
\text{rg=row(\a,\rg)}
\text{chif=2,3,4,5,6,7,8,9}
\text{chif=shuffle(\chif)}
\real{rep=\chif[1]+\chif[2]/10^(\rg[2]-1)+\chif[3]/10^(\rg[3]-1)}
\text{enonc=\name_enonc}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdeclitt2
\integer{rg=randint(3..5)}
\integer{u=randint(2..9)}
\integer{nb=randint(11..99)}
\real{rep=\u+\nb/10^(\rg-1)}
\text{enonc=\name_enonc}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdeclitt3
\integer{rg=randint(2..5)}
\integer{nb=randint(11..999)}
\real{rep=\nb/10^(\rg-1)}
\text{enonc=\name_enonc}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdeclitt4
\integer{rg=randint(2..5)}
\integer{nb1=randint(11..999)}
\real{nb=\nb1/10^(\rg-1)}
\text{rep=\rangdec[\rg]}
\text{enonc=\name_enonc}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdeclitt5
\matrix{rg=1,2,4
1,2,5
1,3,4
1,3,5
1,4,5}
\integer{a=randint(1..5)}
\text{rg=row(\a,\rg)}
\text{chif=2,3,4,5,6,7,8,9}
\text{chif=shuffle(\chif)}
\real{nb=\chif[1]+\chif[2]/10^(\rg[2]-1)+\chif[3]/10^(\rg[3]-1)}
\text{enonc=\name_enonc}
\integer{larg=8}
#endif
#if defined TARGET_oefecritdeclitt1
\text{ennombre=\chif[1] \rangdec[1] \chif[2] \rangdec[\rg[2]] \chif[3] \rangdec[\rg[3]]=}
#endif
#if defined TARGET_oefecritdeclitt2
\text{ennombre=\u \rangdec[1] \nb \rangdec[\rg]=}
#endif
#if defined TARGET_oefecritdeclitt3
\text{ennombre=\nb \rangdec[\rg]=}
#endif
#if defined TARGET_oefecritdeclitt4
\text{ennombre=\nb  = \nb1}
#endif
#if defined TARGET_oefecritdeclitt1 || defined TARGET_oefecritdeclitt2 || defined TARGET_oefecritdeclitt3 || defined TARGET_oefecritdeclitt4
\statement{
\enonc:
<div class="wimscenter">
\ennombre
\embed{r1,\larg}</div>
}
\answer{}{\rep}{type=atext}
\latex{
\begin{statement}
\enonc:
\begin{center}
\ennombre \(\dots\dots\)
\end{center}
\end{statement}
}
#endif
#if defined TARGET_oefecritdeclitt5
\statement{
\enonc
<div class="wimscenter">
\nb  = \chif[1] \embed{r1,\larg} \chif[2] \embed{r2,\larg} \chif[3] \embed{r3,\larg}
</div>
}
\answer{}{1;\rangdec}{type=menu}
\answer{}{\rg[2];\rangdec}{type=menu}
\answer{}{\rg[3];\rangdec}{type=menu}
#endif
