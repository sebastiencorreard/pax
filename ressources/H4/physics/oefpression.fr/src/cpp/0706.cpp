target=0706

#include "author.inc"
#include "lang_0706b.inc"
\title{TITLE}
\title_en{TITLE_en}

\integer{diametre=random(4..12)}
\integer{force=10*random(300..400)}

\real{surface=pi*(\diametre/2)^2}
\real{surf=\surface*10^(-4)}
\real{pression=\force*10/\surf}
\real{press=rint(\pression/100000)}
\text{image=\imagedir/serie_700_transpalette.jpg}

\statement{
#include "lang_0706.inc"
<div class="wims_instruction">
#include "lang_common.inc"
</div>
}
\hint{<p>
\( p=\frac{F}{S}\)
</p>}

\help{
\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}
}

\answer{\name_vocab[1;] cm<sup>2</sup>}{\surface #4}{type=sigunits}
\answer{\name_vocab[2;] m<sup>2</sup>}{\surf #4}{type=sigunits}
\answer{\name_vocab[3;] }{\pression #4}{type=sigunits}
\answer{\name_vocab[4;]}{\press #4}{type=sigunits}
