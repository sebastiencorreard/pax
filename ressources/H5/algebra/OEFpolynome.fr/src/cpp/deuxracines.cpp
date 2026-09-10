target=sumprdt diffprdt invprdt
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{10000}

#if defined TARGET_sumprdt
\integer{a=1}
#endif
#if defined TARGET_diffprdt
\integer{a=2}
#endif
#if defined TARGET_invprdt
\integer{a=3}
#endif
\integer{u=random(-1,1)*randint(1..8)}
\integer{v=random(-1,1)*randint(1..8)}
\integer{v=\v/3=\u/2?\v+1:\v}
\rational{s=\u/2+\v/3}
\rational{x1=\u/2<\v/3?\u/2:\v/3}
\rational{x2=\u/2<\v/3?\v/3:\u/2}
\rational{diff=\x2-\x1}
\rational{y1=-\x1}
\rational{i=2/\u+3/\v}
\rational{p=\u*\v/6}
\rational{mp=-\u*\v/6}
\rational{d=(\s)^2-4*\p}
\text{ts=texmath(\s)}
\text{tp=texmath(\p)}
\text{tmp=texmath(\mp)}
\text{tdiff=texmath(\diff)}
\text{ti=texmath(\i)}
#if defined TARGET_sumprdt
\title{Somme et produit}
\text{intro=la somme vaut \(\ts) et le produit \(\tp)}
\text{equat=texmath(x^2-\s*x+\p=0)}
\text{tsol=\(x_1) et \(x_2) sont solutions de l'équation du second degré:
<div class="wimscenter">\(\equat).</div>
Le discriminant de ce polynôme est égal à \(\d), ses racines sont \(x_1=\x1) et \(x_2=\x2).</p>}
#endif
#if defined TARGET_diffprdt
\title{Différence et produit}
\text{intro=la différence vaut \(\tdiff) et le produit vaut \(\tp)}
\text{equat=texmath(x^2-\diff*x-\p=0)}
\rational{d=(\diff)^2+4*\p}
\text{tsol=Posons \(X_1 = -x_1) <br> On se ramène alors à chercher deux nombres \(X_1) et \(x_2) dont la somme vaut \(\tdiff) et le produit vaut \(\tmp).<br>
Ces nombres sont solutions de l'équation du second degré:
<div class="wimscenter">\(\equat).</div>
Le discriminant de ce polynôme est égal à \(\d), ses racines sont \(X_1=\y1) et \(x_2=\x2).<br>
Les deux nombres cherchés initialement sont donc \(x_1=\x1) et \(x_2=\x2).<br>}
#endif
#if defined TARGET_invprdt
\title{Inverses et produit}
\text{intro=la somme des inverses vaut \(\ti) et la somme vaut \(\ts)}
\text{equat=texmath(x^2-\s*x+\p=0)}
\text{tsol=La somme des inverses correspond à \(\displaystyle\frac{x_1+x_2}{x_1x_2}=\ti) <br>
On cherche donc deux nombres dont la somme vaut \(\ts) et le produit vaut \(\tp).<br> \(x_1) et \(x_2) sont solutions de l'équation du second degré:
<div class="wimscenter">\(\equat).</div>
Le discriminant de ce polynôme est égal à \(\d), ses racines sont \(x_1=\x1) et \(x_2=\x2).<br>}
#endif
\statement{Trouver deux nombres \(x_1) et \(x_2), avec \(x_1< x_2), dont \intro.
<p>Valeur de \(x_1):\embed{reply 1,10}</p>
<p>Valeur de \(x_2):\embed{reply 2,10}
</p>}


\answer{x1}{\x1}{type=numeric}
\answer{x2}{\x2}{type=numeric}


\solution{\tsol}
