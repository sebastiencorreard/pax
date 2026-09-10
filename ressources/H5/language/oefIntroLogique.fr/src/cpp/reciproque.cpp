target=reciproque

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{init= 10}

usare slib lang/fname?  
\text{elles=Léa,Lili,Julie,Leila,Lola}
\text{luis=Léo,Lulu,Jules,Malik,Luis}
\integer{i=random(1..4)}
\text{Elle=\elles[\i]}
\text{Lui=\luis[\i]}

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

\text{si=\a<4?\si1:\si2}

\text{ass=
\si \A \alors \C,
\si \A \name_ou \si \B \alors \C,
\si \A \name_et \si \B \alors \D,
\si \A \alors \C \name_ou \D,
\si \B \alors \C \name_et \D,
\si \nonA \name_ou \si \B \alors \C,
\si \A et \si \nonB \alors \D,
\si \A \alors \nonC \name_ou \D,
\si \B \alors \C \name_ou \nonD,
\si \A \alors \C \name_et \nonD,
\si \B \alors \nonC \name_et \D
}

\text{contra=
\si \nonC \alors \nonA,
\si \nonC \alors \nonA \name_et \nonB,
\si \nonD \alors \nonA \name_ou \nonB,
\si \nonC \name_et \si \nonD \alors  \nonA,
\si \nonC \name_ou \si \nonD \alors  \nonB,
\si \nonC \alors \A et \nonB,
\si \nonD \alors \nonA \name_ou \B,
\si \C \name_et \si \nonD \alors \nonA,
\si \nonC \name_et \si \D \alors \nonB,
\si \nonC \name_ou \si \D \alors \nonA,
\si \C \name_ou \si \nonD \alors  \nonB
}

\text{rec=
\si \C \alors \A,
\si \C \alors \A \name_ou \B,
\si \D \alors \A \name_et \B,
\si \C \name_ou \si \D \alors \A,
\si \C \name_et \si \D \alors \B,
\si \C \alors \nonA \name_ou \B,
\si \D \alors \A \name_et \nonB,
\si \nonC \name_ou \si \D \alors \A,
\si \C \name_ou \si \nonD \alors \B,
\si \C \name_et \si \nonD \alors \A,
\si \nonC \name_et \si \D \alors \B
}

\integer{rep=random(1..3)}
\integer{i=random(1..11)}

\text{prop1=item(\i,\ass)}

\integer{j=\i-1}
\integer{k=\i+1}
\text{autre=\rep==3 and \j==0?item(2..11,\rec),item(2..11,\contra)}
\text{autre=\rep==3 and \j>0?item(1..\j,\rec),item(\k..11,\contra)}

\text{prop2=\rep==1?item(\i,\rec)}
\text{prop2=\rep==2?item(\i,\contra)}
\text{prop2=\rep==3?randitem(\autre)}

\statement{<div class="wims_question">

<ul><li>\Lui \name_statement1\spacebeforecolon:
<div class="wimscenter">
<span class="fraseB"> \(P_1) : " \prop1 "</span>
</div>
</li>
<li>
\Puis \Elle \name_statement2 \(P_2 )\spacebeforecolon:
<div class="wimscenter">
<span class="fraseA">\(P_2) : " \prop2 "</span>
</div>
</li>
</ul>

<div>\Laproposition \(P_2) \formuleepar \Elle
 \embed{reply1} \delaproposition \(P_1) \enonceepar \Lui.  </div>

</div>
}

\answer{}{\rep;\name_answers}{type=menu}

\hint{
\name_hint "\si \(A) \alors \(B)". \Alors\spacebeforecolon:
<ul>
<li>
\sa <b>\reciproque</b> \estlaproposition "\si \(B) \alors \(A)"\spacebeforecolon;
</li>
<li>
\sa <b>\contraposee</b> \estlaproposition "\si \(non B) \alors \(non A)".
</li>
</ul>
<p>\Laconjonction "\(A) \name_et \(B\;)" \apournegation "\(\non2 A) \name_ou \(\non2 B\;)".</p>
<p>\Ladisjonction "\(A) \name_ou \(B\;)" \apournegation "\(\non2 A) \name_et \(\non2 B\;)".</p>
}
