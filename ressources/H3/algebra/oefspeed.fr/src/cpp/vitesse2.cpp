target=vitesse2

#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#include "lang.inc"
\real{v=randint(0..24)*5}
\integer{hd=randint(0..10)}
\integer{ha=randint(\hd+3..\hd+7)}
\integer{t=\ha-\hd}
\integer{d=\v*\t}
\integer{kmd=randint(10000..10500)}
\integer{kma=\kmd+\d}

\steps{reply1
reply2
reply3}
\text{enonce=wims(replace internal XXXX by \hd in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \kmd in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \ha in \enonce)}
\text{enonce=wims(replace internal TTTT by \kma in \enonce)}


\statement{\enonce <div>
\if {\step=1}{\name_question[1]? }
\if {\step=2}{\name_question[2]?}
\if {\step=3}{\name_question2[1;] \d km \name_question2[2;] \t \name_hkm[1].
  \name_question2[3;]?}
</div>
<div class="wims_instruction">\name_instruction</div>}

\answer{\name_answer[1]}{\d km} {type=units}
\answer{\name_answer[2]}{\t h} {type=units}
\answer{\name_answer[3]}{\v km/h}{type=units}

\hint{\if{\step=1}{\name_hint1}
  \if{\step=2}{\name_hint2}
  \if{\step=3}{\name_hint3}
}
