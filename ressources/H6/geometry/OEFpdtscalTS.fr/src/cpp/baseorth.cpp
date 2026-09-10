target=baseorth1 baseorth2 baseorth3 baseorth4 baseorth5

#include "author.inc"
#define TITRE Base orthonormale
#if defined TARGET_baseorth1
# define NUM 1
#endif
#if defined TARGET_baseorth2
# define NUM 2
#endif
#if defined TARGET_baseorth3
# define NUM 3
#endif
#if defined TARGET_baseorth4
# define NUM 4
#endif
#if defined TARGET_baseorth5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_baseorth1
\integer{ux=randint(-10..10)}
\integer{uy=randint(-10..10)}
\integer{n=(\ux)^2+(\uy)^2}
\rational{nx=simplify(\ux/\n)}
\text{x=texmath(\nx)\sqrt{\n}}
\rational{ny=simplify(\uy/\n)}
\text{y=texmath(\ny)\sqrt{\n}}
\text{my=texmath(-\ny)\sqrt{\n}}
\statement{<p>
 Le plan est muni d'un repère orthonormal \((O,\vec{i},\vec{j})).
 Soit \(\vec{u}\left(\begin{array}{c} \ux \\ \uy \end{array}\right)).
 </p>
 <ul><li>
 Trouver un vecteur de norme 1 colinéaire à \(\vec{u}):
<div class="wimscenter"> (\embed{reply1,10}, \embed{reply2,10}).</div>
</li><li>
 Trouver un vecteur de norme 1 orthogonal à \(\vec{u}).
<div class="wimscenter"> (\embed{reply3,10}, \embed{reply4,10}).</div>
</li></ul>
<div class="wims_instruction">Taper "sqrt(a)" pour \(\sqrt{a}).</div>

}
\answer{abscisse 1}{\x1}{type=numeric}
\answer{ordonnée 1}{\y1}{type=numeric}
\answer{abscisse 2}{\x2}{type=numeric}
\answer{ordonnée 2}{\y2}{type=numeric}
\condition{vecteur colinéaire}{(\x1)^2+(\y1)^2=1 and \x1*\uy-\y1*\ux=0}
\condition{vecteur orthogonal}{(\x2)^2+(\y2)^2=1 and \x2*\ux+\y2*\uy=0}
\solution{une solution possible est:
<ul class="wims_nopuce"><li>
 vecteur colinéaire et de norme 1: \(\left(\begin{array}{c} \x \\ \y \end{array}\right)) ou son opposé
 </li><li>
 vecteur orthogonal et de norme 1 \(\left(\begin{array}{c} \my \\ \x \end{array}\right)) ou son opposé
</li></ul>
}
#endif
#if defined TARGET_baseorth2
\integer{ux=randint(-10..10)}
\integer{uy=randint(-10..10)}
\integer{n=(\ux)^2+(\uy)^2}
\rational{nx=simplify(\ux/\n)}
\rational{ny=simplify(\uy/\n)}
\text{x=texmath(\nx)\sqrt{\n}}
\text{y=texmath(\ny)\sqrt{\n}}
\text{my=texmath(-\ny)\sqrt{\n}}
\statement{<p>
 Le plan est muni d'un repère orthonormal \((O,\vec{i},\vec{j})).
 Étant donné un vecteur \(\vec{u}\left(\begin{array}{c} \ux \\ \uy \end{array}\right)),
 déterminer le vecteur \(\vec{v}) colinéaire à \(\vec{u}) et de même sens que \(\vec{u})
 et le vecteur \(\vec{w})
 tels que \((O,\vec{v},\vec{w})) soit un repère orthonormal direct.
 </p>
<div class="wimscenter"> \(\vec{v})=(\embed{reply1,10},\embed{reply2,10})</div>
<div class="wimscenter"> \(\vec{w})=(\embed{reply3,10},\embed{reply4,10})</div>
}
\answer{abscisse v}{\x1}{type=numeric}
\answer{ordonnée v}{\y1}{type=numeric}
\answer{abscisse w}{\x2}{type=numeric}
\answer{ordonnée w}{\y2}{type=numeric}
\condition{vecteur v unitaire}{(\x1)^2+(\y1)^2=1}
\condition{vecteur v  et u colinéaires et de même sens}{\x1*\uy-\y1*\ux=0 and \x1*\ux>=0 and \y1*\uy>=0}
\condition{vecteur w unitaire}{(\x2)^2+(\y2)^2=1}
\condition{vecteur w orthogonal à u}{\x2*\ux+\y2*\uy=0}
\condition{(v,w) orthonormal direct}{\x2=-\y1 and \y2=\x1}
\solution{\(\vec{v}\left(\begin{array}{c} \x \\ \y \end{array}\right)) et \(\vec{w}\left(\begin{array}{c} \my \\ \x \end{array}\right))}
#endif

#if (defined TARGET_baseorth3  || defined TARGET_baseorth4 )
\integer{ux=randint(-10..10)}
\integer{uy=randint(-10..10)}
\integer{n=(\ux)^2+(\uy)^2}
\rational{nx=simplify(\ux/\n)}
\rational{ny=simplify(\uy/\n)}
\text{a=texmath(maxima(\nx*s))}
\text{a=wims(replace internal s by \sqrt{\n} in \a)}
\text{b=texmath(maxima(\ny*s))}
\text{b=wims(replace internal s by \sqrt{\n} in \b)}
\text{c=texmath(maxima(-\ny*s))}
\text{c=wims(replace internal s by \sqrt{\n} in \c)}
\function{fx=\nx*sqrt(\n)*x+\ny*sqrt(\n)*y}
\function{fy=-\ny*sqrt(\n)*x+\nx*sqrt(\n)*y}

# if defined TARGET_baseorth3
\statement{<p>
 Le plan est muni d'un repère orthonormal \((O,\vec{i},\vec{j})).
 On se donne une base orthonormale \(\vec{u}(\a,\b)) et \(\vec{v}(\c,\a)).
 </p><p>
 Étant donné un vecteur quelconque \(\vec{w}=x\vec{i}+y\vec{j}),
 donner ses coordonnées \((X,Y)\) dans la base \((\vec{u},\vec{v})\).</p>
<div class="wimscenter"><label for="reply1">\(X=\)</label> \embed{reply1}</div>
<div class="wimscenter"><label for="reply2">\(Y=\)</label>\embed{reply2}.</div>
}
\answer{\(X\)}{\fx}{type=function}
\answer{\(Y\)}{\fy}{type=function}
# else
\real{vx=-\ny*sqrt(\n)}
\real{vy=\nx*sqrt(\n)}
\integer{xw=randint(1..5)*randint(1,-1)}
\integer{yw=randint(1..5)*randint(1,-1)}
\text{tw=texmath(maxima(\xw*x+\yw*y))}
\text{tw=wims(replace internal x by \vec{i} in \tw)}
\text{tw=wims(replace internal y by \vec{j} in \tw)}
\rational{nX=simplify(\xw*\nx+\yw*\ny)}
\rational{nY=simplify(-\xw*\ny+\yw*\nx)}
\real{fx=\nX*sqrt(\n)}
\real{fy=\nY*sqrt(\n)}
\statement{
<p>
 Le plan est muni d'un repère orthonormal \((O,\vec{i},\vec{j})).
 Soit le vecteur unitaire \(\vec{u}(\a,\b)).</p>
 Déterminer le vecteur \(\vec{v}) tel que \((\vec{u},\vec{v})) soit une base
 orthonormale directe.
<div class="wimscenter"><label for="reply1">\(\vec{v}\)=</label>(\embed{reply1,10},\embed{reply2,10})</div>
 Soit le vecteur \(\vec{w}=\tw). Donner ses coordonnées dans la base \((\vec{u},\vec{v})).
<div class="wimscenter"><label for="reply3">\(X=\)</label> \embed{reply3} </div>
<div class="wimscenter"><label for="reply4">\(Y=\)</label> \embed{reply4} </div>
}
\answer{abscisse de v}{\vx}{type=numeric}
\answer{ordonnée de v}{\vy}{type=numeric}
\answer{X}{\fx}{type=function}
\answer{Y}{\fy}{type=function}
\solution{ \(\vec{v})(\vx,\vy) et \(X=\nX \sqrt{\n}), \(Y=\nY \sqrt{\n})}
# endif
#endif
#if defined TARGET_baseorth5
\matrix{V=slib(matrix/orthogonal 3,3)}
\matrix{a=\V[1;]}
\matrix{b=\V[2;]}
\matrix{c=\V[3;]}
\integer{x=randint(1..10)*randint(1,-1)}
\integer{y=randint(1..10)*randint(1,-1)}
\matrix{v=pari(print(\x*[\a]+\y*[\b]))}

\statement{
<p>
 L'espace est muni d'un repère orthonormal \((O,\vec{i},\vec{j},\vec{k})).
 On considère le vecteur unitaire
\(\vec{a}\left(\begin{array}{c} \a[1] \\ \a[2] \\ \a[3] \end{array}\right))
 et un vecteur \(\vec{v}\left(\begin{array}{c} \v[1] \\ \v[2] \\ \v[3] \end{array}\right)).
 </p>
<ol>
<li>Déterminer les coordonnées d'un vecteur unitaire \(\vec{b}) orthogonal à \(\vec{a}) et qui s'expriment comme combinaison linéaire des vecteurs \(\vec{a}) et \(\vec{v}).
<div class="wimscenter">\(\vec{b})=(\embed{reply1,7},\embed{reply2,7},\embed{reply3,7})</div>
</li><li>
Déterminer les coordonnées d'un vecteur unitaire \(\vec{c}) orthogonal à
\(\vec{a}) et \(\vec{b}).
<div class="wimscenter">\(\vec{c})=(\embed{reply4,7},\embed{reply5,7},\embed{reply6,7})</div>
</li>
</ol>
}
\answer{abscisse de b}{\x1}{type=numeric}
\answer{ordonnée de b}{\y1}{type=numeric}
\answer{cote de b}{\z1}{type=numeric}
\answer{abscisse de b}{\x2}{type=numeric}
\answer{ordonnée de b}{\y2}{type=numeric}
\answer{cote de b}{\z2}{type=numeric}
\condition{vecteur b}{(\x1=\b[1] and \y1=\b[2] and \z1=\b[3]) or  (\x1=-\b[1] and \y1=-\b[2] and \z1=-\b[3])}
\condition{vecteur c}{(\x2=\c[1] and \y2=\c[2] and \z2=\c[3]) or  (\x2=-\c[1] and \y2=-\c[2] and \z2=-\c[3])}
\solution{ On peut choisir \(\vec{b}(\b[1],\b[2],\b[3])) ou son opposé.<p>
 On peut choisir \(\vec{c}(\c[1],\c[2],\c[3])) ou son opposé.</p>}
#endif
