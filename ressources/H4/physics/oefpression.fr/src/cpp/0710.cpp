target=0710

#include "author.inc"
#include "lang_0710b.inc"

\title{TITLE}
\title_en{TITLE_en}

\real{masse=randint(1800..2500)/100}
\real{diametre=randint(8..15)}
\real{rho_cu=randint(850..895)/100}
\real{gravite=randint(972..988)/100}
\real{rho_eau=randint(975..1025)/1000}

\real{volume=\masse/\rho_cu}
\real{poids=(\masse/1000)*\gravite}
\real{archimede=((\volume*\rho_eau)/1000)*\gravite}
\real{poids_app=\poids-\archimede}
\text{image=\imagedir/serie_700_cuivre2.jpg}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>

#include "lang_0710.inc"
<div class="wims_instruction">
#include "lang_common.inc"
</div>
<p>
\name_vocab[1;] \(\rho_{\name_vocab[7;]}= \rho_cu\) g/cm<sup>3</sup>,
 g = \gravite N/kg,
 \(\rho_\name_vocab[8;] = \rho_eau)\ g/cm<sup>3</sup>.
</p>
}
\hint{<p>
\(p_A - p_{at} = \rho.g.h\)
</p>}

\help{

\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}
}
\answer{\name_vocab[2;] cm<sup>3</sup>}{\volume #4}{type=sigunits}
\answer{\name_vocab[3;]}{\poids #4}{type=sigunits}
\choice{\name_vocab[4;]}{newton}{joule,kg,pascal,bar}
\answer{\name_vocab[5;]}{\archimede #4}{type=sigunits}
\choice{\name_vocab[4;]}{newton}{joule,kg,pascal,bar}
\answer{\name_vocab[6;]}{\poids_app #4}{type=sigunits}
\choice{\name_vocab[4;]}{newton}{joule,kg,pascal,bar}
