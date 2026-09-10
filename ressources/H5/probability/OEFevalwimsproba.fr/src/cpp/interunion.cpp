target=interunion2 interunion0 interunion3 interunion4 interunion5
#if defined TARGET_interunion0
\author{Bruno, Mifsud}
\email{communaute.mutuwims@laposte.net}
#else
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
#endif
\format{html}
#if defined TARGET_interunion2
# define NUM 2
#endif
#if defined TARGET_interunion0
# define NUM 0
#endif
#if defined TARGET_interunion3
# define NUM 3
#endif
#if defined TARGET_interunion4
# define NUM 4
#endif
#if defined TARGET_interunion5
# define NUM 5
#endif
#include "lang_titles.inc"
#if (defined TARGET_interunion0 || defined TARGET_interunion2 || defined TARGET_interunion3 )
\real{a=randint(20..80)/100}
\real{ab=1-\a}
# if defined TARGET_interunion2 || defined TARGET_interunion0
\real{b=randint(20..80)/100}
\real{d=\a>\b?randint(0..\b*100)/100:randint(0..\a*100)/100}
# else
\real{b=randint(10..100*\ab-10)/100}
\real{d=0}
# endif
\real{c=\a+\b-\d}
\if{\c>1}{
  \real{c=1}
  \real{d=\a+\b-\c}
  \real{d=abs(\d)<0.001?0}
}
#if defined TARGET_interunion0
\text{data=\(P(A)\),\a
\(P(B)\),\b
\(P(A \cup B)\),\c
\(P(A \cap B)\),\d
}
#else
\text{data=\(P(\bar{A}\cup \bar{B})),1-\d
\(P(\bar{A} \cap \bar{B})),1-\c
\(P(A \cap \bar{B})),\a-\d
\(P(A \cup \bar{B})),1-\b+\d
\(P(\bar{A} \cap B)),\b-\d
\(P(\bar{A} \cup B)),1-\a+\d
\(P(\bar{A})),1-\a
\(P(\bar{B})),1-\b
}
#endif
#if defined TARGET_interunion2
\text{tintro=\(P(A)=\a\) , \(P(B)=\b\) et \(P(A \cup B)=\c\)}
\text{typeev=}
\text{q=\(P(A \cap B)\)}
\text{p=\d}
\text{nb=3}
#endif
#if defined TARGET_interunion0
\text{typeev=}
\text{ind=shuffle(4)}
\text{cedata=row(\ind[1],\data)}
 \real{val=\cedata[2]}
 \text{q=\cedata[1]}
 \text{p=\cedata[2]}
\for{i=2 to 4}{
  \text{cedata=row(\ind[\i],\data)}
  \real{val=\cedata[2]}
  \text{q=wims(append item \cedata[1] to \q)}
  \text{p=wims(append item \val to \p)}}
  \text{tintro=\q[4]\(=\p[4]\), \q[2]\(=\p[2]\) et \q[3]\(=\p[3]\)}
#endif
#if defined TARGET_interunion3
\text{typeev=incompatibles}
\text{tintro=\(P(A)=\a\) et \(P(B)=\b\)}
\text{q=\(P(A\cup B)\),\(P(A \cap B)\)}
\text{p=\c,\d}
\integer{nb=2}
#endif
\text{ind=shuffle(rows(\data)/2)}
\for{i=1 to \nb}{
 \text{cedata=row(2*\i+randint(1,0),\data)}
 \real{val=\cedata[2]}
 \text{q=wims(append item \cedata[1] to \q)}
 \text{p=wims(append item \val to \p)}
 }
\statement{<p>
Soit \({\Omega}\) un univers et deux événements \typeev \(A\) et \(B\) tels que
</p>
<div class="wimscenter">\tintro.</div>
<div class="wims_question">
Calculer :
<ul>
<li><label for="reply1">\q[1]</label>=\embed{reply1,3}</li>
#if (defined TARGET_interunion2 || defined TARGET_interunion3)
<li><label for="reply2">\q[2]</label>=\embed{reply2,3}</li>
<li><label for="reply3">\q[3]</label>=\embed{reply3,3}</li>
<li><label for="reply4">\q[4]</label>=\embed{reply4,3}</li>
#endif
</ul>
</div>
}
\answer{\q[1]}{\p[1]}{type=numexp}
#if (defined TARGET_interunion2 || defined TARGET_interunion3)
\answer{\q[2]}{\p[2]}{type=numexp}
\answer{\q[3]}{\p[3]}{type=numexp}
\answer{\q[4]}{\p[4]}{type=numexp}
#endif
#if defined TARGET_interunion0
\solution{<p>On sait que : \(P(A)+P(B)=P(A \cup B)+P(A \cap B)\)</p>
<p>Or : \tintro.</p>
<p>Il suffit alors de remplacer dans la formule les valeurs données dans l'énoncé pour obtenir le résultat.</p>
<p> \q[1] \(\ =   \p[1]\)</p>
}
#endif
#endif

#if defined TARGET_interunion4
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
 dont les faces sont numérotées de 1 à 6.
</p>
<table class="wimscenter wimsborder">
<tr><th>\(X_i)</th><td>1</td><td>2</td><td>3</td><td>4</td><td>5</td><td>6</td></tr>
<tr><th>\(P_i)</th><td>\p[1]</td><td>\p[2]</td><td>\p[3]</td><td>\p[4]</td><td>\p[5]</td><td>\p[6]</td></tr>
</table>
<div class="wims_question">
  Déterminer la probabilité de chacun des événements suivants.
<ul>
<li>\(A\) « Le résultat est pair » : <label for="reply1">\(P(A)=\)</label>\embed{reply1,3}</li>
<li>\(B\) « Le résultat est au plus égal à 3 » : <label for="reply2">\(P(B)= \)</label>\embed{reply2,3}</li>
<li>\(C\) « le résultat est un nombre premier » : <label for="reply3">\(P(C)=\)</label>\embed{reply3,3}</li>
<li>\(D= A \cup B\) : <label for="reply4">\(P(D)=\)</label>\embed{reply4,3}</li>
<li>\(E = B \cap C\) : <label for="reply5">\(P(E)=\)</label>\embed{reply5,3}</li>
<li>\(F =\bar{A}\) : <label for="reply6">\(P(F)=\)</label>\embed{reply6,3}</li>
</ul></div>
}
\answer{Le résultat est pair}{\rep1}{type=numexp}{option=noreduction}
\answer{Le résultat est au plus égal à 3}{\rep2}{type=numexp}{option=noreduction}
\answer{Le résultat est un nombre premier}{\rep3}{type=numexp}{option=noreduction}
\answer{\(A \cup B\)}{\rep4}{type=numexp}{option=noreduction}
\answer{\(B \cap C\)}{\rep5}{type=numexp}{option=noreduction}
\answer{\(\bar{A}\)}{\rep6}{type=numexp}{option=noreduction}
#endif
#if defined TARGET_interunion5
\text{v=}
\text{p=}
\text{pt=0}
\text{x=0,5,10,100,500}
\for{i=1 to 5}{
   \integer{n=randint(1..10)}
   \text{v=wims(append item \n to \v)}
   \integer{pt=\pt+\n}
}
\text{v=wims(sort reverse list \v)}
\for{i=1 to 5}{\text{p=wims(append item \v[\i]/\pt to \p)}}
\rational{rep1=1-\p[1]}
\rational{rep2=\p[4]+\p[5]}
\rational{rep3=\p[3]+\p[1]+\p[2]}
\rational{rep4=\p[3]+\p[2]}
\integer{n=randint(4..15)*2}
\integer{e=0}
\for{i=1 to 5}
 {
 \rational{e=\e+\p[\i]*(\x[\i]-\n)}
 }
\integer{rep6=\e>0?1:2}
\statement{<p>
La loi de probabilité ci-dessous décrit le gain possible à une loterie
 sans tenir compte du prix du billet.</p>
<table class="wimscenter wimsborder">
<tr><th>Gain en euros</th><td>0</td><td>5</td><td>10</td><td>100</td><td>500</td></tr>
<tr><th>\(P_i\)</th><td>\p[1]</td><td>\p[2]</td><td>\p[3]</td><td>\p[4]</td><td>\p[5]</td></tr>
</table>
<div class="wims_question">
  Déterminer la probabilité de chacun des événements suivants :
<ul>
<li>\(A\) « Le joueur est gagnant » : <label for="reply1">\(P(A)=\)</label>\embed{reply1,3}</li>
<li>\(B\) « Le joueur a gagné au moins 100 euros » : <label for="reply2">\(P(B)=\)</label>\embed{reply2,3}</li>
<li>\(C\) « Le joueur a gagné au plus 10 euros » : <label for="reply3">\(P(C)=\)</label>\embed{reply3,3}</li>
<li>\(D = A \cap C\) : <label for="reply4">\(P(D)=\)</label>\embed{reply4,3}</li>
</ul></div>
}
\answer{Le joueur est gagnant}{\rep1}{type=numexp}{option=noreduction}
\answer{Le joueur a gagné au moins 100 euros}{\rep2}{type=numexp}{option=noreduction}
\answer{Le joueur a gagné au plus 10 euros}{\rep3}{type=numexp}{option=noreduction}
\answer{\(A \cap C)}{\rep4}{type=numexp}{option=noreduction}
#endif
