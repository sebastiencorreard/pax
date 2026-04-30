target=0709

#include "author.inc"
#include "lang_0709b.inc"
\title{TITLE}
\title_en{TITLE_en}

\real{profondeur=randint(80..150)}
\real{pression=randint(8..15)}
\real{press_at=100*randint(975..1025)}
\real{rhoo=randint(1000..1035)}
\real{gravite=randint(972..988)/100}
\text{image=\imagedir/serie_700_pression_sous_marine4.jpg}

\real{pa_pascal=\press_at+\rhoo*\gravite*\profondeur}
\real{pa_bar=rint(\pa_pascal/100000)}
\text{rupture=\ouinon[1]}
\text{rupture=\pa_bar<=\pression?non}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>

#include "lang_0709.inc"
}
\hint{<p>
\(p_A - p_{at} = \rho.g.h\)
</p>}
\answer{\(p_A) \name_vocab[1;]}{\pa_pascal}{type=default}
\answer{\(p_A) \name_vocab[2;]}{\pa_bar}{type=default}
\choice{\name_vocab[3;]}{\rupture}{\ouinon}
