target=additrousimpl

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\title{TITRE #}

\integer{choix=randint(2)}
\if{\choix=1}{
              \integer{nb1=randint(1..50)}
              \integer{nb2=randint(-50..50)}
              \integer{\choix2=randint(2)}
              \if{\choix2=1}{\text{expres=,\(\plus \nb1 = \nb2\)}
                              \integer{rep=\nb2-\nb1}}
                            {\text{expres=,\(\minus \nb1 = \nb2\)}
                            \integer{rep=\nb2+\nb1}}}
              {\integer{nb1=randint(-50..50)}
              \integer{nb2=randitem(randint(-50..\nb1-1),randint(\nb1+1..50))}
              \if{\nb2<\nb1}{\text{expres=\(\nb1 \minus\),\(= \nb2\)}
                              \integer{rep=\nb1-\nb2}}
                             {\text{expres=\(\nb1 \plus\),\(= \nb2\)}
                             \integer{rep=\nb2-\nb1}}
              }
\text{trep=\textcolor{green}{\rep}}

\statement{<div><label for="reply1">Trouver le nombre manquant&nbsp;:</label>
\expres[1] \embed{reply1,5} <span class="nowrap">\expres[2].</span></div>}

\answer{?}{\rep}{type=numexp}
\solution{\expres[1] \(\trep\) \expres[2]}
