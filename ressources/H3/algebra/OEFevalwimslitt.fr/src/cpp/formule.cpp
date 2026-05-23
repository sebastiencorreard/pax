target=formule1 formule2 formule3 formule4 formule5
#include "author.inc"
#if defined TARGET_formule1
# define NUM 1
#endif
#if defined TARGET_formule2
# define NUM 2
#endif
#if defined TARGET_formule3
# define NUM 3
#endif
#if defined TARGET_formule4
# define NUM 4
#endif
#if defined TARGET_formule5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_formule1
\integer{age=randint(12..16)}
\text{x=randitem(X,Y,Z,N)}
\text{alea=randint(1..2)}
\if{\alea=1}{
  \text{name=slib(lang/fname fr,boy)}
  \text{name_pronom=il}
}{
  \text{name=slib(lang/fname fr,girl)}
  \text{name_pronom=elle}
}
\text{name_question=a \age ans. Quel âge aura-t-\name_pronom dans \(\x\) ans&nbsp;}
\statement{\name \name_question?}
\answer{\name_answer}{\x+\age,\age+\x}{type=litexp}
#endif
#if defined TARGET_formule2
\text{l=shuffle(A,B,C,D,E)}
\integer{v=randint(9..15)}
\text{x=randitem(x,y,a,b,u,v)}
\text{image=draw(200,100
range 0,20,0,10
polygon black,2,2,14,2,19,2,14,8,2,8
text black,2,1.9,medium,\l[4]
text black,14,1.9,medium,\l[3]
text black,19,1.9,medium,\l[5]
text black,14,9.3,medium,\l[2]
text black,2,9.3,medium,\l[1]
dsegment 14,2,14,8,black)}
\text{unit=randitem(cm,m,dm,dam)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
  Sur la figure, \(\l[1]\l[2]\l[3]\l[4]) est un rectangle et \(\l[2]\l[3]\l[5])
  un triangle rectangle isocèle en \l[3].<br>
  On sait que \l[4]\l[5] = \v \unit et on pose \(\l[1]\l[4]\) = \(\x\) \unit.<p>
  Exprimer la mesure de l'aire de la surface \(\l[1]\l[2]\l[5]\l[4]) en fonction de \(\x\).
</p>
<div>
<b>\name_answer\name_insec:</b>
<label for="reply1">
La mesure de l'aire de \(\l[1]\l[2]\l[5]\l[4]) est de </label>
\embed{r1,15} \(\unit^2\).
</div>
</div></div>}
\answer{\name_answer}{\x*(\v-\x)+\x^2/2}{type=auto}
#endif
#if defined TARGET_formule3
\text{list=wims(values v for v=2 to 9)}
\text{list=shuffle(\list)}
\integer{n=\list[1]}
\integer{n2=\list[2]}
\text{x=randitem(x,y,y,t,u,v,a,b)}
\integer{ch=randint(1,2)}
\text{opename=\ch=1?somme:différence}
\text{ope=\ch=1?+:-}

\matrix{donnees=La \opename de \n et de \(\x\),\(\n\ope \x \)
Le produit de \n par \(\x\),\(\n\times \x\)
La \opename de \n2 et du produit de \(\x\) par \n,\(\n2\ope \x\times \n\)
Le produit de \n2 par la \opename de \n et de \(\x\),\(\n2\times (\n\ope\x)\)}

\text{col1=column(1,\donnees)}
\text{col2=column(2,\donnees)}

\statement{
\name_question
<div class="wimscenter">
\embed{r1,100x200x200}
</div>}
\answer{\name_answer}{\col1;\col2}{type=correspond}
#endif
#if defined TARGET_formule4
\text{l=shuffle(A,B,C,D,E,F,G,H,I,J)}
\integer{v2=randint(2..8)}
\integer{v1=randint(12..18)}
\text{x=randitem(x,y,b,u,v)}

\text{image=draw(200,200
range 0,20,0,20
polygon black,6,2,14,2,14,14,18,14,18,18,2,18,2,14,6,14
text black,2,19.3,medium,\l[1]
text black,6,19.3,medium,\l[2]
text black,14,19.3,medium,\l[3]
text black,18,19.3,medium,\l[4]
text black,18.1,13.9,medium,\l[5]
text black,14.3,13.9,medium,\l[6]
text black,14,1.9,medium,\l[7]
text black,6,1.9,medium,\l[8]
text black,4.8,13.9,medium,\l[9]
text black,2,13.9,medium,\l[10]
dsegment 6,14,6,18,black
dsegment 14,14,14,18,black)}
\text{unit=randitem(cm,m,dm,dam)}
\integer{a=2*(\v1+\v2)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
Sur la figure, \(\l[2]\l[3]\l[7]\l[8]\) est un rectangle.
\(\l[1]\l[2]\l[9]\l[10]) et  \(\l[3]\l[4]\l[5]\l[6]\) sont deux carrés.
<br>
On sait que \(\l[2]\l[8] = \v1 \unit) et \(\l[8]\l[7] = \v2 \unit\).<br>
On note \(\x\) la mesure (en \unit) de la longueur des côtés des carrés \(\l[1]\l[2]\l[9]\l[10]\)
et \(\l[3]\l[4]\l[5]\l[6]\).<br>
Exprimer la mesure du périmètre de la figure en fonction de \(\x\).
<div>
<b>\name_answer\name_insec:</b>
<label for="reply1">La mesure du périmètre de la figure est de</label> \embed{r1,7} \unit.
</div>
</div>
</div>
}
\answer{\name_answer}{4*\x+\a,\a+4*\x}{type=auto}
#endif
#if defined TARGET_formule5
\matrix{name_pronom=lui,il
lui,elle}
\text{alea=randint(1..2)}
\if{\alea=2}{
  \text{name=slib(lang/fname fr,girl)}
}
{
\text{name=slib(lang/fname fr,boy)}
}
\integer{abo=randint(12..25)}
\integer{film=randint(3..6)}
\text{x=randitem(X,Y,Z,N)}

\statement{\name a acheté un abonnement au cinéma près de chez \name_pronom[\alea;1].
  Cet abonnement \name_pronom[\alea;1] a coûté \abo euros.
  Maintenant pour chaque film qu'\name_pronom[\alea;2] va voir, \name_pronom[\alea;2] paye \film euros.
  <p>
  Écrire en fonction de \(\x\) combien \name_pronom[\alea;2] dépensera pour aller
  voir \(\x\) films.
  </p>
  <div class="spacer">
  <label for="reply1">\name_answer\name_insec:</label> \embed{r1,7} euros.
  </div>}
\answer{\name_answer}{\abo+\film*\x}{type=auto}
#endif
