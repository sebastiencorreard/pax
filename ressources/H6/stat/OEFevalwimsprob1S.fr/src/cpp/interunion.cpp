target=interunion2 interunion3 interunion4 interunion5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{90}

#if (defined TARGET_interunion2 || defined TARGET_interunion3)
#if #TARGET(interunion2)
\text{v=slib(stat/rcomposition 100,4)}
\real{d=\v[4]/100} aetb
#else 
\text{v=slib(stat/rcomposition 100,3)}
\real{d=0}
#endif
\real{aetnb=\v[1]/100}
\real{naetb=\v[2]/100}
\real{naetnb=\v[3]/100}
\real{a=\d+\aetnb}
\real{b=\d+\naetb}
\real{c=\a+\naetb} A ou B
\text{data=\(P(\bar{A}\cup \bar{B})),1-\d
\(P(\bar{A} \cap \bar{B})),\naetnb
\(P(A \cap \bar{B})),\aetnb
\(P(A \cup \bar{B})),\a+\naetnb
\(P(\bar{A} \cap B)),\naetb
\(P(\bar{A} \cup B)),1-\a+\d
\(P(\bar{A})),1-\a
\(P(\bar{B})),1-\b
}
#if defined TARGET_interunion2
\title{Union et intersection d'événements 2}
\text{tintro=\(P(A)=\a) , \(P(B)=\b) et \(P(A \cup B)=\c)}
\text{typeev=}
\text{q=\(P(A \cap B))}
\text{p=\d}
\text{nb=3}
#endif
#if defined TARGET_interunion3
\title{Union et intersection d'événements 3}
\text{typeev=incompatibles}
\text{tintro=\(P(A)=\a) et \(P(B)=\b)}
\text{q=\(P(A\cup B)),\(P(A \cap B))}
\text{p=\c,\d}
\integer{nb=2}
#endif
\text{ind=shuffle(rows(\data)/2)}
\for{i=1 to \nb}
 {
 \text{cedata=row(2*\i+randint(1,0),\data)}
 \text{q=wims(append item \cedata[1] to \q)}
 \text{p=wims(append item \cedata[2] to \p)}
 }
\statement{<p>
Soit \(\Omega\;\) un univers muni d'une probabilité \(P\) et deux événements \typeev \(A\) et \(B\) tels que</p>
<div class="wimscenter">\tintro.</div>
<div class="wims_question"> Calculer :
<ul>
<li><label for="reply1"> \q[1] =</label> \embed{reply1,3}</li>
<li><label for="reply2"> \q[2] =</label> \embed{reply2,3}</li>
<li><label for="reply3"> \q[3] =</label> \embed{reply3,3}</li>
<li><label for="reply4"> \q[4] =</label> \embed{reply4,3}</li>
</ul></div>
}
\answer{\q[1]}{\p[1]}{type=numeric}
\answer{\q[2]}{\p[2]}{type=numeric}
\answer{\q[3]}{\p[3]}{type=numeric}
\answer{\q[4]}{\p[4]}{type=numeric}
\solution{Les calculs reposent sur les propriétés de \(P\) suivantes :
<div class="wimscenter">
si \(C\) et \(D\) sont deux événements alors 
\(P(\bar{D}) = 1 - P(D)\) et \(P(C\cup D) = P(C) + P(D) - P(C\cap D)\).
</div>}
#endif

#if defined TARGET_interunion4
\title{Union et intersection d'événements 4}
\text{v=}
\text{p=}
\text{pt=0}

\for{i=1 to 6}{
  \integer{n=randint(1..10)}
  \text{v=wims(append item \n to \v)}
  \integer{pt=\pt+\n}
}
\for{i=1 to 6}{\text{p=wims(append item \v[\i]/\pt to \p)}}
\rational{rep1=\p[2]+\p[4]+\p[6]}
\rational{rep2=\p[1]+\p[2]+\p[3]}
\rational{rep3=\p[2]+\p[3]+\p[5]}
\rational{rep4=1-\p[5]}
\rational{rep5=\p[2]+\p[3]}
\rational{rep6=1-\rep1}

\statement{<p>
La loi de probabilité ci-dessous décrit le lancer d'un dé truqué,
 dont les faces sont numérotées de 1 à 6.</p>
<table class="wimsborder wimscenter">
<tr><th>Numéro</th><td>1</td><td>2</td><td>3</td><td>4</td><td>5</td><td>6</td></tr>
<tr><th>Probabilité</th><td>\p[1]</td><td>\p[2]</td><td>\p[3]</td><td>\p[4]</td><td>\p[5]</td><td>\p[6]</td></tr>
</table>
<div class="wims_question">
Déterminer la probabilité de chacun des événements suivants :
<ul>
<li>\(A\) <span class="wims_emph">"Le résultat est pair"</span> : <label for="reply1">\(P(A) =\) \embed{reply1,3}</label></li>
<li>\(B\) <span class="wims_emph">"Le résultat est au plus égal à 3"</span> : <label for="reply2">\(P(B) =\) \embed{reply2,3}</label></li>
<li>\(C\) <span class="wims_emph">"le résultat est un nombre premier"</span> : <label for="reply3">\(P(C) =\) \embed{reply3,3}</label></li>
<li>\(D = A \cup B\) : <label for="reply4">\(P(D) = \)</label>\embed{reply4,3}</li>
<li>\(E = B \cap C\) : <label for="reply5">\(P(E) = \)</label>\embed{reply5,3}</li>
<li>\(F = \bar{A}\) : <label for="reply6">\(P(F) =\)</label> \embed{reply6,3}</li>
</ul>
</div>
}
\answer{\(P(A)\)}{\rep1}{type=numexp}{option=noreduction}
\answer{\(P(B)\)}{\rep2}{type=numexp}{option=noreduction}
\answer{\(P(C)\)}{\rep3}{type=numexp}{option=noreduction}
\answer{\(P(A \cup B)\)}{\rep4}{type=numexp}{option=noreduction}
\answer{\(P(B \cap C)\)}{\rep5}{type=numexp}{option=noreduction}
\answer{\(P(\bar{A})\)}{\rep6}{type=numexp}{option=noreduction}

#endif

#if defined TARGET_interunion5
\title{Union et intersection d'événements 5}
\text{p=}
\text{x=0,5,10,100,500}
\text{vp = wims(makelist x for x=1 to 20)}
\text{v=slib(data/random 5, item, \vp)}
\text{pt=slib(stat/sum [\v])}
\text{v=wims(sort reverse numeric list \v)}
\for{i=1 to 5}{\text{p=wims(append item \v[\i]/\pt to \p)}}
\rational{rep1=1-\p[1]}
\rational{rep2=\p[4]+\p[5]}
\rational{rep3=\p[3]+\p[1]+\p[2]}
\rational{rep4=\p[3]+\p[2]}
\integer{e=0}
\for{i=1 to 5}
  {
  \rational{e=\e+\p[\i]*\x[\i]}
  }
\integer{n=randint(max(1,\e-8)..(\e+10))} prix du billet
\integer{n=abs(\n-\e)<0.1?\n+1:\n}
\real{e=\e-\n}
\integer{rep6=\e>0?1:2}
\real{e=round(100*\e)/100}
\statement{<p>
La loi de probabilité ci-dessous décrit le gain possible à une loterie
 sans tenir compte du prix du billet.</p>
<table class="wimsborder wimscenter">
<tr><th>Gain en euros</th><td>0</td><td>5</td><td>10</td><td>100</td><td>500</td></tr>
<tr><th>Probabilité d'obtenir ce gain</th><td>\p[1]</td><td>\p[2]</td><td>\p[3]</td><td>\p[4]</td><td>\p[5]</td></tr>
</table>
<div class="wims_question">
Déterminer la probabilité de chacun des événements suivants :
<ul class="spacer">
<li>\(A\)  <span class="wims_emph">"Le joueur est gagnant"</span> : <label for="reply1">\(P(A) = \)\embed{reply1,3}</label></li>
<li>\(B\)  <span class="wims_emph">"Le joueur a gagné au moins 100 euros"</span> : <label for="reply2">\(P(B) =\)</label> \embed{reply2,3}</li>
<li>\(C\) <span class="wims_emph">"Le joueur a gagné au plus 10 euros"</span> : <label for="reply3">\(P(C) =\)</label> \embed{reply3,3}</li>
<li>\(D = A \cap C\) : \(P(D) =\) <label for="reply4">\embed{reply4,3}</label></li>
</ul>
</div>
L'organisateur du jeu prévoit de fixer le prix du billet à \(\n\) euros.
<div class="wims_question">
 Calculer l'espérance du "gain" en tenant compte du prix du billet.<br>
<label for="reply5">Espérance = </label>\embed{reply5,3} <i> arrondie au centième d'euro.</i>
</div>
<div class="wims_question">
<label for="reply6"> Le jeu sera-t-il favorable au joueur ?</label> \embed{reply6}
</div>
}
\answer{\(P(A)\)}{\rep1}{type=numexp}{option=noreduction}
\answer{\(P(B)\)}{\rep2}{type=numexp}{option=noreduction}
\answer{\(P(C)\)}{\rep3}{type=numexp}{option=noreduction}
\answer{\(P(A \cap C)\)}{\rep4}{type=numexp}{option=noreduction}
\answer{Espérance}{\e}{type=numeric}
\answer{Favorable au joueur}{\rep6;Oui,Non}{type=radio}
#endif
