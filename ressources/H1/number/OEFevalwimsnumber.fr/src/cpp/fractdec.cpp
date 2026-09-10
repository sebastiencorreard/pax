target=oeffractdec1 oeffractdec2 oeffractdec3 oeffractdec4 oeffractdec5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}
#if defined TARGET_oeffractdec1
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
\integer{rep1=10^(\rg[2]-1)}
\integer{rep2=10^(\rg[3]-1)}
\text{enonc=\name_enonc}
\integer{larg=3}
#endif
#if defined TARGET_oeffractdec2
\matrix{rg=1,2,4
1,2,5
1,3,4
1,3,5
1,4,5}

\integer{a=randint(1..5)}
\text{rg=row(\a,\rg)}
\text{chif=1,2,3,4,5,6,7,8,9}
\text{chif=shuffle(\chif)}
\real{nb=\chif[1]+\chif[2]/10^(\rg[2]-1)+\chif[3]/10^(\rg[3]-1)}
\integer{rep1=10^(\rg[2]-1)}
\integer{rep2=10^(\rg[3]-1)}
\text{enonc=\name_enonc}
\integer{larg=3}
#endif
#if defined TARGET_oeffractdec3
\text{rg=shuffle(4)}
\text{rg=item(1..2,\rg)}
\text{rg=wims(sort items \rg)}
\text{chif=shuffle(9)}
\real{nb=\chif[1]+\chif[2]/10^\rg[1]+\chif[3]/10^\rg[2]}
\integer{nb1=\chif[2]*10^(\rg[2]-\rg[1])+\chif[3]}
\integer{rep1=10^\rg[2]}

\text{enonc=\name_enonc}
\integer{larg=3}
#endif
#if defined TARGET_oeffractdec4
\matrix{rg=1,2,4
1,2,5
1,3,4
1,3,5
1,4,5}
\integer{a=randint(1..5)}
\text{rg=row(\a,\rg)}
\text{chif=1,2,3,4,5,6,7,8,9}
\text{chif=shuffle(\chif)}
\real{rep=\chif[1]+\chif[2]/10^(\rg[2]-1)+\chif[3]/10^(\rg[3]-1)}
\integer{d1=10^(\rg[2]-1)}
\integer{d2=10^(\rg[3]-1)}
\integer{larg=8}
\text{enonc=\name_enonc:
  <div class="wimscenter">\(\chif[1] + \frac{\chif[2]}{\d1} + \frac{\chif[3]}{\d2} \)
}
#endif
#if defined TARGET_oeffractdec5
\text{rg=shuffle(4)}
\text{rg=item(1..2,\rg)}
\text{rg=wims(sort items \rg)}
\text{chif=shuffle(9)}
\real{rep=\chif[1]+\chif[2]/10^\rg[1]+\chif[3]/10^\rg[2]}
\integer{nb=\chif[2]*10^(\rg[2]-\rg[1])+\chif[3]}
\integer{d1=10^\rg[2]}
\integer{larg=8}
\text{enonc=\name_enonc: <div class="wimscenter">\(\chif[1] + \frac{\nb}{\d1} \)
}
#endif
#if TARGET_oeffractdec1
\statement{\enonc
<div class="wimscenter">
\special{mathmlinput [\nb = \chif[1] + \frac{\chif[2]}{reply1}+\frac{\chif[3]}{reply2}], \larg
reply1
reply2}
</div>
}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\latex{
\begin{statement}
\enonc \(\nb= \chif[1] + \frac{\chif[2]}{\dots}+\frac{\chif[3]}{\dots}\)
\end{statement}
}
#endif
#if TARGET_oeffractdec2
\statement{\enonc
<div class="wimscenter">
\special{mathmlinput [\nb = reply1 + \frac{reply2}{reply4} + \frac{reply3}{reply5} ],\larg
reply1
reply2
reply3
reply4
reply5}
</div>
}
\answer{}{\chif[1]}{type=numeric}
\answer{}{\chif[2]}{type=numeric}
\answer{}{\chif[3]}{type=numeric}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\latex{
\begin{statement}
\enonc \(\nb = \dots + \frac{\dots}{\dots} + \frac{\dots}{\dots}\)
\end{statement}
}
#endif
#if defined TARGET_oeffractdec3
\statement{\enonc
<div class="wimscenter">
\special{mathmlinput [ \nb= reply1 + \frac{reply2}{reply3} ],\larg
reply1
reply2
reply3}
</div>
}
\answer{}{\chif[1]}{type=numeric}
\answer{}{\nb1}{type=numeric}
\answer{}{\rep1}{type=numeric}
\latex{
\begin{statement}
\enonc \(\nb = \dots\dots + \frac{\dots\dots}{\dots\dots}\)
\end{statement}
}
#endif
#if defined TARGET_oeffractdec4 || defined TARGET_oeffractdec5
\statement{\enonc = \embed{r1,\larg} </div>}

\answer{}{\rep}{type=atext}
\latex{
\begin{statement}
\enonc = \(\dots\dots\)
\end{statement}
}
#endif
