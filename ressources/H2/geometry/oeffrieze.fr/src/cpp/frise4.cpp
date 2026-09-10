target=frise4
\title{Frise F1lg}
\title_nl{Strookpatroongroep F1lg}
\title_en{Frieze F1lg}
\title_it{Fregi F1lg}
\title_es{Friso F1lg}
\title_ca{Fris F1lg}

#include "auth.inc"
\integer{s=6} pair pour simplifier
\integer{t=3}
\text{colors=shuffle(blue,red,yellow,green,purple,blue,red,yellow,green,purple)}
\text{point=wims(makelist wims(makelist x:y for x = 0 to \s-1) for y=1 to \t)}
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
  \for{j=0 to \n}{
    \if{\j>0}{
     \text{h=[\frise[\u;1],\frise[\u;2]]}
    \text{rep=pari(\h+[\j*\s,0])}
    \text{rep=wims(replace internal , by : in \rep)}
    \text{rep1=wims(append item \rep to \rep1)}
    }{
    \if{\frise[\u;1]>=\s/2}{
    \text{h=[\frise[\u;1],-\frise[\u;2]+1]}
    \text{rep=pari(\h+[-\s/2,0])}
    \text{rep=wims(replace internal , by : in \rep)}
    \text{rep1=wims(append item \rep to \rep1)}
    }
    }
    \text{h=[\frise[\u;1],-\frise[\u;2]+1]}
    \text{rep=pari(\h+[\j*\s + \s/2,0])}
     \if{\rep[1] < (\n+1)*\s}{
       \text{rep=wims(replace internal , by : in \rep)}
       \text{rep1=wims(append item \rep to \rep1)}
     }
    \text{frise1=wims(replace internal , by : in \frise[\u;])}
  }
 \text{Frise=wims(append line square \colors[\u],\frise1 to \Frise)}
 \text{Rep=wims(append line \colors[\u],\rep1 to \Rep)}
}

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
segment red,0:0,\x1:0
copy 0,0,\translation}
#include "lang_warning.inc"
#include "lang_4.inc"
segment red,\s:-\t,\s:\t,0:0,\x1:0,\s1:-\t,\s1:\t
\statement{\instruction
<div class="wimscenter">
\embed{r1, \width x \height
[\dessin]}
 </div>
<div class="wims_instruction">\warning</div>}

\answer{}{\Rep}{type=clicktile}
