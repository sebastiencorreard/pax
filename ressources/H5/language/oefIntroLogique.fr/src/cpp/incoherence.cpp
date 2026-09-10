target=incoherence

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\range{-10..10}
\text{monaide=}
\for{ii = 8 to 10}{
  \text{currrecord=wims(record \ii of \glossaire)}
  \text{monaide=\monaide
	\currrecord}
}
\help{\monaide}

\integer{a=random(1..6)}
\integer{cas=random(1..3)}

\text{A=\Alist[\a]}
\text{B=\Blist[\a]}
\text{C=\Clist[\a]}
\text{D=\Dlist[\a]}
\text{E=\Elist[\a]}

\text{nonA=\nonAlist[\a]}
\text{nonB=\nonBlist[\a]}
\text{nonC=\nonClist[\a]}
\text{nonD=\nonDlist[\a]}
\text{nonE=\nonElist[\a]}

\text{\si=\a<4?\si1:\si2}

\text{liste=shuffle(\A,\B,\C,\D,\E)}

/** reglement 1; contradiction sur A et D  **/

\text{reg=\cas==1?shuffle(
\si \B \alors \A,
\C \name_ou \B,
\si \E \alors \nonD,
\D \ssi \A,
\si \C \alors \A \name_et \E,
\si \A \alors \C)
}

\text{rep=\cas==1?position(\A,\liste),position(\D,\liste)}

/** reglement 2; contradiction sur A  **/

\text{reg=\cas==2?shuffle(
\A \name_ou \B,
\si \B \name_ou \si \C \alors  \A ,
\si \A \ssi \D,
\si \D \name_ou  \si \nonC \alors \nonA ,
\si \B \alors \nonC)
}

\text{rep=\cas==2?position(\A,\liste)}

/** reglement 3; contradiction sur B  et A ; A et B étant équivalent**/

\text{reg=\cas==3?shuffle(
\A \name_ou \B,  \D \name_ou \C,
\si \A \name_et \si \D \alors  \B ,
\si \A \name_et \si \C \alors  \B ,
\si \D \name_et \si \C \alors  \nonB ,
\si \B \name_et \si \nonD \alors \nonA,
\si \B \name_et \si \nonC \alors \nonA,
\si \nonA \alors \nonB)
}

\text{rep=\cas==3?position(\B,\liste),position(\A,\liste)}

\integer{numliste=items(\liste)}

\statement{<div class="wims_question">
<p>
\name_statement1 \if{\a<4}{\name_statement2}{\name_statement3} \name_statement4\spacebeforecolon:
</p>
<ol>
<li>\reg[1]</li>
<li>\reg[2]</li>
<li>\reg[3]</li>
<li>\reg[4]</li>
<li>\reg[5]</li>
\if{\cas!=2}{<li>\reg[6]</li>}
\if{\cas==3}{<li>\reg[7]</li>}
\if{\cas==3}{<li>\reg[8]</li>}
</ol>

<p>\name_question1 <span class="wims_emph">\name_question2</span>\spacebeforecolon\name_question3 <span class="wims_emph">\name_question4</span>
\name_question5.<br/>
\name_question6
</p>
<ul class="inline">
\for{k=1 to \numliste}{
<li class="unbreakable">\embed{r1,\k}</li>
}
</ul>
</div>
<div class="wims_instruction">\name_remark</div>
}

\answer{\Contradiction}{\rep;\liste}{type=radio}

\hint{<p>
<b>\name_hint1</b>\spacebeforecolon:
</p>      
<ul>
<li>\name_hint2</li>
<li>\name_hint3</li>
<li>\name_hint3</li>
</ul>
\name_hint5
<p><b>\Exemple</b>\spacebeforecolon:</p>
\name_example1
<div class="wimscenter">\(P_1)\spacebeforecolon: A \name_ou B  &nbsp; ;&nbsp;
\(P_2)\spacebeforecolon: \si A \alors C \name_ou B &nbsp; ;&nbsp;
\(P_3)\spacebeforecolon: \si C \alors \non2 A \name_et B &nbsp; ;&nbsp;
\(P_4)\spacebeforecolon: \si B \alors A \name_et C &nbsp; .&nbsp;
</div>
<p>
\name_example2
</p>
<ol>
<li>\name_example3</li>
<li>\name_example4</li>
</ol>\name_example5
}
