target=situation situationsimpl

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=slib(lang/fname fr)}
\integer{nb1=randint(2..10)}
\integer{nb2=randint(2..10)}

#if defined TARGET_situation
\title{TITRE}
#endif
#if defined TARGET_situationsimpl
\title{TITRE #}
#endif

\matrix{liste1=La température descend de \nb2&nbsp°C puis descend de \nb1&nbsp;°C.,\( (-\nb2) + (-\nb1) \),\( - \nb2 - \nb1 \)
La température monte de \nb2&nbsp;°C puis monte de \nb1&nbsp;°C., \( (+\nb2) + (+\nb1) \),\( \nb2 + \nb1 \)
La température monte de \nb2&nbsp;°C puis descend de \nb1&nbsp;°C., \( (+\nb2) + (-\nb1) \),\( \nb2 - \nb1 \)
La température descend de \nb2&nbsp;°C puis monte de \nb1&nbsp;°C., \( (-\nb2) + (+\nb1) \),\( -\nb2 + \nb1 \)}
\matrix{liste2=\nom descend de \nb2 étages puis descend de \nb1 étages.,\( (-\nb2) + (-\nb1) \),\( - \nb2 - \nb1\)
\nom monte de \nb2 étages puis monte de \nb1 étages., \( (+\nb2) + (+\nb1) \),\( \nb2 + \nb1 \)
\nom monte de \nb2 étages puis descend de \nb1 étages., \( (+\nb2) + (-\nb1) \),\( \nb2 - \nb1 \)
\nom descend de \nb2 étages puis monte de \nb1 étages., \( (-\nb2) + (+\nb1) \),\( -\nb2 + \nb1 \)}
\matrix{liste3=\nom perd \nb2&nbsp;€ puis perd \nb1&nbsp;€.,\( (-\nb2) + (-\nb1) \),\( - \nb2 - \nb1\)
\nom gagne \nb2&nbsp;€ puis gagne \nb1&nbsp;€., \( (+\nb2) + (+\nb1) \),\( \nb2 + \nb1 \)
\nom gagne \nb2&nbsp;€ puis perd \nb1&nbsp;€., \( (+\nb2) + (-\nb1) \),\( \nb2 - \nb1 \)
\nom perd \nb2&nbsp;€ puis gagne \nb1&nbsp;€., \( (-\nb2) + (+\nb1) \),\( -\nb2 + \nb1 \)}
\integer{k=randint(3)}
\if{\k=1}{\matrix{liste=\liste1}}
\if{\k=2}{\matrix{liste=\liste2}}
\if{\k=3}{\matrix{liste=\liste3}}
\statement{ Associer chaque phrase à l'addition qui lui correspond.
\if{\k=3}{<p>Lors d'un jeu de hasard,</p>}
<div class="wimscenter">\embed{reply1,75x160x2x3}</div>}
#if defined TARGET_situation
\answer{}{\liste[;1];\liste[;2]}{type=correspond}{option=split}
#endif
#if defined TARGET_situationsimpl
\answer{}{\liste[;1];\liste[;3]}{type=correspond}{option=split}
#endif
