target=coefracine1 coefracine2 coefracine3 coefracine4 coefracine5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#if defined TARGET_coefracine1
# define NUM 1
#endif
#if defined TARGET_coefracine2
# define NUM 2
#endif
#if defined TARGET_coefracine3
# define NUM 3
#endif
#if defined TARGET_coefracine4
# define NUM 4
#endif
#if defined TARGET_coefracine5
# define NUM 5
#endif
#include "lang_titles.inc"

#if defined TARGET_coefracine1
\integer{a=randint(1..3)}
\integer{u=random(-1,1)*randint(1..8)}
\integer{v=random(-1,1)*randint(1..8)}
\integer{v=\v/3=\u/2?\v+1:\v}
\rational{x1=\u/2<\v/3?\u/2:\v/3}
\rational{x2=\u/2<\v/3?\v/3:\u/2}
\ifval{\a=2 and abs(\x2)<abs(\x1)}{
  \rational{x11=\x1}
  \rational{x1=\x2}
  \rational{x2=\x11}
}

\rational{s=\x1+\x2}
\rational{diff=\x2-(\x1)}
\rational{i=1/(\x1)+1/(\x2)}
\rational{p=\x1*(\x2)}
\rational{p1=\s/(\i)}
\text{ts=texmath(\s)}
\text{tp=texmath(\p)}
\text{tdiff=texmath(\diff)}
\text{ti=texmath(\i)}
\text{r1=\x1}
\text{r2=\x2}
\if{\a=1}{
  \text{intro=dont la somme vaut \(\ts) et le produit \(\tp)}
  \text{equat=texmath(x^2-\s*x+\p=0)}
  \rational{d=(\s)^2-4*(\p)}
  \text{y1=x_1}
  \text{y2=x_2}
  \text{condition=\(x_1 < x_2\)}
}
\if{\a=2}{
  \text{intro=dont la différence \(x_2-\x_1\) vaut \(\tdiff) et dont le produit vaut \(\tp)}
  \text{equat=texmath(x^2-\diff*x-\p=0)}
  \rational{d=(\diff)^2+4*(\p)}
  \text{y1=-x_1}
  \text{y2=x_2}
  \rational{r1=-(\x1)}
  \text{condition=\(|x_1| \leq |x_2|\)}
}
\if{\a=3}{
  \text{intro=dont la somme vaut \(\ts) et dont la somme des inverses vaut \(\ti)}
  \text{equat=texmath(x^2-\s*x+\p1=0)}
  \rational{d=(\s)^2-4*(\p1)}
  \text{y1=x_1}
  \text{y2=x_2}
  \text{condition=\(x_1 < x_2\)}
}
\statement{<p>
  Trouver deux nombres \(x_1) et \(x_2), avec \condition \intro.
  </p>
  <ul class="wims_nopuce">
    <li>
    <label for="reply1">Valeur de \(x_1)</label>:\embed{reply 1,10}
    </li><li>
    <label for="reply2">Valeur de \(x_2)</label>:\embed{reply 2,10}
    </li>
  </ul>
}

\answer{x1}{\x1}{type=numexp}
\answer{x2}{\x2}{type=numexp}

\feedback{(\a=2 and \reply1=-(\x2) and \reply2=-(\x1)) or
    (\a!=2 and \reply1=\x2 and \reply2=\x1)}{
  \(x_1=\reply1\) et \(x_2=\reply2\) ne vérifient pas \condition.
}

\solution{\(\y1) et \(\y2) sont solutions de l'équation du second degré&nbsp;:
<div class="wimscenter">\(\equat).</div>
Le discriminant de ce polynôme est égal à \(\d), ses racines sont \(\r1) et \(\r2).
De plus, \(x_1=\x1) et \(x_2=\x2) vérifient la condition \condition.
}
#endif
#if defined TARGET_coefracine2
\text{val=slib(pythagore 100)}
\integer{x=\val[1]<\val[2]?\val[1]:\val[2]}
\integer{y=\val[1]<\val[2]?\val[2]:\val[1]}
\integer{s=\x+\y}
\integer{P=\x*\y}

\integer{h=\val[3]}
\integer{p=\x+\y+\h}
\statement{<p>
  Un triangle rectangle a une hypoténuse de longueur \h cm et un périmètre de \p cm.
 Quelles sont les longueurs des deux autres côtés?
 </p>
<ul class="wims_nopuce"><li>
  <label for="reply1">Petit côté de l'angle droit</label> = \embed{reply1,4}cm
</li><li>
  <label for="reply2">Grand côté de l'angle droit</label> = \embed{reply2,4}cm
</li></ul>
}
\answer{Petit côté}{\x}{type=numeric}
\answer{Grand côté}{\y}{type=numeric}
\solution{Notons \(x) le petit côté et \(y) le grand côté de l'angle droit.<br>
  D'après les hypothèses on a: \(x^2+y^2=\h^2) et \(x+y+\h=\p).
<p>
  On obtient facilement \(x + y=\s) et \(x y=\P).
</p>
}
#endif
#if defined TARGET_coefracine3
\text{val=slib(pythagore 100)}
\integer{x=\val[1]<\val[2]?\val[1]:\val[2]}
\integer{y=\val[1]<\val[2]?\val[2]:\val[1]}
\integer{s=\x+\y}
\integer{P=\x*\y}
\real{a=\P/2}

\integer{h=\val[3]}
\integer{p=\x+\y+\h}
\statement{<p>
  Un triangle rectangle a une hypoténuse de longueur \h cm et et
  une aire de \a cm<sup>2</sup>.
</p>
 Quelles sont les longueurs des deux autres côtés?
<ul class="wims_nopuce"><li>
  <label for="reply1">Petit côté de l'angle droit</label> = \embed{reply1,4}cm
</li><li>
  <label for="reply2">Grand côté de l'angle droit</label> = \embed{reply2,4}cm
</li></ul>
}
\answer{Petit côté}{\x}{type=numeric}
\answer{Grand côté}{\y}{type=numeric}
\solution{Notons \(x) le petit côté et \(y) le grand côté de l'angle droit.<br>
  D'après les hypothèses on a: \(x^2+y^2=\h^2) et \(\frac{xy}{2} =\a).<p>
  On obtient facilement \(x+y=\s) et \(xy=\P).
</p>
}
#endif

#if defined TARGET_coefracine4
\integer{a=randint(1..4)*randint(1,-1)}
\integer{x1=randint(1..8)*randint(1,-1)}
\integer{x2=\x1+randint(1..8)*randint(1,-1)}
\integer{x2=\x2=0? -\x1}
\integer{s=\x1+\x2}
\rational{sd=simplify(\s/2)}
\text{sd=texmath(\sd)}
\integer{p=\x1*\x2}
\integer{b=-\a*\s}
\integer{c=\p*\a}

\statement{
  On considère une parabole \(\mathcal{P}) qui coupe l'axe des ordonnées au point \(A(0;\c))
  et dont l'axe de symétrie a pour équation \(x=\sd).<br>
  On sait de plus que le produit des abscisses \(x_1) et \(x_2)
  des points d'intersection de \(\mathcal{P}) avec l'axe des abscisses vaut \(\p).
<p>
  On note \(y=a x^2+b x +c) l'équation de \(\mathcal{P}).</p>
  Déterminer les réels \(a), \(b) et \(c):
<ul class="wims_nopuce">
<li>
<label for="reply1">\(a=)</label> \embed{reply1,4}
</li><li>
<label for="reply2">\(b=)</label> \embed{reply2,4}
</li><li>
<label for="reply3">\(c=)</label> \embed{reply3,4}
</li>
</ul>
}
\answer{a}{\a}{type=numeric}
\answer{b}{\b}{type=numeric}
\answer{c}{\c}{type=numeric}
#endif

#if defined TARGET_coefracine5
\integer{x=randint(3..10)}
\integer{y=randint(8..20)}
\integer{s=\x+\y}
\rational{ep=simplify(1/\x+1/\y)}
\rational{ep=(\ep)^(-1)}
\text{ep=texmath(\ep)}
\statement{
\(R_1) et \(R_2) sont deux résistances inconnues.
<ul><li>
  Si on les branche en parallèle, on obtient une résistance équivalente de \(\ep \Omega).
</li><li>
  Si on les branche en série, on obtient une résistance équivalente de \(\s \Omega).
</li></ul>
  Déterminer les valeurs de \(R_1) et \(R_2).
<ul class="wims_nopuce">
<li>
<label for="reply1">\(R_1=) </label>\embed{reply1,4}
</li><li>
<label for="reply2">\(R_2=) </label>\embed{reply2,4}
</li>
</ul>
}
\hint{Quand les résistances sont en série, la résistance totale est la somme des résistances.<br>
Quand les résistances sont en parallèle, les conductances s'ajoutent. L'inverse de la résistance totale
est la somme des des inverses des résistances.}
\answer{\(R_1)}{\r1}{type=numeric}
\answer{\(R_2)}{\r2}{type=numeric}
\condition{valeurs des résistances}{(\r1=\x and \r2=\y) or (\r1=\y and \r2=\x)}
#endif
