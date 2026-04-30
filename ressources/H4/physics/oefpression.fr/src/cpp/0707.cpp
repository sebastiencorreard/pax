target=0707

#include "author.inc"
#include "lang_0707b.inc"
\title{TITLE}
\title_en{TITLE_en}

\real{diametre=randint(70..140)/10}
\real{force=randint(10..30)}

\real{aire_tete=3.14*(\diametre/2)^2}
\real{a_t=\aire_tete*10^(-6)}
\real{aire_pointe=randint(15..35)/100}
\real{pression_tete=rint(\force/\a_t)}
\real{pression_pointe=\force/(\aire_pointe/1000000)}
\text{image=\imagedir/serie_700_punaise3.jpg}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>
#include "lang_0709.inc"

}
\hint{<p>
\(p=\frac{F}{S}\)
</p>}

\help{
\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}
}

\answer{\name_vocab[1;] mm<sup>2</sup>}{\aire_tete #4}{type=sigunits}
\answer{\name_vocab[2;] m<sup>2</sup>}{\a_t #4}{type=sigunits}
\answer{\name_vocab[3;]}{\pression_tete #4}{type=sigunits}
\choice{\name_vocab[4;]}{pascal}{joule,ampere,volt}
\answer{\name_vocab[5;]}{\pression_pointe #4}{type=sigunits}
\choice{\name_vocab[4;]}{pascal}{joule,ampere,volt}
