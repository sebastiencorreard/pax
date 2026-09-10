target=frise1
\title{Frise F1}
\title_nl{Strookpatroongroep F1}
\title_en{Frieze group F1}
\title_it{Fregi F1}
\title_es{Friso F1}
\title_ca{Fris F1}
#include "auth.inc"
\integer{s=6}
\integer{t=3}
\text{colors=shuffle(blue,red,yellow,green,purple,blue,red,yellow,green,purple)}
\text{point=wims(makelist wims(makelist x:y for x = 0 to \s-1) for y=-\t+1 to \t)}
\text{point=shuffle(\point)}
\integer{N=5}
\matrix{frise=\point[1..\N]}
\matrix{frise=wims(replace internal , by ; in \frise)}
\matrix{frise=wims(replace internal : by , in \frise)}

\integer{n=3}
\text{Rep=}
\text{Frise=}
\for{u=1 to \N}{
  \text{rep1=}
  \for{j=1 to \n}{
    \text{h=[\frise[\u;1],\frise[\u;2]]}
    \text{rep=pari(\h+[\j*\s,0])}
    \text{rep=wims(replace internal , by : in \rep)}
    \text{rep1=wims(append item \rep to \rep1)}
    \text{frise1=wims(replace internal , by : in \frise[\u;])}
  }
 \text{Frise=wims(append line square \colors[\u],\frise1 to \Frise)}
 \text{Rep=wims(append line \colors[\u],\rep1 to \Rep)}
}
matrix{Rep=\Rep}
\integer{x1=(\n+1)*\s}
\integer{s1=2*\s}
\integer{width=100*(\n+1)}
\integer{height=100}
\text{xrange=0,\x1}
#include "arrow.inc"
\text{dessin=xrange \xrange
yrange -\t,\t
\Frise
background_color lightgreen
copy 0,0,\translation}

#include "lang_warning.inc"
#include "lang_1.inc"

\statement{\instruction
<div class="wimscenter">
\embed{r1, \width x \height
[\dessin]}
</div>
<div class="wims_instruction">\warning</div>
}

\answer{}{\Rep}{type=clicktile}
