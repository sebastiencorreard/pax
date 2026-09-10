target=oeffractdix1 oeffractdix2 oeffractdix3 oeffractdix4 oeffractdix5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}

#if defined TARGET_oeffractdix1
\integer{rg=2}
\integer{chif1=randint(1..99)}
\integer{chif2=randint(1..99-\chif1)}
\real{rep=(\chif1+\chif2)/10^2}
\integer{d1=100}
\integer{d2=100}
\integer{larg=8}
\integer{chif=0}
#endif
#if defined TARGET_oeffractdix2
\integer{rg=2}
\integer{chif1=randint(1..99)}
\integer{chif2=randint(100-\chif1..99)}
\real{rep=(\chif1+\chif2)/10^2}
\integer{d1=100}
\integer{d2=100}
\integer{larg=8}
\integer{chif=0}
#endif
#if defined TARGET_oeffractdix3
\text{rg=shuffle(3)}
\text{rg=item(1..2,\rg)}
\text{rg=wims(sort items \rg)}
\integer{chif1=randint(1..10^\rg[1]-1)}
\integer{chif2=randint(1..10^\rg[2]-\chif1*10^(\rg[2]-\rg[1])-1)}
\real{rep=\chif1/10^\rg[1]+\chif2/10^\rg[2]}
\integer{d1=10^\rg[1]}
\integer{d2=10^\rg[2]}
\integer{larg=8}
\integer{chif=0}
#endif
#if defined TARGET_oeffractdix4
\text{rg=shuffle(3)}
\text{rg=item(1..2,\rg)}
\text{rg=wims(sort items \rg)}
\integer{chif1=randint(1..10^\rg[1]-1)}
\integer{chif2=randint(10^\rg[2]-\chif1*10^(\rg[2]-\rg[1])..10^\rg[2]-1)}
\real{rep=\chif1/10^\rg[1]+\chif2/10^\rg[2]}
\integer{d1=10^\rg[1]}
\integer{d2=10^\rg[2]}
\integer{larg=8}
\integer{chif=0}
#endif
#if defined TARGET_oeffractdix5
\text{rg=shuffle(3)}
\text{rg=item(1..2,\rg)}
\text{rg=wims(sort items \rg)}
\integer{chif=randint(1..9)}
\integer{chif1=randint(1..10^\rg[1]-1)}
\integer{chif2=randint(10^\rg[2]-\chif1*10^(\rg[2]-\rg[1])..10^\rg[2]-1)}
\real{rep=\chif+\chif1/10^\rg[1]+\chif2/10^\rg[2]}
\integer{d1=10^\rg[1]}
\integer{d2=10^\rg[2]}
\integer{larg=8}
#endif
\text{chiff=\chif<>0 ? \chif +:}
\statement{\name_enonc&nbsp;:
<div class="wimscenter">
<label for="reply1">\(
\chiff
\frac{\chif1}{\d1} + \frac{\chif2}{\d2} \)</label>
=\embed{r1,\larg}.
</div>
}
\answer{}{\rep}{type=atext}
\latex{
\begin{statement}
\name_enonc:
\begin{center}\(
\chiff
\frac{\chif1}{\d1} + \frac{\chif2}{\d2} =\)
\end{center}
\end{statement}
}
