target=0705

#include "author.inc"

\integer{masse=10*random(15..35)}


\integer{quantite=random(10..25)}
\real{gravite=randint(972..988)/100}
\integer{masse2=randint(20..40)}
\real{longueur=random(2,2.5,3,3.5,4,4.5,5,5.5,6,6.5)}
\real{largeur=(\longueur/2)+random(-1,1)*random(0.25,0.5,0.75)}
\text{image=\imagedir/serie_700_gerbage.jpg}

\real{poids=\quantite*\masse*\gravite}
\real{pression=(\poids+\masse2*\gravite)/(\longueur*\largeur)}

#include "lang_0705b.inc"
\title{TITLE}
\title_en{TITLE_en}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>
#include "lang_0705.inc"
<div class="wims_instruction">
#include "lang_common.inc"
</div>
}
\hint{<p>
\(P=m g\)<br>
\(p=\frac{F}{S}\)
</p>}

\help{

\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}
}
\solution{
\name_solution
}

\answer{\name_vocab[1;]}{\poids N#4}{type=sigunits}
\answer{\name_vocab[2;]}{\pression Pa#4}{type=sigunits}
