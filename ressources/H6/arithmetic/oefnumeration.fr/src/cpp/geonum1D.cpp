target=geonum1D

#include "header.inc"
#include "lang_titles.inc"

###publié dans H6/arithmetic/oefnumeration.fr

\title{TITLE}
\title_it{TITLE_it}
\integer{N=randint(4..7)}
\text{M=7}

\text{sequence=slib(stat/random \N, 0,1,Z)}

\text{test=position(0,\sequence)}
\text{sequence=items(\test)>(\N+1)/2 ? wims(replace item number \test[1] by 1 in \sequence)}
\text{nombre=0.wims(nospace wims(items2words \sequence))}
\text{n=0}
\for{j = 1 to \N}{
  \real{n=\n + 2^(-\j)*\sequence[\j]}
 }

\text{dessin=xrange 0,1.1
yrange -1,1
hline black,0,0
parallel 0,-0.1,0,0.1,2^(-\M+1),0,2^(\M+1),grey
parallel 0,-0.2,0,0.2,2^(-\M+2),0,2^(\M+1),red
parallel 0,-0.3,0,0.3,2^(-\M+3),0,2^(\M+1),blue
parallel 0,-0.4,0,0.4,2^(-\M+4),0,2^(\M+1),green
parallel 0,-0.5,0,0.5,2^(-\M+5),0,2^(\M+1),orange
parallel 0,-0.6,0,0.6,2^(-\M+6),0,2^(\M+1),purple
text black,1,0,large,1
text black,0,0,large,0
}
\text{dessin1=\dessin
linewidth 10
point \n,0,green}
\text{point=slib(draw/convpixel \n,0,700,100,0,1.1,-1,1,0,pixels)}
\text{dessin=draw(700,100
\dessin1)
}
\text{dessinlatex=drawtikz(700,100
\dessin1)}
#include "lang.inc"

\statement{\name_statement
<div class="wimscenter">
<img src="\dessin" alt="">
</div>
<div class="wimscenter">\embed{r1,10
default}
</div>
<div class="wims_instruction">\name_instruction_point</div>
}

\answer{}{\nombre}{type=numeric}{option=comma}

\latex{
\begin{statement}
\begin{center}
\dessinlatex
\end{center}
\name_statement
\end{statement}
}
