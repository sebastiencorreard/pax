target=0704

#include "author.inc"
#include "lang_0704b.inc"
\title{TITLE}
\title_en{TITLE_en}

\integer{index=randint(1..3)}
\text{monument=item(\index,\monu)}
\text{article1=item(\index,\arti1)}
\text{article2=item(\index,\arti2)}
\text{article3=item(\index,\arti3)}
\text{article4=item(\index,\arti4)}
\integer{pied=random(1..4)}
\text{lpieds=3,4,5,6}
\text{lmpieds=trois,quatre,cinq,six}
\real{pieds=item(\pied,\lpieds)}
\text{mpieds=item(\pied,\lmpieds)}

\real{masse=randint(3..8)*100+random(1,2,3,4)*random(25,30,40,70)}
\real{surface=randint(2..9)+random(-1,1)*random(0,0.25,0.5)}
\real{gravite=randint(972..988)/100}
\real{poids=\masse*1000*\gravite}
\real{pression=\poids/(\pieds*\surface)}
\text{image=\imagedir/serie_700_tour_eiffel.jpg}

\statement{
<div class="float_left spacer"><img src="\image" alt=""></div>
#include "lang_0704.inc"

<div class="wims_instruction">
#include "lang_common.inc"
</div>
}
\hint{
<p>
\(P=m g\)<br>
\(p=\frac{F}{S}\)
</p>}

\help{
\if{\help_subject issametext fscient or \help_subject issametext }
{
#include "lang_help.inc"
}

}

\answer{\name_vocab[1;] \(P)}{\poids N#4}{type=sigunits}
\answer{\name_vocab[2;] \(p)}{\pression Pa#4}{type=sigunits}
