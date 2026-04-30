target=nature1 nature2 nature3 nature4 nature5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard; Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}

#define TITRE Nature d'un nombre
#if (defined TARGET_nature1 || defined TARGET_nature2 )
# if defined TARGET_nature1
 \title{TITRE I}
 \integer{a=3*randint(17,19,23)}
 \text{data=Le nombre \(3.14) est irrationnel,2
  Le nombre \a est premier,2
  Tout nombre réel est un nombre rationnel,2
  Tout nombre décimal est un nombre rationnel,1
  Tout nombre entier est rationnel,1
  Tout entier naturel est un entier,1
  Aucun nombre décimal n'est irrationnel,1
}
# endif
# if defined TARGET_nature2
 \title{TITRE II}
 \integer{d=7*randint(17,13,23)}
 \integer{a=randint(1..9)}
 \integer{a2=randint(1..9)}
 \integer{b=randint(1..9)}
 \integer{b2=randint(1..9)}
 \integer{b2=\b2=\a2?\b2+1}
 \integer{b2=\b2=10?0}
 \integer{c=randint(1..9)}
 \integer{c2=randint(1..9)}
 \integer{option1=\b2\c2=99?2:1}
 \integer{option2=3-\option1}
 \text{data=wims(embraced randrow {\a2.\b2\c2<u>\b2\c2</u> n'est pas décimal,\option1;\a2.\b2\c2<u>\b2\c2</u> est décimal,\option2})
  \a.\b\c est décimal,1
  Le nombre \d n'est pas premier,1
  Tout nombre réel est nombre décimal,2
  Tout entier naturel est un nombre décimal,1
  Tout nombre rationnel est un nombre décimal,2
  Le nombre 0 n'est pas décimal,2
}
\text{aide=Le bloc de chiffres souligné se répète à l'infini.}

# endif
\text{lstind=shuffle(5)}
\integer{i3=\lstind[1]+2}
\integer{i4=\lstind[2]+2}
\text{lstind=1,2,\i3,\i4}
\text{lstind=shuffle(\lstind)}
\text{data1=row(\lstind[1],\data)}
\text{data2=row(\lstind[2],\data)}
\text{data3=row(\lstind[3],\data)}
\text{data4=row(\lstind[4],\data)}
#endif
#if defined TARGET_nature3
 \title{TITRE III}
 \integer{a=randint(2,3,5,6,7,8)}
 \integer{b=random(3,6,7,9,12,14,15)}
 \text{data=Le nombre \(\sqrt{\a}) est irrationnel,1
  Tous les nombres \(\sqrt{a})&#44; a étant un entier naturel&#44; sont irrationnels,2
  L'inverse de \(\b) n'est pas décimal,1
  Le nombre \(pi) est irrationnel,1
  Tous les inverses des nombres entiers sont des nombres décimaux,2
  Aucun inverse de rationnal n'est un entier,2
}
\text{lstind=shuffle(3)}
\integer{i4=\lstind[2]+3}
\text{lstind=1,2,3,\i4}
\text{lstind=shuffle(\lstind)}
\text{data1=row(\lstind[1],\data)}
\text{data2=row(\lstind[2],\data)}
\text{data3=row(\lstind[3],\data)}
\text{data4=row(\lstind[4],\data)}
#endif
#if defined TARGET_nature4
 \title{TITRE IV}
\integer{a=random(1..3)}
\integer{p=random(2..8)}
\integer{q=random(2,4,5,7,8)}
\text{lstfrac=}

\text{f=\(\frac{\p}{9}\times 2^\a)}
\text{lstfrac=wims(append item \f to \lstfrac)}

\text{f=\(\p \times \frac{3}{3}\times 5^\a)}
\text{lstfrac=wims(append item \f to \lstfrac)}

\text{f=\(\frac{\p^2}{7}\times 2^\a)}
\text{lstfrac=wims(append item \f to \lstfrac)}

\text{f=\(\frac{\q}{3}\times 10^\a)}
\text{lstfrac=wims(append item \f to \lstfrac)}

\text{f=\(\frac{\p}{2^\a}\times 5^\a)}
\text{lstfrac=wims(append item \f to \lstfrac)}

\text{goodrep=1,3,4}
#endif
#if defined TARGET_nature5
 \title{TITRE V}
 \integer{a=randint(3..15)}
 \integer{b=\a-1}
 \text{data=\((\sqrt{\a}+\sqrt{\b})(\sqrt{\a}-\sqrt{\b})) est irrationnel,2,\((\sqrt{\a}+\sqrt{\b})(\sqrt{\a}-\sqrt{\b})=\a - \b)
  Le produit de deux nombres décimaux est un nombre décimal,1,\((a \times 10^p)\times (b \times 10^q)=ab \times 10^{p+q})
  La somme de deux nombres décimaux est un nombre décimal,1
  Le produit de deux nombres rationnels non décimaux n'est jamais un nombre décimal,2, contre exemple \(\frac{3}{7} \times \frac{7}{3}=1)
  La somme de deux nombres rationnels positifs non décimaux n'est jamais un nombre décimal,2, contre exemple \(\frac{1}{3}+\frac{2}{3}=1)
  Le carré d'un nombre qui n'est pas décimal&#44; n'est pas non plus décimal,2, contre exemple \(\sqrt{2}),
  Le carré d'un nombre rationnel qui n'est pas décimal&#44; n'est pas non plus décimal,1

}
\text{lstind=shuffle(6)}
\integer{i2=\lstind[1]+1}
\integer{i3=\lstind[2]+1}
\integer{i4=\lstind[3]+1}
\text{lstind=1,\i2,\i3,\i4}
\text{lstind=shuffle(\lstind)}
\text{data1=row(\lstind[1],\data)}
\text{data2=row(\lstind[2],\data)}
\text{data3=row(\lstind[3],\data)}
\text{data4=row(\lstind[4],\data)}
\text{feedtxt=}
\text{feedn=items(\data1)}
\if{\feedn=3}{
 \text{feedtxt=wims(append item \data1[1]:\data1[3]<br> to \feedtxt)}
 }
\text{feedn=items(\data2)}
\if{\feedn=3}{
 \text{feedtxt=wims(append item \data2[1]:\data2[3]<br> to \feedtxt)}
 }
\text{feedn=items(\data3)}
\if{\feedn=3}{
 \text{feedtxt=wims(append item \data3[1]:\data3[3]<br> to \feedtxt)}
 }
\text{feedn=items(\data4)}
\if{\feedn=3}{
 \text{feedtxt=wims(append item \data4[1]:\data4[3]<br> to \feedtxt)}
 }
#endif
#if defined TARGET_nature4
\statement{
  Parmi les fractions suivantes, lesquelles ne représentent pas un nombre décimal?
<div class="wimscenter">
\embed{reply1}
</div>
}
\answer{}{\goodrep;\lstfrac}{type=checkbox}{option=shuffle}
#else
\text{lstrep=Vrai,Faux}

\statement{
 Cocher les bonnes réponses:
<ol>
<li>\data1[1]:\embed{reply1}</li>
<li>\data2[1]:\embed{reply2}</li>
<li>\data3[1]:\embed{reply3}</li>
<li>\data4[1]:\embed{reply4}</li>
</ol>
# if defined TARGET_nature2
<div class="wims_instruction">
\aide
</div>
# endif
}
\answer{\data1[1]}{\data1[2];\lstrep}{type=radio}
\answer{\data2[1]}{\data2[2];\lstrep}{type=radio}
\answer{\data3[1]}{\data3[2];\lstrep}{type=radio}
\answer{\data4[1]}{\data4[2];\lstrep}{type=radio}
#endif
#if defined TARGET_nature5
\feedback{1=1}{\feedtxt}
#endif
