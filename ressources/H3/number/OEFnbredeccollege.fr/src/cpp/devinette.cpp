target=oefdevinette1 oefdevinette2

\language{fr}
#include "author.inc"
\format{html}
%Paramètres de l'exercice%

#include "lang_titles.inc"
#include "lang.inc"

%Programmation%
#if defined TARGET_oefdevinette1
\integer{nb1=randint(0..999)}
#endif
#if defined TARGET_oefdevinette2
\integer{nb1=randint(100..999)}
\integer{nb5=randint(0..9)}
#endif
\integer{nb2=randint(0..9)}
\integer{nb3=randint(0..9)}
\integer{nb4=randint(0..9)}
#if defined TARGET_oefdevinette1
\real{rep=\nb1+\nb3/10+\nb2/100+\nb4/1000}
#endif
#if defined TARGET_oefdevinette2
\real{rep=\nb1*10+\nb3+\nb2/1000+\nb4/100+\nb5/10}
#endif
%Présentation de la page%

\statement{
<ul class="wims_nopuce">
<li>
#if defined TARGET_oefdevinette1
\name_statement[1] \nb1.
</li><li>
\name_statement[2]
</li><li>
\name_statement[3] \nb2.
</li><li>
\name_statement[4] \nb3.
</li><li>
\name_statement[5] \nb4.
#endif
#if defined TARGET_oefdevinette2
\name_statement[6]
</li><li>
\name_statement[2]
</li><li>
\name_statement[7] \nb1.
</li><li>
\name_statement[5] \nb2.
</li><li>
\name_statement[8] \nb3.
</li><li>
\name_statement[3] \nb4.
</li><li>
\name_statement[4] \nb5.
#endif
</li></ul>
\name_statement[9] : \embed{r1,10}
}

%Analyse de la réponse de l'élève%

\answer{}{\rep}{type=numeric}
