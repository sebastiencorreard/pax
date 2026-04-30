\title{E pour résoudre une équation du second degré}

\text{code=
\#importation de la librairie mathématiques#
from math import *
def ...
...
...
\#Test#
print(racine2deg(1,5,4))}

\integer{a=randitem(+1,-1)*randint(1..4)}
\integer{c=randitem(+1,-1)*randint(1..5)}
\integer{p=-4*\a*\c}
\integer{b=(\p>0)?randint(1..5):randint(-\p+1..-\p+4)}
\real{xp1=(-\b+sqrt((\b)^2+\p))/2/\a}
\real{xp2=(-\b-sqrt((\b)^2+\p))/2/\a}
\integer{bb=randitem(2,4,6,8,10,12)}
\integer{aa=1}
\integer{cc=(\bb)^2/4}
\real{xO=-\bb/2/\aa}
\text{prob=Résoudre une équation du second degré}
\text{enonce=Soit une fonction polynôme du second degré de la forme \(f(x)=a x^2 + b x+ c \) où \(a\), \(b\) et \(c\) sont des réels.
<br>
Soit \(  \mathcal{C}_f \) la courbe représentative de la fonction \(f\).
<br>
Les solutions, si elles existent, d'une équation du second degré de la forme
 \(a x^2 + b x+ c = 0\) sont les abscisses des points d'intersections éventuels de
 \(  \mathcal{C}_f \) avec l'axe des abscisses.
<h3 style="font-weight: bold;">Résolution de l'équation du second degré \(a x^2 + b x+ c = 0\)
 avec  \(a \ne 0\)</h3>
Le signe du discriminant \({\Delta}\) permet de déterminer le nombre de solutions de l'équation
 \(a x^2 + b x+ c = 0\) avec \(\Delta=b^2-4ac\).
<ul><li>\(\mathbf{\Delta>0}\), l'équation du second degré a <u>deux solutions</u> réelles :
<div class="wimscenter">\(x_1=\frac{-b+\sqrt{\Delta}}{2a}\) et \(x_2=\frac{-b-\sqrt{\Delta}}{2a}\) </div>
</li>
<li>\(\mathbf{\Delta=0}\), l'équation du second degré a <u>une solution</u> réelle :
<div class="wimscenter">\(x_0=\frac{-b}{2a}\)</div>
</li>
<li>\(\mathbf{\Delta<0}\), l'équation du second degré n'a <u>aucune solution</u> réelle.</li>
</ul>}
\text{inst=print(racine2deg(1,5,4))}

\text{question=Écrire une fonction Python intitulée "racine2deg" ayant pour paramètre
 les valeurs de \(a\), \(b\) et \(c\).
 Cette fonction "racine2deg" doit retourner :
 <ul><li>une liste de deux variables \(\left[ x_1,x_2 \right]\) si \(\mathbf{\Delta>0}\)</li>
<li>une liste d'une variable \([x_1]\) si \(\mathbf{\Delta=0}\)</li>
<li>une liste contenant le mot \([\text{'} vide \text{'}]\) si \(\mathbf{\Delta<0}\)</li>
</ul>}


def racine2deg(a,b,c):
  delta=b**2-4*a*c
  if delta > 0:
    racineDeDelta=sqrt(delta)
    racine = [(-b+racineDeDelta)/(2*a),(-b-racineDeDelta)/(2*a)]
  elif delta < 0:
    racine = ['vide']  #liste vide
  else:
     racine = [-b/(2*a)] #liste d un seul élément
  return racine


\text{post='@@@@'+'\eva1'+'=racine2deg(\aa,\bb,\cc)'+'@@@@'+'\eva2'+'=racine2deg(\a,\b,\c)'+'@@@@'+'\eva3'+'=racine2deg(4,3,1)'}
\text{rtest=[\eva1,[\xO]],[\eva2,[\xp1,\xp2]],[\eva3,[vide]]}
