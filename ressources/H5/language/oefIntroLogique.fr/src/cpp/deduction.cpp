target=deduction

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\integer{init= 10}
\text{monaide=}
\for{ii = 8 to 10}{
  \text{currrecord=wims(record \ii of \glossaire)}
  \text{monaide=\monaide
	\currrecord}
}
\help{\monaide}

\integer{a=random(1..\init)}

\text{A=item(\a,\Alist)}
\text{B=item(\a,\Blist)}
\text{nonA=item(\a,\nonAlist)}
\text{nonB=item(\a,\nonBlist)}

\text{AouB=\A \name_ou \B}
\text{AetB=\A \name_et \B}

\text{nonAouB=\nonA \name_ou  \B}
\text{AounonB=\A \name_ou  \nonB}
\text{nonAounonB=\nonA \name_ou  \nonB}
\text{nonAetB=\nonA \name_et  \B}
\text{AetnonB=\A \name_et  \nonB}
\text{niAniB= \nonA \name_et  \nonB}

\text{si=\a<4?\Si1:\Si2}

\integer{casH=random(1..2)}
\integer{casC=random(1..6)}
\text{hyp=\A,\nonB}
\text{H=item(\casH,\hyp)}

/** liste d'assertions ; les  4 premières sont justes **/
\text{ass=\casH==1?
\B,\AetB,\AounonB,\nonAouB,\nonAounonB,\nonAetB,\AetnonB,\niAniB:
\nonA,\nonAounonB,\niAniB,\AounonB, \nonAetB,\AetnonB,\A,\AetB}

\text{C=item(\casC,\ass)}

\integer{rep=\casC<5?1:2}

\statement{<div class="wims_question">
<ul>
<li>
<p>\name_statement1</p>
<div class="wimscenter"><span class="fraseB"> \(H_1) : " \si \A, \alors \B "</span></div>
</li>
<li>
<p>\name_statement2</p>
<div class="wimscenter"><span class="fraseA"> \(H_2) : " \H "</span></div>
</li>
<li>
<p>\name_statement3</p>
<div class="wimscenter"><span class="fraseC"> \(C) : "  \C "</span></div>
</li>
</ul>

<div>\name_statement4 \embed{reply1}</div>
</div>}

??
\Alist
\answer{\name_answer}{\rep;\oui,\non}{type=checkbox}
