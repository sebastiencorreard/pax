target=geonum2D

#include "header.inc"
#include "lang_titles.inc"

###publié dans H6/arithmetic/oefnumeration.fr

\title{TITLE}
\title_it{TITLE_it}
\integer{N=randint(4..5)}
\text{M=6}

\text{sequence1=slib(stat/random \N, 0,1,Z)}
\text{sequence2=slib(stat/random \N, 0,1,Z)}

\text{test=position(0,\sequence1)}
\text{sequence1=items(\test)>(\N+1)/2 ? wims(replace item number \test[1] by 1 in \sequence1)}
\text{nombre1=0.wims(nospace wims(items2words \sequence1))}
\text{nombre2=0.wims(nospace wims(items2words \sequence2))}

\text{n1=0}
\text{n2=0}
\for{j = 1 to \N}{
  \real{n1=\n1 + 2^(-\j)*\sequence1[\j]}
  \real{n2=\n2 + 2^(-\j)*\sequence2[\j]}
 }

\text{dessin=xrange -0.2,1.1
yrange -0.2,1.1

parallel 0,-0.05,0,1.1,2^(-\M+1),0,2^(\M+1),grey
parallel 0,-0.1,0,1.1,2^(-\M+2),0,2^(\M+1),red
parallel 0,-0.15,0,1.1,2^(-\M+3),0,2^(\M+1),blue
parallel 0,-0.2,0,1.1,2^(-\M+4),0,2^(\M+1),green
parallel 0,-0.2,0,1.1,2^(-\M+5),0,2^(\M+1),black
parallel -0.05,0,1.1,0,0,2^(-\M+1),2^(\M+1),grey
parallel -0.1,0,1.1,0,0,2^(-\M+2),2^(\M+1),red
parallel -0.15,0,1.1,0,0,2^(-\M+3),2^(\M+1),blue
parallel -0.2,0,1.1,0,0,2^(-\M+4),2^(\M+1),green
parallel -0.2,0,1.1,0,0,2^(-\M+5),2^(\M+1),black
hline black,0,0
vline black,0,0
text black,1,0,large,1
text black,-0.02,0,large,0
text black,-0.02,1,large,1

}
\text{dessin1=\dessin
linewidth 10
point \n1,\n2,green}

\text{point=slib(draw/convpixel \n1,\n2,500,500,-0.2,1.1,-0.2,1.1,0,pixels)}
\text{dessin=draw(500,500
\dessin1)}
\text{dessinlatex=drawtikz(500,500
\dessin1)}
#include "lang.inc"
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dessin" alt=""></div>
 <div class="medium_size text_col">
\name_statement
<div class="wimscenter">(\embed{r1,6
default}, \embed{r2,6
default})
</div>
<div class="wims_instruction">\name_instruction_point</div>
</div></div>
}

\answer{}{\nombre1}{type=numeric}{option=comma}
\answer{}{\nombre2}{type=numeric}{option=comma}

\latex{
\begin{statement}
\begin{center}
\dessinlatex
\end{center}
\name_statement
\end{statement}
}
