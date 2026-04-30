target=miseeneq1 miseeneq2 miseeneq3 miseeneq4 miseeneq5
#include "author.inc"
\keywords{pbsolving,linear_system}
#define TITRE Mise en équation
\text{eleve=random(Kevin,Alexandra,Laura,Pierre,Jemina)}
\text{tconsigne=}
#if defined TARGET_miseeneq1
\title{TITRE I}
\integer{k=randint(1,2)}
\if{\k=1}
 {
 \integer{x=random(200..500)}
 \integer{y=\x+random(10..100)}
 \integer{a=\x+\y}
 \integer{b=\y-\x}
 \integer{c1=\a}
 \integer{a1=1}
 \integer{b1=1}
 \integer{c2=\b}
 \integer{a2=-1}
 \integer{b2=1}
 \text{tintro= Trouver deux entiers dont la somme vaut \a et la différence vaut \b.}
 }
 {
 \integer{a=random(2..5)}
 \text{ta=double,triple,quadruple,quintuple}
 \integer{x=random(10..50)}
 \integer{y=\a*\x}
 \integer{s=\x+\y}
 \integer{c1=0}
 \integer{a1=\a}
 \integer{b1=-1}
 \integer{c2=\s}
 \integer{a2=1}
 \integer{b2=1}

 \text{tintro= Trouver deux entiers dont la somme vaut \s et tels que le second soit le \ta[\a-1] de l'autre.}
 }
\text{tx=Premier nombre}
\text{ty=Deuxième nombre}
\text{tconsigne=<div class="wims_instruction">Le premier nombre est le plus petit des deux.</div>
}
#endif

#if defined TARGET_miseeneq2
\title{TITRE II}
\integer{k=random(1,2)}
\integer{x=random(200..500)}
\integer{a=random(100..200)}
\integer{y=\a+\x}
\integer{p=2*(\x+\y)}
\if{\k=1}
  {
  \integer{b=random(5..15)}
  \integer{c=\b+random(5..30)}
  \integer{d=\b*\x+\c*\y+\b*\c}
  \text{tintro=Le périmètre d'un rectangle est de \p m.<p>
  Si l'on augmente l'une de ses dimensions de \b m et l'autre de \c m, son aire augmente de \d m2.
</p><p>Calculer ses dimensions, sachant que la longueur est supérieure à la largeur. </p>}
 \integer{c1=\p}
 \integer{a1=2}
 \integer{b1=2}
 \integer{c2=\d-\b*\c}
 \integer{a2=\b}
 \integer{b2=\c}
  }
\if{\k=2}
  {
\text{tintro=Un paysan laboure un champ dont le périmètre est \p m.
  La largeur du champ mesure \a metres de moins que la longueur.<p>
 Quelles sont les dimensions de ce champ,
 sachant que la longueur est supérieure à la largeur&#63;</p> }
 \integer{c1=\p}
 \integer{a1=2}
 \integer{b1=2}
 \integer{c2=\a}
 \integer{a2=-1}
 \integer{b2=1}

  }
\text{tx=largeur}
\text{ty=longueur}

#endif


#if defined TARGET_miseeneq3
\title{TITRE III}
\integer{n=random(10..15)}
\integer{a=random(2..9)}
\integer{c=random(2..9)}
\integer{c=\a=\c?\c+1}
\integer{b=\n-\a}
\integer{d=\n-\c}
\integer{x=random(10..50)}
\real{x=\x/10}
\integer{y=random(10..50)}
\real{y=\y/10}
\real{t1=\a*\x+\b*\y}
\real{t2=\c*\x+\d*\y}
\text{tx=prix d'un soda}
\text{ty=prix d'un café}
 \real{c1=\t1}
 \integer{a1=\a}
 \integer{b1=\b}
 \real{c2=\t2}
 \integer{a2=\c}
 \integer{b2=\d}

\text{tintro=Des amis se réunissent dans un bar.
 Lors de leur première commande qui se compose de
 \a sodas et de \b cafés, ils paient \t1 Euros.
  La deuxième tournée se compose de \c sodas et \d cafés et s'élève à
\t2 Euros.<p>
  Quel est le prix d'un soda et celui d'un café &#63;</p>}
#endif


#if defined TARGET_miseeneq4
\title{TITRE IV}
\integer{k=randint(1..3)}

\if{\k=1}
 {
 \integer{b=random(4..10)}
 \integer{c=random(4..10)}
 \integer{min=1+(\b-\c)/2}
 \integer{min=\min<4?4}
 \integer{y1=random(\min..10)}
 \integer{x1=3*\y1}
 \integer{x=\x1+\b}
 \integer{y=\y1+\c}
 \integer{a=\x-\y}
\text{tintro=Des élèves d'un lycée organisent une fête.<p>
 Au début de la soirée, il a \a filles de plus que de garçons.
  A 22h, après le départ de \b filles et de \c garçons, le nombre de filles est le triple de celui des garçons.
  </p>
  Trouver le nombre de filles et de garçons présents au début de la soirée.}
 \integer{c1=\a}
 \integer{a1=1}
 \integer{b1=-1}
 \integer{c2=\b-3*\c}
 \integer{a2=1}
 \integer{b2=-3}

 \text{tx=Nombre de filles}
 \text{ty=Nombre de garçons}
 }
\if{\k=2}
 {
 \integer{x=random(5..15)}
 \integer{a=random(3..8)}
 \integer{a1=\a+1}
 \integer{b=random(0..\a-1)}
 \integer{y=\x*\a+\b}
 \integer{c=\x-\b}
\text{tintro=Plusieurs copains se partagent un paquet de bonbons.
<p>
  Quand chacun en prend \a, il en reste \b.
  Et si chacun en prend \a1, il en manque \c.</p><p>
  Déterminer le nombre de copains et le nombre de bonbons dans le paquet.</p>}
 \integer{c2=-\c}
 \integer{a2=-\a1}
 \integer{b2=1}
 \integer{c1=\b}
 \integer{a1=-\a}
 \integer{b1=1}

 \text{tx=Nombre de copains}
 \text{ty=Nombre de bonbons}
 }
\if{\k=3}
 {
\integer{x=random(5..10)}
\integer{y=2*\x}
\integer{a=random(2..\x)}
\integer{b=2*(\y-\a)-\x}
\text{tintro=Dans une classe, il y a deux fois plus de garçons que de filles.
\a garçons quittent la salle et \b filles arrivent :
 il y a alors deux fois plus de filles que de garçons.<p>
  Combien y avait-il de filles et de garçons au début &#63;</p>}
 \text{tx=Nombre de filles}
 \text{ty=Nombre de garçons}
 \integer{c1=0}
 \integer{a1=2}
 \integer{b1=-1}
 \integer{c2=\b+2*\a}
 \integer{a2=-1}
 \integer{b2=2}

 }

#endif

#if defined TARGET_miseeneq5
\title{TITRE V}
\integer{a=random(100..300)}
\integer{b=random(100..300)}
\integer{x=random(400..600)}
\integer{y=\x-\a}
\integer{z=\x+\b}
\integer{s=\x+\y+\z}
\text{tx=Montant touché par la première personne}
\text{ty=Montant touché par la deuxième personne}
\text{tintro=Il y a \s Euros à partager entre trois personnes.<br>
 La première touche \a Euros de plus que la deuxième, mais \b de moins que la troisième.<br>
<p> Combien vont toucher la première personne et la deuxième personne&#63;</p>}
#endif

\text{tsol1=texmath(\a1*x+\b1*y)}
\text{tsol2=texmath(\a2*x+\b2*y)}
\statement{<div>
\tintro
</div>
\tconsigne
#if (defined TARGET_miseeneq1 || defined TARGET_miseeneq2 || defined TARGET_miseeneq3 || defined TARGET_miseeneq4 )
  Pour résoudre ce problème, \eleve a posé :<br>
  Soit \(x) : \tx et \(y) : \ty.<br>
  Puis \eleve a traduit le problème par le système :
<div class="wimscenter">
\( \left \lbrace \begin{array}{rcll} a x + b y&=&c & (1)\\ a' x + b' y&=&c' & (2)\end{array}\right .)
</div>
  Déterminer les coefficients numériques de ce système.
<table>
<tr><td>\(a\) = \embed{reply3,4}</td><td>\(b\) = \embed{reply4,4}</td><td>\(c\) = \embed{reply5,4}</td></tr>
<tr><td>\(a'\) = \embed{reply6,4}</td><td>\(b'\) = \embed{reply7,4}</td><td>\(c'\) = \embed{reply8,4}</td></tr>
</table>
<p> Puis résoudre ce système.</p>
#endif
<table>
<tr><td>\tx : </td><td>\embed{reply1,5}</td></tr>
<tr><td>\ty : </td><td>\embed{reply2,5}</td></tr>
</table>
}

\answer{\tx}{\x}{type=numeric}
\answer{\ty}{\y}{type=numeric}
#if (defined TARGET_miseeneq1 || defined TARGET_miseeneq2 || defined TARGET_miseeneq3 || defined TARGET_miseeneq4 )
\answer{\(a\)}{\ra}{type=numeric}
\answer{\(b\)}{\rb}{type=numeric}
\answer{\(c\)}{\rc}{type=numeric}
\answer{\(a'\)}{\ra2}{type=numeric}
\answer{\(b'\)}{\rb2}{type=numeric}
\answer{\(c'\)}{\rc2}{type=numeric}
\integer{mc=\ra*\x+\rb*\y}
\integer{mc2=\ra2*\x+\rb2*\y}
\condition{\ra*\x+\rb*\y=\rc and \ra2*\x+\rb2*\y=\rc2 and (\ra<>0 or \rb<>0 or \rc<>0) and (\ra2<>0 or \rb2<>0 or \rc2<>0)}
\solution{Le problème peut se traduire par le système :
<div class="wimscenter">\( \left \lbrace \begin{array}{rcll} \tsol1&=&\c1 & (1)\\ \tsol2&=&\c2 & (2)\end{array}\right .)
</div>

}
#endif
