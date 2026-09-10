target=implication

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\language{fr}
\range{-10..10}
\text{monaide=wims(record 12  of \glossaire)}
\help{\monaide}

\steps{reply1
reply2}

\text{si=randitem(\Si2,\Quand,\Chaque)}
\text{alors=randitem(&#32;\alors,&#44;)}

\for{i = 1 to 8 }{
\text{Ai = item(\i,\prem)}
\text{Bi = item(\i,\conc)}
\if{\i=1}{\text{rules=\si \Ai\alors \Bi}}{\text{rules=\rules, \si \Ai\alors \Bi}}
}

\integer{n=randint(1..8)}
\integer{n2=(\n==8)?1:\n+1}
\text{rule=item(\n,\rules)}
\text{rule2=item(\n2,\rules)}
\text{A=item(\n,\prem)}
\text{B=item(\n,\conc)}
\text{C=item(\n2,\conc)}
\text{nonA=item(\n,\nonPr)}
\text{nonB=item(\n,\nonCo)}
\text{nonC=item(\n2,\nonCo)}
\text{sujA=item(\n,\sujPr)}
\text{sujB=item(\n,\sujCo)}
\text{sujC=item(\n2,\sujCo)}

\integer{q=randint(1..4)}

!!!! les questions réponses à l'étape 1
\matrix{qcm1=(\q==1)?
\A
1
\B,\nonB,\none}

\matrix{qcm1=\q==2?
\nonA
3
\B,\nonB,\none}

\matrix{qcm1=\q==3?
\B
3
\A,\nonA,\none}

\matrix{qcm1=\q==4?
\nonB
2
\A,\nonA,\none}

\text{query1=row(1, \qcm1)}
\text{rep1=row(2, \qcm1)}
\text{liste1=row(3,\qcm1)}

!!!! les questions réponses à l'étape 2


\integer{q=randint(1..4)}
\matrix{qcm2=\q==1?
\A
1,3
\B,\nonB,\C,\nonC,\none}

\matrix{qcm2=\q==2?
\nonA
5
\B,\nonB,\C,\nonC,\none}



\matrix{qcm2=\q==3?
\B
3
\A,\nonA,\C,\nonC,\none}


\matrix{qcm2=\q==4?
\nonB
2
\A,\nonA,\C,\nonC,\none}


\matrix{qcm2=\q==5?
\C
5
\A,\nonA,\B,\nonB,\none}


\matrix{qcm2=\q==6?
\nonC
3,4
\A,\nonA,\B,\nonB,\none}


\text{query2=row(1, \qcm2)}
\text{rep2=row(2, \qcm2)}
\text{liste2=row(3,\qcm2)}

\statement{
<div class="citation">\name_citation</div>

<div class="wims_question">

\if{\step=1}{
<p><b>\Question \step.</b> <br/>\name_characters \sujA \name_et \sujB.
\name_statement1a
</p>
<div class="wimscenter"><span class="fraseB"> \rule </span></div>
<p>\name_statement2 \query1\spacebeforecolon?</p>
<div class="wimscenter"> \embed{reply1} </div>
}

\if{\step=2}{
<p><b>\Question \step.</b> <br/>\name_characters \sujA, \sujB \name_et \sujC.
\name_statement1b
</p>
<ul>
<li> <span class="fraseB">\rule</span> </li>
<li> <span class="fraseB">\rule2</span> </li>
</ul>
<p>\name_statement2 \query2\spacebeforecolon?</p>
<div class="wimscenter"> \embed{reply2} </div>
}

</div>
}

\answer{\Question 1}{\rep1 ; \liste1}{type=radio}
\answer{\Question 2}{\rep2 ; \liste2}{type=checkbox}
