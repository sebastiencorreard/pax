target=frise15
\title{Lettre en frise F2}
\title_nl{Strookpatroongroep letters F2}
\title_en{Frieze with letter F2}
\title_it{Fregi con lettere F2}
\title_es{Friso con letra F2}
\title_ca{Fris amb lletra F2}

#include "auth.inc"
#include "lettre.inc"
\integer{s=16}
\integer{t=8}
\text{colors=shuffle(blue,red,yellow,green,purple,blue,red,yellow,green,purple)}

\matrix{frise=wims(replace internal , by ; in \frise)}
\matrix{frise=wims(replace internal : by , in \frise)}
\text{lettre=\c=1? randrow(\lettre):randrow(\chiffre)}
\text{frise=\lettre[2..-1]}
\matrix{frise=wims(items2lines \frise)}
\matrix{frise=wims(replace internal : by , in \frise)}
\integer{nc=rows(\frise)}

\integer{N=\nc}
\integer{n=2}
\text{Rep=}
\text{Frise=}
\text{rep1=}
\text{frise1=}
\for{u=1 to \N}{
  \for{j=0 to \n}{
    \if{\j>0}{
     \text{h=[\frise[\u;1],\frise[\u;2]]}
    \text{rep=pari(\h+[\j*\s,0])}
    \text{rep=wims(replace internal , by : in \rep)}
    \text{rep1=wims(append item \rep to \rep1)}
    }
    \text{h=[\s-1-(\frise[\u;1]),-(\frise[\u;2])+1]}
    \text{rep=pari(\h+[(\j-2)*\s,0])}
    \text{rep=wims(replace internal , by : in \rep)}
    \text{rep1=wims(append item \rep to \rep1)}
  }
  \text{frise1=wims(append item wims(replace internal , by : in \frise[\u;]) to \frise1)}
}
\text{Frise=wims(append line square \colors[1],\frise1 to \Frise)}
\text{Rep=wims(append line \colors[1],\rep1 to \Rep)}

\integer{x1=(\n)*\s}
\integer{s1=2*\s}
\integer{s2=-\s/2}
\integer{width=200*(\n+1)}
\integer{height=200}
\text{xrange=-\s,\x1}
#include "arrow.inc"
\text{dessin=xrange \xrange
yrange -\t,\t
\Frise
background_color lightgreen
point red,\s2:0
copy 0,0,\translation}
\integer{cnt1=items(\frise1)}
\integer{cnt=items(\rep1)}

#include "lang_warning.inc"
#include "lang_5.inc"

\statement{\instruction
<div class="wimscenter">
\embed{r1, \width x \height
[\dessin]}
</div>
<div class="wims_instruction">\warning</div>
}

\answer{}{\Rep}{type=clicktile}
