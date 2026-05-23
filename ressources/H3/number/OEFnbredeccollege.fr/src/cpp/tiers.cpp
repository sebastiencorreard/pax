target=oeftiers1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
%Paramètres de l'exercice%

\language{fr}

\format{html}

%Programmation%

\integer{nb2=randint(1..49)}
\integer{nb1=2*\nb2}
\integer{nb4=randint(1..12)}
\integer{nb3=\nb4*3}
\integer{nb5=randint(1..12)}
\integer{nb6=\nb5*4}
\integer{nb7=randint(1..12)}
\integer{nb8=\nb7*3}
\integer{nb10=randint(1..12)}
\integer{nb9=\nb10*4}
\integer{nb11=randint(1..49)}
\integer{nb12=\nb11*2}
\text{rep1=\name_voc[1]}
\text{rep2=\name_voc[2]}
\text{rep3=\name_voc[3]}
\text{rep4=\name_voc[4]}
\text{rep5=\name_voc[5]}
\text{rep6=\name_voc[6]}

%Présentation de la page%
\statement{
\name_stat
<ul><li>
\nb1 \name_isthe[1] \embed{r1,10} \name_of \nb2.
</li><li>
\nb3 \name_isthe[2] \embed{r2,10} \name_of \nb4.
</li><li>
\nb5 \name_isthe[3] \embed{r3,10} \name_of \nb6.
</li><li>
\nb7 \name_isthe[4] \embed{r4,10} \name_of \nb8.
</li><li>
\nb9 \name_isthe[5] \embed{r5,10} \name_of \nb10.
</li><li>
\nb11 \name_isthe[6] \embed{r6,10} \name_of \nb12.
</li></ul>
<div class="wims_instruction">\name_inst</div>
}

%Analyse de la réponse de l'élève%

\answer{}{\rep1}{type=case nocase}
\answer{}{\rep2}{type=case nocase}
\answer{}{\rep3}{type=case nocase}
\answer{}{\rep4}{type=case nocase}
\answer{}{\rep5}{type=case nocase}
\answer{}{\rep6}{type=case nocase}
