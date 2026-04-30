target=0708

#include "author.inc"
#include "lang_0708b.inc"
\title{TITLE}
\title_en{TITLE_en}


\real{diametre=randint(100..200)/100}
\real{force=randint(5..20)}
\real{FORCE=randint(600..1000)}
\text{image=\imagedir/serie_700_principe_presse_hydraulique.jpg}

\real{aire_petit=pi*(\diametre/2)^2}
\real{a_p=\aire_petit*10^(-4)}
\real{pression=\force/\a_p}
\real{DIAMETRE=sqrt(\FORCE*10/\pression/pi)}
\real{diam=rint(\DIAMETRE*100)}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>

#include "lang_0708.inc"
<div class="wims_instruction">
#include "lang_common.inc"
</div>

}
\hint{<p>
\name_aide
</p>}

\help{
\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}
}

\answer{\name_vocab[1;] cm<sup>2</sup>}{\aire_petit #4}{type=sigunits}
\answer{\name_vocab[2;] m<sup>2</sup>}{\a_p #4}{type=sigunits}
\answer{\name_vocab[3;]}{\pression #4}{type=sigunits}
\choice{\name_vocab[4;]}{pascal}{joule,watt,calorie}
\answer{\name_vocab[5;]}{\DIAMETRE #4}{type=sigunits}
\choice{\name_vocab[4;]}{m}{mm,cm,dm}
\answer{\name_vocab[6;]}{\diam}{type=real}
